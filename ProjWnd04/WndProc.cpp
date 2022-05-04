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
	wsprintf(g_strTime, L"%d�� %d�� %d��", st.wHour, st.wMinute, st.wSecond);

	InvalidateRect(hWnd, NULL, true);
	return 0;
}
int OnPaint(HWND hWnd, WPARAM wParam, LPARAM lParam)
{
	PAINTSTRUCT ps;
	HDC hdc = BeginPaint(hWnd, &ps);
	// TODO: ���⿡ hdc�� ����ϴ� �׸��� �ڵ带 �߰��մϴ�...
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
//  �Լ�: WndProc(HWND, UINT, WPARAM, LPARAM)
//
//  �뵵: �� â�� �޽����� ó���մϴ�.
//
//  WM_COMMAND  - ���ø����̼� �޴��� ó���մϴ�.
//  WM_PAINT    - �� â�� �׸��ϴ�.
//  WM_DESTROY  - ���� �޽����� �Խ��ϰ� ��ȯ�մϴ�.
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
