#pragma once
#include "cprocessing.h"

class GameObject
{
    protected:
        float coordX;
        float coordY;

    public:
        GameObject(float x, float y) : coordX(x), coordY(y) {}

        virtual ~GameObject() = default;

        virtual void move() = 0;
        virtual void draw() = 0;

        CP_Vector GetLocation() const {return {coordX, coordY};};
};