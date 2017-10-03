
/*
 * Copyright (c) 2017, The Linux Foundation. All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted (subject to the limitations in the
 * disclaimer below) provided that the following conditions are met:
 *
 *    * Redistributions of source code must retain the above copyright
 *      notice, this list of conditions and the following disclaimer.
 *
 *    * Redistributions in binary form must reproduce the above
 *      copyright notice, this list of conditions and the following
 *      disclaimer in the documentation and/or other materials provided
 *      with the distribution.
 *
 *    * Neither the name of The Linux Foundation nor the names of its
 *      contributors may be used to endorse or promote products derived
 *      from this software without specific prior written permission.
 *
 * NO EXPRESS OR IMPLIED LICENSES TO ANY PARTY'S PATENT RIGHTS ARE
 * GRANTED BY THIS LICENSE. THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT
 * HOLDERS AND CONTRIBUTORS "AS IS" AND ANY EXPRESS OR IMPLIED
 * WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF
 * MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED.
 * IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE FOR
 * ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
 * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE
 * GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
 * INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER
 * IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR
 * OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN
 * IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 *
 */
#include <hexagon_protos.h>
#include <stdint.h>
#include <string.h>
#include <nn_graph.h>
#include <nn_asm_ops.h>
#include "quantize.h"

#define MAX_THREADS 3

struct tensor_copy_scaled_opstate {
	int32_t height, width, depth,d0;
	uint8_t const * srcp;
	int32_t src_batch_stride;
	int32_t src_row_stride;
	int32_t src_d32_stride;

	uint8_t * dstp;
	int32_t dst_batch_stride;
	int32_t dst_row_stride;
	int32_t dst_d32_stride;

	uint32_t scl_off;

	int nd32;		// # of d32 operations
	int n_opers;	// nd32 * batches
	volatile int next_oper;
	void (*scaled_aligned_copy_fp)(
			uint8_t *, int32_t,
			uint8_t const * , int32_t ,
			int32_t, int32_t, int32_t );

	struct tcopy_threadinfo {
		struct tensor_copy_scaled_opstate * opst_p;
		nn_sem_t done_sem;
	} thrinfo[MAX_THREADS];
};

static void scaled_copy_operation( struct nn_graph *nn, void * thrinfop);
static void scalemem_d32_reference(
		uint8_t * dstp, int32_t dst_row_pitch,
		uint8_t const * srcp, int32_t src_row_pitch,
		int32_t height,
		int32_t width,
		int32_t scl_off );

//
// This copies one d32 tensor to another, with
// optional linear scaling out = in*a +b
//
//  Caller must:
//    - pre-allocate the output tensor
//    - must be the same size as input tensor
//    - must have the same depth_before padding
//   -  should have same width_before padding (modulo 4)  (else, use_hvx will be ignored).
//
//  NOTE: this currently does 32-bit aligned stores (i.e. it writes all of the depth extent,
//  including the padding).
//
//
//
//  The scaling is done as  out[i] = (in[i] *scale +   offset*256   +  16384) >> 15
//
//  In more detail:
//      (1)  p = (in[i] * scale ) >> 8;   [ fits in i16]
//      (2)  t  = add(p, offset)        [ saturate to i16]
//      (3)  out[i] = saturate_u8(   (t+64) >> 7 )
//
//  => offset = 0, scale in range 32704..32767 will be handled as a copy
//  => offset = 32640, scale = -32768 .. -32705  will result in a 1's complement operation.
//
// This is used for add_d32 and sub_d32 operator, when one of the inputs is a scalar, the
// operation can be done by a copy (with possible range extension).
// Also, for mul_d32 when one of the inputs is  a scalar, the op can be done by a copy (or
// inversion, when the scalar is negative).
//
// Normally returns 0; can return -1 if it logs an error.
//
int
tensor_copy_scaled_d32(
		struct nn_graph *nn,
		struct tensor const *tensor_src,
		struct tensor const *tensor_dst,
		int16_t scale,
		int16_t offset,
		int use_hvx,
		int max_threads )
{
	struct tensor_copy_scaled_opstate ops;
	int i;
	int batches = tensor_src->shape.batches;
	ops.height = tensor_src->shape.height;
	ops.width = tensor_src->shape.width;
	int depth = tensor_src->shape.depth;
	int d0 = tensor_src->format.depth_pad[0];

	ops.depth = depth;
	ops.d0 = d0;

	ops.srcp = tensor_location_bhw_d32( tensor_src, 0,0,0);
	ops.src_batch_stride = tensor_batch_stride_d32( tensor_src );
	ops.src_row_stride = tensor_row_stride_d32( tensor_src );
	ops.src_d32_stride = tensor_d32_stride_d32( tensor_src );

	ops.dstp = tensor_location_bhw_d32( tensor_dst, 0,0,0);
	ops.dst_batch_stride = tensor_batch_stride_d32( tensor_dst );
	ops.dst_row_stride = tensor_row_stride_d32( tensor_dst );
	ops.dst_d32_stride = tensor_d32_stride_d32( tensor_dst );

	ops.nd32 = (unsigned)( tensor_src->format.depth_pad[0] + depth + 31)/32;

	unsigned align = ((size_t)ops.srcp ^ (size_t)ops.dstp) & 127;
	if(  (align &31)!= 0 ){
		return errlog( nn, "tensor_copy_scaled_d32: tensors not aligned");
	}

	ops.scaled_aligned_copy_fp = ( use_hvx  && (align ==0))? scalemem_d32_hvx: scalemem_d32_reference;

	ops.n_opers = ops.nd32 * batches;

	ops.next_oper = 0;

	ops.scl_off = (uint16_t)scale | (offset << 16);

	int num_threads = min_i32( MAX_THREADS, ops.n_opers );
	for( i = 0; i < num_threads; i++ ){
		ops.thrinfo[i].opst_p = &ops;
		nn_sem_init(&ops.thrinfo[i].done_sem,0);
		nn_os_work_for_vector(nn,scaled_copy_operation,&ops.thrinfo[i]);
	}

	for( i = 0; i < num_threads; i++ ){
		nn_sem_wait(&ops.thrinfo[i].done_sem);
	}

	return 0;

}

