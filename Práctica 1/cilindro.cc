#include "cilindro.h"

Cilindro::Cilindro(const int num_vert_perfil, const int num_instancias_perf, const float altura, const float radio){
    std::vector<Tupla3f> perfil;
    perfil.resize(num_vert_perfil);
    float distanciaPuntos = altura / num_instancias_perf;

    Tupla3f aux;
    int contador = 0;
    for(int i = 0;i<num_vert_perfil;i++){
        aux(0) = radio;
        aux(1) = i*distanciaPuntos;
        aux(2) = 0;
        perfil[i] = aux;
    }

    crearMalla(perfil,num_instancias_perf,true,true);
}