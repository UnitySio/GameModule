#include "pch.h"
#include "Bullet.h"
#include "Window.h"
#include "Camera.h"
#include "SceneManager.h"

Bullet::Bullet() :
	direction_{},
	timer_()
{
}

void Bullet::SetDirection(Vector2 difference)
{
	direction_ = difference;
}

void Bullet::Update()
{
	timer_ += DELTA_TIME;

	if (timer_ > 1.f)
	{
		SCENE->Destroy(shared_from_this());
	}

	Translate(direction_ * 300.f * DELTA_TIME);
}

void Bullet::Render()
{
	Vector2 render_postiion = CAMERA->GetRenderPosition(GetPosition());

	Rectangle(WINDOW->GetHDC(),
		render_postiion.x_ - 5.f,
		render_postiion.y_ - 5.f,
		render_postiion.x_ + 5.f,
		render_postiion.y_ + 5.f);
}

void Bullet::OnDestroy()
{
	OutputDebugString(L"Destroyed.\n");
}
