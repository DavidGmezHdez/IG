// #############################################################################
//
// Informática Gráfica (Grado Informática)
//
// Archivo: Malla3D.h
// -- declaraciones de clase Malla3D (mallas indexadas) y derivados
//
// #############################################################################

#ifndef MALLA3D_H_INCLUDED
#define MALLA3D_H_INCLUDED

#include "aux.h"
#include "material.h"
#include "textura.h"

// *****************************************************************************
//
// clase para objetos 3D (mallas indexadas)
//
// *****************************************************************************
using namespace std;

class Malla3D
{
   public:

   // dibuja el objeto en modo inmediato
   void draw_ModoInmediato(int modo);

   // Crea VBO
   GLuint crearVBO(GLuint tipo_vbo, GLuint tamanio_bytes, GLvoid * puntero_ram);

   // dibuja el objeto en modo diferido (usando VBOs)
   void draw_ModoDiferido(int modo);

   //funcion que redibuja el objeto con el modo ajedrez
   void draw_ajedrezInmediato();
   
   // función que redibuja el objeto
   // está función llama a 'draw_ModoInmediato' (modo inmediato)
   // o bien a 'draw_ModoDiferido' (modo diferido, VBOs)
   void draw(bool modoDibujado,bool points,bool lines,bool fill, bool chess);

   void setColor(float R, float G, float B);

   void calcularNormalesCaras();

   void calcularNormalesVertices();

   void calcularNormales();

   Tupla3f getPosicion(){return posicion;};

   Tupla3f getColor(){return color;};

   void setMaterial(Material mat);

   void setTextura(Textura tex);

   void setPosicion(Tupla3i pos);

   inline void setCoordenadasTextura(std::vector<Tupla2f> texturas){ct = texturas;};

   virtual void calcularCoordenadas(){};

   inline bool getSuperpuesto(){return superpuesto;};

   inline void setSuperpuesto(bool sup){superpuesto = sup;};
   
   protected:

   void calcular_normales() ; // calcula tabla de normales de vértices (práctica 3)

   

   std::vector<Tupla3f> v,vnotapas,nc,nv;   // tabla de coordenadas de vértices (una tupla por vértice, con tres floats)
   std::vector<Tupla3i> f,fnotapas,impares, pares; // una terna de 3 enteros por cada cara o triángulo
   std::vector<Tupla3f> c, cimpares, cpares,cp,cl; //una terna 3 float por cada color
   std::vector<Tupla2f> ct;                        //Terna de 2 floats para textura 
   Tupla3f posicion;                               //Terna de 3 floats para saber la posicion
   Tupla3f color;                                  //Terna de 4 floats para saber el color
   bool puntos,lineas,solido,ajedrez;
   GLuint vbo_v = 0,vbo_f= 0, vbo_c = 0,vbo_cp = 0,vbo_cl = 0, vbo_nv = 0,vbo_ct = 0;
   Material *m = nullptr;
   Textura *t = nullptr;
   bool superpuesto = false;
} ;

#endif
