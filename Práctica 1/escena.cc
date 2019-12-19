#include "aux.h"     // includes de OpenGL/glut/glew, windows, y librería std de C++
#include "escena.h"

//**************************************************************************
// constructor de la escena (no puede usar ordenes de OpenGL)
//**************************************************************************

Escena::Escena()
{
   Front_plane       = 50.0;
   Back_plane        = 2000.0;
   Observer_distance = 4*Front_plane;
   Observer_angle_x  = 0.0 ;
   Observer_angle_y  = 0.0 ;

   ejes.changeAxisSize( 5000 );

   //Creacion de objetos
   //Tetrahedro
   mallas[0] = new Tetraedro();
   //Cubo
   mallas[1] = new Cubo();
   //Peon
   mallas[2] = new ObjRevolucion("plys/peon.ply",30,tapas,tapas);
   //Hormiga
   mallas[3] = new ObjPLY("plys/ant.ply");
   //Cilindro
   mallas[4] = new Cilindro(50,25,10);
   //Esfera
   mallas[5] = new Esfera(50,50,10);
   //Cuadro
   mallas[6] = new Cuadro();
   //AlaX
   mallas[7] = new AlaX();

   //Creacion de materiales
   plata = Material({0.19225,0.19225,0.19225, 1.0},{0.50754, 0.50754,0.50754, 1.0},{0.0, 0.0,0.0, 1.0},128.0);//Sin brillos especulares
   oro = Material({0.24725,0.1995, 0.0745, 0.6},{0.0, 0.0, 0.0, 0.1},{0.628281, 0.555802, 0.366065, 0.1},128.0);//Sin reflectividad difusa
   bronce = Material({0.2125,0.1275,0.054,1.0},{0.714, 0.4284, 0.18144,1.0},{0.393548, 0.271906, 0.166721, 1.0},0.2);
   negro = Material({0.0,0.0,0.0,1.0},{0.0,0.0,0.0,1.0},{0.50,0.50,0.50,1.0},128*0.25);

   //Creacion de texturas
   madera = Textura("archivosP5/text-madera.jpg",1);

   //Creacion de luces
   luces[0] = new LuzPosicional(GL_LIGHT1,{-100, 100, 100},{0.0,0.0,0.0,1.0},{1.0,1.0,1.0,1.0},{1.0,1.0,1.0,1.0});
   luces[1] = new LuzDireccional(GL_LIGHT2,{0, 0},{0.0, 0.0, 0.0, 1.0}, {1.0, 1.0, 1.0, 1.0}, {1.0, 1.0, 1.0, 1.0});

   //Creacion de cámaras
   camaras[0] = new Camara(1,{200,200,200},{0,0,0},{0,1,0},100,100);
   camaras[1] = new Camara(2,{-200,-200,-200}, {0,0,0},{0,1,0},500, 500);
   camaras[2] = new Camara(1,{200,-200,0}, {0,0,0}, {0,1,0},100, 100);
   camaras[3] = new Camara(2, {-200,0,0}, {0,0,0}, {0,1,0},200, 200);
   
   numCamaraActiva = 0;

   //Modificando los parámetros para la animacion
   animacionAutomatica = animacionManual = animacionLuz = false;
   grado = -1;

   //Aplicacion de materiales
   for(int i=0,j=0;i<8;i++,j++){
      switch(j%3){
         case 0:
            mallas[i]->setMaterial(bronce);
            break;
         case 1:
            mallas[i]->setMaterial(plata);
            break;
         case 2:
            mallas[i]->setMaterial(oro);
            break;
      }
   }
   
   //Aplicacion de texturas
   mallas[6]->calcularCoordenadas();
   mallas[6]->setTextura(madera);
   mallas[1]->calcularCoordenadas();
   mallas[1]->setTextura(madera);

   //Declaracion variables seleccion
   objeto = -1;

}

//**************************************************************************
// inicialización de la escena (se ejecuta cuando ya se ha creado la ventana, por
// tanto sí puede ejecutar ordenes de OpenGL)
// Principalmemnte, inicializa OpenGL y la transf. de vista y proyección
//**************************************************************************

void Escena::inicializar( int UI_window_width, int UI_window_height )
{
	glClearColor( 1.0, 1.0, 1.0, 1.0 );// se indica cual sera el color para limpiar la ventana	(r,v,a,al)

	glEnable( GL_DEPTH_TEST );	// se habilita el z-bufer
    
	Width  = UI_window_width/10;
	Height = UI_window_height/10;

   change_projection( float(UI_window_width)/float(UI_window_height) );
	glViewport( 0, 0, UI_window_width, UI_window_height );
}

