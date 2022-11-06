#pragma once

#include "Object.h"
#include "StateMachine.h"
#include "Texture.h"

class Player : public Object, public StateMachine
{
private:
	float move_speed_;

	std::shared_ptr<State> states_[2];

	std::shared_ptr<Texture> left_;
	std::shared_ptr<Texture> right_;

	int direction_;

	bool is_ground_;

	float horizontal;
protected:
	std::shared_ptr<State> GetInitiateState();
public:
	bool is_attack_;

	Player();
	~Player() final = default;

	void InputUpdate() final;
	void Update() final;
	void LateUpdate() final;
	void PhysicsUpdate() final;
	void Render() final;
	void OnTriggerEnter(Object* other) final;
	void OnTriggerStay(Object* other) final;
	void OnTriggerExit(Object* other) final;
};
