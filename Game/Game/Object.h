#pragma once

class SpriteRenderer;

class Object : public std::enable_shared_from_this<Object>
{
private:
	WCHAR name_[128];

	Vector2 position_;
	Vector2 rotation_; // ���� �̻��
	Vector2 scale_;

	std::shared_ptr<SpriteRenderer> sprite_renderer_;
public:
	Object();
	Object(const Object& kOrigin); // ������Ʈ�� ����Ǿ��� ��
	virtual ~Object() = default;

	void SetName(LPCWSTR name);
	void SetPosition(Vector2 position);
	void SetRotation(Vector2 rotation);
	void SetScale(Vector2 scale);
	void Translate(Vector2 translation);
	void AddSpriteRenderer();

	virtual void Update();
	virtual void LateUpdate();
	virtual void PhysicsUpdate();
	virtual void Render();

	Vector2 GetPosition(); // ���� ��ġ
	Vector2 GetRotation();
	Vector2 GetScale();

	std::shared_ptr<SpriteRenderer> GetSpriteRenderer();
};
