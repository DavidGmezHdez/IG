#include "cono.h"

Cono::Cono(const int num_vert_perfil, const int num_instancias_perf, const float altura, const float radio){
    std::vector<Tupla3f> perfil;
    perfil.resize(num_vert_perfil);
    float distanciaPuntosY = altura/num_vert_perfil;
    float distanciaPuntosX = radio/num_vert_perfil;

    for(int i = num_instancias_perf-1,j=0; i>=0; --i,++j){
        Tupla3f aux(j * distanciaPuntosX,i * distanciaPuntosY,0);
        perfil[j] = aux;
    }
    crearMalla(perfil,num_instancias_perf,true,true);
}