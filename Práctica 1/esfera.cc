#include "esfera.h"

Esfera::Esfera(const int num_vert_perfil, const int num_instancias_perf, const float radio){
    std::vector<Tupla3f> perfil;
    perfil.resize(num_vert_perfil);

    for(int i = 0;i<num_vert_perfil;i++){
        Tupla3f aux(radio * cos((PI/2) + ((2*PI/2)*i)/num_vert_perfil), radio * sin((PI/2) + ((2*PI/2)*i)/num_vert_perfil) , 0);
        perfil[i] = aux;
    }

    crearMalla(perfil,num_instancias_perf,true,true);
}