#pragma once
class State
{
private:
public:
    State() = default;
    virtual ~State() = default;

    virtual void OnStateEnter() = 0;
    virtual void OnStateUpdate() = 0;
    virtual void OnStateExit() = 0;
};
