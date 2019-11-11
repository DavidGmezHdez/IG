
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

void Malla3D::draw_ModoInmediato(std::vector<Tupla3f> vertices,  std::vector<Tupla3i> caras)
{
   glEnableClientState(GL_VERTEX_ARRAY);
   glVertexPointer(3,GL_FLOAT,0,vertices.data());
   glEnableClientState(GL_COLOR_ARRAY);
   glColorPointer(3, GL_FLOAT, 0, c.data());
   glShadeModel(GL_FLAT);
   glDrawElements(GL_TRIANGLES, 3*caras.size(),GL_UNSIGNED_INT,caras.data());
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

void Malla3D::draw_ModoDiferido(std::vector<Tupla3f> vertices,  std::vector<Tupla3i> caras)
{
   if(vbo_v == 0 && vbo_f==0){
      vbo_v = crearVBO(GL_ARRAY_BUFFER,3*sizeof(float)*vertices.size(),vertices.data());
      vbo_f = crearVBO(GL_ELEMENT_ARRAY_BUFFER,3*sizeof(int)*caras.size(),caras.data());  
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
   glDrawElements(GL_TRIANGLES,3*caras.size(),GL_UNSIGNED_INT,caras.data());
   glBindBuffer(GL_ELEMENT_ARRAY_BUFFER,0);
   glDisableClientState(GL_COLOR_ARRAY);
   glDisableClientState(GL_VERTEX_ARRAY); 
}

// -----------------------------------------------------------------------------
// Visualización en modo inmediato con el modo ajedrez
// -----------------------------------------------------------------------------

void Malla3D::draw_ajedrezInmediato(std::vector<Tupla3f> vertices,  std::vector<Tupla3i> caras){
   glEnableClientState(GL_VERTEX_ARRAY);
   glVertexPointer(3,GL_FLOAT,0,vertices.data());
   glEnableClientState(GL_COLOR_ARRAY);
   
   for(int i=0;i<caras.size();i+=2){
      impares.push_back(f[i]);
      pares.push_back(f[i+1]);
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
   nv.resize(v.size());
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

/*
void Malla3D::setMaterial(Material mat){
   this->m = mat;
}
*/


// -----------------------------------------------------------------------------
// Función de visualización de la malla,
// puede llamar a  draw_ModoInmediato o bien a draw_ModoDiferido
// -----------------------------------------------------------------------------

void Malla3D::draw(bool modoDibujado, bool chess, bool tapas)
{
   this->tapas = tapas;
   this->ajedrez = chess;

   switch(tapas){
      case false:
         if(ajedrez)
            draw_ajedrezInmediato(this->v,this->f);
         else if(modoDibujado)
            draw_ModoDiferido(this->v,this->f);
         else
            draw_ModoInmediato(this->v,this->f);
      break;
      case true:
         if(ajedrez)
            draw_ajedrezInmediato(this->vtapas,this->ftapas);
         else if(modoDibujado)
            draw_ModoDiferido(this->vtapas,this->ftapas);
         else
            draw_ModoInmediato(this->vtapas,this->ftapas);
   }

/*
 if(tapas){
    if(!modoDibujado){
        if(chess){
          draw_ajedrezInmediato(this->vtapas, this->ftapas);
        }

        else{
          draw_ModoInmediato(this->vtapas, this->ftapas);
        }
      }

      else{
        draw_ModoDiferido(this->vtapas, this->ftapas);
      }
  }
  
  else{
      if(!modoDibujado){
      if(chess){
       draw_ajedrezInmediato(this->v, this->f);
      }

      else{
        draw_ModoInmediato(this->v, this->f);
      }
    }

    else{
      draw_ModoDiferido(this->v, this->f);
    }
  }
*/




}