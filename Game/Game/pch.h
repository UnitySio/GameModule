#pragma once
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
0x0000 - �������� Ű�� �Էµ��� �ʾ�����, ȣ�� �������� Ű�� �Էµ��� ����
0x0001 - ������ Ű�� �ԷµǾ�����, ȣ�� �������� Ű�� �Էµ��� ����
0x8000 - �������� Ű�� �Էµ��� �ʾ�����, ȣ�� �������� Ű�� �Էµ�
0x8001 - �������� Ű�� �ԷµǾ�����, ȣ�� �������� Ű�� �Էµ�
*/

#define GetKeyDown(virtual_key) (GetAsyncKeyState(virtual_key) & 0x0001)
#define GetKey(virtual_key) (GetAsyncKeyState(virtual_key) & 0x8000)

enum class SceneType
{
	kTESTSCENE = 0,
	kEND // �׻� �������� �־�� ��
};

enum class GroupObjectType
{
	kDEFAULT = 0,
	kPLAYER,
	kEND // �׻� �������� �־�� ��
};

class pch
{
};

