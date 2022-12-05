#pragma once

#include "Object.h"

class Combo :
	public Object
{
private:
	float timer_;

	UINT combo_;
public:
	Combo();
	~Combo() final = default;

	void Update() final;
	void Render() final;
};

