#include "skybox.h"

Skybox::Skybox(float lado){
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
   Tupla3i t1(2, 1, 0), t2(2, 0, 3);
   f.push_back(t1);
   f.push_back(t2);

   // Cara final
   Tupla3i t3(5, 4, 6), t4(7, 6, 4);
   f.push_back(t3);
   f.push_back(t4);

   // Cara derecha
   Tupla3i t5(1, 2, 7), t6(1, 7, 4);
   f.push_back(t5);
   f.push_back(t6);

   // Cara izquierda
   Tupla3i t7(3, 0, 6), t8(0, 5, 6);
   f.push_back(t7);
   f.push_back(t8);

   // Cara de arriba
   Tupla3i t9(3, 6, 7), t10(3, 7, 2);
   f.push_back(t9);
   f.push_back(t10);

   // Cara de abajo
   Tupla3i t11(5, 1, 4), t12(1, 5, 0);
   f.push_back(t11);
   f.push_back(t12);
}

void Skybox::calcularCoordenadas(){
    Tupla2f c0(0,0),c1(1.0,0.0),c2(1.0,1.0),c3(0.0,1.0),c4(0,0),c5(1.0,0.0),c6(1.0,1.0),c7(0.0,1.0);
    ct.resize(8);
    ct[0] = c0;
    ct[1] = c2;
    ct[2] = c1;
    ct[3] = c3;
    ct[4] = c7;
    ct[5] = c6;
    ct[6] = c5;
    ct[7] = c4;
    
}
