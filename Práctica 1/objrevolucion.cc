#include "aux.h"
#include "objrevolucion.h"


const float PI = 3.141592653;


// *****************************************************************************
//
// Clase ObjRevolucion (práctica 2)
//
// *****************************************************************************


// *****************************************************************************
// objeto de revolución obtenido a partir de un perfil (en un PLY)

ObjRevolucion::ObjRevolucion() {}

ObjRevolucion::ObjRevolucion(const std::string & archivo, int num_instancias, bool tapa_sup, bool tapa_inf) {
   std::vector<Tupla3f> perfil_original;
   ply::read_vertices(archivo,perfil_original);
   crearMalla(perfil_original,50,tapa_sup,tapa_inf);s
   
}

// *****************************************************************************
// objeto de revolución obtenido a partir de un perfil (en un vector de puntos)

 
ObjRevolucion::ObjRevolucion(std::vector<Tupla3f> archivo, int num_instancias, bool tapa_sup, bool tapa_inf) {
   crearMalla(archivo,num_instancias,tapa_sup,tapa_inf);
}

void ObjRevolucion::crearPuntos(std::vector<Tupla3f> perfil_original, int num_instancias){
   this->v.clear();
   Tupla3f aux;
   for(int i = 0;i<num_instancias;i++){
      for(int j=0;j<perfil_original.size();j++){
         aux(2) = cos((2*PI*i)/num_instancias) * aux(0);
         aux(0) = sin((2*PI*i)/num_instancias) * aux(0);
         this->v.push_back(aux);
      }
   }
}

void ObjRevolucion::crearTriangulos(std::vector<Tupla3f> perfil_original, int num_instancias){
   this->f.clear();
   int a,b;
   for (int i=0;i<num_instancias;i++){
      for(int j=0;j<perfil_original.size();j++){
         a = perfil_original.size() * i + j;
         b = perfil_original.size()*((i+j)%num_instancias) + j;
         Tupla3i aux1(a,b,b+1),aux2(a,b+1,a+1);
         this->f.push_back(aux1);
         this->f.push_back(aux2);
      }
   }
}

void ObjRevolucion::crearMalla(std::vector<Tupla3f> perfil_original, int num_instancias, bool tapa_sup, bool tapa_inf) {
   this->crearPuntos(perfil_original,num_instancias);
   this->crearTriangulos(perfil_original,num_instancias);
   
}
