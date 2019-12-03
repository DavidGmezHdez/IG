#include "motor.h"

Motor::Motor(){
    base = new Cubo();
    cola = new Cubo();
    androide = new Esfera(50,50,10);
    gradoAndroide = 0;
}
void Motor::draw(bool modoDibujado,bool points,bool lines,bool fill, bool chess){
glPushMatrix();

    glPushMatrix();
        glScalef(20,20,20);
        base->draw(modoDibujado,points,lines,fill,chess);
    glPopMatrix();

    glPushMatrix();
        glTranslatef(-12,0,0);
        glScalef(15,15,15);
        cola->draw(modoDibujado,points,lines,fill,chess);
    glPopMatrix();

    glPushMatrix();
        glTranslatef(5,22,0);
        glRotatef(gradoAndroide,0,1,0);
        glScalef(1,1,1);
        androide->draw(modoDibujado,points,lines,fill,chess);
    glPopMatrix();

glPopMatrix();
}

void Motor::girarAndroide(float incremento){
    gradoAndroide+=incremento;
}


//Modificadores colores
void Motor::setColor(float R,float G,float B){
    base->setColor(R,G,B);
    cola->setColor(R,G,B);
    androide->setColor(R,G,B);
}
void Motor::setColorBase(float R,float G,float B){
    base->setColor(R,G,B);
}

void Motor::setColorCola(float R,float G,float B){
    cola->setColor(R,G,B);
}

void Motor::setColorAndroide(float R,float G,float B){
    androide->setColor(R,G,B);
}

//Modificadores materiales
void Motor::setMaterial(Material mat){
    base->setMaterial(mat);
    cola->setMaterial(mat);
    /*
    rotor1->setMaterial(mat);
    rotor2->setMaterial(mat);
    rotor3->setMaterial(mat);
    rotor4->setMaterial(mat);
    */
    androide->setMaterial(mat);
}

void Motor::setMaterialBase(Material mat){
    base->setMaterial(mat);
}

void Motor::setMaterialCola(Material mat){
    cola->setMaterial(mat);
}

void Motor::setMaterialAndroide(Material mat){
    androide->setMaterial(mat);
}