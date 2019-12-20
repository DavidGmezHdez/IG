#include "semiesfera.h"

Semiesfera::Semiesfera(const int num_vert_perfil, const int num_instancias_perf, const float radio){
    std::vector<Tupla3f> perfil;

    for(int i = 0;i<num_vert_perfil;i++){
        Tupla3f aux;
        aux(1) = cos((PI/2) + i*PI/num_vert_perfil) * radio;
        aux(0) = sin((PI/2) + i*PI/num_vert_perfil) * radio;
        aux(2) = 0.0;

        perfil.push_back(aux);
    }
    crearMalla(perfil,num_instancias_perf,true,true);
}


void Semiesfera::crearTriangulos(std::vector<Tupla3f> perfil_original,int num_instancias){
    this->f.clear();
   int a,b;
   for (int i=0;i<num_instancias;i++){
      for(int j=0;j<perfil_original.size()-1;j++){
         a = perfil_original.size()* i + j;
         b = perfil_original.size()*((i+1)%num_instancias) + j;
         Tupla3i aux1(b+1,b,a),aux2(a+1,b+1,a);
         this->f.push_back(aux1);
         this->f.push_back(aux2);
      }
   }
}