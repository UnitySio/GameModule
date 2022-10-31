#pragma once

#include "Object.h"
#include "StateMachine.h"
#include "Texture.h"

class Player : public Object, public StateMachine
{
private:

	float move_speed_;

	std::shared_ptr<State> states_[4];

	std::shared_ptr<Texture> left_;
	std::shared_ptr<Texture> right_;

	int direction_;

	bool is_ground_;
protected:
	std::shared_ptr<State> GetInitiateState();
public:
	Player();
	~Player() final = default;

	void Update() final;
	void LateUpdate() final;
	void PhysicsUpdate() final;
	void Render() final;
};
