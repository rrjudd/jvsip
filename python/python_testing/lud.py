# Created RJudd
# Converted from lud tests in c_VSIP_testing Directory
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
from vsip import vsip_init,vsip_finalize
from vsip import vsip_cmplx_d, vsip_cmplx_f,vsip_csub_f,vsip_csub_d,vsip_cmag_d,vsip_cmag_f

def lud(p):
   """
     Usage is lud(p) where p is a string of either '_d' or '_f' to denote precision.
     only works for real data. 
   """
   print('********\nTEST lud'+p+'\n')
   block = vsip.create('block'+p,(500,vsip.VSIP_MEM_NONE))
   AC = vsip.bind(block,(0,6,6,1,6))
   AG = vsip.bind(block,(36,2,6,18,6))
   IC = vsip.bind(block,(150,1,6,6,6))
   IG = vsip.bind(block,(200,2,6,14,6))
   B = vsip.bind(block,(300,6,6,1,6))
   A = vsip.bind(block,(350,6,6,1,6))
   X = vsip.bind(block,(400,5,6,1,3))
   Y = vsip.bind(block,(450,3,6,1,3))
   ludC = vsip.create('lu'+p,6)
   ludG = vsip.create('lu'+p,6)
   AT = vsip.transview(A)
   data= [ [0.50,     7.00,    10.00,    12.00,    -3.00,     0.00],
            [2.00,    13.00,    18.00,     6.00,     0.00,   130.00],
            [3.00,    -9.00,     2.00,     3.00,     2.00,    -9.00],
            [4.00,     2.00,     2.00,     4.00,     1.00,     2.00],
            [0.20,     2.00,     9.00,     4.00,     1.00,     2.00],
            [0.10,     2.00,     0.30,     4.00,     1.00,     2.00]]
              
   ydata= [[  77.85,   155.70,   311.40],
         [ 942.00,  1884.00,  3768.00],
         [   1.00,     2.00,     4.00],
         [  68.00,   136.00,   272.00],
         [  85.20,   170.40,   340.80],
         [  59.00,   118.00,   236.00]]

   Ident = [[1, 0, 0, 0, 0, 0],
                 [0, 1, 0, 0, 0, 0],
                 [0, 0, 1, 0, 0, 0],
                 [0, 0, 0, 1, 0, 0],
                 [0, 0, 0, 0, 1, 0],
                 [0, 0, 0, 0, 0, 1]]

   for i in range(6):  
       for j in range(6):
           vsip.put(A, (i,j),data[i][j])
           vsip.put(AC,(i,j),data[i][j])
           vsip.put(AG,(i,j),data[i][j])
           vsip.put(IC,(i,j),Ident[i][j])
           vsip.put(IG,(i,j),Ident[i][j])
   for i in range(6):
       for j in range(3):
           vsip.put(X,(i,j),ydata[i][j])

   print("Matrix A = \n");VU.mprint(A,'%7.2f')
   vsip.lud(ludC,AC); vsip.lud(ludG,AG)
   print("vsip_lusol(lud,vsip.VSIP_MAT_NTRANS,X)\n")
   print("Solve A X = I \n")
   vsip.lusol(ludC,vsip.VSIP_MAT_NTRANS,IC)
   vsip.lusol(ludG,vsip.VSIP_MAT_NTRANS,IG)
   print("for compact case X = \n");VU.mprint(IC,'%8.4f')
   print("for general case X = \n");VU.mprint(IG,'%8.4f')
   chk = 0
   for i in range(6):
       for j in range(6):
           chk += abs(vsip.get(IC,(i,j)) - vsip.get(IG,(i,j)))
   if chk > .01: 
       print("error\n") 
   else:
       print("agree\n")
   vsip.prod(A,IC,B)
   chk = 0
   for i in range(6):   
       for j in range(6):
           chk += abs(vsip.get(B,(i,j)) - Ident[i][j])
   vsip.prod(A,IG,B)
   for i in range(6):
       for j in range(6):
           chk += abs(vsip.get(B,(i,j)) - Ident[i][j])
   print("mprod(A,X) = \n"); VU.mprint(B,'%8.3f')
   if chk > .01: 
       print("error\n") 
   else:
       print("correct\n")
   print("Matrix Transpose A = \n");VU.mprint(AT,'%7.2f')
   for i in range(6):
       for j in range(6):
         vsip.put(IC,(i,j),Ident[i][j])
         vsip.put(IG,(i,j),Ident[i][j])
   print("vsip_lusol(lud,vsip.VSIP_MAT_TRANS,X)\n")
   print("Solve trans(A) X = I \n")
   vsip.lusol(ludC,vsip.VSIP_MAT_TRANS,IC)
   vsip.lusol(ludG,vsip.VSIP_MAT_TRANS,IG)
   print("for compact case X = \n");VU.mprint(IC,'%8.4f')
   print("for general case X = \n");VU.mprint(IG,'%8.4f')
   chk = 0
   for i in range(6):
       for j in range(6):
         chk += abs(vsip.get(IC,(i,j)) - vsip.get(IG,(i,j)))
   if chk > .01:
       print("error\n") 
   else: 
       print("agree\n")
   vsip.prod(AT,IC,B)
   chk = 0
   for i in range(6):
       for j in range(6):
          chk += abs(vsip.get(B,(i,j)) - Ident[i][j])
   vsip.prod(AT,IG,B)
   for i in range(6):
       for j in range(6):
          chk += abs(vsip.get(B,(i,j)) - Ident[i][j])
   print("mprod(trans(A),X) = \n"); VU.mprint(B,'%8.3f')
   if chk > .01:
       print("error\n") 
   else: 
       print("correct\n")
   print("check A X = Y; vsip.VSIP_MAT_NTRANS\n")
   print("Y = \n");VU.mprint(X,'%8.4f')
   vsip.lusol(ludC,vsip.VSIP_MAT_NTRANS,X)
   print("X = \n"); VU.mprint(X,'%8.4f')
   vsip.prod(A,X,Y)
   print(" Y = A X\n");VU.mprint(Y,'%8.4f')
   chk = 0
   for i in range(6):
       for j in range(3):
           chk += abs(vsip.get(Y,(i,j)) - ydata[i][j])
   if chk > .01:
       print("error\n") 
   else : 
       print("agree\n")
   for i in range(6):
       for j in range(3):
          vsip.put(X,(i,j),ydata[i][j])
   print("Y = \n");VU.mprint(X,'%8.4f')
   vsip.lusol(ludG,vsip.VSIP_MAT_TRANS,X)
   vsip.prod(AT,X,Y)
   print("X = \n");VU.mprint(X,'%8.4f')
   print("Y = trans(A) X\n");VU.mprint(Y,'%8.4f')
   chk = 0
   for i in range(6):
       for j in range(3):
           chk += abs(vsip.get(Y,(i,j)) - ydata[i][j])
   if (chk > .01):
       print("error\n") 
   else: 
       print("agree\n")
   vsip.destroy(AC)
   vsip.destroy(AG)
   vsip.destroy(IC)
   vsip.destroy(IG)
   vsip.destroy(B)
   vsip.destroy(A)
   vsip.destroy(X)
   vsip.destroy(Y)
   vsip.allDestroy(AT)
   vsip.destroy(ludC)
   vsip.destroy(ludG)

