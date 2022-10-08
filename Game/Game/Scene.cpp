#include "Scene.h"

void Scene::SetName(LPCWSTR name)
{
	wsprintf(name_, L"%s", name);
}

LPCWSTR Scene::GetName()
{
	return name_;
}

void Scene::CreateInstance(shared_ptr<Object> object, ObjectTypeGroup type)
{
	objects_[(size_t)type].push_back(object);
}

void Scene::Update(float delta_time)
{
	for (size_t i = 0; i < 2; i++)
	{
		for (size_t j = 0; j < objects_[i].size(); j++)
		{
			objects_[i][j]->Update(delta_time);
		}
	}
}

void Scene::LateUpdate(float delta_time)
{
	for (size_t i = 0; i < 2; i++)
	{
		for (size_t j = 0; j < objects_[i].size(); j++)
		{
			objects_[i][j]->LateUpdate(delta_time);
		}
	}
}

void Scene::Render(HDC hdc)
{
	for (size_t i = 0; i < 2; i++)
	{
		for (size_t j = 0; j < objects_[i].size(); j++)
		{
			objects_[i][j]->Render(hdc);
		}
	}
}
