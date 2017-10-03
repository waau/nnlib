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

#include <stdint.h>

const uint8_t const_Count128[128] __attribute__((aligned(128))) = {
		0,  1,  2,  3,  4,  5,  6,  7,  8,  9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20, 21, 22, 23, 24, 25, 26, 27, 28, 29, 30, 31,
	   32, 33, 34, 35, 36, 37, 38, 39, 40, 41, 42, 43, 44, 45, 46, 47, 48, 49, 50, 51, 52, 53, 54, 55, 56, 57, 58, 59, 60, 61, 62, 63,
	   64, 65, 66, 67, 68, 69, 70, 71, 72, 73, 74, 75, 76, 77, 78, 79, 80, 81, 82, 83, 84, 85, 86, 87, 88, 89, 90, 91, 92, 93, 94, 95,
	   96, 97, 98, 99,100,101,102,103,104,105,106,107,108,109,110,111,112,113,114,115,116,117,118,119,120,121,122,123,124,125,126,127
};

const uint8_t const_Count64[128] __attribute__((aligned(128))) = {
		0,  1,  2,  3,  4,  5,  6,  7,  8,  9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20, 21, 22, 23, 24, 25, 26, 27, 28, 29, 30, 31,
	   32, 33, 34, 35, 36, 37, 38, 39, 40, 41, 42, 43, 44, 45, 46, 47, 48, 49, 50, 51, 52, 53, 54, 55, 56, 57, 58, 59, 60, 61, 62, 63,
		0,  1,  2,  3,  4,  5,  6,  7,  8,  9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20, 21, 22, 23, 24, 25, 26, 27, 28, 29, 30, 31,
	   32, 33, 34, 35, 36, 37, 38, 39, 40, 41, 42, 43, 44, 45, 46, 47, 48, 49, 50, 51, 52, 53, 54, 55, 56, 57, 58, 59, 60, 61, 62, 63
};

const uint8_t const_Count32[128] __attribute__((aligned(128))) = {
		0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20,21,22,23,24,25,26,27,28,29,30,31,
		0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20,21,22,23,24,25,26,27,28,29,30,31,
		0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20,21,22,23,24,25,26,27,28,29,30,31,
		0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20,21,22,23,24,25,26,27,28,29,30,31
};


