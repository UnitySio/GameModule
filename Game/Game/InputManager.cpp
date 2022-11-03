#include "pch.h"
#include "InputManager.h"

using namespace std;

// 멤버 변수 초기화
shared_ptr<InputManager> InputManager::instance_ = nullptr;
once_flag InputManager::flag_;

InputManager::InputManager() :
	keys_()
{
}

shared_ptr<InputManager> InputManager::GetInstance()
{
	call_once(flag_, [] // 람다식
		{
			instance_.reset(new InputManager);
		});

	return instance_;
}

void InputManager::Release()
{
	instance_.reset();
}

void InputManager::Initiate()
{
	// 사용할 키들을 추가
	AddKey(VK_UP);
	AddKey(VK_LEFT);
	AddKey(VK_DOWN);
	AddKey(VK_RIGHT);
	AddKey(VK_LCONTROL);
	AddKey(VK_LSHIFT);
}

void InputManager::AddKey(int key)
{
	keys_.insert({ key, {} });
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
