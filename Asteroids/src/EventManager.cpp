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
