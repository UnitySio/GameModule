#pragma once

#include "Scene.h"

class DefaultScene : public Scene
{
private:
public:
	DefaultScene();
	~DefaultScene() final = default;

	void Enter() final;
	void Exit() final;
};
