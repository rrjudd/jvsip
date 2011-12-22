/* Created RJudd November 2, 2002       */
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
/* $Id: VI_cblockadmit_f_as.h,v 2.0 2003/02/22 15:18:28 judd Exp $ */
/* VI_cblockadmit_f always split */

{ 
   if(b->Rp == (vsip_scalar_f*)NULL)
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
      if(b->Ip == (vsip_scalar_f*)NULL){ /* must be interleaved */
         /* copy needed; care about update flag */
         b->R->array = b->r_data;
         b->I->array = b->i_data;
         if(update){ /* need to copy */
            vsip_length n = b->size;
            vsip_scalar_f *ptr_data = b->Rp,
                          *ptr_Rarray = b->R->array,
                          *ptr_Iarray = b->I->array;
            while(n-- > 0){
               *ptr_Rarray = *ptr_data;
                ptr_Rarray++; ptr_data++;
               *ptr_Iarray = *ptr_data;
                ptr_Iarray++; ptr_data++;
            }
         }
      } else { /* must be split */
         /* no copy needed; don't care about update flag, always true */
         b->R->array = b->Rp;
         b->I->array = b->Ip;
      }
   }
}
