#pragma once

#include "include/Globals.h"

using namespace std;

/**********************************************************
 *
 * VARIABLES DECLARATION
 *
 *********************************************************/

// The width and height of your window, change them as you like
int screen_width=640;
int screen_height=480;

// Absolute rotation values (0-359 degrees) and rotation increments for each frame
double rotation_x=0, rotation_x_increment=0.1;
double rotation_y=0, rotation_y_increment=0.05;
double rotation_z=0, rotation_z_increment=0.03;

//Now the object is generic, the cube has annoyed us a little bit, or not?
obj_type object;

double escala = 0.015f;




int frameCount = 0; //  The number of frames
float fps = 0; //  Number of frames per second
int currentTime = 0, previousTime = 0; //  currentTime - previousTime is the time elapsed between every call of the Idle function

int show_menu = 0; //1 se muestra el menu principal, 0 empieza el juego

GLfloat rotZ = 0.0f; // Rotate screen on z axis
GLfloat posX = 0.0f; //posicion del vehiculo eje X
GLfloat posY = 0.0f; //posicion del vehiculo eje Y

int level = 1; //nivel de juego (acelera el juego a medida que aumenta)
int points = 0; //puntaje
int multiplier = 1; //multiplicador del puntaje

char textBuffer[30];

GLfloat velocidad_movil = 0.1f;
GLfloat velocidad_paredes = 0.1f;

GLfloat extra_pos_x = 0.0f;
GLfloat extra_pos_y = 0.0f;

double extra_color_red = 0.0;
double extra_color_green = 0.0;
double extra_color_blue = 0.0;

float dist = 0.0;

int extra_tiempo = 0;
int extra_activo = 0;
int tiempo_extra_activo = 0;
int bandera_extra_activo = 0;
int invensibilidad = 0;
int vidas_jugador = 3;
int puntos_jugador = 0;

typedef struct
{
    float x;
    float y;
    float z;
} geoPoint;

typedef struct
{
    float a;
    float b;
    float c;
    float d;
} plane;

typedef struct
{
    GLubyte *dibujo;        // Un puntero a los datos de la imagen
    GLuint	bpp;		// bpp significa bits per pixel (bits por punto) es la calidad en palabras sensillas
    GLuint largo;		// Largo de la textura
    GLuint ancho;		// Ancho de la textura
    GLuint ID;		// ID de la textura, es como su nombre para opengl
} textura;

/* AUDIO */
SoundManager soundManager;

/* TEXTURAS */
textura arena;
textura muro;
textura agua;
textura horizonte;

void cuadrado(double);
double posEnLineaRecta(void);
float distancePointPlane(geoPoint,plane);
plane planeEquation(geoPoint,geoPoint,geoPoint);
void square2d(double,double,double,double);
void figura(int,double);
void inicializarExtra(void);
void drawString(char*,float,float,float);
void tableroUsuario(double,double,double);
void circle2d(double);
void init(void);
void pelotitasExtrasAnimacion(double);
void probabilidadExtra(void);
void generarExtras(void);
int detectarColisionExtras(void);
void manejadorExtras(void);
void dibujarEjesCoordenadas(void);
void dibujarNave(double);
void reducirAnguloEntre0y360(void);
void display(void);
void reshape (int,int);
void keyboard (unsigned char,int,int);
void specialKey(int,int,int);
static void idle(void);
int cargarTGA(char *,textura *);
void loadObj(char *);
void menu(void);
void calculateFPS(void);
double getXrel(double,double,double);
double getYrel(double,double,double);

