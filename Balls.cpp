#include "Balls.h"

Ball::Ball(float x, float y, CP_Vector d) : GameObject(x, y), direction(CP_Vector_Normalize(d)) {}

void Ball::move()
{
    float dt = CP_System_GetDt();
    coordX += direction.x * speed * dt;
    coordY += direction.y * speed * dt;
}

void Ball::draw()
{
    CP_Settings_Fill(CP_Color_Create(255, 0, 0, 255));
    CP_Graphics_DrawCircle(coordX, coordY, 10.f);
}
