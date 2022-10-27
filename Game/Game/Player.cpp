#include "pch.h"
#include "Player.h"
#include "Window.h"
#include "SpriteRenderer.h"
#include "InputManager.h"
#include "PlayerIdle.h"
#include "PlayerWalk.h"
#include "PlayerAttack.h"

using namespace std;

std::shared_ptr<State> Player::GetInitiateState()
{
	return states_[0];
}

Player::Player() :
	move_speed_(100.f)
{
	states_[0] = make_shared<PlayerIdle>(this);
	states_[1] = make_shared<PlayerWalk>(this);
	states_[2] = make_shared<PlayerAttack>(this);

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

	StateMachine::Initiate();
}

void Player::Update()
{
	//Object::Update();
	temp_->Update();
	StateMachine::Update();
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
