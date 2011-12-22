static 
void 
VI_cgivens_d(
             vsip_cscalar_d a,
             vsip_cscalar_d b,
             vsip_cscalar_d *c,
             vsip_cscalar_d *s,
             vsip_cscalar_d  *r)
{
   vsip_scalar_d am = vsip_cmag_d(a);
   vsip_scalar_d bm = vsip_cmag_d(b);
   c->i = 0.0;
   if(am == 0.0){
      *r = b;
      c->r = 0.0; 
      s->r = 1; s->i = 0.0;   
   } else {
      vsip_scalar_d scale = am + bm;
      vsip_cscalar_d alpha = vsip_cmplx_d(a.r/am, a.i/am);
      vsip_scalar_d scalesq = scale * scale;
      vsip_scalar_d norm = scale * (vsip_scalar_d)sqrt((am*am)/scalesq + (bm * bm)/scalesq);
      c->r =am/norm;
      
      s->r =  (alpha.r * b.r + alpha.i * b.i)/norm; 
      s->i = (-alpha.r * b.i + alpha.i * b.r)/norm;
      r->r = alpha.r * norm;  r->i = alpha.i * norm;
   }
   return;
}

static 
void 
VI_cgivens_r_d( vsip_cmview_d *A)
{
   vsip_length m = A->col_length;
   vsip_length n = A->row_length;
   vsip_length i,j,k;
   vsip_cscalar_d c,s10,s01,r;
   vsip_stride r_st = A->row_stride * A->block->cstride;
   
   for(j=0; j<n; j++){
      for(i=m-1; i>j; i--){
         vsip_scalar_d *a0p_r = A->block->R->array + (A->offset + (i-1) * A->col_stride + j * A->row_stride) * A->block->cstride;
         vsip_scalar_d *a0p_i = A->block->I->array + (A->offset + (i-1) * A->col_stride + j * A->row_stride) * A->block->cstride;
         vsip_scalar_d *a1p_r = A->block->R->array + (A->offset + i * A->col_stride + j * A->row_stride) * A->block->cstride;
         vsip_scalar_d *a1p_i = A->block->I->array + (A->offset + i * A->col_stride + j * A->row_stride) * A->block->cstride;
         vsip_cscalar_d a,b;
         a.r = *a0p_r; a.i = *a0p_i;
         b.r = *a1p_r; b.i = *a1p_i;
         VI_cgivens_d(a,b,&c,&s01,&r);
         /* rotate r so the iamginary part is 0 */
         *a0p_r = vsip_cmag_d(r); *a0p_i = 0;
         *a1p_r = 0.0; *a1p_i = 0.0;
         /* store a rotation vector in r */
         r.r /= *a0p_r; r.i = - r.i / *a0p_r;
         a0p_r += r_st; a0p_i += r_st;
         a1p_r += r_st; a1p_i += r_st;
         s10.r = - s01.r; s10.i = s01.i;
         for(k=1; k<n-j; k++){
            vsip_scalar_d a0_r = *a0p_r, a1_r = *a1p_r;
            vsip_scalar_d a0_i = *a0p_i, a1_i = *a1p_i;
            vsip_cscalar_d a0;
            a0.r = a0_r * c.r + a1_r * s01.r - a1_i * s01.i;
            a0.i = a0_i * c.r + s01.r * a1_i + a1_r * s01.i;
            /* correct a0 for rotation and place in matrix*/
            *a0p_r = r.r * a0.r - r.i * a0.i; 
            *a0p_i = r.r * a0.i + r.i * a0.r;
            *a1p_r = a1_r * c.r + s10.r * a0_r - s10.i * a0_i;
            *a1p_i = a1_i * c.r + s10.r * a0_i + s10.i * a0_r; 
            a0p_r += r_st; a0p_i += r_st;
            a1p_r += r_st; a1p_i += r_st;
         }
      }
   }
   return;
}
