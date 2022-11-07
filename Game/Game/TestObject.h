#pragma once

#include "Object.h"

class TestObject : public Object
{
private:
	Object* target_;
public:
	TestObject(Object* target);
	~TestObject() final = default;

	void Update() final;
	void Render() final;
	void OnDestroy() final;
};
