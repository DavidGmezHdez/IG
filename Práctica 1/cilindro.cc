#include "cilindro.h"

Cilindro::Cilindro(const int num_vert_perfil, const int num_instancias_perf, const float altura, const float radio){
    std::vector<Tupla3f> perfil;
    perfil.resize(num_vert_perfil);
    float distanciaPuntos = num_vert_perfil / altura;

    Tupla3f aux;
    int contador = 0;
    for(int i = 0;i<num_vert_perfil;i++){
        aux(0) = radio;
        aux(1) = contador;
        aux(2) = 0;
        perfil[i] = aux;
        contador+=distanciaPuntos;
    }

    crearMalla(perfil,num_instancias_perf,true,true);
}