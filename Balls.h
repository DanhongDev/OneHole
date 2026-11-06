#pragma once
#include "cprocessing.h"
#include "GameObject.h"

class Ball : public GameObject
{
    private:
        CP_Vector direction;
        static constexpr float speed = 150.f;

    public:
        Ball(float x, float y, CP_Vector d);
        void move() override;
        void draw() override;
};