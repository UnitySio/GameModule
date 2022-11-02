#pragma once
#pragma comment(lib, "Msimg32.lib")
//#pragma comment(lib, "fmod_vc.lib")
#pragma comment(lib, "Gdiplus.lib")

#include <stdlib.h>
#include <crtdbg.h>
#include <Ole2.h>
#include <gdiplus.h>
#include <mutex>
#include <vector>
#include <list>
#include <map>
#include <algorithm>

#include "Vector2.h"
#include "TimeManager.h"

#define _CRTDBG_MAP_ALLOC
#define WINDOW Window::GetInstance()
#define TIME_MANAGER TimeManager::GetInstance()
#define SCENE_MANAGER SceneManager::GetInstance()
#define INPUT_MANAGER InputManager::GetInstance()
#define COLLISION_MANAGER CollisionManager::GetInstance()
#define DELTA_TIME TimeManager::GetInstance()->GetDeltaTime()
#define MOUSE_POSITION Window::GetInstance()->GetMousePosition()

enum class SceneType : size_t
{
	kDefault = 0,
	kEnd // kEnd는 항상 마지막에 있어야 합니다.
};

enum class LayerType : size_t
{
	kDefault = 0,
	kEnd // kEnd는 항상 마지막에 있어야 합니다.
};

enum class PlayerStateType : size_t
{
	kIdle = 0,
	kWalk,
	kJump,
	kFalling,
	kAttack,
	kEnd // kEnd는 항상 마지막에 있어야 합니다.
};

enum class PlayerClipType : size_t
{
	kIdle = 0,
	kWalk,
	kJump,
	kFalling,
	kAttack
};

class pch
{
};
