#ifndef GLOBALS_H_INCLUDED
#define GLOBALS_H_INCLUDED

#define DEBUG 0

#include <windows.h>
#include <stdio.h>
#include <iostream>
#include <stdlib.h>
#include <string>
#include <GL/glut.h>
#include <cmath>
#include <time.h>
#include <fmod/fmod.h>

using namespace std;

#include "SoundManager.h"

/* TAMAÑO Y POSICIONES DONDE APARECE LA VENTANA */
#define ANCHO_VENTANA 800
#define ALTO_VENTANA 600
#define X_APARICION 50
#define Y_APARICION 50



#define PI 3.141592654
#define RADS 0.0174532925
#define TAM_CUADRILATERO 8
#define MAX_LEVEL 30
#define RADIO_PELOTA_EXTRA 1
#define RADIO_MOVIL 1
#define TIEMPO_APARICION_EXTRA 2500
#define TIEMPO_VALIDEZ_EXTRA 500
#define TIEMPO_VALIDEZ_EXTRA_INVENSIBILIDAD 1500
#define TIEMPO_VALIDEZ_EXTRA_VELOCIDAD_MOVIL 1500
#define TIEMPO_VALIDEZ_EXTRA_VELOCIDAD_MURO 1500
#define MAX_VIEW_DISTANCE 35.0
#define GAME_NAME "OpenGL Game"
#define DELAY_GAME 10
#define DELAY_MENU 90

#define CERCANIA_USUARIO -5

#define X_CAMARA 0
#define Y_CAMARA -15
#define Z_CAMARA 8


/**********************************************************
 *
 * TYPES DECLARATION
 *
 *********************************************************/

#define MAX_VERTICES 70000 // Max number of vertices (for each object)
#define MAX_POLYGONS 70000 // Max number of polygons (for each object)

// Our vertex type
typedef struct{
    float x,y,z;
}vertex_type;

// The polygon (triangle), 3 numbers that aim 3 vertices
typedef struct{
    unsigned short a,b,c;
}polygon_type;

// The mapcoord type, 2 texture coordinates for each vertex
typedef struct{
    float u,v;
}mapcoord_type;

// The object type
typedef struct {
	char name[20];

	int vertices_qty;
    int polygons_qty;

    vertex_type vertex[MAX_VERTICES];
    polygon_type polygon[MAX_POLYGONS];
    mapcoord_type mapcoord[MAX_VERTICES];
    int id_texture;
} obj_type, *obj_type_ptr;


#include "texture.h"
#include "3dsloader.h"
#endif // GLOBALS_H_INCLUDED
