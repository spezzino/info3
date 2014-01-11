#include "Plane.h"

Plane::Plane(){
}

Plane::~Plane(){
}

Plane::Plane(float a, float b, float c, float d){
    this->a = a;
    this->b = b;
    this->c = c;
    this->d = d;
}

Plane Plane::getEquation(Point p1, Point p2, Point p3){
    Point v1 = Point(p1.x - p2.x, p1.y - p2.y, p1.z - p2.z);
    Point v2 = Point(p3.x - p2.x, p3.y - p2.y, p3.z - p2.z);
    Point n = Point( (v1.y * v2.z) - (p1.z * p2.y),
                  (p1.x * p2.z) - (p1.z * p2.x),
                  (p1.x * p2.y) - (p1.y * p2.x)
                );

    Point negN = Point(-n.x, -n.y, -n.z);

    Plane p = Plane(negN.x, negN.y, negN.z, (negN.x * -p1.x) + (negN.y * -p1.y) + (negN.z * -p1.z));

    return p;
}
