#pragma once

#include "Object.h"

class Block : public Object
{
private:
public:
	Block();
	~Block() final = default;

	void Update(float delta_time) final;
	void LateUpdate(float delta_time) final;
	void Render(HDC hdc) final;

	void OnTriggerEnter(std::shared_ptr<BoxCollider2D> other) final;
	void OnTriggerStay(std::shared_ptr<BoxCollider2D> other) final;
	void OnTriggerExit(std::shared_ptr<BoxCollider2D> other) final;
};

