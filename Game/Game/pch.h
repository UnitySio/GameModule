#pragma once
#pragma comment(lib, "Msimg32.lib")
#pragma comment(lib, "Gdiplus.lib")

#define _CRTDBG_MAP_ALLOC

#include <stdlib.h>
#include <crtdbg.h>
#include <conio.h>
#include <Ole2.h>
#include <gdiplus.h>
#include <mutex>
#include <vector>
#include <map>

#include "Vector2.h"

/* GetAsyncKeyState
0x0000 - 이전에도 키가 입력되지 않았으며, 호출 시점에도 키가 입력되지 않음
0x0001 - 이전에 키가 입력되었지만, 호출 시점에는 키가 입력되지 않음
0x8000 - 이전에는 키가 입력되지 않았지만, 호출 시점에는 키가 입력됨
0x8001 - 이전에도 키가 입력되었으며, 호출 시점에도 키가 입력됨
*/

#define GetKeyDown(virtual_key) (GetAsyncKeyState(virtual_key) & 0x0001)
#define GetKey(virtual_key) (GetAsyncKeyState(virtual_key) & 0x8000)

enum class SceneType
{
	kTestScene = 0,
	kEnd // 항상 마지막에 있어야 함
};

enum class LayerType
{
	kDefault = 0,
	kPlayer,
	kEnd // 항상 마지막에 있어야 함
};

class pch
{
};
