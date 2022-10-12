#include "pch.h"
#include "TestScene.h"
#include "Layer.h"
#include "Player.h"
#include "Block.h"
#include "CollisionManager.h"

using namespace std;

void TestScene::Enter()
{
	shared_ptr<Layer> layer = CreateLayer(L"Default", 0);
	CreateLayer(L"UI", UINT_MAX);

	shared_ptr<Object> player = make_unique<Player>();
	player->SetName(L"Player");
	player->SetPosition({ 320, 240 });
	player->SetScale({ 32, 32 });
	player->SetPivot({ 0.5, 0.5 });
	layer->CreateObject(player, GroupObjectType::kPLAYER);

	//layer->DestroyObject(layer->FindObject(L"Player"));

	shared_ptr<Object> object = make_unique<Block>();
	object->SetName(L"Block");
	object->SetPosition({ 100, 100 });
	object->SetScale({ 32, 32 });
	object->SetPivot({ 0.5, 0.5 });
	layer->CreateObject(object, GroupObjectType::kDEFAULT);

	CollisionManager::GetInstance()->SetCollisionMatrix(GroupObjectType::kPLAYER, GroupObjectType::kDEFAULT);
}

void TestScene::Exit()
{
}
