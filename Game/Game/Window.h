#pragma once

#include "resource.h"
#include "framework.h"
#include "Singleton.h"

#define MAX_LOADSTRING 100

class Window :
    public Singleton<Window>
{
private:
    HINSTANCE hInst; // 현재 인스턴스
    HWND hWnd;

    HDC hdc;
    HDC memDC;
    HBITMAP bitmap_;

    POINT resolution_;
    RECT client_area_;

    static LRESULT CALLBACK StaticWndProc(HWND, UINT, WPARAM, LPARAM);
    LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);

    bool is_logic_loop_;

    POINT mouse_position_;

    HANDLE logic_thread_;
    HANDLE semaphore_;
public:
    Window();
    ~Window() final = default;

    WCHAR szTitle[MAX_LOADSTRING]; // 제목 표시줄 텍스트입니다.
    WCHAR szWindowClass[MAX_LOADSTRING]; // 기본 창 클래스 이름입니다.

    ATOM MyRegisterClass(HINSTANCE hinstance);
    BOOL InitInstance(HINSTANCE, int);

    static DWORD WINAPI LogicThread(LPVOID lpParam);

    HWND GetHWND();
    HDC GetHDC();

    void SetThread(HANDLE handle);
    void Logic();
    void InputUpdate(); // GetAsyncKeyState는 메인 스레드에서만 동작하기 때문에 입력과 관련된 처리는 무조건 InputUpdate에서 처리해야 합니다.
    void Update(); // Update는 매 프레임 마다 실행됩니다.
    void LateUpdate(); // LateUpdate는 모든 Update 함수가 처리된 후 실행됩니다.
    void PhysicsUpdate(); // PhysicsUpdate는 모든 LateUpdate 함수가 처리된 후 실행됩니다, 해당 함수에서는 물리만을 처리합니다.
    void Render();

    Vector2 GetMousePosition();
    Vector2 GetResolution();
};
