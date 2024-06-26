#ifndef __OLED_H
#define __OLED_H 
 
#include "main.h"
#include "stm32f4xx_hal.h"
#include "stdlib.h"
#include "stdio.h"

//定义亮度变量类型
typedef enum
{
	LIGHT_HIGH=1,
	LIGHT_MID,
	LIGHT_LOW,
}LIGHT_LEVEL;
//-----------------OLED端口定义---------------- 
 
 
#define OLED_RES_Clr() HAL_GPIO_WritePin(OLED_RES_GPIO_Port,OLED_RES_Pin,GPIO_PIN_RESET)//RES
#define OLED_RES_Set() HAL_GPIO_WritePin(OLED_RES_GPIO_Port,OLED_RES_Pin,GPIO_PIN_SET)
 
#define OLED_DC_Clr() HAL_GPIO_WritePin(OLED_DC_GPIO_Port,OLED_DC_Pin,GPIO_PIN_RESET)//DC
#define OLED_DC_Set() HAL_GPIO_WritePin(OLED_DC_GPIO_Port,OLED_DC_Pin,GPIO_PIN_SET)
 		     
#define OLED_CS_Clr()  HAL_GPIO_WritePin(OLED_CS_GPIO_Port,OLED_CS_Pin,GPIO_PIN_RESET)//CS
#define OLED_CS_Set()  HAL_GPIO_WritePin(OLED_CS_GPIO_Port,OLED_CS_Pin,GPIO_PIN_SET)
 
#define OLED_CMD  0	//写命令
#define OLED_DATA 1	//写数据
 
#define uint8_t unsigned char
#define uint32_t unsigned int
#define WHICH_SPI &hspi1//根据使用的SPI更改
 
void OLED_ClearPoint(uint8_t x,uint8_t y);   //去掉点
void OLED_ColorTurn(uint8_t i);   //改变颜色
void OLED_DisplayTurn(uint8_t i); //
void OLED_WR_Byte(uint8_t dat,uint8_t cmd);   //写入一个字节
void OLED_DisPlay_On(void);   //开启显示
void OLED_DisPlay_Off(void);  //关闭显示
void OLED_Refresh(void);  //更新OLED显存
void OLED_Clear(void);  //清屏
void OLED_DrawPoint(uint8_t x,uint8_t y);   //加上一个点（需要更新显存）
void OLED_DrawLine(uint8_t x1,uint8_t y1,uint8_t x2,uint8_t y2);   //画线
void OLED_ShowChar(uint8_t x,uint8_t y,uint8_t chr,uint8_t size1);//显示字母
void OLED_ShowString(uint8_t x,uint8_t y,uint8_t *chr,uint8_t size1);//显示字符串
void OLED_ShowStringPro(uint8_t x,uint8_t y,char* chr,uint8_t size1);//显示字符串
void OLED_ShowNum(uint8_t x,uint8_t y,uint32_t num,uint8_t len,uint8_t size1);//显示数字
void OLED_ShowChinese(uint8_t x,uint8_t y,uint8_t num,uint8_t size1);  //显示中文
void OLED_WR_BP(uint8_t x,uint8_t y);//
void OLED_ShowPicture(uint8_t x0,uint8_t y0,uint8_t x1,uint8_t y1,uint8_t BMP[]);//显示图片
void OLED_Init(void);//OLED初始化
void OLED_ShowData_String(uint8_t x, uint8_t y,uint8_t char_size ,const char* fmt,...);//
void OLED_show_light(uint32_t light_level);//
#endif
