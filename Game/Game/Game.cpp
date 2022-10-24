

#include "pch.h"
#include "Game.h"

using namespace Gdiplus;

int APIENTRY wWinMain(_In_ HINSTANCE hInstance,
	_In_opt_ HINSTANCE hPrevInstance,
	_In_ LPWSTR    lpCmdLine,
	_In_ int       nCmdShow)
{
	UNREFERENCED_PARAMETER(hPrevInstance);
	UNREFERENCED_PARAMETER(lpCmdLine);

	// TODO: 여기에 코드를 입력합니다.

	GdiplusStartupInput gdiplus_startup_input;
	ULONG_PTR gdiplus_token;

	GdiplusStartup(&gdiplus_token, &gdiplus_startup_input, NULL);

	// 전역 문자열을 초기화합니다.
	LoadStringW(hInstance, IDS_APP_TITLE, Window::GetInstance()->szTitle, MAX_LOADSTRING);
	LoadStringW(hInstance, IDC_GAME, Window::GetInstance()->szWindowClass, MAX_LOADSTRING);
	Window::GetInstance()->MyRegisterClass(hInstance);

	// 애플리케이션 초기화를 수행합니다:
	if (!Window::GetInstance()->InitInstance(hInstance, nCmdShow))
	{
		return FALSE;
	}

	HACCEL hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_GAME));

	MSG msg;

#ifdef _DEBUG
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
#endif // _DEBUG

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
			Window::GetInstance()->Logic();
		}
	}

#ifdef _DEBUG
	_CrtDumpMemoryLeaks();
#endif // _DEBUG


	GdiplusShutdown(gdiplus_token);

	return (int)msg.wParam;
}
