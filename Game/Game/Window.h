#pragma once

#include "resource.h"
#include "framework.h"

#define MAX_LOADSTRING 100

class Window
{
private:
	HINSTANCE hInst; // 현재 인스턴스
	HWND hWnd;

	HDC hdc;
	HDC memDC;
	HBITMAP bitmap_;

	POINT resolution_;
	RECT view_area_;

	static LRESULT CALLBACK StaticWndProc(HWND, UINT, WPARAM, LPARAM);
	LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);

	// 싱글톤
	static std::shared_ptr<Window> instance_;
	static std::once_flag flag_;

	POINT mouse_position_;
public:
	Window();
	~Window() = default;

	Window(const Window&) = delete;
	Window& operator=(const Window&) = delete;

	WCHAR szTitle[MAX_LOADSTRING]; // 제목 표시줄 텍스트입니다.
	WCHAR szWindowClass[MAX_LOADSTRING]; // 기본 창 클래스 이름입니다.

	ATOM MyRegisterClass(HINSTANCE hinstance);
	BOOL InitInstance(HINSTANCE, int);

	static std::shared_ptr<Window> GetInstance();

	HWND GetHWND();
	HDC GetHDC();

	HANDLE logic_thread_;
	static DWORD WINAPI LogicThread(LPVOID lpParam);

	bool is_logic_loop_;

	void Logic();
	void InputUpdate(); // GetAsyncKeyState는 메인 스레드에서만 동작하기 때문에 입력과 관련된 처리는 무조건 InputUpdate에서 처리해야 합니다.
	void Update(); // Update는 매 프레임 마다 실행됩니다.
	void LateUpdate(); // LateUpdate는 모든 Update 함수가 처리된 후 실행됩니다.
	void PhysicsUpdate();
	void Render();

	Vector2 GetMousePosition();
};
