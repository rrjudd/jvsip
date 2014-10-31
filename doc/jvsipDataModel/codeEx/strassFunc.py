def strass(A, B, C):
    assert 'View' in repr(A) and 'View' in repr(B) and 'View' in repr(C),\
          'Strass works with pyJvsip views'
    assert 'mview' in A.type,'strass only works with matrix views'
    assert A.type==B.type and A.type==C.type,'Matrix types must be the same'
    n=A.rowlength
    if n % 2 == 1  or n < 129:
        pjv.prod(A,B,C)
    else:
        A00 = A.cloneview; Aij = A.cloneview
        Ai0 = A.cloneview; A0j = A.cloneview
        B00 = B.cloneview; Bij = B.cloneview
        Bi0 = B.cloneview; B0j = B.cloneview
        C00 = C.cloneview; Cij = C.cloneview
        Ci0 = C.cloneview; C0j = C.cloneview
        m = n/2; i = m; j = i
        P1 = pjv.create(A.type,m,m)
        P2 = pjv.create(A.type,m,m)
        P3 = pjv.create(A.type,m,m)
        P4 = pjv.create(A.type,m,m)
        P5 = pjv.create(A.type,m,m)
        P6 = pjv.create(A.type,m,m)
        P7 = pjv.create(A.type,m,m)
        mgetsub(A,A00,0,0,1,1,m,m);mgetsub(A,A0j,0,j,1,1,m,m)
        mgetsub(A,Ai0,i,0,1,1,m,m);mgetsub(A,Aij,i,j,1,1,m,m)
        mgetsub(B,B00,0,0,1,1,m,m);mgetsub(B,B0j,0,j,1,1,m,m)
        mgetsub(B,Bi0,i,0,1,1,m,m);mgetsub(B,Bij,i,j,1,1,m,m)
        mgetsub(C,C00,0,0,1,1,m,m);mgetsub(C,C0j,0,j,1,1,m,m)
        mgetsub(C,Ci0,i,0,1,1,m,m);mgetsub(C,Cij,i,j,1,1,m,m)
        pjv.add(A00,Aij,C00); pjv.add(B00,Bij,Cij); strass(C00,Cij,P1)
        pjv.add(Ai0,Aij,C00);strass(C00,B00,P2)
        pjv.sub(B0j,Bij,C00); strass(A00,C00,P3)
        pjv.sub(Bi0,Bij,C00); strass(Aij,C00,P4)
        pjv.add(A00,A0j,C00); strass(C00,Bij,P5)
        pjv.sub(Ai0,A00,C00); pjv.add(B00,B0j,Cij); strass(C00,Cij,P6)
        pjv.sub(A0j,Aij,C00); pjv.add(Bi0,Bij,Cij); strass(C00,Cij,P7)
        pjv.add(P1,P4,C00);pjv.sub(C00,P5,C00); pjv.add(C00,P7,C00)
        pjv.add(P3,P5,C0j)
        pjv.add(P2,P4,Ci0)
        pjv.add(P1,P3,Cij); pjv.sub(Cij,P2,Cij); pjv.add(Cij,P6,Cij)
    return C

