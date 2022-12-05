#include "pch.h"
#include "Combo.h"
#include "SceneManager.h"

using namespace std;

Combo::Combo() :
	timer_(),
	combo_()
{
}

void Combo::Update()
{
	timer_ += DELTA_TIME;

	if (timer_ > 1.f)
	{
		SCENE->Destroy(shared_from_this());
	}
}

void Combo::Render()
{
}
