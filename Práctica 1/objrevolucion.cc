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
// *****************************************************************************

ObjRevolucion::ObjRevolucion() {}

ObjRevolucion::ObjRevolucion(const std::string & archivo, int num_instancias, bool tapa_sup, bool tapa_inf) {
   std::vector<Tupla3f> perfil_original;
   ply::read_vertices(archivo,perfil_original);
   crearMalla(perfil_original,num_instancias,tapa_sup,tapa_inf);
   
}

// *****************************************************************************
// objeto de revolución obtenido a partir de un perfil (en un vector de puntos)
// *****************************************************************************
 
ObjRevolucion::ObjRevolucion(std::vector<Tupla3f> archivo, int num_instancias, bool tapa_sup, bool tapa_inf) {
   crearMalla(archivo,num_instancias,tapa_sup,tapa_inf);
}

// *****************************************************************************
// Creación de los puntos
// *****************************************************************************

void ObjRevolucion::crearPuntos(std::vector<Tupla3f> perfil_original, int num_instancias,bool tapaSup, bool hayTapaSup, bool tapaInf, bool hayTapaInf){
   this->v.clear();
   Tupla3f aux, TuplatapaSup,TuplatapaInf;

   if(tapaInf && hayTapaSup)
      tapaInf = this->sacarTapaInf(perfil_original);

   if(tapaSup && hayTapaSup)
      tapaSup = this->sacarTapaSup(perfil_original);
   

   for(int i = 0;i<num_instancias;i++){
      for(int j=0;j<perfil_original.size();j++){
         aux(1) = perfil_original[j](1);
         aux(2) = cos((2*PI*i)/num_instancias) * perfil_original[j](0);
         aux(0) = sin((2*PI*i)/num_instancias) * perfil_original[j](0);
         this->v.push_back(aux);
      }
   }
   
   if(tapaInf && hayTapaInf)
      this->v.push_back(TuplatapaInf);

   if(tapaSup && hayTapaSup)
      this->v.push_back(TuplatapaSup);
   
}


// *****************************************************************************
// objeto de revolución obtenido a partir de un perfil (en un vector de puntos dado en sentido contrario)
// *****************************************************************************

void ObjRevolucion::crearPuntosReversos(std::vector<Tupla3f> perfil_original, int num_instancias){
   this->v.clear();
   Tupla3f aux;
   for(int i=0,j=perfil_original.size();i<perfil_original.size();i++,j--){
      perfil_original[i] = perfil_original[j];
   }
}

// *****************************************************************************
// Creacion de los triángulos
// *****************************************************************************

void ObjRevolucion::crearTriangulos(std::vector<Tupla3f> perfil_original, int num_instancias){
   this->f.clear();
   int a,b;
   for (int i=0;i<num_instancias;i++){
      for(int j=0;j<perfil_original.size()-1;j++){
         a = perfil_original.size() * i + j;
         b = perfil_original.size()*((i+1)%num_instancias) + j;
         Tupla3i aux1(a,b,b+1),aux2(a,b+1,a+1);
         this->f.push_back(aux1);
         this->f.push_back(aux2);
      }
   }
}

// *****************************************************************************
// Función que busca la tapa superior
// *****************************************************************************

bool ObjRevolucion::buscarTapaSup(std::vector<Tupla3f> perfil_original){
   int tamanio = perfil_original.size();
   return (perfil_original[0](0) == 0 && perfil_original[0](2) == 0);
}

// *****************************************************************************
// Función que busca la tapa inferior
// *****************************************************************************

bool ObjRevolucion::buscarTapaInf(std::vector<Tupla3f> perfil_original){
   int tamanio = perfil_original.size();
   return (perfil_original[tamanio](0) == 0 && perfil_original[tamanio](2) == 0);
}

// *****************************************************************************
// Función que devuelve el polo norte
// *****************************************************************************

Tupla3f ObjRevolucion::sacarTapaSup(std::vector<Tupla3f> perfil_original){
   Tupla3f tapaSup = perfil_original[0];
   perfil_original.erase(perfil_original.begin());
   return tapaSup;
}

// *****************************************************************************
// Función que devuelve el polo sur
// *****************************************************************************

Tupla3f ObjRevolucion::sacarTapaInf(std::vector<Tupla3f> perfil_original){
   Tupla3f tapaInf = perfil_original[perfil_original.size()];
   perfil_original.pop_back();
   return tapaInf;
}

// *****************************************************************************
// Función que crea los triángulos de la tapa superior
// *****************************************************************************

void ObjRevolucion::crearTapaSup(std::vector<Tupla3f> perfil_original, int num_instancias){
   int a,b;
   for (int i=0;i<num_instancias;i++){
         Tupla3i aux(perfil_original.size()*num_instancias + 1,perfil_original.size()*(((i+1)%num_instancias) + 1),perfil_original.size()*(i+1)-1);
         this->f.push_back(aux);
   }
}

// *****************************************************************************
// Función que crea los triángulos de la tapa inferior
// *****************************************************************************

void ObjRevolucion::crearTapaInf(std::vector<Tupla3f> perfil_original, int num_instancias){
   std::cout<<"Hola";
}

// *****************************************************************************
// Función principal que crea la malla del objeto
// *****************************************************************************

void ObjRevolucion::crearMalla(std::vector<Tupla3f> perfil_original, int num_instancias, bool tapa_sup, bool tapa_inf) {
   bool hayTapa_inf = this->buscarTapaInf(perfil_original);
   bool hayTapa_sup = this->buscarTapaSup(perfil_original);
   
   if(perfil_original[0](1) < perfil_original[perfil_original.size()](1))
      this->crearPuntosReversos(perfil_original,num_instancias);

   this->crearPuntos(perfil_original,num_instancias,tapa_sup,hayTapa_sup,tapa_inf,hayTapa_inf);

   this->crearTriangulos(perfil_original,num_instancias);
   
   if(tapa_sup && hayTapa_sup)
      this->crearTapaSup(perfil_original,num_instancias);

   if(tapa_inf && hayTapa_inf)
      this->crearTapaInf(perfil_original,num_instancias);
      
}
