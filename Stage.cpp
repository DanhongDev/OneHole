#include "Stage.h"
#include "Block.h"
#include "GOManager.h"
#include "Player.h"
#include "Balls.h"

void stage_init()
{
    block_init();
    GOManager& manager = GOManager::GetInstance();

    manager.Add(new Player(1000.f, 680.f, 100.f, 10));
    manager.Add(new Ball(640.f, 500.f, {0.f, 1.f}));
}

void stage_update()
{
	CP_Graphics_ClearBackground(CP_Color_Create(0,0,0,255));
    block_update();
    GOManager::GetInstance().Update();
}

void stage_exit()
{
    block_exit();
    GOManager::GetInstance().Clear();
}