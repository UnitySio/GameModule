#pragma once

// 예외 처리가 필요함
#include "Coroutine.h"

struct Clip
{
    bool is_loop;
    size_t start_frame;
    size_t frame_count;
};

class Object;
class Texture;

class Animator
{
private:
    friend class Object;

    Object* owner_;

    std::map<std::wstring, Clip> clips_;

    bool is_play_;

    float timer_;

    UINT frame_rate_;

    std::wstring current_clip_;
public:
    Animator();
    Animator(const Animator& kOrigin);
    ~Animator() = default;

    Animator& operator=(const Animator&) = delete;

    Coroutine coroutine = Play();
    Coroutine Play();

    void AddClip(std::wstring clip, bool is_loop, UINT start_frame, UINT frame_count);
    void SetClip(std::wstring clip);
    void Update();

    bool IsPlay();

    const std::map<std::wstring, Clip>& GetClips();

    std::wstring GetCurrentClip();
};
