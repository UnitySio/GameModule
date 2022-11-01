#pragma once

#include "resource.h"
#include "framework.h"

#define MAX_LOADSTRING 100

class Window
{
private:
	HINSTANCE hInst; // ���� �ν��Ͻ�
	HWND hWnd;

	HDC hdc;
	HDC memDC;
	HBITMAP bitmap_;

	POINT resolution_;
	RECT view_area_;

	static LRESULT CALLBACK StaticWndProc(HWND, UINT, WPARAM, LPARAM);
	LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);

	// �̱���
	static std::shared_ptr<Window> instance_;
	static std::once_flag flag_;

	POINT mouse_position_;
public:
	Window();
	~Window() = default;

	Window(const Window&) = delete;
	Window& operator=(const Window&) = delete;

	WCHAR szTitle[MAX_LOADSTRING]; // ���� ǥ���� �ؽ�Ʈ�Դϴ�.
	WCHAR szWindowClass[MAX_LOADSTRING]; // �⺻ â Ŭ���� �̸��Դϴ�.

	ATOM MyRegisterClass(HINSTANCE hinstance);
	BOOL InitInstance(HINSTANCE, int);

	static std::shared_ptr<Window> GetInstance();

	HWND GetHWND();
	HDC GetHDC();

	HANDLE logic_thread_;
	static DWORD WINAPI LogicThread(LPVOID lpParam);

	bool is_logic_loop_;

	void Logic();
	void InputUpdate(); // GetAsyncKeyState�� ���� �����忡���� �����ϱ� ������ �Է°� ���õ� ó���� ������ InputUpdate���� ó���ؾ� �մϴ�.
	void Update(); // Update�� �� ������ ���� ����˴ϴ�.
	void LateUpdate(); // LateUpdate�� ��� Update �Լ��� ó���� �� ����˴ϴ�.
	void PhysicsUpdate();
	void Render();

	Vector2 GetMousePosition();
};
