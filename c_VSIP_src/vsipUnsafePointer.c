/*
//  vsipUnsafePointer.c
//  vsip
//
//  Created by Randall R. Judd on 12/26/16.
//  Copyright © 2016 JVSIP. All rights reserved.
*/
 
#include<vsip.h>
#include<vsip_blockattributes_d.h>
#include<vsip_blockattributes_f.h>
#include<vsip_cblockattributes_d.h>
#include<vsip_cblockattributes_f.h>

double* vsipUnsafeBlockPtr_d(vsip_block_d *blk, vsip_stride *stride){
    *stride = blk->rstride;
    return blk->array;
}

float* vsipUnsafeBlockPtr_f(vsip_block_f *blk, vsip_stride *stride){
    *stride = blk->rstride;
    return blk->array;
}
double* vsipUnsafeBlockPtr_cdR(vsip_cblock_d *blk, vsip_stride *stride){
    *stride = blk->cstride;
    return blk->R->array;
}

float* vsipUnsafeBlockPtr_cfR(vsip_cblock_f *blk, vsip_stride *stride){
    *stride = blk->cstride;
    return blk->R->array;
}
double* vsipUnsafeBlockPtr_cdI(vsip_cblock_d *blk, vsip_stride *stride){
    *stride = blk->cstride;
    return blk->I->array;
}

float* vsipUnsafeBlockPtr_cfI(vsip_cblock_f *blk, vsip_stride *stride){
    *stride = blk->cstride;
    return blk->I->array;
}