int cargarTGA( char *nombre, textura *imagen)
{
    GLubyte		cabezeraTGA[12]= {0,0,2,0,0,0,0,0,0,0,0,0};		// Cabezera de un tga sin compresion
    GLubyte     compararTGA[12];                                        // Aca vamos a comprar la cabezera
    GLubyte		cabezera[6];						// Los 6 bytes importantes
    GLuint		bytesporpunto;						// Cuantos bytes hay por punto
    GLuint		tamanoimagen;						// Aca guardaremos el tamaño de la imagen
    GLuint		temp,i;							// Variable temporal, y una para usar con el for
    GLuint		tipo=GL_RGBA;						// Nuestro typo por defecto, lo veremos mas abajo

    FILE * archivo = fopen(nombre, "rb+");	// Cargamos nuestro archivo en memoria

    if( archivo == NULL ||			// Existe nuestro archivo??
            fread(compararTGA,1,sizeof(compararTGA),archivo)!=sizeof(compararTGA)  ||      // Hay 12 bytes para leer??
            memcmp(cabezeraTGA,compararTGA,sizeof(compararTGA))!=0		||	// Son iguales??
            fread(cabezera,1,sizeof(cabezera),archivo)!=sizeof(cabezera))
    {
        if(archivo==NULL)
        {
            printf("No se encontro el archivo %s\n",nombre);
            return 0;		// No se abrio el archivo
        }
        else
        {
            if(fread(compararTGA,1,sizeof(compararTGA),archivo)!=sizeof(compararTGA))
            {
                printf("Hay 12 bytes para leer?? %s\n",nombre);
                return 0;		// No se abrio el archivo
            }
            else
            {
                if(memcmp(cabezeraTGA,compararTGA,sizeof(compararTGA))!=0)
                {
                    printf("Son iguales?? %s\n",nombre);
                    return 0;		// No se abrio el archivo
                }
                else
                {
                    if(fread(cabezera,1,sizeof(cabezera),archivo)!=sizeof(cabezera))
                    {
                        printf("Opcion ultima?? %s\n",nombre);
                        return 0;		// No se abrio el archivo
                    }
                    else
                    {
                        fclose(archivo);
                        return 0;
                    }
                }
            }

        }
    }
    /* Ahora hay que leer la cabezera del archivo, para saber cuanto es el largo, ancho, y los bytes por puntos,
    para eso aca hay una ilustracion de la cabezera :
    6 bytes -> xxxxxxx xxxxxxx xxxxxxx xxxxxxx xxxxxxx xxxxxxx
    	   |--- Largo ---| |---Ancho-----| |-bpp-|
    El dato del largo se guarda en el cabezera[0] y cabezera[1], para leerlo hay que multiplicar cabezera[0] por 256 y 	sumarselo a cabezera[1], para leer ancho y bpp es el mismo procedimiento */
    imagen->largo=256*cabezera[1]+ cabezera[0];
    imagen->ancho=256*cabezera[3]+ cabezera[2];

    /* Ahora vemos si hay datos no validos, como largo o ancho iguales menores a 0 o iguales a 0 */
    if( imagen->largo <= 0 ||	// Largo mayor que 0??
            imagen->ancho <= 0 ||	// Ancho mayor que 0??
            (cabezera[4]!=24 && cabezera[4]!=32))  	// bpp es 24 o 32?? (solo se cargan 24 y 32 bpp)
    {
        printf("Datos invalidos\n");
        fclose(archivo);
        return 0;
    }
    imagen->bpp=cabezera[4];	// Aca se guardan los bits por punto
    bytesporpunto=cabezera[4]/8;	// Aca los bytes por punto (1 byte = 8 bits)
    tamanoimagen=imagen->largo * imagen->ancho * bytesporpunto;      // Esta es la memoria que nesecitaremos para guardar los datos de la textura
    /*Ahora reservamos espacio en memoria para nuestra textura, luego leemos la textura del archivo */
    imagen->dibujo = (GLubyte *)malloc(tamanoimagen);	// Reservamos la memoria necesaria para nuestra textura
    if(imagen->dibujo== NULL ||		// Se logro reservar la memoria???
            fread(imagen->dibujo, 1, tamanoimagen, archivo) != tamanoimagen )  	// Se lee, y se comprueba que lo leido es de la misma longitud que la asignada a a dibujo.
    {
        if(imagen->dibujo != NULL)
        {
            printf("Error leyendo imagen\n");
            free(imagen->dibujo);
        }
        else printf("Error asignando memoria\n");
        fclose(archivo);
        return 0;
    }
    /* El formato tga guarda las imagenes en BGR, y opengl usa RGB,por lo cambiamos de lugares */
    for(i=0; i< (int)tamanoimagen; i+=bytesporpunto)
    {
        temp=imagen->dibujo[i];				// Guardamos el primer valor
        imagen->dibujo[i] = imagen->dibujo[i + 2];	// Asignamos el nuevo primer valor
        imagen->dibujo[i + 2] = temp;			// Asignamos el ultimo valor
    }

    fclose (archivo);	// Cerramos el archivo

    /* Listo, terminamos con el codigo de carga, volvemos a opengl, ahora hay que asignarle a la textura un ID, luego 	decirle a opengl cuales son el largo, el ancho y los bpp */

    glGenTextures( 1 , &imagen[0].ID);    // Crea un ID para la textura, buscando un id que este vacio
    glBindTexture(GL_TEXTURE_2D, imagen[0].ID);       // Seleccionamos nuestra textura
    if(imagen->bpp ==24) tipo= GL_RGB;	// Si nuestra textura es de 24 bits, entonces se crea una textura rgb, sino una rgba
    /* Ahora creamos nuestra textura, entrando el largo, ancho y tipo */
    glTexImage2D(GL_TEXTURE_2D, 0, tipo, imagen[0].ancho, imagen[0].largo, 0, tipo, GL_UNSIGNED_BYTE, imagen[0].dibujo);
    /* Ahora le decimos a opengl como queremos que se vea nuestra textura, MAG_FILTER es cuando la textura es mas grande que el lugar donde la asignamos, y MIG_FILTER, es cuando la textura es mas pequeña que el lugar donde la asignamos, GL_LINEAR es para que se vea bien tanto cerca como lejos, pero ocupa bastante procesador. Otra opcion el GL_NEARES, que ocupa menos prosesador */
    glTexParameterf(GL_TEXTURE_2D,GL_TEXTURE_WRAP_S,GL_REPEAT);
    glTexParameterf(GL_TEXTURE_2D,GL_TEXTURE_WRAP_T,GL_REPEAT);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    return 1;	// Todo salio bien
}

float distancePointPlane(geoPoint p0, plane p)
{
    float distance = 0.0f;

    distance = abs( p.a * p0.x + p.b * p0.y + p.c * p0.z + p.d );
    distance = distance / sqrt( pow(p.a, 2) + pow(p.b, 2) + pow(p.c, 2) );
    return distance;
}

