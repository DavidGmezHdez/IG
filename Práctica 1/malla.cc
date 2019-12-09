
#include "aux.h"
#include "malla.h"

// *****************************************************************************
//
// Clase Malla3D
//
// *****************************************************************************




// -----------------------------------------------------------------------------
// Función para poner el color del objeto en modo solido, en modo lineas y puntos el color será por defecto
// -----------------------------------------------------------------------------
void Malla3D::setColor(float R, float G, float B){
   c.clear();
   cp.clear();
   cl.clear();
   Tupla3f colorPuntos(0.7, 0.3, 1.0), colorLineas(0.3, 0.0, 0.0), colorSolido(R,G,B);
   for(int i=0;i<v.size();i++){
      cp.push_back(colorPuntos);
      cl.push_back(colorLineas);
      c.push_back(colorSolido);
   }

   cp.push_back(colorPuntos);
   cl.push_back(colorLineas);
   c.push_back(colorSolido);
}


// -----------------------------------------------------------------------------
// Visualización en modo inmediato con 'glDrawElements'
// -----------------------------------------------------------------------------
void Malla3D::draw_ModoInmediato(int modo)
{
   glEnableClientState(GL_VERTEX_ARRAY);
   glVertexPointer(3,GL_FLOAT,0,v.data());
   glEnableClientState(GL_NORMAL_ARRAY);
   glNormalPointer(GL_FLOAT,0,nv.data());

   if(!ct.empty()){
      glEnableClientState(GL_TEXTURE_COORD_ARRAY);
      glTexCoordPointer(2,GL_FLOAT,0,ct.data());
   }


   glEnableClientState(GL_COLOR_ARRAY);

   switch(modo){
      case 1:
         glColorPointer(3, GL_FLOAT, 0, cp.data());
         break;
      case 2:
         glColorPointer(3, GL_FLOAT, 0, cl.data());
         break;
      case 3:
         glColorPointer(3, GL_FLOAT, 0, c.data());
         break;
   }


   glDrawElements(GL_TRIANGLES, 3*f.size(),GL_UNSIGNED_INT,f.data());
   glDisableClientState(GL_COLOR_ARRAY);
   glDisableClientState(GL_TEXTURE_COORD_ARRAY);
   glDisableClientState(GL_NORMAL_ARRAY);
   glDisableClientState(GL_VERTEX_ARRAY);
}

// -----------------------------------------------------------------------------
// Creación VBOs
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
// Visualización en modo diferido con 'glDrawElements' (usando VBOs)
// -----------------------------------------------------------------------------

void Malla3D::draw_ModoDiferido(int modo)
{
   if(vbo_v == 0 && vbo_f==0){
      vbo_v = crearVBO(GL_ARRAY_BUFFER,3*sizeof(float)*v.size(),v.data());
      vbo_f = crearVBO(GL_ELEMENT_ARRAY_BUFFER,3*sizeof(int)*f.size(),f.data());
   }
   glBindBuffer(GL_ARRAY_BUFFER,vbo_v);  
   glVertexPointer(3,GL_FLOAT,0,0);
   glBindBuffer(GL_ARRAY_BUFFER,0);
   glEnableClientState(GL_VERTEX_ARRAY);
   glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, vbo_f);
   
   if (vbo_nv == 0)
      vbo_nv = crearVBO(GL_ARRAY_BUFFER,3*sizeof(float)*nv.size(),nv.data());

   glBindBuffer(GL_ARRAY_BUFFER,vbo_nv);
   glNormalPointer(GL_FLOAT,0,0);
   glBindBuffer(GL_ARRAY_BUFFER,0);
   glEnableClientState(GL_NORMAL_ARRAY);

   
   if(vbo_ct == 0)
      vbo_ct = crearVBO(GL_ARRAY_BUFFER,2*sizeof(float)*ct.size(),ct.data());
   
   glBindBuffer(GL_ARRAY_BUFFER,vbo_ct);
   glTexCoordPointer(2,GL_FLOAT,0,0);
   glBindBuffer(GL_ARRAY_BUFFER,0);
   glEnableClientState(GL_TEXTURE_COORD_ARRAY);
   

   glEnableClientState(GL_COLOR_ARRAY);
   
   switch(modo){
      case 1:
         if (vbo_cp == 0)
            vbo_cp = crearVBO(GL_ARRAY_BUFFER,3*sizeof(int)*cp.size(),cp.data());
         glBindBuffer(GL_ARRAY_BUFFER,vbo_cp);
         break;
      case 2:
         if (vbo_cl == 0)
            vbo_cl = crearVBO(GL_ARRAY_BUFFER,3*sizeof(int)*cl.size(),cl.data());
         glBindBuffer(GL_ARRAY_BUFFER,vbo_cl);
         break;
      case 3:
         if (vbo_c==0)
            vbo_c = crearVBO(GL_ARRAY_BUFFER,3*sizeof(int)*c.size(),c.data()); 
         glBindBuffer(GL_ARRAY_BUFFER,vbo_c);
         break;
   }
   glColorPointer(3, GL_FLOAT, 0, 0);
   glBindBuffer(GL_ARRAY_BUFFER,0);

   glDrawElements(GL_TRIANGLES,f.size()*3,GL_UNSIGNED_INT, 0 );
   glBindBuffer(GL_ELEMENT_ARRAY_BUFFER,0);
   glDisableClientState(GL_COLOR_ARRAY);
   glDisableClientState(GL_TEXTURE_COORD_ARRAY);
   glDisableClientState(GL_NORMAL_ARRAY);
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
   this->m = new Material(mat);
}


void Malla3D::setTextura(Textura tex){
   this->t = new Textura(tex);
   this->calcularCoordenadas();
}

// -----------------------------------------------------------------------------
// Función que calcula las coordenadas para las texturas
// -----------------------------------------------------------------------------

void Malla3D::calcularCoordenadas(){
   Tupla2f c0(0,0),c1(t->getAncho(),0),c2(0,t->getAlto()),c3(t->getAncho(),t->getAlto());
   ct.push_back(c0); ct.push_back(c1); ct.push_back(c2); ct.push_back(c3);
}

// -----------------------------------------------------------------------------
// Función de visualización de la malla,
// puede llamar a  draw_ModoInmediato o bien a draw_ModoDiferido
// -----------------------------------------------------------------------------

void Malla3D::draw(bool modoDibujado,bool points,bool lines,bool fill, bool chess)
{
   puntos = points;
   lineas = lines;
   solido = fill;
   ajedrez = chess;

   if(m!=nullptr)
      m->aplicar();
/*
   if(ct.empty())
      this->calcularCoordenadas();
 */
   if(nv.empty())
      this->calcularNormales();

   if(puntos){
      glPolygonMode(GL_FRONT_AND_BACK, GL_POINT);
      if(ajedrez)
         draw_ajedrezInmediato();
      else if(modoDibujado)
         draw_ModoDiferido(1);
      else
         draw_ModoInmediato(1);
   }

   if(lineas){
      glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
      if(ajedrez)
         draw_ajedrezInmediato();
      else if(modoDibujado)
         draw_ModoDiferido(2);
      else
         draw_ModoInmediato(2);
   }

   if(solido){
      glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
      if(ajedrez)
         draw_ajedrezInmediato();
      else if(modoDibujado)
         draw_ModoDiferido(3);
      else
         draw_ModoInmediato(3);
   }

   if(ajedrez)
      draw_ajedrezInmediato();
}