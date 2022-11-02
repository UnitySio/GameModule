#pragma once

class Object;

class BoxCollider2D
{
private:
	friend class Object;

	static UINT next_uid_;

	Object* owner_;

	Vector2 offset_;
	Vector2 position_;
	Vector2 scale_;

	UINT uid_;
public:
	BoxCollider2D();
	BoxCollider2D(const BoxCollider2D& kOrigin);
	~BoxCollider2D() = default;

	BoxCollider2D& operator=(const BoxCollider2D& kBoxCollider2D) = delete;

	void PhysicsUpdate();
	void Render();
	void SetOffset(Vector2 offset);
	void SetScale(Vector2 scale);
	void OnTriggerEnter(std::shared_ptr<BoxCollider2D> other);
	void OnTriggerStay(std::shared_ptr<BoxCollider2D> other);
	void OnTriggerExit(std::shared_ptr<BoxCollider2D> other);

	Vector2 GetPosition();
	Vector2 GetScale();

	UINT GetUID();

	Object* GetOwner();
};

