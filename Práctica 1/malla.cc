
#include "aux.h"
#include "malla.h"

// *****************************************************************************
//
// Clase Malla3D
//
// *****************************************************************************

// -----------------------------------------------------------------------------
// Visualización en modo inmediato con 'glDrawElements'
// -----------------------------------------------------------------------------

void Malla3D::setColor(Tupla3f color, std::vector<Tupla3f> &colores){
   for(int i=0;i<colores.size();i++){
      colores[i](0) = color(0);
      colores[i](1) = color(1);
      colores[i](2) = color(2);
   }
}


void Malla3D::draw_ModoInmediato()
{
   glEnableClientState(GL_VERTEX_ARRAY);
   glVertexPointer(3,GL_FLOAT,0,v.data());

   glEnableClientState(GL_COLOR_ARRAY);

   Tupla3f color(1.0,0.0,0.0);
   if(c.empty()){
      c.resize(v.size());
      setColor(color,c);
   }

   glColorPointer(3, GL_FLOAT, 0, c.data());
   glShadeModel(GL_FLAT);
   glDrawElements(GL_TRIANGLES, 3*f.size(),GL_UNSIGNED_INT,f.data());
   glDisableClientState(GL_COLOR_ARRAY);
   glDisableClientState( GL_VERTEX_ARRAY );
}

// -----------------------------------------------------------------------------
// Visualización en modo diferido con 'glDrawElements' (usando VBOs)
// -----------------------------------------------------------------------------

GLuint Malla3D::crearVBO(GLuint tipo_vbo, GLuint tamanio_bytes, GLvoid * puntero_ram){
   GLuint id_vbo;
   glGenBuffers( 1, & id_vbo );
   glBindBuffer( tipo_vbo, id_vbo );
   glBufferData( tipo_vbo, tamanio_bytes, puntero_ram, GL_STATIC_DRAW );
   glBindBuffer( tipo_vbo, 0 );
   return id_vbo ;
}

// -----------------------------------------------------------------------------

void Malla3D::draw_ModoDiferido()
{
   if(vbo_v == 0 && vbo_f==0){
      vbo_v = crearVBO(GL_ARRAY_BUFFER,3*sizeof(float)*v.size(),v.data());
      vbo_f = crearVBO(GL_ELEMENT_ARRAY_BUFFER,3*sizeof(int)*f.size(),f.data());  
   }
   glBindBuffer(GL_ARRAY_BUFFER,vbo_v); 
   glVertexPointer(3,GL_FLOAT,0,0);
   glBindBuffer(GL_ARRAY_BUFFER,0); 
   glEnableClientState(GL_VERTEX_ARRAY);
   glEnableClientState(GL_COLOR_ARRAY);
   Tupla3f color(1.0,0.0,0.0);
   if(c.empty()){
      c.resize(v.size());
      setColor(color,c);
   }
   glColorPointer(3, GL_FLOAT, 0, c.data());
   glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, vbo_f);
   glDrawElements(GL_TRIANGLES,3*f.size(),GL_UNSIGNED_INT,f.data());
   glBindBuffer(GL_ELEMENT_ARRAY_BUFFER,0);
   glDisableClientState(GL_COLOR_ARRAY);
   glDisableClientState(GL_VERTEX_ARRAY); 
}

// -----------------------------------------------------------------------------
// Visualización en modo inmediato con el modo ajedrez
// -----------------------------------------------------------------------------

void Malla3D::draw_ajedrezInmediato(){
   glEnableClientState(GL_VERTEX_ARRAY);
   glVertexPointer(3,GL_FLOAT,0,v.data());
   glEnableClientState(GL_COLOR_ARRAY);
   
   for(int i=0;i<f.size();i+=2){
      impares.push_back(f[i]);
      pares.push_back(f[i+1]);
   }

   glShadeModel(GL_FLAT);

   cimpares.resize(c.size());
   cpares.resize(c.size());

   for(int i=0;i<cpares.size();++i){
      cpares[i][0] = (200.0);
      cpares[i][1] = (0.0);
      cpares[i][2] = (0.0);
      cimpares[i](0) = (0.0);
      cimpares[i](1) = (0.0);
      cimpares[i](2) = (0.0);
   }
   
   glColorPointer(3, GL_FLOAT, 0, cpares.data());
   glDrawElements(GL_TRIANGLES, 3*pares.size(),GL_UNSIGNED_INT,pares.data());

   glColorPointer(3, GL_FLOAT, 0, cimpares.data());
   glDrawElements(GL_TRIANGLES, 3*impares.size(),GL_UNSIGNED_INT,impares.data());

   glDisableClientState(GL_COLOR_ARRAY);
   glDisableClientState( GL_VERTEX_ARRAY );
   
}

// -----------------------------------------------------------------------------
// Función de visualización de la malla,
// puede llamar a  draw_ModoInmediato o bien a draw_ModoDiferido
// -----------------------------------------------------------------------------

void Malla3D::draw(bool modoDibujado, bool chess)
{

   this->ajedrez = chess;
   if(ajedrez)
      draw_ajedrezInmediato();
   else if(modoDibujado)
      draw_ModoDiferido();
   else
      draw_ModoInmediato();


   /*Apuntes práctica 3
      Crear un vector de normales
      material = activo


   */

   
}