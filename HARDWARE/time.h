#ifndef __TIME_H
#define __TIME_H

#include "stdint.h"
#include "main.h"
#include "multi_button.h"
typedef struct{
	uint8_t time_hour;    //现在时间（小时）
	uint8_t time_minute;  //现在时间（分钟）
	uint8_t time_second;  //现在时间（秒）
	uint8_t alarm_hour;    //设置闹钟时间（小时）
	uint8_t alarm_minute;  //设置闹钟时间（分钟）
	uint8_t alarm_second;  //设置闹钟时间（秒）
	uint8_t alarm_flag;    //到闹钟指定时间响铃事件标志位
}_clock;
extern _clock clock;
extern int count;
extern uint16_t  setflag;
extern uint16_t  set;
extern uint16_t  select;

void clock_init();
void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim);
void  BTN1_SINGLE_Click_Handler();
void  BTN2_SINGLE_Click_Handler();
void BTN3_LONG_PRESS_START_Handler();
void  BTN3_SINGLE_Click_Handler();
void  BTN4_SINGLE_Click_Handler();
uint8_t read_button_GPIO(uint8_t button_id);


#endif
