#define _CRT_SECURE_NO_WARNINGS 1

#include"Head.h"
#include"Struct.h"

void PutMenu(DP* const sourse)
{
	assert(sourse);
	if (sourse->Menu)
	{
		int width = sourse->W_Width / 10 * 8,
			height = sourse->W_Height / 10 * 7;
		int x = (sourse->W_Width - width) / 2,
			y = (sourse->W_Height - height) / 2 - sourse->W_Height / 15;

		int round = (width + height) / 2 / 20;

		char Buffer[1024] = "";

		//背景矩形
		setfillcolor(RGB(254, 220, 186));
		fillroundrect(x, y, x + width, y + height, round, round);

		settextstyle(round * 2, 0, "汉仪跳跳体简");
		settextcolor(RGB(106, 127, 127));
		int textx = x + round, texty = y + round;
		int textw = 0, texth = 0;
		sprintf(Buffer, "Level:%d", sourse->Level + 1);

		outtextxy(textx, texty, Buffer);
		texty += textheight(Buffer);

		settextstyle(round, 0, "汉仪跳跳体简");
		sprintf(Buffer, "将所有矩形移动到最右方柱子上");
		outtextxy(textx, texty, Buffer);
		texty += textheight(Buffer);

		sprintf(Buffer, "数字较大矩形不能在数字较小矩形上方");
		outtextxy(textx, texty, Buffer);
		texty += textheight(Buffer);

		settextstyle(round * 2, 0, "汉仪跳跳体简");
		sprintf(Buffer, "轻点开始游戏<-/ ");
		outtextxy(textx, texty, Buffer);
		texty += textheight(Buffer);
	}
}

void PutWin(DP* const sourse)
{
	assert(sourse);
	if (sourse->win)
	{
		int w = sourse->W_Width / 10 * 8;
		int h = sourse->W_Height / 10 * 7;

		int x = (sourse->W_Width - w) / 2;
		int y = (sourse->W_Height - h) / 2 - sourse->W_Height / 15;

		int round = (w + h) / 2 / 20;

		char Buffer[1024] = "";
		//画矩形
		setfillcolor(RGB(254, 220, 186));
		fillroundrect(x, y, x + w, y + h, round, round);
		//WIN
		sprintf(Buffer, "WIN");
		settextcolor(RGB(106, 127, 127));
		settextstyle(sourse->W_Height / 3, 0, "汉仪跳跳体简");
		x = sourse->W_Width / 2 - textwidth(Buffer) / 2;
		y = sourse->W_Height / 2 - textheight(Buffer) / 2 - sourse->W_Height / 15;
		outtextxy(x, y, Buffer);
		//按Enter继续
		y += sourse->W_Height / 3;
		sprintf(Buffer, "轻点继续");
		settextstyle(sourse->W_Height / 20, 0, "汉仪跳跳体简");
		x = x = sourse->W_Width / 2 - textwidth(Buffer) / 2;
		outtextxy(x, y, Buffer);
	}
}

