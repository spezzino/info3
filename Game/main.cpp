//#pragma once

#include "include/Globals.h"

using namespace std;

// OBJETOS A SER REPRESENTADOS
obj_type nave, extra, tronco;

GLint cielo, play, help, help_text, menu_exit;
int iterador_menu = 1;
int mostrar_ayuda = 0;


GLfloat troncos_x[NRO_TRONCOS], troncos_y[NRO_TRONCOS];


int frameCount = 0; //  The number of frames
float fps = 0; //  Number of frames per second
int currentTime = 0, previousTime = 0; //  currentTime - previousTime is the time elapsed between every call of the Idle function

int show_menu = 1; //1 se muestra el menu principal, 0 empieza el juego

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

float radioObstaculo1 = 20;
float radioObstaculo2 = 40;
float radioObstaculo3 = 60;

int crashTime = 0;

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
    geoPoint p1;
    geoPoint p2;
    geoPoint p3;
    geoPoint p4;
} pointsObject;

/* AUDIO */
SoundManager soundManager;

/* TEXTURAS */
textura arena;
textura muro;
textura agua;
textura horizonte;
textura sky;

void cuadrado(double);
float distanciaEnLineaRecta(geoPoint, geoPoint);
float posEnLineaRecta(void);
float distancePointPlane(geoPoint,plane);
plane planeEquation(geoPoint,geoPoint,geoPoint);
pointsObject square2d(float,float,float,float, GLint);
void figura(int,float);
void inicializarExtra(void);
void drawString(char*,float,float,float);
void drawGeoPoint(geoPoint);
void drawGeoPoint(float,float,float);
void tableroUsuario(double,double,double);
void circle2d(float);
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
float getXrel(float,float,float);
float getYrel(float,float,float);
void dibujarObjeto(obj_type objeto_en_cuestion, GLfloat escala);

void inicializarTroncos(void)
{

    for(int i = 0; i< NRO_TRONCOS ; i++)
    {
        troncos_x[i] = rand()%40 + (TAM_CUADRILATERO + 2);
        troncos_y[i] = rand()%40 + (TAM_CUADRILATERO + 2);
    }

}
float distancePointPlane(geoPoint p0, plane p)
{
    float distance = 0.0f;

    distance = abs( (p.a * p0.x) + (p.b * p0.y) + (p.c * p0.z) + p.d );
    distance = distance / sqrt( pow(p.a, 2) + pow(p.b, 2) + pow(p.c, 2) );
    return distance;
}

