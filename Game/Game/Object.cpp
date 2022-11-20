#include "pch.h"
#include "Object.h"
#include "SpriteRenderer.h"
#include "Animator.h"
#include "Rigidbody2D.h"
#include "BoxCollider2D.h"

using namespace std;

Object::Object() :
    name_(),
    position_{},
    scale_{},
    is_destroy_(),
    sprite_renderer_(),
    animator_(),
    rigidbody2d_(),
    box_collider2d_()
{
}

Object::Object(const Object& kOrigin) :
    position_{kOrigin.position_},
    scale_{kOrigin.scale_},
    is_destroy_()
{
    wsprintf(name_, L"%s", kOrigin.name_);

    if (kOrigin.sprite_renderer_ != nullptr)
    {
        sprite_renderer_ = make_shared<SpriteRenderer>(*(SpriteRenderer*)kOrigin.sprite_renderer_.get());
        sprite_renderer_->owner_ = this;
    }

    if (kOrigin.animator_ != nullptr)
    {
        animator_ = make_shared<Animator>(*(Animator*)kOrigin.animator_.get());
        animator_->owner_ = this;
    }

    if (kOrigin.rigidbody2d_ != nullptr)
    {
        rigidbody2d_ = make_shared<Rigidbody2D>(*(Rigidbody2D*)kOrigin.rigidbody2d_.get());
        rigidbody2d_->owner_ = this;
    }

    if (kOrigin.box_collider2d_ != nullptr)
    {
        box_collider2d_ = make_shared<BoxCollider2D>(*(BoxCollider2D*)kOrigin.box_collider2d_.get());
        box_collider2d_->owner_ = this;
    }
}

void Object::SetName(LPCWSTR kName)
{
    wsprintf(name_, L"%s", kName);
}

void Object::SetPosition(Vector2 position)
{
    position_ = position;
}

void Object::SetScale(Vector2 scale)
{
    scale_ = scale;
}

void Object::SetDestroy()
{
    is_destroy_ = true;
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

void Object::AddAnimator()
{
    animator_ = make_shared<Animator>();
    animator_->owner_ = this;
}

void Object::AddRigidbody2D()
{
    rigidbody2d_ = make_shared<Rigidbody2D>();
    rigidbody2d_->owner_ = this;
}

void Object::AddBoxCollider2D()
{
    box_collider2d_ = make_shared<BoxCollider2D>();
    box_collider2d_->owner_ = this;
}

void Object::Update()
{
    if (animator_ != nullptr)
    {
        animator_->Update();
    }
}

void Object::LateUpdate()
{
}

void Object::PhysicsUpdate()
{
    if (rigidbody2d_ != nullptr)
    {
        rigidbody2d_->PhysicsUpdate();
    }

    if (box_collider2d_ != nullptr)
    {
        box_collider2d_->PhysicsUpdate();
    }
}

void Object::Render()
{
    if (sprite_renderer_ != nullptr)
    {
        sprite_renderer_->Render();
    }

    if (box_collider2d_ != nullptr)
    {
        box_collider2d_->Render();
    }
}

void Object::OnTriggerEnter(Object* other)
{
}

void Object::OnTriggerStay(Object* other)
{
}

void Object::OnTriggerExit(Object* other)
{
}

void Object::OnDestroy()
{
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

bool Object::IsDestroy()
{
    return is_destroy_;
}

shared_ptr<SpriteRenderer> Object::GetSpriteRenderer()
{
    return sprite_renderer_;
}

shared_ptr<Animator> Object::GetAnimator()
{
    return animator_;
}

shared_ptr<Rigidbody2D> Object::GetRigidbody2D()
{
    return rigidbody2d_;
}

shared_ptr<BoxCollider2D> Object::GetBoxCollider2D()
{
    return box_collider2d_;
}
