// stdafx.cpp : source file that includes just the standard includes
//	myAppleChess.pch will be the pre-compiled header
//	stdafx.obj will contain the pre-compiled type information

#include "stdafx.h"


bool isBlack;//执黑与否
int intChessManual[MAX][MAX];    //当前的棋局
DWORD dwIP;//对方的地址
HWND theHWND;//视图类的句柄
bool myTurn;//轮到与否
char posiX;//对方下的位置
char posiY;//同上
