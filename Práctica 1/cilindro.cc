#include "cilindro.h"

Cilindro::Cilindro(const int num_vert_perfil, const int num_instancias_perf, const float altura, const float radio){
    std::vector<Tupla3f> perfil;
    perfil.resize(num_vert_perfil);
    float distanciaPuntos = altura / num_instancias_perf;

    for(int i = 0;i<num_vert_perfil;i++){
        Tupla3f aux(radio,i*distanciaPuntos,0);
        perfil[i] = aux;
    }

    crearMalla(perfil,num_instancias_perf,true,true);
}