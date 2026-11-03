#include "Balls.h"

#include <vector>
using namespace std;

namespace
{
    vector<Ball> ball;
}
void balls_init()
{
    ball.push_back(Ball(900.f, 680.f, {0.f, -1.f}));
}
void balls_update()
{
    
}
void balss_exit()
{

}

// Constructor
Ball::Ball(float X, float Y, CP_Vector v) : coordX(X), coordY(Y), velocity(v) {}