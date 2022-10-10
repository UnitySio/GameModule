#include "pch.h"
#include "Core.h"
#include "Time.h"
#include "SceneManager.h"

using namespace Gdiplus;

// ��� ���� �ʱ�ȭ
unique_ptr<Core> Core::instance_ = nullptr;
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
    wcex.lpszMenuName = NULL/*MAKEINTRESOURCEW(IDC_GAME)*/;
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
    new_bitmap = CreateCompatibleBitmap(memDC, resolution_.x, resolution_.y);
    hdc = CreateCompatibleDC(memDC);

    HBITMAP old_bitmap = (HBITMAP)SelectObject(hdc, new_bitmap);
    DeleteObject(old_bitmap);

    // Time �ʱ�ȭ
    Time::GetInstance()->Initiate();

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

// ���� ��ȭ ������ �޽��� ó����
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
    call_once(flag_, [] // ���ٽ�
        {
            instance_.reset(new Core);
        });

    return instance_.get();
}

void Core::Logic() // ���� �ֱ�
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
    wsprintf(scene_word, L"���� Scene: %s", SceneManager::GetInstance()->GetInstance()->GetCurrentScene());
    PointF scene_font_position(10, 24);
    graphics.DrawString(scene_word, -1, &font_style, scene_font_position, &black_brush);

    PointF font_position(10, 36);
    graphics.DrawString(L"TIP: ����Ű�� ����Ͽ� �̵��ϼ���.", -1, &font_style, font_position, &black_brush);

    SceneManager::GetInstance()->Render(hdc);

    BitBlt(memDC, 0, 0, resolution_.x, resolution_.y, hdc, 0, 0, SRCCOPY);
}
