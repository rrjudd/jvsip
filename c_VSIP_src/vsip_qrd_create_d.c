/* Created RJudd August 29, 1999 */
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
/* $Id: vsip_qrd_create_d.c,v 2.0 2003/02/22 15:19:01 judd Exp $ */
/* Create QRD object for real qrd float */
/* vsip_qrd_create_d.c */

#include<vsip.h>
#include<vsip_qrdattributes_d.h>
#include"VI_vcreate_d.h"
#include"VI_valldestroy_d.h"

vsip_qr_d *vsip_qrd_create_d(
            vsip_length M,
            vsip_length N,
            vsip_qrd_qopt qopt)
{
  vsip_qr_d *qr = (vsip_qr_d*) malloc(sizeof(vsip_qr_d));
  if(( qr != NULL)){
     if((qr->v = VI_vcreate_d(M,VSIP_MEM_NONE))!= NULL){
        if((qr->w = VI_vcreate_d((vsip_length)10 * M,VSIP_MEM_NONE)) != NULL){
          if((qr->beta = (vsip_scalar_d*)malloc(N * sizeof(vsip_scalar_d)))!=NULL){
             /* everything is created all right */
             qr->M = M;
             qr->N = N;
             qr->qopt = qopt;
             qr->A = &(qr->AA);
          } else {
             VI_valldestroy_d(qr->w);
             VI_valldestroy_d(qr->v);
             free(qr);
             qr = (vsip_qr_d*) NULL;
          }
        } else {
             VI_valldestroy_d(qr->v);
             free(qr);
             qr = (vsip_qr_d*) NULL;
        }
     } else {
       free(qr);
       qr = (vsip_qr_d*) NULL;
     }
  } else {
     qr = (vsip_qr_d*) NULL;
  }
  return qr;
}

/* w must be long enough for any size row length for matrix multiply */
/* here we have arbitraily decided this is 10 * M */

  
       
