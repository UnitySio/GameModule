#include "pch.h"
#include "SpriteRenderer.h"
#include "Window.h"
#include "Texture.h"
#include "Object.h"
#include "Animator.h"
#include "Camera.h"

using namespace std;

SpriteRenderer::SpriteRenderer() :
	owner_(),
	texture_(),
	current_frame_(),
	pivot_position_{}
{
}

SpriteRenderer::SpriteRenderer(const SpriteRenderer& kOrigin) :
	owner_(),
	texture_(kOrigin.texture_),
	current_frame_(),
	pivot_position_{}
{
}

void SpriteRenderer::SetTexture(shared_ptr<Texture> sprite)
{
	texture_ = sprite;
}

void SpriteRenderer::SetFrame(size_t frame)
{
	current_frame_ = frame;
}

void SpriteRenderer::Render(Vector2 position, Vector2 scale)
{
	if (texture_ != nullptr)
	{
		Vector2 render_position = CAMERA->GetRenderPosition(position);

		Vector2 multiple = { texture_->GetSpriteSize().x_ * scale.x_, texture_->GetSpriteSize().y_ * scale.y_ };
		pivot_position_ = render_position - multiple * texture_->GetPivot();

		TransparentBlt(WINDOW->GetHDC(),
			pivot_position_.x_,
			pivot_position_.y_,
			multiple.x_,
			multiple.y_,
			texture_->GetMemDC(),
			texture_->GetFrames()[current_frame_].x_,
			texture_->GetFrames()[current_frame_].y_,
			texture_->GetSpriteSize().x_,
			texture_->GetSpriteSize().y_,
			RGB(255, 0, 255));
	}
}

size_t SpriteRenderer::GetCurrentFrame()
{
	return current_frame_;
}
