#include "pch.h"
#include "Block.h"
#include "BoxCollider2D.h"

#include <tchar.h>

using namespace std;
using namespace Gdiplus;

Block::Block()
{
	AddBoxCollider2D();
	GetBoxCollider2D()->SetOffset({ 0.f, 0.f });
	GetBoxCollider2D()->SetScale({ 32.f, 32.f });
	AddRigidbody2D();
}

void Block::Update(float delta_time)
{
}

void Block::LateUpdate(float delta_time)
{
	Object::LateUpdate(delta_time);
}

void Block::Render(HDC hdc)
{
	Graphics graphics(hdc);

	SolidBrush white_brush(Color(255, 255, 255, 255));

	Pen black_pen(Color(255, 0, 0, 0));

	graphics.FillRectangle(&white_brush, GetRenderPositon().x, GetRenderPositon().y, GetScale().x, GetScale().y);
	graphics.DrawRectangle(&black_pen, GetRenderPositon().x, GetRenderPositon().y, GetScale().x, GetScale().y);
}

void Block::OnTriggerEnter(shared_ptr<BoxCollider2D> other)
{
}

void Block::OnTriggerStay(shared_ptr<BoxCollider2D> other)
{
}

void Block::OnTriggerExit(shared_ptr<BoxCollider2D> other)
{
}
