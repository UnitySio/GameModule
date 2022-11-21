#include "pch.h"
#include "Ground.h"
#include "Window.h"
#include "Camera.h"
#include "BoxCollider2D.h"

using namespace std;

Ground::Ground()
{
    AddBoxCollider2D();
    GetBoxCollider2D()->SetSize({1600.f, 64.f});
}

void Ground::Update()
{
    Object::Update();
}

void Ground::Render()
{
    Object::Render();

    Vector2 render_position = CAMERA->GetRenderPosition(GetPosition());

    Rectangle(WINDOW->GetHDC(), render_position.x_ - 800, render_position.y_ - 32, render_position.x_ + 800,
              render_position.y_ + 32);
}

void Ground::OnTriggerEnter(Object* other)
{
    Vector2 other_position = other->GetBoxCollider2D()->GetPosition();
    Vector2 position = GetBoxCollider2D()->GetPosition();

    Vector2 other_scale = other->GetBoxCollider2D()->GetSize();
    Vector2 scale = GetBoxCollider2D()->GetSize();

    float distance = abs(other_position.y_ - position.y_);
    float length = (other_scale.y_ / 2.f + scale.y_ / 2.f) - distance;

    other_position = other->GetPosition();
    other_position.y_ -= length;
    other->SetPosition(other_position);
}

void Ground::OnTriggerStay(Object* other)
{
    Vector2 other_position = other->GetBoxCollider2D()->GetPosition();
    Vector2 position = GetBoxCollider2D()->GetPosition();

    Vector2 other_scale = other->GetBoxCollider2D()->GetSize();
    Vector2 scale = GetBoxCollider2D()->GetSize();

    float distance = abs(other_position.y_ - position.y_);
    float length = (other_scale.y_ / 2.f + scale.y_ / 2.f) - distance;

    other_position = other->GetPosition();
    other_position.y_ -= length;
    other->SetPosition(other_position);
}

void Ground::OnTriggerExit(Object* other)
{
}
