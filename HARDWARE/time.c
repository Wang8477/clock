#include "time.h"
_clock clock;
int count =0;
uint16_t  setflag=0;
uint16_t  set=0;
uint16_t  select=0;

/*******************************/
void clock_init()
{
	clock.time_hour=0;    //设置现在时间（小时）
	clock.time_minute=0;  //设置现在时间（分钟）
	clock.time_second=0;  //设置现在时间（秒）
	clock.alarm_hour=1;    //设置闹钟时间（小时）
	clock.alarm_minute=0;  //设置闹钟时间（分钟）
	clock.alarm_second=0;  //设置闹钟时间（秒）
	clock.alarm_flag=0;    //闹钟指定时间响铃事件标志位
	HAL_GPIO_WritePin(BEEP_GPIO_Port,BEEP_Pin,GPIO_PIN_RESET);//蜂鸣器
}

void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim)
{
	if(htim->Instance==TIM10)//定时器每1s中断
	{
			
		if(setflag ==0)
			{
				if(clock.time_second==59&&clock.time_minute==59&&clock.time_hour==23)//当23时59分59秒时转到0点0分0秒
				{
					clock.time_second=0;
					clock.time_minute=0;
					clock.time_hour=0;
				}
				else if(clock.time_second==59&&clock.time_minute==59)//当x点59分59秒时转到(x+1)点0分0秒
				{
					clock.time_second=0;
					clock.time_minute=0;
					clock.time_hour++;
				}
				else if(clock.time_second==59)//当x点x分59秒时转到x点（x+1）分0秒
				{
					clock.time_second=0;
					clock.time_minute++;
				}
				else clock.time_second++; //当x点x分x秒时转到x点x分(x+1)秒
		}
	}
	if(htim->Instance ==TIM11  )
	{
		button_ticks();
		if(clock.alarm_hour==clock.time_hour&&clock.alarm_minute==clock.time_minute\
			&&clock.alarm_second==clock.time_second&&!clock.alarm_flag)//到响铃时间时且闹钟此时没有响
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