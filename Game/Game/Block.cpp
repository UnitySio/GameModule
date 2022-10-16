#include "pch.h"
#include "Block.h"
#include "BoxCollider2D.h"

#include <tchar.h>

using namespace std;
using namespace Gdiplus;

Block::Block()
{
	AddBoxCollider2D();
	GetBoxCollider2D()->SetOffset({ 0, 0 });
	GetBoxCollider2D()->SetScale({ 200, 200 });
	AddRigidbody2D();
}

void Block::Update(float delta_time)
{
}

void Block::LateUpdate(float delta_time)
{
	Object::LateUpdate(delta_time);
}

void Block::Render(HDC hdc)
{
	Rectangle(hdc, GetRelativePosition().x, GetRelativePosition().y, GetRelativePosition().x + GetScale().x, GetRelativePosition().y + GetScale().y);
}

void Block::OnTriggerEnter(shared_ptr<BoxCollider2D> other)
{
	Object* other_owner = other->GetOwner();

	if (wcscmp(other_owner->GetName(), L"Player") == 0)
	{
	}
}

void Block::OnTriggerStay(shared_ptr<BoxCollider2D> other)
{
	Object* other_owner = other->GetOwner();

	if (wcscmp(other_owner->GetName(), L"Player") == 0)
	{
	}
}

void Block::OnTriggerExit(shared_ptr<BoxCollider2D> other)
{
	Object* other_owner = other->GetOwner();

	if (wcscmp(other_owner->GetName(), L"Player") == 0)
	{

	}
}
