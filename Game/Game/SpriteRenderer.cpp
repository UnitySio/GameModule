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
	sprite_(),
	current_frame_()
{
}

SpriteRenderer::SpriteRenderer(const SpriteRenderer& kOrigin) :
	owner_(),
	sprite_(kOrigin.sprite_),
	current_frame_()
{
	sprite_ = kOrigin.sprite_;
}

void SpriteRenderer::SetSprite(shared_ptr<Texture> sprite)
{
	sprite_ = sprite;
}

void SpriteRenderer::Render(Vector2 position, Vector2 scale)
{
	if (sprite_ != nullptr)
	{
		Vector2 render_position = CAMERA->GetRenderPosition(position);

		Vector2 multiple = { sprite_->frame_scale_.x_ * scale.x_, sprite_->frame_scale_.y_ * scale.y_ };
		Vector2 pivot_position = render_position - multiple * sprite_->pivot_;

		int start_frame = (owner_->animator_ != nullptr) ? owner_->animator_->clips_[owner_->animator_->current_clip_].start_frame : 0;

		TransparentBlt(WINDOW->GetHDC(),
			pivot_position.x_,
			pivot_position.y_,
			multiple.x_,
			multiple.y_,
			sprite_->memDC,
			sprite_->frames_[current_frame_ + start_frame].x_,
			sprite_->frames_[current_frame_ + start_frame].y_,
			sprite_->frame_scale_.x_,
			sprite_->frame_scale_.y_,
			RGB(255, 0, 255));
	}
}
