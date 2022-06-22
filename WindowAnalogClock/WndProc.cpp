#include "pch.h"
#include "WndProc.h"

#define CLOCK1 0

extern HINSTANCE hInst;
HBITMAP hImageBM;

HDC hScreenDC;
HDC hMemoryDC;
HBITMAP hBM;
HDC hImageDC;
int Hour, Min, Second;

int HourNeedle = 70;
int MinNeedle = 100;
int SecondNeedle = 100;

int OnCreate(HWND hWnd, WPARAM wParam, LPARAM lParam) {

	hScreenDC = GetDC(hWnd);

	hMemoryDC = CreateCompatibleDC(hScreenDC);
	//cx cy �̹��� ũ��
	hBM = CreateCompatibleBitmap(hScreenDC, 300, 300);
	SelectObject(hMemoryDC, hBM);

	hImageDC = CreateCompatibleDC(hScreenDC);
	//��Ʈ�� �о����
	hImageBM = (HBITMAP)LoadImage(hInst, L"ClockFace.bmp", IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);
	SelectObject(hImageDC, hImageBM);

	SetTimer(hWnd, CLOCK1, 1000, NULL);

	SendMessage(hWnd, WM_TIMER, 0, 0);
	return 0;
}

int OnTimer(HWND hWnd, WPARAM wParam, LPARAM lParam) {

	SYSTEMTIME st;

	GetLocalTime(&st);

	Hour = st.wHour;
	Min = st.wMinute;
	Second = st.wSecond;

	POINT ptNeedle = { 0,0 };
	float theta = 0.0f;
	TCHAR strClock[128] = L"";
	wsprintf(strClock, L"%2d : %02d : % 02d", Hour, Min, Second);
	SetWindowText(hWnd, L"�����ٶ�");

	//�̹����� ȭ�鿡 ������ִ� �Լ�
	//��Ʈ�������� �о�;� ������
	BitBlt(hMemoryDC, 0, 0, 300, 300, hImageDC, 0, 0, SRCCOPY);
	{
		theta = PI / 180.0f * ((Hour - 4.5f) * 30);
		ptNeedle.x = (cos(theta) * HourNeedle) - (sin(theta) * HourNeedle);
		ptNeedle.y = (cos(theta) * HourNeedle) + (sin(theta) * HourNeedle);
		MoveToEx(hMemoryDC, 150, 150, NULL);
		LineTo(hMemoryDC, 150 + ptNeedle.x, 150 + ptNeedle.y);
	}
	{
		theta = PI / 180.0f * ((Min - 22.5f) * 6);
		ptNeedle.x = (cos(theta) * MinNeedle) - (sin(theta) * MinNeedle);
		ptNeedle.y = (cos(theta) * MinNeedle) + (sin(theta) * MinNeedle);
		MoveToEx(hMemoryDC, 150, 150, NULL);
		LineTo(hMemoryDC, 150 + ptNeedle.x, 150 + ptNeedle.y);
	}
	{
		theta = PI / 180.0f * ((Second - 22.5f) * 6);
		ptNeedle.x = cos(theta) * SecondNeedle - sin(theta) * SecondNeedle;
		ptNeedle.y = cos(theta) * SecondNeedle + sin(theta) * SecondNeedle;
		MoveToEx(hMemoryDC, 150, 150, NULL);
		LineTo(hMemoryDC, 150 + ptNeedle.x, 150 + ptNeedle.y);
	}
	BitBlt(hScreenDC, 0, 0, 300, 300, hMemoryDC, 0, 0, SRCCOPY);

	return 0;
}

int OnPaint(HWND hWnd, WPARAM wParam, LPARAM lParam) {

	PAINTSTRUCT ps;

	ReleaseDC(hWnd, hMemoryDC);
	ReleaseDC(hWnd, hImageDC);
	DeleteObject(hBM);
	EndPaint(hWnd, &ps);

	return 0;
}

int OnCommand(HWND hWnd, WPARAM wParam, LPARAM lParam) {

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
		return DefWindowProc(hWnd, WM_COMMAND, wParam, lParam);
	}

	return 0;
}

int OnDestroy(HWND hWnd, WPARAM wParam, LPARAM lParam) {

	KillTimer(hWnd, CLOCK1);

	//ReleaseDC()�� �޸𸮿� �Ҵ�� ȭ�� DC�� �����ϱ� ���� �뵵�� ����
	ReleaseDC(hWnd, hImageDC);
	DeleteObject(hImageBM);

	ReleaseDC(hWnd, hMemoryDC);
	DeleteObject(hBM);

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
	case WM_CREATE:
	{
		OnCreate(hWnd, wParam, lParam);
		return 0;
	}
	case WM_TIMER: {
		OnTimer(hWnd, wParam, lParam);
		return 0;
	}
	case WM_COMMAND:
	{
		OnCommand(hWnd, wParam, lParam);
		return 0;
	}
	break;
	/*case WM_PAINT:
	{
		OnPaint(hWnd, wParam, lParam);
		return 0;
	}*/
	break;
	case WM_DESTROY:
		OnDestroy(hWnd, wParam, lParam);
		return 0;
	default:
		return DefWindowProc(hWnd, message, wParam, lParam);
	}
	return 0;
}
