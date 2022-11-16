#pragma once
#pragma comment(lib, "Msimg32.lib")
//#pragma comment(lib, "fmod_vc.lib")
#pragma comment(lib, "Gdiplus.lib")
#pragma comment(lib, "ws2_32.lib")

#include <WinSock2.h>
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
#define TIME TimeManager::GetInstance()
#define SCENE SceneManager::GetInstance()
#define INPUT InputManager::GetInstance()
#define COLLISION CollisionManager::GetInstance()
#define CAMERA Camera::GetInstance()
#define DELTA_TIME TimeManager::GetInstance()->GetDeltaTime()
#define MOUSE_POSITION Window::GetInstance()->GetMousePosition()

struct FloatRect
{
	float left;
	float top;
	float right;
	float bottom;
};

enum class SceneType : size_t
{
	kDefault = 0,
	kEnd // kEnd는 항상 마지막에 있어야 합니다.
};

enum class LayerType : size_t
{
	kDefault = 0,
	kGround,
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

class pch
{
};
