#include "EventManager.h"

TickEventManager::TickEventManager()
{
}

void TickEventManager::trigger()
{
    for (std::function<void()>* func : subscribers)
    {
        (*func)();
    }
}

void TickEventManager::subscribe(std::function<void()>* func)
{
    subscribers.insert(func);
}

void TickEventManager::unsubscribe(std::function<void()>* func)
{
    subscribers.erase(func);
}


KeyEventManager::KeyEventManager()
{
}

void KeyEventManager::trigger(int keycode)
{
    for (std::function<void(int)>* func : subscribers)
    {
        (*func)(keycode);
    }
}

void KeyEventManager::subscribe(std::function<void(int)>* func)
{
    subscribers.insert(func);
}

void KeyEventManager::unsubscribe(std::function<void(int)>* func)
{
    subscribers.erase(func);
}
