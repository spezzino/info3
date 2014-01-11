#ifndef OBJECT_H
#define OBJECT_H

#pragma once
#include "Globals.h"

class Object
{
    public:
        Object();
        Object(float,float,float);
        virtual ~Object();

        float x;
        float y;
        float z;

        void printCoords(void);

    protected:
    private:
};

#endif // OBJECT_H
