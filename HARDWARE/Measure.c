/****************************************************************
*文件名：Measure.c
*模块版本:V1.0

*作用：对电压值进行采样和温度的获取
****************************************************************/
/*****************头文件引用******************/
#include "Measure.h"
uint16_t ADCValue[sample_num]={0};//初始化ADC-DMA接收数组
void StartMeasurement(void)
{
	HAL_ADC_Start_DMA(&hadc1,(uint32_t*)ADCValue,sample_num);//开启ADC-DMA传输
}
/****************************************************************
*函数名：GetVolt
*作用：ADC通过DMA方式获取电压
*传入参数：ADCValue:ADC采样值DMA存储数组
           sample：采样次数
*返回值：平均电压值
****************************************************************/
float GetVolt(void)
{
	float volt=0;
	uint32_t sum=0;
	for(int i=0;i<sample_num;i++)
	{
		sum+=*(ADCValue+i);//累加值
	}
	volt=(float)sum/(4096*sample_num)*3.3; //计算电压
	return volt;
}