void DissPlay(DP* sourse)
{
	//所有图形打印及文字打印链接
	int ButtomWidth = sourse->W_Width + 1;
	int ButtomHeight = sourse->W_Height / 9;
	int GrowpWidth = sourse->W_Width / 40;
	int GrowpHeight = sourse->W_Height / 7;
	int GrowpRound = GrowpHeight / 20;

	int DissMaxLayerNumber = 15;
	int DissBaseLayerHeight = (int)sourse->W_Height / 25;
	int DissBaseMaxLayerHeight = DissMaxLayerNumber * DissBaseLayerHeight;
	int DissLayerHeight = DissBaseLayerHeight;
	if (sourse->LayerNumber > DissMaxLayerNumber)
	{
		DissLayerHeight = DissLayerHeight / sourse->LayerNumber * DissMaxLayerNumber;
	}

	int DissLayerMaxWidth = sourse->W_Width / sourse->GrowpNumber - sourse->W_Width / sourse->GrowpNumber / 5 * 1;
	int DissLayerMinWidth = sourse->W_Width / sourse->GrowpNumber - sourse->W_Width / sourse->GrowpNumber / 5 * 4;
	int DissLayerStepWidth = (DissLayerMaxWidth - DissLayerMinWidth) / sourse->LayerNumber / 2;
	int LayerRound = DissLayerHeight / 10;
	int DissLayerX = (int)sourse->W_Width / sourse->GrowpNumber / 2;
	int DissLayerY = (int)sourse->W_Height - ButtomHeight;
	int i = 0, j = 0;
	int x = 0, y = 0;
	cleardevice();

	Growp* TmpGrowp = NULL;
	Layer* TmpLayer = NULL;

	//ChoiceBK
	{
		for (i = 0; i < sourse->GrowpNumber; i++)
		{
			if (sourse->MouxeXY == i + 1)
			{
				setfillcolor(RGB(172, 200, 196));
				fillrectangle(i * sourse->W_Width / sourse->GrowpNumber, 0, (i + 1) * sourse->W_Width / sourse->GrowpNumber, sourse->W_Height);
			}
			if (sourse->choice_sourse == i + 1)
			{
				setfillcolor(RGB(172, 200, 196));
				fillrectangle(i * sourse->W_Width / sourse->GrowpNumber, 0, (i + 1) * sourse->W_Width / sourse->GrowpNumber, sourse->W_Height);
			}
		}
		for (i = 0; i < sourse->GrowpNumber; i++)
		{
			
			if (!sourse->choice_sourse)
			{
				break;
			}
			if (sourse->choice_sourse - 1 != i)
			{
				if (IfMoveLayer(sourse->sourse, sourse->choice_sourse - 1, i))
				{
					setfillcolor(RGB(198, 224, 181));
					fillrectangle(i * sourse->W_Width / sourse->GrowpNumber, 0, (i + 1) * sourse->W_Width / sourse->GrowpNumber, sourse->W_Height);
				}
				else
				{
					setfillcolor(RGB(192, 137, 123));
					fillrectangle(i * sourse->W_Width / sourse->GrowpNumber, 0, (i + 1) * sourse->W_Width / sourse->GrowpNumber, sourse->W_Height);
				}
			}
		}
	}

	//growp
	x = 0, y = 0;
	x = -(int)GrowpWidth / 2 - sourse->W_Width / sourse->GrowpNumber/2;
	setfillcolor(0x9FAC2B);
	for (i = 0; i < sourse->GrowpNumber; i++)
	{
		int j = 0;
		x += sourse->W_Width / sourse->GrowpNumber;
		fillroundrect(x, GrowpHeight, x + GrowpWidth, sourse->W_Height, GrowpRound, GrowpRound);
	}

	//layer
	int width = 0;

	int r = 0x7A, R = 0x25;
	int g = 0xBE, G = 0x74;
	int b = 0xEF, B = 0x9E;

	TmpGrowp = sourse->sourse;
	for (i = 0; i < sourse->GrowpNumber; i++)
	{
		TmpLayer = TmpGrowp->Arr;
		x = DissLayerX + i * (int)sourse->W_Width / sourse->GrowpNumber;
		for (j = 0; j < TmpGrowp->LayerNumber; j++)
		{
			setfillcolor(RGB(r + (R - r) / (TmpGrowp->LayerNumber - 1) * (TmpLayer->Number - 1),
				g + (G - g) / (TmpGrowp->LayerNumber - 1) * (TmpLayer->Number - 1),
				b + (B - b) / (TmpGrowp->LayerNumber - 1) * (TmpLayer->Number - 1)));
			//50 + (200 - 50) / 9 * n
			width = DissLayerMinWidth + (DissLayerMaxWidth - DissLayerMinWidth) 
				/ (TmpGrowp->LayerNumber - 1) * (TmpLayer->Number - 1);
			y = DissLayerY - DissLayerHeight * (j + 1);

			if (!TmpLayer->Number)
			{
				break;
			}
			fillroundrect(x - width / 2, y, x + width / 2, y + DissLayerHeight, LayerRound, LayerRound);

			TmpLayer = NextLayer(TmpLayer);
		}
		TmpGrowp = NextGrowp(TmpGrowp);
	}

	x = -1;
	y = sourse->W_Height - ButtomHeight;
	setfillcolor(0x374757);
	fillrectangle(x, y, x + ButtomWidth, y + ButtomHeight);

	PutText(sourse);

	PutWin(sourse);

	PutMenu(sourse);

	FlushBatchDraw();
}

void PutText(DP* sourse)
{
	//所有文字打印
	int ButtomWidth = sourse->W_Width + 1;
	int ButtomHeight = sourse->W_Height / 9;
	char Buffer[1024] = "";
	int x = 0, y = 0;

	Growp* TmpGrowp = NULL;
	Layer* TmpLayer = NULL;

	int DissBaseLayerHeight = (int)sourse->W_Height / 25;
	int i = 0, j = 0;

	int width = 0;
	int DissMaxLayerNumber = 15;
	int DissBaseMaxLayerHeight = DissMaxLayerNumber * DissBaseLayerHeight;
	int DissLayerHeight = DissBaseLayerHeight;
	if (sourse->LayerNumber > DissMaxLayerNumber)
	{
		DissLayerHeight = DissLayerHeight / sourse->LayerNumber * DissMaxLayerNumber;
	}
	int DissLayerX = (int)sourse->W_Width / sourse->GrowpNumber / 2;
	int DissLayerY = (int)sourse->W_Height - ButtomHeight;

	settextstyle(DissLayerHeight * 1.2, 0, "汉仪跳跳体简");
	settextcolor(0xDFBFFF);

	TmpGrowp = sourse->sourse;
	for (i = 0; i < sourse->GrowpNumber; i++)
	{
		x = DissLayerX + i * (int)sourse->W_Width / sourse->GrowpNumber;
		TmpLayer = TmpGrowp->Arr;
		for (j = 0; j < TmpGrowp->LayerNumber; j++)
		{
			//50 + (200 - 50) / 9 * n

			if (!TmpLayer->Number)
			{
				break;
			}

			sprintf(Buffer, "%d", TmpLayer->Number);

			int Tx = x - textwidth(Buffer) / 2;

			y = DissLayerY - DissLayerHeight * (j + 1);
			outtextxy(Tx, y, Buffer);

			TmpLayer = NextLayer(TmpLayer);
		}
		TmpGrowp = NextGrowp(TmpGrowp);
	}

	sprintf(Buffer, "已移动步数%d", *(sourse->MoveNumber));
	settextstyle(ButtomHeight * 0.4, 0, "汉仪跳跳体简");
	settextcolor(0xcfcfcf);
	x = sourse->W_Width / 2 - textwidth(Buffer) / 2;
	y = sourse->W_Height - textheight(Buffer) * 2.2;
	outtextxy(x, y, Buffer);

}