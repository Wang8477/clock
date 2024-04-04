#ifndef __OLED_H
#define __OLED_H 
 
#include "main.h"
#include "stm32f4xx_hal.h"
#include "stdlib.h"
#include "stdio.h"

//�������ȱ�������
typedef enum
{
	LIGHT_HIGH=1,
	LIGHT_MID,
	LIGHT_LOW,
}LIGHT_LEVEL;
//-----------------OLED�˿ڶ���---------------- 
 
 
#define OLED_RES_Clr() HAL_GPIO_WritePin(OLED_RES_GPIO_Port,OLED_RES_Pin,GPIO_PIN_RESET)//RES
#define OLED_RES_Set() HAL_GPIO_WritePin(OLED_RES_GPIO_Port,OLED_RES_Pin,GPIO_PIN_SET)
 
#define OLED_DC_Clr() HAL_GPIO_WritePin(OLED_DC_GPIO_Port,OLED_DC_Pin,GPIO_PIN_RESET)//DC
#define OLED_DC_Set() HAL_GPIO_WritePin(OLED_DC_GPIO_Port,OLED_DC_Pin,GPIO_PIN_SET)
 		     
#define OLED_CS_Clr()  HAL_GPIO_WritePin(OLED_CS_GPIO_Port,OLED_CS_Pin,GPIO_PIN_RESET)//CS
#define OLED_CS_Set()  HAL_GPIO_WritePin(OLED_CS_GPIO_Port,OLED_CS_Pin,GPIO_PIN_SET)
 
#define OLED_CMD  0	//д����
#define OLED_DATA 1	//д����
 
#define uint8_t unsigned char
#define uint32_t unsigned int
#define WHICH_SPI &hspi1//����ʹ�õ�SPI����
 
void OLED_ClearPoint(uint8_t x,uint8_t y);   //ȥ����
void OLED_ColorTurn(uint8_t i);   //�ı���ɫ
void OLED_DisplayTurn(uint8_t i); //
void OLED_WR_Byte(uint8_t dat,uint8_t cmd);   //д��һ���ֽ�
void OLED_DisPlay_On(void);   //������ʾ
void OLED_DisPlay_Off(void);  //�ر���ʾ
void OLED_Refresh(void);  //����OLED�Դ�
void OLED_Clear(void);  //����
void OLED_DrawPoint(uint8_t x,uint8_t y);   //����һ���㣨��Ҫ�����Դ棩
void OLED_DrawLine(uint8_t x1,uint8_t y1,uint8_t x2,uint8_t y2);   //����
void OLED_ShowChar(uint8_t x,uint8_t y,uint8_t chr,uint8_t size1);//��ʾ��ĸ
void OLED_ShowString(uint8_t x,uint8_t y,uint8_t *chr,uint8_t size1);//��ʾ�ַ���
void OLED_ShowStringPro(uint8_t x,uint8_t y,char* chr,uint8_t size1);//��ʾ�ַ���
void OLED_ShowNum(uint8_t x,uint8_t y,uint32_t num,uint8_t len,uint8_t size1);//��ʾ����
void OLED_ShowChinese(uint8_t x,uint8_t y,uint8_t num,uint8_t size1);  //��ʾ����
void OLED_WR_BP(uint8_t x,uint8_t y);//
void OLED_ShowPicture(uint8_t x0,uint8_t y0,uint8_t x1,uint8_t y1,uint8_t BMP[]);//��ʾͼƬ
void OLED_Init(void);//OLED��ʼ��
void OLED_ShowData_String(uint8_t x, uint8_t y,uint8_t char_size ,const char* fmt,...);//
void OLED_show_light(uint32_t light_level);//
#endif
