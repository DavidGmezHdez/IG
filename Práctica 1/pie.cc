#include "pie.h"

Pie::Pie(float lado){


    //Cuadrado superior
    Tupla3f v0(-lado/2,0,-lado/4),v1(-lado/2,0,-lado/4),v2(-lado/2,0,lado/4);

    //Tupla3f v4(-lado/2,-lado*2,-lado/4),v5(lado/2,-lado*2,-lado/4),v6(-lado/2,-lado*2,lado/4) ,v7(lado/2,-lado*2,lado/4);

    //Tupla3f v8(-lado/2,-lado/2 - (lado/4),0);

    v.push_back(v1);
    v.push_back(v2);
    /*v.push_back(v3);
    v.push_back(v4);
    v.push_back(v4);
    v.push_back(v5);
    v.push_back(v6);
    v.push_back(v7);
    v.push_back(v8);
    */


    Tupla3i f1(0,2,1),f2(1,3,2);
    f.push_back(f1);
    //f.push_back(f2);
}