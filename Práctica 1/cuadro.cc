#include "cuadro.h"


Cuadro::Cuadro(){

    Tupla3f v0(0,0,0),v1(500,0,0), v2(500,500,0) , v3(0,500,0);
    
    v.push_back(v0);
    v.push_back(v1);
    v.push_back(v2);
    v.push_back(v3);

    Tupla3i f0(0,3,2),f1(0,2,1);
    f.push_back(f0);
    f.push_back(f1);

}