#include "alax.h"

AlaX::AlaX(){
    morro = new Morro();
    trasera = new Trasera();
    direccion = {0,0,0};
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

void AlaX::cambiarAterrizaje(float incremento){
    morro->cambiarGradoRemolque(incremento);
}

void AlaX::girarAndroide(float incremento){
    trasera->girarAndroide(incremento);
}

void AlaX::rotarNave(int angulo, int incremento){

    switch(angulo){
        case 0:
            rotacion(0)=(rotacion(0)+incremento)%360;
            break;
        case 1:
            rotacion(1)=(rotacion(1)+incremento)%360;
            break;
        case 2:
            rotacion(2)=(rotacion(2)+incremento)%360;
        break;
    }
}

void AlaX::dirigirNave(int dir, int incremento){
    switch(dir){
        case 0:
            direccion(0)= direccion(0)+incremento;
            break;
        case 1:
            direccion(1)=direccion(1)+incremento;
            break;
        case 2:
            direccion(2)=direccion(2)+incremento;
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
