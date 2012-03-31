/* Created RJudd */
/* $Id: ccfftmop_f.h,v 1.2 2009/05/23 05:27:27 judd Exp $ */

#include"VU_cmprintm_f.include"
static void ccfftmop_f(void)
{  
  printf("******\nTEST ccfftmop for float \n");
  {
      vsip_length N = 1000;
      vsip_cblock_f *block = vsip_cblockcreate_f(N,VSIP_MEM_NONE);
      vsip_cmview_f *A;
      vsip_cmview_f *Ao;
      vsip_cmview_f *B;
      vsip_fftm_f *fft;
      vsip_scalar_f chk;
      { /* 8 by 4 */
         vsip_scalar_f rdta[32] = {0.8147,   0.9575,   0.4218,   0.6787,
                                   0.9058,   0.9649,   0.9157,   0.7577,
                                   0.1270,   0.1576,   0.7922,   0.7431,
                                   0.9134,   0.9706,   0.9595,   0.3922,
                                   0.6324,   0.9572,   0.6557,   0.6555,
                                   0.0975,   0.4854,   0.0357,   0.1712,
                                   0.2785,   0.8003,   0.8491,   0.7060,
                                   0.5469,   0.1419,   0.9340,   0.0318};
         vsip_scalar_f idta[32] = { 0.2769,   0.4387,   0.7094,   0.9597,
                                    0.0462,   0.3816,   0.7547,   0.3404,
                                    0.0971,   0.7655,   0.2760,   0.5853,
                                    0.8235,   0.7952,   0.6797,   0.2238,
                                    0.6948,   0.1869,   0.6551,   0.7513,
                                    0.3171,   0.4898,   0.1626,   0.2551,
                                    0.9502,   0.4456,   0.1190,   0.5060,
                                    0.0344,   0.6463,   0.4984,   0.6991};
         vsip_scalar_f rdta0[32] = { 2.8727,   -0.1281,   -0.3997,    0.9139,
                                     3.5441,    0.0313,    0.0989,   -0.0511,
                                     1.8199,   -0.4850,    0.0185,   -0.8454,
                                     3.2357,    0.5253,    0.5101,   -0.6175,
                                     2.9008,   -0.5877,   -0.3246,    0.5411,
                                     0.7898,    0.2965,   -0.5234,   -0.1729,
                                     2.6339,   -0.6310,   -0.3787,   -0.5102,
                                     1.6546,   -0.4399,    1.3072,   -0.3343};
                                    
         vsip_scalar_f idta0[32] = { 2.3847,   -0.7113,   -0.4121,   -0.1537,
                                     1.5229,   -0.9157,    0.0789,   -0.5013,
                                     1.7239,    0.4066,   -0.9777,   -0.7644,
                                     2.5222,   -0.4346,    0.4842,    0.7222,
                                     2.2881,   -0.2620,    0.4117,    0.3414,
                                     1.2246,   -0.1597,   -0.2652,    0.4687,
                                     2.0208,    0.7369,    0.1176,    0.9255,
                                     1.8782,   -0.5741,   -0.8126,   -0.3539};
         
         fft = vsip_ccfftmop_create_f(8,4,1.0,VSIP_FFT_FWD,VSIP_ROW,0,VSIP_ALG_SPACE);
         A = vsip_cmbind_f(block,4,2,8,17,4); 
         Ao = vsip_cmcreate_f(8,4,VSIP_ROW,VSIP_MEM_NONE);
         B = vsip_cmcreate_f(8,4,VSIP_ROW,VSIP_MEM_NONE);
         vsip_cmcopyfrom_user_f(rdta,idta,VSIP_ROW,A);
         vsip_cmcopyfrom_user_f(rdta0,idta0,VSIP_ROW,B);
         VU_cmprintm_f("5.4",A);
         VU_cmprintm_f("5.4",B);
         vsip_ccfftmop_f(fft,A,Ao);
         VU_cmprintm_f("5.4",A);
         vsip_cmsub_f(Ao,B,B);
         chk = vsip_cmmeansqval_f(B);
         if(chk > .0002 ){
              printf("error\n");
         } else {
              printf("correct\n");
         }  
         vsip_cmalldestroy_f(B);
         vsip_cmalldestroy_f(Ao);
         vsip_cmdestroy_f(A);
         vsip_fftm_destroy_f(fft);
      }
      { /* 8 by 4 */
         vsip_scalar_f rdta[32] = {0.8147,   0.9575,   0.4218,   0.6787,
                                   0.9058,   0.9649,   0.9157,   0.7577,
                                   0.1270,   0.1576,   0.7922,   0.7431,
                                   0.9134,   0.9706,   0.9595,   0.3922,
                                   0.6324,   0.9572,   0.6557,   0.6555,
                                   0.0975,   0.4854,   0.0357,   0.1712,
                                   0.2785,   0.8003,   0.8491,   0.7060,
                                   0.5469,   0.1419,   0.9340,   0.0318};
         vsip_scalar_f idta[32] = { 0.2769,   0.4387,   0.7094,   0.9597,
                                    0.0462,   0.3816,   0.7547,   0.3404,
                                    0.0971,   0.7655,   0.2760,   0.5853,
                                    0.8235,   0.7952,   0.6797,   0.2238,
                                    0.6948,   0.1869,   0.6551,   0.7513,
                                    0.3171,   0.4898,   0.1626,   0.2551,
                                    0.9502,   0.4456,   0.1190,   0.5060,
                                    0.0344,   0.6463,   0.4984,   0.6991};
         vsip_scalar_f rdta0[32] = { 4.3162,    5.4354,    5.5637,    4.1362,
                                     0.0080,    0.1021,    1.0742,   -0.0134,
                                     0.5470,    0.3867,   -0.8246,   -0.4423,
                                     1.0894,   -0.0439,   -0.4482,   -0.4917,
                                    -0.6110,    0.3098,   -0.1261,    1.4304,
                                    -1.3496,    0.5383,   -1.2280,    0.2184,
                                     1.5362,    1.5269,   -0.3030,    0.2125,
                                     0.9814,   -0.5953,   -0.3336,    0.3795 };

         vsip_scalar_f idta0[32] = { 3.2402,    4.1496,    3.8549,    4.3207,
                                    -1.8466,   -0.2123,   -0.2386,   -0.1019,
                                     0.3814,   -0.9233,    1.9116,    0.1148,
                                    -0.6506,   -1.1341,   -0.9334,   -0.8205,
                                     0.7978,   -0.4762,   -0.3359,    1.2839,
                                     1.3138,    2.0013,    0.4610,    0.4445,
                                    -0.5326,   -0.2477,    0.0274,    1.1246,
                                    -0.4882,    0.3523,    0.9282,    1.3115 };

         fft = vsip_ccfftmop_create_f(8,4,1.0,VSIP_FFT_FWD,VSIP_COL,0,VSIP_ALG_SPACE);
         A = vsip_cmbind_f(block,4,2,8,17,4);
         Ao = vsip_cmcreate_f(8,4,VSIP_ROW,VSIP_MEM_NONE);
         B = vsip_cmcreate_f(8,4,VSIP_ROW,VSIP_MEM_NONE);
         vsip_cmcopyfrom_user_f(rdta,idta,VSIP_ROW,A);
         vsip_cmcopyfrom_user_f(rdta0,idta0,VSIP_ROW,B);
         VU_cmprintm_f("5.4",A);
         VU_cmprintm_f("5.4",B);
         vsip_ccfftmop_f(fft,A,Ao);
         VU_cmprintm_f("5.4",Ao);
         vsip_cmsub_f(Ao,B,B);
         chk = vsip_cmmeansqval_f(B);
         if(chk > .0002 ){
              printf("error\n");
         } else {
              printf("correct\n");
         }
         vsip_cmalldestroy_f(B);
         vsip_cmdestroy_f(A);
         vsip_fftm_destroy_f(fft);
      }
     { /* 8 by 4 */
         vsip_scalar_f rdta[32] = {0.8147,   0.9575,   0.4218,   0.6787,
                                   0.9058,   0.9649,   0.9157,   0.7577,
                                   0.1270,   0.1576,   0.7922,   0.7431,
                                   0.9134,   0.9706,   0.9595,   0.3922,
                                   0.6324,   0.9572,   0.6557,   0.6555,
                                   0.0975,   0.4854,   0.0357,   0.1712,
                                   0.2785,   0.8003,   0.8491,   0.7060,
                                   0.5469,   0.1419,   0.9340,   0.0318};
         vsip_scalar_f idta[32] = { 0.2769,   0.4387,   0.7094,   0.9597,
                                    0.0462,   0.3816,   0.7547,   0.3404,
                                    0.0971,   0.7655,   0.2760,   0.5853,
                                    0.8235,   0.7952,   0.6797,   0.2238,
                                    0.6948,   0.1869,   0.6551,   0.7513,
                                    0.3171,   0.4898,   0.1626,   0.2551,
                                    0.9502,   0.4456,   0.1190,   0.5060,
                                    0.0344,   0.6463,   0.4984,   0.6991};
         vsip_scalar_f rdta0[32] = { 4.3162,    5.4354,    5.5637,    4.1362,
                                     0.9814,   -0.5953,   -0.3336,    0.3795,
                                     1.5362,    1.5269,   -0.3030,    0.2125,
                                    -1.3496,    0.5383,   -1.2280,    0.2184,
                                    -0.6110,    0.3098,   -0.1261,    1.4304,
                                     1.0894,   -0.0439,   -0.4482,   -0.4917,
                                     0.5470,    0.3867,   -0.8246,   -0.4423,
                                     0.0080,    0.1021,    1.0742,   -0.0134};

         vsip_scalar_f idta0[32] = { 3.2402,    4.1496,    3.8549,    4.3207,
                                    -0.4882,    0.3523,    0.9282,    1.3115,
                                    -0.5326,   -0.2477,    0.0274,    1.1246,
                                     1.3138,    2.0013,    0.4610,    0.4445,
                                     0.7978,   -0.4762,   -0.3359,    1.2839,
                                    -0.6506,   -1.1341,   -0.9334,   -0.8205,
                                     0.3814,   -0.9233,    1.9116,    0.1148,
                                    -1.8466,   -0.2123,   -0.2386,   -0.1019};

         fft = vsip_ccfftmop_create_f(8,4,1.0,VSIP_FFT_INV,VSIP_COL,0,VSIP_ALG_SPACE);
         A = vsip_cmbind_f(block,4,2,8,17,4);
         Ao = vsip_cmcreate_f(8,4,VSIP_ROW,VSIP_MEM_NONE);
         B = vsip_cmcreate_f(8,4,VSIP_ROW,VSIP_MEM_NONE);
         vsip_cmcopyfrom_user_f(rdta,idta,VSIP_ROW,A);
         vsip_cmcopyfrom_user_f(rdta0,idta0,VSIP_ROW,B);
         VU_cmprintm_f("5.4",A);
         VU_cmprintm_f("5.4",B);
         vsip_ccfftmop_f(fft,A,Ao);
         VU_cmprintm_f("5.4",Ao);
         vsip_cmsub_f(Ao,B,B);
         chk = vsip_cmmeansqval_f(B);
         if(chk > .0002 ){
              printf("error\n");
         } else {
              printf("correct\n");
         }
         vsip_cmalldestroy_f(B);
         vsip_cmalldestroy_f(Ao);
         vsip_cmdestroy_f(A);
         vsip_fftm_destroy_f(fft);
      }

      vsip_cblockdestroy_f(block);
  }
  return;
}
