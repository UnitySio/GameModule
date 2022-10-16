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
	BoxCollider2D(const BoxCollider2D& kBoxCollider2D);
	~BoxCollider2D() = default;

	BoxCollider2D& operator=(BoxCollider2D&) = delete;

	void LateUpdate(float delta_time);

	void OnTriggerEnter(std::shared_ptr<BoxCollider2D> other);
	void OnTriggerStay(std::shared_ptr<BoxCollider2D> other);
	void OnTriggerExit(std::shared_ptr<BoxCollider2D> other);

	void SetOffset(Vector2 vector2);
	void SetScale(Vector2 vector2);

	Vector2 GetAbsolutePosition();
	Vector2 GetScale();

	UINT GetUID();

	Object* GetOwner();
};
