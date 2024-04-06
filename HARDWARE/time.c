#include "time.h"
_clock clock;
int count =0;
uint16_t  setflag=0;
uint16_t  set=0;
uint16_t  select=0;

/*******************************/
void clock_init()
{
	clock.time_hour=0;    //��������ʱ�䣨Сʱ��
	clock.time_minute=0;  //��������ʱ�䣨���ӣ�
	clock.time_second=0;  //��������ʱ�䣨�룩
	clock.alarm_hour=1;    //��������ʱ�䣨Сʱ��
	clock.alarm_minute=0;  //��������ʱ�䣨���ӣ�
	clock.alarm_second=0;  //��������ʱ�䣨�룩
	clock.alarm_flag=0;    //����ָ��ʱ�������¼���־λ
	HAL_GPIO_WritePin(BEEP_GPIO_Port,BEEP_Pin,GPIO_PIN_RESET);//������
}

void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim)
{
	if(htim->Instance==TIM10)//��ʱ��ÿ1s�ж�
	{
			
		if(setflag ==0)
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
	if(htim->Instance ==TIM11  )
	{
		button_ticks();
		if(clock.alarm_hour==clock.time_hour&&clock.alarm_minute==clock.time_minute\
			&&clock.alarm_second==clock.time_second&&!clock.alarm_flag)//������ʱ��ʱ�����Ӵ�ʱû����
		{
			clock .alarm_flag =1;
		}
		else clock .alarm_flag =0;
	}
}
void  BTN1_SINGLE_Click_Handler()
{
}
void  BTN2_SINGLE_Click_Handler()
{
	select++;
	if(select==2)
	{select=0;}
}
void BTN3_LONG_PRESS_START_Handler()
{
	setflag ++;
	if(setflag ==2)
	{setflag =0;}
}
void  BTN3_SINGLE_Click_Handler()
{
	if(setflag )
	{
		set++;
		if(set==3)
		{set=0;}
	}
}
void  BTN4_SINGLE_Click_Handler()
{ 
	if(select)
	{
		switch(set)
		{
			case 0:
				clock.alarm_hour ++;
			if(clock .alarm_hour ==24)
				clock.alarm_hour =0;
			break;
			case 1:
				clock.alarm_minute ++;
			if(clock .alarm_minute ==60)
				clock.alarm_minute =0;
			break;
			case 2:
				clock.alarm_second ++;
			if(clock .alarm_second ==60)
				clock.alarm_second =0;
			break;
						default :
				break ;
		}
	}
	else 
	{
		switch(set)
		{
			case 0:
				clock.time_hour ++;
			if(clock .time_hour ==24)
				clock.time_hour =0;
			break ;
			case 1:
				clock.time_minute ++;
			if(clock .time_minute ==60)
				clock.time_minute =0;
			break ;
			case 2:
				clock.time_second ++;
			if(clock .time_second ==60)
				clock.time_second =0;
			break;
			default :
				break ;
		}
	}
}
uint8_t read_button_GPIO(uint8_t button_id)
{
	switch(button_id)
	{
		case 0:
			return HAL_GPIO_ReadPin(KEY0_GPIO_Port, KEY0_Pin);
		case 1:
			return HAL_GPIO_ReadPin(KEY1_GPIO_Port, KEY1_Pin);
		case 2:
			return HAL_GPIO_ReadPin(KEY2_GPIO_Port, KEY2_Pin);
		case 3:
			return HAL_GPIO_ReadPin(KEY3_GPIO_Port, KEY3_Pin);
		default:
			return 0;
	}
}