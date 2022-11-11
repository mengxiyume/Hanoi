#pragma once

#include"Struct.h"

Layer* GetLayer(Layer* last);						//last����ΪNULLʱ��������ͷ
Growp* GetGrowp(Growp* last, size_t LayerNumber);	//last����ΪNULLʱ��������ͷ

Growp* NextGrowp(Growp* dest);
Layer* NextLayer(Layer* dest);

Layer* LastLayer(Layer* dest);
Growp* LastGrowp(Growp* dest);

void CloseGrowp(Growp* sourse);
void CloseLayer(Layer* sourse);

Growp* GoToGrowp(Growp* const sourse, size_t GrowpNumber);
Layer* GoToLayer(Growp* const sourse, size_t GrowpNumber, size_t LayerNumber);