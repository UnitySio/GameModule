#include "pch.h"
#include "GroundObject.h"
#include "Window.h"
#include "Camera.h"
#include "BoxCollider2D.h"

using namespace std;

GroundObject::GroundObject()
{
	AddBoxCollider2D();
	GetBoxCollider2D()->SetScale({ 300.f, 32.f });
}

void GroundObject::Render()
{
	Object::Render();

	Vector2 render_position = CAMERA->GetRenderPosition(GetPosition());

	Rectangle(WINDOW->GetHDC(), render_position.x_ - 150, render_position.y_ - 16, render_position.x_ + 150, render_position.y_ + 16);
}

void GroundObject::OnTriggerEnter(Object* other)
{
	Vector2 other_position = other->GetPosition();
	Vector2 position = other->GetPosition();

	float len = abs(other_position.y_ - position.y_);
	float a = 80 - len;

	other_position = other->GetPosition();
	other_position.y_ -= a;
	other->SetPosition(other_position);
}

void GroundObject::OnTriggerStay(Object* other)
{
}

void GroundObject::OnTriggerExit(Object* other)
{
}
