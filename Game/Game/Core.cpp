#include "pch.h"
#include "Core.h"
#include "TimeManager.h"
#include "SceneManager.h"
#include "Scene.h"
#include "CollisionManager.h"

using namespace std;
using namespace Gdiplus;

// ��� ���� �ʱ�ȭ
shared_ptr<Core> Core::instance_ = nullptr;
once_flag Core::flag_;

// â Ŭ������ ���
ATOM Core::MyRegisterClass(HINSTANCE hInstance)
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

// �ν��Ͻ� �ڵ��� �����ϰ� �� â�� ����
BOOL Core::InitInstance(HINSTANCE hInstance, int nCmdShow)
{
	hInst = hInstance; // �ν��Ͻ� �ڵ��� ���� ������ �����մϴ�.

	resolution_ = { 640, 480 };

	RECT area = { 0, 0, resolution_.x, resolution_.y };
	AdjustWindowRect(&area, WS_OVERLAPPEDWINDOW, FALSE);

	hWnd = CreateWindowW(szWindowClass, szTitle, WS_OVERLAPPED | WS_CAPTION | WS_SYSMENU | WS_THICKFRAME | WS_MINIMIZEBOX,
		0, 0, area.right - area.left, area.bottom - area.top, nullptr, nullptr, hInstance, nullptr);

	if (!hWnd)
	{
		return FALSE;
	}

	ShowWindow(hWnd, nCmdShow);
	UpdateWindow(hWnd);

	memDC = GetDC(hWnd);
	new_bitmap_ = CreateCompatibleBitmap(memDC, resolution_.x, resolution_.y);
	hdc = CreateCompatibleDC(memDC);

	HBITMAP old_bitmap = (HBITMAP)SelectObject(hdc, new_bitmap_);
	DeleteObject(old_bitmap);

	// TimeManager �ʱ�ȭ
	TimeManager::GetInstance()->Initiate();

	// SceneManager �ʱ�ȭ
	SceneManager::GetInstance()->Initiate();

	return TRUE;
}

// �� â�� �޽����� ó��
LRESULT Core::StaticWndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	return instance_->WndProc(hWnd, message, wParam, lParam);
}

LRESULT Core::WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	switch (message)
	{
	case WM_CREATE:
	{
		HMENU menu = GetSystemMenu(hWnd, FALSE);
		EnableMenuItem(menu, SC_MAXIMIZE, MF_DISABLED);
		EnableMenuItem(menu, SC_MINIMIZE, MF_DISABLED);
		InvalidateRgn(hWnd, NULL, TRUE);

		run_timer_ = 0;
	}
	break;
	case WM_GETMINMAXINFO:
	{
		RECT area = { 0, 0, resolution_.x, resolution_.y };
		AdjustWindowRect(&area, WS_OVERLAPPEDWINDOW, FALSE);

		((MINMAXINFO*)lParam)->ptMinTrackSize.x = area.right - area.left;
		((MINMAXINFO*)lParam)->ptMinTrackSize.y = area.bottom - area.top;
		((MINMAXINFO*)lParam)->ptMaxTrackSize.x = area.right - area.left;
		((MINMAXINFO*)lParam)->ptMaxTrackSize.y = area.bottom - area.top;
	}
	break;
	case WM_PAINT:
	{
		ValidateRect(hWnd, NULL); // �� �̻� WM_PAINT�� ȣ������ ����
	}
	break;
	case WM_COMMAND:
	{
		int wmId = LOWORD(wParam);
		// �޴� ������ ���� �м��մϴ�:
		switch (wmId)
		{
		default:
			return DefWindowProc(hWnd, message, wParam, lParam);
		}
	}
	break;
	case WM_DESTROY:
		// Smart Pointer Singleton �������� �޸� ����
		TimeManager::GetInstance()->Release();
		SceneManager::GetInstance()->Release();
		CollisionManager::GetInstance()->Release();
		instance_.reset();

		ReleaseDC(hWnd, hdc);
		DeleteDC(memDC);
		DeleteObject(new_bitmap_);
		PostQuitMessage(0);
		break;
	default:
		return DefWindowProc(hWnd, message, wParam, lParam);
	}
	return 0;
}

shared_ptr<Core> Core::GetInstance()
{
	call_once(flag_, [] // ���ٽ�
		{
			instance_.reset(new Core);
		});

	return instance_;
}

void Core::Logic() // ���� �ֱ�
{
	TimeManager::GetInstance()->Update();

	float delta_time_ = TimeManager::GetInstance()->GetDeltaTime();


	Update(delta_time_);
	LateUpdate(delta_time_);
	Render();
}

HDC Core::GetHDC()
{
	return hdc;
}

void Core::Update(float delta_time)
{
	SceneManager::GetInstance()->Update(delta_time);

	run_timer_ += delta_time;
}

void Core::LateUpdate(float delta_time)
{
	SceneManager::GetInstance()->LateUpdate(delta_time);
	CollisionManager::GetInstance()->LateUpdate(delta_time);
}

void Core::Render()
{
	Graphics graphics(hdc);

	FontFamily arial_font(L"Arial");
	Font font_style(&arial_font, 12, FontStyleBold, UnitPixel);

	SolidBrush white_brush(Color(255, 255, 255, 255));
	SolidBrush black_brush(Color(255, 0, 0, 0));

	graphics.FillRectangle(&white_brush, -1, -1, resolution_.x, resolution_.y);

	WCHAR fps_word[1024];
	wsprintf(fps_word, L"FPS: %d", TimeManager::GetInstance()->GetFPS());
	PointF fps_font_position(10, 10);
	graphics.DrawString(fps_word, -1, &font_style, fps_font_position, &black_brush);

	WCHAR scene_word[1024];
	wsprintf(scene_word, L"Current Scene: %s", SceneManager::GetInstance()->GetCurrentScene()->GetName());
	PointF scene_font_position(10, 24);
	graphics.DrawString(scene_word, -1, &font_style, scene_font_position, &black_brush);

	// �׽�Ʈ �ڵ�
	WCHAR timer_word[1024];
	_stprintf_s(timer_word, L"Run Time: %.2fs", run_timer_);
	PointF timer_font_position(10, 36);
	graphics.DrawString(timer_word, -1, &font_style, timer_font_position, &black_brush);

	SceneManager::GetInstance()->Render(hdc);

	BitBlt(memDC, 0, 0, resolution_.x, resolution_.y, hdc, 0, 0, SRCCOPY);
}