plane planeEquation(geoPoint p1, geoPoint p2, geoPoint p3)
{
    geoPoint v1 = {p1.x - p2.x, p1.y - p2.y, p1.z - p2.z};
    geoPoint v2 = {p3.x - p2.x, p3.y - p2.y, p3.z - p2.z};
    geoPoint n = { (v1.y * v2.z) - (p1.z * p2.y),
                   (p1.x * p2.z) - (p1.z * p2.x),
                   (p1.x * p2.y) - (p1.y * p2.x)
                 };

    geoPoint negN = {-n.x, -n.y, -n.z};

    plane p = {negN.x, negN.y, negN.z, (negN.x * -p1.x) + (negN.y * -p1.y) + (negN.z * -p1.z)};

    return p;
}

void drawGeoPoint(geoPoint p)
{
    if(DEBUG)
    {
        sprintf(textBuffer, "(%.2f,%.2f,%.2f)", p.x, p.y, p.z);
        glColor3f(1,1,1);
        drawString(textBuffer, p.x,p.y,p.z);
    }
}

void square2d(double x, double y, double z, double angle)
{

    glEnable(GL_TEXTURE_2D);
    // Muro
    glBindTexture(GL_TEXTURE_2D,muro.ID);
    glBegin(GL_QUADS);
    glTexCoord2f(-y,0);
    glVertex3f(x,-y,0);
    glTexCoord2f(-y,z);
    glVertex3f(x,-y,z);
    glTexCoord2f(y,z);
    glVertex3f(x,y,z);
    glTexCoord2f(y,0);
    glVertex3f(x,y,0);
    glEnd();
    glDisable(GL_TEXTURE_2D);

    //cargar los puntos con las coordenadas reales luego de la rotacion
    geoPoint p1 = {getXrel(x,-y,angle),getYrel(x,-y,angle),0};
    drawGeoPoint(p1);
    geoPoint p2 = {getXrel(x,-y,angle),getYrel(x,-y,angle),z};
    drawGeoPoint(p2);
    geoPoint p3 = {getXrel(x,y,angle),getYrel(x,y,angle),z};
    drawGeoPoint(p3);
    geoPoint p4 = {getXrel(x,y,angle),getYrel(x,y,angle),0};
    drawGeoPoint(p4);

    plane p = planeEquation(p1,p2,p3);

    GLfloat angulo_rotZ_radianes = 0.0174532925 * rotZ;
    GLfloat xRel = getXrel(posX,posY,angulo_rotZ_radianes);
    GLfloat yRel = getYrel(posX,posY,angulo_rotZ_radianes);

    geoPoint p0 = {xRel, yRel, 1};
    // SI ES MENOR A 1 OCURRE UNA COLISION
    dist = distancePointPlane(p0,p);
    if(dist < RADIO_MOVIL)
    {
        //exit(1);
    }

    glColor3d(1,0,0);
    sprintf(textBuffer, "dist: %.2f",dist);
    drawString(textBuffer, 0,0,5.8);

    sprintf(textBuffer, "rotZ: %.2f | rot: %.2f",rotZ,angle);
    drawString(textBuffer, 0,0,5.0);

    sprintf(textBuffer, "xRel: %.2f | yRel: %.2f", xRel, yRel);
    drawString(textBuffer, 0,0,4.2);
}

double getXrel(double x, double y, double angle)
{
    return (x*cos(angle*0.0174532925) + y*sin(angle*0.0174532925));
}

double getYrel(double x, double y, double angle)
{
    return (-x*sin(angle*0.0174532925) + y*cos(angle*0.0174532925));
}

void figura(int vertex, double size)
{
    int i = 0;
    double angle = 360 / vertex;
    double edge = size*4/vertex;

    double fixer = 1;
    switch(vertex)
    {
    case 5:
        fixer = 1.35;
        break;
    case 6:
        fixer = 1.67;
        break;
    case 7:
        fixer = 2.0;
        break;
    default:
        fixer = 1.0;
        break;
    }
    glPushMatrix();
    //glRotated(-90, 0,0,1); //cambiar el primer 0 por un rand fijo

    //for(i=0; i<vertex-1; i++){
    glPushMatrix();
    i=1;
    glRotated(i*angle,0,0,1);
    square2d(edge*fixer,edge,1,i*angle);
    glPopMatrix();
    //}
    glPopMatrix();
}


void inicializarExtra(void)
{
    velocidad_movil = 0.1f;
    velocidad_paredes = 0.1f;

    extra_pos_x = 0.0f;
    extra_pos_y = 0.0f;

    extra_color_red = 0.0;
    extra_color_green = 0.0;
    extra_color_blue = 0.0;

    extra_tiempo = 0;
    extra_activo = 0;
    tiempo_extra_activo = 0;
    bandera_extra_activo = 0;
    invensibilidad = 0;

}
/* GLUT callback Handlers */
void drawString( char *s, float enX , float enY, float enZ)
{
    unsigned i;
    glRasterPos3f(enX ,enY,enZ);
    for (i=0; i<strlen(s); i++)
        glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18,s[i]);
}

