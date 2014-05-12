#include<vsip.h>
#include<math.h>
#include<assert.h>
void mview_store_d(vsip_mview_d *M, char* fname);
vsip_mview_d *mcenter_d(vsip_mview_d *gram);
vsip_mview_d *cmscale_d(vsip_cmview_d *gram_data);
vsip_mview_d *noiseGen( vsip_scalar_d alpha, vsip_length Mp, vsip_length Nn, vsip_length Ns);
vsip_mview_d *narrowBandGen( vsip_mview_d *data, vsip_scalar_d alpha, void **targets, vsip_scalar_d Fs);
