
#include "material.h"


Material::Material(){
    this->difuso(0) = 0;
    this->difuso(1) = 0;
    this->difuso(2) = 0;
    this->difuso(3) = 0;

    this->especular(0) = 0;
    this->especular(1) = 0;
    this->especular(2) = 0;
    this->especular(3) = 0;

    this->ambiente(0) = 0;
    this->ambiente(1) = 0;
    this->ambiente(2) = 0;
    this->ambiente(3) = 0;

    this->brillo = 0.0;


}

 Material::Material(Tupla4f mdifuso,Tupla4f mespecular,Tupla4f mambiente,float mbrillo){
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

Material Material::operator=(const Material &m){
    this->difuso = m.difuso;
    this->especular = m.especular;
    this->ambiente = m.ambiente;
    this->brillo = m.brillo;
}