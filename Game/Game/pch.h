#pragma once
#pragma comment(lib, "Msimg32.lib")
#pragma comment(lib, "fmod_vc.lib")
#pragma comment(lib, "Gdiplus.lib")

#include <Ole2.h>
#include <gdiplus.h>
#include <mutex>
#include <list>
#include <algorithm>

#include "Vector2.h"
#include "TimeManager.h"

#define DELTA_TIME TimeManager::GetInstance()->GetDeltaTime()

enum class SceneType : size_t
{
	kDefault = 0,
	kEnd // kEnd�� �׻� �������� �־�� �մϴ�.
};

enum class LayerType : size_t
{
	kDefault = 0,
	kEnd // kEnd�� �׻� �������� �־�� �մϴ�.
};

class pch
{
};
