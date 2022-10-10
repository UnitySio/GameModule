#include "pch.h"
#include "Scene.h"
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

shared_ptr<Layer> Scene::CreateLayer(LPCWSTR name, UINT z_order)
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
}

void Scene::Update(float delta_time)
{
	for (size_t i = 0; i < layers_.size(); i++)
	{
		layers_[i]->Update(delta_time);
	}
}

void Scene::LateUpdate(float delta_time)
{
	for (size_t i = 0; i < layers_.size(); i++)
	{
		layers_[i]->LateUpdate(delta_time);
	}
}

void Scene::Render(HDC hdc)
{
	for (size_t i = 0; i < layers_.size(); i++)
	{
		layers_[i]->Render(hdc);
	}
}
