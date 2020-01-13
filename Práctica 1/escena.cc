#include "aux.h"     // includes de OpenGL/glut/glew, windows, y librería std de C++
#include "escena.h"

//**************************************************************************
// CONSTRUCTORES
//**************************************************************************

//**************************************************************************
// constructores de objetos
//**************************************************************************
void Escena::creacionObjetos(){
   //Creacion de objetos
   //Tetrahedro
   tetraedro = new Tetraedro();
   //Cubo
   cubo = new Cubo();
   //Peon
   peon = new ObjRevolucion("plys/peon.ply",30,tapas,tapas);
   //Hormiga
   hormiga = new ObjPLY("plys/ant.ply");
   //Cilindro
   cilindro = new Cilindro(50,25,10);
   //Esfera
   esfera = new Esfera(50,50,10);
   //Cuadro
   cuadro = new Cuadro(100);
   //AlaX
   alaX = new AlaX();
   //Suelo
   suelo = new Cuadro(2500);

   skybox = new Skybox();

}
//**************************************************************************
// constructores de auxiliares
//**************************************************************************
void Escena::creacionAuxiliares(){
   //Creacion de materiales
   plata = Material({0.19225,0.19225,0.19225, 1.0},{0.50754, 0.50754,0.50754, 1.0},{0.508273, 0.508273,0.508273, 1.0},128.0);
   oro = Material({0.24725,0.1995, 0.0745, 0.6},{0.75164, 0.60648, 0.22648	, 1.0},{0.628281, 0.555802, 0.366065, 0.1},128.0);
   bronce = Material({0.2125,0.1275,0.054,1.0},{0.714, 0.4284, 0.18144,1.0},{0.393548, 0.271906, 0.166721, 1.0},0.2);
   negro = Material({0.0,0.0,0.0,1.0},{0.0,0.0,0.0,1.0},{0.50,0.50,0.50,1.0},128*0.25);

   cristal = Material({0.0f,0.0f,0.0f,1.0f},{0.55f,0.55f,0.55f,1.0f},{0.70f,0.70f,0.70f,1.0f},32.0f); 
   blanco = Material({ 0.0f,0.0f,0.0f,1.0f },{ 0.55f,0.55f,0.55f,1.0f},{0.70f,0.70f,0.70f,1.0f },32.0f); 
   rojo = Material({ 0.0f,0.0f,0.0f,1.0f },{ 0.5f,0.0f,0.0f,1.0f},{0.7f,0.6f,0.6f,1.0f },32.0f); 
   azul = Material({0.105882f, 0.058824f, 0.113725f, 1.0f},{0.427451f, 0.470588f, 0.541176f, 1.0f},{0.333333f, 0.333333f, 0.521569f, 1.0f},9.84615f); 

   //Creacion de texturas
   madera = Textura("archivosP5/text-madera.jpg",1);
   lata = Textura("archivosP5/text-lata-1.jpg",2);
   hierba = Textura("archivosP5/text-hierba.jpg",3);
   planeta = Textura("archivosP5/textura-planeta-tierra.jpg",4);
   poster = Textura("archivosP5/text-cuadro.jpg",5);
   cielo = Textura("archivosP5/text-cielo.jpg",6);

   //Creacion de luces
   luces[0] = new LuzPosicional(GL_LIGHT1,{-100, 100, 100},{0.0,0.0,0.0,1.0},{1.0,1.0,1.0,1.0},{1.0,1.0,1.0,1.0});
   luces[1] = new LuzDireccional(GL_LIGHT2,{0, 0},{0.0, 0.0, 0.0, 1.0}, {1.0, 1.0, 1.0, 1.0}, {1.0, 1.0, 1.0, 1.0});

   //Creacion de cámaras
   camaras[0] = new Camara(1,{200,200,200},{0,0,0},{0,1,0},100,100);
   camaras[1] = new Camara(2,{500,300,100}, {0,0,0},{0,1,0},500, 500);
   camaras[2] = new Camara(1,{200,200,0}, {0,0,0}, {0,1,0},100, 100);
   camaras[3] = new Camara(2, {-700,300,0}, {0,0,0}, {0,1,0},200, 200);
}

