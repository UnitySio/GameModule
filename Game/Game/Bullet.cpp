#include "pch.h"
#include "Bullet.h"
#include "Window.h"
#include "Camera.h"

Bullet::Bullet() :
	direction_{}
{
}

void Bullet::SetDirection(Vector2 difference)
{
	direction_ = difference;
}

void Bullet::Update()
{
	Translate(direction_ * 100.f * DELTA_TIME);
}

void Bullet::Render()
{
	Vector2 render_postiion = CAMERA->GetRenderPosition(GetPosition());

	Ellipse(WINDOW->GetHDC(),
		render_postiion.x_ - 5.f,
		render_postiion.y_ - 5.f,
		render_postiion.x_ + 5.f,
		render_postiion.y_ + 5.f);
}
