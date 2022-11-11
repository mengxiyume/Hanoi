#define _CRT_SECURE_NO_WARNINGS 1

#include"Struct.h"
#include"Head.h"

Growp* ReadGame(size_t* GrowpNumber, size_t* LayerNumber, size_t* MoveNumber)
{
	FILE* pLevel = NULL;
	FILE* Tmp = fopen("./Level.txt", "r");


	
	Growp* ret = NULL;
	if (!Tmp)
	{
		return NULL;
	}
	pLevel = Tmp;
	fscanf(pLevel, "%u%d%u\n", GrowpNumber, LayerNumber, MoveNumber);

	ret = NewGame(*LayerNumber, *GrowpNumber);
	
	int i = 0, j = 0;

	Growp* TmpGrowp = ret;
	for (i = 0; i < *GrowpNumber; i++)
	{
		TmpGrowp->LayerNumber = *LayerNumber;
		Layer* TmpLayer = TmpGrowp->Arr;
		for (j = 0; j < *LayerNumber; j++)
		{
			fscanf(pLevel, "%d", &TmpLayer->Number);
			TmpLayer = NextLayer(TmpLayer);
		}
		fscanf(pLevel, "\n");
		TmpGrowp = NextGrowp(TmpGrowp);
	}
	fclose(pLevel);
	pLevel = NULL;

	return ret;
}

void SaveGame(Growp* const sourse, size_t GrowpNumber, size_t MoveNumber)
{
	assert(sourse && GrowpNumber);
	FILE* pLevel = NULL;
	FILE* pTmp = fopen("./Level.txt", "w");
	assert(pTmp);
	pLevel = pTmp;
	int i = 0, j = 0;
	Growp* TmpGrowp = sourse;

	fprintf(pLevel, "%u %d %u\n", GrowpNumber, sourse->LayerNumber, MoveNumber);
	for (i = 0; i < GrowpNumber; i++)
	{
		Layer* TmpLayer = TmpGrowp->Arr;
		for (j = 0; j < TmpGrowp->LayerNumber; j++)
		{
			fprintf(pLevel, "%d ", TmpLayer->Number);
			TmpLayer = NextLayer(TmpLayer);
		}
		fprintf(pLevel, "\n");
		TmpGrowp = NextGrowp(TmpGrowp);
	}
	fclose(pLevel);
	pLevel = NULL;
}