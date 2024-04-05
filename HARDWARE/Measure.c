/****************************************************************
*�ļ�����Measure.c
*ģ��汾:V1.0

*���ã��Ե�ѹֵ���в������¶ȵĻ�ȡ
****************************************************************/
/*****************ͷ�ļ�����******************/
#include "Measure.h"
uint16_t ADCValue[sample_num]={0};//��ʼ��ADC-DMA��������
void StartMeasurement(void)
{
	HAL_ADC_Start_DMA(&hadc1,(uint32_t*)ADCValue,sample_num);//����ADC-DMA����
}
/****************************************************************
*��������GetVolt
*���ã�ADCͨ��DMA��ʽ��ȡ��ѹ
*���������ADCValue:ADC����ֵDMA�洢����
           sample����������
*����ֵ��ƽ����ѹֵ
****************************************************************/
float GetVolt(void)
{
	float volt=0;
	uint32_t sum=0;
	for(int i=0;i<sample_num;i++)
	{
		sum+=*(ADCValue+i);//�ۼ�ֵ
	}
	volt=(float)sum/(4096*sample_num)*3.3; //�����ѹ
	return volt;
}
