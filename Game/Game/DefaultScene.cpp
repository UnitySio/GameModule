#include "pch.h"
#include "DefaultScene.h"
#include "Object.h"
#include "Player.h"
#include "GroundObject.h"
#include "TestObject.h"
#include "CollisionManager.h"
#include "Camera.h"

using namespace std;

DefaultScene::DefaultScene()
{
}

void DefaultScene::Enter()
{
	shared_ptr<Object> ground = make_shared<GroundObject>();
	CreateObject(ground, LayerType::kDefault, L"Ground 1", { 320.f, 380.f }, { 0.f, 0.f }, { 1.f, 1.f });

	shared_ptr<Object> ground_ = make_shared<GroundObject>();
	CreateObject(ground_, LayerType::kDefault, L"Ground 2", { 640.f, 240.f }, { 0.f, 0.f }, { 1.f, 1.f });

	shared_ptr<Object> ground__ = make_shared<GroundObject>();
	CreateObject(ground__, LayerType::kDefault, L"Ground 3", { 150.f, 200.f }, { 0.f, 0.f }, { 1.f, 1.f });

	shared_ptr<Object> ground___ = make_shared<GroundObject>();
	CreateObject(ground___, LayerType::kDefault, L"Ground 4", { 650.f, 784.f }, { 0.f, 0.f }, { 1.f, 1.f });

	shared_ptr<Object> player = make_shared<Player>();
	CreateObject(player, LayerType::kDefault, L"Player", { 320.f, 240.f }, { 0.f, 0.f }, { 3.f, 3.f });

	shared_ptr<Object> test = make_shared<TestObject>(player.get());
	CreateObject(test, LayerType::kDefault, L"Test", { 320.f, 240.f }, { 0.f, 0.f }, { 1.f, 1.f });

	COLLISION->SetCollisionMatrix(LayerType::kDefault, LayerType::kDefault);

	CAMERA->SetTarget(player.get());
	CAMERA->SetLimitArea({ 0.f, 0.f, 800.f, 800.f });
}

void DefaultScene::Exit()
{
}
