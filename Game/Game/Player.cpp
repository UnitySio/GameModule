#include "pch.h"
#include "Player.h"
#include "Window.h"

using namespace std;

Player::Player() :
	move_speed_(100.f)
{
	sprite_.Load(L"Resources/Character_Sheet.bmp");
}

void Player::Update()
{
	HWND focus = GetFocus();

	if (focus != nullptr)
	{
		if (GetAsyncKeyState(VK_LEFT) & 0x8000)
		{
			Translate(Vector2().Left() * move_speed_ * DELTA_TIME);
		}

		if (GetAsyncKeyState(VK_RIGHT) & 0x8000)
		{
			Translate(Vector2().Right() * move_speed_ * DELTA_TIME);
		}

		if (GetAsyncKeyState(VK_UP) & 0x8000)
		{
			Translate(Vector2().Up() * move_speed_ * DELTA_TIME);
		}

		if (GetAsyncKeyState(VK_DOWN) & 0x8000)
		{
			Translate(Vector2().Down() * move_speed_ * DELTA_TIME);
		}
	}
}

void Player::LateUpdate()
{
}

void Player::PhysicsUpdate()
{
}

void Player::Render()
{
}