// **************************************************************************
//
// función de dibujo de la escena: limpia ventana, fija cámara, dibuja ejes,
// y dibuja los objetos
//
// **************************************************************************

void Escena::dibujar()
{
	glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT ); // Limpiar la pantalla
   glEnable(GL_CULL_FACE);
   glEnable(GL_NORMALIZE);
   glDisable(GL_LIGHTING);
   glEnable(GL_SMOOTH);
	change_projection(1);
   change_observer();
   
   ejes.draw();
   
   if(luz){
      if(!glIsEnabled(GL_LIGHTING)){
         glEnable(GL_LIGHTING);
      }

      for(int i=0;i<8;i++){
         if(luces[i]!=nullptr && switchLuces[i])
            luces[i]->activar();
         else if(luces[i]!=nullptr && !switchLuces[i])
            glDisable(luces[i]->getID());
      }
      
      glShadeModel(GL_SMOOTH);
   }
   else{
      if(glIsEnabled(GL_LIGHTING))
         glDisable(GL_LIGHTING);
      glShadeModel(GL_FLAT);
   }

   glPushMatrix();
   glPointSize(6);
   switch (seleccionDibujo){
      case 1:
         glPushMatrix();
         glTranslatef(100,0,0);
         glScalef(25,25,25);
         mallas[0]->setColor(0,0,1);
         mallas[0]->setPosicion({100,0,0});
         mallas[0]->draw(metodoDibujado,puntos,lineas,solido,ajedrez);
         glPopMatrix();

         glPushMatrix();
         glTranslatef(-100,0,100);
         glScalef(25,25,25);
         mallas[1]->setColor(0,1,0);
         mallas[1]->setPosicion({-100,0,100});
         mallas[1]->draw(metodoDibujado,puntos,lineas,solido,ajedrez);
         glPopMatrix();
         
         glPushMatrix();
         glScalef(25.0,25.0,25.0);
         mallas[2]->setColor(1,0,0);
         mallas[2]->setPosicion({0,0,0});
         mallas[2]->draw(metodoDibujado,puntos,lineas,solido,ajedrez);
         glPopMatrix();

         glPushMatrix();
         glTranslatef(-100,0,0);
         glScalef(3,3,3);
         mallas[3]->setColor(1,0,1);
         mallas[3]->setPosicion({-100,0,0});
         mallas[3]->draw(metodoDibujado,puntos,lineas,solido,ajedrez);
         glPopMatrix();

         glPushMatrix();
         glTranslatef(-100,0,-100);
         glScalef(3,3,3);
         mallas[4]->setColor(0,0,1);
         mallas[4]->setPosicion({-100,0,-100});
         mallas[4]->draw(metodoDibujado,puntos,lineas,solido,ajedrez);
         glPopMatrix();
         
         glPushMatrix();
         glTranslatef(100,0,100);
         glScalef(5,5,5);
         mallas[5]->setColor(1,0,1);
         mallas[5]->setPosicion({100,0,100});
         mallas[5]->draw(metodoDibujado,puntos,lineas,solido,ajedrez);
         glPopMatrix();
         break;
      case 2:
         glEnable(GL_TEXTURE_2D);
         glPushMatrix();
         mallas[6]->setColor(1,0,0);
         mallas[6]->draw(metodoDibujado,puntos,lineas,solido,ajedrez);
         glPopMatrix();
         
         glTranslatef(-100,0,100);
         glScalef(25,25,25);
         mallas[1]->setColor(0,1,0);
         mallas[1]->setPosicion({-100,0,100});
         mallas[1]->draw(metodoDibujado,puntos,lineas,solido,ajedrez);

         glDisable(GL_TEXTURE_2D);
         break;
      case 3:
         glPushMatrix();
         mallas[7]->setColor(1,0,0);
         mallas[7]->setPosicion({0,0,0});
         mallas[7]->draw(metodoDibujado,puntos,lineas,solido,ajedrez);
         glPopMatrix();
         break;
   }
   glPopMatrix();
}



//**************************************************************************
// Funcion que anima automaticamente el modelo
//**************************************************************************

void Escena::animarModeloJerarquico(){
   if(animacionAutomatica)
      mallas[7]->animacionAutomatica();

   if(animacionLuz)
      luces[0]->animarLuz();
   
   
}


