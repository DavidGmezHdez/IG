#include "aux.h"
#include "objrevolucion.h"



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

void ObjRevolucion::crearPuntos(std::vector<Tupla3f> perfil_original,int num_instancias,bool tapaSup,bool tapaInf){
   this->v.clear();  
   Tupla3f aux, TuplatapaSup,TuplatapaInf;

   if(tapaSup){
         if(buscarTapaSup(perfil_original))
            TuplatapaSup = sacarTapaSup(perfil_original);
         else
            TuplatapaSup(0) = 0; TuplatapaSup(2) = 0; TuplatapaSup(1) = perfil_original[0](1);
      }
   
   if(tapaInf){
         if(buscarTapaInf(perfil_original))
            TuplatapaInf = sacarTapaInf(perfil_original);
         else
            TuplatapaInf(0) = 0; TuplatapaInf(2) = 0; TuplatapaInf(1) = perfil_original[perfil_original.size()-1](1);
      }

      for(int i = 0;i<num_instancias;i++){
         for(int j=0;j<perfil_original.size();j++){
            aux(0) = cos((2*PI*i)/num_instancias) * perfil_original[j](0);
            aux(1) = perfil_original[j](1);
            aux(2) = sin((2*PI*i)/num_instancias) * perfil_original[j](0);
            v.push_back(aux);
         }
      }

      v.push_back(TuplatapaSup);
      v.push_back(TuplatapaInf);
      
       
}


// *****************************************************************************
// objeto de revolución obtenido a partir de un perfil (en un vector de puntos dado en sentido contrario)
// *****************************************************************************

std::vector<Tupla3f> ObjRevolucion::crearPuntosReversos(std::vector<Tupla3f> perfil_original){
   std::vector<Tupla3f> reverso, aux = perfil_original;
   reverso.reserve(perfil_original.size());

   for(int i=0; i < perfil_original.size(); i++){
      reverso.push_back(aux.back());
      aux.pop_back();
   }

   return reverso;
}

// *****************************************************************************
// Creacion de los triángulos
// *****************************************************************************

void ObjRevolucion::crearTriangulos(std::vector<Tupla3f> perfil_original,int num_instancias){
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

// *****************************************************************************
// Función que busca la tapa superior
// *****************************************************************************

bool ObjRevolucion::buscarTapaSup(std::vector<Tupla3f> perfil_original){
   int tamanio = perfil_original.size();
   return perfil_original[0](0) == 0 && perfil_original[0](2) == 0;
}


// *****************************************************************************
// Función que busca la tapa inferior
// *****************************************************************************

bool ObjRevolucion::buscarTapaInf(std::vector<Tupla3f> perfil_original){
   int tamanio = perfil_original.size();
   return perfil_original[tamanio-1](0) == 0 && perfil_original[tamanio-1](2) == 0;
}


// *****************************************************************************
// Función que devuelve el polo norte
// *****************************************************************************

Tupla3f ObjRevolucion::sacarTapaSup(std::vector<Tupla3f> &perfil_original){
   Tupla3f tapaSup = perfil_original[0];
   perfil_original.erase(perfil_original.begin());
   return tapaSup;
}

// *****************************************************************************
// Función que devuelve el polo sur
// *****************************************************************************

Tupla3f ObjRevolucion::sacarTapaInf(std::vector<Tupla3f> &perfil_original){
   Tupla3f tapaInf = perfil_original[perfil_original.size()-1];
   perfil_original.pop_back();
   return tapaInf;
}


// *****************************************************************************
// Función que crea los triángulos de la tapa superior
// *****************************************************************************

void ObjRevolucion::crearTapaSup(std::vector<Tupla3f> &perfil_original,int &num_instancias){
   for(int i=0;i<num_instancias;i++){
      Tupla3i aux(perfil_original.size()*((i+1)%num_instancias),perfil_original.size()*i,num_instancias*perfil_original.size());
      this->f.push_back(aux);
   }
}

// *****************************************************************************
// Función que crea los triángulos de la tapa inferior
// *****************************************************************************

void ObjRevolucion::crearTapaInf(std::vector<Tupla3f> &perfil_original,int &num_instancias){
   for (int i=0;i<num_instancias;i++){
         Tupla3i aux(num_instancias*perfil_original.size()+1,perfil_original.size()*(i+1)-1,perfil_original.size()*(((i+1)%num_instancias)+1)-1);
         this->f.push_back(aux);
   }
}


// *****************************************************************************
// Función que activa o no las tapas
// *****************************************************************************

void ObjRevolucion::switchTapas(bool &tapas){
   std::vector<Tupla3f> auxv = v;
   v = vnotapas;
   vnotapas = auxv;

   std::vector<Tupla3i> auxf = f;
   f = fnotapas;
   fnotapas = auxf;

   tapas = !tapas;
}


void ObjRevolucion::calcularCoordenadas(std::vector<Tupla3f> perfil_original, int num_instancias){
   calcularPerfil(perfil_original);
   std::vector<Tupla2f>aux;

   for(float i = 0;i<num_instancias;i++){
      for(float j=0;j<perfil_original.size();j++){
         aux.push_back({i/num_instancias,(float)distancias[j]/distancias[perfil_original.size()-1]});
      }
   }

   for(int i = aux.size()-1;i>0;i--)
      ct.push_back(aux[i]);
      
}

double ObjRevolucion::calcularVertices(Tupla3f a, Tupla3f b){
   return sqrt((pow(a(0)-b(0),2)) + (pow(a(1)-b(1),2)) + (pow(a(2)-b(2),2)));
}

void ObjRevolucion::calcularPerfil(std::vector<Tupla3f> perfil_original){
   distancias.clear();
   distancias.resize(perfil_original.size()+1);
   distancias[0] = 0;

   for(int i= 1;i<perfil_original.size();i++)
      distancias[i] = distancias[i-1] + calcularVertices(perfil_original[i-1],perfil_original[i]);
      
}

// *****************************************************************************
// Función principal que crea la malla del objeto
// *****************************************************************************

void ObjRevolucion::crearMalla(std::vector<Tupla3f> perfil_original, int num_instancias, bool tapa_sup, bool tapa_inf) {
   Tupla3f tapaInf, tapaSup;
   N = num_instancias, M = perfil_original.size();
   if(perfil_original[0](1) < perfil_original[perfil_original.size()-1](1))
      perfil_original = crearPuntosReversos(perfil_original);
   
   this->crearPuntos(perfil_original,num_instancias,tapa_sup,tapa_inf);

   this->crearTriangulos(perfil_original,num_instancias);
   
   this->vnotapas = v;
   this->fnotapas = f;

   if(tapa_sup)
      this->crearTapaSup(perfil_original,num_instancias);
   if(tapa_inf)
      this->crearTapaInf(perfil_original,num_instancias);
   
   if(ct.empty())
      calcularCoordenadas(perfil_original,num_instancias);
      
}