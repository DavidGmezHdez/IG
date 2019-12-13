#include "camara.h"

Camara::Camara(Tupla3f e, Tupla3f a, Tupla3f u, int t, float f, float as, float n, float fa){
    this->tipo = t;
    this->eye = e;
    this->at = a;
    this->up = u.normalized();

    this->fov = f;
    this->aspect = as;
    this->near = n;
    this->far=fa;

    
}


void Camara::rotarXExaminar(float angulo);
void Camara::rotarYExaminar(float angulo);
void Camara::rotarZExaminar(float angulo);
        
void Camara::rotarXPrimeraPersona(float angulo);
void Camara::rotarYPrimeraPersona(float angulo);
void Camara::rotarZPrimeraPersona(float angulo);

void Camara::mover(float x, float y, float z){
    this->eye(0) = x;
    this->eye(1) = y;
    this->eye(2) = z;
}
void Camara::zoom(float factor);
        
void Camara::setObserver(){
    gluLookAt(eye(0),eye(1),eye(2), at(0),at(1),at(2), up(0),up(1),up(2));
}

void Camara::setProyeccion(){
    switch(tipo){
        case 1:
            gluPerspective(this->fov,this->aspect,this->near,this->far);
            break;
    }
}