//**************************************************************************
// setcolors para los objetos y no tener que hacerlos en el draw
//**************************************************************************
void Escena::asignacionColores(){
   tetraedro->setColor(0,0,1);
   cubo->setColor(0,1,0);
   peon->setColor(1,0,0);
   hormiga->setColor(1,0,1);
   cilindro->setColor(0,0,1);
   esfera->setColor(1,0,1);
   cuadro->setColor(1,0,0);
   suelo->setColor(1,0,0);
   alaX->setColor({0.6,0.6,0.6},{0.8,0.8,0.8},{0.8,0,0},{0.1,0.1,0.1},{0.8,0,0},{0.8,0.8,0.8},{0.1,0.1,0.1},{0.5,0.5,0.5},{0.8,0.8,0.8},{0.1,0.1,0.1},{0,0,0.8});
   skybox->setColor(1.0,0,0);
}

//**************************************************************************
// setmaterial para los objetos y no tener que hacerlos en el draw
//**************************************************************************
void Escena::asignacionMateriales(){
   //Aplicacion de materiales
   tetraedro->setMaterial(bronce);
   cubo->setMaterial(plata);
   peon->setMaterial(plata);
   hormiga->setMaterial(bronce);
   cilindro->setMaterial(oro);
   esfera->setMaterial(bronce);
   cuadro->setMaterial(plata);
   alaX->setMaterialGeneral(cristal,blanco,rojo,negro,rojo,blanco,negro,plata,blanco,negro,azul);
   suelo->setMaterial(plata);
   skybox->setMaterial(bronce);

}
//**************************************************************************
// settextura para los objetos y no tener que hacerlos en el draw
//**************************************************************************
void Escena::asignacionTexturas(){
   //Aplicacion de texturas
   cuadro->setTextura(poster);
   cubo->setTextura(madera);
   cilindro->setTextura(lata);
   esfera->setTextura(planeta);
   skybox->setTextura(cielo);

   std::vector<Tupla2f> texturasSuelo;
   texturasSuelo.push_back({0,0});
   texturasSuelo.push_back({1000,0});
   texturasSuelo.push_back({0,1000});
   texturasSuelo.push_back({1000,1000});
   suelo->setCoordenadasTextura(texturasSuelo);
   suelo->setTextura(hierba);
}


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

   creacionObjetos();

   creacionAuxiliares();

   asignacionColores();

   asignacionMateriales();

   asignacionTexturas();

   //Modificando los parametros de visualizacion (por defecto SOLIDO)
   puntos = false, lineas = false, solido = true, ajedrez = false, luz = false;

   //Modificando los parametros de la camara activa
   numCamaraActiva = 0;

   //Modificando los parámetros para la animacion
   animacionAutomatica = animacionManual = animacionLuz = false;
   grado = -1;

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


//**************************************************************************
// ESCENA
//**************************************************************************

//**************************************************************************
// funcion que enciende las luces activas
//**************************************************************************
void Escena::crearLuces(){
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
}


//**************************************************************************
// funcion que dibuja los objetos con comandos de OpenGL
//**************************************************************************
void Escena::crearEscena(){
   glPushMatrix();
      glPointSize(6); 
         glPushMatrix();
         tetraedro->setPosicion({200,0,0});
         glScalef(25.0,25.0,25.0);
         tetraedro->draw(metodoDibujado,puntos,lineas,solido,ajedrez);
         glPopMatrix();

         glPushMatrix();
         peon->setPosicion({-100,50,0});
         glScalef(25.0,25.0,25.0);
         peon->draw(metodoDibujado,puntos,lineas,solido,ajedrez);
         glPopMatrix();

         glPushMatrix();
         hormiga->setPosicion({-100,0,0});
         glScalef(3,3,3);
         hormiga->draw(metodoDibujado,puntos,lineas,solido,ajedrez);
         glPopMatrix();

         if(luz)
            glEnable(GL_TEXTURE_2D);
         
         glPushMatrix();
         cuadro->setPosicion({200,100,0});
         cuadro->draw(metodoDibujado,puntos,lineas,solido,ajedrez);
         glPopMatrix();
         
         glPushMatrix();
         cubo->setPosicion({-100,0,100});
         glScalef(25,25,25);
         cubo->draw(metodoDibujado,puntos,lineas,solido,ajedrez);
         glPopMatrix();

         glPushMatrix();
         cilindro->setPosicion({-100,50,-100});
         glScalef(1.2,1.5,1.2);
         glRotatef(180,1,0,0);
         cilindro->draw(metodoDibujado,puntos,lineas,solido,ajedrez);
         glPopMatrix();

         glPushMatrix();
         esfera->setPosicion({100,0,100});
         glScalef(2,2,2);
         esfera->draw(metodoDibujado,puntos,lineas,solido,ajedrez);
         glPopMatrix();
         
         glDisable(GL_TEXTURE_2D);

         glEnable(GL_TEXTURE_2D);
         glPushMatrix();
         suelo->setPosicion({-suelo->getLado()/2,-18,suelo->getLado()/2});
         glRotatef(-90,1,0,0);
         suelo->draw(metodoDibujado,puntos,lineas,solido,ajedrez);
         glPopMatrix();

         glPushMatrix();
         glScalef(1000,1000,1000);
         skybox->draw(metodoDibujado,puntos,lineas,solido,ajedrez);
         glPopMatrix();

         glDisable(GL_TEXTURE_2D);

         glPushMatrix();
         alaX->draw(metodoDibujado,puntos,lineas,solido,ajedrez);
         glPopMatrix();
   glPopMatrix();
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

   if(xpixel!=-1 && ypixel != -1)
      dibujaSeleccion();
   glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );

   glEnable(GL_CULL_FACE);
   glEnable(GL_NORMALIZE);
   glDisable(GL_LIGHTING);
   glEnable(GL_SMOOTH);
	change_projection(1);
   change_observer();
   
   ejes.draw();

   crearLuces();

   crearEscena();
}



