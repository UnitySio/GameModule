#pragma once

class Texture;

class Temp
{
private:
	struct Clip
	{
		size_t start;
		size_t frames;
	};

	std::shared_ptr<Texture> texture_;

	std::vector<Vector2> frames_;
	std::map<std::string, Clip> clips_;

	float frame_width_;
	float frame_height_;
	float timer_;

	UINT frame_rate_;

	size_t current_frame_;
	std::string current_clip_;
public:
	Temp();
	~Temp() = default;

	void SetTexture(std::shared_ptr<Texture> texture);
	void Slice(UINT row, UINT col);
	void SetClip(std::string name);
	void Update();
	void Render(Vector2 position, Vector2 scale);
};
