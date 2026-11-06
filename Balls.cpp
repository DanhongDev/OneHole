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
    CP_Graphics_DrawCircle(coordX, coordY, (radius*2.f));
}

void Ball::SetDirection(CP_Vector newDirection)
{
    // 임시로 튕겼을때 위로만 튕기도록 해보기
    direction = newDirection;
    // 추후에 입사각과 반사각이 같음. 이 성질을 이용한 방향이 바뀌도록 계산하는 식 넣어보기
}
