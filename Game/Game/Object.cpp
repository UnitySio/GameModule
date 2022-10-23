#include "pch.h"
#include "Object.h"

Object::Object() :
	name_(),
	position_{},
	rotation_{},
	scale_{}
{
}

Object::Object(const Object& kOrigin) :
	position_{ kOrigin.position_ },
	rotation_{ kOrigin.rotation_ },
	scale_{ kOrigin.scale_ }
{
	wsprintf(name_, L"%s", kOrigin.name_);
}

void Object::SetName(LPCWSTR name)
{
	wsprintf(name_, L"%s", name);
}

void Object::SetPosition(Vector2 position)
{
	position_ = position;
}

void Object::SetRotation(Vector2 rotation)
{
	rotation_ = rotation;
}

void Object::SetScale(Vector2 scale)
{
	scale_ = scale;
}

void Object::Translate(Vector2 translation)
{
	position_ += translation;
}

void Object::Update()
{
}

void Object::LateUpdate()
{
}

void Object::PhysicsUpdate()
{
}

void Object::Render()
{
}

Vector2 Object::GetPosition()
{
	return position_;
}

Vector2 Object::GetRotation()
{
	return rotation_;
}

Vector2 Object::GetScale()
{
	return scale_;
}
