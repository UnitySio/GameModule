#pragma once
class Object
{
private:
public:
	Object();
	~Object();

	virtual void Initiate();
	virtual void Update();
	virtual void LateUpdate();
	virtual void Render();
};

