#include "Stage.h"
#include "cprocessing.h"
#include "Block.h"
#include "GOManager.h"
#include "Player.h"
#include "Balls.h"
#include "Block.h"
#include "CollisionManager.h"

// 일단 Stage.h/.cpp 에서 stage_01, _02, ... 해보고 나중에 필요할 때 StageManager와 같은 stage관련 매니저 만들어보기
namespace
{
    const int rows = 40, cols = 121;
    const int startX = 50, startY = 50;
    const int gap = 10;
    const int block_size = 10;
}
void Stage_01()
{
    GOManager &manager = GOManager::GetInstance();

    const int hole_row = rows - 5;
    const int hole_col = cols / 2;

    for(int row=0; row<rows; row++)
    {
        for(int col=0; col<cols; col++)
        {
            const bool is_hole = row >= hole_row && col == hole_col;
            if(is_hole) continue;

            bool isWall = false;
            if(row == 0 || row == rows - 1 || col == 0 || col == cols - 1) isWall = true;
            else if(row >= hole_row && (col == hole_col - 1 || col == hole_col + 1)) isWall = true;
            else isWall = false;

            manager.Add(new Block(startX + (col * gap), startY + (row * gap), isWall));
        }
    }
    return;
}

void stage_init()
{
    // Stage 1. 세팅
    Stage_01();

    GOManager &manager = GOManager::GetInstance();
    manager.Add(new Player(1000.f, 680.f, 100.f, 10));
    manager.Add(new Ball(640.f, 500.f, {0.f, 1.f}));
}

void stage_update()
{
	CP_Graphics_ClearBackground(CP_Color_Create(0,0,0,255));

    GOManager &manager = GOManager::GetInstance();
    // 각 GO들의 상태를 업데이트를 먼저 한 후
    manager.Update();

    // Collision 판단
    static CollisionManager collisionmanager; // update()가 호출될 때마다 새로 만드는거 방지 --> static 선언
    collisionmanager.CollisionCheck();

    // 부서진 블록들 제거 작업
    manager.RemoveDeadObjects();

    // 작업 후 그리기
    manager.Draw();
}

void stage_exit()
{
    GOManager::GetInstance().Exit();
}