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

#include<vsip.h>
#define L 20 /* A length*/
int main(){
    vsip_init((void*)0);
    {
        vsip_vview_d*   a = vsip_vcreate_d(L,0);
        vsip_vview_d*   b = vsip_vcreate_d(L,0);
        vsip_vview_vi*  ab_vi = vsip_vcreate_vi(L,0);
        vsip_vview_bl*  ab_bl= vsip_vcreate_bl(L,0);
        int i;
        vsip_length N;
        /* make up some data */
        vsip_vramp_d(0,2 * M_PI/(L-1),a);
        vsip_vcos_d(a,b);
        /* find out where b is greater than zero */
        vsip_vfill_d(0,a);
        vsip_vlgt_d(b,a,ab_bl);
        /* find the index where b is greater than zero */
        if((N = vsip_vindexbool(ab_bl,ab_vi))){
            /* make a vector of those points where b is greater than zero*/
            vsip_vgather_d(b,ab_vi,vsip_vputlength_d(a,N));
            /*print out the results */
            printf("Index   Value\n");
            for(i=0; i<N; i++)
                printf("%li      %6.3f\n",
                       vsip_vget_vi(ab_vi,i),
                       vsip_vget_d(a,i));
        }
        else{ printf("Zero Length Index");
        }
        vsip_valldestroy_d(a);
        vsip_valldestroy_d(b);
        vsip_valldestroy_vi(ab_vi);
        vsip_valldestroy_bl(ab_bl);
    }
    vsip_finalize((void*)0);
    return 0;
}
