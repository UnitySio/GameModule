#include "pch.h"
#include "GroundObject.h"
#include "Window.h"
#include "Camera.h"
#include "BoxCollider2D.h"

using namespace std;

GroundObject::GroundObject()
{
	AddBoxCollider2D();
	GetBoxCollider2D()->SetSize({ 300.f, 32.f });
}

void GroundObject::Render()
{
	Object::Render();

	Vector2 render_position = CAMERA->GetRenderPosition(GetPosition());

	Rectangle(WINDOW->GetHDC(), render_position.x_ - 150, render_position.y_ - 16, render_position.x_ + 150, render_position.y_ + 16);
}

void GroundObject::OnTriggerEnter(Object* other)
{
	Vector2 other_position = other->GetBoxCollider2D()->GetPosition();
	Vector2 position = GetBoxCollider2D()->GetPosition();

	Vector2 other_scale = other->GetBoxCollider2D()->GetScale();
	Vector2 scale = GetBoxCollider2D()->GetScale();

	if (GetPosition().y_ > other->GetPosition().y_)
	{
		float a = abs(other_position.y_ - position.y_);
		float b = (other_scale.y_ / 2.f + scale.y_ / 2.f) - a;

		other_position = other->GetPosition();
		other_position.y_ -= b;
		other->SetPosition(other_position);
	}
}

void GroundObject::OnTriggerStay(Object* other)
{
	Vector2 other_position = other->GetBoxCollider2D()->GetPosition();
	Vector2 position = GetBoxCollider2D()->GetPosition();

	Vector2 other_scale = other->GetBoxCollider2D()->GetScale();
	Vector2 scale = GetBoxCollider2D()->GetScale();

	if (GetPosition().y_ > other->GetPosition().y_)
	{
		float a = abs(other_position.y_ - position.y_);
		float b = (other_scale.y_ / 2.f + scale.y_ / 2.f) - a;

		other_position = other->GetPosition();
		other_position.y_ -= b;
		other->SetPosition(other_position);
	}
}

void GroundObject::OnTriggerExit(Object* other)
{
}
