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
		current_scene_->CreateObject(objects_[i], LayerType::kDefault, L"Bullet", { 320.f, 240.f }, {}, {});
	}

	objects_.clear();
}

void SceneManager::Instantiate(shared_ptr<Object> object)
{
	objects_.push_back(object);
}

void SceneManager::Destroy(shared_ptr<Object> object)
{
}

shared_ptr<Scene> SceneManager::GetCurrentScene()
{
	return current_scene_;
}
