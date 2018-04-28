#pragma once

#include <functional>
#include <vector>
#include <unordered_set>


class TickEventManager
{
public:
    TickEventManager();
    void trigger();
    void subscribe(std::function<void()>* func);
    void unsubscribe(std::function<void()>* func);

private:
    std::unordered_set<std::function<void()>*> subscribers;
};


template <typename T>
class EventManager
{
public:
    EventManager() {}
    void trigger(T arg)
    {
        for (std::function<void(T)>* func : subscribers)
        {
            (*func)(arg);
        }
    }
    void subscribe(std::function<void(T)>* func)
    {
        subscribers.insert(func);
    }
    void unsubscribe(std::function<void(T)>* func)
    {
        subscribers.erase(func);
    }

private:
    std::unordered_set <std::function<void(T)>*> subscribers;
};
