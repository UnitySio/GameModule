#pragma once

class Object;
class Texture;

class Animator
{
private:
	friend class Object;

	std::weak_ptr<Object> owner_;

	UINT frame_rate_;

	bool is_play_;
public:
	Animator();
	Animator(const Animator& kOrigin);
	~Animator() = default;
};
