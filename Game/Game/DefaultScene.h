#pragma once

#include "Scene.h"

class DefaultScene :
	public Scene
{
public:
	DefaultScene() = default;
	~DefaultScene() final = default;

	void Enter() final;
	void Exit() final;
};
