#include "pch.h"
#include "SceneManager.h"
#include "TestScene.h"

using namespace std;

// 멤버 변수 초기화
shared_ptr<SceneManager> SceneManager::instance_ = nullptr;
once_flag SceneManager::flag_;

SceneManager::SceneManager() : scenes_{}, current_scene_()
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
    scenes_[(size_t)SceneType::kTestScene] = make_shared<TestScene>();
    scenes_[(size_t)SceneType::kTestScene]->SetName(L"Test Scene");
    current_scene_ = scenes_[(size_t)SceneType::kTestScene];

    current_scene_->Enter();
}

void SceneManager::Update(float delta_time)
{
    current_scene_->Update(delta_time);
}

void SceneManager::LateUpdate(float delta_time)
{
    current_scene_->LateUpdate(delta_time);
}

void SceneManager::Render(HDC hdc)
{
    current_scene_->Render(hdc);
}

shared_ptr<Scene> SceneManager::GetCurrentScene()
{
    return current_scene_;
}
