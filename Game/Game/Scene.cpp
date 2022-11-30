#include "pch.h"
#include "Scene.h"
#include "Object.h"
#include "CollisionManager.h"

using namespace std;

Scene::Scene() :
	name_(),
	objects_()
{
}

void Scene::SetName(LPCWSTR kName)
{
	wsprintf(name_, L"%s", kName);
}

void Scene::CreateObject(shared_ptr<Object> object, LayerType type, LPCWSTR kName, Vector2 position, Vector2 scale)
{
	object->SetName(kName);
	object->SetPosition(position);
	object->SetScale(scale);

	objects_[(size_t)type].push_back(object);
}

void Scene::SceneUpdate()
{
	for (size_t i = 0; i < (size_t)LayerType::kEnd; i++)
	{
		vector<shared_ptr<Object>>::iterator iter = objects_[i].begin();
		for (; iter != objects_[i].end();)
		{
			if ((*iter)->IsDestroy())
			{
				(*iter)->OnDestroy();
				(*iter).reset();
				iter = objects_[i].erase(iter);
			}
			else
			{
				iter++;
			}
		}
	}
}

shared_ptr<Object> Scene::FindObject(LPCWSTR kName)
{
	for (size_t i = 0; i < (size_t)LayerType::kEnd; i++)
	{
		vector<shared_ptr<Object>>::iterator iter = objects_[i].begin();
		for (; iter != objects_[i].end(); ++iter)
		{
			if (wcscmp(kName, (*iter)->GetName()) == 0)
			{
				return (*iter);
			}
		}
	}
}

LPCWSTR Scene::GetName()
{
	return name_;
}

void Scene::Exit()
{
	// ���ο� ���� �ҷ����� �� �ش� ���� �ִ� ��� ������Ʈ�� �޸� ����
	for (size_t i = 0; i < (size_t)LayerType::kEnd; i++)
	{
		vector<shared_ptr<Object>>::iterator iter = objects_[i].begin();
		for (; iter != objects_[i].end(); ++iter)
		{
			(*iter).reset();
		}

		objects_[i].clear();
	}

	// �浹 ���� �ʱ�ȭ
	COLLISION->Reset();

	TIME->SetTimeScale(1.f);
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
				// ����ȭ�� ���� ī�޶� �ۿ� ���� ��� �׸��� ����
				// ���� �׽�Ʈ �ڵ�
				/*Vector2 render_position = CAMERA->GetRenderPosition(objects_[i][j]->GetPosition());
				if (render_position.x_ > 0 && render_position.x_ < 640)
				{
					if (render_position.y_ > 0 && render_position.y_ < 480)
					{
						objects_[i][j]->Render();
					}
				}*/
				objects_[i][j]->Render();
			}
		}
	}
}

const vector<shared_ptr<Object>>& Scene::GetLayerObjects(LayerType type)
{
	return objects_[(size_t)type];
}
