#include "aux.h"
#include "malla.h"
#include "cubo.h"
Cubo::Cubo(float lado)
{
  
   // inicializar la tabla de vértices
   // Primer cuadrado
   Tupla3f v0(-lado, -lado, lado), v1(lado, -lado, lado), v2(lado, lado, lado), v3(-lado, lado, lado);
   
   v.push_back(v0);
   v.push_back(v1);
   v.push_back(v2);
   v.push_back(v3);

   // Segundo cuadrado
   Tupla3f v4(lado, -lado, -lado), v5(-lado, -lado, -lado),v6(-lado, lado, -lado),v7(lado, lado, -lado);
   v.push_back(v4);
   v.push_back(v5);
   v.push_back(v6);
   v.push_back(v7);

   // inicializar la tabla de caras o triángulos:
   // Cara frontal
   Tupla3i t1(0, 1, 2), t2(0, 2, 3);
   f.push_back(t1);
   f.push_back(t2);

   // Cara final
   Tupla3i t3(4, 5, 6), t4(4, 6, 7);
   f.push_back(t3);
   f.push_back(t4);

   // Cara derecha
   Tupla3i t5(1, 7, 2), t6(1, 4, 7);
   f.push_back(t5);
   f.push_back(t6);

   // Cara izquierda
   Tupla3i t7(0, 3, 6), t8(0, 6, 5);
   f.push_back(t7);
   f.push_back(t8);

   // Cara de arriba
   Tupla3i t9(3, 7, 6), t10(3, 2, 7);
   f.push_back(t9);
   f.push_back(t10);

   // Cara de abajo
   Tupla3i t11(1, 5, 4), t12(1, 0, 5);
   f.push_back(t11);
   f.push_back(t12);

}

void Cubo::calcularCoordenadas(){
    Tupla2f c0(0,0),c1(1.0,0.0),c2(0.0,1.0),c3(1.0,1.0),c4(0,0),c5(1.0,0.0),c6(0.0,1.0),c7(1.0,1.0) ;
    ct.push_back(c0); ct.push_back(c1); ct.push_back(c2); ct.push_back(c3);
    ct.push_back(c4); ct.push_back(c5); ct.push_back(c6); ct.push_back(c7);
}





