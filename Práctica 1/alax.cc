#include "alax.h"

AlaX::AlaX(){
    morro = new Morro();
    trasera = new Trasera();
    direccion = {-700,700,-700};
    rotacion = {0,0,0};
}

void AlaX::draw(bool modoDibujado,bool points,bool lines,bool fill, bool chess){
glPushMatrix();

    glTranslatef(direccion(0),direccion(1),direccion(2));
    glRotatef(rotacion(0),1,0,0);
    glRotatef(rotacion(1),0,1,0);
    glRotatef(rotacion(2),0,0,1);

    glPushMatrix();
        morro->draw( modoDibujado,points,lines,fill,chess);
    glPopMatrix();

    glPushMatrix();
        trasera->draw( modoDibujado,points,lines,fill,chess);
    glPopMatrix();

glPopMatrix();
}


void AlaX::switchAlas(float grado){
    trasera->switchAlas(grado);
}

void AlaX::desplegarAlas(float incremento){
    trasera->desplegarAlas(incremento);
}

void AlaX::plegarAlas(float incremento){
    trasera->plegarAlas(incremento);
}


void AlaX::sacarTrenAterrizaje(int incremento){
    morro->sacarTrenAterrizaje(incremento);
}

void AlaX::guardarTrenAterrizaje(int incremento){
    morro->guardarTrenAterrizaje(incremento);
}

void AlaX::girarAndroide(float incremento){
    trasera->girarAndroide(incremento);
}

void AlaX::rotarNave(int angulo, int incremento,int max){
/*
    switch(angulo){
        case 0:
                if(rotacion(0)+incremento > max)
                    rotacion(0) = max;
                else if(rotacion(0)+incremento < -max) 
                    rotacion(0)= -max;
                else
                    rotacion(0) = (rotacion(0)+incremento)%360;
            break;
        case 1:
                if(rotacion(1)+incremento > max)
                    rotacion(1) = max;
                else if(rotacion(1)+incremento < -max)
                    rotacion(1)= -max;
                else
                    rotacion(1) = (rotacion(1)+incremento)%360;
            break;
        case 2:
                if(rotacion(2)+incremento > max)
                    rotacion(2) = max;
                else if(rotacion(2)+incremento < -max)
                    rotacion(2)= -max;
                else
                    rotacion(2) = (rotacion(2)+incremento)%360;
        break;
    }
*/

    switch(angulo){
        case 0:
                if(rotacion(0)+incremento!=max)
                    rotacion(0) = (rotacion(0)+incremento)%360;
            break;
        case 1:
                if(rotacion(1)+incremento!=max)
                    rotacion(1) = (rotacion(1)+incremento)%360;
            break;
        case 2:
                if(rotacion(2)+incremento!=max)
                    rotacion(2) = (rotacion(2)+incremento)%360;
        break;
    }

}


void AlaX::dirigirNave(int dir, int incremento, int posicionFinal){
    switch(dir){
        case 0:
                if(direccion(0)+incremento!=posicionFinal)
                    direccion(0)= direccion(0)+incremento;
            break;
        case 1:
                if(direccion(1)+incremento!=posicionFinal)
                    direccion(1)= direccion(1)+incremento;
            break;
        case 2:
                if(direccion(2)+incremento!=posicionFinal)
                    direccion(2)= direccion(2)+incremento;
            break;
    }

}


//Modificadores colores
void AlaX::setColor(float R,float G,float B){
    setColorTrasera(R,G,B);
    setColorMorro(R,G,B);
}

void AlaX::setColorTrasera(float R,float G,float B){
    trasera->setColor(R,G,B);
}

void AlaX::setColorMorro(float R,float G,float B){
    morro->setColor(R,G,B);
}

//Modificadores materiales
void AlaX::setMaterial(Material mat){
    setMaterialTrasera(mat);
    setMaterialMorro(mat);
}

void AlaX::setMaterialTrasera(Material mat){
    trasera->setMaterial(mat);
}

void AlaX::setMaterialMorro(Material mat){
    morro->setMaterial(mat);
}
