#include "pch.h"
#include "GroundObject.h"
#include "Window.h"
#include "BoxCollider2D.h"

using namespace std;

GroundObject::GroundObject()
{
	AddBoxCollider2D();
	GetBoxCollider2D()->SetScale({ 32.f, 32.f });
}

void GroundObject::Render()
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
