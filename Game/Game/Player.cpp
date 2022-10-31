#include "pch.h"
#include "Player.h"
#include "Window.h"
#include "SpriteRenderer.h"
#include "Animator.h"
#include "Rigidbody2D.h"
#include "InputManager.h"
#include "PlayerIdle.h"
#include "PlayerWalk.h"
#include "PlayerJump.h"
#include "PlayerFalling.h"

using namespace std;

shared_ptr<State> Player::GetInitiateState()
{
	return states_[(size_t)PlayerStateType::kIdle];
}

Player::Player() :
	move_speed_(200.f),
	direction_(1),
	is_ground_()
{
	states_[(size_t)PlayerStateType::kIdle] = make_shared<PlayerIdle>(this);
	states_[(size_t)PlayerStateType::kWalk] = make_shared<PlayerWalk>(this);
	states_[(size_t)PlayerStateType::kJump] = make_shared<PlayerJump>(this);
	states_[(size_t)PlayerStateType::kFalling] = make_shared<PlayerFalling>(this);

	right_ = make_shared<Texture>();
	right_->Load(L"Resources/WarriorRightSheet.bmp", 6, 17);
	right_->SetPivot({ 0.385f, 0.97f });

	left_ = make_shared<Texture>();
	left_->Load(L"Resources/WarriorLeftSheet.bmp", 6, 17);
	left_->SetPivot({ 0.625f, 0.97f });

	AddSpriteRenderer();
	GetSpriteRenderer()->SetSprite(right_);

	AddAnimator();
	GetAnimator()->AddClip((size_t)PlayerClipType::kIdle, true, 0, 6);
	GetAnimator()->AddClip((size_t)PlayerClipType::kWalk, true, 6, 8);
	GetAnimator()->AddClip((size_t)PlayerClipType::kJump, false, 41, 3);
	GetAnimator()->AddClip((size_t)PlayerClipType::kFalling, false, 44, 5);

	AddRigidbody2D();

	StateMachine::Initiate();
}

void Player::Update()
{
	Object::Update();
	StateMachine::Update();

	if (INPUT_MANAGER->GetKey('D'))
	{
		direction_ = 1;
		GetRigidbody2D()->SetVelocity({ move_speed_, GetRigidbody2D()->GetVelocity().y_ });
	}

	if (INPUT_MANAGER->GetKeyUp('D'))
	{
		GetRigidbody2D()->SetVelocity({ 0, GetRigidbody2D()->GetVelocity().y_ });
	}

	if (INPUT_MANAGER->GetKey('A'))
	{
		direction_ = -1;
		GetRigidbody2D()->SetVelocity({ -move_speed_, GetRigidbody2D()->GetVelocity().y_ });
	}

	if (INPUT_MANAGER->GetKeyUp('A'))
	{
		GetRigidbody2D()->SetVelocity({ 0, GetRigidbody2D()->GetVelocity().y_ });
	}

	// 이동 중
	if (GetRigidbody2D()->GetVelocity().x_ != 0.f)
	{
		if (current_state_ != states_[(size_t)PlayerStateType::kWalk])
		{
			ChangeState(states_[(size_t)PlayerStateType::kWalk]);
		}
	}
	else // 이동 중이 아님
	{
		if (is_ground_ && current_state_ != states_[(size_t)PlayerStateType::kIdle])
		{
			ChangeState(states_[(size_t)PlayerStateType::kIdle]);
		}
	}

	if (GetRigidbody2D()->GetVelocity().y_ > 0)
	{
		if (current_state_ != states_[(size_t)PlayerStateType::kFalling])
		{
			ChangeState(states_[(size_t)PlayerStateType::kFalling]);
		}
	}

	if (GetRigidbody2D()->GetVelocity().y_ < 0)
	{
		if (current_state_ != states_[(size_t)PlayerStateType::kJump])
		{
			ChangeState(states_[(size_t)PlayerStateType::kJump]);
		}
	}

	if (direction_ == 1)
	{
		GetSpriteRenderer()->SetSprite(right_);
	}
	else if (direction_ == -1)
	{
		GetSpriteRenderer()->SetSprite(left_);
	}

	if (!is_ground_)
	{
		GetRigidbody2D()->AddForce(Vector2().Down() * 1000);
	}

	if (INPUT_MANAGER->GetKey('W'))
	{
		is_ground_ = false;
		GetRigidbody2D()->SetVelocity({ GetRigidbody2D()->GetVelocity().x_, -500 });
	}

	if (is_ground_)
	{
		if (INPUT_MANAGER->GetKeyDown('S'))
		{
			is_ground_ = false;
			GetRigidbody2D()->SetVelocity({ GetRigidbody2D()->GetVelocity().x_ + (500 * direction_), -500 });
		}
	}
}

void Player::LateUpdate()
{
}

void Player::PhysicsUpdate()
{
	Object::PhysicsUpdate();

	if (!is_ground_)
	{
		if (GetPosition().y_ >= 480)
		{
			is_ground_ = true;
			GetRigidbody2D()->SetVelocity({ GetRigidbody2D()->GetVelocity().x_, 0 });
		}
	}
}

void Player::Render()
{
	Object::Render();

	HPEN new_pen = CreatePen(PS_SOLID, 0, RGB(255, 0, 0));
	HPEN old_pen = (HPEN)SelectObject(WINDOW->GetHDC(), new_pen);

	HBRUSH new_brush = CreateSolidBrush(RGB(255, 0, 0));
	HBRUSH old_brush = (HBRUSH)SelectObject(WINDOW->GetHDC(), new_brush);

	Ellipse(WINDOW->GetHDC(), GetPosition().x_ - 2, GetPosition().y_ - 2, GetPosition().x_ + 2, GetPosition().y_ + 2);

	SelectObject(WINDOW->GetHDC(), old_pen);
	DeleteObject(new_pen);

	SelectObject(WINDOW->GetHDC(), old_brush);
	DeleteObject(new_brush);
}
