#include "GOManager.h"
#include "GameObject.h"

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
    if(obj)
    {
        objects.push_back(obj);
    }
}

void GOManager::Update()
{
    for(GameObject *o : objects)
    {
        o->move();
        o->draw();
    }
}

void GOManager::Exit()
{
    for(GameObject *o : objects) delete o;
    objects.clear();
}


