#include "pch.h"
#include "Window.h"
#include "InputManager.h"
#include "SceneManager.h"
#include "Scene.h"
#include "CollisionManager.h"
#include "Camera.h"

using namespace std;
using namespace Gdiplus;

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

	hWnd = CreateWindowW(szWindowClass, szTitle,
		WS_OVERLAPPED | WS_CAPTION | WS_SYSMENU | WS_THICKFRAME | WS_MINIMIZEBOX,
		(screen_width - (client_area_.right - client_area_.left)) / 2,
		(screen_height - (client_area_.bottom - client_area_.top)) / 2,
		client_area_.right - client_area_.left, client_area_.bottom - client_area_.top, nullptr,
		nullptr, hInstance, nullptr);

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
	return GetInstance()->WndProc(hWnd, message, wParam, lParam);
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
	case WM_DESTROY:
		is_logic_loop_ = false;
		WaitForSingleObject(logic_thread_, INFINITE); // Thread가 완료될 때까지 대기
		TIME->Release();
		INPUT->Release();
		SCENE->Release();
		COLLISION->Release();
		CAMERA->Release();
		GetInstance()->Release();
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
	semaphore_ = CreateSemaphore(NULL, 0, 1, NULL); // 세마포 생성
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
		GetInstance()->Logic();

		if (!GetInstance()->is_logic_loop_)
		{
			break;
		}
	}

	return 0;
}

void Window::SetThread(HANDLE handle)
{
	logic_thread_ = handle;
}

// 서브 스레드에서 동작
void Window::Logic()
{
	GetInstance()->Update();
	GetInstance()->LateUpdate();
	GetInstance()->PhysicsUpdate();
	ReleaseSemaphore(semaphore_, 1, NULL);
	GetInstance()->Render();
	SCENE->SceneUpdate();
}

// 메인 스레드에서 동작
void Window::InputUpdate()
{
	WaitForSingleObject(semaphore_, INFINITE);
	INPUT->InputUpdate();
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
	SetBkMode(hdc, TRANSPARENT);

	// Background
	HBRUSH new_brush = CreateSolidBrush(RGB(49, 77, 121));
	HBRUSH old_brush = (HBRUSH)SelectObject(hdc, new_brush);

	PatBlt(hdc, 0, 0, resolution_.x, resolution_.y, PATCOPY);

	SelectObject(hdc, old_brush);
	DeleteObject(new_brush);

	// 여기서 부터 코드 작성

	SCENE->Render();

	SetTextColor(hdc, RGB(255, 255, 255));
	RECT rect = { 0, 0, 500, 500 };
	DrawText(WINDOW->GetHDC(), L"RESTART: R\nMOVE: W, A, S, D\nRUN: SHIFT\nJUMP: SPACE\nATTACK: MOUSE LBUTTON\nDASH: MOUSE RBUTTON", -1, &rect, DT_LEFT);

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
