#include "cprocessing.h"
#include "Player.h"
#include "WinodwConfig.h"

namespace
{
    Player *player = nullptr;
}

void player_init()
{
    player = new Player(1000.f, 680.f, 100, 10);
}
void player_update()
{
    if(player)
    {
        player->move();
        player->draw();
    }
}
void player_exit()
{
    delete player;
    player = nullptr;
}

Player::Player(float coordX, float coordY, int bar_sizeX, int bar_sizeY) : coordX(coordX), coordY(coordY), bar_sizeX(bar_sizeX), bar_sizeY(bar_sizeY) {}

void Player::move()
{
    float mouseX = CP_Input_GetMouseX();
    if(mouseX <= (bar_sizeX/2)) mouseX = (bar_sizeX/2);
    else if(mouseX >= window_config.width - (bar_sizeX/2)) mouseX = window_config.width - (bar_sizeX/2);

    coordX = mouseX;
}

void Player::draw()
{
    CP_Settings_Fill(CP_Color_Create(0, 255, 0, 255));
    CP_Graphics_DrawRect(coordX, coordY, bar_sizeX, bar_sizeY);
}
