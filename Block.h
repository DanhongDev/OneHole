#pragma once
#include "GameObject.h"

class Block : public GameObject
{
    private:
    bool isWall;

    public:
    Block(float x, float y, bool isWall);
    void draw() override;
    bool GetisWall() const {return isWall;};
};