def clud(p):
   def cmplx(p,re,im):
      return eval('vsip_cmplx'+p+'(re,im)')
   def csub(p,a,b):
       return eval('vsip_csub'+p+'(a,b)')
   def cmag(p,a):
       return eval('vsip_cmag'+p+'(a)')
   """
     Usage is clud(p) where p is a string of either '_d' or '_f' to denote precision.
     only works for complex data. 
   """
   print('********\nTEST clud'+p+'\n')
   block = vsip.create('cblock'+p,(600,vsip.VSIP_MEM_NONE))
   AC = vsip.bind(block,(0,7,7,1,7))
   AG = vsip.bind(block,(175,-2,7,-18,7))
   IC = vsip.bind(block,(176,1,7,7,7))
   IG = vsip.bind(block,(226,2,7,15,7))
   B = vsip.bind(block,(335,7,7,1,7))
   A = vsip.bind(block,(385,7,7,1,7))
   X = vsip.bind(block,(434,5,7,1,3))
   Y = vsip.bind(block,(475,3,7,1,3))
   ludC = vsip.create('clu'+p,7)
   ludG = vsip.create('clu'+p,7)
   data_r = [ \
          [0.5,  7.0, 10.0, 12.0, -3.0,  0.0,   0.05], \
          [2.0, 13.0, 18.0,  6.0,  0.0, 130.0,  8.0], \
          [3.0, -9.0,  2.0,  3.0,  2.0,  -9.0,  6.0], \
          [4.0,  2.0,  2.0,  4.0,  1.0,   2.0,  3.0], \
          [0.2,  2.0,  9.0,  4.0,  1.0,   2.0,  3.0], \
          [0.1,  2.0,  0.3,  4.0,  1.0,   2.0,  3.0], \
          [0.0,  0.2,  3.0,  4.0,  1.0,   2.0,  3.0]];
   data_i = [
         [0.1, 0.1, 0.1, 0.1, 0.1, 0.1, 0.1], \
        [0.1, 0.1, 0.1, 0.1, 0.1, 0.1, 0.1], \
        [0.1, 0.1, 0.1, 0.2, 0.2,-0.2, 0.2], \
        [0.2, 0.2, 0.2, 0.2, 0.2, 0.2, 0.2], \
        [0.3, 0.3, 0.3, 0.3, 0.3, 0.3, 0.3], \
        [0.4, 0.4, 0.4, 0.4, 0.4, 0.4, 0.4], \
        [0.4, 0.4, 0.4, 0.4, 0.4, 0.4, 0.4]];

   ydata_r = [ \
        [77.85,   155.70,   311.40], \
       [942.00,  1884.00,  3768.00], \
         [1.00,     2.00,     4.00], \
        [68.00,   136.00,   272.00], \
        [85.20,   170.40,   340.80], \
        [59.00,   118.00,   236.00], \
         [5.00,    18.00,     6.00]];

   ydata_i = [ \
        [4.5,      1.70,   -3.40], \
        [3.7,    184.00,   -2.00], \
        [1.00,     3.00,    2.00], \
        [68.00,   16.00,  272.00], \
        [85.20, 1170.40,  340.80], \
        [59.00,   18.50,   62.00], \
        [59.00,   11.60,   26.00]];

                  
   Ident = [    \
                  [1, 0, 0, 0, 0, 0, 0], \
                  [0, 1, 0, 0, 0, 0, 0], \
                  [0, 0, 1, 0, 0, 0, 0], \
                  [0, 0, 0, 1, 0, 0, 0], \
                  [0, 0, 0, 0, 1, 0, 0], \
                  [0, 0, 0, 0, 0, 1, 0], \
                  [0, 0, 0, 0, 0, 0, 1]];
   AH = vsip.create('cmview'+p,(7,7,vsip.VSIP_ROW,vsip.VSIP_MEM_NONE));

   for i in range(7):  
       for j in range(7):
           a=cmplx(p,data_r[i][j],data_i[i][j])
           e=cmplx(p,Ident[i][j],0.0)
           vsip.put(A, (i,j),a)
           vsip.put(AC,(i,j),a)
           vsip.put(AG,(i,j),a)
           vsip.put(IC,(i,j),e)
           vsip.put(IG,(i,j),e)
   for i in range(7):
       for j in range(3):
           a=cmplx(p,ydata_r[i][j],ydata_i[i][j])
           vsip.put(X,(i,j),a)
   vsip.herm(A,AH)
   print("Matrix A = \n");VU.mprint(A,'%7.2f')
   vsip.lud(ludC,AC); vsip.lud(ludG,AG)
   print("vsip_clusol(lud,vsip.VSIP_MAT_NTRANS,X)\n")
   print("Solve A X = I \n")
   vsip.lusol(ludC,vsip.VSIP_MAT_NTRANS,IC)
   vsip.lusol(ludG,vsip.VSIP_MAT_NTRANS,IG)
   print("for compact case X = \n");VU.mprint(IC,'%8.4f')
   print("for general case X = \n");VU.mprint(IG,'%8.4f')
   chk = 0
   for i in range(7):
       for j in range(7):
           chk += cmag(p,csub(p,vsip.get(IC,(i,j)),vsip.get(IG,(i,j))))
   if chk > .01: 
       print("error\n") 
   else:
       print("agree\n")
   vsip.prod(A,IC,B)
   chk = 0
   for i in range(7):   
       for j in range(7):
           chk += cmag(p,csub(p,vsip.get(B,(i,j)),cmplx(p,Ident[i][j],0.0)))
   vsip.prod(A,IG,B)
   for i in range(7):
       for j in range(7):
           chk += cmag(p,csub(p,vsip.get(B,(i,j)),cmplx(p,Ident[i][j],0.0)))
   print("mprod(A,X) = \n"); VU.mprint(B,'%8.3f')
   if chk > .01: 
       print("error\n") 
   else:
       print("correct\n")
   # check case VSIP_MAT_HERM
   print("Matrix Hermitian A = \n");VU.mprint(AH,'%7.2f')
   for i in range(7):
       for j in range(7):
         vsip.put(IC,(i,j),cmplx(p,Ident[i][j],0.0))
         vsip.put(IG,(i,j),cmplx(p,Ident[i][j],0.0))
   print("vsip_clusol(lud,vsip.VSIP_MAT_HERM,X)\n")
   print("Solve herm(A) X = I \n")
   vsip.lusol(ludC,vsip.VSIP_MAT_HERM,IC)
   vsip.lusol(ludG,vsip.VSIP_MAT_HERM,IG)
   print("for compact case X = \n");VU.mprint(IC,'%8.4f')
   print("for general case X = \n");VU.mprint(IG,'%8.4f')
   chk = 0
   for i in range(7):
       for j in range(7):
         chk += cmag(p,csub(p,vsip.get(IC,(i,j)),vsip.get(IG,(i,j))))
         chk += cmag(p,csub(p,vsip.get(IC,(i,j)),vsip.get(IG,(i,j))))
   if chk > .01:
       print("error\n") 
   else: 
       print("agree\n")
   vsip.prod(AH,IC,B)
   chk = 0
   for i in range(7):
       for j in range(7):
           chk += cmag(p,csub(p,vsip.get(B,(i,j)),cmplx(p,Ident[i][j],0.0)))
   vsip.prod(AH,IG,B)
   for i in range(7):
       for j in range(7):
           chk += cmag(p,csub(p,vsip.get(B,(i,j)),cmplx(p,Ident[i][j],0.0)))
   print("mprod(trans(A),X) = \n"); VU.mprint(B,'%8.3f')
   if chk > .01:
       print("error\n") 
   else: 
       print("correct\n")
   # check case A X = B for VSIP_MAT_NTRANS
   print("check A X = Y; VSIP_MAT_NTRANS\n")
   print("Y = \n");VU.mprint(X,"%8.4f")
   vsip.lusol(ludC,vsip.VSIP_MAT_NTRANS,X)
   print("X = \n"); VU.mprint(X,"%8.4f")
   vsip.prod(A,X,Y)
   print(" Y = A X\n");VU.mprint(Y,"%8.4f")
   chk = 0;
   for i in range(7):
       for j in range(3):
           chk += cmag(p,csub(p,vsip.get(Y,(i,j)),cmplx(p,ydata_r[i][j],ydata_i[i][j])))
   if (chk > .01):
       print("error\n") 
   else: 
       print("agree\n")

   for i in range(7):
       for j in range(3):
          vsip.put(X,(i,j),cmplx(p,ydata_r[i][j],ydata_i[i][j]))
   print("Y = \n");VU.mprint(X,'%8.4f')
   vsip.lusol(ludG,vsip.VSIP_MAT_HERM,X)
   vsip.prod(AH,X,Y)
   print("X = \n");VU.mprint(X,'%8.4f')
   print("Y = trans(A) X\n");VU.mprint(Y,'%8.4f')
   chk = 0
   for i in range(7):
       for j in range(3):
           chk += cmag(p,csub(p,vsip.get(Y,(i,j)),cmplx(p,ydata_r[i][j],ydata_i[i][j])))
   if (chk > .02):
       print("error\n") 
   else: 
       print("agree\n")
   vsip.destroy(AC)
   vsip.destroy(AG)
   vsip.destroy(IC)
   vsip.destroy(IG)
   vsip.destroy(B)
   vsip.destroy(A)
   vsip.destroy(X)
   vsip.destroy(Y)
   vsip.allDestroy(AH)
   vsip.destroy(ludC)
   vsip.destroy(ludG)

vsip_init(None)
lud('_f')
lud('_d')
clud('_f')
clud('_d')
vsip_finalize(None)
