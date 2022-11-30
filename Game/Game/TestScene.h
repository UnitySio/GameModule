#pragma once

#include "Scene.h"

class TestScene :
	public Scene
{
public:
    TestScene() = default;
    ~TestScene() final = default;

    void Enter() final;
    void Exit() final;
};
