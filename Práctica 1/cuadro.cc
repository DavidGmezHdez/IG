#include "cuadro.h"


Cuadro::Cuadro(){

    Tupla3f v0(0.0,0.0,0.0), v1(100.0, 0.0, 0.0), v2(0.0, 100.0, 0.0), v3(100.0, 100.0, 0.0);
   
    v.push_back(v0);
    v.push_back(v1);
    v.push_back(v2);
    v.push_back(v3);

    Tupla3i f0(2,0,1),f1(1,3,2);
    f.push_back(f0);
    f.push_back(f1);

    Tupla3f c0(1.0, 0.0, 0.0), c1(1.0, 0.0, 0.0), c2(1.0, 0.0, 0.0), c3(1.0, 0.0, 0.0);
    c.push_back(c0);
    c.push_back(c1);
    c.push_back(c2);
    c.push_back(c3);

}

void Cuadro::calcularCoordenadas(){   
    Tupla2f c0(0,0),c1(1.0,0.0),c2(0.0,1.0),c3(1.0,1.0);
    ct.push_back(c0); ct.push_back(c1); ct.push_back(c2); ct.push_back(c3);
}