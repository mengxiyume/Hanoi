#pragma once

#include"Struct.h"

Growp* ReadGame(size_t* GrowpNumber, size_t* LayerNumber, size_t* MoveNumber);
void SaveGame(Growp* const sourse, size_t GrowpNumber, size_t MoveNumber);