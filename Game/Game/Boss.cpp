#include "pch.h"
#include "Boss.h"
#include "SpriteRenderer.h"
#include "BoxCollider2D.h"
#include "Rigidbody2D.h"
#include "Animator.h"
#include "Window.h"
#include "SceneManager.h"
#include "Camera.h"
#include "Bullet.h"

using namespace std;

shared_ptr<State> Boss::GetInitiateState()
{
	return nullptr;
}

Boss::Boss() :
	target_(),
	is_ground_(),
	direction_(1),
	hp_(1000000.f),
	max_hp_(hp_)
{
	left_idle_ = make_shared<Texture>();
	left_idle_->Load(L"Resources/BossLeftIdleSheet.bmp", 11);
	left_idle_->SetPivot({ .46f, .63f });

	left_run_ = make_shared<Texture>();
	left_run_->Load(L"Resources/BossLeftRunSheet.bmp", 8);
	left_run_->SetPivot({ .46f, .63f });

	right_idle_ = make_shared<Texture>();
	right_idle_->Load(L"Resources/BossRightIdleSheet.bmp", 11);
	right_idle_->SetPivot({ .54f, .63f });

	right_run_ = make_shared<Texture>();
	right_run_->Load(L"Resources/BossRightRunSheet.bmp", 8);
	right_run_->SetPivot({ .54f, .63f });

	AddSpriteRenderer(); // 스프라이트 렌더러
	GetSpriteRenderer()->SetTexture(left_idle_);

	AddBoxCollider2D(); // 박스 콜라이더
	GetBoxCollider2D()->SetSize({ 100.f, 150.f });
	GetBoxCollider2D()->SetOffset({ 0.f, -75.f });

	AddRigidbody2D(); // 리자드 바디
	AddAnimator(); // 애니메이터
	GetAnimator()->AddClip(L"IDLE", true, 0, 11);
	GetAnimator()->AddClip(L"WALK", true, 0, 8);
	GetAnimator()->SetClip(L"IDLE");
}

void Boss::SetTarget(shared_ptr<Object> target)
{
	target_ = target;
}

void Boss::Update()
{
	Object::Update();

	float distance = Vector2().Distance(target_->GetPosition(), GetPosition());

	if (distance < 300.f)
	{
		// 플레이어가 왼쪽에 있을 경우
		if (target_->GetPosition().x_ < GetPosition().x_ - 100)
		{
			direction_ = -1;
			GetRigidbody2D()->SetVelocity({ -200.f, GetRigidbody2D()->GetVelocity().y_ });
		}
		else if (target_->GetPosition().x_ > GetPosition().x_ + 100)
		{
			direction_ = 1;
			GetRigidbody2D()->SetVelocity({ 200.f, GetRigidbody2D()->GetVelocity().y_ });
		}
		else
		{
			GetRigidbody2D()->SetVelocity({ 0.f, GetRigidbody2D()->GetVelocity().y_ });
		}

		if (target_->GetPosition().y_ < GetPosition().y_ - 150.f)
		{
			if (is_ground_)
			{
				GetRigidbody2D()->SetVelocity({ GetRigidbody2D()->GetVelocity().x_, -500.f });
			}
		}
	}
	else
	{
		GetRigidbody2D()->SetVelocity({ 0.f, GetRigidbody2D()->GetVelocity().y_ });
	}

	if (GetRigidbody2D()->GetVelocity().x_ != 0.f)
	{
		if (GetAnimator()->GetCurrentClip() != L"WALK")
		{
			GetAnimator()->SetClip(L"WALK");
		}
	}
	else
	{
		if (GetAnimator()->GetCurrentClip() != L"IDLE")
		{
			GetAnimator()->SetClip(L"IDLE");
		}
	}

	if (direction_ == 1)
	{
		if (GetAnimator()->GetCurrentClip() == L"WALK")
		{
			GetSpriteRenderer()->SetTexture(right_run_);
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
			GetSpriteRenderer()->SetTexture(left_run_);
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

	if (hp_ <= 0)
	{
		SCENE->Destroy(shared_from_this());
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

	Vector2 render_position = CAMERA->GetRenderPosition(GetPosition());

	Rectangle(WINDOW->GetHDC(), render_position.x_ - 50, render_position.y_ + 8, render_position.x_ + 50, render_position.y_ + 24);
	
	HBRUSH new_brush = CreateSolidBrush(RGB(255, 0, 0));
	HBRUSH old_brush = (HBRUSH)SelectObject(WINDOW->GetHDC(), new_brush);
	
	Rectangle(WINDOW->GetHDC(), render_position.x_ - 50, render_position.y_ + 8, render_position.x_ - 50 + (hp_ / max_hp_) * 100, render_position.y_ + 24);
	
	SelectObject(WINDOW->GetHDC(), old_brush);
	DeleteObject(new_brush);
	
	WCHAR word[1024];
	_stprintf_s(word, L"%.f%%", (hp_ / max_hp_) * 100);
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

	if (wcscmp(other->GetName(), L"Bullet") == 0)
	{
		hp_ -= 100.f;
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