//**************************************************************************
// Funcion que controla si se ha pulsado alguna tecla del raton
//**************************************************************************

void Escena::clickRaton(int boton, int estado, int x, int y){
   switch(boton){
      case GLUT_RIGHT_BUTTON:
         if(estado == GLUT_DOWN){
            boton = false;
            xraton = x;
            yraton = y;
         }
         break;
      case GLUT_LEFT_BUTTON:
         boton = true;
         break;
      case 3:
         if(estado == GLUT_UP)
            camaras[numCamaraActiva]->zoom(1);
         break;
      case 4:
         if(estado == GLUT_DOWN)
            camaras[numCamaraActiva]->zoom(-1);
         break;
   }


}


//**************************************************************************
// Funcion que controla si se ha pulsado el boton derecho
//**************************************************************************
void Escena::ratonMovido(int x, int y){
   if(!boton){
      camaras[numCamaraActiva]->rotarXPrimeraPersona((x-xraton)*0.1);
      camaras[numCamaraActiva]->rotarYPrimeraPersona((y-yraton)*0.1);
      xraton = x;
      yraton = y;
   }
   else{
      xpixel = x;
      ypixel = y;
   }

}


void Escena::seleccionarObjetivo(int obj){
   if(objsel != obj){
      objsel = obj;
      camaras[numCamaraActiva]->setAt(mallas[obj]->getPosicion());
   }
   else{
      objeto = -1;
      camaras[numCamaraActiva]->setAt({0,0,0});
   }
}

//**************************************************************************
// Funcion que controla la seleccion de objetos de la escena
//**************************************************************************

void Escena::dibujaSeleccion(){
   glDisable(GL_DITHER);
   glDisable(GL_LIGHTING);
   puntos = false, lineas = false, solido = true, ajedrez = false, luz = false;

   vector<Tupla3f> coloresAux;

   for(int i=0;i<8;i++){
      coloresAux.push_back(mallas[i]->getColor());
   }

   float j=0.0;
   for(int i=0;i<8;i++){
      mallas[i]->setColor(j,0,0);
      j+=0.1;
   }

   GLint viewport[4];
   GLubyte pixel[3];

   glGetIntegerv(GL_VIEWPORT,viewport);

   glReadPixels(xpixel,viewport[3]-ypixel,1,1,GL_RGB,GL_UNSIGNED_BYTE,(void *) pixel);


   if(round(pixel[0]*10)/10 == 0.0)
      seleccionarObjetivo(0);
   else if(round(pixel[0]*10)/10 == 0.1)
      seleccionarObjetivo(1);
   else if(round(pixel[0]*10)/10 == 0.2)
      seleccionarObjetivo(2);
   else if(round(pixel[0]*10)/10 == 0.3)
      seleccionarObjetivo(3);
   else if(round(pixel[0]*10)/10 == 0.4)
      seleccionarObjetivo(4);
   else if(round(pixel[0]*10)/10 == 0.5)
      seleccionarObjetivo(5);
   else if(round(pixel[0]*10)/10 == 0.6)
      seleccionarObjetivo(6);
   else if(round(pixel[0]*10)/10 == 0.7)
      seleccionarObjetivo(7);

   //Volvemos a ponerle los colores
   for(int i=0;i<8;i++){
      mallas[i]->setColor(coloresAux[i](0),coloresAux[i](1),coloresAux[i](2));
   }

}


//**************************************************************************
//
// función que se invoca cuando se pulsa una tecla
// Devuelve true si se ha pulsado la tecla para terminar el programa (Q),
// devuelve false en otro caso.
//
//**************************************************************************

