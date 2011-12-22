/* Created RJudd September 15, 1999*/
/* SPAWARSYSCEN D881 */
/**********************************************************************
// For TASP VSIPL Documentation and Code neither the United States    /
// Government, the United States Navy, nor any of their employees,    /
// makes any warranty, express or implied, including the warranties   /
// of merchantability and fitness for a particular purpose, or        /
// assumes any legal liability or responsibility for the accuracy,    /
// completeness, or usefulness of any information, apparatus,         /
// product, or process disclosed, or represents that its use would    /
// not infringe privately owned rights                                /
**********************************************************************/    
#ifndef _vsip_cludattributes_f_h
#define _vsip_cludattributes_f_h 1
#include<vsip.h>
#include<VI.h>
#include<vsip_cmviewattributes_f.h>
#include<vsip_cvviewattributes_f.h>
#include<vsip_vviewattributes_vi.h>

struct vsip_cludattributes_f{
       vsip_cmview_f* LU;
       vsip_cmview_f  LLU;
       vsip_index* P;
       vsip_length   N;
       };
#endif /* _vsip_cludattributes_f */
