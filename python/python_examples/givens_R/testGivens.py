from vsip import *
import vsiputils as vsip
import vsipUser as VU
from VI_givens_d import *


def testGivens(): 
   A = vsip.create('cmview_d',(10,6,VSIP_ROW,VSIP_MEM_NONE));
   czero = vsip_cmplx_d(0.0,0.0);
   vsip.fill(czero,A);
   for i in range(vsip.getrowlength(A)):
       ac = vsip.colview(A,i);
       ac_r= vsip.realview(ac);
       ac_i = vsip.imagview(ac);
       vsip.ramp(-1.3,1.1,ac_r);
       vsip.ramp(+1.3,-1.1,ac_i);
       vsip.destroy(ac_r); vsip.destroy(ac_i);
       vsip.destroy(ac);
   ad = vsip_cmdiagview_d(A,0);
   ad_r = vsip_vrealview_d(ad);
   ad_i = vsip_vimagview_d(ad);
   vsip.ramp(3,1.2,ad_r);
   vsip.ramp(3,-1.2,ad_i);
   vsip.destroy(ad_i);
   vsip.destroy(ad_r);
   vsip.destroy(ad);
   print("Input data \n");
   print("A = " + VU.mstring(A,"%6.4f"))
   VI_cgivens_r_d(A)
   print("R = " + VU.mstring(A,"%7.4f"))
   vsip.allDestroy(A);

testGivens()
