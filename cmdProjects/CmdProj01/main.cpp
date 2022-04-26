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
using namespace std;


char g_strtNum[10][5][7] =
{
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

void gotoxy(int x, int y) {
	COORD CursorPosition = { x,y };
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), CursorPosition);
}

void OutPutNum(int num) {
	if (num > 9) { cout << "한자리만\n"; return; }
	for (int i = 0; i < 5; i++) {
		gotoxy(5, i + 2);
		printf("%s\n", g_strtNum[num][i]);
	}
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

	int seedNum = pow(10, nSize);
	int i;
	int* num = (int*)malloc(nSize * sizeof(int));

	for (i = 0; i < nSize; i++) {
		num[i] = number / seedNum;
		number %= seedNum;
		seedNum /= 10;

		OutPutNum(x += 7, y, num[i]);
	}
}

void main(int argc, char** argv) {
	DrawNum(0, 0, 123456789);


}