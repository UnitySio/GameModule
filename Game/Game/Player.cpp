#include "pch.h"
#include "Player.h"
#include "Window.h"
#include "SpriteRenderer.h"
#include "InputManager.h"

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

	shared_ptr<Texture> sprite_sheet_ = make_shared<Texture>();
	sprite_sheet_->Load(L"Resources/WarriorSheet.bmp");
	sprite_sheet_->SetPivot({ 0.4f, 1.f });

	temp_ = make_shared<Temp>();
	temp_->SetTexture(sprite_sheet_);
	temp_->Slice(6, 17);
}

void Player::Update()
{
	//Object::Update();
	temp_->Update();

	HWND focus = GetFocus();

	if (focus != nullptr)
	{
		if (InputManager::GetInstance()->GetKeyDown('A'))
		{
			temp_->SetClip("WALK");
		}

		if (InputManager::GetInstance()->GetKey('A'))
		{
			Translate(Vector2().Left() * move_speed_ * DELTA_TIME);
		}

		if (InputManager::GetInstance()->GetKeyUp('A'))
		{
			temp_->SetClip("IDLE");
		}

		if (InputManager::GetInstance()->GetKeyDown('D'))
		{
			temp_->SetClip("WALK");
		}

		if (InputManager::GetInstance()->GetKey('D'))
		{
			Translate(Vector2().Right() * move_speed_ * DELTA_TIME);
		}

		if (InputManager::GetInstance()->GetKeyUp('D'))
		{
			temp_->SetClip("IDLE");
		}

		if (InputManager::GetInstance()->GetKeyDown('W'))
		{
			temp_->SetClip("WALK");
		}

		if (InputManager::GetInstance()->GetKey('W'))
		{
			Translate(Vector2().Up() * move_speed_ * DELTA_TIME);
		}

		if (InputManager::GetInstance()->GetKeyUp('W'))
		{
			temp_->SetClip("IDLE");
		}

		if (InputManager::GetInstance()->GetKeyDown('S'))
		{
			temp_->SetClip("WALK");
		}

		if (InputManager::GetInstance()->GetKey('S'))
		{
			Translate(Vector2().Down() * move_speed_ * DELTA_TIME);
		}

		if (InputManager::GetInstance()->GetKeyUp('S'))
		{
			temp_->SetClip("IDLE");
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
	//Object::Render();

	temp_->Render(GetPosition(), GetScale());

	HPEN new_pen = CreatePen(PS_SOLID, 0, RGB(255, 0, 0));
	HPEN old_pen = (HPEN)SelectObject(WINDOW->GetHDC(), new_pen);

	MoveToEx(WINDOW->GetHDC(), GetPosition().x_, GetPosition().y_, NULL);
	LineTo(WINDOW->GetHDC(), MOUSE_POSITION.x_, MOUSE_POSITION.y_);

	SelectObject(WINDOW->GetHDC(), old_pen);
	DeleteObject(new_pen);
}
