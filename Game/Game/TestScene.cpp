#include "pch.h"
#include "TestScene.h"
#include "Player.h"

using namespace std;

void TestScene::Enter()
{
	shared_ptr<Layer> layer = CreateLayer(L"Default", 0);
	CreateLayer(L"UI", UINT_MAX);

	shared_ptr<Object> object = make_unique<Player>();
	object->SetName(L"Player");
	object->SetPosition({ 320, 240 });
	object->SetScale({ 32, 32 });
	object->SetPivot({ 0.5, 0.5 });
	layer->CreateObject(object, GroupObjectType::kPLAYER);

	//layer->DestroyObject(layer->FindObject(L"Player"));
}

void TestScene::Exit()
{
}
