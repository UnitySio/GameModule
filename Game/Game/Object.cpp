#include "pch.h"
#include "Object.h"

using namespace std;

Object::Object() : name_{}, position_{}, scale_{}
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
