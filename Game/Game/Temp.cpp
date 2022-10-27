#include "pch.h"
#include "Temp.h"
#include "Texture.h"
#include "Window.h"

using namespace std;

Temp::Temp() :
	texture_(),
	frames_(),
	clips_(),
	frame_width_(),
	frame_height_(),
	timer_(),
	frame_rate_(15),
	current_frame_(),
	current_clip_("IDLE")
{
	clips_.insert({ "IDLE", { 0, 6 } });
	clips_.insert({ "WALK", { 6, 8 } });
	clips_.insert({ "ATTACK", { 14, 12 } });
}

void Temp::SetTexture(shared_ptr<Texture> texture)
{
	texture_ = texture;
}

void Temp::Slice(UINT row, UINT col)
{
	frame_width_ = texture_->GetWidth() / row;
	frame_height_ = texture_->GetHeight() / col;

	for (size_t i = 0; i < col; i++)
	{
		for (size_t j = 0; j < row; j++)
		{
			Vector2 position = { frame_width_ * j, frame_height_ * i };
			frames_.push_back({ position });
		}
	}
}

void Temp::SetClip(std::string name)
{
	if (current_clip_ != name)
	{
		current_clip_ = name;
		current_frame_ = 0;
	}
}

void Temp::Update()
{
	timer_ += DELTA_TIME;

	if (timer_ >= 1.f / frame_rate_)
	{
		current_frame_ = (current_frame_ + 1) % clips_[current_clip_].frames; // 8
		timer_ = 0;
	}
}

void Temp::Render(Vector2 position, Vector2 scale)
{
	Vector2 multiple = { frame_width_ * scale.x_, frame_height_ * scale.y_ };
	Vector2 pivot_position = position - multiple * texture_->pivot_;

	TransparentBlt(WINDOW->GetHDC(), pivot_position.x_, pivot_position.y_, multiple.x_, multiple.y_, texture_->memDC, frames_[current_frame_ + clips_[current_clip_].start].x_, frames_[current_frame_ + clips_[current_clip_].start].y_, frame_width_, frame_height_, RGB(255, 0, 255));
}
