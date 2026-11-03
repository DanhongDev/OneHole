#include "cprocessing.h"
#include "Stage.h"
#include "Block.h"
#include "Player.h"

void stage_init()
{
    block_init();
    player_init();
}

void stage_update()
{
	CP_Graphics_ClearBackground(CP_Color_Create(0,0,0,255));
    block_update();
    player_update();
}

void stage_exit()
{
    block_exit();
    player_exit();
}