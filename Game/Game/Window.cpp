#include "pch.h"
#include "Window.h"
#include "InputManager.h"
#include "SceneManager.h"
#include "Scene.h"
#include "CollisionManager.h"
#include "Camera.h"

using namespace std;
using namespace Gdiplus;

// 멤버 변수 초기화
shared_ptr<Window> Window::instance_ = nullptr;
once_flag Window::flag_;

// 창 클래스를 등록
ATOM Window::MyRegisterClass(HINSTANCE hInstance)
{
	WNDCLASSEXW wcex;

	wcex.cbSize = sizeof(WNDCLASSEX);

	wcex.style = CS_HREDRAW | CS_VREDRAW | CS_DBLCLKS;
	wcex.lpfnWndProc = StaticWndProc;
	wcex.cbClsExtra = 0;
	wcex.cbWndExtra = 0;
	wcex.hInstance = hInstance;
	wcex.hIcon = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_GAME));
	wcex.hCursor = LoadCursor(nullptr, IDC_ARROW);
	wcex.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
	wcex.lpszMenuName = NULL;
	wcex.lpszClassName = szWindowClass;
	wcex.hIconSm = LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_SMALL));

	return RegisterClassExW(&wcex);
}

// 인스턴스 핸들을 저장하고 주 창을 만듬
BOOL Window::InitInstance(HINSTANCE hInstance, int nCmdShow)
{
	hInst = hInstance; // 인스턴스 핸들을 전역 변수에 저장합니다.

	int screen_width = GetSystemMetrics(SM_CXSCREEN);
	int screen_height = GetSystemMetrics(SM_CYSCREEN);

	hWnd = CreateWindowW(szWindowClass, szTitle, WS_OVERLAPPED | WS_CAPTION | WS_SYSMENU | WS_THICKFRAME | WS_MINIMIZEBOX,
		(screen_width - (client_area_.right - client_area_.left)) / 2, (screen_height - (client_area_.bottom - client_area_.top)) / 2, client_area_.right - client_area_.left, client_area_.bottom - client_area_.top, nullptr, nullptr, hInstance, nullptr);

	if (!hWnd)
	{
		return FALSE;
	}

	ShowWindow(hWnd, nCmdShow);
	UpdateWindow(hWnd);

	memDC = GetDC(hWnd);
	bitmap_ = CreateCompatibleBitmap(memDC, resolution_.x, resolution_.y);
	hdc = CreateCompatibleDC(memDC);

	HBITMAP old_bitmap = (HBITMAP)SelectObject(hdc, bitmap_);
	DeleteObject(old_bitmap);

	TIME->Initiate();
	INPUT->Initiate();
	CAMERA->Initiate();
	SCENE->Initiate();

	return TRUE;
}

// 주 창의 메시지를 처리
LRESULT Window::StaticWndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	return instance_->WndProc(hWnd, message, wParam, lParam);
}

LRESULT Window::WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	switch (message)
	{
	case WM_GETMINMAXINFO:
	{
		((MINMAXINFO*)lParam)->ptMinTrackSize.x = client_area_.right - client_area_.left;
		((MINMAXINFO*)lParam)->ptMinTrackSize.y = client_area_.bottom - client_area_.top;
		((MINMAXINFO*)lParam)->ptMaxTrackSize.x = client_area_.right - client_area_.left;
		((MINMAXINFO*)lParam)->ptMaxTrackSize.y = client_area_.bottom - client_area_.top;
	}
	break;
	case WM_COMMAND:
	{
		int wmId = LOWORD(wParam);
		// 메뉴 선택을 구문 분석합니다:
		switch (wmId)
		{
		default:
			return DefWindowProc(hWnd, message, wParam, lParam);
		}
	}
	break;
	case WM_PAINT:
	{
		// WM_PAINT를 호출하지 않음
		ValidateRect(hWnd, NULL);
	}
	break;
	break;
	case WM_DESTROY:
		is_logic_loop_ = false;
		WaitForSingleObject(logic_thread_, INFINITE); // Thread가 완료될 때까지 대기
		TIME->Release();
		INPUT->Release();
		SCENE->Release();
		COLLISION->Release();
		CAMERA->Release();
		instance_.reset();
		PostQuitMessage(0);
		break;
	default:
		return DefWindowProc(hWnd, message, wParam, lParam);
	}
	return 0;
}

Window::Window() :
	hInst(),
	hWnd(),
	hdc(),
	memDC(),
	bitmap_(),
	szTitle(),
	szWindowClass(),
	mouse_position_{},
	is_logic_loop_(true)
{
	resolution_ = { 640, 480 };
	client_area_ = { 0, 0, resolution_.x, resolution_.y };
	AdjustWindowRect(&client_area_, WS_OVERLAPPEDWINDOW, FALSE);
}

shared_ptr<Window> Window::GetInstance()
{
	call_once(flag_, [] // 람다식
		{
			instance_.reset(new Window);
		});

	return instance_;
}

HWND Window::GetHWND()
{
	return hWnd;
}

HDC Window::GetHDC()
{
	return hdc;
}

DWORD WINAPI Window::LogicThread(LPVOID lpParam)
{
	while (TRUE)
	{
		instance_->Logic();

		if (!instance_->is_logic_loop_)
		{
			break;
		}
	}

	return 0;
}

// 서브 스레드에서 동작
void Window::Logic()
{
	instance_->Update();
	instance_->LateUpdate();
	instance_->PhysicsUpdate();
	instance_->Render();
	SCENE->SceneUpdate();
}

// 메인 스레드에서 동작
void Window::InputUpdate()
{
	INPUT->InputUpdate();
	SCENE->InputUpdate();
}

void Window::Update()
{
	GetCursorPos(&mouse_position_);
	ScreenToClient(hWnd, &mouse_position_);

	TIME->Update();
	SCENE->Update();
	CAMERA->Update();
}

void Window::LateUpdate()
{
	SCENE->LateUpdate();
	CAMERA->LateUpdate();
}

void Window::PhysicsUpdate()
{
	SCENE->PhysicsUpdate();
	COLLISION->PhysicsUpdate();
}

void Window::Render()
{
	// 임시 배경
	HPEN new_pen = CreatePen(PS_SOLID, 0, RGB(71, 71, 71));
	HPEN old_pen = (HPEN)SelectObject(hdc, new_pen);

	HBRUSH new_brush = CreateSolidBrush(RGB(71, 71, 71));
	HBRUSH old_brush = (HBRUSH)SelectObject(hdc, new_brush);

	Rectangle(hdc, 0, 0, resolution_.x, resolution_.y);

	SelectObject(hdc, old_pen);
	DeleteObject(new_pen);

	SelectObject(hdc, old_brush);
	DeleteObject(new_brush);

	SCENE->Render();

	WCHAR fps_word[128];
	wsprintf(fps_word, L"FPS: %d", TIME->GetFPS());
	TextOut(hdc, 0, 0, fps_word, wcslen(fps_word));

	BitBlt(memDC, 0, 0, resolution_.x, resolution_.y, hdc, 0, 0, SRCCOPY);
}

Vector2 Window::GetMousePosition()
{
	return { (float)mouse_position_.x, (float)mouse_position_.y };
}

Vector2 Window::GetResolution()
{
	return { (float)resolution_.x, (float)resolution_.y };
}