//
// 1st 3 are a for 'log2(x-1)' function, 2nd-order poly x 16-entry LUT
//
// 2nd 3 are for pow2(-x),  2nd-order poly x 16-entry LUT
//
const
int16_t lut_Log2_and_Pow2[6*64] __attribute__ ((aligned(128))) = {
  0,     0,   2866,  0,  5568,  0,  8124,  0,  10549, 0,  12856, 0,  15055, 0,  17156, 0,
  19168, 0,  21098,  0,  22952, 0,  24736, 0,  26455, 0,  28114, 0,  29717, 0,  31267, 0,
  0,     0,  0,      0,  0,     0,  0,     0,  0,     0,  0,     0,  0,     0,  0,     0,
  0,     0,  0,      0,  0,     0,  0,     0,  0,     0,  0,     0,  0,     0,  0,     0,

  23622, 0,  22233,  0,  20999, 0,  19895, 0,  18901, 0,  18002, 0,  17184, 0,  16438, 0,
  15753, 0,  15123,  0,  14542, 0,  14004, 0,  13504, 0,  13038, 0,  12604, 0,  12198, 0,
  0,     0,  0,      0,  0,     0,  0,     0,  0,     0,  0,     0,  0,     0,  0,     0,
  0,     0,  0,      0,  0,     0,  0,     0,  0,     0,  0,     0,  0,     0,  0,     0,

  -5561, 0,  -4942,  0,  -4422, 0,  -3980, 0,  -3601, 0,  -3274, 0,  -2989, 0,  -2740, 0,
  -2521, 0,  -2327,  0,  -2155, 0,  -2001, 0,  -1863, 0,  -1739, 0,  -1626, 0,  -1525, 0,
  0,     0,  0,      0,  0,     0,  0,     0,  0,     0,  0,     0,  0,     0,  0,     0,
  0,     0,  0,      0,  0,     0,  0,     0,  0,     0,  0,     0,  0,     0,  0,     0,
/////////////////

  32767,  0, 31379,  0, 30048,  0, 28774,  0, 27554,  0, 26386,  0, 25268,  0, 24196,  0,
  23170,  0, 22188,  0, 21247,  0, 20347,  0, 19484,  0, 18658,  0, 17867,  0, 17109,  0,
  0,     0,  0,      0,  0,     0,  0,     0,  0,     0,  0,     0,  0,     0,  0,     0,
  0,     0,  0,      0,  0,     0,  0,     0,  0,     0,  0,     0,  0,     0,  0,     0,

 -22709,  0,-21746,  0,-20824,  0,-19941,  0,-19096,  0,-18286,  0,-17511,  0,-16769,  0,
 -16058,  0,-15377,  0,-14725,  0,-14101,  0,-13503,  0,-12930,  0,-12382,  0,-11857,  0,
  0,     0,  0,      0,  0,     0,  0,     0,  0,     0,  0,     0,  0,     0,  0,     0,
  0,     0,  0,      0,  0,     0,  0,     0,  0,     0,  0,     0,  0,     0,  0,     0,

   7703,  0,  7377,  0,  7064,  0,  6765,  0,  6478,  0,  6203,  0,  5940,  0,  5688,  0,
   5447,  0,  5216,  0,  4995,  0,  4783,  0,  4580,  0,  4386,  0,  4200,  0,  4022,  0,
  0,     0,  0,      0,  0,     0,  0,     0,  0,     0,  0,     0,  0,     0,  0,     0,
  0,     0,  0,      0,  0,     0,  0,     0,  0,     0,  0,     0,  0,     0,  0,     0
};

//
// tables for 'fracdivide'
// two lookup tables of 32 x int16 (k1 in even lanes, k2 in odd)
//
const
int16_t lut_fracdivide_k1k2[6*64] __attribute__ ((aligned(128))) = {
        1023, 30784, 989, 28915,        955, 27153, 921, 25488,
        887, 23913, 854, 22422,         820, 21007, 786, 19662,
        753, 18383, 719, 17165,         686, 16004, 653, 14895,
        620, 13836, 586, 12823,         553, 11853, 520, 10923,

        487, 10032, 454, 9176,          421, 8353, 389, 7562,
        356, 6801, 323, 6068,            291, 5362, 258, 4681,
        226, 4024, 193, 3390,           161, 2777, 129, 2185,
         96, 1612, 64, 1057,             32, 520, 0, 0
};

//
// lut for reciprocal square root
// this is used with a vlut32, with even lanes being
//  16..63 (to actually do the lookup) and odd lanes being 0
// (so those results will be 0).
const
int16_t lut_root_recip[64] __attribute__ ((aligned(128))) = {
	   0, 0, 0, 0,    0, 0, 0, 0,
	   0, 0, 0, 0,    0, 0, 0, 0,
	   63, 61, 60, 58,   57, 55, 54, 53,
	   52, 51, 50, 49,   48, 47, 46, 46,
	   45, 44, 44, 43,   42, 42, 41, 41,
	   40, 40, 39, 39,   38, 38, 38, 37,
	   37, 36, 36, 36,   35, 35, 35, 34,
	   34, 34, 33, 33,   33, 33, 32, 32
};

// table of reciprocals, as floats.

