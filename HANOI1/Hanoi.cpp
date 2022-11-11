#define _CRT_SECURE_NO_WARNINGS 1

#include"Head.h"
#include"Struct.h"

int Window_Width = 1920;
int Window_Height = 1080;

size_t LayerNumber = 3;
size_t GrowpNumber = 3;
size_t MoveNumber = 0;
size_t Level = 0;

Growp* OpenHanoi()
{
	Growp* ret = NULL;

	//init set
	{
		setbkcolor(RGB(255, 249, 212));
		settextstyle(100, 0, "汉仪跳跳体简");
		settextcolor(0x1CCC4B);
		setbkmode(TRANSPARENT);
		setlinestyle(PS_NULL);
		cleardevice();
	}

	if (!(ret = ReadGame(&GrowpNumber, &LayerNumber, &MoveNumber)))
	{
		ret = NewGame(LayerNumber, GrowpNumber);
		InitGame(ret);
	}
	Level = LayerNumber - 3;
	return ret;
}

void SetHW(int* W,int* H)
{
	FILE* pWHmode = NULL;
	FILE* pTmp = fopen("mode.txt", "r");
	if (!pTmp)
	{
		pTmp = fopen("mode.txt", "w");
		assert(pTmp);
		pWHmode = pTmp;
		printf("请输入当前屏幕高宽\n");
		printf("宽：");
		scanf("%d", W);
		printf("高：");
		scanf("%d", H);
		fprintf(pWHmode, "宽:%d高:%d", *W, *H);

		printf("\n谢谢!\n");
		printf("如需修改请到%s目录下找到mode.txt更改\n", __FILE__);
		system("pause");

		fclose(pWHmode);
		pWHmode = NULL;
		pTmp = NULL;
	}
	else
	{
		pWHmode = pTmp;
		fscanf(pWHmode, "宽:%d高:%d", W, H);
		fclose(pWHmode);
		pWHmode = NULL;
		pTmp = NULL;
	}
}

int Hanoi()
{

	SetHW(&Window_Width, &Window_Height);
	printf("\n--EManSiS--arrorn--20221102--0.1.01\n");
	initgraph(Window_Width, Window_Height);
	Growp* game = OpenHanoi();
	SaveGame(game, GrowpNumber, MoveNumber);
	DP diss{ 0 };
	diss.W_Width = Window_Width;
	diss.W_Height = Window_Height;
	diss.sourse = game;
	diss.GrowpNumber = GrowpNumber;
	diss.LayerNumber = LayerNumber;
	diss.MoveNumber = &MoveNumber;
	diss.Level = Level;

	Choice choice{ 0 };

	MoveNumber = NULL;

	BeginBatchDraw();

	while (true)
	{
		//AI
		{
			bool bb = false;
			diss.Menu = true;
			LayerNumber = 5;
			while (true)
			{
				if (diss.OpenBegin)
				{
					diss.Level = Level + 1;
				}
				diss.LayerNumber = LayerNumber;
				CloseGame(&diss);
				if (AI_GAME(&diss))
				{
					break;
				}
				DWORD t1, t2;
				t1 = t2 = GetTickCount();
				while (true)
				{
					t2 = GetTickCount();

					DissPlay(&diss);

					if (t2 - t1 > 2000)
					{
						break;
					}
					if (IfReturn())
					{
						bb = true;
						break;
					}
				}
				if (bb)
				{
					bb = false;
					break;
				}

				LayerNumber++;
			}
			game = OpenHanoi();
			diss.sourse = game;
			diss.GrowpNumber = GrowpNumber;
			diss.LayerNumber = LayerNumber;
			diss.Level = Level;
			diss.Menu = false;
			diss.win = false;
			if (IsWin(game, 2))
			{
				CloseGame(&diss);
				LayerNumber++;
				diss.LayerNumber = LayerNumber;
				game = NewGame(LayerNumber, GrowpNumber);
				InitGame(game);
				diss.sourse = game;
				diss.GrowpNumber = GrowpNumber;
				diss.LayerNumber = LayerNumber;
				diss.Level = Level;
				SaveGame(game, GrowpNumber, MoveNumber);
			}
			DissPlay(&diss);
		}

		MOUSEMSG msg = GetMouseMsg();

		bool sAndd = false;
		bool MouseOnce = false;

		int MouseXY = NULL;
		int n = 0;
		diss.win = false;

		diss.OpenBegin = true;
		while (true)
		{
			//输入消息
			{
				if (MouseHit())
				{
					msg = GetMouseMsg();
				}
			}

			//消息处理
			{
				//鼠标所在区域
				for (n = 1; n <= 3; n++)
				{
					if (msg.x > (n - 1) * Window_Width / 3 && msg.x <= Window_Width * n / 3)
					{
						if (msg.y >= Window_Height - Window_Height / 9)
						{
							diss.MouxeXY = false;
							MouseXY = NULL;
							break;
						}
						MouseXY = n;
						diss.MouxeXY = n;
					}
				}

				//鼠标点击选择
				if (msg.uMsg == WM_LBUTTONUP)
				{
					if (!MouseOnce)
					{
						MouseOnce = true;
						if (!choice.state)
						{
							if (GoToGrowp(game, MouseXY - 1)->Arr->Number)
							{
								diss.choice_sourse = MouseXY;
								choice.destination = NULL;
								choice.sourse = MouseXY;
								choice.state = true;
							}
						}
						else if (choice.state && choice.sourse && MouseXY)
						{
							choice.destination = MouseXY;
							//移动
							sAndd = true;
							choice.state = false;
						}
					}
				}
				else
				{
					MouseOnce = false;
				}

				//移动及胜利判定
				if (sAndd)
				{
					sAndd = false;
					MoveLayer(game,choice.sourse-1, choice.destination-1, &MoveNumber);
					diss.choice_destination = diss.choice_sourse = NULL;
					choice.sourse = choice.destination = NULL;
					SaveGame(game, GrowpNumber, MoveNumber);
					if (IsWin(game, 2))
					{
						diss.win = true;
						while (!IfReturn())
							DissPlay(&diss);
						CloseGame(&diss);
						LayerNumber++;
						diss.LayerNumber = LayerNumber;
						game = NewGame(LayerNumber, GrowpNumber);
						InitGame(game);
						diss.sourse = game;
						diss.GrowpNumber = GrowpNumber;
						diss.LayerNumber = LayerNumber;
						diss.Level = Level;
						MoveNumber = NULL;
						*(diss.MoveNumber) = NULL;
						SaveGame(game, GrowpNumber, MoveNumber);
						break;
					}
				}
			}

			//输出消息
			printf("1 ");
			DissPlay(&diss);
		}
	}

	EndBatchDraw();
	return 0;
}