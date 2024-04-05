#ifndef __TIME_H
#define __TIME_H

#include "stdint.h"
#include "main.h"



void clock_init();
void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim);






#endif