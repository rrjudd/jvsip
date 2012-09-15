#ifndef _JVSIP_H
#define _JVSIP_H
#include<vsip.h>
void jvsip_mprod2_d( const vsip_mview_d*, const vsip_mview_d*, const vsip_mview_d*);
void jvsip_mprod2_f( const vsip_mview_f*, const vsip_mview_f*, const vsip_mview_f*);
void jvsip_cmprod2_d( const vsip_cmview_d*, const vsip_cmview_d*, const vsip_cmview_d*);
void jvsip_cmprod2_f( const vsip_cmview_f*, const vsip_cmview_f*, const vsip_cmview_f*);
void jvsip_cmprodh2_d( const vsip_cmview_d*, const vsip_cmview_d*, const vsip_cmview_d*);
void jvsip_cmprodh2_f( const vsip_cmview_f*, const vsip_cmview_f*, const vsip_cmview_f*);
#endif /* _JVSIP_H */
