#include "cilindro.h"

Cilindro::Cilindro(const int num_vert_perfil, const int num_instancias_perf, const float altura, const float radio){
    std::vector<Tupla3f> perfil;
    perfil.reserve(num_vert_perfil);
    Tupla3f p1(radio,altura/2,0),p2(radio,altura/4,0),p3(radio,0,0),p4(radio,-altura/4,0),p5(radio,-altura/2,0);
    perfil.push_back(p1);
    perfil.push_back(p2);
    perfil.push_back(p3);
    perfil.push_back(p4);
    perfil.push_back(p5);
    ObjRevolucion(perfil,num_instancias_perf,true,true);
}