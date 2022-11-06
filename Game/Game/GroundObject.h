#pragma once

#include "Object.h"

class GroundObject : public Object
{
private:
public:
	GroundObject();
	~GroundObject() final = default;

	void Render();
	void OnTriggerEnter(Object* other) final;
	void OnTriggerStay(Object* other) final;
	void OnTriggerExit(Object* other) final;
};
