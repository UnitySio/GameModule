#pragma once
#pragma comment(lib, "fmod_vc.lib")
#pragma comment(lib, "Gdiplus.lib")

#include <Ole2.h>
#include <gdiplus.h>
#include <mutex>
#include <vector>

#include "Vector2.h"
#include "TimeManager.h"

#define DELTA_TIME TimeManager::GetInstance()->GetDeltaTime();

class pch
{
};

