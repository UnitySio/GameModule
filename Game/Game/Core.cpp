#include "pch.h"
#include "Core.h"
#include "Time.h"
#include "SceneManager.h"

using namespace Gdiplus;

// 멤버 변수 초기화
unique_ptr<Core> Core::instance_ = nullptr;
once_flag Core::flag_;

// 창 클래스를 등록
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
    wcex.lpszMenuName = NULL/*MAKEINTRESOURCEW(IDC_GAME)*/;
    wcex.lpszClassName = szWindowClass;
    wcex.hIconSm = LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_SMALL));

    return RegisterClassExW(&wcex);
}

// 인스턴스 핸들을 저장하고 주 창을 만듬
BOOL Core::InitInstance(HINSTANCE hInstance, int nCmdShow)
{
    hInst = hInstance; // 인스턴스 핸들을 전역 변수에 저장합니다.

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
    new_bitmap = CreateCompatibleBitmap(memDC, resolution_.x, resolution_.y);
    hdc = CreateCompatibleDC(memDC);

    HBITMAP old_bitmap = (HBITMAP)SelectObject(hdc, new_bitmap);
    DeleteObject(old_bitmap);

    // Time 초기화
    Time::GetInstance()->Initiate();

    // SceneManager 초기화
    SceneManager::GetInstance()->Initiate();

    return TRUE;
}

// 주 창의 메시지를 처리
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
        ValidateRect(hWnd, NULL); // 더 이상 WM_PAINT를 호출하지 않음
    }
    break;
    case WM_COMMAND:
    {
        int wmId = LOWORD(wParam);
        // 메뉴 선택을 구문 분석합니다:
        switch (wmId)
        {
        case IDM_ABOUT:
            DialogBox(hInst, MAKEINTRESOURCE(IDD_ABOUTBOX), hWnd, About);
            break;
        case IDM_EXIT:
            DestroyWindow(hWnd);
            break;
        default:
            return DefWindowProc(hWnd, message, wParam, lParam);
        }
    }
    break;
    case WM_DESTROY:
        ReleaseDC(hWnd, hdc);
        DeleteDC(memDC);
        DeleteObject(new_bitmap);
        PostQuitMessage(0);
        break;
    default:
        return DefWindowProc(hWnd, message, wParam, lParam);
    }
    return 0;
}

// 정보 대화 상자의 메시지 처리기
INT_PTR CALLBACK Core::About(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
    UNREFERENCED_PARAMETER(lParam);
    switch (message)
    {
    case WM_INITDIALOG:
        return (INT_PTR)TRUE;

    case WM_COMMAND:
        if (LOWORD(wParam) == IDOK || LOWORD(wParam) == IDCANCEL)
        {
            EndDialog(hDlg, LOWORD(wParam));
            return (INT_PTR)TRUE;
        }
        break;
    }
    return (INT_PTR)FALSE;
}

Core* Core::GetInstance()
{
    call_once(flag_, [] // 람다식
        {
            instance_.reset(new Core);
        });

    return instance_.get();
}

void Core::Logic() // 생명 주기
{
    Time::GetInstance()->Update();

    float delta_time_ = Time::GetInstance()->GetDeltaTime();

    Update(delta_time_);
    LateUpdate(delta_time_);
    Render();
}

void Core::Update(float delta_time)
{
    SceneManager::GetInstance()->Update(delta_time);
}

void Core::LateUpdate(float delta_time)
{
    SceneManager::GetInstance()->LateUpdate(delta_time);
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
    wsprintf(fps_word, L"FPS: %d", Time::GetInstance()->GetFPS());
    PointF fps_font_position(10, 10);
    graphics.DrawString(fps_word, -1, &font_style, fps_font_position, &black_brush);
    
    WCHAR scene_word[1024];
    wsprintf(scene_word, L"현재 Scene: %s", SceneManager::GetInstance()->GetInstance()->GetCurrentScene());
    PointF scene_font_position(10, 24);
    graphics.DrawString(scene_word, -1, &font_style, scene_font_position, &black_brush);

    PointF font_position(10, 36);
    graphics.DrawString(L"TIP: 방향키를 사용하여 이동하세요.", -1, &font_style, font_position, &black_brush);

    SceneManager::GetInstance()->Render(hdc);

    BitBlt(memDC, 0, 0, resolution_.x, resolution_.y, hdc, 0, 0, SRCCOPY);
}
