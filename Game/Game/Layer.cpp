#include "pch.h"
#include "Layer.h"
#include "Object.h"

using namespace std;

Layer::Layer() : name_{}, z_order_(), objects_{}
{
}

void Layer::SetName(LPCWSTR name)
{
	wsprintf(name_, L"%s", name);
}

void Layer::SetZOrder(UINT z_order)
{
	z_order_ = z_order;
}

void Layer::Update(float delta_time)
{
	for (size_t i = 0; i < (size_t)GroupObjectType::kEND; i++)
	{
		for (size_t j = 0; j < objects_[i].size(); j++)
		{
			objects_[i][j]->Update(delta_time);
		}
	}
}

void Layer::LateUpdate(float delta_time)
{
	for (size_t i = 0; i < (size_t)GroupObjectType::kEND; i++)
	{
		for (size_t j = 0; j < objects_[i].size(); j++)
		{
			objects_[i][j]->LateUpdate(delta_time);
		}
	}
}

void Layer::Render(HDC hdc)
{
	for (size_t i = 0; i < (size_t)GroupObjectType::kEND; i++)
	{
		for (size_t j = 0; j < objects_[i].size(); j++)
		{
			objects_[i][j]->Render(hdc);
		}
	}
}

LPCWSTR Layer::GetName()
{
	return name_;
}

UINT Layer::GetZOrder()
{
	return z_order_;
}

void Layer::CreateObject(shared_ptr<Object> object, GroupObjectType type)
{
	objects_[(size_t)type].push_back(object);
}

shared_ptr<Object> Layer::FindObject(LPCWSTR name)
{
	for (size_t i = 0; i < (size_t)GroupObjectType::kEND; i++)
	{
		vector<shared_ptr<Object>>::iterator iter = objects_[i].begin();

		for (; iter != objects_[i].end(); ++iter)
		{
			if (wcscmp((*iter)->GetName(), name) == 0)
			{
				return *iter;
			}
		}
	}
}

void Layer::DestroyObject(shared_ptr<Object> object)
{
	for (size_t i = 0; i < (size_t)GroupObjectType::kEND; i++)
	{
		vector<shared_ptr<Object>>::iterator iter = objects_[i].begin();

		for (; iter != objects_[i].end(); ++iter)
		{
			if (*iter == object)
			{
				objects_[i].erase(iter);
				return;
			}
		}
	}
}
