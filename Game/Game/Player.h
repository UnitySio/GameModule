#pragma once

#include "Object.h"
#include "StateMachine.h"
#include "Texture.h"
#include "Temp.h"

class Player : public Object, public StateMachine
{
private:
	float move_speed_;

	std::shared_ptr<Temp> temp_;
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
