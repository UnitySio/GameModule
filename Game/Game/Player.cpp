#include "pch.h"
#include "Player.h"
#include "Window.h"
#include "SpriteRenderer.h"

using namespace std;

Player::Player() :
	move_speed_(100.f)
{
	shared_ptr<Texture> sprite_ = make_shared<Texture>();
	sprite_->Load(L"Resources/0.bmp");
	sprite_->SetPivot({ 0.5f, 1.f });

	AddSpriteRenderer();
	GetSpriteRenderer()->SetSprite(sprite_);

	AddAnimator();
}

void Player::Update()
{
	Object::Update();

	HWND focus = GetFocus();

	if (focus != nullptr)
	{
		if (GetAsyncKeyState('A') & 0x8000)
		{
			Translate(Vector2().Left() * move_speed_ * DELTA_TIME);
		}

		if (GetAsyncKeyState('D') & 0x8000)
		{
			Translate(Vector2().Right() * move_speed_ * DELTA_TIME);
		}

		if (GetAsyncKeyState('W') & 0x8000)
		{
			Translate(Vector2().Up() * move_speed_ * DELTA_TIME);
		}

		if (GetAsyncKeyState('S') & 0x8000)
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
	Object::Render();

	if (GetAsyncKeyState(VK_LBUTTON) & 0x8000)
	{
		HPEN new_pen = CreatePen(PS_SOLID, 0, RGB(255, 0, 0));
		HPEN old_pen = (HPEN)SelectObject(WINDOW->GetHDC(), new_pen);

		MoveToEx(WINDOW->GetHDC(), GetPosition().x_, GetPosition().y_, NULL);
		LineTo(WINDOW->GetHDC(), MOUSE_POSITION.x_, MOUSE_POSITION.y_);

		SelectObject(WINDOW->GetHDC(), old_pen);
		DeleteObject(new_pen);
	}
}
