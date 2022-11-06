#include "pch.h"
#include "TestObject.h"
#include "Window.h"
#include "Camera.h"
#include "SceneManager.h"
#include "InputManager.h"

TestObject::TestObject(Object* target) :
	target_(target)
{
}

void TestObject::Update()
{
	if (target_)
	{
		SetPosition(Vector2().Lerp(GetPosition(), target_->GetPosition(), DELTA_TIME * 5.f));
	}

	if (INPUT->GetKeyDown(VK_LSHIFT))
	{
		SCENE->Destroy(this);
	}
}

void TestObject::Render()
{
	Vector2 render_position = CAMERA->GetRenderPosition(GetPosition());

	Rectangle(WINDOW->GetMemDC(), render_position.x_ - 16, render_position.y_ - 16, render_position.x_ + 16, render_position.y_ + 16);
}
