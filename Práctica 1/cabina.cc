#include "cabina.h"

Cabina::Cabina(float lado){

    Tupla3f v0(-lado, -lado, lado), v1(lado, -lado, lado), v2(lado, lado, lado), v3(-lado, lado, lado);

    v.push_back(v0);
    v.push_back(v1);
    v.push_back(v2);
    v.push_back(v3);

    // Segundo cuadrado
    Tupla3f v4(lado, -lado, -lado), v5(-lado, -lado, -lado),v6(-lado, lado, -lado),v7(lado, lado, -lado);
    v.push_back(v4);
    v.push_back(v5);
    v.push_back(v6);
    v.push_back(v7);

    Tupla3f v8(-lado,-lado,5*lado),v9(lado,-lado,5*lado);
    v.push_back(v8);
    v.push_back(v9);

    // inicializar la tabla de caras o triángulos:
    // Cara frontal
    Tupla3i t1(0, 1, 2), t2(0, 2, 3);
    f.push_back(t1);
    f.push_back(t2);

    // Cara final
    Tupla3i t3(4, 5, 6), t4(4, 6, 7);
    f.push_back(t3);
    f.push_back(t4);

    // Cara derecha
    Tupla3i t5(1, 7, 2), t6(1, 4, 7);
    f.push_back(t5);
    f.push_back(t6);

    // Cara izquierda
    Tupla3i t7(0, 3, 6), t8(0, 6, 5);
    f.push_back(t7);
    f.push_back(t8);

    // Cara de arriba
    Tupla3i t9(3, 7, 6), t10(3, 2, 7);
    f.push_back(t9);
    f.push_back(t10);

    // Cara de abajo
    Tupla3i t11(1, 5, 4), t12(1, 0, 5);
    f.push_back(t11);
    f.push_back(t12);

    //Triangulos de los lados
    Tupla3i t13(0, 8, 3), t14(1, 2, 9);
    f.push_back(t13);
    f.push_back(t14);

    //Parte superior
    Tupla3i t15(8, 9, 3), t16(9, 2, 3);
    f.push_back(t15);
    f.push_back(t16);

    //Parte superior
    Tupla3i t17(8, 0, 9), t18(9, 0, 1);
    f.push_back(t17);
    f.push_back(t18);
}