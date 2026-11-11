#include "CollisionManager.h"
#include "GOManager.h"
#include "GameObject.h"
#include "Player.h"
#include "Balls.h"
#include "Block.h"

namespace
{
    bool IsBallCollidingWithObject(const Ball& ball, const GameObject &target)
    {
        // player의 현재 위치와 크기 정보 호출
        const CP_Vector target_loc = target.GetLocation();
        const CP_Vector target_size = target.GetSize();

        // ball의 현재 위치와 반지름 정보 호출
        const CP_Vector ball_loc = ball.GetLocation();
        const float ball_radius = ball.GetRadius();

        // 가져온 target 정보를 이용해 위치에 따른 범위 계산
        const float target_left = target_loc.x - (target_size.x/2.f);
        const float target_right = target_loc.x + (target_size.x/2.f);
        const float target_top = target_loc.y - (target_size.y/2.f);
        const float target_btm = target_loc.y + (target_size.y/2.f);

        // ball과 target를 clamp
        const float closestX = CP_Math_ClampFloat(ball_loc.x, target_left, target_right);
        const float closestY = CP_Math_ClampFloat(ball_loc.y, target_top, target_btm);

        // 두점 사이의 거리 공식을 이용하여 충돌 판정
        const float dx = ball_loc.x - closestX;
        const float dy = ball_loc.y - closestY;

        return dx*dx + dy*dy <= ball_radius * ball_radius;
    }
}
void CollisionManager::CollisionCheck()
{
    GOManager &manager = GOManager::GetInstance();

    // 등록된 객체 쌍의 충돌 확인
    for(Ball* ball : manager.GetBalls())
    {
        // 충돌이 있어난 GO들이 있다면 서로의 관계를 파악: Ball <-> Player, Ball <-> Block(Wall)  
        for(GameObject *target : manager.GetTargets())
        {
            // Ball <-> Player: 공은 플레이어와 닿으면 튕겨진다.
            if(auto *player = dynamic_cast<Player*>(target))
            {
                if(IsBallCollidingWithObject(*ball, *player))
                {
                    // ball->SetDirection({0.f, -1.f});
                    // 튕기는 각도 계산 후 방향 설정
                    CP_Vector cur_dir = ball->GetDirection();
                    CP_Vector nor_dir = CP_Vector_Normalize(cur_dir);
                    nor_dir.x *= std::cosf(CP_Math_Radians(90.f));
                    nor_dir.y *= std::sinf(CP_Math_Radians(90.f));
                    nor_dir.x *= ball->GetSpeed();
                    nor_dir.y *= ball->GetSpeed();
                    cur_dir = nor_dir;
                    ball->SetDirection(cur_dir);
                }
            }
            // Ball <-> Block: 공은 블록을 부수고 튕겨진다. Ball <-> Wall: 공은 블록을 부수지는 못하고 튕겨진다.
            else if(auto *block = dynamic_cast<Block*>(target))
            {
                if(block->GetisWall()) // true -> Wall
                {
                    // 튕기는 각도 계산 후 방향 설정
                }
                else // false -> Block
                {
                    if(IsBallCollidingWithObject(*ball, *block))
                    {
                        block->SetAliveState(false);
                    }
                    // 각도 맞춰서 튕기는 로직 구현하기
                    
                }
            }
        }
    }
}
