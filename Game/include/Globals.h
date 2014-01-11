#ifndef GLOBALS_H_INCLUDED
#define GLOBALS_H_INCLUDED

#pragma once

#define DEBUG 1

#include <windows.h>
#include <stdio.h>
#include <iostream>
#include <stdlib.h>
#include <string>
#include <GL/glut.h>
#include <math.h>
#include <time.h>
#include <fmod/fmod.h>

using namespace std;

#include "Point.h"
#include "Plane.h"
#include "SoundManager.h"

#define PI 3.141592654
#define TAM_CUADRILATERO 5
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

#define POSICION_COL_1 -12
#define POSICION_COL_2 -2
#define POSICION_COL_3 8
#define POSICION_FILA -2
#define CERCANIA_USUARIO -5

#endif // GLOBALS_H_INCLUDED
