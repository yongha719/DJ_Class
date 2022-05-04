#include "pch.h"
#include "WndProc.h"
#include "Number.h"

#define Time01 1001
#define _1_SEC_ 1000
TCHAR g_strTime[128] = L"";

int OnPaint(HWND hWnd, WPARAM wParam, LPARAM lParam);
int OnCreate(HWND hWnd, WPARAM wParam, LPARAM lParam) {
	SetTimer(hWnd, 0, 1000, NULL);
	SendMessage(hWnd, WM_TIMER, Time01, 0);
	return 0;
}

int OnTimer(HWND hWnd, WPARAM wParam, LPARAM lParam) {
	SYSTEMTIME st;
	GetLocalTime(&st);
	wsprintf(g_strTime, L"%d시 %d분 %d초", st.wHour, st.wMinute, st.wSecond);

	InvalidateRect(hWnd, NULL, true);
	return 0;
}
int OnPaint(HWND hWnd, WPARAM wParam, LPARAM lParam)
{
	PAINTSTRUCT ps;
	HDC hdc = BeginPaint(hWnd, &ps);
	// TODO: 여기에 hdc를 사용하는 그리기 코드를 추가합니다...
	HFONT hFont = CreateFont()
	TextOut(hdc, 100, 100, g_strTime, wcslen(g_strTime));
	DrawNumber(hdc, 20,0,0,9212);

	NumOutput(hdc, 0, 0, 9, 20);
	EndPaint(hWnd, &ps);
	return 0;
}

int OnDestroy(HWND hWnd, WPARAM wParam, LPARAM lParam)
{
	KillTimer(hWnd, Time01);
	PostQuitMessage(0);
	return 0;
}

//
//  함수: WndProc(HWND, UINT, WPARAM, LPARAM)
//
//  용도: 주 창의 메시지를 처리합니다.
//
//  WM_COMMAND  - 애플리케이션 메뉴를 처리합니다.
//  WM_PAINT    - 주 창을 그립니다.
//  WM_DESTROY  - 종료 메시지를 게시하고 반환합니다.
//
//
LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	switch (message)
	{
	case WM_CREATE: return OnCreate(hWnd, wParam, lParam);
	case WM_TIMER: return OnTimer(hWnd, wParam, lParam);
	case WM_PAINT:  return OnPaint(hWnd, wParam, lParam);
	case WM_DESTROY:return OnDestroy(hWnd, wParam, lParam);
	default:        return DefWindowProc(hWnd, message, wParam, lParam);
	}
	return 0;
}
