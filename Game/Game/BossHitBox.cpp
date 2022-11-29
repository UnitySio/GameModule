#include "pch.h"
#include "BossHitBox.h"
#include "BoxCollider2D.h"
#include "Player.h"

using namespace std;

BossHitBox::BossHitBox()
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
    (*(Player*)other).OnDamage(1000);
}

void BossHitBox::OnTriggerStay(Object* other)
{
}

void BossHitBox::OnTriggerExit(Object* other)
{
}
