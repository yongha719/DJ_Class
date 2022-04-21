#include "WndProc.h"

int OnPaint(HWND hWnd, WPARAM wParam, LPARAM lParam) {

	PAINTSTRUCT ps;
	HDC hdc = BeginPaint(hWnd, &ps);
	// TODO: ���⿡ hdc�� ����ϴ� �׸��� �ڵ带 �߰��մϴ�...
	EndPaint(hWnd, &ps);
	return 0;
}

int OnDestroy(HWND hWnd, WPARAM wParam, LPARAM lParam) {

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
	case WM_PAINT:		return OnPaint(hWnd, wParam, lParam);
	case WM_DESTROY:    return OnDestroy(hWnd, wParam, lParam);
	default:			return DefWindowProc(hWnd, message, wParam, lParam);
	}
	return 0;
}
