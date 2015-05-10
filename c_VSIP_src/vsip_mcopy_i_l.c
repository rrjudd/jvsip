#include<vsip.h>
#include<vsip_mviewattributes_l.h>

void (vsip_mcopy_l_l)(
         const vsip_mview_l* a,
         const vsip_mview_l* r) 
{
    vsip_length n_mj, /* major length */
                n_mn; /* minor length */
    vsip_stride ast_mj, ast_mn;
    vsip_scalar_l *ap = (a->block->array) + a->offset;
    vsip_scalar_l *ap0 = ap;
    vsip_index i=0,j=0;
    /* pick direction dependent on input */
    if(a->row_stride < a->col_stride){ /* Row Major */
        n_mj = a->row_length; n_mn = a->col_length;
        ast_mj = a->row_stride; ast_mn = a->col_stride;
        while(n_mn-- > 0){
           vsip_length n = n_mj;
           while(n-- >0){
               vsip_mput_l(r,i,j,(vsip_scalar_l) *ap);
               ap += ast_mj; j++;
           }
           ap0 += ast_mn;
           ap = ap0; i++; j=0;
        }
    } else { /* must be Col Major */
        n_mn = a->row_length; n_mj = a->col_length;
        ast_mn = a->row_stride; ast_mj = a->col_stride;
        while(n_mn-- > 0){
           vsip_length n = n_mj;
           while(n-- >0){
               vsip_mput_l(r,i,j,(vsip_scalar_l) *ap);
               ap += ast_mj; i++;
           }
           ap0 += ast_mn;
           ap = ap0; i=0; j++;
        }
    }
    return;
}