void tableroUsuario( double t, double k, double a)
{
    int posicion_en_z = POSICION_FILA;

    glColor3d(1,1,0);
    sprintf(textBuffer, "rotZ: %.1f", rotZ);
    drawString(textBuffer,POSICION_COL_1,CERCANIA_USUARIO,posicion_en_z--);
    sprintf(textBuffer, "k: %.2f", k);
    drawString(textBuffer,POSICION_COL_1,CERCANIA_USUARIO,posicion_en_z--);
    sprintf(textBuffer, "a: %.2f", a);
    drawString(textBuffer,POSICION_COL_1,CERCANIA_USUARIO,posicion_en_z--);
    sprintf(textBuffer, "level: %d", level);
    drawString(textBuffer,POSICION_COL_1,CERCANIA_USUARIO,posicion_en_z--);
    sprintf(textBuffer, "posLR: %.2f", posEnLineaRecta());
    drawString(textBuffer,POSICION_COL_1,CERCANIA_USUARIO,posicion_en_z--);
    // DATOS DE LA NAVE
    posicion_en_z = POSICION_FILA;
    sprintf(textBuffer, "posX: %.2f", posX);
    drawString(textBuffer,POSICION_COL_2,CERCANIA_USUARIO,posicion_en_z--);
    sprintf(textBuffer, "posY: %.2f", posY);
    drawString(textBuffer,POSICION_COL_2,CERCANIA_USUARIO,posicion_en_z--);

    // DATOS DE LA PELOTA EXTRA
    posicion_en_z = POSICION_FILA;
    sprintf(textBuffer, "extra_pos_x: %.2f", extra_pos_x);
    drawString(textBuffer,POSICION_COL_3,CERCANIA_USUARIO,posicion_en_z--);
    sprintf(textBuffer, "extra_pos_y: %.2f", extra_pos_y);
    drawString(textBuffer,POSICION_COL_3,CERCANIA_USUARIO,posicion_en_z--);
}
/*
Funcion que dibuja el cuadrilatero de juego
*/
void circle2d(double radius)
{
    glEnable(GL_TEXTURE_2D);

    // Arena
    glColor3ub(255,218,53);
    glBindTexture(GL_TEXTURE_2D,arena.ID);
    glBegin(GL_POLYGON);
    glTexCoord3f(MAX_VIEW_DISTANCE, MAX_VIEW_DISTANCE,0);
    glVertex3f(MAX_VIEW_DISTANCE, MAX_VIEW_DISTANCE,0);
    glTexCoord3f(MAX_VIEW_DISTANCE, -MAX_VIEW_DISTANCE,0);
    glVertex3f(MAX_VIEW_DISTANCE, -MAX_VIEW_DISTANCE,0);
    glTexCoord3f(-MAX_VIEW_DISTANCE, -MAX_VIEW_DISTANCE,0);
    glVertex3f(-MAX_VIEW_DISTANCE, -MAX_VIEW_DISTANCE,0);
    glTexCoord3f(-MAX_VIEW_DISTANCE, MAX_VIEW_DISTANCE,0);
    glVertex3f(-MAX_VIEW_DISTANCE, MAX_VIEW_DISTANCE,0);
    glEnd();

    // Agua
    glColor3ub(119,171,255);
    glTranslated(0,0,0.1);
    glBindTexture(GL_TEXTURE_2D,agua.ID);
    glBegin(GL_POLYGON);
    float angle, radian, x, y, xcos, ysin, tx, ty;
    for (angle=0.0; angle<360.0; angle+=15.0)
    {
        radian = angle * (PI/180.0f);

        xcos = (float)cos(radian);
        ysin = (float)sin(radian);
        x = xcos * TAM_CUADRILATERO;
        y = ysin * TAM_CUADRILATERO;
        tx = xcos * 0.5 + 0.5;
        ty = ysin * 0.5 + 0.5;

        glTexCoord2f(tx, ty);
        glVertex2f(x, y);
    }

    glEnd();

    glDisable(GL_TEXTURE_2D);


    sprintf(textBuffer, "(2,2)");
    drawString(textBuffer, 2,2,0.1);
    sprintf(textBuffer, "(-2,-2)");
    drawString(textBuffer, -2,-2,0.1);
    sprintf(textBuffer, "(0,0)");
    drawString(textBuffer, 0,0,0.1);
    sprintf(textBuffer, "(2,-2)");
    drawString(textBuffer, 2,-2,0.1);
    sprintf(textBuffer, "(-2,2)");
    drawString(textBuffer, -2,2,0.1);
    sprintf(textBuffer, "(2,0)");
    drawString(textBuffer, 2,0,0.1);
    sprintf(textBuffer, "(0,2)");
    drawString(textBuffer, 0,2,0.1);
    sprintf(textBuffer, "(0,-2)");
    drawString(textBuffer, 0,-2,0.1);
    sprintf(textBuffer, "(-2,0)");
    drawString(textBuffer, -2,0,0.1);
    sprintf(textBuffer, "(-4,-4)");
    drawString(textBuffer, -4,-4,0.1);
    sprintf(textBuffer, "(-4,4)");
    drawString(textBuffer, -4,4,0.1);
    sprintf(textBuffer, "(4,4)");
    drawString(textBuffer, 4,4,0.1);
    sprintf(textBuffer, "(4,-4)");
    drawString(textBuffer, 4,-4,0.1);

}


