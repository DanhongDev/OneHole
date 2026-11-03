#pragma once
#include "cprocessing.h"

void balls_init();
void balls_update();
void balls_exit();

class Ball
{
    private:
    float coordX, coordY;
    CP_Vector velocity;

    public:
    Ball(float coordX, float coordY, CP_Vector velocity);
    const CP_Vector GetCoord() {return {coordX, coordY};};
};