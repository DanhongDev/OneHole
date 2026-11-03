#pragma once

void block_init();
void block_update();
void block_exit();

void DrawBlock();

class Block
{
    private:
    int x;
    int y;
    bool isWall;
    bool isAlive;

    public:
    Block(int x, int y, bool isWall);
    void draw() const;
};