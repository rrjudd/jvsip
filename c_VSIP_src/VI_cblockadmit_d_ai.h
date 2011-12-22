/* Created RJudd June 2, 2002       */
/* SPAWARSYSCEN D857                */
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
/* $Id: VI_cblockadmit_d_ai.h,v 2.0 2003/02/22 15:18:28 judd Exp $ */
/* VI_cblockadmit_d always interleaved */

{ 
   if(b->Rp == (vsip_scalar_d*)NULL)
      blockadmit = 1; /* fail if no data array */
   else if(b->kind != VSIP_USER_BLOCK)
      blockadmit = 1; /* fail if not a user block */
   else {
      b->admit = VSIP_ADMITTED_BLOCK;
      b->a_scalar.r = 0.0; b->a_scalar.i = 0.0;
      b->a_zero.r = 0.0; b->a_zero.i = 0.0;
      b->a_one.r = 1.0; b->a_one.i = 0.0;
      b->a_imag_one.r = 0.0; b->a_imag_one.i = 1.0;
      blockadmit = 0; /* return zero on success */
      if(b->Ip == (vsip_scalar_d*)NULL){ /* must be interleaved */
         /* no copy needed; don't care about update flag, always true */
         b->R->array = b->Rp;
         b->I->array = b->Rp + 1;
      } else { /* must be split */
         b->R->array = b->data;
         b->I->array = b->data + 1;
         if(update){ /* need to copy */
            vsip_length n = b->size;
            vsip_scalar_d *ptr_data = b->data,
                          *ptr_Rp = b->Rp,
                          *ptr_Ip = b->Ip;
            while(n-- > 0){
               *ptr_data = *ptr_Rp;
                ptr_data++; ptr_Rp++;
               *ptr_data = *ptr_Ip;
                ptr_data++; ptr_Ip++;
            }
         }
      }
   }
}
