#pragma once

class Object;
class Texture;

class SpriteRenderer
{
private:
	friend class Object;

	Object* owner_;

	std::shared_ptr<Texture> texture_;

	size_t current_frame_;
public:
	SpriteRenderer();
	SpriteRenderer(const SpriteRenderer& kOrigin);
	~SpriteRenderer() = default;

	SpriteRenderer& operator=(const SpriteRenderer&) = delete;

	void SetTexture(std::shared_ptr<Texture> sprite);
	void SetFrame(size_t frame);
	void Render(Vector2 position, Vector2 scale);

	size_t GetCurrentFrame();
};
