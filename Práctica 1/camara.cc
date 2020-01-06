#include "camara.h"

Camara::Camara( int t,Tupla3f e, Tupla3f a, Tupla3f u,float ancho, float alto){
    this->tipo = t;
    this->eye = e;
    this->at = a;
    this->up = u.normalized();
    this->fov = atan(left/near)*(180/M_PI)*2;
    this->aspect = ancho/alto;

    this->left = alto/2;
    this->top = ancho/2;
    this->near = 50;
    this->far=3000;


    /*
    VectorDir es el vector VPN, y sería, por decirlo de una forma intuitiva,
    el eje Z de nuestro sistema de coordenadas de vista.
    */
    vectorDir = {at(0) - eye(0), at(1) - eye(1), at(2) - eye(2)};
    /*
    VectorX sería el eje X de nuestro sistema de coordenadas de vista
    (digamos “el que marca el sentido hacia la derecha”) y es
    perpendicular al plano que forman VUP y VPN, por tanto, se
    calcula como el resultado normalizado del producto vectorial
    entre éstos dos vectores. ¡Ojo que el orden afecta!
    */
    vectorX = vectorDir.cross(this->up);
    vectorX = vectorX.normalized();
    /*
    VectorY sería el eje Y del sistema de coordenadas de vista, y es
    ortogonal a n y u, por lo que su cálculo es también mediante el
    producto vectorial de estos dos ejes:
    */
    vectorY = vectorX.cross(this->vectorDir);
    vectorY = vectorY.normalized();
    
}


Tupla3f Camara::cambiarMatriz(Tupla3f eje, Tupla3f vector, float angulo){
    Tupla3f rotacion;
    rotacion(0) = (cos(angulo) + eje(0) * eje(0) *(1-cos(angulo))) * vector(0) +
                  (eje(0) * eje(1)*(1-cos(angulo)) - eje(2)*sin(angulo)) * vector(1) +
                  (eje(0) * eje(2)*(1-cos(angulo)) + eje(1)*sin(angulo)) * vector(2);

    rotacion(1) = (eje(1) * eje(0)*(1-cos(angulo)) + eje(2)*sin(angulo)) * vector(0) +
                  (cos(angulo) + eje(1) * eje(1) *(1-cos(angulo))) * vector(1) +
                  (eje(1) * eje(2)*(1-cos(angulo)) - eje(0)*sin(angulo)) * vector(2);

    rotacion(2) = (eje(2) * eje(0)*(1-cos(angulo)) - eje(1)*sin(angulo)) * vector(0) +
                  (eje(2) * eje(1)*(1-cos(angulo)) + eje(0)*sin(angulo)) * vector(1) +
                  (cos(angulo) + eje(2) * eje(2) *(1-cos(angulo))) * vector(2);
    
    return rotacion;
}



void Camara::rotarPP(float angulo, int eje){

    Tupla3f auxAt,auxUp;

    vectorDir = {at(0) - eye(0), at(1) - eye(1), at(2) - eye(2)};

    angulo*=(M_PI/180);

    switch(eje){
        case 0:
            auxAt = cambiarMatriz(vectorY,vectorDir,angulo);
            auxUp = cambiarMatriz(vectorY,up,angulo);
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

    //Cambiamos el up
    this->up = auxUp;

}

void Camara::rotarE(float angulo, int eje){
    Tupla3f auxVectorDir , auxAt, auxUp;

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

    //Cambiamos el up
    this->up = auxUp;

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
            glFrustum(-left, left, -top, top, near, far);
            break;
        case 2:
            glOrtho(-left, left, -top, top, near, far);
            break;
    }
}