#pragma once

#include "Object.h"
#include "Texture.h"

class Player : public Object
{
private:
	float move_speed_;

	std::vector<std::shared_ptr<Texture>> sprites_;

	int idx_;

	float timer_;
public:
	Player();
	~Player() final = default;

	void Update() final;
	void LateUpdate() final;
	void PhysicsUpdate() final;
	void Render() final;
};