//**************************************************************************
// ANIMACION
//**************************************************************************

//**************************************************************************
// Funcion que anima automaticamente el modelo
//**************************************************************************
void Escena::animarModeloJerarquico(){
   if(animacionAutomatica)
      alaX->animacionAutomatica();

   if(animacionLuz)
      luces[0]->animarLuz();
}

//**************************************************************************
// RATON
//**************************************************************************

//**************************************************************************
// Funcion que controla si se ha pulsado alguna tecla del raton
//**************************************************************************

void Escena::clickRaton(int boton, int estado, int x, int y){
   switch(boton){
      case GLUT_RIGHT_BUTTON:
         if(estado == GLUT_DOWN){
            botonPulsado = true;
            xraton = x;
            yraton = y;
         }
         break;
      case GLUT_LEFT_BUTTON:
         if(estado == GLUT_DOWN){ 
            xpixel = x;
            ypixel = y;
         }
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
// Funcion que controla si se ha pulsado el boton derecho para decidir si se rota en primera persona o se rota entorno a un objeto
//**************************************************************************
void Escena::ratonMovido(int x, int y){
   if(botonPulsado){
      if(objetoSeleccionado){
         camaras[numCamaraActiva]->rotarXExaminar((x-xraton)*0.1);
         camaras[numCamaraActiva]->rotarYExaminar((y-yraton)*0.1);
      }
      else{
         camaras[numCamaraActiva]->rotarXPrimeraPersona((x-xraton)*0.1);
         camaras[numCamaraActiva]->rotarYPrimeraPersona((y-yraton)*0.1);
      }
      xraton = x;
      yraton = y;
   }
}

//**************************************************************************
// SELECCION
//**************************************************************************

//**************************************************************************
// Funcion que cambia los colores de los objetos para hacer posible la seleccion
//**************************************************************************
void Escena::asignarColoresSeleccion(){
   tetraedro->setColor(0,0,0);
   cubo->setColor(0,0,1);
   peon->setColor(0,1,0);
   hormiga->setColor(0,1,1);
   cilindro->setColor(1,0,0);
   esfera->setColor(1,0,1);
   cuadro->setColor(1,1,0);
   alaX->setColor({1,1,1},{1,1,1},{1,1,1},{1,1,1},{1,1,1},{1,1,1},{1,1,1},{1,1,1},{1,1,1},{1,1,1},{1,1,1});
}


//**************************************************************************
// Funcion que selecciona el objetivo de la camara | Si el objeto al que esta fijando vuelve a ser pulsado, vuelve a fijarse en el eje de coordenadas
//**************************************************************************
void Escena::seleccionarObjetivo(int obj,Malla3D* malla){
   switch(obj){
      case 0:
         cout<<"Ha seleccionado el tetraedro"<<endl;
         break;
      case 1:
         cout<<"Ha seleccionado el cubo"<<endl;
         break;
      case 2:
         cout<<"Ha seleccionado el peon"<<endl;
         break;
      case 3:
         cout<<"Ha seleccionado la hormiga"<<endl;
         break;
      case 4:
         cout<<"Ha seleccionado el cilindro"<<endl;
         break;
      case 5:
         cout<<"Ha seleccionado la esfera"<<endl;
         break;
      case 6:
         cout<<"Ha seleccionado el cuadro"<<endl;
         break;
      case 7:
         cout<<"Ha seleccionado el Ala X"<<endl;
         break;
      case -1:
         cout<<"Volviendo a posicion original"<<endl;
         break;
   }

   //Cuando seleccionas un objeto que no sea el suelo o el skybox
   if(objsel != obj && obj != -1){
      objsel = obj;
      for(int i=0;i<7;i++){
         if(camaras[i]!=nullptr)
            camaras[i]->setAt(malla->getPosicion());
      }
      objetoSeleccionado = true;
   }
   //Cuando deseleccionas pulsando en otro sitio que no sea el objeto seleccionado (el suelo o el skybox)
   else if(obj == -1){
      objsel = -1;
      for(int i=0;i<7;i++){
         if(camaras[i] != nullptr)
            camaras[i]->volverAtAnterior();
      }
      objetoSeleccionado = false;
   }
   //Cuando deseleccionas pulsando en el mismo objeto seleccionado
   else{
      objsel = -1;
      for(int i=0;i<7;i++){
         if(camaras[i] != nullptr)
            camaras[i]->volverAtAnterior();
      }
      objetoSeleccionado = false;
   }
}

//**************************************************************************
// Funcion que lee los pixeles en funcion del click izquierdo del raton y manda a fijar un objeto
//**************************************************************************
void Escena::asignarPixeles(){
   GLint viewport[4];
   GLubyte pixel[3];

   glGetIntegerv(GL_VIEWPORT,viewport);

   glReadPixels(xpixel,viewport[3]-ypixel,1,1,GL_RGB,GL_UNSIGNED_BYTE,(void *) pixel);

   //printf("%d %d %d\n",pixel[0],pixel[1],pixel[2]);
   if(pixel[0] == 0 && pixel[1] == 0 && pixel[2] == 0)
      seleccionarObjetivo(0,tetraedro);
   else if(pixel[0] == 0 && pixel[1] == 0 && pixel[2] == 255)
      seleccionarObjetivo(1,cubo);
   else if(pixel[0] == 0 && pixel[1] == 255 && pixel[2] == 0)
      seleccionarObjetivo(2,peon);
   else if(pixel[0] == 0 && pixel[1] == 255 && pixel[2] == 255)
      seleccionarObjetivo(3,hormiga);
   else if(pixel[0] == 255 && pixel[1] == 0 && pixel[2] == 0)
      seleccionarObjetivo(4,cilindro);
   else if(pixel[0] == 255 && pixel[1] == 0 && pixel[2] == 255)
      seleccionarObjetivo(5,esfera);
   else if(pixel[0] == 255 && pixel[1] == 255 && pixel[2] == 0)
      seleccionarObjetivo(6,cuadro);
   else if(pixel[0] == 255 && pixel[1] == 255 && pixel[2] == 255)
      seleccionarObjetivo(7,alaX);
   else
      seleccionarObjetivo(-1,suelo);
   
}

//**************************************************************************
// Funcion que controla la seleccion de objetos de la escena
//**************************************************************************
void Escena::dibujaSeleccion(){
   glDisable(GL_DITHER);
   glDisable(GL_LIGHTING);

   std::vector<bool>estadoAnterior= {puntos,lineas,solido,ajedrez,luz,metodoDibujado};
   puntos = false, lineas = false, solido = true, ajedrez = false, luz = false, metodoDibujado = false;

   //Cambiamos los colores
   asignarColoresSeleccion();
   
   //Creamos la escena con los colores
   crearEscena();

   //Deducimos cual es el pixel en el que ha hecho click
   asignarPixeles();

   //Volvemos a ponerle los colores
   asignacionColores();
   xpixel = -1; ypixel = -1;
   
   puntos = estadoAnterior[0];
   lineas = estadoAnterior[1];
   solido = estadoAnterior[2];
   ajedrez = estadoAnterior[3];
   luz = estadoAnterior[4];
   metodoDibujado = estadoAnterior[5];
}


//**************************************************************************
// TECLAS
//**************************************************************************

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
               alaX->setPosicion({-700,700,-700});
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
            cilindro->switchTapas(tapas);
            peon->switchTapas(tapas);
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
               alaX->animacionManual(grado,inc);
            }
         }
         break;
      
      case '-':
         if(modoMenu == SELVISUALIZACION){
            if(!animacionAutomatica){
               inc = -1.0;
               alaX->animacionManual(grado,inc);
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
         camaras[numCamaraActiva]->rotarYExaminar(-1) ;
         break;
	   case GLUT_KEY_DOWN:
         camaras[numCamaraActiva]->rotarYExaminar(1) ;
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
// CÁMARAS
//**************************************************************************

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
