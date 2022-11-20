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
    RECT client_area_;

    static LRESULT CALLBACK StaticWndProc(HWND, UINT, WPARAM, LPARAM);
    LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);

    // �̱���
    static std::shared_ptr<Window> instance_;
    static std::once_flag flag_;

    bool is_logic_loop_;

    POINT mouse_position_;

    HANDLE logic_thread_;
    HANDLE semaphore_;
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
    static DWORD WINAPI LogicThread(LPVOID lpParam);

    HWND GetHWND();
    HDC GetHDC();

    void SetThread(HANDLE handle);
    void Logic();
    void InputUpdate(); // GetAsyncKeyState�� ���� �����忡���� �����ϱ� ������ �Է°� ���õ� ó���� ������ InputUpdate���� ó���ؾ� �մϴ�.
    void Update(); // Update�� �� ������ ���� ����˴ϴ�.
    void LateUpdate(); // LateUpdate�� ��� Update �Լ��� ó���� �� ����˴ϴ�.
    void PhysicsUpdate(); // PhysicsUpdate�� ��� LateUpdate �Լ��� ó���� �� ����˴ϴ�, �ش� �Լ������� �������� ó���մϴ�.
    void Render();

    Vector2 GetMousePosition();
    Vector2 GetResolution();
};
