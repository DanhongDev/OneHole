#include "CollisionManager.h"
#include "GOManager.h"
#include "GameObject.h"
#include "Player.h"
#include "Balls.h"

namespace
{
    float Clamp(float val, float min_val, float max_val)
    {
        if(val < min_val) return min_val;
        if(val > max_val) return max_val;
        return val;
    }

    bool IsBallCollidingWithPlayer(const Ball& ball, const Player &player)
    {
        // player의 현재 위치와 크기 정보 호출
        const CP_Vector player_loc = player.GetLocation();
        const CP_Vector player_size = player.GetSize();

        const // ball의 현재 위치와 반지름 정보 호출
        const CP_Vector ball_loc = ball.GetLocation();
        const float ball_radius = ball.GetRadius();

        const // 가져온 player 정보를 이용해 위치에 따른 범위 계산
        const float player_left = player_loc.x - (player_size.x/2.f);
        const float player_right = player_loc.x + (player_size.x/2.f);
        const float player_top = player_loc.y - (player_size.y/2.f);
        const float player_btm = player_loc.y + (player_size.y/2.f);

        const // ball과 player를 clamp
        const float closestX = Clamp(ball_loc.x, player_left, player_right);
        const float closestY = Clamp(ball_loc.y, player_top, player_btm);

        const // 두점 사이의 거리 공식을 이용하여 충돌 판정
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
        for(GameObject *target : manager.GetTargets())
        {
            // Ball <-> Player
            if(auto *player = dynamic_cast<Player*>(target))
            {
                if(IsBallCollidingWithPlayer(*ball, *player))
                {
                    ball->SetDirection({0.f, -1.f});
                }
            }
            // Ball <-> Blocks
            // else if(auto *block = dynamic_cast<Block>(target))
            // {

            // }
        }
    }
}
