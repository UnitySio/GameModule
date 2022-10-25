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
#include <algorithm>

#include "Vector2.h"
#include "TimeManager.h"

#define _CRTDBG_MAP_ALLOC
#define DELTA_TIME TimeManager::GetInstance()->GetDeltaTime()

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

class pch
{
};
