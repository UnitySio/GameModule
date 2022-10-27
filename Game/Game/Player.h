#pragma once

#include "Object.h"
#include "StateMachine.h"
#include "Texture.h"
#include "Temp.h"

class Player : public Object, public StateMachine
{
private:
	friend class PlayerIdle;
	friend class PlayerWalk;
	friend class PlayerAttack;

	float move_speed_;

	std::shared_ptr<Temp> temp_;

	std::shared_ptr<State> states_[3];
protected:
	std::shared_ptr<State> GetInitiateState() override;
public:
	Player();
	~Player() final = default;

	void Update() final;
	void LateUpdate() final;
	void PhysicsUpdate() final;
	void Render() final;
};
