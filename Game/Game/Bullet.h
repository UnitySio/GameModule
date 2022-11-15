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
};
