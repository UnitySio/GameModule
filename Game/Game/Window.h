#pragma once

#include "resource.h"
#include "framework.h"

#define MAX_LOADSTRING 100

/*#define KEYNONE 0x0000
#define KEYUP 0x0001
#define KEYDOWN 0x8000
#define KEY 0x8001*/

#define GetKeyDown(virtual_key) (GetAsyncKeyState(virtual_key) & 0x8000)

class Window
{
private:
	HINSTANCE hInst; // 현재 인스턴스
	HWND hWnd;
	HDC hdc;
	HDC memDC;
	HBITMAP new_bitmap;
	RECT buffer;

	POINT resolution_;

	static LRESULT CALLBACK StaticWndProc(HWND, UINT, WPARAM, LPARAM);
	LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);
	static INT_PTR CALLBACK About(HWND, UINT, WPARAM, LPARAM);

	// 싱글톤
	static unique_ptr<Window> instance_;
	static once_flag flag_;

	void Update(float delta_time);
	void LateUpdate(float delta_time);
	void Render();
public:
	Window() = default;
	~Window() = default;

	Window(const Window&) = delete;
	Window& operator=(const Window&) = delete;

	WCHAR szTitle[MAX_LOADSTRING]; // 제목 표시줄 텍스트입니다.
	WCHAR szWindowClass[MAX_LOADSTRING]; // 기본 창 클래스 이름입니다.

	ATOM MyRegisterClass(HINSTANCE hinstance);
	BOOL InitInstance(HINSTANCE, int);

	static Window* GetInstance();

	void Logic();
};
