#include "semiesfera.h"

Semiesfera::Semiesfera(const int num_vert_perfil, const int num_instancias_perf, const float radio){
    std::vector<Tupla3f> perfil;

    for(int i = 0;i<num_vert_perfil;i++){
        Tupla3f aux;
        aux(1) = sin((PI/2) + i*PI/num_vert_perfil) * radio;
        aux(0) = cos((PI/2) + i*PI/num_vert_perfil) * radio;
        aux(2) = 0.0;

        perfil.push_back(aux);
    }
    crearMalla(perfil,num_instancias_perf,true,true);
}


void Semiesfera::crearPuntos(std::vector<Tupla3f> perfil_orignal, int num_instancias,bool tapaSup, bool tapaInf){
    this->v.clear();  
   Tupla3f aux, TuplatapaSup,TuplatapaInf;

   if(tapaSup){
        TuplatapaSup(0) = 0; TuplatapaSup(2) = 0; TuplatapaSup(1) = perfil_orignal[0](1);
      }

   if(tapaInf){
        TuplatapaInf(0) = 0; TuplatapaInf(2) = 0; TuplatapaInf(1) = perfil_orignal[perfil_orignal.size()-1](1);
      }

      for(int i = 0;i<num_instancias;i++){
         for(int j=0;j<perfil_orignal.size()/2;j++){
            aux(0) = cos((2*PI*i)/num_instancias) * perfil_orignal[j](0);
            aux(1) = perfil_orignal[j](1);
            aux(2) = sin((2*PI*i)/num_instancias) * perfil_orignal[j](0);
            v.push_back(aux);
         }
      }

      v.push_back(TuplatapaSup);
      v.push_back(TuplatapaInf);
      
     
      
}

void Semiesfera::crearTriangulos(std::vector<Tupla3f> perfil_original,int num_instancias){
    this->f.clear();
   int a,b;
   for (int i=0;i<num_instancias;i++){
      for(int j=0;j<perfil_original.size()-1;j++){
         a = perfil_original.size()* i + j;
         b = perfil_original.size()*((i+1)%num_instancias) + j;
         Tupla3i aux1(a,b,b+1),aux2(a,b+1,a+1);
         this->f.push_back(aux1);
         this->f.push_back(aux2);
      }
   }
}