plane planeEquation(geoPoint a, geoPoint b, geoPoint c)
{
    geoPoint rab = {b.x - a.x, b.y - a.y, b.z - a.z};
    geoPoint rac = {c.x - a.x, c.y - a.y, c.z - a.z};
    geoPoint n = { (rab.y * rac.z) - (rab.z * rac.y),
                   (rab.x * rac.z) - (rab.z * rac.x),
                   (rab.x * rac.y) - (rab.y * rac.x)
                 };

    //geoPoint negN = {-n.x, -n.y, -n.z};

    //plane p = {negN.x, negN.y, negN.z, (negN.x * -p1.x) + (negN.y * -p1.y) + (negN.z * -p1.z)};
    plane p = {n.x, n.y, n.z, ( (n.x * -a.x) + (n.y * -a.y) + (n.z * -a.z) )};

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

void drawGeoPoint(float x, float y, float z)
{
    if(DEBUG)
    {
        sprintf(textBuffer, "(%.2f,%.2f,%.2f)", x, y, z);
        glColor3f(1,1,1);
        drawString(textBuffer, x,y,z);
    }
}

pointsObject square2d(float x, float y, float z, float angle, GLint textura_id)
{

    //cargar los puntos con las coordenadas reales luego de la rotacion
    geoPoint p1 = {getXrel(x,-y,angle),getYrel(x,-y,angle),0};
    geoPoint p2 = {getXrel(x,-y,angle),getYrel(x,-y,angle),z};
    geoPoint p3 = {getXrel(x,y,angle),getYrel(x,y,angle),z};
    geoPoint p4 = {getXrel(x,y,angle),getYrel(x,y,angle),0};

    glEnable(GL_TEXTURE_2D);
    // Muro
    glBindTexture(GL_TEXTURE_2D,textura_id);
    glBegin(GL_QUADS);
    glTexCoord2f(p1.y,0);
    glVertex3f(p1.x,p1.y,0);
    glTexCoord2f(p2.y,p2.z);
    glVertex3f(p2.x,p2.y,p2.z);
    glTexCoord2f(p3.y,p3.z);
    glVertex3f(p3.x,p3.y,p3.z);
    glTexCoord2f(p4.y,0);
    glVertex3f(p4.x,p4.y,0);
    glEnd();
    glDisable(GL_TEXTURE_2D);

    plane p = planeEquation(p1,p2,p3);

    GLfloat xRel = getXrel(posX,posY,rotZ);
    GLfloat yRel = getYrel(posX,posY,rotZ);

    geoPoint p0 = {xRel, yRel, 1};
    // SI ES MENOR A 1 OCURRE UNA COLISION
    dist = distancePointPlane(p0,p);
    float distp2p0 = distanciaEnLineaRecta(p2,p0);
    float distp3p0 = distanciaEnLineaRecta(p3,p0);
    float distp2p3 = distanciaEnLineaRecta(p2,p3);

    if(dist <= RADIO_MOVIL)
    {
        if(!(distp2p0 >= distp2p3 || distp3p0 >= distp2p3))
        {
            if(DEBUG)
            {
                glColor3d(1,0,0);
                sprintf(textBuffer, "crash %d", glutGet(GLUT_ELAPSED_TIME));
                drawString(textBuffer, -5,-5,4.8);
            }
            if(crashTime == 0)
            {
                //has crashed!!
                crashTime = glutGet(GLUT_ELAPSED_TIME);
            }
        }
    }

    if(crashTime > 0 && (glutGet(GLUT_ELAPSED_TIME) - crashTime > 5000))
    {
        crashTime = 0;
    }
    if(DEBUG)
    {
        printf("%d\n", glutGet(GLUT_ELAPSED_TIME));
        glColor3d(0,1,0);
        sprintf(textBuffer, "crash %d", crashTime);
        drawString(textBuffer, -3,-3,5.8);
    }

    glColor3d(1,0,0);
    sprintf(textBuffer, "dist: %.2f",dist);
    drawString(textBuffer, 0,0,5.8);

    sprintf(textBuffer, "rotZ: %.2f | rot: %.2f",rotZ,angle);
    drawString(textBuffer, 0,0,5.0);

    sprintf(textBuffer, "xRel: %.2f | yRel: %.2f", xRel, yRel);
    drawString(textBuffer, 0,0,4.2);

    pointsObject points1 = {p1,p2,p3,p4};
    return points1;
}

float getXrel(float x, float y, float angle)
{
    float rad = angle*RADS;
    return (x*std::cos(rad) + y*std::sin(rad));
}

float getYrel(float x, float y, float angle)
{
    float rad = angle*RADS;
    return (-x*std::sin(rad) + y*std::cos(rad));
}

void drawPoints(pointsObject points1)
{
    drawGeoPoint(points1.p1);
    drawGeoPoint(points1.p2);
    drawGeoPoint(points1.p3);
    drawGeoPoint(points1.p4);
}

void figura(int vertex, float size)
{
    int i = 0;
    float angle = 360 / vertex;
    float edge = size*4/vertex;

    float fixer = 1;
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

    for(i=0; i<vertex-1; i++)
    {
        glPushMatrix();
        //glRotated(-(i*angle),0,0,1);
        pointsObject points1 = square2d(edge*fixer,edge,1,i*angle, muro.ID);
        glPopMatrix();
        drawPoints(points1);
    }
    glPopMatrix();
}


void inicializarExtra(void)
{
    velocidad_movil = 0.1f;

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
void circle2d(float radius)
{
    glEnable(GL_TEXTURE_2D);

    // Arena
    glColor3ub(255,218,53);
    glBindTexture(GL_TEXTURE_2D,arena.ID);
    glBegin(GL_POLYGON);
    glTexCoord2f(0.0,0.0);
    glVertex3f(-MAX_VIEW_DISTANCE, -MAX_VIEW_DISTANCE,0);
    glTexCoord2f(1.0,0.0);
    glVertex3f(-MAX_VIEW_DISTANCE, MAX_VIEW_DISTANCE,0);
    glTexCoord2f(1.0,1.0);
    glVertex3f(MAX_VIEW_DISTANCE, MAX_VIEW_DISTANCE,0);
    glTexCoord2f(0.0,1.0);
    glVertex3f(MAX_VIEW_DISTANCE, -MAX_VIEW_DISTANCE,0);
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


    if(DEBUG)
    {
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
}


// Initialize the OpenGL window
void init(void)
{


    // Setea el color celeste de fondo
    glClearColor (0.255, 0.784, 0.862, 0.0);

//    glShadeModel (GL_FLAT); // Set the shading model to GL_FLAT
//
    glEnable (GL_LINE_SMOOTH);
    glHint(GL_LINE_SMOOTH_HINT, GL_NICEST); // Set Line Antialiasing
//
    glClearDepth(1.0f);
//    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LEQUAL);

    glShadeModel(GL_SMOOTH); // Type of shading for the polygons

    // Viewport transformation
    // glViewport(0,0,screen_width,screen_height);

    // Projection transformation
    glMatrixMode(GL_PROJECTION); // Specifies which matrix stack is the target for matrix operations
    //glLoadIdentity(); // We initialize the projection matrix as identity
    //gluPerspective(45.0f,(GLfloat)screen_width/(GLfloat)screen_height,10.0f,10000.0f); // We define the "viewing volume"

    glEnable(GL_DEPTH_TEST); // We enable the depth test (also called z buffer)
    glPolygonMode (GL_FRONT_AND_BACK, GL_FILL); // Polygon rasterization mode (polygon filled)

    Load3DS (&nave,"objectos_3d\\boat03.3ds");
    nave.id_texture=LoadBitmap("objectos_3d\\boat03.bmp");
    // If the last function returns -1 it means the file was not found so we exit from the program
    if (nave.id_texture==-1)
    {
        MessageBox(NULL,"No se puede cargar textura de la nave", "Zetadeck",MB_OK | MB_ICONERROR);
        exit (0);
    }


    Load3DS (&extra,"objectos_3d\\barril.3ds");
    extra.id_texture=LoadBitmap("objectos_3d\\barril.bmp");
    // If the last function returns -1 it means the file was not found so we exit from the program
    if (extra.id_texture==-1)
    {
        MessageBox(NULL,"No se puede cargar textura del objeto extra", "Zetadeck",MB_OK | MB_ICONERROR);
        exit (0);
    }

    cielo=LoadBitmap("textures\\blue-sky.bmp");
    // If the last function returns -1 it means the file was not found so we exit from the program
    if (cielo==-1)
    {
        MessageBox(NULL,"No se puede cargar textura del horizonte", "Zetadeck",MB_OK | MB_ICONERROR);
        exit (0);
    }

    play=LoadBitmap("image_menu\\play.bmp");
    // If the last function returns -1 it means the file was not found so we exit from the program
    if (play==-1)
    {
        MessageBox(NULL,"No se puede cargar imagen play", "Zetadeck",MB_OK | MB_ICONERROR);
        exit (0);
    }

    help=LoadBitmap("image_menu\\help.bmp");
    // If the last function returns -1 it means the file was not found so we exit from the program
    if (help==-1)
    {
        MessageBox(NULL,"No se puede cargar imagen help", "Zetadeck",MB_OK | MB_ICONERROR);
        exit (0);
    }

    help_text=LoadBitmap("image_menu\\text-help.bmp");
    // If the last function returns -1 it means the file was not found so we exit from the program
    if (help_text==-1)
    {
        MessageBox(NULL,"No se puede cargar imagen text-help", "Zetadeck",MB_OK | MB_ICONERROR);
        exit (0);
    }
    menu_exit=LoadBitmap("image_menu\\exit.bmp");
    // If the last function returns -1 it means the file was not found so we exit from the program
    if (menu_exit==-1)
    {
        MessageBox(NULL,"No se puede cargar imagen exit", "Zetadeck",MB_OK | MB_ICONERROR);
        exit (0);
    }

    if(!cargarTGA("textures/sky.tga", &sky))
    {
        printf("Error cargando textura\n");
        exit(0); // Cargamos la textura y chequeamos por errores
    }

    //if(!cargarTGA("textures/dry_earth.tga", &arena))
    if(!cargarTGA("textures/sand.tga", &arena))
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

    gluLookAt ( 0, -15, 8, 0, 0, 0, 0,0,1);
}


void pelotitasExtrasAnimacion(double t)
{
    glPushMatrix();
    glColor3d(extra_color_red, extra_color_green, extra_color_blue);
    glRotated(t*128, 1, 1, 0);
    glPushMatrix();
    glTranslated(1,0,0.25);
    glutSolidSphere(0.5,9,9);
    glPopMatrix();
    glPushMatrix();
    glTranslated(-1,0,0.25);
    glutSolidSphere(0.5,9,9);
    glPopMatrix();
    glPopMatrix();

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
        //glColor3d(extra_color_red, extra_color_green, extra_color_blue);
        dibujarObjeto(extra, 1.0f);
        //glutSolidSphere(RADIO_PELOTA_EXTRA,20,20);
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
        //printf("Colision");
        return 1;
    }
    else
    {
        // printf("No hay colision");
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
void dibujarObjeto(obj_type objeto_en_cuestion, GLfloat escala)
{
    glScalef(escala,escala,escala);
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, objeto_en_cuestion.id_texture); // We set the active texture
    glBegin(GL_TRIANGLES); // glBegin and glEnd delimit the vertices that define a primitive (in our case triangles)
    for (int l_index=0; l_index<objeto_en_cuestion.polygons_qty; l_index++)
    {
        //----------------- FIRST VERTEX -----------------
        // Texture coordinates of the first vertex
        glTexCoord2f( objeto_en_cuestion.mapcoord[ objeto_en_cuestion.polygon[l_index].a ].u,
                      objeto_en_cuestion.mapcoord[ objeto_en_cuestion.polygon[l_index].a ].v);
        // Coordinates of the first vertex
        glVertex3f( objeto_en_cuestion.vertex[ objeto_en_cuestion.polygon[l_index].a ].x,
                    objeto_en_cuestion.vertex[ objeto_en_cuestion.polygon[l_index].a ].y,
                    objeto_en_cuestion.vertex[ objeto_en_cuestion.polygon[l_index].a ].z); //Vertex definition

        //----------------- SECOND VERTEX -----------------
        // Texture coordinates of the second vertex
        glTexCoord2f( objeto_en_cuestion.mapcoord[ objeto_en_cuestion.polygon[l_index].b ].u,
                      objeto_en_cuestion.mapcoord[ objeto_en_cuestion.polygon[l_index].b ].v);
        // Coordinates of the second vertex
        glVertex3f( objeto_en_cuestion.vertex[ objeto_en_cuestion.polygon[l_index].b ].x,
                    objeto_en_cuestion.vertex[ objeto_en_cuestion.polygon[l_index].b ].y,
                    objeto_en_cuestion.vertex[ objeto_en_cuestion.polygon[l_index].b ].z);

        //----------------- THIRD VERTEX -----------------
        // Texture coordinates of the third vertex
        glTexCoord2f( objeto_en_cuestion.mapcoord[ objeto_en_cuestion.polygon[l_index].c ].u,
                      objeto_en_cuestion.mapcoord[ objeto_en_cuestion.polygon[l_index].c ].v);
        // Coordinates of the Third vertex
        glVertex3f( objeto_en_cuestion.vertex[ objeto_en_cuestion.polygon[l_index].c ].x,
                    objeto_en_cuestion.vertex[ objeto_en_cuestion.polygon[l_index].c ].y,
                    objeto_en_cuestion.vertex[ objeto_en_cuestion.polygon[l_index].c ].z);
    }
    glEnd();
    glDisable(GL_TEXTURE_2D);
}
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
    glTranslated(posX,posY,0.2);
    glRotated(90,0,0,1);
    if (bandera_extra_activo == 1)
    {
        pelotitasExtrasAnimacion(glutGet(GLUT_ELAPSED_TIME) / 1000.0);
    }
    dibujarObjeto(nave, 0.015f);
    glPopMatrix();
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
void dibujarHorizonte(float x, float y, float z, GLint textura_id)
{

    float amplitud_horizonte = 25.0f;
    float distancia_horizonte = 20.0f;

    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D,textura_id);

    glPushMatrix();
    glBegin(GL_QUADS);
    glTexCoord2f(0.0,0.0);
    glVertex3f(-amplitud_horizonte,distancia_horizonte, 0.0);

    glTexCoord2f(1.0,0.0);
    glVertex3f(-amplitud_horizonte,distancia_horizonte, amplitud_horizonte);

    glTexCoord2f(1.0,1.0);
    glVertex3f(amplitud_horizonte,distancia_horizonte, amplitud_horizonte);

    glTexCoord2f(0.0,1.0);
    glVertex3f(amplitud_horizonte,distancia_horizonte, 0.0);

    glEnd();
    glDisable(GL_TEXTURE_2D);

    glPopMatrix();
}

// Draw the lines (x,y,z)
void display(void)
{

    const double t = glutGet(GLUT_ELAPSED_TIME) / 1000.0; //time
    const double k = (t) / (MAX_LEVEL - level); //time based events
    const double a = 15 - ((int)k%15) - (k-floor(k)); //oscilador de 15 segundos (el primer entero es la frecuencia)

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    //glMatrixMode(GL_MODELVIEW);

    if(DEBUG)
    {
        sprintf(textBuffer, "FPS: %4.2f", fps);
        drawString(textBuffer, 0,0,6.8);
    }

    if(show_menu == 0)  //modo juego
    {
        soundManager.stopMenuMusic();
        soundManager.playGameMusic();
        reducirAnguloEntre0y360();
        dibujarHorizonte(50.0,50.0,50.0,sky.ID);
        glPushMatrix();
        glRotatef(rotZ,0.0,0.0,1.0);
        if(DEBUG)
        {
            dibujarEjesCoordenadas();
        }
        circle2d(TAM_CUADRILATERO);

        glPopMatrix();

        dibujarNave(t);
        manejadorExtras();
        tableroUsuario(k,t,a);

        figura(5,radioObstaculo1);
        figura(4,radioObstaculo2);
        figura(6,radioObstaculo3);

        if(radioObstaculo1 < 1.2)
        {
            radioObstaculo1 = 60;
        }
        else
        {
            radioObstaculo1 -= velocidad_paredes;
        }

        if(radioObstaculo2 < 1.2)
        {
            radioObstaculo2 = 60;
        }
        else
        {
            radioObstaculo2 -= velocidad_paredes;
        }

        if(radioObstaculo3 < 1.2)
        {
            radioObstaculo3 = 60;
        }
        else
        {
            radioObstaculo3 -= velocidad_paredes;
        }

    }
    else   //modo menu
    {
        menu();
    }

    glutSwapBuffers();
}

void cargarImagenMenu(int imagen)
{
    float x = 11.5f;
    float y = 4.0f;
    float z = 7.5f;

    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D,imagen);

    glRotated(180,0,0,1);
    glPushMatrix();
    glBegin(GL_QUADS);


    glTexCoord2f(1.0,0.0);
    glVertex3f(-x,y, -z);

    glTexCoord2f(1.0,1.0);
    glVertex3f(-x,-y, z);

    glTexCoord2f(0.0,1.0);
    glVertex3f(x,-y, z);

    glTexCoord2f(0.0,0.0);
    glVertex3f(x,y, -z);

    glEnd();
    glDisable(GL_TEXTURE_2D);

    glPopMatrix();
}

void iterar_menu (int incremento)
{

    iterador_menu+=incremento;
    if(iterador_menu > 3)
    {
        iterador_menu = 1;
    }
    if(iterador_menu < 1)
    {
        iterador_menu = 3;
    }
}
void menu()
{
    glPushMatrix();
//    glColor3d(1,0,0);
//    glScaled(3,3,3);
//    drawString(GAME_NAME, 0,0,0);
//    drawString("Press P to Play", 0,0,-1);
    switch (iterador_menu)
    {

    case 1:
        cargarImagenMenu(play);
        break;
    case 2:
        if (mostrar_ayuda == 0)
        {
            cargarImagenMenu(help);
        }
        else
        {
            cargarImagenMenu(help_text);
        }
        break;
    case 3:
        cargarImagenMenu(menu_exit);
        break;
    default:
        break;
    }
    soundManager.stopGameMusic();
    soundManager.playMenuMusic();
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
        if (show_menu == 1)
        {
            show_menu = 0;
        }
        break;
    case 27:
        exit(1);
        break;
    case 13:
        if (show_menu == 1 && mostrar_ayuda == 1)
        {
            mostrar_ayuda = 0;
        }
        else
        {
            if (show_menu == 1)
            {
                switch(iterador_menu)
                {
                case 1:
                    show_menu = 0;
                    break;
                case 2:
                    mostrar_ayuda = 1;
                    break;
                case 3:
                    exit(1);
                    break;
                }
            }
        }
        break;
        glutPostRedisplay(); // Redraw the scene
    }
}

