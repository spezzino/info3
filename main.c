/*
 * FreeGLUT Shapes Demo
 *
 * Written by Nigel Stewart November 2003
 *
 * This program is test harness for the sphere, cone 
 * and torus shapes in FreeGLUT.
 *
 * Spinning wireframe and smooth shaded shapes are
 * displayed until the ESC or q key is pressed.  The
 * number of geometry stacks and slices can be adjusted
 * using the + and - keys.
 */

#include <GL/glut.h>

#include <stdlib.h>

static int slices = 16;
static int stacks = 16;

#define MENU 0
#define GAME 1

static int pantalla = MENU;

GLfloat X = 0.0f; // Translate screen to x direction (left or right)
GLfloat Y = 0.0f; // Translate screen to y direction (up or down)
GLfloat Z = 0.0f; // Translate screen to z direction (zoom in or out)
GLfloat rotX = 0.0f; // Rotate screen on x axis 
GLfloat rotY = 0.0f; // Rotate screen on y axis
GLfloat rotZ = 0.0f; // Rotate screen on z axis
GLfloat rotLx = 0.0f; // Translate screen by using the glulookAt function (left or right)
GLfloat rotLy = -6.0f; // Translate screen by using the glulookAt function (up or down)
GLfloat rotLz = 1.0f; // Translate screen by using the glulookAt function (zoom in or out)

/* GLUT callback Handlers */
void drawString(void * font, char *s, float x, float y, float z){
     unsigned i;
     glRasterPos3f(x,y,z);
     for (i=0;i<strlen(s);i++)
         glutBitmapCharacter(font,s[i]);    
}

static void 
resize(int width, int height)
{
    const float ar = (float) width / (float) height;
    
    glViewport(0, 0, width, height);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glFrustum(-ar, ar, -1.0, 1.0, 2.0, 100.0);
    
    //gluLookAt(x1,y1,z1,x2,y2,z2,x3,y3,z3) [x1,y1,z1] posicion camara, [x2,y2,z2] visto, 
    //[x3,y3,z3] vector posicion te define el norte de la camara  
    //gluLookAt(0,-6,2,1,1,2,0,0,1);
    gluLookAt (rotLx, rotLy, rotLz,1,1,2,0,1,0); 
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity() ;
}

static void 
display(void)
{
    const double t = glutGet(GLUT_ELAPSED_TIME) / 1000.0;
    const double a = t*90.0;
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    
if(pantalla == GAME){
    
    glRotatef(rotX,1.0,0.0,0.0); // Rotate on x
    glRotatef(rotY,0.0,1.0,0.0); // Rotate on y
    glRotatef(rotZ,0.0,0.0,1.0); // Rotate on z
    glTranslatef(X, Y, Z); 	// Translates the screen left or right, 
    
    glPushMatrix(); //Linea recta
     glBegin(GL_LINES);
     //eje x     
     glColor3f(1.0f,0,0);
     drawString(GLUT_BITMAP_HELVETICA_18,"x",2,0.2,0);
     glVertex3f(0,0,0);
     glVertex3f(10,0,0);
     //eje y
     glColor3f(0,1,0);
     drawString(GLUT_BITMAP_HELVETICA_18,"y",0,2,0.2);
     glVertex3f(0,0,0);
     glVertex3f(0,10,0);
     //eje z
     glColor3f(0,0,1);
     drawString(GLUT_BITMAP_HELVETICA_18,"z",0.2,0,2);
     glVertex3f(0,0,0);
     glVertex3f(0,0,10);
     glEnd();
    glPopMatrix();
     
     /*
    glPushMatrix();
     //linea punteada
     glEnable(GL_LINE_STIPPLE);
     glLineStipple(1, 10);
     glBegin(GL_LINES);
     //eje x
     glColor3f(1,0,0);
     glVertex3f(0,0,0);
     glVertex3f(-10,0,0);
     //eje y
     glColor3f(0,1,0);
     glVertex3f(0,0,0);
     glVertex3f(0,-10,0);
     //eje z
     glColor3f(0,0,1);
     glVertex3f(0,0,0);
     glVertex3f(0,0,-10);
     
     glDisable(GL_LINE_STIPPLE); 
     glEnd();
    glPopMatrix();
     */
    
    glPushMatrix();
        glColor3d(1,0,0);
        glTranslated(1,1,1);
        glutSolidCube(1);
    glPopMatrix();
    
    glPushMatrix();
        glColor3d(0,1,0);
        glTranslated(2,2,1);
        glutSolidSphere(1,slices,stacks);
    glPopMatrix();
    
    glPushMatrix();
        glColor3d(0,0,1);
        glTranslated(3,3,1);
        glutSolidTetrahedron();
    glPopMatrix();
    
    //cuadrado 2d cara frontal
    
    /*
    glPushMatrix();
        glColor3d(1,1,1);
        glBegin(GL_QUADS);
        glVertex3f(-5,0,15-t);
        glVertex3f(-5,5,15-t);
        glVertex3f(5,5,15-t);
        glVertex3f(5,0,15-t);
        glEnd();
    glPopMatrix();
    */
    glPushMatrix();
        glColor3d(1,1,1);
        glBegin(GL_QUADS);
        glVertex3f(-5,0,15-t);
        glVertex3f(-5,5,15-t);
        glVertex3f(5,5,15-t);
        glVertex3f(5,0,15-t);
        glEnd();
    glPopMatrix();
    
    //completar un cuadrado que se achique hasta el centro
    
    /*
    //cuadrado 2d cara trasera
    glPushMatrix();
        glBegin(GL_QUADS);
        glVertex3f(1,1,0);
        glVertex3f(-1,1,0);
        glVertex3f(-1,-1,0);
        glVertex3f(1,-1,0);
        glEnd();
    glPopMatrix();
    */
}else{
    glPushMatrix();
        drawString(GLUT_BITMAP_HELVETICA_18,"z",0.2,0,2);
    glPopMatrix();
}
    
    glutSwapBuffers();
}

