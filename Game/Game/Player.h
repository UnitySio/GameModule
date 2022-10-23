#pragma once

#include "Object.h"
#include "Sprite.h"

class Player : public Object
{
private:
	float move_speed_;

	Sprite sprite_;
public:
	Player();
	~Player() final = default;

	void Update() final;
	void LateUpdate() final;
	void PhysicsUpdate() final;
	void Render() final;
};
