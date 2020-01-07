#include "trasera.h"

Trasera::Trasera(){
    alaSupDer = new Ala();
    alaSupIzq = new Ala();
    alaInfDer = new Ala();
    alaInfIzq = new Ala();
    motor = new Motor();

    gradoAla1 = 0;
    gradoAla2 = 0;
    desplegadas = false;
}

void Trasera::draw(bool modoDibujado,bool points,bool lines,bool fill, bool chess){
glPushMatrix();
    
    glPushMatrix();
        motor->draw(modoDibujado,points,lines,fill,chess);
    glPopMatrix();

    glPushMatrix();
        glTranslatef(0,12,22);
        glRotatef(gradoAla1,1,0,0);
        alaSupDer->draw(modoDibujado,points,lines,fill,chess);
    glPopMatrix();

    glPushMatrix();
        glTranslatef(0,12,-22);
        glRotatef(gradoAla2,1,0,0);
        glRotatef(180,1,0,0);
        alaSupIzq->draw(modoDibujado,points,lines,fill,chess);
    glPopMatrix();

    glPushMatrix();
        glTranslatef(0,-12,22);
        glRotatef(gradoAla2,1,0,0);
        alaInfDer->draw(modoDibujado,points,lines,fill,chess);
    glPopMatrix();

    glPushMatrix();
        glTranslatef(0,-12,-22);
        glRotatef(gradoAla1,1,0,0);
        glRotatef(180,1,0,0);
        alaInfIzq->draw(modoDibujado,points,lines,fill,chess);
    glPopMatrix();


glPopMatrix();
}


void Trasera::desplegarAlas(float incremento){
    if(!desplegadas){
        if((gradoAla2+incremento)<gradoMax && (gradoAla1-incremento)>-gradoMax){
            gradoAla2+=incremento;
            gradoAla1-=incremento;
        }
        else{
            gradoAla2 = gradoMax;
            gradoAla1 = -gradoMax;
            desplegadas = true;
        }
    }
}

void Trasera::plegarAlas(float incremento){
    if(desplegadas){
        if((gradoAla2+incremento)>0 && (gradoAla1-incremento)<0){
            gradoAla2+=incremento;
            gradoAla1-=incremento;
        }
        else{
            gradoAla2 = 0;
            gradoAla1 = 0;
            desplegadas = false;
        }
    }
}

void Trasera::switchAlas(float grado){
    if(!desplegadas)
        desplegarAlas(grado);
    else
        plegarAlas(-grado);
}

void Trasera::girarAndroide(float incremento){
    motor->girarAndroide(incremento);
}

//Modificadores de colores

void Trasera::setColor(Tupla3f rotor, Tupla3f base, Tupla3f laser, Tupla3f canon,Tupla3f baseMotor, Tupla3f cola, Tupla3f androide){
    setColorAlas(rotor,base,laser,canon);
    setColorMotor(base,cola,androide);
}

void Trasera::setColorAlas(Tupla3f rotor, Tupla3f base, Tupla3f laser, Tupla3f canon){
    alaSupDer->setColorBase(base(0),base(1),base(2));
    alaSupDer->setColorRotor(rotor(0),rotor(1),rotor(2));
    alaSupDer->setColorLaser(laser(0),laser(1),laser(2));
    alaSupDer->setColorCanon(canon(0),canon(1),canon(2));

    alaSupIzq->setColorBase(base(0),base(1),base(2));
    alaSupIzq->setColorRotor(rotor(0),rotor(1),rotor(2));
    alaSupIzq->setColorLaser(laser(0),laser(1),laser(2));
    alaSupIzq->setColorCanon(canon(0),canon(1),canon(2));
    
    alaInfDer->setColorBase(base(0),base(1),base(2));
    alaInfDer->setColorRotor(rotor(0),rotor(1),rotor(2));
    alaInfDer->setColorLaser(laser(0),laser(1),laser(2));
    alaInfDer->setColorCanon(canon(0),canon(1),canon(2));

    alaInfIzq->setColorBase(base(0),base(1),base(2));
    alaInfIzq->setColorRotor(rotor(0),rotor(1),rotor(2));
    alaInfIzq->setColorLaser(laser(0),laser(1),laser(2));
    alaInfIzq->setColorCanon(canon(0),canon(1),canon(2));

}

void Trasera::setColorMotor(Tupla3f base, Tupla3f cola, Tupla3f androide){
    motor->setColorBase(base(0),base(1),base(2));
    motor->setColorCola(cola(0),cola(1),cola(2));
    motor->setColorAndroide(androide(0),androide(1),androide(2));
}


void Trasera::setMaterialAlas(Material rotor, Material base, Material laser, Material canon){
    alaSupDer->setMaterialBase(base);
    alaSupDer->setMaterialRotor(rotor);
    alaSupDer->setMaterialLaser(laser);
    alaSupDer->setMaterialCanon(canon);

    alaSupIzq->setMaterialBase(base);
    alaSupIzq->setMaterialRotor(rotor);
    alaSupIzq->setMaterialLaser(laser);
    alaSupIzq->setMaterialCanon(canon);

    alaInfDer->setMaterialBase(base);
    alaInfDer->setMaterialRotor(rotor);
    alaInfDer->setMaterialLaser(laser);
    alaInfDer->setMaterialCanon(canon);

    alaInfIzq->setMaterialBase(base);
    alaInfIzq->setMaterialRotor(rotor);
    alaInfIzq->setMaterialLaser(laser);
    alaInfIzq->setMaterialCanon(canon);

}

void Trasera::setMaterialMotor(Material base, Material cola, Material androide){
    motor->setMaterialBase(base);
    motor->setMaterialCola(cola);
    motor->setMaterialAndroide(androide);
}