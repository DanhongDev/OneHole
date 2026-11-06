#include "GOManager.h"
#include "GameObject.h"
#include "Balls.h"

#include <algorithm>

GOManager::~GOManager()
{
    Exit();
}

GOManager &GOManager::GetInstance()
{
    static GOManager instance;
    return instance;
}

void GOManager::Add(GameObject *obj)
{
    // RTTI의 dynamic_cast를 사용할 수 있어. GameObject에는 가상 함수가 있으므로 변환이 가능해. --> 에 대해 질문해보기
    if(obj == nullptr) return;
    
    objects.push_back(obj);

    if(auto *ball = dynamic_cast<Ball*>(obj)) //<dynamic_cast<Ball*>(obj)에 대한 코드에 대해 질문하기
    {
        balls.push_back(ball);
    }
    else
    {
        targets.push_back(obj);
    }
}

void GOManager::Update()
{
    for(GameObject *o : objects)
    {
        o->move();
    }
}

void GOManager::Draw()
{
    for(GameObject *o : objects)
    {
        o->draw();
    }
}

void GOManager::Remove(GameObject *obj)
{
    if(obj == nullptr) return;

    // balls에서 포인터 제거
    if(auto *ball = dynamic_cast<Ball*>(obj))
    {
        balls.erase(std::remove(balls.begin(), balls.end(), ball), balls.end());
    }

    // targets에서 포인터 제거
    targets.erase(std::remove(targets.begin(), targets.end(), obj), targets.end());

    // objects에서 delete
    auto it = std::find(objects.begin(), objects.end(), obj);
    if(it != objects.end())
    {
        delete *it;
        objects.erase(it);
    }
}

void GOManager::Exit()
{
    for(GameObject *o : objects) delete o;
    objects.clear();
    balls.clear();
    targets.clear();
}


