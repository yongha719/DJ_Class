#include "WndProc.h"

int x, y;
TCHAR strTime[128] = L"";

int OnPaint(HWND hWnd, WPARAM wParam, LPARAM lParam) 
{
	PAINTSTRUCT ps;
	HDC hdc = BeginPaint(hWnd, &ps);
	// TODO: 여기에 hdc를 사용하는 그리기 코드를 추가합니다...
	TextOutW(hdc, x,   y,    L"┌─────────┐", 11);
	TextOutW(hdc, x, y + 16, strTime, 12);
	TextOutW(hdc, x, y + 32, L"└─────────┘", 11);
	EndPaint(hWnd, &ps);
	return 0;
}
int OnDestroy(HWND hWnd, WPARAM wParam, LPARAM lParam)
{
	PostQuitMessage(0);
	return 0;
}
int OnMouseMove(HWND hWnd, WPARAM wParam, LPARAM lParam)
{
	x = LOWORD(lParam);
	y = HIWORD(lParam);

	InvalidateRect(hWnd, NULL, true);

	return 0;
}
int OnTimer(HWND hWnd, WPARAM wParam, LPARAM lParam)
{
	SYSTEMTIME st;
	GetLocalTime(&st);
	wsprintf(strTime, L"│ %02d:%02d:%02d │", st.wHour, st.wMinute, st.wSecond);

	InvalidateRect(hWnd, NULL, true);

	return 0;
}

int OnCreate(HWND hWnd, WPARAM wParam, LPARAM lParam)
{
	SetTimer(hWnd, 0, 1000, NULL);

	return 0;
}

LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	switch (message)
	{
	case WM_CREATE:     return OnCreate(hWnd, wParam, lParam);
	case WM_TIMER:	    return OnTimer(hWnd, wParam, lParam);
	case WM_MOUSEMOVE:  return OnMouseMove(hWnd, wParam, lParam);
	case WM_PAINT:      return OnPaint(hWnd, wParam, lParam);
	case WM_DESTROY:    return OnDestroy(hWnd, wParam, lParam);
	default:            return DefWindowProc(hWnd, message, wParam, lParam);
	}
	return 0;
}
