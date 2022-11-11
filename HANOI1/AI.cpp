#define _CRT_SECURE_NO_WARNINGS 1

#include"Struct.h"
#include"Head.h"

bool AI_Move(Growp* AI_, int x, int y, size_t* MoveNumber)
{
	MoveLayer(AI_, x, y, MoveNumber);
	return true;
}

bool AI_Hanoi(Growp* AI_, int a, int b, int c,size_t Count, size_t* MoveNumber, DP* diss)
{

	if (IfReturn())
	{
		return true;
	}
	if (Count == 1)
	{
		AI_Move(AI_, a, c, MoveNumber);
		PutGame(AI_, 3);
		DissPlay(diss);
	}
	else
	{
		if (AI_Hanoi(AI_, a, c, b, Count - 1, MoveNumber, diss))
		{
			return true;
		}
		AI_Move(AI_, a, c, MoveNumber);
		PutGame(AI_, 3);
		DissPlay(diss);
		if (AI_Hanoi(AI_, b, a, c, Count - 1, MoveNumber, diss))
		{
			return true;
		}
	}
	return false;
}

bool AI_GAME(DP* sourse)
{
	Growp* AI_ = NewGame(sourse->LayerNumber, sourse->GrowpNumber);
	*(sourse->MoveNumber) = NULL;
	sourse->sourse = AI_;
	InitGame(AI_);

	return AI_Hanoi(AI_, 0, 1, 2, AI_->LayerNumber, sourse->MoveNumber, sourse);
}