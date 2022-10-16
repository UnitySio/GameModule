#pragma once

#include "resource.h"
#include "framework.h"

using namespace std;

#define MAX_LOADSTRING 100

class Core
{
private:
	HINSTANCE hInst; // 현재 인스턴스
	HWND hWnd;
	HDC hdc;
	HDC memDC;
	HBITMAP new_bitmap_;
	RECT buffer_;

	POINT resolution_;

	static LRESULT CALLBACK StaticWndProc(HWND, UINT, WPARAM, LPARAM);
	LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);

	// 싱글톤
	static shared_ptr<Core> instance_;
	static once_flag flag_;

	void Update(float delta_time);
	void LateUpdate(float delta_time);
	void Render();

	float run_timer_;
public:
	Core() = default;
	~Core() = default;

	Core(const Core&) = delete;
	Core& operator=(const Core&) = delete;

	WCHAR szTitle[MAX_LOADSTRING]; // 제목 표시줄 텍스트입니다.
	WCHAR szWindowClass[MAX_LOADSTRING]; // 기본 창 클래스 이름입니다.

	ATOM MyRegisterClass(HINSTANCE hinstance);
	BOOL InitInstance(HINSTANCE, int);

	static std::shared_ptr<Core> GetInstance();

	void Logic();

	HDC GetHDC();
};
