#pragma once

#include <functional>
#include <vector>
#include <unordered_set>


class TickEventManager
{
public:
    TickEventManager();
    void trigger();
    void subscribe(std::function<void()> func);
    void unsubscribe(std::function<void()> func);

private:
    struct FunctionHasher
    {
        size_t operator()(const std::function<void()>& func) const
        {
            return reinterpret_cast<size_t>(&func);
        }
    };
    struct FunctionComparator
    {
    public:
        bool operator()(const std::function<void()>& func1, const std::function<void()>& func2) const
        {
            return reinterpret_cast<size_t>(&func1) == reinterpret_cast<size_t>(&func2);
        }
    };

    std::unordered_set <std::function<void()>, FunctionHasher, FunctionComparator> subscribers;
};

class KeyEventManager
{
public:
    KeyEventManager();
    void trigger(int keycode);
    void subscribe(std::function<void(int)> func);
    void unsubscribe(std::function<void(int)> func);

private:
    struct FunctionHasher
    {
        size_t operator()(const std::function<void(int)>& func) const
        {
            return reinterpret_cast<size_t>(&func);
        }
    };
    struct FunctionComparator
    {
    public:
        bool operator()(const std::function<void(int)>& func1, const std::function<void(int)>& func2) const
        {
            return reinterpret_cast<size_t>(&func1) == reinterpret_cast<size_t>(&func2);
        }
    };


    std::unordered_set <std::function<void(int)>, FunctionHasher, FunctionComparator> subscribers;
};
