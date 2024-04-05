#include "time.h"

int count =0;
int SleepFlag=0;

typedef struct{
	uint8_t time_hour;    //����ʱ�䣨Сʱ��
	uint8_t time_minute;  //����ʱ�䣨���ӣ�
	uint8_t time_second;  //����ʱ�䣨�룩
	uint8_t alarm_hour;    //��������ʱ�䣨Сʱ��
	uint8_t alarm_minute;  //��������ʱ�䣨���ӣ�
	uint8_t alarm_second;  //��������ʱ�䣨�룩
	uint8_t alarm_flag;    //������ָ��ʱ�������¼���־λ
}_clock;
 _clock clock;

/*******************************/
void clock_init()
{
	clock.time_hour=0;    //��������ʱ�䣨Сʱ��
	clock.time_minute=0;  //��������ʱ�䣨���ӣ�
	clock.time_second=0;  //��������ʱ�䣨�룩
	clock.alarm_hour=0;    //��������ʱ�䣨Сʱ��
	clock.alarm_minute=0;  //��������ʱ�䣨���ӣ�
	clock.alarm_second=0;  //��������ʱ�䣨�룩
	clock.alarm_flag=0;    //����ָ��ʱ�������¼���־λ
	//HAL_GPIO_WritePin(BEEP_GPIO_Port,BEEP_Pin,GPIO_PIN_RESET);//������
}

void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim)
{
	if(htim->Instance==TIM10)//��ʱ��ÿ1s�ж�
	{
	
			if(clock.time_second==59&&clock.time_minute==59&&clock.time_hour==23)//��23ʱ59��59��ʱת��0��0��0��
			{
				clock.time_second=0;
				clock.time_minute=0;
				clock.time_hour=0;
			}
			else if(clock.time_second==59&&clock.time_minute==59)//��x��59��59��ʱת��(x+1)��0��0��
			{
				clock.time_second=0;
				clock.time_minute=0;
				clock.time_hour++;
			}
			else if(clock.time_second==59)//��x��x��59��ʱת��x�㣨x+1����0��
			{
				clock.time_second=0;
				clock.time_minute++;
			}
			else clock.time_second++; //��x��x��x��ʱת��x��x��(x+1)��
			
	}
}