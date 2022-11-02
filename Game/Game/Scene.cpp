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

LPCWSTR Scene::GetName()
{
	return name_;
}

void Scene::InputUpdate()
{
	for (size_t i = 0; i < (size_t)LayerType::kEnd; i++)
	{
		for_each(objects_[i].begin(), objects_[i].end(), [](shared_ptr<Object> object) {
			object->InputUpdate();
			});
	}
}

void Scene::Update()
{
	for (size_t i = 0; i < (size_t)LayerType::kEnd; i++)
	{
		for_each(objects_[i].begin(), objects_[i].end(), [](shared_ptr<Object> object) {
			object->Update();
			});
	}
}

void Scene::LateUpdate()
{
	for (size_t i = 0; i < (size_t)LayerType::kEnd; i++)
	{
		for_each(objects_[i].begin(), objects_[i].end(), [](shared_ptr<Object> object) {
			object->LateUpdate();
			});
	}
}

void Scene::PhysicsUpdate()
{
	for (size_t i = 0; i < (size_t)LayerType::kEnd; i++)
	{
		for_each(objects_[i].begin(), objects_[i].end(), [](shared_ptr<Object> object) {
			object->PhysicsUpdate();
			});
	}
}

void Scene::Render()
{
	for (size_t i = 0; i < (size_t)LayerType::kEnd; i++)
	{
		for_each(objects_[i].begin(), objects_[i].end(), [](shared_ptr<Object> object) {
			object->Render();
			});
	}
}

const list<shared_ptr<Object>>& Scene::GetLayerObjects(LayerType type)
{
	return objects_[(size_t)type];
}
