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

   glDrawElements(GL_TRIANGLES, 3*f.size(),GL_UNSIGNED_INT,f.data());
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
   glBindBuffer(GL_ARRAY_BUFFER,crearVBO(GL_ARRAY_BUFFER,sizeof(v.size()),v.data())); 
   glVertexPointer(3,GL_FLOAT,0,0);
   glBindBuffer(GL_ARRAY_BUFFER,0); 
   glEnableClientState(GL_VERTEX_ARRAY);
   glBindBuffer(GL_ELEMENT_ARRAY_BUFFER,crearVBO(GL_ELEMENT_ARRAY_BUFFER,sizeof(f.size()),f.data()));
   glDrawElements(GL_TRIANGLES,3*f.size(),GL_UNSIGNED_INT,0);
   glBindBuffer(GL_ELEMENT_ARRAY_BUFFER,0);
   glDisableClientState(GL_VERTEX_ARRAY); 
}

// -----------------------------------------------------------------------------
/*
//dibuja los puntos del objeto
void Malla3D::draw_Puntos(){
  glPolygonMode(GL_FRONT_AND_BACK,GL_POINT);
  glBegin(GL_TRIANGLES);
  for (unsigned int i=0;i<f.size();i++){
     glVertex3fv((GLfloat *) &v[f[i](1)]);
     glVertex3fv((GLfloat *) &v[f[i](2)]);
     glVertex3fv((GLfloat *) &v[f[i](3)]);
  }
  glEnd();
}

// -----------------------------------------------------------------------------


//dibuja las lineas del objeto
void Malla3D::draw_Lineas(){
   glPolygonMode(GL_FRONT_AND_BACK,GL_LINE);
   glBegin(GL_TRIANGLES);
   for (unsigned int i=0;i<f.size();i++){
     glVertex3fv((GLfloat *) &v[f[i](1)]);
     glVertex3fv((GLfloat *) &v[f[i](2)]);
     glVertex3fv((GLfloat *) &v[f[i](3)]);
   }
   glEnd();
}


// -----------------------------------------------------------------------------


//dibuja las caras del objeto
void Malla3D::draw_Caras(){
   glPolygonMode(GL_FRONT_AND_BACK,GL_FILL);
   glBegin(GL_TRIANGLES);
   for (unsigned int i=0;i<f.size();i++){
     glVertex3fv((GLfloat *) &v[f[i](1)]);
     glVertex3fv((GLfloat *) &v[f[i](2)]);
     glVertex3fv((GLfloat *) &v[f[i](3)]);
   }
   glEnd();
}


// -----------------------------------------------------------------------------


//dibuja las caras del objeto en modo ajedrez
//void Malla3D::draw_Ajedrez();


// -----------------------------------------------------------------------------

*/
// Función de visualización de la malla,
// puede llamar a  draw_ModoInmediato o bien a draw_ModoDiferido

void Malla3D::draw(int modoDibujado, int modoVisualizacion)
{
   // completar .....(práctica 1)
   switch (modoVisualizacion){
      case 1:
         metodoGL = GL_POINT;
         break;
      case 2:
         metodoGL = GL_LINE;
         break;
      case 3:
         metodoGL = GL_FILL;
         break;
      case 4:
         //draw_Ajedrez();
         break;
   }

   glPolygonMode(GL_FRONT_AND_BACK,metodoGL);

   if(modoDibujado == 1)
      draw_ModoInmediato();
   else if(modoDibujado == 2)
      draw_ModoDiferido();

}

