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
/* $Id: vsip_cqrd_create_d.c,v 2.1 2007/04/16 16:55:05 judd Exp $ */
/* Create QRD object for real qrd float */
/* vsip_cqrd_create_d.c */

#include<vsip.h>
#include<vsip_cqrdattributes_d.h>
#include"VI_cvalldestroy_d.h"

vsip_cqr_d *vsip_cqrd_create_d(
            vsip_length M,
            vsip_length N,
            vsip_qrd_qopt qopt)
{
  vsip_cqr_d *qr = (vsip_cqr_d*) malloc(sizeof(vsip_cqr_d));
  if(( qr != NULL)){
     if((qr->v = vsip_cvcreate_d(M,VSIP_MEM_NONE))!= NULL){
        if((qr->w = vsip_cvcreate_d((vsip_length)10 * M,VSIP_MEM_NONE)) != NULL){
          if((qr->beta = (vsip_scalar_d*)malloc(N * sizeof(vsip_scalar_d)))!=NULL){
             if((qr->cI = vsip_cvcreate_d(N,VSIP_MEM_NONE))!=NULL){
                /* everything is created all right */
                qr->M = M;
                qr->N = N;
                qr->qopt = qopt;
                qr->A = &(qr->AA);
             } else {
                free(qr->beta);
                VI_cvalldestroy_d(qr->w);
                VI_cvalldestroy_d(qr->v);
                free(qr);
                qr = (vsip_cqr_d*) NULL;
             }
          } else {
             VI_cvalldestroy_d(qr->w);
             VI_cvalldestroy_d(qr->v);
             free(qr);
             qr = (vsip_cqr_d*) NULL;
          }
        } else {
             VI_cvalldestroy_d(qr->v);
             free(qr);
             qr = (vsip_cqr_d*) NULL;
        }
     } else {
       free(qr);
       qr = (vsip_cqr_d*) NULL;
     }
  } else {
     qr = (vsip_cqr_d*) NULL;
  }
  return qr;
}

  
       
