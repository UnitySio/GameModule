#include "pch.h"
#include "Player.h"
#include "Window.h"
#include "SpriteRenderer.h"

using namespace std;

Player::Player() :
	move_speed_(100.f),
	idx_(),
	timer_()
{
	WCHAR word[128];
	for (int i = 0; i < 4; i++)
	{
		wsprintf(word, L"Resources/%d.bmp", i);
		shared_ptr<Texture> sprite_ = make_shared<Texture>();
		sprite_->Load(word);
		sprite_->SetPivot({ 0.5f, 1.f });
		sprites_.push_back(sprite_);
	}

	//sprites_[1]->SetPivot({ 0.5f, 0.5f });
	//sprites_[3]->SetPivot({ 0.5f, 0.5f });

	AddSpriteRenderer();
	GetSpriteRenderer()->SetSprite(sprites_[0]);

	AddAnimator();
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

	timer_ += DELTA_TIME;

	if (timer_ >= 1.f / 5.f)
	{
		if (idx_ > 3)
		{
			idx_ = 0;
		}

		GetSpriteRenderer()->SetSprite(sprites_[idx_++]);

		timer_ = 0;
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
}
