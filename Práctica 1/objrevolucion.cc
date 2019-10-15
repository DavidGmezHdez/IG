#include "aux.h"
#include "objrevolucion.h"


const float PI = : 3.141592653;


// *****************************************************************************
//
// Clase ObjRevolucion (práctica 2)
//
// *****************************************************************************


// *****************************************************************************
// objeto de revolución obtenido a partir de un perfil (en un PLY)

ObjRevolucion::ObjRevolucion() {}

ObjRevolucion::ObjRevolucion(const std::string & archivo, int num_instancias, bool tapa_sup, bool tapa_inf) {
   
}

// *****************************************************************************
// objeto de revolución obtenido a partir de un perfil (en un vector de puntos)

 
ObjRevolucion::ObjRevolucion(std::vector<Tupla3f> archivo, int num_instancias, bool tapa_sup, bool tapa_inf) {
   this->v.clear();
   Tupla3f aux;
   for(int i = 0;i<num_instancias;i++){
      for(int j=0;j<archivo.size();j++){
         
         aux(0) = archivo[j] + ((2*PI*i)/num_instancias);
         aux(2) = archivo[j] + ((2*PI*i)/num_instancias);
         this->v.push_back(aux);
      }
   }
}

void ObjRevolucion::crearMalla(std::vector<Tupla3f> perfil_original, int num_instancias) {

}
