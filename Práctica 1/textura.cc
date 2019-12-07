#include "textura.h"

Textura::Textura(std::string archivo,GLuint id){
    textura_id = id;
    
    glGenTextures(1,&textura_id);

    if(pimg == nullptr)
        pimg = new jpg::Imagen(archivo);
    
    ancho = pimg->tamX();

    alto = pimg->tamY();


    for(int i=0;i<ancho;i++){
        for(int j=0;j<alto;j++){
            data.push_back(pimg->leerPixel(i,j));
        }
    }
}

void Textura::activar(){
    
    glBindTexture(GL_TEXTURE_2D,textura_id);

    glLightModeli(GL_LIGHT_MODEL_COLOR_CONTROL,GL_SEPARATE_SPECULAR_COLOR);
    
    //Como a partir de una coordenada de textura se selecciona un texel
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR); 
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_LINEAR);
    

    // Entorno para las texturas
    glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_DECAL);

    //Coordenadas fuera de [0,1]
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S,GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T,GL_REPEAT);
    

    gluBuild2DMipmaps(GL_TEXTURE_2D,GL_RGB,ancho,alto,GL_RGB,GL_UNSIGNED_BYTE,pimg->leerPixels());
}