// Initialize the OpenGL window
void init(void)
{



    glClearColor (0.255, 0.784, 0.862, 0.0); // Clear the color

//    glShadeModel (GL_FLAT); // Set the shading model to GL_FLAT
//
//    glEnable (GL_LINE_SMOOTH);
//    glHint(GL_LINE_SMOOTH_HINT, GL_NICEST); // Set Line Antialiasing
//
//    glClearDepth(1.0f);
//    glEnable(GL_DEPTH_TEST);
//    glDepthFunc(GL_LEQUAL);

    glShadeModel(GL_SMOOTH); // Type of shading for the polygons

    // Viewport transformation
    glViewport(0,0,screen_width,screen_height);

    // Projection transformation
    glMatrixMode(GL_PROJECTION); // Specifies which matrix stack is the target for matrix operations
    glLoadIdentity(); // We initialize the projection matrix as identity
    gluPerspective(45.0f,(GLfloat)screen_width/(GLfloat)screen_height,10.0f,10000.0f); // We define the "viewing volume"

    glEnable(GL_DEPTH_TEST); // We enable the depth test (also called z buffer)
    glPolygonMode (GL_FRONT_AND_BACK, GL_FILL); // Polygon rasterization mode (polygon filled)

    glEnable(GL_TEXTURE_2D); // This Enable the Texture mapping
    //Load3DS (&object,"D:\\Mis documentos\\Facultad\\10.Info3\\EstudioC\\Prueba2Object\\objectos_3d\\boat.3ds");
    Load3DS (&object,"objectos_3d\\boat.3ds");

    //object.id_texture=LoadBitmap("D:\\Mis documentos\\Facultad\\10.Info3\\EstudioC\\Prueba2Object\\boat.bmp"); // The Function LoadBitmap() return the current texture ID

    object.id_texture=LoadBitmap("objectos_3d\\boat.bmp");
    // If the last function returns -1 it means the file was not found so we exit from the program
    if (object.id_texture==-1)
    {
        MessageBox(NULL,"Image file: spaceshiptexture.bmp not found", "Zetadeck",MB_OK | MB_ICONERROR);
        exit (0);
    }

    if(!cargarTGA("textures/sandtga.tga", &arena))
    {
        printf("Error cargando textura\n");
        exit(0); // Cargamos la textura y chequeamos por errores
    }

    if(!cargarTGA("textures/agua.tga", &agua))
    {
        printf("Error cargando textura\n");
        exit(0); // Cargamos la textura y chequeamos por errores
    }
    if(!cargarTGA("textures/muro.tga", &muro))
    {
        printf("Error cargando textura\n");
        exit(0); // Cargamos la textura y chequeamos por errores
    }
}


void pelotitasExtrasAnimacion(double t)
{
    glPushMatrix();
    //glScaled(1.0f,1.0f,1.0f);
    glRotated(t*128, 0.5, 1, 1);
    glPushMatrix();
    glColor3d(extra_color_red, extra_color_green, extra_color_blue);
    glTranslated(2,0,0.25);
    glutSolidSphere(0.5,9,9);
    glPopMatrix();
    glPushMatrix();
    glTranslated(-2,0,0.25);
    glutSolidSphere(0.5,9,9);
    glPopMatrix();
    glPopMatrix();
    //printf("Deberia dibujar animacion");
}

void probabilidadExtra(void)
{
    int numero_probabilidad = 0;
    srand(time(NULL) * glutGet(GLUT_ELAPSED_TIME) / 1000.0 ) ;
    // obtener un valor randomico entre 1 y 100.
    numero_probabilidad = rand()%100 + 1;

    //  elegir tipo de color acorde a las probabilidades de aparicion de las pelotas.
    if (numero_probabilidad <= 10)
    {
        // Color rojo
        extra_color_red = 1.0;
        extra_color_green = 0.0;
        extra_color_blue = 0.0;
        extra_activo = 1;
    }
    else
    {
        if(numero_probabilidad > 10 && numero_probabilidad <= 20 )
        {
            // Color blanco
            extra_color_red = 1.0;
            extra_color_green = 1.0;
            extra_color_blue = 1.0;
            extra_activo = 2;
        }
        else
        {
            if(numero_probabilidad > 20 && numero_probabilidad <= 35 )
            {
                // Color verde
                extra_color_red = 0.0;
                extra_color_green = 1.0;
                extra_color_blue = 0.0;
                extra_activo = 3;
            }
            else
            {
                if(numero_probabilidad > 35 && numero_probabilidad <= 50 )
                {
                    // Color azul
                    extra_color_red = 0.0;
                    extra_color_green = 0.0;
                    extra_color_blue = 1.0;
                    extra_activo = 4;
                }
                else
                {
                    // Color rosa
                    extra_color_red = 0.73;
                    extra_color_green = 0.16;
                    extra_color_blue = 0.96;
                    extra_activo = 5;
                }
            }

        }
    }
    // generar posiciones aleatorias
    extra_pos_x = rand()%((TAM_CUADRILATERO-1)*2) - (TAM_CUADRILATERO - 1) ;
    extra_pos_y = rand()%((TAM_CUADRILATERO-1)*2) - (TAM_CUADRILATERO - 1) ;
}

