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
        GOManager(const GOManager&) = delete; // 왜 const GOManager& 인지에 대해서
        GOManager& operator=(const GOManager&) = delete; // 이 연산자 오버라이딩에 대해서
        // 인스턴스 복사를 막아야 하는 이유

    public:
        static GOManager& GetInstance();

        void Add(GameObject* obj);
        void Update();
        void Clear();
};