const
float lut_reciprocal[128] __attribute__ ((aligned(128))) = {
	    0x1.000000p+00f,  /* 1/1 = 1.000000000 */
	    0x8.000000p-04f,  /* 1/2 = 0.500000000 */
	    0x5.555558p-04f,  /* 1/3 = 0.333333343 */
	    0x4.000000p-04f,  /* 1/4 = 0.250000000 */
	    0x3.333334p-04f,  /* 1/5 = 0.200000003 */
	    0x2.AAAAACp-04f,  /* 1/6 = 0.166666672 */
	    0x2.492494p-04f,  /* 1/7 = 0.142857149 */
	    0x2.000000p-04f,  /* 1/8 = 0.125000000 */
	    0x1.C71C72p-04f,  /* 1/9 = 0.111111112 */
	    0x1.99999Ap-04f,  /* 1/10 = 0.100000001 */
	    0x1.745D18p-04f,  /* 1/11 = 0.090909094 */
	    0x1.555556p-04f,  /* 1/12 = 0.083333336 */
	    0x1.3B13B2p-04f,  /* 1/13 = 0.076923080 */
	    0x1.24924Ap-04f,  /* 1/14 = 0.071428575 */
	    0x1.111112p-04f,  /* 1/15 = 0.066666670 */
	    0x1.000000p-04f,  /* 1/16 = 0.062500000 */
	    0xF.0F0F10p-08f,  /* 1/17 = 0.058823530 */
	    0xE.38E390p-08f,  /* 1/18 = 0.055555556 */
	    0xD.794360p-08f,  /* 1/19 = 0.052631579 */
	    0xC.CCCCD0p-08f,  /* 1/20 = 0.050000001 */
	    0xC.30C310p-08f,  /* 1/21 = 0.047619049 */
	    0xB.A2E8C0p-08f,  /* 1/22 = 0.045454547 */
	    0xB.216430p-08f,  /* 1/23 = 0.043478262 */
	    0xA.AAAAB0p-08f,  /* 1/24 = 0.041666668 */
	    0xA.3D70A0p-08f,  /* 1/25 = 0.039999999 */
	    0x9.D89D90p-08f,  /* 1/26 = 0.038461540 */
	    0x9.7B4260p-08f,  /* 1/27 = 0.037037037 */
	    0x9.249250p-08f,  /* 1/28 = 0.035714287 */
	    0x8.D3DCB0p-08f,  /* 1/29 = 0.034482758 */
	    0x8.888890p-08f,  /* 1/30 = 0.033333335 */
	    0x8.421080p-08f,  /* 1/31 = 0.032258064 */
	    0x8.000000p-08f,  /* 1/32 = 0.031250000 */
	    0x7.C1F080p-08f,  /* 1/33 = 0.030303031 */
	    0x7.878788p-08f,  /* 1/34 = 0.029411765 */
	    0x7.507508p-08f,  /* 1/35 = 0.028571429 */
	    0x7.1C71C8p-08f,  /* 1/36 = 0.027777778 */
	    0x6.EB3E48p-08f,  /* 1/37 = 0.027027028 */
	    0x6.BCA1B0p-08f,  /* 1/38 = 0.026315790 */
	    0x6.906908p-08f,  /* 1/39 = 0.025641026 */
	    0x6.666668p-08f,  /* 1/40 = 0.025000000 */
	    0x6.3E7060p-08f,  /* 1/41 = 0.024390243 */
	    0x6.186188p-08f,  /* 1/42 = 0.023809524 */
	    0x5.F417D0p-08f,  /* 1/43 = 0.023255814 */
	    0x5.D17460p-08f,  /* 1/44 = 0.022727273 */
	    0x5.B05B08p-08f,  /* 1/45 = 0.022222223 */
	    0x5.90B218p-08f,  /* 1/46 = 0.021739131 */
	    0x5.726208p-08f,  /* 1/47 = 0.021276595 */
	    0x5.555558p-08f,  /* 1/48 = 0.020833334 */
	    0x5.397828p-08f,  /* 1/49 = 0.020408163 */
	    0x5.1EB850p-08f,  /* 1/50 = 0.020000000 */
	    0x5.050508p-08f,  /* 1/51 = 0.019607844 */
	    0x4.EC4EC8p-08f,  /* 1/52 = 0.019230770 */
	    0x4.D48740p-08f,  /* 1/53 = 0.018867925 */
	    0x4.BDA130p-08f,  /* 1/54 = 0.018518519 */
	    0x4.A79048p-08f,  /* 1/55 = 0.018181818 */
	    0x4.924928p-08f,  /* 1/56 = 0.017857144 */
	    0x4.7DC120p-08f,  /* 1/57 = 0.017543860 */
	    0x4.69EE58p-08f,  /* 1/58 = 0.017241379 */
	    0x4.56C798p-08f,  /* 1/59 = 0.016949153 */
	    0x4.444448p-08f,  /* 1/60 = 0.016666668 */
	    0x4.325C50p-08f,  /* 1/61 = 0.016393442 */
	    0x4.210840p-08f,  /* 1/62 = 0.016129032 */
	    0x4.104108p-08f,  /* 1/63 = 0.015873017 */
	    0x4.000000p-08f,  /* 1/64 = 0.015625000 */
	    0x3.F03F04p-08f,  /* 1/65 = 0.015384615 */
	    0x3.E0F840p-08f,  /* 1/66 = 0.015151516 */
	    0x3.D22634p-08f,  /* 1/67 = 0.014925373 */
	    0x3.C3C3C4p-08f,  /* 1/68 = 0.014705882 */
	    0x3.B5CC10p-08f,  /* 1/69 = 0.014492754 */
	    0x3.A83A84p-08f,  /* 1/70 = 0.014285714 */
	    0x3.9B0AD0p-08f,  /* 1/71 = 0.014084507 */
	    0x3.8E38E4p-08f,  /* 1/72 = 0.013888889 */
	    0x3.81C0E0p-08f,  /* 1/73 = 0.013698630 */
	    0x3.759F24p-08f,  /* 1/74 = 0.013513514 */
	    0x3.69D038p-08f,  /* 1/75 = 0.013333334 */
	    0x3.5E50D8p-08f,  /* 1/76 = 0.013157895 */
	    0x3.531DECp-08f,  /* 1/77 = 0.012987013 */
	    0x3.483484p-08f,  /* 1/78 = 0.012820513 */
	    0x3.3D91D4p-08f,  /* 1/79 = 0.012658228 */
	    0x3.333334p-08f,  /* 1/80 = 0.012500000 */
	    0x3.291620p-08f,  /* 1/81 = 0.012345679 */
	    0x3.1F3830p-08f,  /* 1/82 = 0.012195121 */
	    0x3.159720p-08f,  /* 1/83 = 0.012048192 */
	    0x3.0C30C4p-08f,  /* 1/84 = 0.011904762 */
	    0x3.030304p-08f,  /* 1/85 = 0.011764706 */
	    0x2.FA0BE8p-08f,  /* 1/86 = 0.011627907 */
	    0x2.F14990p-08f,  /* 1/87 = 0.011494253 */
	    0x2.E8BA30p-08f,  /* 1/88 = 0.011363637 */
	    0x2.E05C0Cp-08f,  /* 1/89 = 0.011235955 */
	    0x2.D82D84p-08f,  /* 1/90 = 0.011111111 */
	    0x2.D02D04p-08f,  /* 1/91 = 0.010989011 */
	    0x2.C8590Cp-08f,  /* 1/92 = 0.010869565 */
	    0x2.C0B02Cp-08f,  /* 1/93 = 0.010752688 */
	    0x2.B93104p-08f,  /* 1/94 = 0.010638298 */
	    0x2.B1DA48p-08f,  /* 1/95 = 0.010526316 */
	    0x2.AAAAACp-08f,  /* 1/96 = 0.010416667 */
	    0x2.A3A0FCp-08f,  /* 1/97 = 0.010309278 */
	    0x2.9CBC14p-08f,  /* 1/98 = 0.010204081 */
	    0x2.95FAD4p-08f,  /* 1/99 = 0.010101010 */
	    0x2.8F5C28p-08f,  /* 1/100 = 0.010000000 */
	    0x2.88DF0Cp-08f,  /* 1/101 = 0.009900990 */
	    0x2.828284p-08f,  /* 1/102 = 0.009803922 */
	    0x2.7C4598p-08f,  /* 1/103 = 0.009708738 */
	    0x2.762764p-08f,  /* 1/104 = 0.009615385 */
	    0x2.702704p-08f,  /* 1/105 = 0.009523810 */
	    0x2.6A43A0p-08f,  /* 1/106 = 0.009433962 */
	    0x2.647C68p-08f,  /* 1/107 = 0.009345794 */
	    0x2.5ED098p-08f,  /* 1/108 = 0.009259259 */
	    0x2.593F68p-08f,  /* 1/109 = 0.009174312 */
	    0x2.53C824p-08f,  /* 1/110 = 0.009090909 */
	    0x2.4E6A18p-08f,  /* 1/111 = 0.009009009 */
	    0x2.492494p-08f,  /* 1/112 = 0.008928572 */
	    0x2.43F6F0p-08f,  /* 1/113 = 0.008849557 */
	    0x2.3EE090p-08f,  /* 1/114 = 0.008771930 */
	    0x2.39E0D4p-08f,  /* 1/115 = 0.008695652 */
	    0x2.34F72Cp-08f,  /* 1/116 = 0.008620690 */
	    0x2.302304p-08f,  /* 1/117 = 0.008547009 */
	    0x2.2B63CCp-08f,  /* 1/118 = 0.008474576 */
	    0x2.26B904p-08f,  /* 1/119 = 0.008403362 */
	    0x2.222224p-08f,  /* 1/120 = 0.008333334 */
	    0x2.1D9EACp-08f,  /* 1/121 = 0.008264462 */
	    0x2.192E28p-08f,  /* 1/122 = 0.008196721 */
	    0x2.14D020p-08f,  /* 1/123 = 0.008130081 */
	    0x2.108420p-08f,  /* 1/124 = 0.008064516 */
	    0x2.0C49BCp-08f,  /* 1/125 = 0.008000000 */
	    0x2.082084p-08f,  /* 1/126 = 0.007936508 */
	    0x2.040810p-08f,  /* 1/127 = 0.007874016 */
	    0x2.000000p-08f   /* 1/128 = 0.007812500 */
};


