#include "pch.h"
#include "SpriteRenderer.h"
#include "Window.h"
#include "Texture.h"

using namespace std;

SpriteRenderer::SpriteRenderer() :
	owner_(),
	sprite_()
{
}

SpriteRenderer::SpriteRenderer(const SpriteRenderer& kSpriteRenderer) :
	owner_(kSpriteRenderer.owner_)
{
	sprite_ = kSpriteRenderer.sprite_;
}

void SpriteRenderer::SetSprite(shared_ptr<Texture> sprite)
{
	sprite_ = sprite;
}

void SpriteRenderer::Render(Vector2 position, Vector2 scale)
{
	TransparentBlt(Window::GetInstance()->GetHDC(), position.x_, position.y_, scale.x_, scale.y_, sprite_->memDC, 0, 0, sprite_->GetWidth(), sprite_->GetHeight(), RGB(0, 128, 0));
}
