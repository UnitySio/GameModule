#include "pch.h"
#include "Animator.h"
#include "Player.h"
#include "SpriteRenderer.h"

using namespace std;

Coroutine Animator::Play()
{
	while (is_play_)
	{
		if (!clips_[current_clip_].is_logic_loop_ && owner_->sprite_renderer_->current_frame_ == clips_[current_clip_].frame_count - 1)
		{
			is_play_ = false;
		}

		co_await suspend_always{};

		owner_->sprite_renderer_->current_frame_ = (owner_->sprite_renderer_->current_frame_ + 1) % clips_[current_clip_].frame_count;
	}
}

Animator::Animator() :
	owner_(),
	clips_{},
	is_play_(),
	timer_(),
	frame_rate_(15),
	current_clip_()
{
}

Animator::Animator(const Animator& kOrigin) :
	owner_(),
	clips_{ kOrigin.clips_ },
	is_play_(),
	timer_(),
	frame_rate_(kOrigin.frame_rate_),
	current_clip_()
{
}

void Animator::AddClip(size_t clip, bool is_loop, UINT start_frame, UINT frame_count)
{
	clips_.insert({ clip, { is_loop, start_frame, frame_count } });
}

void Animator::SetClip(size_t clip)
{
	current_clip_ = clip;
	owner_->sprite_renderer_->current_frame_ = 0;
	is_play_ = true;
	timer_ = 0;
}

void Animator::Update()
{
	if (is_play_)
	{
		timer_ += DELTA_TIME;

		if (timer_ >= 1.f / frame_rate_)
		{
			coroutine.co_handler_.resume();

			timer_ = 0;
		}
	}
}

bool Animator::IsPlay()
{
	return is_play_;
}
