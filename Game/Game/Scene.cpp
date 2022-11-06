#include "pch.h"
#include "Scene.h"
#include "Object.h"

using namespace std;

Scene::Scene() :
	name_(),
	objects_()
{
}

void Scene::SetName(LPCWSTR name)
{
	wsprintf(name_, L"%s", name);
}

void Scene::CreateObject(shared_ptr<Object> object, LayerType type, LPCWSTR name, Vector2 position, Vector2 rotation, Vector2 scale)
{
	object->SetName(name);
	object->SetPosition(position);
	object->SetRotation(rotation);
	object->SetScale(scale);

	objects_[(size_t)type].push_back(object);
}

void Scene::ObjectUpdate()
{
	for (size_t i = 0; i < (size_t)LayerType::kEnd; i++)
	{
		vector<shared_ptr<Object>>::iterator iter = objects_[i].begin();
		for (; iter != objects_[i].end(); ++iter)
		{
			if ((*iter)->IsDestroy())
			{
				(*iter).reset();
				iter = objects_[i].erase(iter);
			}
		}
	}
}

LPCWSTR Scene::GetName()
{
	return name_;
}

void Scene::InputUpdate()
{
	for (size_t i = 0; i < (size_t)LayerType::kEnd; i++)
	{
		for (size_t j = 0; j < objects_[i].size(); j++)
		{
			if (!objects_[i][j]->IsDestroy())
			{
				objects_[i][j]->InputUpdate();
			}
		}
	}
}

void Scene::Update()
{
	for (size_t i = 0; i < (size_t)LayerType::kEnd; i++)
	{
		for (size_t j = 0; j < objects_[i].size(); j++)
		{
			if (!objects_[i][j]->IsDestroy())
			{
				objects_[i][j]->Update();
			}
		}
	}
}

void Scene::LateUpdate()
{
	for (size_t i = 0; i < (size_t)LayerType::kEnd; i++)
	{
		for (size_t j = 0; j < objects_[i].size(); j++)
		{
			if (!objects_[i][j]->IsDestroy())
			{
				objects_[i][j]->LateUpdate();
			}
		}
	}
}

void Scene::PhysicsUpdate()
{
	for (size_t i = 0; i < (size_t)LayerType::kEnd; i++)
	{
		for (size_t j = 0; j < objects_[i].size(); j++)
		{
			if (!objects_[i][j]->IsDestroy())
			{
				objects_[i][j]->PhysicsUpdate();
			}
		}
	}
}

void Scene::Render()
{
	for (size_t i = 0; i < (size_t)LayerType::kEnd; i++)
	{
		for (size_t j = 0; j < objects_[i].size(); j++)
		{
			if (!objects_[i][j]->IsDestroy())
			{
				objects_[i][j]->Render();
			}
		}
	}
}

const vector<shared_ptr<Object>>& Scene::GetLayerObjects(LayerType type)
{
	return objects_[(size_t)type];
}
