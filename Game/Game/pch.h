#pragma once
#pragma comment(lib, "Gdiplus.lib")

#include <Ole2.h>
#include <gdiplus.h>
#include <mutex>
#include <vector>

#include "Vector2.h"

/* GetAsyncKeyState
0x0000 - �������� Ű�� �Էµ��� �ʾ�����, ȣ�� �������� Ű�� �Էµ��� ����
0x0001 - ������ Ű�� �ԷµǾ�����, ȣ�� �������� Ű�� �Էµ��� ����
0x8000 - �������� Ű�� �Էµ��� �ʾ�����, ȣ�� �������� Ű�� �Էµ�
0x8001 - �������� Ű�� �ԷµǾ�����, ȣ�� �������� Ű�� �Էµ�
*/

#define GetKeyDown(virtual_key) (GetAsyncKeyState(virtual_key) & 0x8000)

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