void generarExtras(void)
{
    if (extra_tiempo > 0)
    {
        // dibujar pelota
        glPushMatrix();
        glRotated(rotZ,0.0,0.0,1.0);
        glTranslated(extra_pos_x,extra_pos_y,1);
        glColor3d(extra_color_red, extra_color_green, extra_color_blue);
        glutSolidSphere(RADIO_PELOTA_EXTRA,20,20);
        sprintf(textBuffer, "%d", extra_tiempo);
        drawString( textBuffer, extra_pos_x, extra_pos_y, 1);
        // etiquetar pelota
        glPopMatrix();
        extra_tiempo--;
        return;
    }
    else
    {
        probabilidadExtra();
        // dibujar pelota
        glPushMatrix();
        glColor3d(extra_color_red, extra_color_green, extra_color_blue);
        glRotated(rotZ,0.0,0.0,1.0);
        glTranslated(extra_pos_x,extra_pos_y, 1.5);
        glutSolidCube(RADIO_PELOTA_EXTRA);
        glPopMatrix();

        extra_tiempo = TIEMPO_APARICION_EXTRA;
    }
}

int detectarColisionExtras(void)
{
    GLfloat angulo_rotZ_radianes = 0.0174532925 * rotZ;
    GLfloat extra_pos_x_relativa = extra_pos_x*cos(angulo_rotZ_radianes) - extra_pos_y*sin(angulo_rotZ_radianes);
    GLfloat extra_pos_y_relativa = extra_pos_x*sin(angulo_rotZ_radianes) + extra_pos_y*cos(angulo_rotZ_radianes);
    GLfloat distanciaEntreMovilPelota = sqrt(pow((GLfloat)extra_pos_x_relativa - posX,2) + pow(((GLfloat)extra_pos_y_relativa - posY),2));

    //if (distanciaEntreMovilPelota <= (RADIO_PELOTA_EXTRA+RADIO_MOVIL) && extra_activo != 0)
    if (distanciaEntreMovilPelota <= (RADIO_PELOTA_EXTRA+RADIO_MOVIL))
    {
        printf("1");
        return 1;
    }
    else
    {
        printf("0");
        return 0;
    }

}

/*
10% - Rojo      (#FF0000) : vida extra.
10% - Blanco    (#FFFFFF) : invensibilidad por 5 segundos.
15% - Verde     (#00FF00): velocidad del movil x2 por 5 segundos.
15% - Azul      (#0000FF) : velocidad reducida x2 de los obstaculos
50% - Rosa      (#FA58AC) : 1000 puntos
*/

void manejadorExtras(void)
{
    if (bandera_extra_activo == 1)
    {
        // Implica que hay un extra activo
        switch(extra_activo)
        {
        case 2:
            // Caso blanco, invensibilidad por 5 segundos
            if(invensibilidad-- <= 0)
            {
                inicializarExtra();
            }
            break;
        case 3:
            // Caso verde, velocidad movil por 2 por 5 segundos.
            if(tiempo_extra_activo-- <= 0)
            {
                inicializarExtra();
            }
            break;
        case 4:
            // Caso azul, velocidad muros disminuido por 2
            if(tiempo_extra_activo-- <= 0)
            {
                inicializarExtra();
            }
            break;
        default:
            inicializarExtra();
            break;
        }
    }
    else
    {
        generarExtras();
        // No hay ningun extra activo, por tanto tenemos que verificar si no hay colision
        if (detectarColisionExtras())
        {
            // Hubo una colision, manejar que tipo de extra es.
            switch(extra_activo)
            {
            case 1:
                // Caso rojo, vida extra
                soundManager.playPowerUp1Sound();
                vidas_jugador++;
                inicializarExtra();
                break;
            case 2:
                // Caso blanco, invensibilidad por 5 segundos
                soundManager.playPowerUp2Sound();
                invensibilidad = TIEMPO_VALIDEZ_EXTRA_INVENSIBILIDAD;
                bandera_extra_activo = 1;
                break;
            case 3:
                // Caso verde, velocidad movil por 2 por 5 segundos.
                soundManager.playPowerUp3Sound();
                velocidad_movil *= 2;
                tiempo_extra_activo = TIEMPO_VALIDEZ_EXTRA_VELOCIDAD_MOVIL;
                bandera_extra_activo = 1; // Otorga la vida pero no hay tiempo restante para ese extra.
                break;
            case 4:
                // Caso azul, velocidad muros disminuido por 2
                velocidad_paredes /= 2;
                soundManager.playPowerUp4Sound();
                // Otorgarle al jugador el extra que comio
                tiempo_extra_activo = TIEMPO_VALIDEZ_EXTRA_VELOCIDAD_MURO;
                bandera_extra_activo = 1; // Otorga la vida pero no hay tiempo restante para ese extra.
                break;
            case 5:
                // Caso rosa, otorgarle 1000 puntos al usuario.
                soundManager.playPowerUp5Sound();
                puntos_jugador += 1000;
                inicializarExtra();
                break;
            default:
                inicializarExtra();
                break;
            }
        }
    }
}

