#include "pch.h"
#include "Bullet.h"
#include "Window.h"
#include "Camera.h"
#include "SceneManager.h"
#include "BoxCollider2D.h"
#include "Rigidbody2D.h"

Bullet::Bullet() :
    direction_{},
    timer_()
{
    AddBoxCollider2D();
}

void Bullet::SetDirection(Vector2 difference)
{
    direction_ = difference;
}

void Bullet::Update()
{
    timer_ += DELTA_TIME;

    if (timer_ > 5.f)
    {
        SCENE->Destroy(shared_from_this());
    }

    Translate(direction_ * 500.f * DELTA_TIME);
}

void Bullet::Render()
{
    Object::Render();

    Vector2 render_postiion = CAMERA->GetRenderPosition(GetPosition());

    Ellipse(WINDOW->GetHDC(),
            render_postiion.x_ - 5.f,
            render_postiion.y_ - 5.f,
            render_postiion.x_ + 5.f,
            render_postiion.y_ + 5.f);
}

void Bullet::OnDestroy()
{
    //OutputDebugString(L"Destroyed.\n");
}

void Bullet::OnTriggerEnter(Object* other)
{
    if (wcscmp(other->GetName(), L"Ground") == 0)
    {
        SCENE->Destroy(shared_from_this());
    }
}

void Bullet::OnTriggerStay(Object* other)
{
}

void Bullet::OnTriggerExit(Object* other)
{
}
