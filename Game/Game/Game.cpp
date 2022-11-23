#include "pch.h"
#include "Game.h"

using namespace Gdiplus;

int APIENTRY wWinMain(_In_ HINSTANCE hInstance,
                      _In_opt_ HINSTANCE hPrevInstance,
                      _In_ LPWSTR lpCmdLine,
                      _In_ int nCmdShow)
{
    UNREFERENCED_PARAMETER(hPrevInstance);
    UNREFERENCED_PARAMETER(lpCmdLine);

    // TODO: 여기에 코드를 입력합니다.

    GdiplusStartupInput gdiplus_startup_input;
    ULONG_PTR gdiplus_token;

    GdiplusStartup(&gdiplus_token, &gdiplus_startup_input, NULL);

    // 전역 문자열을 초기화합니다.
    LoadStringW(hInstance, IDS_APP_TITLE, WINDOW->szTitle, MAX_LOADSTRING);
    LoadStringW(hInstance, IDC_GAME, WINDOW->szWindowClass, MAX_LOADSTRING);
    WINDOW->MyRegisterClass(hInstance);

    // 애플리케이션 초기화를 수행합니다:
    if (!WINDOW->InitInstance(hInstance, nCmdShow))
    {
        return FALSE;
    }

    HACCEL hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_GAME));

    MSG msg;

#ifdef _DEBUG
    _CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
#endif // _DEBUG

    HANDLE mutex;

    mutex = OpenMutex(MUTANT_ALL_ACCESS, false, L"Game");

    if (mutex == nullptr)
    {
        CreateMutex(NULL, true, L"Game");
    }
    else
    {
        MessageBox(NULL, L"The client is already running.", L"Game", MB_OK);
        return 0;
    }

    // 로직 스레드 시작
    WINDOW->SetThread(CreateThread(NULL, 0, WINDOW->LogicThread, NULL, 0, NULL));

    // 기본 메시지 루프입니다:
    while (TRUE)
    {
        // 윈도우 메시지가 있을 경우 TRUE, 없을 경우 FALSE
        if (PeekMessage(&msg, nullptr, 0, 0, PM_REMOVE))
        {
            if (WM_QUIT == msg.message)
            {
                break;
            }

            TranslateMessage(&msg);
            DispatchMessage(&msg);
        }
        else // Dead Time
        {
            WINDOW->InputUpdate();
        }
    }

    CloseHandle(mutex);

#ifdef _DEBUG
    _CrtDumpMemoryLeaks();
#endif // _DEBUG

    GdiplusShutdown(gdiplus_token);

    return (int)msg.wParam;
}
