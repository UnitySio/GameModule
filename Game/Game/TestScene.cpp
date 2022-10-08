#include "TestScene.h"
#include "Object.h"
#include "Player.h"

void TestScene::Enter()
{
	shared_ptr<Object> object = make_unique<Player>();
	object->SetName(L"Player");
	object->SetPosition({ 0, 0 });
	object->SetScale({ 100, 100 });
	CreateInstance(object, ObjectTypeGroup::kPLAYER);
}

void TestScene::Exit()
{
}
