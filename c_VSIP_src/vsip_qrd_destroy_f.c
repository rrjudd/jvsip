/* Created RJudd August 29, 1999 */
/* SPAWARSYCEN D881 */
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
/* $Id: vsip_qrd_destroy_f.c,v 2.0 2003/02/22 15:19:01 judd Exp $ */
/* vsip_qrd_destry_f */

#include<vsip.h>
#include<vsip_qrdattributes_f.h>
#include"VI_valldestroy_f.h"

int vsip_qrd_destroy_f(
         vsip_qr_f* qr)
{
   if(qr != NULL){
       VI_valldestroy_f(qr->w);
       VI_valldestroy_f(qr->v);
       free(qr->beta);
       free(qr);
   }
   return 0;
}