static void specKey(int key, int x, int y){
    switch(key){
        case GLUT_KEY_LEFT:
             glRotated(1,0,0,1);
             break;           
        case GLUT_KEY_RIGHT:
             glRotated(-1,0,0,1);
             break;  
        case GLUT_KEY_UP:
             glTranslated(0,-1,0);//(x,y,z)
             break;           
        case GLUT_KEY_DOWN:
             glTranslated(0,1,0);
             break;     
    }       
}

static void 
key(unsigned char key, int x, int y)
{
    switch (key) 
    {
        case 27 :
        case 'q':
            exit(0);
            break;
        
        case 'p':
             if(pantalla == GAME)
                 pantalla = MENU;
             else
                 pantalla = GAME;
        
        case 'w':
             glRotated(1,1,0,0); //(rotated,x,y,z)
             break;
        case 'a':
             glRotated(1,0,1,0);
             break;
        case 's':
             glRotated(-1,1,0,0); //(rotated,x,y,z)
             break;
        case 'd':
             glRotated(-1,0,1,0);
             break;  
              
        case '+':
            slices++;
            stacks++;
            break;

        case '-':
            if (slices>3 && stacks>3)
            {
                slices--;
                stacks--;
            }
            break;
    }

    glutPostRedisplay();
}

static void 
idle(void)
{
    glutPostRedisplay();
}

const GLfloat light_ambient[]  = { 0.0f, 0.0f, 0.0f, 1.0f };
const GLfloat light_diffuse[]  = { 1.0f, 1.0f, 1.0f, 1.0f };
const GLfloat light_specular[] = { 1.0f, 1.0f, 1.0f, 1.0f };
const GLfloat light_position[] = { 2.0f, 5.0f, 5.0f, 0.0f };

const GLfloat mat_ambient[]    = { 0.7f, 0.7f, 0.7f, 1.0f };
const GLfloat mat_diffuse[]    = { 0.8f, 0.8f, 0.8f, 1.0f };
const GLfloat mat_specular[]   = { 1.0f, 1.0f, 1.0f, 1.0f };
const GLfloat high_shininess[] = { 100.0f };

/* Program entry point */

int 
main(int argc, char *argv[])
{
    glutInit(&argc, argv);
    glutInitWindowSize(640,480);
    glutInitWindowPosition(10,10);
    glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE | GLUT_DEPTH);

    glutCreateWindow("FreeGLUT Shapes");

    glutReshapeFunc(resize);
    glutDisplayFunc(display);
    glutKeyboardFunc(key);
    glutSpecialFunc(specKey);
    glutIdleFunc(idle);

    glClearColor(1,1,1,1);
    glEnable(GL_CULL_FACE);
    glCullFace(GL_BACK);

    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LESS);

    glEnable(GL_LIGHT0);
    glEnable(GL_NORMALIZE);
    glEnable(GL_COLOR_MATERIAL);
    glEnable(GL_LIGHTING);

    glLightfv(GL_LIGHT0, GL_AMBIENT,  light_ambient);
    glLightfv(GL_LIGHT0, GL_DIFFUSE,  light_diffuse);
    glLightfv(GL_LIGHT0, GL_SPECULAR, light_specular);
    glLightfv(GL_LIGHT0, GL_POSITION, light_position);

    glMaterialfv(GL_FRONT, GL_AMBIENT,   mat_ambient);
    glMaterialfv(GL_FRONT, GL_DIFFUSE,   mat_diffuse);
    glMaterialfv(GL_FRONT, GL_SPECULAR,  mat_specular);
    glMaterialfv(GL_FRONT, GL_SHININESS, high_shininess);

    glutMainLoop();

    return EXIT_SUCCESS;
}
