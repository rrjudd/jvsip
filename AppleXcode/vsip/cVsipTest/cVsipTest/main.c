//
//  main.c
//  cVsipTest
//
//  Created by Randall R. Judd on 6/2/17.
//  Copyright © 2017 JVSIP. All rights reserved.
//

#include <stdio.h>
#include <vsip.h>
#include <VI_nuV.h>
#include <VI_jofk.h>
#include <vsip_fftattributes_d.h>
#include <vsip_cvviewattributes_d.h>
#include <vsip_vviewattributes_d.h>
#include <vsip_cblockattributes_d.h>
#include <vsip_blockattributes_d.h>
int main(int argc, const char * argv[]) {
/*  
    vsip_scalar_vi *pn = (vsip_scalar_vi*) malloc(6 * sizeof(vsip_scalar_vi));
    vsip_scalar_vi *p0 = (vsip_scalar_vi*) malloc(6 * sizeof(vsip_scalar_vi));
    vsip_scalar_vi *pF = (vsip_scalar_vi*) malloc(6 * sizeof(vsip_scalar_vi));
    vsip_length N = 1024 * 5 * 3 * 7 * 11 * 17;
    vsip_length k = VI_nuV(N, pn, p0, pF);
    printf("%lu\n",k);
    for(int i = 0; i<k; i++){
        printf("%lu: %lu: %lu\n",pn[i], p0[i], pF[i]);
    }
    free(pn); free(p0); free(pF);
 */
    int init = vsip_init((void*)0);
    int i;
    vsip_scalar_vi N = 8 * 3 * 3 * 7;
    vsip_fft_d *fft = vsip_ccfftop_create_d(N, 1.0,VSIP_FFT_FWD,1,VSIP_ALG_TIME);
    printf("%lu\n",fft->pF[fft->length - 1]);
    for(i=0; i<fft->length; i++) {
        printf("%lu, %lu\n",fft->pn[i],fft->p0[i]);
    }

    for(i=0; i<fft->N; i++){
        printf("%lu\n",fft->index[i]);
    }
    vsip_fft_destroy_d(fft);
    init = vsip_finalize((void*)0);
    return 0;
}
