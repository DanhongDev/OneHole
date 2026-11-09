#include "Block.h"
#include "cprocessing.h"

#include <vector>
using namespace std;

Block::Block(float x, float y, bool isWall) : GameObject{x, y}, isWall(isWall) {}

void Block::draw()
{
    if(!isAlive) return;

    CP_Settings_Fill(isWall ? CP_Color_Create(80, 80, 80, 255) : CP_Color_Create(255, 255, 255, 255));

    CP_Graphics_DrawRect(coordX, coordY, 10, 10);
}