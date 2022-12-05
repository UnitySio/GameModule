#include "pch.h"
#include "PlayerHitBox.h"
#include "BoxCollider2D.h"
#include "Rigidbody2D.h"
#include "Boss.h"
#include "SceneManager.h"
#include "Scene.h"
#include "Combo.h"

using namespace std;

PlayerHitBox::PlayerHitBox(Player* owner) :
    owner_(owner)
{
    AddBoxCollider2D();
    GetBoxCollider2D()->SetSize({ 120.f, 120.f });
}

void PlayerHitBox::Render()
{
    Object::Render();
}

void PlayerHitBox::OnTriggerEnter(Object* other)
{
    if (wcscmp(other->GetName(), L"Boss") == 0)
    {
        (*(Boss*)other).OnDamage((*(Boss*)other).GetPosition(), 500);
        (*(Boss*)other).GetRigidbody2D()->SetVelocity({ owner_->direction_ * 100.f, -100.f });

        shared_ptr<Object> combo = SCENE->GetCurrentScene()->FindObject(L"Combo");
        (*(Combo*)combo.get()).AddCombo();
    }
}

void PlayerHitBox::OnTriggerStay(Object* other)
{
}

void PlayerHitBox::OnTriggerExit(Object* other)
{
}
