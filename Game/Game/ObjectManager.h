#pragma once

#include "framework.h"
#include "Object.h"
#include "StateMachine.h"

#include <map>

class ObjectManager
{
private:
	// ΩÃ±€≈Ê
	static unique_ptr<ObjectManager> instance_;
	static once_flag flag_;
public:
	ObjectManager() = default;
	~ObjectManager() = default;

	ObjectManager(const ObjectManager&) = delete;
	ObjectManager& operator=(const ObjectManager&) = delete;

	static ObjectManager* GetInstance();

	void Initiate();
	void Update(float delta_time);
	void LateUpdate(float delta_time);
	void Render();

	void CreateObject(Object* object);
};

