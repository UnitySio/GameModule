#include "pch.h"
#include "BoxCollider2D.h"
#include "Object.h"

using namespace Gdiplus;

UINT BoxCollider2D::next_uid_ = 0;

BoxCollider2D::BoxCollider2D() : owner_(), offset_{}, position_{}, scale_{}, uid_(next_uid_++)
{
}

BoxCollider2D::BoxCollider2D(const BoxCollider2D& kBoxCollider2D) : owner_(), offset_{ kBoxCollider2D.offset_ }, position_{ kBoxCollider2D.position_ }, scale_{ kBoxCollider2D.scale_ }, uid_(next_uid_++)
{
}

void BoxCollider2D::LateUpdate(float delta_time)
{
	Vector2 position = owner_->GetPosition();
	Vector2 pivot = owner_->GetPivot();
	Vector2 scale = owner_->GetScale();

	position_ = position - ((scale * pivot) - scale / 2) + offset_;
}

void BoxCollider2D::OnTriggerEnter(std::shared_ptr<BoxCollider2D> other)
{
	owner_->OnTriggerEnter(other);
}

void BoxCollider2D::OnTriggerStay(std::shared_ptr<BoxCollider2D> other)
{
	owner_->OnTriggerStay(other);
}

void BoxCollider2D::OnTriggerExit(std::shared_ptr<BoxCollider2D> other)
{
	owner_->OnTriggerExit(other);
}

void BoxCollider2D::SetOffset(Vector2 vector2)
{
	offset_ = vector2;
}

void BoxCollider2D::SetScale(Vector2 vector2)
{
	scale_ = vector2;
}

Vector2 BoxCollider2D::GetPosition()
{
	return position_;
}

Vector2 BoxCollider2D::GetScale()
{
	return scale_;
}

UINT BoxCollider2D::GetUID()
{
	return uid_;
}

Object* BoxCollider2D::GetOwner()
{
	return owner_;
}
