#include "pch.h"
#include "Window.h"
#include "SceneManager.h"
#include "Scene.h"

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

	hWnd = CreateWindowW(szWindowClass, szTitle, WS_OVERLAPPED | WS_CAPTION | WS_SYSMENU | WS_THICKFRAME | WS_MINIMIZEBOX,
		0, 0, view_area_.right - view_area_.left, view_area_.bottom - view_area_.top, nullptr, nullptr, hInstance, nullptr);

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

	TimeManager::GetInstance()->Initiate();
	SceneManager::GetInstance()->Initiate();

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
		((MINMAXINFO*)lParam)->ptMinTrackSize.x = view_area_.right - view_area_.left;
		((MINMAXINFO*)lParam)->ptMinTrackSize.y = view_area_.bottom - view_area_.top;
		((MINMAXINFO*)lParam)->ptMaxTrackSize.x = view_area_.right - view_area_.left;
		((MINMAXINFO*)lParam)->ptMaxTrackSize.y = view_area_.bottom - view_area_.top;
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
		TimeManager::GetInstance()->Release();
		SceneManager::GetInstance()->Release();
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
	szWindowClass()
{
	resolution_ = { 640, 480 };
	view_area_ = { 0, 0, resolution_.x, resolution_.y };
	AdjustWindowRect(&view_area_, WS_OVERLAPPEDWINDOW, FALSE);
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

void Window::Logic()
{
	Update();
	LateUpdate();
	PhysicsUpdate();
	Render();
}

void Window::Update()
{
	GetCursorPos(&mouse_position_);
	ScreenToClient(hWnd, &mouse_position_);

	TimeManager::GetInstance()->Update();
	SceneManager::GetInstance()->Update();
}

void Window::LateUpdate()
{
	SceneManager::GetInstance()->LateUpdate();
}

void Window::PhysicsUpdate()
{
	SceneManager::GetInstance()->PhysicsUpdate();
}

void Window::Render()
{
	// 임시 배경
	HPEN new_pen = CreatePen(PS_NULL, 0, RGB(255, 255, 255));
	HPEN old_pen = (HPEN)SelectObject(hdc, new_pen);

	HBRUSH new_brush = CreateSolidBrush(RGB(255, 255, 255));
	HBRUSH old_brush = (HBRUSH)SelectObject(hdc, new_brush);

	Rectangle(hdc, 0, 0, resolution_.x, resolution_.y);

	SelectObject(hdc, old_pen);
	DeleteObject(new_pen);

	SelectObject(hdc, old_brush);
	DeleteObject(new_brush);

	// TODO: 여기에 코드를 입력합니다.

	SceneManager::GetInstance()->Render();

	WCHAR scene_name_word[1024];
	WCHAR mouse_position_word[1024];

	wsprintf(scene_name_word, L"Current Scene: %s", SceneManager::GetInstance()->GetCurrentScene()->GetName());
	wsprintf(mouse_position_word, L"%d, %d", mouse_position_.x, mouse_position_.y);

	SetBkMode(hdc, TRANSPARENT); // TextOut 배경색 제거
	TextOut(hdc, 0, 0, scene_name_word, wcslen(scene_name_word));
	TextOut(hdc, mouse_position_.x + 16, mouse_position_.y + 16, mouse_position_word, wcslen(mouse_position_word));

	BitBlt(memDC, 0, 0, resolution_.x, resolution_.y, hdc, 0, 0, SRCCOPY);
}

Vector2 Window::GetMousePosition()
{
	return { (float)mouse_position_.x, (float)mouse_position_.y };
}
