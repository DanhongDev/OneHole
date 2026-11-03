#pragma once

void player_init();
void player_update();
void player_exit();

class Player
{
    private:
    float coordX, coordY;
    int bar_sizeX, bar_sizeY;

    public:
    Player(float coordX, float coordY, int bar_sizeX, int bar_sizeY);
    void move();
    void draw();
};