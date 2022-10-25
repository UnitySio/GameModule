#pragma once

class Object;
class Texture;

class SpriteRenderer
{
private:
	friend class Object;

	std::weak_ptr<Object> owner_;

	std::shared_ptr<Texture> sprite_;
public:
	SpriteRenderer();
	SpriteRenderer(const SpriteRenderer& kSpriteRenderer);
	~SpriteRenderer() = default;

	void SetSprite(std::shared_ptr<Texture> sprite);
	void Render(Vector2 position, Vector2 scale);
};