// called on special key pressed
void specialKey(int key, int x, int y)
{
    const float pelr = posEnLineaRecta();
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
        if(show_menu == 1)
        {
            iterar_menu(-1);
            soundManager.playMenuSound();
        }
        break;
    case GLUT_KEY_DOWN : // Rotate on y axis (opposite)
        if ((pelr < TAM_CUADRILATERO) || (pelr >= TAM_CUADRILATERO && posY > 0))
        {
            posY -= 0.1f;
        };
        if(show_menu == 1)
        {
            iterar_menu(1);
            soundManager.playMenuSound();
        }
        break;
    }

    glutPostRedisplay(); // Redraw the scene

}

float posEnLineaRecta(void)
{
    return sqrt( pow(posX,2) + pow(posY,2) );
}

float distanciaEnLineaRecta(geoPoint p1, geoPoint p2)
{
    return sqrt( pow(p1.x-p2.x, 2)+ pow(p1.y-p2.y, 2) + pow(p1.z-p2.z, 2));
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
    glutInitWindowSize (ANCHO_VENTANA,ALTO_VENTANA); // Set the screen size
    glutInitWindowPosition(X_APARICION, Y_APARICION); // Posicion de la ventana
    glutCreateWindow(GAME_NAME);
    init();
    glutReshapeFunc(reshape);
    glutDisplayFunc(display);
    glutKeyboardFunc(keyboard); // set window's key callback
    glutSpecialFunc(specialKey); // set window's to specialKey callback
    glutIdleFunc(idle);
    glutMainLoop();

    return EXIT_SUCCESS;
}
