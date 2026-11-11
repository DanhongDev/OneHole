#pragma once
#include "GameObject.h"

class Block : public GameObject
{
    private:
    bool isWall;
    static constexpr float width = 10.f;
    static constexpr float height = 10.f;

    public:
    Block(float x, float y, bool isWall);

    void draw() override;
    CP_Vector GetSize() const override;
    
    bool GetisWall() const {return isWall;};
};