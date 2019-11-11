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
//#include "material.h"
#include <string.h>

// *****************************************************************************
//
// clase para objetos 3D (mallas indexadas)
//
// *****************************************************************************

class Malla3D
{
   public:

   // dibuja el objeto en modo inmediato
   void draw_ModoInmediato(std::vector<Tupla3f> vertices,  std::vector<Tupla3i> caras);

   // Crea VBO
   GLuint crearVBO(GLuint tipo_vbo, GLuint tamanio_bytes, GLvoid * puntero_ram);

   // dibuja el objeto en modo diferido (usando VBOs)
   void draw_ModoDiferido(std::vector<Tupla3f> vertices,  std::vector<Tupla3i> caras);

   //funcion que redibuja el objeto con el modo ajedrez
   void draw_ajedrezInmediato(std::vector<Tupla3f> vertices,  std::vector<Tupla3i> caras);
   
   // función que redibuja el objeto
   // está función llama a 'draw_ModoInmediato' (modo inmediato)
   // o bien a 'draw_ModoDiferido' (modo diferido, VBOs)
   void draw(bool modoDibujado, bool chess,bool tapas);

   void crearAjedrez();

   void setColor(float R, float G, float B);

   void calcularNormalesCaras();

   void calcularNormalesVertices();

   void calcularNormales();

   //void setMaterial(Material mat);
   
   protected:

   void calcular_normales() ; // calcula tabla de normales de vértices (práctica 3)

   std::vector<Tupla3f> v,vtapas,nc,nv ;   // tabla de coordenadas de vértices (una tupla por vértice, con tres floats)
   std::vector<Tupla3i> f,ftapas,impares, pares; // una terna de 3 enteros por cada cara o triángulo
   std::vector<Tupla3f> c, cimpares, cpares; //una terna 3 float por cada color
   bool ajedrez,tapas;
   GLuint vbo_v = 0,vbo_f= 0, vbo_c = 0;
   //Material m;

} ;

#endif
