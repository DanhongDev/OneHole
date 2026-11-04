#pragma once
#include "GameObject.h"

class Player : public GameObject
{
    private:
        int width;
        int height;

    public:
        Player(float x, float y, int w, int h);
        void move() override;
        void draw() override;
};