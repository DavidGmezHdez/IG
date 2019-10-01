#include "aux.h"
#include "malla.h"

// *****************************************************************************
//
// Clase Malla3D
//
// *****************************************************************************

// Visualización en modo inmediato con 'glDrawElements'

void Malla3D::draw_ModoInmediato()
{
  // visualizar la malla usando glDrawElements,
  // completar (práctica 1)
  // ...
   glEnableClientState(GL_VERTEX_ARRAY);
   glVertexPointer(3,GL_FLOAT,0,v.data());
   glEnableClientState(GL_COLOR_ARRAY);
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
   // (la primera vez, se deben crear los VBOs y guardar sus identificadores en el objeto)
   // completar (práctica 1)
   // .....
   glBindBuffer(GL_ARRAY_BUFFER,crearVBO(GL_ARRAY_BUFFER,v.size(),v.data())); 
   glVertexPointer(3,GL_FLOAT,0,0);
   glBindBuffer(GL_ARRAY_BUFFER,0); 
   glEnableClientState(GL_VERTEX_ARRAY);
   glBindBuffer(GL_ELEMENT_ARRAY_BUFFER,crearVBO(GL_ELEMENT_ARRAY_BUFFER,v.size(),v.data()));
   glDrawElements(GL_TRIANGLES,3*f.size(),GL_UNSIGNED_INT,f.data());
   glBindBuffer(GL_ELEMENT_ARRAY_BUFFER,0);
   glDisableClientState(GL_VERTEX_ARRAY); 
}


// -----------------------------------------------------------------------------

// Función de visualización de la malla,
// puede llamar a  draw_ModoInmediato o bien a draw_ModoDiferido

void Malla3D::draw(bool modoDibujado, GLenum modoVisualizacion, bool chess)
{
   // completar .....(práctica 1)
   switch (modoVisualizacion){
      case GL_POINT:
         glPolygonMode(GL_FRONT_AND_BACK,GL_POINT);
         break;
      case GL_LINE:
         glPolygonMode(GL_FRONT_AND_BACK,GL_LINE);
         break;
      case GL_FILL:
        glPolygonMode(GL_FRONT_AND_BACK,GL_FILL);
         break;
   }

   if(modoDibujado)
      draw_ModoDiferido();
   else
      draw_ModoInmediato();

   this->ajedrez = chess;

}



void Malla3D::draw_ajedrez(){
   
   float color_random = static_cast <float> (rand()) / (static_cast <float> (RAND_MAX/255));
   int posicion = static_cast <int> (rand()) / (static_cast <int> (RAND_MAX/2));

   for(int i=0;i<c.size();i+=2){
      c[i](posicion) = color_random;
   }




}

