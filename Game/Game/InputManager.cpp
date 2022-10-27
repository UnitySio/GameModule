#include "pch.h"
#include "InputManager.h"

using namespace std;

// ��� ���� �ʱ�ȭ
shared_ptr<InputManager> InputManager::instance_ = nullptr;
once_flag InputManager::flag_;

InputManager::InputManager() :
	keys_()
{
}

shared_ptr<InputManager> InputManager::GetInstance()
{
	call_once(flag_, [] // ���ٽ�
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
	// ����� Ű���� �߰�
	AddKey('W');
	AddKey('A');
	AddKey('S');
	AddKey('D');
	AddKey(MK_LBUTTON);
}

void InputManager::AddKey(int key)
{
	keys_.insert({ key, {} });
}

void InputManager::Update()
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
