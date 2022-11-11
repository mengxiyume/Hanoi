#pragma once

void PutGame(Growp* const sourse, size_t GrowpNumber);
Growp* NewGame(size_t LayerNumber, size_t GrowpNumber);
void InitGame(Growp* destination);
int MoveLayer(Growp* pSourse, size_t ChoiceSourse, size_t ChoiceDestination, size_t* MoveNumber);
bool IsWin(Growp* const sourse, size_t WinGrowp);
void CloseGame(DP* sourse);
bool IfMoveLayer(Growp* const pSourse, size_t ChoiceSourse, size_t ChoiceDestination);
Layer* EndLayer(Layer* sourse);