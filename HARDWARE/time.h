#ifndef __TIME_H
#define __TIME_H

#include "stdint.h"
#include "main.h"
#include "multi_button.h"
typedef struct{
	uint8_t time_hour;    //����ʱ�䣨Сʱ��
	uint8_t time_minute;  //����ʱ�䣨���ӣ�
	uint8_t time_second;  //����ʱ�䣨�룩
	uint8_t alarm_hour;    //��������ʱ�䣨Сʱ��
	uint8_t alarm_minute;  //��������ʱ�䣨���ӣ�
	uint8_t alarm_second;  //��������ʱ�䣨�룩
	uint8_t alarm_flag;    //������ָ��ʱ�������¼���־λ
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
