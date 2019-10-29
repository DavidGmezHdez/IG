#include "cilindro.h"

Cilindro::Cilindro(const int num_instancias_perf, const float altura, const float radio){
    std::vector<Tupla3f> perfil;
    Tupla3f aux1(radio,0,0),aux2(radio,altura,0);
    perfil.push_back(aux1);
    perfil.push_back(aux2);
    crearMalla(perfil,num_instancias_perf,true,true);
}