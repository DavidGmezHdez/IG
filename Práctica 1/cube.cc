/*
* Practicas de IG
* David Gómez Hernández
*
* GPL 3
*/

#include "cube.h"

/**
*
*@param
*@returns
*/

_cube::_cube(float Size)
{
  Vertices.resize(8);
//Primer cuadrado
  Vertices[0]=_vertex3f(-Size/2,-Size/2,0);
  Vertices[1]=_vertex3f(Size/2,-Size/2,0);
  Vertices[2]=_vertex3f(Size/2,Size/2,0);
  Vertices[3]=_vertex3f(-Size/2,Size/2,0);
  
//Segundo cuadrado
  Vertices[4]=_vertex3f(-Size/2,-Size/2,-Size);
  Vertices[5]=_vertex3f(Size/2,-Size/2,-Size);
  Vertices[6]=_vertex3f(Size/2,Size/2,-Size);
  Vertices[7]=_vertex3f(-Size/2,Size/2,-Size);
  

  Triangles.resize(12);

  Triangles[0]=_vertex3ui(0,1,2);
  Triangles[1]=_vertex3ui(0,2,3);
  Triangles[2]=_vertex3ui(4,5,6);
  Triangles[3]=_vertex3ui(4,6,7);
  Triangles[4]=_vertex3ui(3,7,6);
  Triangles[5]=_vertex3ui(3,2,6);
  Triangles[6]=_vertex3ui(0,4,5);
  Triangles[7]=_vertex3ui(0,1,5);
  Triangles[8]=_vertex3ui(1,5,6);
  Triangles[9]=_vertex3ui(1,2,6);
  Triangles[10]=_vertex3ui(0,4,7);
  Triangles[11]=_vertex3ui(0,3,7);
  
}
