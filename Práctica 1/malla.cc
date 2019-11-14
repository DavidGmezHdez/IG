
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

void Malla3D::setColor(float R, float G, float B){
   c.clear();
   for(int i=0;i<v.size();i++){
      c.push_back(Tupla3f(R,G,B));
   }
}

void Malla3D::draw_ModoInmediato()
{
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
   if(vbo_v == 0 && vbo_f==0){
      vbo_v = crearVBO(GL_ARRAY_BUFFER,3*sizeof(float)*v.size(),v.data());
      vbo_f = crearVBO(GL_ELEMENT_ARRAY_BUFFER,3*sizeof(int)*f.size(),f.data());  
      vbo_c = crearVBO(GL_ARRAY_BUFFER,3*sizeof(int)*c.size(),c.data());
   }
   glBindBuffer(GL_ARRAY_BUFFER,vbo_v);
   glBindBuffer(GL_ARRAY_BUFFER,vbo_c);  
   glVertexPointer(3,GL_FLOAT,0,0);
   glBindBuffer(GL_ARRAY_BUFFER,0);
   glBindBuffer(GL_ARRAY_BUFFER,0); 
   glEnableClientState(GL_VERTEX_ARRAY);
   glEnableClientState(GL_COLOR_ARRAY);
   glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, vbo_f);
   glShadeModel(GL_FLAT);
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

   impares.resize(f.size()/2);
   pares.resize(f.size()/2);
   
   for(int i=0, j=0;i<f.size();i+=2,j++){
      pares[j] = f[i];
      impares[j] = f[i+1];
   }

   glShadeModel(GL_FLAT);

   cimpares.resize(c.size());
   cpares.resize(c.size());

   for(int i=0;i<cpares.size();++i){
      cpares[i][0] = c[i](0);
      cpares[i][1] = c[i](1);
      cpares[i][2] = c[i](2);
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
// Función que calcula las normales de las caras
// -----------------------------------------------------------------------------

void Malla3D::calcularNormalesCaras(){
   Tupla3f p,q,r,a,b,mc,n;
   for(int i=0;i<f.size();i++){
      p = v[f[i](0)];
      q = v[f[i](1)];
      r = v[f[i](2)];
      a = q-p;
      b = r-p;
      mc = a.cross(b);
      n = mc.normalized();
      nc.push_back(n);
   }
}


// -----------------------------------------------------------------------------
// Función que calcula las normales de los vertices
// -----------------------------------------------------------------------------

void Malla3D::calcularNormalesVertices(){
     nv = std::vector<Tupla3f>(v.size(), {0, 0, 0});
   for(int i = 0;i<f.size();i++){
      nv[f[i](0)] = (nv[f[i](0)] + nc[i]).normalized();
      nv[f[i](1)] = (nv[f[i](1)] + nc[i]).normalized();
      nv[f[i](2)] = (nv[f[i](2)] + nc[i]).normalized();
   }
}

// -----------------------------------------------------------------------------
// Función que calcula las normales
// -----------------------------------------------------------------------------
void Malla3D::calcularNormales(){
   this->calcularNormalesCaras();
   this->calcularNormalesVertices();
}


// -----------------------------------------------------------------------------
// Función que modifica el material
// -----------------------------------------------------------------------------

void Malla3D::setMaterial(Material mat){
   this->m = Material(mat);
}

// -----------------------------------------------------------------------------
// Función de visualización de la malla,
// puede llamar a  draw_ModoInmediato o bien a draw_ModoDiferido
// -----------------------------------------------------------------------------

void Malla3D::draw(bool modoDibujado, bool chess)
{
   this->ajedrez = chess;
   if(nv.empty())
      this->calcularNormales();
   this->m.aplicar();
   if(ajedrez)
      draw_ajedrezInmediato();
      else if(modoDibujado)
         draw_ModoDiferido();
      else
         draw_ModoInmediato();
}