#include "pch.h"
#include "Scene.h"
#include "Object.h"

#include <algorithm>

using namespace std;

Scene::Scene() : name_{}
{
}

void Scene::SetName(LPCWSTR name)
{
	wsprintf(name_, L"%s", name);
}

LPCWSTR Scene::GetName()
{
	return name_;
}

/*shared_ptr<Layer> Scene::CreateLayer(LPCWSTR name, UINT z_order)
{
	shared_ptr<Layer> new_layer = make_shared<Layer>();
	new_layer->SetName(name);
	new_layer->SetZOrder(z_order);

	layers_.push_back(new_layer);

	sort(layers_.begin(), layers_.end(), [](shared_ptr<Layer> first, shared_ptr<Layer> second)
		{
			return first->GetZOrder() < second->GetZOrder();
		});

	return new_layer;
}*/

void Scene::Update(float delta_time)
{
	for (size_t i = 0; i < (size_t)LayerType::kEND; i++)
	{
		for (size_t j = 0; j < objects_[i].size(); j++)
		{
			objects_[i][j]->Update(delta_time);
		}
	}
}

void Scene::LateUpdate(float delta_time)
{
	for (size_t i = 0; i < (size_t)LayerType::kEND; i++)
	{
		for (size_t j = 0; j < objects_[i].size(); j++)
		{
			objects_[i][j]->LateUpdate(delta_time);
		}
	}
}

void Scene::Render(HDC hdc)
{
	for (size_t i = 0; i < (size_t)LayerType::kEND; i++)
	{
		for (size_t j = 0; j < objects_[i].size(); j++)
		{
			objects_[i][j]->Render(hdc);
		}
	}
}

void Scene::CreateObject(std::shared_ptr<Object> object, LayerType type)
{
	objects_[(size_t)type].push_back(object);
}

const vector<shared_ptr<Object>>& Scene::GetGroupObject(LayerType type)
{
	return objects_[(UINT)type];
}
