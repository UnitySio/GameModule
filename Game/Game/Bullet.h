#pragma once

#include "Object.h"

class Bullet :
	public Object
{
private:
	Vector2 direction_;

	float timer_;
public:
	Bullet();
	~Bullet() = default;

	void SetDirection(Vector2 difference);
	void Update() final;
	void Render() final;
	void OnDestroy() final;
	void OnTriggerEnter(Object* other) final;
	void OnTriggerStay(Object* other) final;
	void OnTriggerExit(Object* other) final;
};
