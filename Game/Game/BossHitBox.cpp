#include "pch.h"
#include "BossHitBox.h"
#include "BoxCollider2D.h"
#include "Rigidbody2D.h"
#include "Player.h"

using namespace std;

BossHitBox::BossHitBox(Boss* owner) :
    owner_(owner)
{
    AddBoxCollider2D();
    GetBoxCollider2D()->SetSize({ 200.f, 180.f });
}

void BossHitBox::Render()
{
	Object::Render();
}

void BossHitBox::OnTriggerEnter(Object* other)
{
    if (wcscmp(other->GetName(), L"Player") == 0)
    {
        if (!(*(Player*)other).IsDash())
        {
            (*(Player*)other).OnDamage(2000);
            (*(Player*)other).GetRigidbody2D()->SetVelocity({ owner_->direction_ * 200.f, -200.f });
        }
    }
}

void BossHitBox::OnTriggerStay(Object* other)
{
}

void BossHitBox::OnTriggerExit(Object* other)
{
}
