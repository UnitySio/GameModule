#include "pch.h"
#include "Player.h"
#include "Window.h"
#include "SpriteRenderer.h"
#include "Animator.h"
#include "Rigidbody2D.h"
#include "BoxCollider2D.h"
#include "InputManager.h"
#include "PlayerAttack.h"
#include "PlayerIdle.h"
#include "PlayerWalk.h"
#include "PlayerDash.h"
#include "PlayerJump.h"
#include "PlayerFalling.h"
#include "PlayerHit.h"
#include "PlayerDeath.h"
#include "Camera.h"
#include "SceneManager.h"

using namespace std;

void Player::Movement()
{
	shared_ptr<Rigidbody2D> rigid = GetRigidbody2D();

	horizontal_ = (INPUT->GetKey(RIGHT) - INPUT->GetKey(LEFT));
	rigid->SetVelocity({ move_speed_ * horizontal_, rigid->GetVelocity().y_ });

	if (INPUT->GetKeyDown(RUN))
	{
		move_speed_ = 400.f;
	}

	if (INPUT->GetKeyUp(RUN))
	{
		move_speed_ = 200.f;
	}

	if (INPUT->GetKeyDown(JUMP))
	{
		if (is_ground_)
		{
			ChangeState(states_[(size_t)PlayerStateType::kJump]);
		}
	}

	if (GetRigidbody2D()->GetVelocity().y_ > 0.f)
	{
		if (current_state_ != states_[(size_t)PlayerStateType::kFalling])
		{
			ChangeState(states_[(size_t)PlayerStateType::kFalling]);
		}
	}
}

shared_ptr<State> Player::GetInitiateState()
{
	return states_[(size_t)PlayerStateType::kIdle];
}

Player::Player() :
	move_speed_(200.f),
	jump_force_(500.f),
	is_ground_(),
	is_dash_(),
	direction_(1),
	horizontal_(),
	timer_()
{
	SetHP(10000.f);
	SetMaxHP(GetHP());

	// ���� �߰�
	states_[(size_t)PlayerStateType::kIdle] = make_shared<PlayerIdle>(this);
	states_[(size_t)PlayerStateType::kWalk] = make_shared<PlayerWalk>(this);
	states_[(size_t)PlayerStateType::kDash] = make_shared<PlayerDash>(this);
	states_[(size_t)PlayerStateType::kJump] = make_shared<PlayerJump>(this);
	states_[(size_t)PlayerStateType::kFalling] = make_shared<PlayerFalling>(this);
	states_[(size_t)PlayerStateType::kAttack] = make_shared<PlayerAttack>(this);
	states_[(size_t)PlayerStateType::kHit] = make_shared<PlayerHit>(this);
	states_[(size_t)PlayerStateType::kDeath] = make_shared<PlayerDeath>(this);

	// ���� ���ҽ� �Ŵ������� ���ҽ����� ������ �� �ֵ��� ���� ����
	right_ = make_shared<Texture>();
	right_->Load(L"Resources/WarriorRightSheet.bmp", 6, 17);
	right_->SetPivot({ 0.385f, 0.97f });

	left_ = make_shared<Texture>();
	left_->Load(L"Resources/WarriorLeftSheet.bmp", 6, 17);
	left_->SetPivot({ 0.625f, 0.97f });

	AddSpriteRenderer(); // ��������Ʈ ������ ������Ʈ
	GetSpriteRenderer()->SetTexture(right_);

	AddAnimator(); // �ִϸ����� ������Ʈ
	GetAnimator()->AddClip(L"IDLE", true, 0, 6); // IDLE �ִϸ��̼�
	GetAnimator()->AddClip(L"WALK", true, 6, 8); // WALK �ִϸ��̼�
	GetAnimator()->AddClip(L"DASH", false, 85, 5); // DASH �ִϸ��̼�
	GetAnimator()->AddClip(L"JUMP", false, 41, 3); // JUMP �ִϸ��̼�
	GetAnimator()->AddClip(L"FALLING", false, 44, 5); // FALLING �ִϸ��̼�
	GetAnimator()->AddClip(L"ATTACK", false, 14, 12); // ATTACK �ִϸ��̼�
	GetAnimator()->AddClip(L"HIT", false, 37, 4); // HIT �ִϸ��̼�
	GetAnimator()->AddClip(L"DEATH", false, 26, 11); // DEATH �ִϸ��̼�

	AddRigidbody2D(); // ���ڵ� �ٵ� ������Ʈ
	AddBoxCollider2D(); // �ڽ� �ݶ��̴� ������Ʈ
	GetBoxCollider2D()->SetOffset({ 0.f, -50.f });
	GetBoxCollider2D()->SetSize({ 64.f, 100.f });

	// ���� �ӽ� �ʱ�ȭ
	StateMachine::Initiate();
}

