#include<stdio.h>
#include<vsip.h>
#include"param.h"
#include"ts.h"
#include"kw.h"

int main(int argc, char** argv){
    int retval = 0;
    int i, Navg;
    param_obj param;
    kw_obj kw;
    ts_obj ts;
    vsip_mview_f *dtaIn, *gramOut;
    if(retval += param_read(argv[1],&param)){
        printf("Failed to read parameter file\n");
        exit(-1);
    }
    param_log(&param);
    kw_init(&kw, &param);
    ts_init(&ts, &param);
    /* simulate time series and beamform */
    Navg = (int) param.Navg;
    dtaIn = ts_instance(&ts);
    gramOut = kw_instance(&kw);
    kw_zero(&kw);
    for(i=0; i<Navg; i++){
        ts_zero(&ts);
        ts_sim_noise(&ts);
        ts_sim_nb(&ts);
        komega(&kw,dtaIn);
    }
    /* beamform done. Gram should be in gramOut */
    /*************/    
    /* Massage gram data and save to file for plotting */
      for(i=0; i<vsip_mgetrowlength_f(gramOut); i++)
      {/* move zero to middle */
         vsip_vview_f *v = vsip_mcolview_f(gramOut, i);
         vsip_vfreqswap_f(v);
         vsip_vdestroy_f(v);
      }
      {/* massage the data for plot*/
         vsip_scalar_f max = vsip_mmaxval_f(gramOut, NULL),min;
         vsip_scalar_f avg = vsip_mmeanval_f(gramOut);
         vsip_mclip_f(gramOut,0.0, max, avg/100000.0, max, gramOut);
         vsip_mlog10_f(gramOut,gramOut);
         min = -vsip_mminval_f(gramOut, NULL);
         vsip_smadd_f(min, gramOut, gramOut);
         max = vsip_mmaxval_f(gramOut, NULL);
         vsip_smmul_f(1.0/max, gramOut, gramOut);
      }
      { /* output data and plot with octave */
         FILE *fptr = fopen("gramOut","w");
         size_t size = vsip_mgetrowlength_f(gramOut) * vsip_mgetcollength_f(gramOut);
         vsip_scalar_f *out = (vsip_scalar_f*)malloc(size * sizeof(vsip_scalar_f));
         vsip_mcopyto_user_f(gramOut, VSIP_COL, out);
         fwrite(out,size,sizeof(vsip_scalar_f),fptr);
         fclose(fptr);
         free(out);
      }
    /* cleanup */
    kw_fin(&kw);
    ts_fin(&ts);
    param_free(&param);
    return retval;
}