bool Escena::teclaPulsada( unsigned char tecla, int x, int y )
{

   cout << "Tecla pulsada: '" << tecla << "'" << endl;
   bool salir=false;
   bool angulo;
   switch( toupper(tecla) )
   {
      case 'Q' :
         if (modoMenu!=NADA)
            modoMenu=NADA;            
         else {
            salir=true ;
         }
         break ;
      case 'O' :
         // ESTAMOS EN MODO SELECCION DE OBJETO
         modoMenu=SELOBJETO;
         cout<<"Entrando en modo selección objeto"<<endl; 
         break ;
      case 'V' :
         // ESTAMOS EN MODO SELECCION DE MODO DE VISUALIZACION
         modoMenu=SELVISUALIZACION;
         cout<<"Entrando en modo selección visualización"<<endl; 
         break ;
      case 'D' :
         // ESTAMOS EN MODO SELECCION DE DIBUJADO
         modoMenu=SELDIBUJADO;
         cout<<"Entrando en modo selección dibujado"<<endl; 
         break ;
      case 'C':
         modoMenu = SELCAM;
         cout<<"Entrando en modo selección de cámaras"<<endl; 
         break;
      case 'Y':
         if(modoMenu == SELOBJETO)
            seleccionDibujo = 1;
         break;
      case 'N':
         if(modoMenu == SELOBJETO)
            seleccionDibujo = 2;
            cout<<"Dibujando objetos texturas"<<endl; 
         break;
      case 'X':
         if(modoMenu == SELOBJETO)
            seleccionDibujo = 3;
            cout<<"Dibujando modelo jerárquico"<<endl; 
         break;
      case 'P':
         if(modoMenu == SELVISUALIZACION && !luz){
            luz = false;
            puntos = !puntos;
            cout<<"Entrando en modo puntos"<<endl; 
         }
         else if(modoMenu == SELVISUALIZACION && luz)
            animacionLuz = true;
            cout<<"Animando luz puntual automáticamente"<<endl; 
         break;
      case 'L':
         if(modoMenu == SELVISUALIZACION){
            luz = false;
            lineas = !lineas;
            cout<<"Entrando en modo lineas"<<endl; 
         }
         break;
      
      case 'S':
         if(modoMenu == SELVISUALIZACION){
            luz = false;
            solido = !solido;
            cout<<"Entrando en modo caras"<<endl; 
         }
         break;
      
      case 'A':
         if(modoMenu == NADA){
            if(!animacionAutomatica){
               modoMenu = SELANIMAUTO;
               animacionAutomatica = true;
               mallas[7]->setPosicion({-700,700,-700});
               cout<<"Animando modelo jerárquico automáticamente"<<endl; 
            }
         }
         else if(modoMenu == SELANIMAUTO){
            modoMenu = NADA;
            cout<<"Animación automatica desactivada"<<endl; 
            animacionAutomatica = false;
         }
         else if(modoMenu == SELVISUALIZACION && !luz){
            luz = false;
            ajedrez = !ajedrez;
            cout<<"Entrando en modo ajedrez"<<endl; 
         }
         else if(modoMenu == SELVISUALIZACION && luz){
            angulo = true;
            cout<<"Seleccion del angulo ALPHA"<<endl; 
         }
         break;
         
      
      case 'M':
         if(modoMenu == NADA){
            modoMenu = SELANIMMAN;
            animacionAutomatica = false;
            cout<<"Selección de animación manual del modelo jerárquico"<<endl; 
         }
         break;
         
      case 'B':
         if(luz){
            angulo = false;
            cout<<"Entrando en modo selección objeto"<<endl; 
         }
         break;
      
      case 'T':
         if(modoMenu == SELVISUALIZACION){
            mallas[2]->switchTapas(tapas);
            mallas[4]->switchTapas(tapas);
            cout<<"Activando/Desactivando tapas"<<endl; 
         }
         break;
      
      case 'I':
         if(modoMenu == SELVISUALIZACION){
            luz = !luz;
            cout<<"Activando modo iluminación"<<endl; 
         }
      case '0':
         if(modoMenu == SELVISUALIZACION && luz){
            switchLuces[0] = !switchLuces[0];
            if(switchLuces[0])
               cout<<"Activando luz 0"<<endl; 
            else
               cout<<"Desactivando luz 0"<<endl; 
         }
         else if(modoMenu == SELANIMMAN){
            grado = 0;
            cout<<"Seleccion del grado 0"<<endl; 
         }
            else if(modoMenu == SELCAM){
               numCamaraActiva = 0;
               if(camaras[numCamaraActiva] != nullptr){
                  cout<<"Seleccion de cámara "<<numCamaraActiva<<endl; 
                  change_observer();
                  change_projection(1);
               }
               else
                  cerr<<"Cámara "<<numCamaraActiva<<" no creada"<<endl;
         }
         break;
      
      case '1' :
         if(modoMenu == SELDIBUJADO){
            metodoDibujado = false;
            cout<<"Dibujando en modo inmediato"<<endl; 
         }
         else if(modoMenu == SELVISUALIZACION && luz){
            switchLuces[1] = !switchLuces[1];
            if(switchLuces[1])
               cout<<"Activando luz 1"<<endl; 
            else
               cout<<"Desactivando luz 1"<<endl; 
         }
         else if(modoMenu == SELANIMMAN){
            grado = 1;
            cout<<"Seleccion del grado 1"<<endl; 
         }
            else if(modoMenu == SELCAM){
               numCamaraActiva = 1;
               if(camaras[numCamaraActiva] != nullptr){
                  cout<<"Seleccion de cámara "<<numCamaraActiva<<endl; 
                  change_observer();
                  change_projection(1);
               }
               else
                  cerr<<"Cámara "<<numCamaraActiva<<" no creada"<<endl;
         }
         break;
      
      case '2':
         if(modoMenu == SELDIBUJADO){
            metodoDibujado = true;
            cout<<"Dibujando en modo diferido"<<endl; 
         }
         else if(modoMenu == SELVISUALIZACION && luz){
            switchLuces[2] = !switchLuces[2];
            if(switchLuces[0])
               cout<<"Activando luz 2"<<endl; 
            else
               cout<<"Desactivando luz 2"<<endl; 
         }
         else if(modoMenu == SELANIMMAN){
            grado = 2;
            cout<<"Seleccion del grado 2"<<endl; 
         }
            else if(modoMenu == SELCAM){
               numCamaraActiva = 2;
               if(camaras[numCamaraActiva] != nullptr){
                  cout<<"Seleccion de cámara "<<numCamaraActiva<<endl; 
                  change_observer();
                  change_projection(1);
               }
               else
                  cerr<<"Cámara "<<numCamaraActiva<<" no creada"<<endl;
         }
         break;
      
      case '3':
            if(modoMenu == SELVISUALIZACION && luz){
               switchLuces[3] = !switchLuces[3];
               if(switchLuces[3])
                  cout<<"Activando luz 3"<<endl; 
               else
                  cout<<"Desactivando luz 3"<<endl; 
            }
            else if(modoMenu == SELANIMMAN){
               grado = 3;
               cout<<"Seleccion del grado 3"<<endl; 
            }
            else if(modoMenu == SELCAM){
               numCamaraActiva = 3;
               if(camaras[numCamaraActiva] != nullptr){
                  cout<<"Seleccion de cámara "<<numCamaraActiva<<endl; 
                  change_observer();
                  change_projection(1);
               }
               else
                  cerr<<"Cámara "<<numCamaraActiva<<" no creada"<<endl;
         }
         break;
      
      case '4':
            if(modoMenu == SELVISUALIZACION && luz){
               switchLuces[4] = !switchLuces[4];
               if(switchLuces[4])
                  cout<<"Activando luz 4"<<endl; 
               else
                  cout<<"Desactivando luz 4"<<endl; 
            }
            else if(modoMenu == SELANIMMAN){
               grado = 4;
               cout<<"Seleccion del grado 4"<<endl; 
            }
            else if(modoMenu == SELCAM){
               numCamaraActiva =4;
               if(camaras[numCamaraActiva] != nullptr){
                  cout<<"Seleccion de cámara "<<numCamaraActiva<<endl; 
                  change_observer();
                  change_projection(1);
               }
               else
                  cerr<<"Cámara "<<numCamaraActiva<<" no creada"<<endl;
         }
         break;
      
      case '5':
            if(modoMenu == SELVISUALIZACION && luz){
               switchLuces[5] = !switchLuces[5];
               if(switchLuces[5])
                  cout<<"Activando luz 5"<<endl; 
               else
                  cout<<"Desactivando luz 5"<<endl; 
            }
            else if(modoMenu == SELANIMMAN){
               grado = 5;
               cout<<"Seleccion del grado 5"<<endl; 
            }
            else if(modoMenu == SELCAM){
               numCamaraActiva = 5;
               if(camaras[numCamaraActiva] != nullptr){
                  cout<<"Seleccion de cámara "<<numCamaraActiva<<endl; 
                  change_observer();
                  change_projection(1);
               }
               else
                  cerr<<"Cámara "<<numCamaraActiva<<" no creada"<<endl;
         }
         break;
      
      case '6':
            if(modoMenu == SELVISUALIZACION && luz){
               switchLuces[6] = !switchLuces[6];
               if(switchLuces[6])
                  cout<<"Activando luz 6"<<endl; 
               else
                  cout<<"Desactivando luz 6"<<endl; 
            }
            else if(modoMenu == SELCAM){
               numCamaraActiva = 6;
               if(camaras[numCamaraActiva] != nullptr){
                  cout<<"Seleccion de cámara "<<numCamaraActiva<<endl; 
                  change_observer();
                  change_projection(1);
               }
               else
                  cerr<<"Cámara "<<numCamaraActiva<<" no creada"<<endl;
         }
         break;
      
      case '7':
            if(modoMenu == SELVISUALIZACION && luz){
               switchLuces[7] = !switchLuces[7];
               if(switchLuces[7])
                  cout<<"Activando luz 7"<<endl; 
               else
                  cout<<"Desactivando luz 7"<<endl; 
            }
            else if(modoMenu == SELANIMMAN){
               grado = 7;
               cout<<"Seleccion del grado 7"<<endl; 
            }
            else if(modoMenu == SELCAM){
               numCamaraActiva = 7;
               if(camaras[numCamaraActiva] != nullptr){
                  cout<<"Seleccion de cámara "<<numCamaraActiva<<endl; 
                  change_observer();
                  change_projection(1);
               }
               else
                  cerr<<"Cámara "<<numCamaraActiva<<" no creada"<<endl;
         }
         break;
      
      case '>':
         if(luz && angulo && modoMenu == SELVISUALIZACION){
            this->luces[1]->variarAnguloAlpha(-1.0);
            cout<<"Variando > del angulo alfa"<<endl; 
         }
         else if(luz && !angulo && modoMenu == SELVISUALIZACION){
            this->luces[1]->variarAnguloBeta(-1.0);
            cout<<"Variando > del angulo beta"<<endl;  
         }
         break;
      
      case '<':
         if(luz && angulo && modoMenu == SELVISUALIZACION){
            this->luces[1]->variarAnguloAlpha(1.0);
            cout<<"Variando < del angulo alfa"<<endl;  
         }
         else if(luz && !angulo && modoMenu == SELVISUALIZACION){
            this->luces[1]->variarAnguloBeta(1.0);
            cout<<"Variando < del angulo beta"<<endl;  
         }
         break;
      
      case '+':
         if(modoMenu == SELVISUALIZACION){
            if(!animacionAutomatica){
               inc = 1.0;
               mallas[7]->animacionManual(grado,inc);
            }
         }
         break;
      
      case '-':
         if(modoMenu == SELVISUALIZACION){
            if(!animacionAutomatica){
               inc = -1.0;
               mallas[7]->animacionManual(grado,inc);
            }
         }
         break;
      

   }
   return salir;
}
//**************************************************************************

