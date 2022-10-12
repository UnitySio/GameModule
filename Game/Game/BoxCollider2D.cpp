#include "pch.h"
#include "BoxCollider2D.h"
#include "Object.h"

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
	position_ = offset_ + position;
}

void BoxCollider2D::OnTriggerEnter(std::shared_ptr<BoxCollider2D> other)
{
#ifdef _DEBUG
	_cprintf("OnTriggerEnter\n");
#endif // _DEBUG
}

void BoxCollider2D::OnTriggerStay(std::shared_ptr<BoxCollider2D> other)
{
#ifdef _DEBUG
	_cprintf("OnTriggerStay\n");
#endif // _DEBUG
}

void BoxCollider2D::OnTriggerExit(std::shared_ptr<BoxCollider2D> other)
{
#ifdef _DEBUG
	_cprintf("OnTriggerExit\n");
#endif // _DEBUG
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
