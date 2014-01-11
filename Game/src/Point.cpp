#include <stdio.h>
#include "Point.h"

Point::Point(){
}

Point::~Point(){
}

Point::Point(float x, float y, float z){
    this->x = x;
    this->y = y;
    this->z = z;
}

void Point::printCoords(){
    printf("x: %.2f | y: %.2f | z: %.2f", x, y, z);
}
