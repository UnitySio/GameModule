#include "Window.h"
#include "ObjectManager.h"
#include "Time.h"

// 멤버 변수 초기화
unique_ptr<Window> Window::instance_ = nullptr;
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
    wcex.lpszMenuName = NULL/*MAKEINTRESOURCEW(IDC_GAME)*/;
    wcex.lpszClassName = szWindowClass;
    wcex.hIconSm = LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_SMALL));

    return RegisterClassExW(&wcex);
}

// 인스턴스 핸들을 저장하고 주 창을 만듬
BOOL Window::InitInstance(HINSTANCE hInstance, int nCmdShow)
{
    hInst = hInstance; // 인스턴스 핸들을 전역 변수에 저장합니다.

    hWnd = CreateWindowW(szWindowClass, szTitle, WS_OVERLAPPEDWINDOW,
        0, 0, 640, 480, nullptr, nullptr, hInstance, nullptr);

    if (!hWnd)
    {
        return FALSE;
    }

    ShowWindow(hWnd, nCmdShow);
    UpdateWindow(hWnd);

    // Time 초기화
    Time::GetInstance()->Initiate();

    // ObjectManager 초기화
    ObjectManager::GetInstance()->Initiate();

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
    case WM_PAINT:
    {
        PAINTSTRUCT ps;
        HDC hdc, memDC;
        HBITMAP newBitmap, oldBitmap;
        RECT buffer;
        memDC = BeginPaint(hWnd, &ps);

        GetClientRect(hWnd, &buffer);
        hdc = CreateCompatibleDC(memDC);
        newBitmap = CreateCompatibleBitmap(memDC, buffer.right, buffer.bottom);
        oldBitmap = (HBITMAP)SelectObject(hdc, newBitmap);
        PatBlt(hdc, 0, 0, buffer.right, buffer.bottom, WHITENESS);
        // TODO: 여기에 hdc를 사용하는 그리기 코드를 추가합니다...

        OnPaint(hdc);

        GetClientRect(hWnd, &buffer);
        BitBlt(memDC, 0, 0, buffer.right, buffer.bottom, hdc, 0, 0, SRCCOPY);
        SelectObject(hdc, oldBitmap);
        DeleteObject(newBitmap);
        DeleteDC(hdc);
        EndPaint(hWnd, &ps);
    }
    break;
    case WM_DESTROY:
        PostQuitMessage(0);
        break;
    default:
        return DefWindowProc(hWnd, message, wParam, lParam);
    }
    return 0;
}

// 정보 대화 상자의 메시지 처리기
INT_PTR CALLBACK Window::About(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
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

void Window::OnPaint(HDC hdc)
{
    Graphics graphics(hdc);

    Pen black_pen(Color(255, 0, 0, 0));

    graphics.DrawRectangle(&black_pen, (int)x_, (int)y_, 30, 30);
}

Window* Window::GetInstance()
{
    call_once(flag_, [] // 람다식
        {
            instance_.reset(new Window);
        });

    return instance_.get();
}

void Window::Logic() // 생명 주기
{
    Time::GetInstance()->Update();

    float delta_time_ = Time::GetInstance()->GetDeltaTime();

    Update(delta_time_);
    LateUpdate(delta_time_);
    Render();
}

void Window::Update(float delta_time)
{
    ObjectManager::GetInstance()->Update(delta_time);

    float speed = 100 * delta_time * 1.0f;

    if (GetKeyDown(VK_LEFT))
    {
        x_ -= speed;
    }

    if (GetKeyDown(VK_RIGHT))
    {
        x_ += speed;
    }

    if (GetKeyDown(VK_UP))
    {
        y_ -= speed;
    }

    if (GetKeyDown(VK_DOWN))
    {
        y_ += speed;
    }
}

void Window::LateUpdate(float delta_time)
{
    ObjectManager::GetInstance()->LateUpdate(delta_time);
}

void Window::Render()
{
    ObjectManager::GetInstance()->Render();
    InvalidateRect(hWnd, NULL, FALSE);
}
