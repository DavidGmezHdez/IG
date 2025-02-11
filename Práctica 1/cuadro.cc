#include "cuadro.h"


Cuadro::Cuadro(float lado){
// Vertices
    Tupla3f v0(-lado/2,lado/2,0.0),  v1(-lado/2,-lado/2,0.0),  v2(lado/2,-lado/2,0.0),  v3(lado/2,lado/2,0.0);
   
   v.push_back(v0);
   v.push_back(v1);
   v.push_back(v2);
   v.push_back(v3);

   // Triangulos
   Tupla3i  f0(0,1,3), f1(1,2,3);

   f.push_back(f0);
   f.push_back(f1);
}

void Cuadro::calcularCoordenadas(){
    ct.resize(4);
    ct[0] = {0,0};
    ct[1] = {0,1};
    ct[2] = {1,1};
    ct[3] = {1,0};
}