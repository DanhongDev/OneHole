#pragma once
#include "GameObject.h"

class Ball : public GameObject
{
    private:
        CP_Vector direction;
        static constexpr float speed = 150.f;
        static constexpr float radius = 5.f;

    public:
        Ball(float x, float y, CP_Vector d);

        void move() override;
        void draw() override;
        
        float GetSpeed() const {return speed;};
        float GetRadius() const {return radius;};
        CP_Vector GetDirection() const {return direction;};
        void SetDirection(CP_Vector newDirection);
};