void Player::Update()
{
	Object::Update();
	StateMachine::Update();

	if (INPUT->GetKeyDown(RESTART))
	{
		SCENE->LoadScene(SceneType::kDefault);
	}

	if (!IsDeath())
	{
		if (GetHP() != 10000.f)
		{
			timer_ += DELTA_TIME;

			if (timer_ > .001f)
			{
				SetHP(GetHP() + 1.f);
				timer_ = 0;
			}
		}
		else
		{
			timer_ = 0;
		}
	}

	// ���� �ƴ� ��� �Ʒ��������� �߷� ���ӵ��� ��
	if (!is_ground_)
	{
		GetRigidbody2D()->SetGravityAcceleration(Vector2().Down() * 800.f);
	}
}

void Player::LateUpdate()
{
	Object::LateUpdate();

	// �� ������ �������� ����
	SetPosition({ clamp(GetPosition().x_, 0.f, 1600.f), clamp(GetPosition().y_, 0.f, 800.f) });
}

void Player::PhysicsUpdate()
{
	Object::PhysicsUpdate();
}

void Player::Render()
{
	Object::Render();

	// ���� UI ���� ������Ʈ�� ���� ����

	Vector2 render_position = CAMERA->GetRenderPosition(GetPosition());

	HBRUSH new_brush1 = CreateSolidBrush(RGB(100, 100, 100));
	HBRUSH old_brush1 = (HBRUSH)SelectObject(WINDOW->GetHDC(), new_brush1);
	
	Rectangle(WINDOW->GetHDC(), render_position.x_ - 50, render_position.y_ + 8, render_position.x_ + 50, render_position.y_ + 24);
	
	SelectObject(WINDOW->GetHDC(), old_brush1);
	DeleteObject(new_brush1);
	
	HBRUSH new_brush2 = CreateSolidBrush(RGB(200, 0, 0));
	HBRUSH old_brush2 = (HBRUSH)SelectObject(WINDOW->GetHDC(), new_brush2);
	
	Rectangle(WINDOW->GetHDC(), render_position.x_ - 50, render_position.y_ + 8, render_position.x_ - 50 + clamp((int)((GetHP() / GetMaxHP()) * 100), 0, 100), render_position.y_ + 24);
	
	SelectObject(WINDOW->GetHDC(), old_brush2);
	DeleteObject(new_brush2);
	
	WCHAR word[1024];
	wsprintf(word, L"%d%%", clamp((int)((GetHP() / GetMaxHP()) * 100), 0, 100));
	RECT rect = { (LONG)(render_position.x_ - 50), (LONG)(render_position.y_ + 8), (LONG)(render_position.x_ + 50), (LONG)(render_position.y_ + 24) };
	DrawText(WINDOW->GetHDC(), word, -1, &rect, DT_CENTER);
}

void Player::OnTriggerEnter(Object* other)
{
	if (wcscmp(other->GetName(), L"Ground") == 0)
	{
		is_ground_ = true;
		GetRigidbody2D()->SetVelocity({ GetRigidbody2D()->GetVelocity().x_, 0.f });
	}
}

void Player::OnTriggerStay(Object* other)
{
}

void Player::OnTriggerExit(Object* other)
{
	if (wcscmp(other->GetName(), L"Ground") == 0)
	{
		is_ground_ = false;
	}
}

void Player::OnDamage(Vector2 position, UINT damage)
{
	Entity::OnDamage(position, damage);

	if (GetHP() > 0.f)
	{
		ChangeState(states_[(size_t)PlayerStateType::kHit]);
	}
}

void Player::OnDeath()
{
	//SCENE->Destroy(shared_from_this());
	ChangeState(states_[(size_t)PlayerStateType::kDeath]);
}

bool Player::IsDash()
{
	return is_dash_;
}
