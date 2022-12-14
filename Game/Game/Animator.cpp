#include "pch.h"
#include "Animator.h"

#include <tchar.h>

#include "Player.h"
#include "SpriteRenderer.h"

using namespace std;

// 코루틴
Coroutine Animator::Play()
{
    shared_ptr<SpriteRenderer> sprite_renderer = owner_->GetSpriteRenderer();
    
    while (is_play_)
    {
        // 현재 이 구문에서 계산에 문제가 있음
        if (!clips_[current_clip_].is_loop && sprite_renderer->GetCurrentFrame() == clips_[current_clip_].
            frame_count - 1)
        {
            is_play_ = false;
            is_done_ = true;
        }

        co_await suspend_always{};

        owner_->GetSpriteRenderer()->SetFrame(
            (sprite_renderer->GetCurrentFrame() + 1) % clips_[current_clip_].frame_count);
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
    clips_{kOrigin.clips_},
    is_play_(),
    timer_(),
    frame_rate_(kOrigin.frame_rate_),
    current_clip_()
{
}

void Animator::AddClip(std::wstring clip, bool is_loop, UINT start_frame, UINT frame_count)
{
    clips_.insert({clip, {is_loop, start_frame, frame_count}});
}

void Animator::SetClip(std::wstring clip)
{
    current_clip_ = clip;
    owner_->GetSpriteRenderer()->SetFrame(0);
    is_play_ = true;
    is_done_ = false;
    timer_ = 0;
}

void Animator::SetFrameRate(UINT frame_rate)
{
    frame_rate_ = frame_rate;
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

bool Animator::IsDone()
{
    return is_done_;
}

const map<wstring, Clip>& Animator::GetClips()
{
    return clips_;
}

std::wstring Animator::GetCurrentClip()
{
    return current_clip_;
}
