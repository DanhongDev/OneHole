#include "GOManager.h"
#include "GameObject.h"

GOManager::~GOManager()
{
    Clear();
}

GOManager &GOManager::GetInstance()
{
    static GOManager ptr;
    return ptr;
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

void GOManager::Clear()
{
    for(GameObject *o : objects) delete o;
    objects.clear();
}


