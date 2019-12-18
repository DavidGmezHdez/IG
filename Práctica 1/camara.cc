#include "camara.h"

Camara::Camara( int t,Tupla3f e, Tupla3f a, Tupla3f u,float ancho, float alto){
    this->tipo = t;
    this->eye = e;
    this->at = a;
    this->up = u.normalized();
    this->fov = atan(left/near)*(180*M_PI)*2;
    this->aspect = ancho/alto;

    this->left = alto/2;
    this->top = ancho/2;
    this->near = 50;
    this->far=3000;


    //Vector direccion
    vectorDir = {at(0) - eye(0), at(1) - eye(1), at(2) - eye(2)};

    //Eje X
    vectorX = {(vectorDir(1)*up(2)) - (vectorDir(2)*up(1)),
                (vectorDir(2)*up(0)) - (vectorDir(0)*up(2)),
                (vectorDir(0)*up(1)) - (vectorDir(1)*up(1))};
    vectorX = vectorX.normalized();
    //Eje Y
    vectorY = {(vectorDir(2)*vectorX(1)) - (vectorDir(1)*vectorX(2)),
                (vectorDir(0)*vectorX(2)) - (vectorDir(2)*vectorX(0)),
                (vectorDir(1)*vectorX(0)) - (vectorDir(0)*vectorX(1))};
    vectorY = vectorY.normalized();
}


Tupla3f Camara::cambiarMatriz(Tupla3f eje, Tupla3f vector, float angulo){
    Tupla3f rotacion;

    rotacion(0) = (cos(angulo) + eje(0) * (eje(0) *(1-cos(angulo)))) * vector(0) +
                  (eje(0) * (eje(1)*(1-cos(angulo))) - (eje(2)*sin(angulo))) * vector(1) +
                  (eje(0) * (eje(2)*(1-cos(angulo))) - (eje(1)*sin(angulo))) * vector(2);

    rotacion(1) = (eje(1) * (eje(0)*(1-cos(angulo))) - (eje(2)*sin(angulo))) * vector(0) +
                  (cos(angulo) + eje(1) * (eje(1) *(1-cos(angulo)))) * vector(1) +
                  (eje(1) * (eje(2)*(1-cos(angulo))) - (eje(0)*sin(angulo))) * vector(2);

    rotacion(1) = (eje(2) * (eje(0)*(1-cos(angulo))) - (eje(2)*sin(angulo))) * vector(0) +
                  (eje(2) * (eje(1)*(1-cos(angulo))) - (eje(0)*sin(angulo))) * vector(1);
                  (cos(angulo) + eje(2) * (eje(2) *(1-cos(angulo)))) * vector(2);

    return rotacion;

}

void Camara::rotarPP(float angulo, int eje){

    Tupla3f auxAt,auxUp;

    vectorDir = {at(0) - eye(0), at(1) - eye(1), at(2) - eye(2)};

    angulo*=(M_PI/180);

    switch(eje){
        case 0:
            auxAt = cambiarMatriz(vectorX,vectorDir,angulo);
            auxUp = cambiarMatriz(vectorX,up,angulo);
            vectorX = cambiarMatriz(vectorY,vectorX,angulo);
            break;
        case 1:
            auxAt = cambiarMatriz(vectorX,vectorDir,angulo);
            auxUp = cambiarMatriz(vectorX,up,angulo);
            vectorY = cambiarMatriz(vectorX,vectorY,angulo);
            break;
    }

    //Cambiamos el at
    at(0) = auxAt(0) + eye(0);
    at(1) = auxAt(1) + eye(1);
    at(2) = auxAt(2) + eye(2);
    up = auxUp;    

}

void Camara::rotarE(float angulo, int eje){
    Tupla3f auxVectorDir , auxUp;

    auxVectorDir = {eye(0) - at(0), eye(1) - at(1), eye(2) - at(2)};

    angulo*=(M_PI/180);

    switch(eje){
        case 0:
            auxVectorDir = cambiarMatriz(vectorY,auxVectorDir,angulo);
            auxUp = cambiarMatriz(vectorY,up,angulo);
            vectorX = cambiarMatriz(vectorY,vectorX,angulo);
            break;
        case 1:
            auxVectorDir = cambiarMatriz(vectorX,auxVectorDir,angulo);
            auxUp = cambiarMatriz(vectorX,up,angulo);
            vectorY = cambiarMatriz(vectorX,vectorY,angulo);
            break;
    }

    //Cambiamos el at
    eye(0) = at(0) + auxVectorDir(0);
    eye(1) = at(1) + auxVectorDir(1);
    eye(2) = at(2) + auxVectorDir(2);
    up = auxUp;  

}

//Rotamos en X
void Camara::rotarXExaminar(float angulo){
    rotarE(angulo,0);
}

//Rotamos en Y
void Camara::rotarYExaminar(float angulo){
    rotarE(angulo,1);
}
//void Camara::rotarZExaminar(float angulo){}
        
//Rotamos en X en Primera Persona
void Camara::rotarXPrimeraPersona(float angulo){
    rotarPP(angulo,0);
}

//Rotamos en Y en Primera Persona
void Camara::rotarYPrimeraPersona(float angulo){
    rotarPP(angulo,1);
}

//void Camara::rotarZPrimeraPersona(float angulo){}

void Camara::mover(float x, float y, float z){
    this->eye(0) = x;
    this->eye(1) = y;
    this->eye(2) = z;
}
void Camara::zoom(float factor){

    if(fov-factor>=1 && fov-factor<=180)
        fov-=factor;
    
    left = tan((fov/2)*(M_PI/180))*near;
    top = left*aspect;

}
        
void Camara::setObserver(){
    gluLookAt(eye(0),eye(1),eye(2), at(0),at(1),at(2), up(0),up(1),up(2));
}

void Camara::setProyeccion(){
    switch(tipo){
        case 1:
            gluPerspective(fov,aspect,near,far);
            break;
        case 2:
            glOrtho(-left, left, -top, top, near, far);
            break;
    }
}