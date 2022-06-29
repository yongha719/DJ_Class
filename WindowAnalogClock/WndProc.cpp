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

/// <summary>
/// 창 만들것을 요청할때 전송됨
/// </summary>
int OnCreate(HWND hWnd, WPARAM wParam, LPARAM lParam) {

	hScreenDC = GetDC(hWnd);

	hMemoryDC = CreateCompatibleDC(hScreenDC);
	//cx cy 이미지 크기
	hBM = CreateCompatibleBitmap(hScreenDC, 300, 300);
	SelectObject(hMemoryDC, hBM);

	hImageDC = CreateCompatibleDC(hScreenDC);
	//비트맵 읽어오기
	hImageBM = (HBITMAP)LoadImage(hInst, L"ClockFace.bmp", IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);
	SelectObject(hImageDC, hImageBM);

	SetTimer(hWnd, CLOCK1, 1000, NULL);

	SendMessage(hWnd, WM_TIMER, 0, 0);
	return 0;
}

/// <summary>
/// 시곗바늘 그려주는 함수
/// </summary>
int SetNeedles() {
	POINT ptNeedle = { 0,0 };
	float theta = 0.0f;

	//시침 바늘 그려주는 부분
	theta = PI / 180.0f * ((Hour - 4.5f) * 30);
	ptNeedle.x = (cos(theta) * HourNeedle) - (sin(theta) * HourNeedle);
	ptNeedle.y = (cos(theta) * HourNeedle) + (sin(theta) * HourNeedle);
	MoveToEx(hMemoryDC, 150, 150, NULL);
	LineTo(hMemoryDC, 150 + ptNeedle.x, 150 + ptNeedle.y);

	//분침
	theta = PI / 180.0f * ((Min - 22.5f) * 6);
	ptNeedle.x = (cos(theta) * MinNeedle) - (sin(theta) * MinNeedle);
	ptNeedle.y = (cos(theta) * MinNeedle) + (sin(theta) * MinNeedle);
	MoveToEx(hMemoryDC, 150, 150, NULL);
	LineTo(hMemoryDC, 150 + ptNeedle.x, 150 + ptNeedle.y);

	//초침
	theta = PI / 180.0f * ((Second - 22.5f) * 6);
	ptNeedle.x = cos(theta) * SecondNeedle - sin(theta) * SecondNeedle;
	ptNeedle.y = cos(theta) * SecondNeedle + sin(theta) * SecondNeedle;
	MoveToEx(hMemoryDC, 150, 150, NULL);
	LineTo(hMemoryDC, 150 + ptNeedle.x, 150 + ptNeedle.y);

	return 0;
}


/// <summary>
/// 화면 출력 관련 함수
/// 이미지 출력, 콘솔 이름 등등
/// </summary>
int OnTimer(HWND hWnd, WPARAM wParam, LPARAM lParam) {

	SYSTEMTIME st;

	GetLocalTime(&st);

	Hour = st.wHour;
	Min = st.wMinute;
	Second = st.wSecond;

	POINT ptNeedle = { 0,0 };
	float theta = 0.0f;
	TCHAR strClock[128] = L"";

	SetWindowText(hWnd, L"윈도우 아날로그 시계 수행평가");

	//텍스트 출력
	TCHAR Time[10] = L"";

	//wsprintf 첫번째 인자에 두번째인자에 들어간 문자열이 담김
	if (Hour < 12) wsprintf(Time, L"아침");
	else wsprintf(Time, L"저녁");
	wsprintf(strClock, L"지금은 %s %2d : %02d : %02d입니다", Time, Hour % 12, Min, Second);
	TextOut(hScreenDC, 50, 400, strClock, 22);

	//이미지를 화면에 출력해주는 함수
	//비트맵파일을 읽어와야 가능함
	BitBlt(hMemoryDC, 0, 0, 300, 300, hImageDC, 0, 0, SRCCOPY);
	SetNeedles();

	BitBlt(hScreenDC, 0, 0, 300, 300, hMemoryDC, 0, 0, SRCCOPY);


	return 0;
}

/// <summary>
/// 화면을 그리는 함수 여기선 OnPaint에서 함
/// </summary>
int OnPaint(HWND hWnd, WPARAM wParam, LPARAM lParam) {

	PAINTSTRUCT ps;

	ReleaseDC(hWnd, hMemoryDC);
	ReleaseDC(hWnd, hImageDC);
	DeleteObject(hBM);
	EndPaint(hWnd, &ps);

	return 0;
}

/// <summary>
/// 메뉴 선택 구문 분석하는 함수?
/// </summary>
int OnCommand(HWND hWnd, WPARAM wParam, LPARAM lParam) {

	int wmId = LOWORD(wParam);

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

/// <summary>
/// 창 제거될때 요청 전송
/// 종료시에 해줘야 할 일을 모아둠
/// Ex) 메모리 할당 해제등등
/// </summary>
int OnDestroy(HWND hWnd, WPARAM wParam, LPARAM lParam) {

	KillTimer(hWnd, CLOCK1);

	//ReleaseDC()는 메모리에 할당된 화면 DC를 해제하기 위한 용도로 사용됨
	ReleaseDC(hWnd, hImageDC);
	DeleteObject(hImageBM);

	ReleaseDC(hWnd, hMemoryDC);
	DeleteObject(hBM);

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
