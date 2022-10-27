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

	std::map<LPCWSTR, std::vector<std::shared_ptr<Texture>>> clips_;
public:
	Animator();
	Animator(const Animator& kOrigin);
	~Animator() = default;

	void AddClip(LPCWSTR name, std::vector<std::shared_ptr<Texture>> clip);
	void Update();
};
