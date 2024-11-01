#include<iostream>
#include<time.h>
#include<math.h>
#include<cmath>
#include<graphics.h>
using namespace std;
int a[3][3] = { 0 };          //全局变量保存棋局信息
int flag = 1;
//int a[3][3] =                      // 画圆为 1 画×为 2
//{
//	1,1,1,
//	0,0,0,
//	2,2,2
//};

void DrawtipText()
{
	static TCHAR str[64];
	_stprintf_s(str, _T("当前棋子类型：%c"), (flag == 1) ? 'O' : 'X');//flag==1 ? 'o' : 'x'
		settextcolor(RED);
		outtextxy(350, 50, str);
}

bool  CheckWin(int c)
{
   //穷举法列出所有获胜情况
	if (a[0][0] == c && a[0][1] == c && a[0][2] == c || a[1][0] == c && a[1][1] == c && a[1][2] == c ||
		a[2][0] == c && a[2][1] == c && a[2][2] == c)
		return true;
	if (a[0][0] == c && a[1][0] == c && a[2][0] == c || a[0][1] == c && a[1][1] == c && a[2][1] == c ||
		a[0][2] == c && a[1][2] == c && a[2][2] == c)
		return true;
	if (a[0][0] == c && a[1][1] == c && a[2][2] == c || a[2][0] == c && a[1][1] == c && a[0][2] == c)
		return true;
	return false;
}

int Getindex_x(int x)
{
	int index_x;
	if (x < 100)return 0;
	if (x >= 700)return 2;
	index_x = (x - 100) / 200;
	return index_x;
}
int Getindex_y(int y)
{
	int index_y;
	if (y < 100)return 0;
	if (y >= 700)return 2;
	index_y = (y - 100) / 200;
	return index_y;
}

bool CheckDraw()
{
	for (int i = 0; i < 3; i++)
	{
		for (int j = 0; j < 3; j++)
		{
			if (a[i][j] == 0)return false;   //棋盘上还有空位说明棋还未下完
		}
	}
	if (!CheckWin(1) && !CheckWin(2))return true;
	return false;

}

void DrawBoard()
{
	line(100, 100, 700, 100);
	line(100, 300, 700, 300);
	line(100, 500, 700, 500);
	line(100, 700, 700, 700);
	line(100, 100, 100, 700);
	line(300, 100, 300, 700);
	line(500, 100, 500, 700);
	line(700, 100, 700, 700);
}

void DrawPiece()      //需要根据数组中的数据绘制旗子
{
	for (int i = 0; i < 3; i++)
	{
		for (int j = 0; j < 3; j++)
		{
			if (a[i][j] == 1)
				circle(100 + j * 200 + 100, 100 + i * 200 + 100, 100);
			if (a[i][j] == 2)
			{
				line(100 + j * 200, 100 + i * 200, 300 + j * 200, 300 + i * 200);
				line(j * 200 + 100, 300 + i * 200, j * 200 + 300, i * 200 + 100);
			}
		}
	}
}



int main()
{
	  DWORD time1 =GetTickCount();                     //判断哪一方下手   画圆为 1 画×为 2
	initgraph(800, 800);
	BeginBatchDraw();
	ExMessage m;
	
	while (flag)
	{
		
		while (peekmessage(&m))   //先有数据输入然后才根据输入的数据绘制棋局
		{
			//没有胜负决出，继续落子
			if (m.message == WM_LBUTTONDOWN)
			{
				int index_x = Getindex_x(m.y);
				int index_y = Getindex_y(m.x);
				if (a[index_x][index_y] == 0)
					a[index_x][index_y] = flag;
				flag = flag > 1 ? 1 : 2;  //状态转换
			}
		}
		cleardevice();
		DrawtipText();
		DrawBoard();
		DrawPiece();
		FlushBatchDraw();


		//  将判断逻辑移到图形绘制的后方，能让任何情况下的图形都被绘制，避免了胜负定时的画面没有被绘制的情况
		if (CheckWin(1))
		{
			
			MessageBox(GetHWnd(), _T("O玩家获胜!"), _T("游戏结束"), MB_OK);
			flag = 0;
		}
		if (CheckWin(2))
		{
			
			MessageBox(GetHWnd(), _T("X玩家获胜!"), _T("游戏结束"), MB_OK);

			flag = 0;
		}
		if (CheckDraw())
		{
			
			MessageBox(GetHWnd(), _T("势均力敌，平局!"), _T("游戏结束"), MB_OK);
			flag = 0;
		}
		DWORD time2 = GetTickCount();
		DWORD delta = time2 - time1;
		if (delta < 1000 / 60)
		{
			Sleep(1000 / 60 - delta);
		}
	}

	EndBatchDraw();
	return 0;
}