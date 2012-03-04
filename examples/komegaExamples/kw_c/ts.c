#include"ts.h"

static void VU_rowview_f(
          vsip_vview_f *v, 
          vsip_mview_f* m, 
          vsip_index i)
{
   vsip_mattr_f mattr;
   vsip_vattr_f vattr;
   vsip_mgetattrib_f(m,&mattr);
   vattr.offset = mattr.offset + i * mattr.col_stride;
   vattr.length = mattr.row_length;
   vattr.stride = mattr.row_stride;
   vsip_vputattrib_f(v,&vattr);
   return;
}

int ts_init( ts_obj* ts, param_obj *param)
{
   int retval = 0;
   if(param){
   vsip_scalar_f L = 2 * param->Fs/(param->Nsens * param->Dsens/param->c) + param->Nts + 1;
   vsip_vview_f *kernel = vsip_vcreate_kaiser_f(6,1,0);
   ts->Nsim_freqs=param->Nsim_freqs;
   ts->freqs = param->sim_freqs;
   ts->bearings = param->sim_bearings;
   ts->Nts = param->Nts;
   ts->Nsens = param->Nsens;
   ts->c = param->c;
   ts->Dsens = param->Dsens;
   ts->Nsim_noise=param->Nsim_noise;
   ts->Fs = param->Fs;
   if(kernel) ts->fir=vsip_fir_create_f(kernel,VSIP_NONSYM, 2*L,2,VSIP_STATE_SAVE,0,0);
   if(!ts->fir) retval++;
   ts->noise = vsip_vcreate_f(2*L,VSIP_MEM_NONE);
   if(!ts->noise) retval++;
   ts->bl_noise = vsip_vcreate_f(L,VSIP_MEM_NONE);
   if(!ts->bl_noise) retval++;
   ts->rand = vsip_randcreate(7,1,1,VSIP_PRNG);
   if(!ts->rand) retval++;
   ts->t = vsip_vcreate_f(param->Nts,VSIP_MEM_NONE);
   if(ts->t) vsip_vramp_f(0,1.0/param->Fs,ts->t);
   else retval++;
   ts->t_dt = vsip_vcreate_f(param->Nts,VSIP_MEM_NONE);
   if(!ts->t_dt)  retval++;
   ts->m_data = vsip_mcreate_f(param->Nsens,param->Nts,VSIP_ROW,VSIP_MEM_NONE);
   if(ts->m_data)  ts->v_data = vsip_mrowview_f(ts->m_data,0);
   else retval++;
   if(!ts->v_data) retval++;
   vsip_valldestroy_f(kernel);
   } else {
      printf("param object not valid\n");
      retval++;
   }
   return retval;
}     
void ts_fin(ts_obj* ts)
{
    vsip_fir_destroy_f(ts->fir);
    vsip_valldestroy_f(ts->noise);
    vsip_valldestroy_f(ts->bl_noise);
    vsip_randdestroy(ts->rand);
    vsip_valldestroy_f(ts->t);
    vsip_valldestroy_f(ts->t_dt);
    vsip_vdestroy_f(ts->v_data);
    vsip_malldestroy_f(ts->m_data);
    return;
}
void ts_sim_nb(ts_obj *ts)
{
   int i,j;
   vsip_mview_f *m_data = ts->m_data;
   vsip_vview_f *v_data = ts->v_data;
   vsip_vview_f *t = ts->t;
   vsip_vview_f *t_dt = ts->t_dt;
   vsip_scalar_f dt;
   vsip_scalar_f d_t = ts->Dsens/ts->c;
   for(i=0; i<ts->Nsim_freqs;i++){
      float f=ts->freqs[i];
      float b=d_t * (float)cos(ts->bearings[i]*M_PI/180);
      for(j=0; j<ts->Nsens; j++){
          dt = (float)j * b;
          vsip_svadd_f(dt,t,t_dt);
          vsip_svmul_f(2 * M_PI * f,t_dt,t_dt);
          vsip_vcos_f(t_dt,t_dt);
          vsip_svmul_f(3,t_dt,t_dt);
          VU_rowview_f(v_data,m_data,j);
          vsip_vadd_f(t_dt,v_data,v_data);
      } /* next phone */
   }    /* next frequency/bearing */
   return;
}
void ts_sim_noise( ts_obj *ts){
   vsip_mview_f *m_data  = ts->m_data;
   vsip_vview_f *v_data  = ts->v_data;
   vsip_vview_f *noise   = ts->noise;
   vsip_vview_f *bl_noise  = ts->bl_noise;
   vsip_fir_f   *fir     = ts->fir;
   vsip_randstate *rand = ts->rand;
   vsip_index i,j;
   vsip_scalar_f d_t   = ts->Fs * (float)ts->Dsens / ts->c;
   vsip_offset o_0    = (vsip_offset) (d_t * ts->Nsens + 1);
   vsip_scalar_f a_stp = M_PI/(float)ts->Nsim_noise;
   vsip_vattr_f bl_attr;
   vsip_vgetattrib_f(bl_noise,&bl_attr);
   for(j=0; j<ts->Nsim_noise; j++){
      vsip_scalar_f a_crct = cos((float)j * a_stp);
      vsip_vrandn_f(rand,noise);
      vsip_firflt_f(fir,noise,bl_noise);
      vsip_svmul_f(12.0/(float)ts->Nsim_noise,bl_noise,bl_noise);
      vsip_vputlength_f(bl_noise,ts->Nts);
      for(i=0; i<ts->Nsens; i++){
         vsip_vputoffset_f(bl_noise, (vsip_index)(o_0 + i * d_t * a_crct));
         VU_rowview_f(v_data,m_data,i);
         vsip_vadd_f(bl_noise,v_data,v_data);
      }
      vsip_vputattrib_f(bl_noise,&bl_attr);
   }
   vsip_smadd_f(-vsip_mmeanval_f(m_data),m_data,m_data);
}
void ts_zero(ts_obj *ts){
   vsip_mfill_f(0,ts->m_data);
}
vsip_mview_f * ts_instance(ts_obj *ts){
    return ts->m_data;
}
