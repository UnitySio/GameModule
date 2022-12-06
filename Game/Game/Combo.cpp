#include "pch.h"
#include "Combo.h"
#include "Window.h"
#include "SceneManager.h"
#include "Camera.h"

using namespace std;

Combo::Combo() :
	timer_(),
	combo_(),
	position_{ 980.f, 240.f }
{
}

void Combo::Update()
{
	timer_ += DELTA_TIME;

	if (timer_ > 2.f)
	{
		combo_ = 0;
		timer_ = 0.f;
	}

	position_ = Vector2().Lerp(position_, { 600.f, 240.f }, DELTA_TIME * 60.f);
	SetPosition(position_);
}

void Combo::Render()
{
	Vector2 render_position = GetPosition();

	WCHAR word[1024];
	wsprintf(word, L"%d COMBO", combo_);

	RECT rect = { render_position.x_ - 100, render_position.y_ - 20, render_position.x_ + 20, render_position.y_ };
	DrawText(WINDOW->GetHDC(), word, -1, &rect, DT_SINGLELINE | DT_RIGHT | DT_VCENTER);
}

void Combo::AddCombo()
{
	combo_++;
	timer_ = 0.f;
	position_ = { 980.f, 240.f };
}
