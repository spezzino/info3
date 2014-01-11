#ifndef POINT_H
#define POINT_H

#pragma once

class Point
{
    public:
        Point();
        Point(float,float,float);
        virtual ~Point();

        float x;
        float y;
        float z;

        void printCoords(void);

    protected:
    private:
};

#endif // POINT_H