// table of reciprocals, as int32 (31 frac bits)
// to find (1<<k)/(h*w):
//   uint64_t p = (uint64_t) lut_reciprocal_i32[h-1] * lut_reciprocal_i32[w-1];
//  .. and then >> (62-k),  with rounding if desired e.g.  for k around 16:
//    int32_t px = p >> (61-k)
//    px = (px+1)>>1;
//   
const
int32_t lut_reciprocal_i32[128] __attribute__ ((aligned(128))) = {
     0x7FFFFFFF,   /* 1/1   = 1.000000000 */
     0x40000000,   /* 1/2   = 0.500000000 */
     0x2AAAAAAB,   /* 1/3   = 0.333333333 */
     0x20000000,   /* 1/4   = 0.250000000 */
     0x1999999A,   /* 1/5   = 0.200000000 */
     0x15555555,   /* 1/6   = 0.166666667 */
     0x12492492,   /* 1/7   = 0.142857143 */
     0x10000000,   /* 1/8   = 0.125000000 */
     0x0E38E38E,   /* 1/9   = 0.111111111 */
     0x0CCCCCCD,   /* 1/10  = 0.100000000 */
     0x0BA2E8BA,   /* 1/11  = 0.090909091 */
     0x0AAAAAAB,   /* 1/12  = 0.083333333 */
     0x09D89D8A,   /* 1/13  = 0.076923077 */
     0x09249249,   /* 1/14  = 0.071428571 */
     0x08888889,   /* 1/15  = 0.066666667 */
     0x08000000,   /* 1/16  = 0.062500000 */
     0x07878788,   /* 1/17  = 0.058823529 */
     0x071C71C7,   /* 1/18  = 0.055555556 */
     0x06BCA1AF,   /* 1/19  = 0.052631579 */
     0x06666666,   /* 1/20  = 0.050000000 */
     0x06186186,   /* 1/21  = 0.047619048 */
     0x05D1745D,   /* 1/22  = 0.045454545 */
     0x0590B216,   /* 1/23  = 0.043478261 */
     0x05555555,   /* 1/24  = 0.041666667 */
     0x051EB852,   /* 1/25  = 0.040000000 */
     0x04EC4EC5,   /* 1/26  = 0.038461538 */
     0x04BDA12F,   /* 1/27  = 0.037037037 */
     0x04924925,   /* 1/28  = 0.035714286 */
     0x0469EE58,   /* 1/29  = 0.034482759 */
     0x04444444,   /* 1/30  = 0.033333333 */
     0x04210842,   /* 1/31  = 0.032258065 */
     0x04000000,   /* 1/32  = 0.031250000 */
     0x03E0F83E,   /* 1/33  = 0.030303030 */
     0x03C3C3C4,   /* 1/34  = 0.029411765 */
     0x03A83A84,   /* 1/35  = 0.028571429 */
     0x038E38E4,   /* 1/36  = 0.027777778 */
     0x03759F23,   /* 1/37  = 0.027027027 */
     0x035E50D8,   /* 1/38  = 0.026315789 */
     0x03483483,   /* 1/39  = 0.025641026 */
     0x03333333,   /* 1/40  = 0.025000000 */
     0x031F3832,   /* 1/41  = 0.024390244 */
     0x030C30C3,   /* 1/42  = 0.023809524 */
     0x02FA0BE8,   /* 1/43  = 0.023255814 */
     0x02E8BA2F,   /* 1/44  = 0.022727273 */
     0x02D82D83,   /* 1/45  = 0.022222222 */
     0x02C8590B,   /* 1/46  = 0.021739130 */
     0x02B93105,   /* 1/47  = 0.021276596 */
     0x02AAAAAB,   /* 1/48  = 0.020833333 */
     0x029CBC15,   /* 1/49  = 0.020408163 */
     0x028F5C29,   /* 1/50  = 0.020000000 */
     0x02828283,   /* 1/51  = 0.019607843 */
     0x02762762,   /* 1/52  = 0.019230769 */
     0x026A439F,   /* 1/53  = 0.018867925 */
     0x025ED098,   /* 1/54  = 0.018518519 */
     0x0253C825,   /* 1/55  = 0.018181818 */
     0x02492492,   /* 1/56  = 0.017857143 */
     0x023EE090,   /* 1/57  = 0.017543860 */
     0x0234F72C,   /* 1/58  = 0.017241379 */
     0x022B63CC,   /* 1/59  = 0.016949153 */
     0x02222222,   /* 1/60  = 0.016666667 */
     0x02192E2A,   /* 1/61  = 0.016393443 */
     0x02108421,   /* 1/62  = 0.016129032 */
     0x02082082,   /* 1/63  = 0.015873016 */
     0x02000000,   /* 1/64  = 0.015625000 */
     0x01F81F82,   /* 1/65  = 0.015384615 */
     0x01F07C1F,   /* 1/66  = 0.015151515 */
     0x01E9131B,   /* 1/67  = 0.014925373 */
     0x01E1E1E2,   /* 1/68  = 0.014705882 */
     0x01DAE607,   /* 1/69  = 0.014492754 */
     0x01D41D42,   /* 1/70  = 0.014285714 */
     0x01CD8569,   /* 1/71  = 0.014084507 */
     0x01C71C72,   /* 1/72  = 0.013888889 */
     0x01C0E070,   /* 1/73  = 0.013698630 */
     0x01BACF91,   /* 1/74  = 0.013513514 */
     0x01B4E81B,   /* 1/75  = 0.013333333 */
     0x01AF286C,   /* 1/76  = 0.013157895 */
     0x01A98EF6,   /* 1/77  = 0.012987013 */
     0x01A41A42,   /* 1/78  = 0.012820513 */
     0x019EC8E9,   /* 1/79  = 0.012658228 */
     0x0199999A,   /* 1/80  = 0.012500000 */
     0x01948B10,   /* 1/81  = 0.012345679 */
     0x018F9C19,   /* 1/82  = 0.012195122 */
     0x018ACB91,   /* 1/83  = 0.012048193 */
     0x01861862,   /* 1/84  = 0.011904762 */
     0x01818182,   /* 1/85  = 0.011764706 */
     0x017D05F4,   /* 1/86  = 0.011627907 */
     0x0178A4C8,   /* 1/87  = 0.011494253 */
     0x01745D17,   /* 1/88  = 0.011363636 */
     0x01702E06,   /* 1/89  = 0.011235955 */
     0x016C16C1,   /* 1/90  = 0.011111111 */
     0x01681681,   /* 1/91  = 0.010989011 */
     0x01642C86,   /* 1/92  = 0.010869565 */
     0x01605816,   /* 1/93  = 0.010752688 */
     0x015C9883,   /* 1/94  = 0.010638298 */
     0x0158ED23,   /* 1/95  = 0.010526316 */
     0x01555555,   /* 1/96  = 0.010416667 */
     0x0151D07F,   /* 1/97  = 0.010309278 */
     0x014E5E0A,   /* 1/98  = 0.010204082 */
     0x014AFD6A,   /* 1/99  = 0.010101010 */
     0x0147AE14,   /* 1/100 = 0.010000000 */
     0x01446F86,   /* 1/101 = 0.009900990 */
     0x01414141,   /* 1/102 = 0.009803922 */
     0x013E22CC,   /* 1/103 = 0.009708738 */
     0x013B13B1,   /* 1/104 = 0.009615385 */
     0x01381381,   /* 1/105 = 0.009523810 */
     0x013521D0,   /* 1/106 = 0.009433962 */
     0x01323E35,   /* 1/107 = 0.009345794 */
     0x012F684C,   /* 1/108 = 0.009259259 */
     0x012C9FB5,   /* 1/109 = 0.009174312 */
     0x0129E413,   /* 1/110 = 0.009090909 */
     0x0127350C,   /* 1/111 = 0.009009009 */
     0x01249249,   /* 1/112 = 0.008928571 */
     0x0121FB78,   /* 1/113 = 0.008849558 */
     0x011F7048,   /* 1/114 = 0.008771930 */
     0x011CF06B,   /* 1/115 = 0.008695652 */
     0x011A7B96,   /* 1/116 = 0.008620690 */
     0x01181181,   /* 1/117 = 0.008547009 */
     0x0115B1E6,   /* 1/118 = 0.008474576 */
     0x01135C81,   /* 1/119 = 0.008403361 */
     0x01111111,   /* 1/120 = 0.008333333 */
     0x010ECF57,   /* 1/121 = 0.008264463 */
     0x010C9715,   /* 1/122 = 0.008196721 */
     0x010A6811,   /* 1/123 = 0.008130081 */
     0x01084211,   /* 1/124 = 0.008064516 */
     0x010624DD,   /* 1/125 = 0.008000000 */
     0x01041041,   /* 1/126 = 0.007936508 */
     0x01020408,   /* 1/127 = 0.007874016 */
     0x01000000    /* 1/128 = 0.007812500 */
};


