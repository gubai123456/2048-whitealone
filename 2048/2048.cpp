#define _CRT_SECURE_NO_WARNINGS //去掉编译器内扩增的问题 
#include<stdio.h>
#include<stdlib.h>
#include<graphics.h>
#include<conio.h>
#include<time.h>
#define _CRT_SECURE_NO_WARNINGS //去掉编译器内扩增的问题 

IMAGE img[12];//存12张照片

//图片的的名字的序号
int imgIndex[12] = { 0,2,4,8,16,32,64,128,256,512,1024,2048 };
int i, j,k;
int space = 16;
int map[4][4] = { 0 };
int copy[4][4] = { 0 };
char a;

void produce();

void initmap()
{
	int nx, ny;
	srand((unsigned int)time(NULL));
		nx = rand() % 4;
		ny = rand() % 4;
		map[nx][ny] = rand() & 1 ? 2 : 4;
		space--;
}


void loadResourse()
{
	for (i = 0;i < 12;i++)
	{
		//批量加载	
		char fileName[10] = "";
		sprintf(fileName, "%d.bmp", imgIndex[i]);
		loadimage(img + i, fileName,60,60);
	}
}

void up()
{
	for (i = 0;i < 4;i++)
	{
		for (j = 0;j < 4;j++)
		{
			if (map[i][j] == 0)
				continue;
			else 
				for (k = i + 1;k < 4;k++)
				{
					if (map[k][j] == 0)
						continue;
					else if (map[i][j] == map[k][j])
					{
						map[i][j] *= 2;
						space++;
						map[k][j] = 0;
					}
					else break;
				}
		}
	}

	for (j = 0;j < 4;j++)
	{
		int temp[4] = { 0 };
		int t = 0;
		for (i = 0;i < 4;i++)
		{
			if (map[i][j] != 0)
				temp[t++] = map[i][j];
				map[i][j] = 0;
		}
		t = 0;
		for (i = 0;i < 4;i++)
		{
			map[i][j] = temp[t++];
		}
	}

	for (i = 0;i < 4;i++)
	{
		for (j = 0;j < 4;j++)
		{
			if (copy[i][j] != map[i][j])
			{
				produce();
				return;
			}
		}
	}
}

void down()
{
	for (i = 3;i >= 0;i--)
	{
		for (j = 0;j<4;j++)
		{
			if (map[i][j] == 0)
				continue;
			else
			{
				for (k = i - 1;k >= 0;k--)
				{
					if (map[k][j] == 0)
						continue;
					else if (map[k][j] == map[i][j])
					{
						map[i][j] *= 2;
						space++;
						map[k][j] = 0;
					}
					else break;
				}
			}
		}
	}

	for (j = 0;j < 4;j++)
	{
		int temp[4] = { 0 };
		int t = 0;
		for (i = 3;i >= 0;i--)
		{
			if (map[i][j] != 0)
			{
				temp[t++] = map[i][j];  //不能为-- 数组不能前面为空
				map[i][j] = 0;
			}
		}
		t = 0;
		for (i = 3;i >= 0;i--)
		{
			map[i][j] = temp[t++];
		}
	}
	for (i = 0;i < 4;i++)
	{
		for (j = 0;j < 4;j++)
		{
			if (copy[i][j] != map[i][j])
			{
				produce();
				return;
			}
		}
	}
}

void left()
{
	for (i = 0;i < 4;i++)
	{
		for (j = 0;j < 4;j++)
		{
			if (map[i][j] == 0)
				continue;
			else
			{
				for (k = j + 1;k < 4;k++)
				{
					if (map[i][k] == 0)
						continue;
					else if (map[i][k] == map[i][j])
					{
						map[i][j] *= 2;
						space++;
						map[i][k] = 0;
					}
					else break;
				}
			}
		}
	}

	for (i = 0;i < 4;i++)
	{
		int	temp[4] = { 0 };
		int t = 0;
		for (j = 0;j < 4;j++)
		{
			if (map[i][j] != 0)
			{
				temp[t++] = map[i][j];
				map[i][j] = 0;
			}
		}
		t = 0;
		for (j = 0;j < 4;j++)
		{
			map[i][j] = temp[t++];
		}
	}
	for (i = 0;i < 4;i++)
	{
		for (j = 0;j < 4;j++)
		{
			if (copy[i][j] != map[i][j])
			{
				produce();
				return;
			}
		}
	}
}

