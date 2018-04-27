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

class KeyEventManager
{
public:
    KeyEventManager();
    void trigger(int keycode);
    void subscribe(std::function<void(int)>* func);
    void unsubscribe(std::function<void(int)>* func);

private:
    std::unordered_set <std::function<void(int)>*> subscribers;
};
