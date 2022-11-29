#pragma once

#include "State.h"
#include "Boss.h"

class BossAttack :
	public State
{
private:
	Boss* owner_;

	std::shared_ptr<Object> hit_box;
public:
	BossAttack(Boss* owner);
	~BossAttack() final = default;

	void OnStateEnter() final;
	void OnStateUpdate() final;
	void OnStateExit() final;
	void CreateHitBox(); // ���� �Լ��� ���� ����
	void DestroyHitBox();
};

