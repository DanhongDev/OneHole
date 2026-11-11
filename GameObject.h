#pragma once
#include "cprocessing.h"

class GameObject
{
    protected:
        float coordX;
        float coordY;
        bool isAlive;

    public:
        GameObject(float x, float y) : coordX(x), coordY(y), isAlive(true) {}

        virtual ~GameObject() = default;

        virtual void move() {}
        virtual void draw() = 0;
        virtual CP_Vector GetSize() const { return {}; }

        CP_Vector GetLocation() const {return {coordX, coordY};};

        bool GetAliveState() const {return isAlive;};
        void SetAliveState(bool s) {isAlive = s;};
};