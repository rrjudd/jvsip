# Created RJudd
# Converted from chold tests in c_VSIP_testing Directory
# Note that blockbinds are not functional at this time in python so they have been removed
# This code includes                                            
# no warranty, express or implied, including the warranties     
# of merchantability and fitness for a particular purpose.     
# No person or entity                                         
# assumes any legal liability or responsibility for the accuracy,
# completeness, or usefulness of any information, apparatus,    
# product, or process disclosed, or represents that its use would
# not infringe privately owned rights                           
import vsiputils as vsip
import vsipUser as VU
from vsip import vsip_init, vsip_finalize

def chol(p):
      print("********\nTEST chol"+p+"\n")
      ablock = vsip.create('block'+p,(200,vsip.VSIP_MEM_NONE))
      R = vsip.create('mview'+p,(4,4,vsip.VSIP_ROW,vsip.VSIP_MEM_NONE))
      RH = vsip.create('mview'+p,(4,4,vsip.VSIP_ROW,vsip.VSIP_MEM_NONE))
      A = vsip.bind(ablock,(99,-11,4,-2,4))
      B = vsip.bind(ablock,(100,20,4,2,3))
      ans = vsip.create('mview'+p,(4,3,vsip.VSIP_ROW,vsip.VSIP_MEM_NONE))
      chol = vsip.create('chol'+p,(vsip.VSIP_TR_UPP,4))
      data_R = [ [1.0,  -2.0,  3.0,  1.0], 
                       [0.0,   2.0,  4.0, -1.0], 
                       [0.0,   0.0,  4.0,  3.0], 
                       [0.0,   0.0,  0.0,  6.0] ]
      data_Br = [ [ 1.0, 2.0, 3.0],  
                  [ 0.0, 1.0, 2.0], 
                  [ 3.0, 0.0, 1.0], 
                  [ 3.0, 4.0, 5.0]]
      data_ans = [[  4.6250, 13.9062, 21.0000],
                  [  1.3333,  4.1667,  6.3333],
                  [ -0.3750, -1.3438, -2.0000],
                  [  0.1667,  0.4583,  0.6667]]
   
      for i in range(4):
         for j in range(4):
            vsip.put(R,(i,j),data_R[i][j])
      for i in range(4):
         for j in range(3):
            vsip.put(B,(i,j),data_Br[i][j])
            vsip.put(ans,(i,j),data_ans[i][j])
      vsip.trans(R,RH)
      vsip.prod(RH,R,A)
      print("R = \n");VU.mprint(R,"%4.2f")
      print("RH = \n");VU.mprint(RH,"%4.2f")
      print("A = R * RH\n");VU.mprint(A,"%4.2f")
      print("B \n");VU.mprint(B,"%4.2f")
      vsip.chold(chol,A)
      vsip.cholsol(chol,B)
      print("Solve using cholesky AX = B\n X = \n");VU.mprint(B,"%4.2f")
      vsip.destroy(chol)
      print("right answer \n ans = \n");VU.mprint(ans,"%4.2f")
   
      vsip.sub(ans,B,B)
      chk =  vsip.sumsqval(B)
      if chk > .001: 
         print("error\n")
      else:
         print("correct\n")
      lu = vsip.create('lu'+p,4)
      Bans = vsip.create('mview'+p,(4,3,vsip.VSIP_ROW,vsip.VSIP_MEM_NONE))
      vsip.prod(RH,R,A)
      for i in range(4):
         for j in range(3):
            vsip.put(B,(i,j),data_Br[i][j])
      vsip.lud(lu,A)
      vsip.lusol(lu,vsip.VSIP_MAT_NTRANS,B)
      print("Solve using LUD AX = B\n X = \n");VU.mprint(B,"%4.2f")
      vsip.destroy(lu)
      vsip.prod(RH,R,A)
      vsip.prod(A,B,Bans)
      print("Bans = A X\n");VU.mprint(Bans,"%4.2f")
      vsip.sub(ans,B,B)
      chk =  vsip.sumsqval(B)
      if chk > .001:
         print("error\n")
      else:
         print("correct\n")
      vsip.allDestroy(Bans)
      vsip.allDestroy(R)
      vsip.allDestroy(RH)
      vsip.destroy(B)
      vsip.allDestroy(A)

