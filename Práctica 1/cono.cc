#include "cono.h"

Cono::Cono(const int num_vert_perfil, const int num_instancias_perf, const float altura, const float radio){
    std::vector<Tupla3f> perfil;
    perfil.resize(num_vert_perfil);
    float distanciaPuntosY = altura/num_vert_perfil;
    float distanciaPuntosX = radio/num_vert_perfil;

    Tupla3f aux;
    int contador = 0;
    for(int i = num_instancias_perf-1;i>=0;i--){
        aux(0) = contador * distanciaPuntosX;
        aux(1) = i*distanciaPuntosY;
        aux(2) = 0;
        perfil[i] = aux;
        contador++;
    }
    crearMalla(perfil,num_instancias_perf,true,true);
}