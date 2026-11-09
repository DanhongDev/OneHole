#pragma once

#include <vector>

class GameObject;
class Ball;

class GOManager
{
    private:
        // objects는 실제 객체를 보관하고 있고 balls와 targets는 그 객체를 가리키는 포인터만 보관한다.
        // 따라서 delete는 objects내에서만 해야한다.
        std::vector<GameObject*> objects; // 게임에 등록된 모든 GO들
        std::vector<Ball*> balls; // Ball만 모은 컨테이너
        std::vector<GameObject*> targets; // balls과 Collision이 일어나는 GO들
        
        GOManager() = default;
        ~GOManager();

        // 인스턴스 복제 방지 (복사생성, 대입 막기)
        GOManager(const GOManager&) = delete;
        GOManager& operator=(const GOManager&) = delete;

    public:
        static GOManager &GetInstance();

        const std::vector<Ball*> &GetBalls() const {return balls;};
        const std::vector<GameObject*> &GetTargets() const {return targets;};
        
        void Add(GameObject* obj);
        void Update();
        void Draw();
        void RemoveDeadObjects();
        void Remove(GameObject* obj);
        void Exit();
};