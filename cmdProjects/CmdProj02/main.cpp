/*
Program Title : OutPut Numbers
Author : yongha

email : sdh210210@sdh.hs.kr
Date : 2022 - 04 - 26
Updata : 2022 - 04 - 26
*/
#define _CRT_SECURE_NO_WARNINGS
#include <bits/stdc++.h>	
#include <Windows.h>
#include <conio.h>
using namespace std;

#define BLACK 0
#define DARK_BLUE 1
#define DARK_GREEN 2
#define DARK_SKY_BLUE 3
#define DARK_RED 4
#define DARK_VOILET 5
#define DARK_YELLOW 6
#define GRAY 7
#define DARK_GRAY 8
#define BLUE 9
#define GREEN 10
#define SKY_BLUE 11
#define RED 12
#define VOILET 13
#define YELLOW 14
#define WHITE 15

#define HIDDEN 0
#define SHOW 1

char g_strtNum[10][5][7] = {
	{
	"■■■",
	"■  ■",
	"■  ■",
	"■  ■",
	"■■■"
	},
	{
	"■■  ",
	"  ■  ",
	"  ■  ",
	"  ■  ",
	"■■■"
	},
	{
	"■■■",
	"    ■",
	"■■■",
	"■  ",
	"■■■"
	},
	{
	"■■■",
	"    ■",
	"■■■",
	"    ■",
	"■■■"
	},
	{
	"■    ",
	"■  ■",
	"■■■",
	"    ■",
	"    ■"
	},
	{
	"■■■",
	"■  ",
	"■■■",
	"    ■",
	"■■■"
	},{
	"■■■",
	"■    ",
	"■■■",
	"■  ■",
	"■■■"
	},
	{
	"■■■",
	"    ■",
	"    ■",
	"    ■",
	"    ■"
	},
	{
	"■■■",
	"■  ■",
	"■■■",
	"■  ■",
	"■■■"
	},
	{
	"■■■",
	"■  ■",
	"■■■",
	"    ■",
	"■■■"
	}
};

char strTime[2][5][7] = {
	{
		"      ",
		"  ■  ",
		"      ",
		"  ■  ",
		"      ",
	},
	{
	"      ",
	"      ",
	"      ",
	"      ",
	"      ",
	}
};

void gotoxy(int x, int y) {
	COORD CursorPosition = { x,y };
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), CursorPosition);
}

void SetColor(int color) {
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), color);
}

void CursorView(char show) {
	HANDLE hConsole;
	CONSOLE_CURSOR_INFO ConsoleCursor;

	hConsole = GetStdHandle(STD_OUTPUT_HANDLE);

	ConsoleCursor.bVisible = show;
	ConsoleCursor.dwSize = 1;

	SetConsoleCursorInfo(hConsole, &ConsoleCursor);
}

void PressAnyKey() {
	printf("\nPress a Key!!!");
	_getch();
}

void OutPutNum(int x, int y, int num) {
	if (num > 9) { cout << "한자리만\n"; return; }
	for (int i = 0; i < 5; i++) {
		gotoxy(x, y + i);
		printf("%s\n", g_strtNum[num][i]);
	}
}

void DrawNum(int x, int y, int number) {
	if (number > 1000000000) return;

	char strBuff[128];
	int nSize;
	sprintf(strBuff, "%d", number);//여기서 strbuff를 number로 바꿈?
	nSize = strlen(strBuff); //number의 길이랑 똑같음

	int seedNum = pow(10, nSize-1);
	int* num = (int*)malloc(nSize * sizeof(int));

	for (int i = 0; i < nSize; i++) {
		num[i] = number / seedNum;
		number %= seedNum;
		seedNum /= 10;

		OutPutNum(x += 7, y, num[i]);
	}
}

void DrawColon(int x, int y, bool blsActive) {
	for (int i = 0; i < 5; i++) {
		gotoxy(x, y + i);
		if (blsActive) cout << strTime[0][i];
		else cout << strTime[1][i];
	}
}
int main() {
	DrawNum(0, 0, 123456789);
	SYSTEMTIME st;
	bool blsQuit = false;
	int nKey = -1;

	system("mode con: lines=6 cols=80");
	ShowCursor(HIDDEN);
	while (!blsQuit)
	{
		if (_kbhit()) {
			nKey = _getch();
			switch (nKey)
			{
			case 27:
				blsQuit = !blsQuit;
				break;
			}
		}

		static bool blsBlink = true;

		system("cls");

		GetLocalTime(&st);
		SetColor(RED);
		DrawNum(0, 0, st.wHour);
		SetColor(WHITE);
		//DrawColon(13, 0, blsBlink);
		SetColor(GREEN);
		DrawNum(20, 0, st.wMinute);
		SetColor(WHITE);
		//(30, 0, blsBlink);
		SetColor(YELLOW);
		DrawNum(40, 0, st.wSecond);

		blsBlink = !blsBlink;
		Sleep(500);

	}
	ShowCursor(SHOW);
	PressAnyKey();
	return 0;
}