#include "WndProc.h"

int OnPaint(HWND hWnd, WPARAM wParam, LPARAM lParam) {

	PAINTSTRUCT ps;
	HDC hdc = BeginPaint(hWnd, &ps);
	// TODO: 여기에 hdc를 사용하는 그리기 코드를 추가합니다...
	EndPaint(hWnd, &ps);
	return 0;
}

int OnDestroy(HWND hWnd, WPARAM wParam, LPARAM lParam) {

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
	case WM_PAINT:		return OnPaint(hWnd, wParam, lParam);
	case WM_DESTROY:    return OnDestroy(hWnd, wParam, lParam);
	default:			return DefWindowProc(hWnd, message, wParam, lParam);
	}
	return 0;
}
