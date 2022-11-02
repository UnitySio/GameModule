#pragma once

class Object;
class Texture;

class SpriteRenderer
{
private:
	friend class Object;
	friend class Animator;
	friend class BoxCollider2D;

	Object* owner_;

	std::shared_ptr<Texture> sprite_;

	size_t current_frame_;
public:
	SpriteRenderer();
	SpriteRenderer(const SpriteRenderer& kOrigin);
	~SpriteRenderer() = default;

	SpriteRenderer& operator=(const SpriteRenderer& kSpriteRenderer) = delete;

	void SetSprite(std::shared_ptr<Texture> sprite);
	void Render(Vector2 position, Vector2 scale);
};
