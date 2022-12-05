#pragma once

#include "Singleton.h"

class InputManager :
    public Singleton<InputManager>
{
private:
    enum class KeyType : UINT
    {
        kNone = 0,
        kDown,
        kHold,
        kUp
    };

    struct Key
    {
        KeyType type;
        bool is_down;
    };

    std::map<int, Key> keys_;
public:
    InputManager();
    ~InputManager() final = default;

    void Initiate();
    void AddKey(int key);
    void InputUpdate();

    bool GetKeyDown(int key);
    bool GetKey(int key);
    bool GetKeyUp(int key);
};
