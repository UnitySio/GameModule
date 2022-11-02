#pragma once

class Object;

class BoxCollider2D
{
private:
	friend class Object;

	Object* owner_;

	Vector2 offset_;
	Vector2 position_;
	Vector2 scale_;
public:
	BoxCollider2D();
	BoxCollider2D(const BoxCollider2D& kOrigin);
	~BoxCollider2D() = default;

	BoxCollider2D& operator=(const BoxCollider2D& kBoxCollider2D) = delete;

	void PhysicsUpdate();
	void Render();
	void SetOffset(Vector2 offset);
	void SetScale(Vector2 scale);
	void OnTriggerEnter();
	void OnTriggerStay();
	void OnTriggerExit();
};

