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

void ObjRevolucion::crearPuntos(bool tapaSup,bool tapaInf){
   this->v.clear();
   bool hayTapa_inf = this->buscarTapaInf();
   bool hayTapa_sup = this->buscarTapaSup();
   Tupla3f aux, TuplatapaSup,TuplatapaInf;

   for(int i = 0;i<N;i++){
      for(int j=0;j<M;j++){
         aux(1) = perfil[j](1);
         aux(2) = cos((2*PI*i)/N) * perfil[j](0);
         aux(0) = sin((2*PI*i)/N) * perfil[j](0);
         this->v.push_back(aux);
      }
   }


   if(tapaInf){
      if(hayTapa_inf)
         tapaInf = this->sacarTapaInf();
      else
         TuplatapaInf(0) = 0; TuplatapaInf(2) = 0; TuplatapaInf(1) = v[v.size()-1](1);

      this->v.push_back(TuplatapaInf);
   }

   if(tapaSup){
      if(hayTapa_sup)
         TuplatapaSup = this->sacarTapaSup();
      else
         TuplatapaSup(0) = 0; TuplatapaSup(2) = 0; TuplatapaSup(1) = v[0](1);
      
      this->v.push_back(TuplatapaSup);
   }
   
}


// *****************************************************************************
// objeto de revolución obtenido a partir de un perfil (en un vector de puntos dado en sentido contrario)
// *****************************************************************************

void ObjRevolucion::crearPuntosReversos(){
   this->v.clear();
   Tupla3f aux;
   for(int i=0,j=M;i<M;i++,j--){
      perfil[i] = perfil[j];
   }
}

// *****************************************************************************
// Creacion de los triángulos
// *****************************************************************************

void ObjRevolucion::crearTriangulos(){
   this->f.clear();
   int a,b;
   for (int i=0;i<N;i++){
      for(int j=0;j<M-1;j++){
         a = M* i + j;
         b = M*((i+1)%N) + j;
         Tupla3i aux1(a,b,b+1),aux2(a,b+1,a+1);
         this->f.push_back(aux1);
         this->f.push_back(aux2);
      }
   }
}

// *****************************************************************************
// Función que busca la tapa superior
// *****************************************************************************

bool ObjRevolucion::buscarTapaSup(){
   return perfil[0](0) == 0 && perfil[0](2) == 0;
}

// *****************************************************************************
// Función que busca la tapa inferior
// *****************************************************************************

bool ObjRevolucion::buscarTapaInf(){
   return perfil[M](0) == 0 && perfil[M](2) == 0;
}

// *****************************************************************************
// Función que devuelve el polo norte
// *****************************************************************************

Tupla3f ObjRevolucion::sacarTapaSup(){
   Tupla3f tapaSup = perfil[0];
   perfil.erase(perfil.begin());
   return tapaSup;
}

// *****************************************************************************
// Función que devuelve el polo sur
// *****************************************************************************

Tupla3f ObjRevolucion::sacarTapaInf(){
   Tupla3f tapaInf = perfil[M-1];
   perfil.pop_back();
   return tapaInf;
}

// *****************************************************************************
// Función que crea los triángulos de la tapa superior
// *****************************************************************************

void ObjRevolucion::crearTapaInf(){
   int a,b;
   for (int i=0;i<N;i++){
         Tupla3i aux(M*N+1,((i+1)%N)*M,M*i);
         this->f.push_back(aux);
   }
}

// *****************************************************************************
// Función que crea los triángulos de la tapa inferior
// *****************************************************************************

void ObjRevolucion::crearTapaSup(){
   int a,b;
   for(int i=0;i<N;i++){
      Tupla3i aux(M*N,M*(i+1)-1,M*(((i+1)%N)+1)-1);
      this->f.push_back(aux);
   }
}

void ObjRevolucion::borrarTapas(){
   for(int i=f.size();i>2*N;i--){
      f.pop_back();
   }

   v.pop_back();
   v.pop_back();

}


void ObjRevolucion::detectarTapas(){
   if (this->buscarTapaSup() && this->buscarTapaInf())
      this->borrarTapas();
   else{
      //this->crearTapaSup()
   }


}


// *****************************************************************************
// Función principal que crea la malla del objeto
// *****************************************************************************

void ObjRevolucion::crearMalla(std::vector<Tupla3f> perfil_original, int num_instancias, bool tapa_sup, bool tapa_inf) {
   for(int i=0;i<perfil_original.size();i++)
      this->perfil.push_back(perfil_original[i]);
   
   this->N = num_instancias;
   this->M = perfil.size();
   if(perfil[0](1) < perfil[M-1](1))
      this->crearPuntosReversos();
   
   this->crearPuntos(tapa_sup,tapa_inf);

   this->crearTriangulos();
   
   if(tapa_inf)
      this->crearTapaInf();

   if(tapa_sup)
      this->crearTapaSup();
   
}
