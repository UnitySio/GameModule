#include "pch.h"
#include "BoxCollider2D.h"
#include "Object.h"
#include "SpriteRenderer.h"
#include "Texture.h"
#include "Window.h"
#include "Camera.h"

using namespace std;

UINT BoxCollider2D::next_uid_ = 0;

BoxCollider2D::BoxCollider2D() :
	owner_(),
	offset_{},
	position_{},
	size_{},
	uid_(next_uid_++)
{
}

BoxCollider2D::BoxCollider2D(const BoxCollider2D& kOrigin) :
	owner_(),
	offset_{ kOrigin.offset_ },
	position_{ kOrigin.position_ },
	size_{ kOrigin.size_ },
	uid_(next_uid_++)
{
}

void BoxCollider2D::PhysicsUpdate()
{
	// 추후 리팩토링 고려 대상
	Vector2 owner_position = owner_->GetPosition();

	position_ = owner_position + offset_;
}

void BoxCollider2D::Render()
{
	Vector2 render_position = CAMERA->GetRenderPosition(position_);

	HPEN new_pen = CreatePen(PS_SOLID, 0, RGB(178, 223, 174));
	HPEN old_pen = (HPEN)SelectObject(WINDOW->GetHDC(), new_pen);

	HBRUSH new_brush = (HBRUSH)GetStockObject(NULL_BRUSH);
	HBRUSH old_brush = (HBRUSH)SelectObject(WINDOW->GetHDC(), new_brush);

	Rectangle(WINDOW->GetHDC(),
		render_position.x_ - size_.x_ / 2.f,
		render_position.y_ - size_.y_ / 2.f,
		render_position.x_ + size_.x_ / 2.f,
		render_position.y_ + size_.y_ / 2.f);

	SelectObject(WINDOW->GetHDC(), old_pen);
	DeleteObject(new_pen);

	SelectObject(WINDOW->GetHDC(), old_brush);
	DeleteObject(new_brush);
}

void BoxCollider2D::SetOffset(Vector2 offset)
{
	offset_ = offset;
}

void BoxCollider2D::SetSize(Vector2 size)
{
	size_ = size;
}

void BoxCollider2D::OnTriggerEnter(Object* other)
{
	owner_->OnTriggerEnter(other);
}

void BoxCollider2D::OnTriggerStay(Object* other)
{
	owner_->OnTriggerStay(other);
}

void BoxCollider2D::OnTriggerExit(Object* other)
{
	owner_->OnTriggerExit(other);
}

Vector2 BoxCollider2D::GetPosition()
{
	return position_;
}

Vector2 BoxCollider2D::GetSize()
{
	return size_;
}

UINT BoxCollider2D::GetUID()
{
	return uid_;
}

Object* BoxCollider2D::GetOwner()
{
	return owner_;
}
