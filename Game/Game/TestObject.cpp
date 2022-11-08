#include "pch.h"
#include "TestObject.h"
#include "Window.h"
#include "Camera.h"
#include "SceneManager.h"
#include "InputManager.h"
#include "Player.h"

TestObject::TestObject(Object* target) :
	target_(target)
{
}

void TestObject::Update()
{
	if (target_)
	{
		//SetPosition(Vector2().Lerp(GetPosition(), target_->GetPosition() + Vector2({ 64.f * -(*(Player*)target_).direction_ , -100.f }), DELTA_TIME * 10.f));
		Vector2 target_position = (*(Player*)target_).GetPosition();
		Vector2 a = target_position - GetPosition();
		Vector2 b = a.Normalized();

		Translate(b * 100.f * DELTA_TIME);
	}

	if (INPUT->GetKeyDown(VK_LSHIFT))
	{
		SCENE->Destroy(shared_from_this());
	}
}

void TestObject::Render()
{
	Vector2 render_position = CAMERA->GetRenderPosition(GetPosition());

	Rectangle(WINDOW->GetHDC(), render_position.x_ - 16, render_position.y_ - 16, render_position.x_ + 16, render_position.y_ + 16);
}

void TestObject::OnDestroy()
{
	OutputDebugString(L"Test Object Destroyed.\n");
}
