#ifndef STATEMANAGER_HPP
#define STATEMANAGER_HPP

#include <memory>
#include <stack>
#include <iostream>

#include "State/BaseState.hpp"

template <class Owner> class StateManager
{
public:
    StateManager() = default;

    std::shared_ptr<BaseState> top();
    template <class T> void push(Owner* owner);
    void pop();

private:
    std::stack<std::shared_ptr<BaseState>> m_states;
};

template <class Owner>
std::shared_ptr<BaseState> StateManager<Owner>::top()
{
    if (m_states.size())
    {
        return m_states.top();
    }

    throw std::runtime_error("[StateManager::top()] No states left in stack");
}

template <class Owner>
template <class T>
void StateManager<Owner>::push(Owner* owner)
{
    if (m_states.size())
    {
        top()->onInactive();
    }

    m_states.push(std::make_shared<T>(owner));
}

template <class Owner>
void StateManager<Owner>::pop()
{
    if (m_states.size())
    {
        m_states.pop();

        if (m_states.size())
        {
            top()->onActive();
        }
    }
    else
    {
        throw std::runtime_error("[StateManager::pop()] No states left in stack");
    }
}

#endif //STATEMANAGER_HPP