void dibujarEjesCoordenadas(void)
{
    /*
    EJES POSITIVOS
    */
    glBegin(GL_LINES);

    // Green for x axis
    glColor3f (0.0, 1.0, 0.0);
    glVertex3f(0,0,0);
    glVertex3f(10,0,0);
    // Red for y axis
    glColor3f(1.0,0.0,0.0);
    glVertex3f(0,0,0);
    glVertex3f(0,10,0);
    // Blue for z axis
    glColor3f(0.0,0.0,1.0);
    glVertex3f(0,0,0);
    glVertex3f(0,0,10);

    glEnd();


    /*
    EJES NEGATIVOS
    */
    // Dotted lines for the negative sides of x,y,z
    glEnable(GL_LINE_STIPPLE); // Enable line stipple to use a
    // dotted pattern for the lines
    glLineStipple(1, 0x0101); // Dotted stipple pattern for the lines
    glBegin(GL_LINES);
    // Green for x axis
    glColor3f (0.0, 1.0, 0.0);
    glVertex3f(-10,0,0);
    glVertex3f(0,0,0);
    // Red for y axis
    glColor3f(1.0,0.0,0.0);
    glVertex3f(0,0,0);
    glVertex3f(0,-10,0);
    // Blue for z axis
    glColor3f(0.0,0.0,1.0);
    glVertex3f(0,0,0);
    glVertex3f(0,0,-10);

    glEnd();
    glDisable(GL_LINE_STIPPLE); // Disable the line stipple


    /*
    ETIQUETAR EJES
    */
    // Green for x axis
    glColor3f (0.0, 1.0, 0.0);
    drawString("x",10,0,0);
    drawString("-x",-10,0,0);
    // Red for y axis
    glColor3f(1.0,0.0,0.0);
    drawString("y",0,10,0);
    drawString("-y",0,-10,0);
    // Blue for z axis
    glColor3f(0.0,0.0,1.0);
    drawString("z",0,0,10);
    drawString("-z",0,0,-10);

}
/**
* Esta funcion convierte el angulo de rotacion entre 0 y 360 para casos en que paso los 360 o sea menor a cero.
*/
void dibujarNave(double t)
{

    // nave
    glPushMatrix();

    if(DEBUG)
    {
        glColor3f(1,1,1);
        sprintf(textBuffer, "(%.2f,%.2f,0)",posX,posY);
        drawString(textBuffer, posX, posY, 2);
    }

    //glColor3d(1,0,0);
    glTranslated(posX,posY,1);
    glRotated(90,0,0,1);
    //glutSolidSphere(RADIO_MOVIL,20,2);
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, object.id_texture); // We set the active texture

    glScaled(escala,escala,escala);
    glBegin(GL_TRIANGLES); // glBegin and glEnd delimit the vertices that define a primitive (in our case triangles)
    for (int l_index=0; l_index<object.polygons_qty; l_index++)
    {
        //----------------- FIRST VERTEX -----------------
        // Texture coordinates of the first vertex
        glTexCoord2f( object.mapcoord[ object.polygon[l_index].a ].u,
                      object.mapcoord[ object.polygon[l_index].a ].v);
        // Coordinates of the first vertex
        glVertex3f( object.vertex[ object.polygon[l_index].a ].x,
                    object.vertex[ object.polygon[l_index].a ].y,
                    object.vertex[ object.polygon[l_index].a ].z); //Vertex definition

        //----------------- SECOND VERTEX -----------------
        // Texture coordinates of the second vertex
        glTexCoord2f( object.mapcoord[ object.polygon[l_index].b ].u,
                      object.mapcoord[ object.polygon[l_index].b ].v);
        // Coordinates of the second vertex
        glVertex3f( object.vertex[ object.polygon[l_index].b ].x,
                    object.vertex[ object.polygon[l_index].b ].y,
                    object.vertex[ object.polygon[l_index].b ].z);

        //----------------- THIRD VERTEX -----------------
        // Texture coordinates of the third vertex
        glTexCoord2f( object.mapcoord[ object.polygon[l_index].c ].u,
                      object.mapcoord[ object.polygon[l_index].c ].v);
        // Coordinates of the Third vertex
        glVertex3f( object.vertex[ object.polygon[l_index].c ].x,
                    object.vertex[ object.polygon[l_index].c ].y,
                    object.vertex[ object.polygon[l_index].c ].z);
    }
    glEnd();

    if (bandera_extra_activo == 1)
    {
        glScaled(1,1,1);
        pelotitasExtrasAnimacion(glutGet(GLUT_ELAPSED_TIME) / 1000.0);
    }
    glDisable(GL_TEXTURE_2D);
    glPopMatrix();
    glFlush();
}

void reducirAnguloEntre0y360(void)
{
    while (rotZ < 0)
    {
        rotZ += 360;
    };
    while (rotZ > 360)
    {
        rotZ -= 360;
    };
}



