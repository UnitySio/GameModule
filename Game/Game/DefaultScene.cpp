#include "pch.h"
#include "DefaultScene.h"

#include "Boss.h"
#include "Object.h"
#include "Player.h"
#include "Ground.h"
#include "CollisionManager.h"
#include "Camera.h"

using namespace std;

void DefaultScene::Enter()
{
    shared_ptr<Object> ground = make_shared<Ground>();
    CreateObject(ground, LayerType::kGround, L"Ground", {400.f, 768.f}, {1.f, 1.f});

    shared_ptr<Object> player = make_shared<Player>();
    CreateObject(player, LayerType::kDefault, L"Player", {0.f, 240.f}, {3.f, 3.f});

    shared_ptr<Object> boss = make_shared<Boss>();
    CreateObject(boss, LayerType::kDefault, L"Boss", { 100.f, 100.f }, { 3.f, 3.f });
    (*(Boss*)boss.get()).SetTarget(player.get()); // 추후 스마트 포인터로 변경 예정
    
    COLLISION->SetCollisionMatrix(LayerType::kDefault, LayerType::kGround);
    COLLISION->SetCollisionMatrix(LayerType::kGround, LayerType::kBullet);

    CAMERA->SetTarget(player.get());
    CAMERA->SetLimitArea({0.f, 0.f, 800.f, 800.f});
}

void DefaultScene::Exit()
{
}
