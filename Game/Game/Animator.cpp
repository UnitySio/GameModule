#include "pch.h"
#include "Animator.h"
#include "Player.h"
#include "SpriteRenderer.h"

using namespace std;

Animator::Animator() :
	owner_(),
	frame_rate_(5),
	current_frame_(),
	is_play_(true),
	timer_()
{
	WCHAR word[128];

	for (int i = 0; i < 4; i++)
	{
		wsprintf(word, L"Resources/%d.bmp", i);
		shared_ptr<Texture> sprite_ = make_shared<Texture>();
		sprite_->Load(word);
		sprite_->SetPivot({ 0.5f, 1.f });
		sprites_.push_back(sprite_);
	}

	
}

Animator::Animator(const Animator& kOrigin) :
	owner_(kOrigin.owner_),
	frame_rate_(kOrigin.frame_rate_),
	current_frame_(),
	is_play_(),
	timer_()
{
}

void Animator::Update()
{
	if (is_play_)
	{
		timer_ += DELTA_TIME;

		if (timer_ >= 1.f / frame_rate_)
		{
			owner_->GetSpriteRenderer()->SetSprite(sprites_[current_frame_]);
			current_frame_ = (current_frame_ + 1) % sprites_.size();
			timer_ = 0;
		}
	}
}
