#pragma once

#include "Object.h"
#include "StateMachine.h"
#include "Texture.h"

class Player :
	public Object,
	public StateMachine
{
private:
	float move_speed_;

	std::shared_ptr<State> states_[2];

	std::shared_ptr<Texture> left_;
	std::shared_ptr<Texture> right_;

	bool is_ground_;

	float horizontal;

	float timer_;

	// 테스트 코드
	float jump_time_;
	float jump_power_;
protected:
	std::shared_ptr<State> GetInitiateState();
public:
	bool is_attack_;
	int direction_;

	Player();
	~Player() final = default;

	void Update() final;
	void LateUpdate() final;
	void PhysicsUpdate() final;
	void Render() final;
	void OnTriggerEnter(Object* other) final;
	void OnTriggerStay(Object* other) final;
	void OnTriggerExit(Object* other) final;
};
