// Strassen Multiplication
// G&VL Alg 1.3.1
#include<cstdlib>
#include<vsip/initfin.hpp>
#include<vsip/vector.hpp>
#include<vsip/matrix.hpp>
#include<vsip/math.hpp>

vsip::Matrix<vsip::scalar_f>
strass( vsip::Matrix<vsip::scalar_f>A, vsip::Matrix<vsip::scalar_f>B,
    vsip::length_type n, vsip::length_type n_min) {
if(n <= n_min){
   return (vsip::prod(A,B));
} else {
   vsip::Matrix<vsip::scalar_f> C(n,n);
   vsip::length_type m = n/2;
   vsip::Domain<1> u(0,1,m);
   vsip::Domain<1> v(m,1,n);
   vsip::Domain<2> uu(u,u);
   vsip::Domain<2> vv(v,v);
   vsip::Domain<2> vu(v,u);
   vsip::Domain<2> uv(u,v);
   vsip::Matrix<vsip::scalar_f>::subview_type Auu(A(uu));
   vsip::Matrix<vsip::scalar_f>::subview_type Buu(B(uu));
   vsip::Matrix<vsip::scalar_f>::subview_type Avv(A(vv));
   vsip::Matrix<vsip::scalar_f>::subview_type Bvv(B(vv));
   vsip::Matrix<vsip::scalar_f>::subview_type Avu(A(vu));
   vsip::Matrix<vsip::scalar_f>::subview_type Auv(A(uv));
   vsip::Matrix<vsip::scalar_f>::subview_type Bvu(B(vu));
   vsip::Matrix<vsip::scalar_f>::subview_type Buv(B(uv));
   vsip::Matrix<vsip::scalar_f> P1 = strass(Auu + Avv, Buu + Bvv, m, n_min);
   vsip::Matrix<vsip::scalar_f> P2 = strass(Avu + Avv, Buu, m, n_min);
   vsip::Matrix<vsip::scalar_f> P3 = strass(Auu , Buv - Bvv, m, n_min);
   vsip::Matrix<vsip::scalar_f> P4 = strass(Avv , Bvu - Buu, m, n_min);
   vsip::Matrix<vsip::scalar_f> P5 = strass(Auu + Auv, Bvv, m, n_min);
   vsip::Matrix<vsip::scalar_f> P6 = strass(Avu - Auu, Buu + Buv, m, n_min);
   vsip::Matrix<vsip::scalar_f> P7 = strass(Auv - Avv, Bvu + Bvv, m, n_min);
   C(uu) = P1 + P4 - P5 + P7;
   C(uv) = P3 + P5;
   C(vu) = P2 + P4;
   C(vv) = P1 + P3 - P2 + P6;
   return C;
   }
}
    


