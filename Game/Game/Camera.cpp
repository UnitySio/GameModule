#include "pch.h"
#include "Camera.h"

using namespace std;

// ��� ���� �ʱ�ȭ
shared_ptr<Camera> Camera::instance_ = nullptr;
once_flag Camera::flag_;

Camera::Camera()
{
}

std::shared_ptr<Camera> Camera::GetInstance()
{
    call_once(flag_, [] // ���ٽ�
        {
            instance_.reset(new Camera);
        });

    return instance_;
}

void Camera::Release()
{
    instance_.reset();
}
