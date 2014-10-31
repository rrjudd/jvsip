vsip_mview_d * VU_strass_d(vsip_mview_d *A, vsip_mview_d *B, vsip_mview_d *C){
   vsip_length n=vsip_mgetrowlength_d(A);
   if((n % 2) | (n < 129)){
      vsip_mprod_d(A,B,C);
   } else {
      vsip_mview_d *A00=vsip_mcloneview_d(A); vsip_mview_d *Aij=vsip_mcloneview_d(A);
      vsip_mview_d *Ai0=vsip_mcloneview_d(A); vsip_mview_d *A0j=vsip_mcloneview_d(A);
      vsip_mview_d *B00=vsip_mcloneview_d(B); vsip_mview_d *Bij=vsip_mcloneview_d(B);
      vsip_mview_d *Bi0=vsip_mcloneview_d(B); vsip_mview_d *B0j=vsip_mcloneview_d(B);
      vsip_mview_d *C00=vsip_mcloneview_d(C); vsip_mview_d *Cij=vsip_mcloneview_d(C);
      vsip_mview_d *Ci0=vsip_mcloneview_d(C); vsip_mview_d *C0j=vsip_mcloneview_d(C);
      vsip_length m=n/2;
      vsip_index i=(vsip_index) m, j=i;
      vsip_mview_d *P1=vsip_mcreate_d(m,m,VSIP_ROW,VSIP_MEM_NONE);
      vsip_mview_d *P2=vsip_mcreate_d(m,m,VSIP_ROW,VSIP_MEM_NONE);
      vsip_mview_d *P3=vsip_mcreate_d(m,m,VSIP_ROW,VSIP_MEM_NONE);
      vsip_mview_d *P4=vsip_mcreate_d(m,m,VSIP_ROW,VSIP_MEM_NONE);
      vsip_mview_d *P5=vsip_mcreate_d(m,m,VSIP_ROW,VSIP_MEM_NONE);
      vsip_mview_d *P6=vsip_mcreate_d(m,m,VSIP_ROW,VSIP_MEM_NONE);
      vsip_mview_d *P7=vsip_mcreate_d(m,m,VSIP_ROW,VSIP_MEM_NONE);
      VU_MGETSUB_D(A,A00,0,0,1,1,m,m);VU_MGETSUB_D(A,A0j,0,j,1,1,m,m);
      VU_MGETSUB_D(A,Ai0,i,0,1,1,m,m);VU_MGETSUB_D(A,Aij,i,j,1,1,m,m);
      VU_MGETSUB_D(B,B00,0,0,1,1,m,m);VU_MGETSUB_D(B,B0j,0,j,1,1,m,m);
      VU_MGETSUB_D(B,Bi0,i,0,1,1,m,m);VU_MGETSUB_D(B,Bij,i,j,1,1,m,m);
      VU_MGETSUB_D(C,C00,0,0,1,1,m,m);VU_MGETSUB_D(C,C0j,0,j,1,1,m,m);
      VU_MGETSUB_D(C,Ci0,i,0,1,1,m,m);VU_MGETSUB_D(C,Cij,i,j,1,1,m,m);
      vsip_madd_d(A00,Aij,C00); vsip_madd_d(B00,Bij,Cij); VU_strass_d(C00,Cij,P1);
      vsip_madd_d(Ai0,Aij,C00); VU_strass_d(C00,B00,P2); 
      vsip_msub_d(B0j,Bij,C00); VU_strass_d(A00,C00,P3);
      vsip_msub_d(Bi0,Bij,C00); VU_strass_d(Aij,C00,P4); 
      vsip_madd_d(A00,A0j,C00); VU_strass_d(C00,Bij,P5);
      vsip_msub_d(Ai0,A00,C00); vsip_madd_d(B00,B0j,Cij); VU_strass_d(C00,Cij,P6);
      vsip_msub_d(A0j,Aij,C00); vsip_madd_d(Bi0,Bij,Cij); VU_strass_d(C00,Cij,P7);
      vsip_madd_d(P1,P4,C00);vsip_msub_d(C00,P5,C00); 
      vsip_madd_d(C00,P7,C00); vsip_madd_d(P3,P5,C0j); 
      vsip_madd_d(P2,P4,Ci0); vsip_madd_d(P1,P3,Cij); 
      vsip_msub_d(Cij,P2,Cij); vsip_madd_d(Cij,P6,Cij);
      vsip_mdestroy_d(C00); vsip_mdestroy_d(Cij); vsip_mdestroy_d(Ci0);
      vsip_mdestroy_d(C0j); vsip_mdestroy_d(A00); vsip_mdestroy_d(Ai0); 
      vsip_mdestroy_d(A0j);vsip_mdestroy_d(Aij); vsip_mdestroy_d(B00);
      vsip_mdestroy_d(Bi0); vsip_mdestroy_d(B0j);vsip_mdestroy_d(Bij);
   }
   return C;