void right()
{
	for (i = 0;i < 4;i++)
	{
		for (j = 3;j >=0;j--)
		{
			if (map[i][j] == 0)
				continue;
			else
			{
				for (k = j - 1;k >= 0;k--)
				{
					if (map[i][k] == map[i][j])
					{
						map[i][j] *= 2;
						space++;
						map[i][k] = 0;
					}
					else if (map[i][k] == 0)
						continue;
					else break;
				}
			}
		}
	}

	for (i = 0;i < 4;i++)
	{
		int temp[4] = { 0 };
		int t = 0;
		for (j = 3;j >= 0;j--)
		{
			if (map[i][j] != 0)
				temp[t++] = map[i][j];
		}
		t = 0;
		for(j = 3;j >= 0;j--)
		{
			map[i][j] = temp[t++];
		}
	}
	for (i = 0;i < 4;i++)
	{
		for (j = 0;j < 4;j++)
		{
			if (copy[i][j] != map[i][j])
			{
				produce();
				return;
			}
		}
	}
}

int jud2() {
	for (i = 0; i < 3; i++)
		for (j = 0; j < 4; j++) {
			if (map[i][j] == map[i + 1][j]) {
				return 1;
				break;
			}
		}
	for (i = 0; i < 4; i++)
		for (j = 0; j < 3; j++) {
			if (map[i][j] == map[i][j + 1]) {
				return 1;
				break;
			}
		}
	return 0;
}

void drawMap()
{
	setbkcolor(RGB(245, 215, 215));
	cleardevice(); //显示背景颜色
	settextcolor(WHITE);
	settextstyle(35, 0, "楷体");
	outtextxy(32, 10, "孤白的2048");

	
	int x, y, k;
	for (i = 0;i < 4;i++)
	{
		for (j = 0;j < 4;j++)
		{
			x = 60 * j;
			y = 60 * i + 50;
			for (k = 0;k < 12;k++)
			{
				if (imgIndex[k] == map[i][j])
					break; //获得 x y
			}
			//贴图
			putimage(x, y, img + k);
		}
	}
}

void produce()
{
	int x1, y1;
	srand((unsigned int)time(NULL));
	do {
		x1 = rand() % 4;
		y1 = rand() % 4;
	} while (map[x1][y1] != 0);
	map[x1][y1] = rand() & 1 ? 2 : 4;
	space--;
}

void keyDown()
{
	for (i = 0;i < 4;i++)
	{
		for (j = 0;j < 4;j++)
		{
			copy[i][j] = map[i][j];
		}
	}
	char key = _getch();
	switch (key)
	{
	case 'w':
	case 'W':up();
		break;

	case 'a':
	case'A':left();
		break;

	case 's':
	case'S': down();
		break;

	case 'd':
	case 'D':right();
		break;

	case -32:          //这里不是‘-32’
		 a = _getch();
		 switch (a) {
		 case 72:up();break;
		 case 75:left();break;
		 case 80:down();break;
		 case 77:right();break;
		}
		 break;
		 
		 
		 
		


	}
}



int main()
{	
	loadResourse();
	initgraph(240, 300);

	//程序如何显示图片
	//1.声明图片变量
	IMAGE background;
	//2.加载资源到资源 loadimage
	loadimage(&background, "class.jpg", 240, 300);
	//3.显示图片 putimage 
	putimage(0, 0, &background);
	_getch();

	initmap();
	drawMap();
	int op;
	do
	{
		while (space)
		{
			keyDown();
			drawMap();
		}
		op=jud2();
		if (op == 1)
		{
			keyDown();
			drawMap();
		}
	} while (op);


	_getch();
	closegraph();
	system("pause");//prevent cmd flash
	return 0;
}