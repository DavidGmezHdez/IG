#include "aux.h"
#include "malla.h"
#include "cubo.h"

Cubo::Cubo(float lado)
{

   // inicializar la tabla de vértices
   v.resize(8);
   Tupla3f p0(lado/2,-lado/2,lado/2); Tupla3f p1(lado/2,-lado/2,-lado/2); Tupla3f p2(-lado/2,-lado/2,-lado/2);
   Tupla3f p3(-lado/2,-lado/2,lado/2); Tupla3f p4(lado/2,lado/2,lado/2); Tupla3f p5(lado/2,lado/2,-lado/2);
   Tupla3f p6(-lado/2,lado/2,-lado/2); Tupla3f p7(-lado/2,lado/2,lado/2);
   v.push_back(p0);
   v.push_back(p1);
   v.push_back(p2);
   v.push_back(p3);
   v.push_back(p4);
   v.push_back(p5);
   v.push_back(p6);
   v.push_back(p7);

   // inicializar la tabla de caras o triángulos:



   
   // (es importante en cada cara ordenar los vértices en sentido contrario
   //  de las agujas del reloj, cuando esa cara se observa desde el exterior del cubo)

}

