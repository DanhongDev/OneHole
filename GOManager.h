#pragma once
#include <vector>

class GameObject;

class GOManager
{
    private:
        std::vector<GameObject*> objects;
        
        GOManager() = default;
        ~GOManager();

        // 인스턴스 복제 방지 (복사생성, 대입 막기)
        GOManager(const GOManager&) = delete;
        GOManager& operator=(const GOManager&) = delete;

    public:
        static GOManager& GetInstance();

        void Add(GameObject* obj);
        void Update();
        void Exit();
};