// Draw the lines (x,y,z)
void display(void)
{

    const double t = glutGet(GLUT_ELAPSED_TIME) / 1000.0; //time

    const double k = (t) / (MAX_LEVEL - level); //time based events

    const double a = 15 - ((int)k%15) - (k-floor(k)); //oscilador de 15 segundos (el primer entero es la frecuencia)

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glMatrixMode(GL_MODELVIEW);

    if(DEBUG)
    {
        sprintf(textBuffer, "FPS: %4.2f", fps);
        drawString(textBuffer, 0,0,6.8);
    }

    if(show_menu == 0)  //modo juego
    {

        reducirAnguloEntre0y360();

        glPushMatrix();
        glRotatef(rotZ,0.0,0.0,1.0);
        if(DEBUG)
        {
            dibujarEjesCoordenadas();
        }
        circle2d(TAM_CUADRILATERO);

        glColor3d(1,1,1);
        //figura(7,10);
        glColor3d(0.5,0.5,0.5);
        figura(4,4);


        glPopMatrix();

        dibujarNave(t);
        manejadorExtras();
        tableroUsuario(k,t,a);
    }
    else   //modo menu
    {
        menu();
    }

    glutSwapBuffers();
}

void menu()
{
    glPushMatrix();
    glColor3d(1,0,0);
    glScaled(3,3,3);
    drawString(GAME_NAME, 0,0,0);
    drawString("Press P to Play", 0,0,-1);
    glPopMatrix();
}


// This function is called whenever the window size is changed
void reshape (int w, int h)
{
    glViewport (0, 0, (GLsizei) w, (GLsizei) h); // Set the viewport
    glMatrixMode (GL_PROJECTION); // Set the Matrix mode
    glLoadIdentity();
    gluPerspective(50, (GLfloat) w /(GLfloat) h , 0.10, MAX_VIEW_DISTANCE);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    gluLookAt ( 0, -15, 8, 0, 0, 0, 0,0,1);
}


// This function is used for the navigation keys
void keyboard (unsigned char key, int x, int y)
{
    switch (key)     // x,X,y,Y,z,Z uses the glRotatef() function
    {
    case 'z': // Rotates screen on z axis
        //rotacion Antihoraria
        rotZ -= 1;
        break;
    case 'x': // Opposite way
        rotZ += 1;
        // rotacion Horaria
        break;
    case '+':
        level = (level == MAX_LEVEL-1) ? MAX_LEVEL-1 : level+1; //-1 prevenir division por 0
        break;
    case '-':
        level = (level == 1) ? 1 : level-1; //-1 prevenir division por 0
        break;
    case 'p':
        show_menu = 0;
        break;
    }
    glutPostRedisplay(); // Redraw the scene
}

// called on special key pressed
void specialKey(int key, int x, int y)
{
    const double pelr = posEnLineaRecta();
    // Check which key is pressed
    switch(key)
    {
    case GLUT_KEY_LEFT : // Rotate on x axis
        if ((pelr < TAM_CUADRILATERO) || (pelr >= TAM_CUADRILATERO && posX > 0))
        {
            posX -= 0.1f;
        };
        break;
    case GLUT_KEY_RIGHT : // Rotate on x axis (opposite)
        if ((pelr < TAM_CUADRILATERO) || (pelr >= TAM_CUADRILATERO && posX < 0))
        {
            posX += 0.1f;
        };
        break;
    case GLUT_KEY_UP : // Rotate on y axis
        if ((pelr < TAM_CUADRILATERO) || (pelr >= TAM_CUADRILATERO && posY < 0))
        {
            posY += 0.1f;
        };
        break;
    case GLUT_KEY_DOWN : // Rotate on y axis (opposite)
        if ((pelr < TAM_CUADRILATERO) || (pelr >= TAM_CUADRILATERO && posY > 0))
        {
            posY -= 0.1f;
        };
        break;
    }
    glutPostRedisplay(); // Redraw the scene
}

double posEnLineaRecta(void)
{
    return sqrt( pow(posX,2) + pow(posY,2) );
}


static void idle(void)
{
    if(DEBUG)
    {
        calculateFPS();
    }
    glutPostRedisplay();
}

void calculateFPS()
{
    //  Increase frame count
    frameCount++;

    //  Get the number of milliseconds since glutInit called
    //  (or first call to glutGet(GLUT ELAPSED TIME)).
    currentTime = glutGet(GLUT_ELAPSED_TIME);

    //  Calculate time passed
    int timeInterval = currentTime - previousTime;

    if(timeInterval > 1000)
    {
        //  calculate the number of frames per second
        fps = frameCount / (timeInterval / 1000.0f);

        //  Set time
        previousTime = currentTime;

        //  Reset frame count
        frameCount = 0;
    }
}

// Main entry point of the program
int main(int argc, char** argv)
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
    glutInitWindowSize (800,600); // Set the screen size
    glutInitWindowPosition(70, 70); // Posicion de la ventana
    glutCreateWindow(GAME_NAME);
    init ();
    glutReshapeFunc(reshape);
    glutDisplayFunc(display);
    glutKeyboardFunc(keyboard); // set window's key callback
    glutSpecialFunc(specialKey); // set window's to specialKey callback
    glutIdleFunc(idle);
    glutMainLoop();



    return EXIT_SUCCESS;
}
