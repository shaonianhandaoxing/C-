#include<stdio.h>//��׼�������
#include<conio.h>//����̨
#include <math.h>//��ѧ����ͷ�ļ�
#include<time.h>//���ں�ʱ��ͷ�ļ�
#include<graphics.h>//ͼ�ο�
#include<mmsystem.h>//ͷ�ļ���
#pragma comment(lib,"Winmm.lib")//���ֿ��ļ�


struct jet
{
	int x, y;//���������
	int hx, hy;//����
	int height;//�̻��߶�
	bool isshoot;//�������
	unsigned long t1, t2, dt;//ʱ������ٶ�
	IMAGE img;//�洢��Ƭ
}jet;

struct fire
{
	int r;//�뾶
	int maxr;//���뾶
	int cx, cy;//���ĵ�����ֲ�
	int x, y;//���ĵ�����ȫ��
	int xy[240][240];//����ͼƬÿһ�����ص�
	bool isboom;//�Ƿ�ʼ��ը
	bool isdraw;//�Ƿ���ʾ
	unsigned long t1, t2, dt;//��ը���ٶ�
}fire;


int main()
{
	initgraph(1200, 800);


	mciSendString("open �����̻�����׹��.mp3", 0, 0, 0);
	mciSendString("play �����̻�����׹��.mp3", 0, 0, 0);


	settextcolor(BLUE);
	settextstyle(25, 0, "����");
	outtextxy(400, 200, "jianzhile");
	outtextxy(666, 666, "������xxx");
	getchar();//���س�������һ������

	//��ʼ�� ����1�����ܳ������ڣ�����2��ȡ�������
	jet.x = rand() % (960 - 20);//���960-20
	jet.y = 750 - 50;//
	jet.hx = jet.x;//�������960-25
	jet.hy = rand() % 400;//��ը��͵㲻����320
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
	fire.dt = 5;//��ը���ٶ�

	fire.xy[240][240];
	IMAGE fimg;
	loadimage(&fimg, "E:/aaa�ĵ�/���๾��/���๾��/fire.jpg", 240, 240);
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
				jet.y -= 5;//��������ߵ�
			putimage(jet.x, jet.y, &jet.img, SRCINVERT);

			if (jet.y <= jet.hy)
			{
				//������ߵ�֮��1.�����̻���2.�����̻�
				putimage(jet.x, jet.y, &jet.img, SRCINVERT);
				jet.isshoot = false;
			}

			if (jet.isshoot == false)//�̻���ը�������
			{
				jet.x = rand() % (1200 - 20);//���960-20
				jet.y = 750;//
				jet.hx = jet.x;//�������960-25
				jet.hy = rand() % 400;//��ը��͵㲻����320
				jet.dt = 10;
				jet.t1 = GetTickCount();
				jet.isshoot = true;
				loadimage(&jet.img, "shoot.jpg", 20, 50);
				putimage(jet.x, jet.y, &jet.img, SRCINVERT);
			}

			jet.t1 = jet.t2;//���·���ʱ�䵽���½ڵ�
		}

		int drt[12] = { 5,5,5,6,6,15,25,25,25,55,55,65 };//�����̻�����Ч��
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
					//x1 y1 628��������ͼƬ�����ص�����
					if (x1 >= 0 && x1 < 240 && y1 >= 0 && y1 < 240)
					{
						// ���ݴ洢��ͼ����ɫ����������ɫ
						putpixel(fire.x + x1, fire.y + y1, fire.xy[x1][y1]);
					}

				}
			}
		}
		Sleep(5);
	}
	return 0;
}