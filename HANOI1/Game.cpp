#define _CRT_SECURE_NO_WARNINGS 1

#include"Head.h"
#include"Struct.h"

void PutGame(Growp* const sourse,size_t GrowpNumber)
{
	assert(sourse && GrowpNumber);
	int i = 0, j = 0;
	Growp* TmpGrowp = NULL;
	Layer* TmpLayer = NULL;

	TmpGrowp = sourse;

	for (i = 0; i < GrowpNumber; i++)
	{
		printf("|%c:| ", 'A' + i);
		TmpLayer = TmpGrowp->Arr;
		while (TmpLayer->Next)
		{
			printf("%03d| ", TmpLayer->Number);
			TmpLayer = NextLayer(TmpLayer);
		}
		printf("%03d| ", TmpLayer->Number);

		TmpGrowp = NextGrowp(TmpGrowp);
		printf("\n");
	}

}

Growp* NewGame(size_t LayerNumber, size_t GrowpNumber)
{
	Growp* ret = NULL;
	Growp* TmpGrowp = NULL;
	Layer* TmpLayer = NULL;

	int i = 0, j = 0;
	for (i = 0; i < GrowpNumber; i++)
	{
		switch (i)
		{
		case 0:
			ret = TmpGrowp = GetGrowp(NULL, LayerNumber);
			for (j = 0; j < LayerNumber; j++)
			{
				switch (j)
				{
				case 0:
					TmpLayer = TmpGrowp->Arr = GetLayer(NULL);
					break;
				default:
					TmpLayer = GetLayer(TmpLayer);
					break;
				}
			}
			break;
		default:
			TmpGrowp = GetGrowp(TmpGrowp, LayerNumber);
			for (j = 0; j < LayerNumber; j++)
			{
				switch (j)
				{
				case 0:
					TmpLayer = TmpGrowp->Arr = GetLayer(NULL);
					break;
				default:
					TmpLayer = GetLayer(TmpLayer);
					break;
				}
			}
		}
	}
	return ret;
}

void InitGame(Growp* destination)
{
	//层初始化为倒序
	Layer* TmpLayer = destination->Arr;
	int i = 0;
	for (i = 0; i < destination->LayerNumber; i++)
	{
		TmpLayer->Number = destination->LayerNumber - i;
		TmpLayer = NextLayer(TmpLayer);
	}
}

Layer* EndLayer(Layer* sourse)
{
	//最后一个元素或者元素为0时返回
	size_t* ret = NULL;
	assert(sourse);
	Layer* TmpLayer = sourse;

	while (true)
	{
		if (!TmpLayer->Next || !TmpLayer->Number)
		{
			return TmpLayer;
		}
		TmpLayer = NextLayer(TmpLayer);
	}
}

bool IfMoveLayer(Growp* const pSourse, size_t ChoiceSourse, size_t ChoiceDestination)
{
	assert(pSourse);

	if (ChoiceSourse == ChoiceDestination)
	{
		return false;
	}

	size_t* TmpSourse = NULL;
	size_t* TmpDestination = NULL;
	size_t DestinationNumber = NULL;
	size_t SourseNumber = NULL;
	Growp* TmpGrowp = pSourse;
	Layer* TmpLayer = NULL;
	int i = 0, j = 0;

	//拿到选择的Growp最后一个
	for (i = 0; i < ChoiceSourse; i++)
	{
		TmpGrowp = NextGrowp(TmpGrowp);
		if (!TmpGrowp)
		{
			return NULL;
		}
	}
	TmpLayer = EndLayer(TmpGrowp->Arr);
	if (!TmpLayer->Number)
	{
		if (!TmpLayer->Last)
		{
			return NULL;
		}
		TmpLayer = LastLayer(TmpLayer);
	}
	TmpSourse = &TmpLayer->Number;
	SourseNumber = *TmpSourse;


	//拿到目标的Growp的第一个为空的链表位
	TmpGrowp = pSourse;
	for (i = 0; i < ChoiceDestination; i++)
	{
		TmpGrowp = NextGrowp(TmpGrowp);
		if (!TmpGrowp)
		{
			return NULL;
		}
	}
	TmpLayer = EndLayer(TmpGrowp->Arr);
	TmpDestination = &TmpLayer->Number;
	if (TmpLayer->Last)
	{
		TmpLayer = LastLayer(TmpLayer);
		DestinationNumber = TmpLayer->Number;
	}

	//将链表内容互换移动
	//链表包含信息少，不用将链表链接处修改
	if (SourseNumber < DestinationNumber)
	{
		return true;
	}
	else if (DestinationNumber == 0)
	{
		return true;
	}

	return false;
}

int MoveLayer(Growp* pSourse, size_t ChoiceSourse, size_t ChoiceDestination, size_t* MoveNumber)
{
	assert(pSourse);

	if (ChoiceSourse == ChoiceDestination)
	{
		return NULL;
	}

	size_t* TmpSourse = NULL;
	size_t* TmpDestination = NULL;
	size_t DestinationNumber = NULL;
	size_t SourseNumber = NULL;
	Growp* TmpGrowp = pSourse;
	Layer* TmpLayer = NULL;
	int i = 0, j = 0;

	//拿到选择的Growp最后一个
	for (i = 0; i < ChoiceSourse; i++)
	{
		TmpGrowp = NextGrowp(TmpGrowp);
		if (!TmpGrowp)
		{
			return NULL;
		}
	}
	TmpLayer = EndLayer(TmpGrowp->Arr);
	if (!TmpLayer->Number)
	{
		if (!TmpLayer->Last)
		{
			return NULL;
		}
		TmpLayer = LastLayer(TmpLayer);
	}
	TmpSourse = &TmpLayer->Number;
	SourseNumber = *TmpSourse;


	//拿到目标的Growp的第一个为空的链表位
	TmpGrowp = pSourse;
	for (i = 0; i < ChoiceDestination; i++)
	{
		TmpGrowp = NextGrowp(TmpGrowp);
		if (!TmpGrowp)
		{
			return NULL;
		}
	}
	TmpLayer = EndLayer(TmpGrowp->Arr);
	TmpDestination = &TmpLayer->Number;
	if (TmpLayer->Last)
	{
		TmpLayer = LastLayer(TmpLayer);
		DestinationNumber = TmpLayer->Number;
	}
	
	//将链表内容互换移动
	//链表包含信息少，不用将链表链接处修改
	if (SourseNumber < DestinationNumber)
	{
		*TmpDestination = *TmpSourse;
		*TmpSourse = NULL;
		(*MoveNumber)++;
		return *TmpDestination;
	}
	else if (DestinationNumber == 0)
	{
		*TmpDestination = *TmpSourse;
		*TmpSourse = NULL;
		(*MoveNumber)++;
		return *TmpDestination;
	}

	return NULL;
}

bool IsWin(Growp* const sourse, size_t WinGrowp)
{
	int i = 0;
	Growp* TmpGrowp = sourse;
	Layer* TmpLayer = NULL;
	for (i = 0; i < WinGrowp; i++)
	{
		//找到win组
		TmpGrowp = NextGrowp(TmpGrowp);
	}
	TmpLayer = TmpGrowp->Arr;
	while (TmpLayer->Next)
	{
		//找到win组最后一个元素
		TmpLayer = NextLayer(TmpLayer);
	}
	if (TmpLayer->Number)
	{
		// win组最后一个元素的number为真则胜利
		//（正常情况下最后一个元素只能为1，且组为降序）
		return true;
	}
	return false;
}

void CloseGame(DP* sourse)
{
	int i = 0, j = 0;
	CloseGrowp(sourse->sourse);
	sourse->sourse = NULL;
}