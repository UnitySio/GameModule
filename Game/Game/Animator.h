#pragma once

class Object;
class Texture;

class Animator
{
private:
	friend class Object;

	Object* owner_;

	UINT frame_rate_;

	size_t current_frame_;

	bool is_play_;

	float timer_;

	std::vector<std::shared_ptr<Texture>> sprites_;
public:
	Animator();
	Animator(const Animator& kOrigin);
	~Animator() = default;

	void Update();
};
