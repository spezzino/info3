#ifndef PLANE_H
#define PLANE_H

#pragma once
#include "Point.h"

class Plane
{
    public:
        Plane();
        virtual ~Plane();

        Plane(float, float, float, float);

        static Plane getEquation(Point, Point, Point);

        float a;
        float b;
        float c;
        float d;

    protected:
    private:
};

#endif // PLANE_H
