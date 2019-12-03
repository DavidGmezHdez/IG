#include "alax.h"

AlaX::AlaX(){
    morro = new Morro();
    trasera = new Trasera();
}

void AlaX::draw(bool modoDibujado,bool points,bool lines,bool fill, bool chess){
glPushMatrix();

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
