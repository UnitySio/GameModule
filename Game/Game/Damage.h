#pragma once

#include "Object.h"

class Damage :
	public Object
{
private:
	UINT damage_;

	float timer_;
public:
	Damage(UINT damage);
	~Damage() final = default;

	void Update() final;
	void Render() final;
};

