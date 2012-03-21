/* Created RJudd March 18, 2012 */
/*********************************************************************
 // This code includes                                                 /
 // no warranty, express or implied, including the warranties          /
 // of merchantability and fitness for a particular purpose.           /
 // No person or entity                                                /
 // assumes any legal liability or responsibility for the accuracy,    /
 // completeness, or usefulness of any information, apparatus,         /
 // product, or process disclosed, or represents that its use would    /
 // not infringe privately owned rights                                /
 **********************************************************************/

#include<vsip.h>
#include<vsip_cvviewattributes_d.h>
#include<vsip_rcfirattributes_d.h>
#include<vsip_vviewattributes_d.h>
#include"VI_cvcopy_d_d.h"
#include"VI_cvfill_d.h"

static vsip_cscalar_d rcvdot_d( const vsip_vview_d* a, const vsip_cvview_d* b) {
    {
        vsip_length n = a->length;
        vsip_stride cbst = b->block->cstride;
        vsip_scalar_d 
        *apr = (vsip_scalar_d*) ((a->block->array) + a->block->rstride * a->offset),
        *bpr = (vsip_scalar_d*) ((b->block->R->array) + cbst * b->offset),
        *bpi = (vsip_scalar_d*) ((b->block->I->array) + cbst * b->offset);
        vsip_stride 
        ast = (a->block->rstride * a->stride), 
        bst = (cbst * b->stride);
        vsip_cscalar_d r;
        r.r = 0; r.i = 0;
        while(n-- > 0){
            r.r += *apr * *bpr;
            r.i += *apr * *bpi;
            apr += ast; bpr += bst; bpi += bst;
        }
        return r;
    }
}


int vsip_rcfirflt_d(
                    vsip_rcfir_d *fir,
                    const vsip_cvview_d *xc,
                    const vsip_cvview_d *yc)
{
    vsip_length nout,k;
    vsip_cvview_d xx = *(xc),
    yy = *(yc);
    vsip_vview_d 
    H1 = *(fir->h),
    H2 = *(fir->h);
    vsip_cvview_d *x=&xx,*y=&yy;
    vsip_vview_d *h1=&H1,*h2=&H2;
    vsip_offset oinc;
    oinc = (vsip_offset)((vsip_stride)fir->D * x->stride);
    /* calculate number of terms in y */
    nout = (fir->N - fir->p);
    nout = ((nout % fir->D) == 0) ? (nout / fir->D ) : (nout / fir->D + 1);
    /* do overlap section */
    k = 0;
    x->length = fir->p + 1;
    h1->length = fir->s->length;
    h2->length = x->length;
    h2->offset = h1->length;
    while(x->length < fir->M){
        vsip_cscalar_d a = rcvdot_d(h1,fir->s);
        vsip_cscalar_d b = rcvdot_d(h2,x);
        vsip_cvput_d(y,k++,vsip_cmplx_d(a.r + b.r,a.i + b.i));
        x->length += fir->D;
        fir->s->length -= fir->D;
        fir->s->offset += fir->D;
        h1->length = fir->s->length;
        h2->length = x->length;
        h2->offset = h1->length;
    }
    x->offset += (x->length - fir->M) * x->stride;
    x->length = fir->M;
    while(k < nout){ /* do the rest of the pieces */
        vsip_cvput_d(y,k++,rcvdot_d(fir->h,x));
        x->offset += oinc;
    }
    {
        vsip_stride temp_p = (fir->p % fir->D) - (fir->N % fir->D);
        fir->p = ((temp_p < 0) ? (vsip_length)((vsip_stride)fir->D + temp_p) : (vsip_length)temp_p);
    }
    fir->s->offset = 0;
    fir->s->length = (fir->state == VSIP_STATE_SAVE) ? fir->M - 1 - fir->p : fir->M -1;
    x->length = fir->s->length;
    /* fix by JMA, 31/01/2000, incorrect offset calculation */
    /*  x->offset = xc->length - fir->s->length; */
    x->offset = xc->offset + (xc->length - fir->s->length) * xc->stride;
    if((fir->s->length > 0) && (fir->state == VSIP_STATE_SAVE)) 
        VI_cvcopy_d_d(x,fir->s);
    if(fir->state == VSIP_STATE_NO_SAVE) {  
        VI_cvfill_d(vsip_cmplx_d((vsip_scalar_d)0,(vsip_scalar_d)0),fir->s);
        fir->p = 0;
    }
    return (int) k;
}
