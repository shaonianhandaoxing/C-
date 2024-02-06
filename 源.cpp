#include<stdio.h>//标准输入输出
#include<conio.h>//控制台
#include <math.h>//数学函数头文件
#include<time.h>//日期和时间头文件
#include<graphics.h>//图形库
#include<mmsystem.h>//头文件库
#pragma comment(lib,"Winmm.lib")//音乐库文件


struct jet
{
	int x, y;//喷射点坐标
	int hx, hy;//极致
	int height;//烟花高度
	bool isshoot;//发射情况
	unsigned long t1, t2, dt;//时间控制速度
	IMAGE img;//存储照片
}jet;

struct fire
{
	int r;//半径
	int maxr;//最大半径
	int cx, cy;//中心点坐标局部
	int x, y;//中心点坐标全局
	int xy[240][240];//保存图片每一个像素点
	bool isboom;//是否开始爆炸
	bool isdraw;//是否显示
	unsigned long t1, t2, dt;//爆炸的速度
}fire;


int main()
{
	initgraph(1200, 800);


	mciSendString("open 化作烟火陪你坠落.mp3", 0, 0, 0);
	mciSendString("play 化作烟火陪你坠落.mp3", 0, 0, 0);


	settextcolor(BLUE);
	settextstyle(25, 0, "宋体");
	outtextxy(400, 200, "jianzhile");
	outtextxy(666, 666, "来自于xxx");
	getchar();//按回车进入下一个环节

	//初始化 问题1，不能超出窗口；问题2，取随机数；
	jet.x = rand() % (960 - 20);//最大到960-20
	jet.y = 750 - 50;//
	jet.hx = jet.x;//定义最大到960-25
	jet.hy = rand() % 400;//爆炸最低点不少于320
	jet.dt = 10;
	jet.t1 = GetTickCount();
	jet.isshoot = true;

	loadimage(&jet.img, "shoot.jpg", 20, 50);
	putimage(jet.x, jet.y, &jet.img, SRCINVERT);

	fire.r = 0;
	fire.maxr = 120;
	fire.cx = 120, fire.cy = 120;
	fire.xy[240][240];
	fire.isboom = false;
	fire.isdraw = false;
	fire.dt = 5;//爆炸的速度

	fire.xy[240][240];
	IMAGE fimg;
	loadimage(&fimg, "E:/aaa文档/咕噜咕噜/咕噜咕噜/fire.jpg", 240, 240);
	SetWorkingImage(&fimg);
	for (int a = 0; a < 240; a++)
		for (int b = 0; b < 240; b++)
			fire.xy[a][b] = getpixel(a, b);
	SetWorkingImage();

	while (1)
	{
		jet.t2 = GetTickCount();
		if (jet.t2 - jet.t1 > jet.dt && jet.isshoot == true)
		{
			putimage(jet.x, jet.y, &jet.img, SRCINVERT);

			if (jet.y > jet.hy)
				jet.y -= 5;//不超过最高点
			putimage(jet.x, jet.y, &jet.img, SRCINVERT);

			if (jet.y <= jet.hy)
			{
				//到达最高点之后1.重置烟花，2.擦除烟花
				putimage(jet.x, jet.y, &jet.img, SRCINVERT);
				jet.isshoot = false;
			}

			if (jet.isshoot == false)//烟花爆炸完毕重置
			{
				jet.x = rand() % (1200 - 20);//最大到960-20
				jet.y = 750;//
				jet.hx = jet.x;//定义最大到960-25
				jet.hy = rand() % 400;//爆炸最低点不少于320
				jet.dt = 10;
				jet.t1 = GetTickCount();
				jet.isshoot = true;
				loadimage(&jet.img, "shoot.jpg", 20, 50);
				putimage(jet.x, jet.y, &jet.img, SRCINVERT);
			}

			jet.t1 = jet.t2;//更新发射时间到最新节点
		}

		int drt[12] = { 5,5,5,6,6,15,25,25,25,55,55,65 };//创建烟花缓速效果
		fire.t2 = GetTickCount();
		if (fire.t2 - fire.t1 > fire.dt && fire.isboom == true)
		{
			if (fire.r < fire.maxr)
			{
				fire.r++;
				fire.dt = drt[fire.r / 10];
				fire.isdraw = true;


				if (fire.r >= fire.maxr - 1)
				{
					fire.isdraw = false;
					fire.isboom = false;
					fire.dt = 5;
					fire.t1 = GetTickCount();
					fire.r = 0;
				}
				fire.t1 = fire.t2;
			};

			if (fire.isdraw == true)
			{
				for (int i = 0; i < 628; i++)
				{
					double a = i * 0.01;
					int x1 = static_cast<int>(fire.cx + fire.r * cos(a));
					int y1 = static_cast<int>(fire.cy - fire.r * sin(a));
					//x1 y1 628个来自于图片的像素点坐标
					if (x1 >= 0 && x1 < 240 && y1 >= 0 && y1 < 240)
					{
						// 根据存储的图像颜色设置像素颜色
						putpixel(fire.x + x1, fire.y + y1, fire.xy[x1][y1]);
					}

				}
			}
		}
		Sleep(5);
	}
	return 0;
}