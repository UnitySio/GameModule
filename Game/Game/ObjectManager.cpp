#include "ObjectManager.h"

// ��� ���� �ʱ�ȭ
unique_ptr<ObjectManager> ObjectManager::instance_ = nullptr;
once_flag ObjectManager::flag_;

ObjectManager* ObjectManager::GetInstance()
{
    call_once(flag_, [] // ���ٽ�
        {
            instance_.reset(new ObjectManager);
        });

    return instance_.get();
}

void ObjectManager::Initiate()
{
}

void ObjectManager::Update(float detla_time)
{
}

void ObjectManager::LateUpdate(float detla_time)
{
}

void ObjectManager::Render()
{
}

void ObjectManager::CreateObject(Object* object)
{
    object->Initiate();
}
