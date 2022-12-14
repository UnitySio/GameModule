#include "pch.h"
#include "InputManager.h"

using namespace std;

InputManager::InputManager() :
    keys_()
{
}

void InputManager::Initiate()
{
    // 사용할 키들을 추가
    AddKey(VK_SPACE);
    AddKey('A');
    AddKey(VK_DOWN);
    AddKey('D');
    AddKey(MK_RBUTTON);
    AddKey(VK_LSHIFT);
    AddKey(MK_LBUTTON);
    AddKey('R');
    AddKey(VK_LEFT);
    AddKey(VK_RIGHT);
}

void InputManager::AddKey(int key)
{
    keys_.insert({key, {}});
}

void InputManager::InputUpdate()
{
    HWND focus = GetFocus();

    if (focus != nullptr)
    {
        map<int, Key>::iterator iter = keys_.begin();

        for (; iter != keys_.end(); ++iter)
        {
            if (GetAsyncKeyState(iter->first) & 0x8000)
            {
                if (iter->second.is_down)
                {
                    iter->second.type = KeyType::kHold;
                }
                else
                {
                    iter->second.type = KeyType::kDown;
                }

                iter->second.is_down = true;
            }
            else
            {
                if (iter->second.is_down)
                {
                    iter->second.type = KeyType::kUp;
                }
                else
                {
                    iter->second.type = KeyType::kNone;
                }

                iter->second.is_down = false;
            }
        }
    }
    else
    {
        map<int, Key>::iterator iter = keys_.begin();

        for (; iter != keys_.end(); ++iter)
        {
            iter->second.is_down = false;
            if (iter->second.type == KeyType::kDown ||
                iter->second.type == KeyType::kHold)
            {
                iter->second.type = KeyType::kUp;
            }
            else
            {
                iter->second.type = KeyType::kNone;
            }
        }
    }
}

bool InputManager::GetKeyDown(int key)
{
    if (keys_[key].type == KeyType::kDown)
    {
        return true;
    }

    return false;
}

bool InputManager::GetKey(int key)
{
    if (keys_[key].type == KeyType::kHold)
    {
        return true;
    }

    return false;
}

bool InputManager::GetKeyUp(int key)
{
    if (keys_[key].type == KeyType::kUp)
    {
        return true;
    }

    return false;
}
