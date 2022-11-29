#include "pch.h"
#include "Boss.h"
#include "SpriteRenderer.h"
#include "BoxCollider2D.h"
#include "Rigidbody2D.h"
#include "Animator.h"
#include "Window.h"
#include "SceneManager.h"
#include "Camera.h"
#include "BossIdle.h"
#include "BossWalk.h"
#include "BossAttack.h"
#include "BossHit.h"
#include "BossDeath.h"

using namespace std;

shared_ptr<State> Boss::GetInitiateState()
{
	return states_[(size_t)BossStateType::kIdle];
}

Boss::Boss() :
	move_speed_(200.f),
	target_(),
	is_ground_(),
	direction_(1)
{
	SetHP(10000.f);
	SetMaxHP(GetHP());

	// 상태 추가
	states_[(size_t)BossStateType::kIdle] = make_shared<BossIdle>(this);
	states_[(size_t)BossStateType::kWalk] = make_shared<BossWalk>(this);
	states_[(size_t)BossStateType::kAttack] = make_shared<BossAttack>(this);
	states_[(size_t)BossStateType::kHit] = make_shared<BossHit>(this);
	states_[(size_t)BossStateType::kDeath] = make_shared<BossDeath>(this);
	
	left_idle_ = make_shared<Texture>();
	left_idle_->Load(L"Resources/BossLeftIdleSheet.bmp", 11);
	left_idle_->SetPivot({ .46f, .63f });

	left_walk_ = make_shared<Texture>();
	left_walk_->Load(L"Resources/BossLeftRunSheet.bmp", 8);
	left_walk_->SetPivot({ .46f, .63f });

	left_attack_ = make_shared<Texture>();
	left_attack_->Load(L"Resources/BossLeftAttack2Sheet.bmp", 7);
	left_attack_->SetPivot({ .46f, .63f });

	left_hit_ = make_shared<Texture>();
	left_hit_->Load(L"Resources/BossLeftHitSheet.bmp", 4);
	left_hit_->SetPivot({ .46f, .63f });

	left_death_ = make_shared<Texture>();
	left_death_->Load(L"Resources/BossLeftDeathSheet.bmp", 11);
	left_death_->SetPivot({ .46f, .63f });

	right_idle_ = make_shared<Texture>();
	right_idle_->Load(L"Resources/BossRightIdleSheet.bmp", 11);
	right_idle_->SetPivot({ .54f, .63f });

	right_walk_ = make_shared<Texture>();
	right_walk_->Load(L"Resources/BossRightRunSheet.bmp", 8);
	right_walk_->SetPivot({ .54f, .63f });

	right_attack_ = make_shared<Texture>();
	right_attack_->Load(L"Resources/BossRightAttack2Sheet.bmp", 7);
	right_attack_->SetPivot({ .54f, .63f });

	right_hit_ = make_shared<Texture>();
	right_hit_->Load(L"Resources/BossRightHitSheet.bmp", 4);
	right_hit_->SetPivot({ .54f, .63f });

	right_death_ = make_shared<Texture>();
	right_death_->Load(L"Resources/BossRightDeathSheet.bmp", 11);
	right_death_->SetPivot({ .54f, .63f });

	AddSpriteRenderer();
	GetSpriteRenderer()->SetTexture(left_idle_);

	AddBoxCollider2D();
	GetBoxCollider2D()->SetSize({ 100.f, 150.f });
	GetBoxCollider2D()->SetOffset({ 0.f, -75.f });

	AddRigidbody2D();
	AddAnimator();
	GetAnimator()->AddClip(L"IDLE", true, 0, 11);
	GetAnimator()->AddClip(L"WALK", true, 0, 8);
	GetAnimator()->AddClip(L"ATTACK", false, 0, 7);
	GetAnimator()->AddClip(L"HIT", false, 0, 4);
	GetAnimator()->AddClip(L"DEATH", false, 0, 11);

	// 상태 머신 초기화
	StateMachine::Initiate();
}

void Boss::SetTarget(shared_ptr<Object> target)
{
	target_ = target;
}

