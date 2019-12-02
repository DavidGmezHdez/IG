#include "remolque.h"

Remolque::Remolque(float lado){


    //Cuadrado superior
    Tupla3f v0(-lado/4,0,lado/4),v1(lado/4,0,lado/4),v2(lado/4,0,-lado/4),v3(-lado/4,0,-lado/4);

    Tupla3f v4(-lado/4,-lado*1.5,lado/4),v5(lado/4,-lado*1.5,lado/4),v6(lado/4,-lado*1.5,-lado/4) ,v7(-lado/4,-lado*1.5,-lado/4);

    Tupla3f v8(-lado/4,-lado*1.5 - (lado/4),lado/4),v9(lado/4,-lado*1.5 - (lado/4),lado/4),
    v10(lado/4,-lado*1.5 - (lado/4),-lado/4),v11(-lado/4,-lado*1.5 - (lado/4),-lado/4);

    Tupla3f v12(-lado/4,-lado*1.5 - (lado/4),lado),v13(lado/4,-lado*1.5 - (lado/4),lado), v14(lado/4,-lado*1.5,lado), v15(-lado/4,-lado*1.5,lado);


    v.push_back(v0);
    v.push_back(v1);
    v.push_back(v2);
    v.push_back(v3);
    v.push_back(v4);
    v.push_back(v5);
    v.push_back(v6);
    v.push_back(v7);
    v.push_back(v8);
    v.push_back(v9);
    v.push_back(v10);
    v.push_back(v11);
    v.push_back(v12);
    v.push_back(v13);
    v.push_back(v14);
    v.push_back(v15);
    

    Tupla3i f1(0,1,3),f2(1,2,3);
    f.push_back(f1);
    f.push_back(f2);

    Tupla3i f3(4,7,5),f4(5,7,6);
    f.push_back(f3);
    f.push_back(f4);

    Tupla3i f5(4,1,0),f6(5,1,4);
    f.push_back(f5);
    f.push_back(f6);

    Tupla3i f7(4,0,7),f8(7,0,3);
    f.push_back(f7);
    f.push_back(f8);

    Tupla3i f9(7,2,6),f10(7,3,2);
    f.push_back(f9);
    f.push_back(f10);

    Tupla3i f11(5,6,1),f12(2,1,6);
    f.push_back(f11);
    f.push_back(f12);

    Tupla3i f13(8,9,4),f14(9,5,4);
    f.push_back(f13);
    f.push_back(f14);

    Tupla3i f15(11,8,4),f16(11,4,7);
    f.push_back(f15);
    f.push_back(f16);

    Tupla3i f17(10,5,9),f18(10,6,5);
    f.push_back(f17);
    f.push_back(f18);

    Tupla3i f19(11,7,10),f20(10,7,6);
    f.push_back(f19);
    f.push_back(f20);

    Tupla3i f21(8,10,9),f22(8,11,10);
    f.push_back(f21);
    f.push_back(f22);
    
    Tupla3i f23(12,14,15),f24(13,14,12);
    f.push_back(f23);
    f.push_back(f24);

    Tupla3i f25(15,14,4),f26(14,5,4);
    f.push_back(f25);
    f.push_back(f26);

    Tupla3i f27(8,12,15),f28(15,4,8);
    f.push_back(f27);
    f.push_back(f28);

    Tupla3i f29(13,9,14),f30(9,5,14);
    f.push_back(f29);
    f.push_back(f30);

    Tupla3i f31(13,12,8),f32(8,9,13);
    f.push_back(f31);
    f.push_back(f32);
}