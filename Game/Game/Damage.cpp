#include "pch.h"
#include "Damage.h"
#include "Window.h"
#include "SceneManager.h"
#include "Camera.h"

Damage::Damage(UINT damage) :
	damage_(damage),
	timer_()
{
}

void Damage::Update()
{
	timer_ += DELTA_TIME;

	if (timer_ > 1.f)
	{
		SCENE->Destroy(shared_from_this());
	}

	Translate(Vector2().Up() * 100.f * DELTA_TIME);
}

void Damage::Render()
{
	Vector2 render_position = CAMERA->GetRenderPosition(GetPosition());

	WCHAR word[1024];
	wsprintf(word, L"%d", damage_);

	TextOut(WINDOW->GetHDC(), render_position.x_, render_position.y_, word, wcslen(word));
}
