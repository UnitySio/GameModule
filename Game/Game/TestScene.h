#pragma once

#include "Scene.h"

class TestScene : public Scene
{
private:
public:
	TestScene() = default;
	virtual ~TestScene() = default;

	virtual void Enter();
	virtual void Exit();
};

