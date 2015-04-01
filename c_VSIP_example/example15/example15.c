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
/* $Id: example15.c,v 2.0 2003/02/22 15:27:31 judd Exp $ */

#include<vsip.h>
#define L  9   /* length */
int main(){vsip_init((void*)0);{
    vsip_vview_f *a = vsip_vcreate_f(L,0),
                 *b = vsip_vcreate_f(L,0);
    vsip_vview_bl *ab_bl = vsip_vcreate_bl(L,0);
    vsip_vview_vi *ab_vi = vsip_vcreate_vi(L,0);
    vsip_length    numTrue = 0;
    int i = 0;
    /* Make up some data */
    vsip_vramp_f(-2.0, 1 , a);
    vsip_vramp_f(2.0, -1 , b);
    printf("index    A       B\n");
    for(i = 0; i<L; i++)
       printf("%3i %7.1f %7.1f \n", i,
              vsip_vget_f(a,i),
              vsip_vget_f(b,i));

    vsip_vleq_f(a,b,ab_bl);

    if(vsip_vanytrue_bl(ab_bl)){
        numTrue = vsip_vindexbool(ab_bl,ab_vi);
        for(i = 0; i < numTrue; i++)
           printf("A = B at index %3i\n",
           (int)vsip_vget_vi(ab_vi,i));
    }
    else{
        printf("No true cases\n");
    }
    vsip_valldestroy_f(a);
    vsip_valldestroy_f(b);
    vsip_valldestroy_bl(ab_bl);
    vsip_valldestroy_vi(ab_vi);
    } vsip_finalize((void*)0); return 0;
}
