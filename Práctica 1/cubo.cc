#include "aux.h"
#include "malla.h"
#include "cubo.h"

Cubo::Cubo(float lado)
{

   // inicializar la tabla de vértices
   v.resize(8);
   
   //Primer cuadrado
   Tupla3f p0(50*lado/2,50*-lado/2,50*lado/2),p1(50*lado/2,50*-lado/2,50*-lado/2), p2(50*-lado/2,50*-lado/2,50*-lado/2),
   p3(50*-lado/2,50*-lado/2,50*lado/2);
   
   //Segundo cuadrado
   Tupla3f p4(50*lado/2,50*lado/2,50*lado/2), p5(50*lado/2,50*lado/2,50*-lado/2),
   p6(50*-lado/2,50*lado/2,50*-lado/2), p7(50*-lado/2,50*lado/2,50*lado/2);
   
   v.push_back(p0);
   v.push_back(p1);
   v.push_back(p2);
   v.push_back(p3);
   v.push_back(p4);
   v.push_back(p5);
   v.push_back(p6);
   v.push_back(p7);

   // inicializar la tabla de caras o triángulos:

   //Cara inferior
   Tupla3i c0(3,0,1), c1(1,2,3);
   f.push_back(c0);
   f.push_back(c1);

   //Cara superior
   Tupla3i c2(4,5,6), c3(6,7,4);
   f.push_back(c2);
   f.push_back(c3);

   //Cara frontal
   Tupla3i c4(4,0,3), c5(3,7,4);
   f.push_back(c4);
   f.push_back(c5);

   //Cara trasera
   Tupla3i c6(1,5,6), c7(6,2,1);
   f.push_back(c6);
   f.push_back(c7);

   //Cara derecha
   Tupla3i c8(4,5,1), c9(1,0,4);
   f.push_back(c8);
   f.push_back(c9);

   //Cara superior
   Tupla3i c10(6,7,3), c11(3,2,6);
   f.push_back(c10);
   f.push_back(c11);

   
   // (es importante en cada cara ordenar los vértices en sentido contrario
   //  de las agujas del reloj, cuando esa cara se observa desde el exterior del cubo)

}