static void
scaled_copy_operation( struct nn_graph *nn, void * thrinfovp)
{
	struct tcopy_threadinfo * thrinfop = (struct tcopy_threadinfo *)thrinfovp;

	struct tensor_copy_scaled_opstate const * ops = thrinfop->opst_p;
	int taskno;

	int width = ops->width;
	int height= ops->height;
	//int dend = ops->d0 + ops->depth;
	int scl_off = ops->scl_off;
	int dst_row_stride = ops->dst_row_stride;
	int src_row_stride = ops->src_row_stride;
	int nd32 = ops->nd32;

	while( taskno = __sync_fetch_and_add(&ops->next_oper, 1), taskno < ops->n_opers){
		int d32_idx = taskno;
		int batch_idx = 0;
		if( taskno >= nd32){
			batch_idx = taskno / nd32;
			d32_idx -= batch_idx * nd32;
		}

		uint8_t const * srcp = ops->srcp + batch_idx*ops->src_batch_stride + d32_idx*ops->src_d32_stride;
		uint8_t * dstp = ops->dstp + batch_idx*ops->dst_batch_stride + d32_idx*ops->dst_d32_stride;
		// (currently this processes the entire depth range)
		// find depth range
		//int dlo =  (d32_idx == 0)? ops->d0 : 0;
		//int dhi = min_i32( 32, dend - 32* d32_idx);

		(*ops->scaled_aligned_copy_fp)(
				dstp, dst_row_stride,
				srcp, src_row_stride,
				height, width, scl_off );
	}
	nn_sem_post(&thrinfop->done_sem);
}

static void scalemem_d32_reference(
		uint8_t * dstp, int32_t dst_row_pitch,
		uint8_t const * srcp, int32_t src_row_pitch,
		int32_t height,
		int32_t width,
		int32_t scl_off )
{
	int ih, iw;

	if( (scl_off >> 6 )== 511 ){
		int rowlen = width*32;
		// can be done as a copy
		for( ih =0; ih < height; ih++){
			memcpy( dstp, srcp, rowlen);
			dstp += dst_row_pitch;
			srcp += src_row_pitch;
		}
	}else if( (scl_off>>6) == (0x7f808000>>6) ){	// 1's complement
		int nw = width * 2;
		for( ih =0; ih < height; ih++){
			uint64_t const * __restrict src64 = (uint64_t const *)( srcp + src_row_pitch * ih );
			uint64_t  * __restrict dst64 = (uint64_t *)( dstp + dst_row_pitch * ih );
			for( iw = 0; iw < nw; iw++){
				uint64_t x0 = ~src64[2*iw];
				uint64_t x1 = ~src64[2*iw+1];
				dst64[2*iw]= x0;
				dst64[2*iw+1]= x1;
			}
		}
	}else {	 // general case
		uint32_t scl_lo = Q6_R_vsplatb_R(scl_off);
		uint32_t scl_hi = Q6_R_vsplatb_R(scl_off>>8);
		uint32_t offshh = Q6_R_combine_RhRh( scl_off, scl_off );
		uint64_t voffset = Q6_P_combine_RR( offshh, offshh);

		int nw = width * 4;
		for( ih =0; ih < height; ih++){
			uint32_t const * __restrict src32 = (uint32_t const *)( srcp + src_row_pitch * ih );
			uint32_t  * __restrict dst32 = (uint32_t *)( dstp + dst_row_pitch * ih );
			for( iw = 0; iw < nw; iw++){	// 8 pixels at a time
				uint32_t pix0 = src32[2*iw];
				uint32_t pix1 = src32[2*iw+1];

				uint64_t prod_0 = Q6_P_vmpybu_RR(pix0, scl_lo);
				prod_0 = Q6_P_vmpybsuacc_RR( Q6_P_vlsrh_PI(prod_0,8), scl_hi, pix0);
				prod_0 = Q6_P_vaddh_PP_sat( prod_0, voffset );

				uint64_t prod_1 = Q6_P_vmpybu_RR(pix1, scl_lo);
				prod_1 = Q6_P_vmpybsuacc_RR( Q6_P_vlsrh_PI(prod_1,8), scl_hi, pix1);
				prod_1 = Q6_P_vaddh_PP_sat( prod_1, voffset );


				dst32[2*iw] = Q6_R_vasrhub_PI_rnd_sat(prod_0, 7);
				dst32[2*iw+1] = Q6_R_vasrhub_PI_rnd_sat(prod_1, 7);
			}
		}
	}
	return;

}

