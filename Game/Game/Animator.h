#pragma once

#include "Coroutine.h"

class Object;
class Texture;

class Animator
{
private:
	struct Clip
	{
		bool is_logic_loop_;
		size_t start_frame;
		size_t frame_count;
	};

	friend class Object;
	friend class SpriteRenderer;

	Object* owner_;

	std::map<size_t, Clip> clips_;

	bool is_play_;

	float timer_;

	UINT frame_rate_;

	size_t current_clip_;
public:
	Animator();
	Animator(const Animator& kOrigin);
	~Animator() = default;

	Animator& operator=(const Animator& kAnimator) = delete;

	Coroutine coroutine = Play();
	Coroutine Play();

	void AddClip(size_t clip, bool is_loop, UINT start_frame, UINT frame_count);
	void SetClip(size_t clip);
	void Update();
};
