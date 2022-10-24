#include "pch.h"
#include "Object.h"
#include "SpriteRenderer.h"

using namespace std;

Object::Object() :
	name_(),
	position_{},
	rotation_{},
	scale_{},
	sprite_renderer_()
{
}

Object::Object(const Object& kOrigin) :
	position_{ kOrigin.position_ },
	rotation_{ kOrigin.rotation_ },
	scale_{ kOrigin.scale_ }
{
	wsprintf(name_, L"%s", kOrigin.name_);

	if (kOrigin.sprite_renderer_ != nullptr)
	{
		sprite_renderer_ = make_shared<SpriteRenderer>(*(SpriteRenderer*)kOrigin.sprite_renderer_.get());
		sprite_renderer_->owner_ = this;
	}
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

void Object::AddSpriteRenderer()
{
	sprite_renderer_ = make_shared<SpriteRenderer>();
	sprite_renderer_->owner_ = this;
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
	if (sprite_renderer_ != nullptr)
	{
		sprite_renderer_->Render(position_, scale_);
	}
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

shared_ptr<SpriteRenderer> Object::GetSpriteRenderer()
{
	return sprite_renderer_;
}