void Escena::teclaEspecial( int Tecla1, int x, int y )
{
   switch ( Tecla1 )
   {
	   case GLUT_KEY_LEFT:
         camaras[numCamaraActiva]->rotarXExaminar(-1);
         break;
	   case GLUT_KEY_RIGHT:
         camaras[numCamaraActiva]->rotarXExaminar(1);
         break;
	   case GLUT_KEY_UP:
         camaras[numCamaraActiva]->rotarYExaminar(1) ;
         break;
	   case GLUT_KEY_DOWN:
         camaras[numCamaraActiva]->rotarYExaminar(-1) ;
         break;
	   case GLUT_KEY_PAGE_UP:
         Observer_distance *=1.2 ;
         break;
	   case GLUT_KEY_PAGE_DOWN:
         Observer_distance /= 1.2 ;
         break;
	}

}

//**************************************************************************
// Funcion para definir la transformación de proyeccion
//
// ratio_xy : relacción de aspecto del viewport ( == ancho(X) / alto(Y) )
//
//***************************************************************************

void Escena::change_projection( const float ratio_xy )
{
   glMatrixMode( GL_PROJECTION );
   glLoadIdentity();

   if(camaras[numCamaraActiva]!=nullptr)
      camaras[numCamaraActiva]->setProyeccion();
}
//**************************************************************************
// Funcion que se invoca cuando cambia el tamaño de la ventana
//***************************************************************************

void Escena::redimensionar( int newWidth, int newHeight )
{
   Width  = newWidth/10;
   Height = newHeight/10;
   change_projection( float(newHeight)/float(newWidth) );
   glViewport( 0, 0, newWidth, newHeight );
}

//**************************************************************************
// Funcion para definir la transformación de vista (posicionar la camara)
//***************************************************************************

void Escena::change_observer()
{
   // posicion del observador
   glMatrixMode(GL_MODELVIEW);
   glLoadIdentity();

   if(camaras[numCamaraActiva]!=nullptr)
     camaras[numCamaraActiva]->setObserver();
}

