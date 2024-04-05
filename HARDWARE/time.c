#include "time.h"

int count =0;
int SleepFlag=0;

typedef struct{
	uint8_t time_hour;    //现在时间（小时）
	uint8_t time_minute;  //现在时间（分钟）
	uint8_t time_second;  //现在时间（秒）
	uint8_t alarm_hour;    //设置闹钟时间（小时）
	uint8_t alarm_minute;  //设置闹钟时间（分钟）
	uint8_t alarm_second;  //设置闹钟时间（秒）
	uint8_t alarm_flag;    //到闹钟指定时间响铃事件标志位
}_clock;
 _clock clock;

/*******************************/
void clock_init()
{
	clock.time_hour=0;    //设置现在时间（小时）
	clock.time_minute=0;  //设置现在时间（分钟）
	clock.time_second=0;  //设置现在时间（秒）
	clock.alarm_hour=0;    //设置闹钟时间（小时）
	clock.alarm_minute=0;  //设置闹钟时间（分钟）
	clock.alarm_second=0;  //设置闹钟时间（秒）
	clock.alarm_flag=0;    //闹钟指定时间响铃事件标志位
	//HAL_GPIO_WritePin(BEEP_GPIO_Port,BEEP_Pin,GPIO_PIN_RESET);//蜂鸣器
}

void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim)
{
	if(htim->Instance==TIM10)//定时器每1s中断
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