void Boss::Update()
{
	Object::Update();
	StateMachine::Update();

	if (direction_ == 1)
	{
		if (GetAnimator()->GetCurrentClip() == L"WALK")
		{
			GetSpriteRenderer()->SetTexture(right_walk_);
		}
		else if (GetAnimator()->GetCurrentClip() == L"ATTACK")
		{
			GetSpriteRenderer()->SetTexture(right_attack_);
		}
		else if (GetAnimator()->GetCurrentClip() == L"HIT")
		{
			GetSpriteRenderer()->SetTexture(right_hit_);
		}
		else if (GetAnimator()->GetCurrentClip() == L"DEATH")
		{
			GetSpriteRenderer()->SetTexture(right_death_);
		}
		else
		{
			GetSpriteRenderer()->SetTexture(right_idle_);
		}
	}
	else if (direction_ == -1)
	{
		if (GetAnimator()->GetCurrentClip() == L"WALK")
		{
			GetSpriteRenderer()->SetTexture(left_walk_);
		}
		else if (GetAnimator()->GetCurrentClip() == L"ATTACK")
		{
			GetSpriteRenderer()->SetTexture(left_attack_);
		}
		else if (GetAnimator()->GetCurrentClip() == L"HIT")
		{
			GetSpriteRenderer()->SetTexture(left_hit_);
		}
		else if (GetAnimator()->GetCurrentClip() == L"DEATH")
		{
			GetSpriteRenderer()->SetTexture(left_death_);
		}
		else
		{
			GetSpriteRenderer()->SetTexture(left_idle_);
		}
	}

	if (!is_ground_)
	{
		GetRigidbody2D()->SetGravityAcceleration(Vector2().Down() * 800.f);
	}
}

void Boss::LateUpdate()
{
	Object::LateUpdate();
}

void Boss::PhysicsUpdate()
{
	Object::PhysicsUpdate();
}

void Boss::Render()
{
	Object::Render();

	// 추후 UI 전용 오브젝트를 만들 예정

	Vector2 render_position = CAMERA->GetRenderPosition(GetPosition());

	Rectangle(WINDOW->GetHDC(), render_position.x_ - 50, render_position.y_ + 8, render_position.x_ + 50, render_position.y_ + 24);
	
	HBRUSH new_brush = CreateSolidBrush(RGB(255, 0, 0));
	HBRUSH old_brush = (HBRUSH)SelectObject(WINDOW->GetHDC(), new_brush);
	
	Rectangle(WINDOW->GetHDC(), render_position.x_ - 50, render_position.y_ + 8, render_position.x_ - 50 + (GetHP() / GetMaxHP()) * 100, render_position.y_ + 24);
	
	SelectObject(WINDOW->GetHDC(), old_brush);
	DeleteObject(new_brush);
	
	WCHAR word[1024];
	_stprintf_s(word, L"%.f%%", (GetHP() / GetMaxHP()) * 100);
	RECT rect = { render_position.x_ - 50, render_position.y_ + 8, render_position.x_ + 50, render_position.y_ + 24 };
	DrawText(WINDOW->GetHDC(), word, -1, &rect, DT_CENTER);
}

void Boss::OnTriggerEnter(Object* other)
{
	if (wcscmp(other->GetName(), L"Ground") == 0)
	{
		is_ground_ = true;
		GetRigidbody2D()->SetVelocity({ GetRigidbody2D()->GetVelocity().x_, 0.f });
	}
}

void Boss::OnTriggerStay(Object* other)
{
}

void Boss::OnTriggerExit(Object* other)
{
	if (wcscmp(other->GetName(), L"Ground") == 0)
	{
		is_ground_ = false;
	}
}

void Boss::OnDamage(UINT damage)
{
	Entity::OnDamage(damage);
	
	if (GetHP() > 0.f)
	{
		ChangeState(states_[(size_t)BossStateType::kHit]);
	}
}

void Boss::OnDeath()
{
	//SCENE->Destroy(shared_from_this());
	ChangeState(states_[(size_t)BossStateType::kDeath]);
}
