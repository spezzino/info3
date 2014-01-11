#include "Object.h"

Object::Object(){
}

Object::~Object(){
}

Object::Object(float x, float y, float z){
    this->x = x;
    this->y = y;
    this->z = z;
}

void Object::printCoords(){
    printf("x: %.2f | y: %.2f | z: %.2f", x, y, z);
}
