#include "pch.h"
#include "Object.h"

using namespace std;

Object::Object() : name_{}, position_{}, scale_{}, pivot_{}
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
	position_ = position_ + vector2;
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
