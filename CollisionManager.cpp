#include "CollisionManager.h"
#include "GOManager.h"
#include "GameObject.h"
#include "Player.h"
#include "Balls.h"
#include "Block.h"

#include <cmath>

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

    CP_Vector GetNorVec(const Ball &ball, const GameObject &target)
    {
        const CP_Vector target_loc = target.GetLocation();
        const CP_Vector target_size = target.GetSize();
        const CP_Vector ball_loc = ball.GetLocation();

        if((target_loc.y - target_size.y/2.f <= ball_loc.y) && (ball_loc.y <= target_loc.y + target_size.y/2.f))
        {
            if(ball_loc.x <= target_loc.x - target_size.x/2.f) return {-1,0}; // left
            else if(target_loc.x + target_size.x/2.f <= ball_loc.x) return {1,0}; // right
        }
        else if((target_loc.x - target_size.x/2.f <= ball_loc.x) && (ball_loc.x <= target_loc.x + target_size.x/2.f))
        {
            if(ball_loc.y <= target_loc.y - target_size.y/2.f) return {0,-1}; // top
            else if(target_loc.y + target_size.y/2.f <= ball_loc.y) return {0,1}; // btm
        }

        return {0, 0};
    }
    bool ChangeDirection(const Ball &ball, const GameObject &target, CP_Vector &new_dir)
    {
        const CP_Vector v = CP_Vector_Normalize(ball.GetDirection());
        const CP_Vector n = GetNorVec(ball, target);

        // 면 법선을 구하지 못한 경우: 모서리 또는 중심이 사각형 안
        if(n.x == 0.f && n.y == 0.f) return false;

        const float dot = v.x * n.x + v.y * n.y;

        // 공이 면을 향해 움직이는 경우에만 반사
        if(dot >= 0.f) return false;

        new_dir = {v.x - (2.f * dot * n.x), v.y - (2.f * dot * n.y)};

        return true;
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
            // 이미 죽은 GO면 건너뛰기
            if(!target->GetAliveState()) continue;

            // Ball <-> Player: 공은 플레이어와 닿으면 튕겨진다.
            if(auto *player = dynamic_cast<Player*>(target))
            {
                if(IsBallCollidingWithObject(*ball, *player))
                {
                    // 방향 변경
                    CP_Vector new_dir;
                    if(ChangeDirection(*ball, *player, new_dir)) 
                    {
                        const CP_Vector normal = GetNorVec(*ball, *player);

                        // 플레이어 윗면에 부딪혔을 때만 반영
                        if(normal.y < 0.f)
                        {
                            const float offset = CP_Math_ClampFloat(
                                (ball->GetLocation().x - player->GetLocation().x) / (player->GetSize().x / 2.f), -1.f, 1.f);

                            const float dirX = CP_Math_ClampFloat(offset * 0.75f, -0.9f, 0.9f);

                            new_dir = {dirX, -std::sqrt(1.f - dirX * dirX)};
                        }
                        
                        ball->SetDirection(new_dir);
                    }
                }
            }
            // Ball <-> Block: 공은 블록을 부수고 튕겨진다. Ball <-> Wall: 공은 블록을 부수지는 못하고 튕겨진다.
            else if(auto *block = dynamic_cast<Block*>(target))
            {
                if(IsBallCollidingWithObject(*ball, *block))
                {
                    // 방향 변경
                    CP_Vector new_dir;
                    if(ChangeDirection(*ball, *block, new_dir)) 
                    {
                        ball->SetDirection(new_dir);

                        if(!block->GetisWall()) block->SetAliveState(false);
                    }
                }
            }

            // 공이 어쩔때 통과를 함 --> 공의 중심과 target사이의 거리가 <= radius로 계산하는데 계산하고 충돌 판정 나기 전에 조금 더 공이 나아가서 그런듯?
                // 부딪히는 범위를 살짝만 증가해줄까??
            
            // 화면 외각에 부딪혔을때도 처리하기.
                // 화면 외각에도 벽을 만들기 or 화면외각 값이용하여 처리하기
                // 아래로 떨어졌을땐 공 죽는걸로 설정하기
        }
    }
}
