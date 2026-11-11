#include "Player.h"
#include "WinodwConfig.h"

Player::Player(float x, float y, int w, int h) : GameObject(x, y), width(w), height(h) {}

void Player::move()
{
    float mouseX = CP_Input_GetMouseX();
    if(mouseX <= (width/2)) mouseX = (width/2);
    else if(mouseX >= window_config.width - (width/2)) mouseX = window_config.width - (width/2);

    coordX = mouseX;
}

void Player::draw()
{
    CP_Settings_Fill(CP_Color_Create(0, 255, 0, 255));
    CP_Graphics_DrawRect(coordX, coordY, width, height);
}

CP_Vector Player::GetSize() const
{
    return {width, height};
}
