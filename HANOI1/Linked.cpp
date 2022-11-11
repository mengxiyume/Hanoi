#define _CRT_SECURE_NO_WARNINGS 1
#include"Struct.h"
#include"Head.h"

Growp* GetGrowp(Growp* last, size_t LayerNumber)
{
	int i = 0;
	Growp* ret = NULL;

	static Growp* LastGrowp = NULL;

	Growp* Tmp = (Growp*)calloc(1, sizeof(Growp));
	assert(Tmp);
	ret = Tmp;
	ret->LayerNumber = LayerNumber;
	if (last)
	{
		//新拿到的链表空间链接到上一个链表尾部
		last->Next = ret;
		Tmp->Last = LastGrowp;
	}
	LastGrowp = ret;
	return ret;
}

Layer* GetLayer(Layer* last)
{
	int i = 0;
	Layer* ret = NULL;
	
	static Layer* LastLayer = NULL;

	Layer* Tmp = (Layer*)calloc(1, sizeof(Layer));
	assert(Tmp);
	ret = Tmp;
	if (last)
	{
		last->Next = ret;
		ret->Last = LastLayer;
	}
	LastLayer = ret;
	return ret;
}

Growp* NextGrowp(Growp* dest)
{
	assert(dest);
	return dest->Next;
}

Layer* NextLayer(Layer* dest)
{
	assert(dest);
	return dest->Next;
}

Growp* LastGrowp(Growp* dest)
{
	assert(dest);
	return dest->Last;
}

Layer* LastLayer(Layer* dest)
{
	assert(dest);
	return dest->Last;
}

void CloseGrowp(Growp* sourse)
{
	assert(sourse);
	if (sourse->Next)
	{
		CloseGrowp(sourse->Next);
	}
	CloseLayer(sourse->Arr);
	sourse->Arr = NULL;
	free(sourse);
	sourse = NULL;
}

void CloseLayer(Layer* sourse)
{
	assert(sourse);
	if (sourse->Next)
	{
		CloseLayer(sourse->Next);
	}
	free(sourse);
	sourse = NULL;
}

Growp* GoToGrowp(Growp* const sourse, size_t GrowpNumber)
{
	assert(sourse);

	int i = 0;

	Growp* TmpGrowp = sourse;

	for (i = 0; i < GrowpNumber; i++)
	{
		TmpGrowp = NextGrowp(TmpGrowp);
	}
	return TmpGrowp;
}

Layer* GoToLayer(Growp* const sourse, size_t GrowpNumber, size_t LayerNumber)
{
	assert(sourse);

	int i = 0;

	Growp* TmpGrowp = sourse;
	Layer* TmpLayer = NULL;

	for (i = 0; i < GrowpNumber; i++)
	{
		TmpGrowp = NextGrowp(TmpGrowp);
	}
	TmpLayer = TmpGrowp->Arr;
	for (i = 0; i < LayerNumber; i++)
	{
		TmpLayer = NextLayer(TmpLayer);
	}
	return TmpLayer;
}