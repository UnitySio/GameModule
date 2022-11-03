#include "pch.h"
#include "GroundObject.h"
#include "Window.h"
#include "BoxCollider2D.h"

using namespace std;

GroundObject::GroundObject()
{
	AddBoxCollider2D();
	GetBoxCollider2D()->SetScale({ 300.f, 32.f });
}

void GroundObject::Render()
{
	Object::Render();
}

void GroundObject::OnTriggerEnter(Object* other)
{
}

void GroundObject::OnTriggerStay(Object* other)
{
}

void GroundObject::OnTriggerExit(Object* other)
{
}
