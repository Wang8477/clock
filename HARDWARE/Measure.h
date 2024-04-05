/****************************************************************
*文件名：Measure.h
*模块版本:V1.0
*作用：对电压值进行采样
****************************************************************/
#ifndef Measure_H
#define Measure_H
#include "main.h"
#include "adc.h"
#define sample_num 20  //采样点
void StartMeasurement(void);
float GetVolt(void);

#endif
