#include "pch.h"
#include "SceneManager.h"
#include "Scene.h"
#include "DefaultScene.h"
#include "Object.h"
#include "InputManager.h"
#include "Window.h"

using namespace std;
using namespace Gdiplus;

// 멤버 변수 초기화
shared_ptr<SceneManager> SceneManager::instance_ = nullptr;
once_flag SceneManager::flag_;

SceneManager::SceneManager() :
	scenes_{},
	current_scene_(),
	objects_{}
{
}

shared_ptr<SceneManager> SceneManager::GetInstance()
{
	call_once(flag_, [] // 람다식
		{
			instance_.reset(new SceneManager);
		});

	return instance_;
}

void SceneManager::Release()
{
	instance_.reset();
}

void SceneManager::Initiate()
{
	shared_ptr<Scene> default_scene = make_shared<DefaultScene>();
	CreateScene(default_scene, SceneType::kDefault, L"Default");

	LoadScene(SceneType::kDefault);
}

void SceneManager::CreateScene(std::shared_ptr<Scene> scene, SceneType scene_type, LPCWSTR name)
{
	scene->SetName(name);

	scenes_[(size_t)scene_type] = scene;
}

void SceneManager::LoadScene(SceneType scene_type)
{
	if (current_scene_ != nullptr)
	{
		current_scene_->Exit();
	}

	current_scene_ = scenes_[(size_t)scene_type];
	current_scene_->Enter();
}

void SceneManager::Update()
{
	if (current_scene_ != nullptr)
	{
		current_scene_->Update();
	}
}

void SceneManager::LateUpdate()
{
	if (current_scene_ != nullptr)
	{
		current_scene_->LateUpdate();
	}
}

void SceneManager::PhysicsUpdate()
{
	if (current_scene_ != nullptr)
	{
		current_scene_->PhysicsUpdate();
	}
}

void SceneManager::Render()
{
	if (current_scene_ != nullptr)
	{
		current_scene_->Render();
	}
}

void SceneManager::SceneUpdate()
{
	for (size_t i = 0; i < objects_.size(); i++)
	{
		current_scene_->CreateObject(objects_[i].object, objects_[i].type, objects_[i].name, objects_[i].position, objects_[i].rotation, objects_[i].scale);
	}

	objects_.clear();

	if (current_scene_ != nullptr)
	{
		current_scene_->SceneUpdate();
	}
}

void SceneManager::Instantiate(shared_ptr<Object> object, LayerType type, LPCWSTR name, Vector2 position, Vector2 rotation, Vector2 scale)
{
	objects_.push_back({ object, type, name, position, rotation, scale});
}

void SceneManager::Destroy(shared_ptr<Object> object)
{
	object->SetDestroy();
}

shared_ptr<Scene> SceneManager::GetCurrentScene()
{
	return current_scene_;
}
