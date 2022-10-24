#pragma once

#include "Object.h"
#include "Texture.h"

class Player : public Object
{
private:
	float move_speed_;

	std::shared_ptr<Texture> sprite_;
public:
	Player();
	~Player() final = default;

	void Update() final;
	void LateUpdate() final;
	void PhysicsUpdate() final;
	void Render() final;
};
