#include<vsip.h>

vsip_index *vindexptr(void)
{
    vsip_index *idx=(vsip_index*) malloc(sizeof(vsip_scalar_mi));
    return idx;
}

void vindexfree(vsip_index *idx)
{
    if(idx) free(idx);
}

vsip_index vindexptrToInt(vsip_index *idx){
    return *idx;
}
