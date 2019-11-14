
#include "material.h"


Material::Material(){}

Material::Material(Tupla4f mambiente,Tupla4f mdifuso,Tupla4f mespecular,float mbrillo){
    this->difuso = mdifuso;
    this->especular = mespecular;
    this->ambiente = mambiente;
    this->brillo = mbrillo;
}


void Material::aplicar(){
    glMaterialfv(GL_FRONT,GL_AMBIENT,this->ambiente);
    glMaterialfv(GL_FRONT,GL_DIFFUSE,this->difuso);
    glMaterialfv(GL_FRONT,GL_SPECULAR,this->especular);
    glMaterialf(GL_FRONT,GL_SHININESS,this->brillo);
}