def cchol(p):
      print("********\nTEST cchol"+p+"\n")
      ablock = vsip.create('cblock'+p,(200,vsip.VSIP_MEM_NONE))
      R = vsip.create('cmview'+p,(4,4,vsip.VSIP_ROW,vsip.VSIP_MEM_NONE))
      RH = vsip.create('cmview'+p,(4,4,vsip.VSIP_ROW,vsip.VSIP_MEM_NONE))
      A = vsip.bind(ablock,(40,-9,4,-2,4))
      B = vsip.bind(ablock,(100,10,4,3,3))
      chol = vsip.create('cchol'+p,(vsip.VSIP_TR_UPP,4))
      ans = vsip.create('cmview'+p,(4,3,vsip.VSIP_ROW,vsip.VSIP_MEM_NONE))
      data_R =     [ [1.0,  -2.0,  3.0,  1.0], 
                      [0.0,   2.0,  4.0, -1.0], 
                      [0.0,   0.0,  4.0,  3.0], 
                      [0.0,   0.0,  0.0,  6.0] ]
      data_I =     [ [0.0,  2.0,  2.0,  1.0], 
                       [0.0,  0.0,  2.0, -4.0], 
                       [0.0,  0.0,  0.0,  2.0], 
                       [0.0,  0.0,  0.0,  0.0] ]
      data_Br =    [ [1.0, 2.0, 3.0],  
                      [0.0, 1.0, 2.0], 
                      [3.0, 0.0, 1.0], 
                      [3.0, 4.0, 5.0]]
      data_Bi =    [ [1.0, 0.5, 3.2], 
                      [2.0, 0.0, 0.6], 
                      [0.6, 2.0, 0.0], 
                      [5.0, 7.0, 8.0]]
      data_ans_r = [ [13.6236, 27.5451, 43.1573],
                      [-0.1104,  5.2370,  3.3312],
                      [-0.8403, -1.9410, -2.9823],
                     [ 0.7000,  0.8125,  1.7375] ]
      data_ans_i = [ [19.4965,  5.3707, 40.9604],
                     [ 6.7292,  5.4896, 15.8781],
                     [-1.4021, -0.3776, -2.9688],
                     [0.3694, -0.1632,  0.4667] ]
      for i in range(4):
         for j in range(4):
            vsip.put(R,(i,j),vsip.complexToCscalar('cscalar'+p,(data_R[i][j] + 1j * data_I[i][j])))
      for i in range(4):
         for j in range(3):
            vsip.put(B,(i,j),vsip.complexToCscalar('cscalar'+p,(data_Br[i][j] + 1j * data_Bi[i][j])))
            vsip.put(ans,(i,j),vsip.complexToCscalar('cscalar'+p,(data_ans_r[i][j] + 1j * data_ans_i[i][j])))
      vsip.herm(R,RH)
      vsip.prod(RH,R,A)
      print("R = \n");VU.mprint(R,"%4.2f")
      print("RH = \n");VU.mprint(RH,"%4.2f")
      print("A = R * RH\n");VU.mprint(A,"%4.2f")
      print("B \n");VU.mprint(B,"%4.2f")
   
      vsip.chold(chol,A)
      vsip.cholsol(chol,B)
      print("Solve using cholesky AX = B\n X = \n");VU.mprint(B,"%4.2f")
      vsip.destroy(chol)
      print("right answer \n ans = \n");VU.mprint(ans,"%4.2f")
      vsip.sub(ans,B,B)
      chk =  vsip.meansqval(B)
      if chk > .001:
         print("error\n")
      else:
         print("correct\n")
      lu = vsip.create('clu'+p,4)
      Bans = vsip.create('cmview'+p,(4,3,vsip.VSIP_ROW,vsip.VSIP_MEM_NONE))
      vsip.prod(RH,R,A)
      for i in range(4):
         for j in range(3):
            vsip.put(B,(i,j),vsip.complexToCscalar('cscalar'+p,(data_Br[i][j] + 1j * data_Bi[i][j])))
      vsip.lud(lu,A)
      vsip.lusol(lu,vsip.VSIP_MAT_NTRANS,B)
      print("Solve using LUD AX = B\n X = \n");VU.mprint(B,"%4.2f")
      vsip.destroy(lu)
      vsip.prod(RH,R,A)
      vsip.prod(A,B,Bans)
      print("Bans = A X \n");VU.mprint(Bans,"%4.2f")
      vsip.sub(ans,B,B)
      chk =  vsip.meansqval(B)
      if chk > .001:
         print("error\n")
      else:
         print("correct\n")
      vsip.allDestroy(Bans)
      vsip.allDestroy(R)
      vsip.allDestroy(RH)
      vsip.destroy(B)
      vsip.allDestroy(A)

vsip_init(None)
chol('_f')
cchol('_f')
chol('_d')
cchol('_d')
vsip_finalize(None)
