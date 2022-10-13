#include "pch.h"
#include "Object.h"
#include "BoxCollider2D.h"
#include "Rigidbody2D.h"

using namespace std;

Object::Object() : name_{}, position_{}, scale_{}, pivot_{}, box_collider2d_(), rigidbody2d_()
{
}

void Object::LateUpdate(float delta_time)
{
	if (box_collider2d_ != nullptr)
	{
		box_collider2d_->LateUpdate(delta_time);
	}

	if (rigidbody2d_ != nullptr)
	{
		rigidbody2d_->LateUpdate(delta_time);
	}
}

void Object::OnTriggerEnter(shared_ptr<BoxCollider2D> other)
{
}

void Object::OnTriggerStay(shared_ptr<BoxCollider2D> other)
{
}

void Object::OnTriggerExit(shared_ptr<BoxCollider2D> other)
{
}

void Object::SetName(LPCWSTR name)
{
	wsprintf(name_, L"%s", name);
}

void Object::SetPosition(Vector2 position)
{
	position_ = position;
}

void Object::SetScale(Vector2 scale)
{
	scale_ = scale;
}

void Object::SetPivot(Vector2 pivot)
{
	pivot_ = pivot;
}

void Object::Translate(Vector2 vector2)
{
	position_ += vector2;
}

LPCWSTR Object::GetName()
{
	return name_;
}

Vector2 Object::GetPosition()
{
	return position_;
}

Vector2 Object::GetScale()
{
	return scale_;
}

Vector2 Object::GetPivot()
{
	return pivot_;
}

Vector2 Object::GetRenderPositon()
{
	return position_ - scale_ * pivot_;
}

shared_ptr<BoxCollider2D> Object::GetBoxCollider2D()
{
	return box_collider2d_;
}

shared_ptr<Rigidbody2D> Object::GetRigidbody2D()
{
	return rigidbody2d_;
}

void Object::AddBoxCollider2D()
{
	box_collider2d_ = make_shared<BoxCollider2D>();
	box_collider2d_->owner_ = this;
}

void Object::AddRigidbody2D()
{
	rigidbody2d_ = make_shared<Rigidbody2D>();
	rigidbody2d_->owner_ = this;
}
