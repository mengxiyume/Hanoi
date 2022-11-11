#pragma once

//#define Window_Width 1440
//#define Window_Height 920

typedef struct Hanoi_Layer
{
	size_t Number;
	Hanoi_Layer* Last;
	Hanoi_Layer* Next;
}Layer;

typedef struct Hanoi_Growp
{
	Hanoi_Layer* Arr;
	int LayerNumber;
	Hanoi_Growp* Last;
	Hanoi_Growp* Next;
}Growp;

typedef struct DissPlayStruct
{
	int W_Width;
	int W_Height;
	Growp* sourse;
	size_t Level;
	size_t GrowpNumber;
	size_t LayerNumber;
	size_t* MoveNumber;
	int MouxeXY;
	int choice_sourse;
	int choice_destination;

	bool win;
	bool Menu;
	bool OpenBegin;
}DP;

typedef struct Choice
{
	unsigned char sourse;
	unsigned char destination;
	bool state;
}Choice;