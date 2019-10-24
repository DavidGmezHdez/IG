#include "aux.h"
#include "malla.h"
#include "tetraedro.h"

Tetraedro::Tetraedro()
{

   // inicializar la tabla de vértices
   Tupla3f v1(-1,-1,-1), v2(0,-1,1), v3(1,-1,-1), v4(0,1,0);
   v.push_back(v1);
   v.push_back(v2);
   v.push_back(v3);
   v.push_back(v4);
    
   // inicializar la tabla de caras o triángulos:
   Tupla3i t1(0,1,3), t2(1,2,3),t4(0,2,1), t3(0,3,2)  ;
   f.push_back(t1);
   f.push_back(t2);
   f.push_back(t3);
   f.push_back(t4);



   Tupla3f c1(200,0,0), c2(200,0,0), c3(200,0,0), c4(200,0,0);
   c.push_back(c1);
   c.push_back(c2);
   c.push_back(c3); 
   c.push_back(c4);

   // (es importante en cada cara ordenar los vértices en sentido contrario
   //  de las agujas del reloj, cuando esa cara se observa desde el exterior del cubo)

}

