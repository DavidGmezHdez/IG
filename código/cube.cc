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
  Vertices[1]=_vertex3f(-Size/2,Size/2,0);
  Vertices[2]=_vertex3f(Size/2,-Size/2,0);
  Vertices[3]=_vertex3f(Size/2,Size/2,0);
//Segundo cuadrado
  Vertices[4]=_vertex3f(-Size/2,-Size/2,-Size);
  Vertices[5]=_vertex3f(-Size/2,Size/2,-Size);
  Vertices[6]=_vertex3f(Size/2,-Size/2,-Size);
  Vertices[7]=_vertex3f(Size/2,Size/2,-Size);

  Triangles.resize(4);

  Triangles[0]=_vertex3ui(0,1,4);
  Triangles[1]=_vertex3ui(1,4,7);
  Triangles[2]=_vertex3ui(2,0,3);
  Triangles[3]=_vertex3ui(0,2,1);
}
