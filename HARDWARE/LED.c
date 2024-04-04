/************************************************************
*模块名称:指示灯驱动模块
*文件名  :LED.c
*说明    :C文件，提供用户自定义数据类型、宏和变量的定义以及接口函数的实现
*版本号  :V1.0
*修改记录:
*************************************************************/
/************************************************************
									本模块包含的头文件
************************************************************/
#include "LED.h"
/************************************************************
							本模块的数据类型、宏和变量的定义
************************************************************/
//定义指示灯对象数类型，采用结构体类型实现
typedef struct 
{
	GPIO_TypeDef *Port;    //端口号
	uint16_t     Pin;      //引脚号
	LED_DRIVE    Level;    //驱动方式
}LED_TypeDef;
//指示灯数量的宏定义，默认8
#define LEDn   8
//定义指示灯对象数组，用于存放每一个指示灯的属性，初始值为0
static LED_TypeDef Leds[LEDn]={0};
/************************************************************
*函数名称 BSP_LED_Config
*函数功能 配置指定指示灯的硬件信息
*入口参数 num   :待配置的指示灯编号, 取值范围 LED0 ~ LED7
*        port  :指示灯控制引脚的端口号,取值范围 GPIOA ~ GPIOI
*        pin   :指示灯控制引脚的引脚号,取值范围 GPIO_PIN_0 ~ GPIO_PIN_15
*        level :指示灯驱动方式,取值范围 LOW_LEVEL 或者 HIGH_LEVEL
*返回值 无
*注意事项 该函数一次只能配置一个指示灯，配置多个指示灯，需要重复调用
************************************************************/
void BSP_LED_Config( LED_INDEX num, GPIO_TypeDef* port, uint16_t pin, LED_DRIVE level)
{
// 配置指示灯的属性：端口号、引脚号以及驱动方式
 Leds[num]. Port = port;
 Leds[num]. Pin = pin;
 Leds[num]. Level = level;
}
/************************************************************
*函数名称 BSP_LED_On
*函数功能 开启指定的指示灯
*入口参数 num   :指示灯编号, 取值范围 LED0 ~LED7
*返回值 无
*注意事项 无
************************************************************/
void BSP_LED_On(LED_INDEX num)
{
 if( Leds[num]. Level == HIGH_LEVEL) // 高电平驱动
 {
 HAL_GPIO_WritePin( Leds[num]. Port, Leds[num]. Pin, GPIO_PIN_SET );
 }
 else // 低电平驱动
 {
 HAL_GPIO_WritePin( Leds[num]. Port, Leds[num]. Pin, GPIO_PIN_RESET );
 }
}
/************************************************************
*函数名称 BSP_LED_Off
*函数功能 关闭指定的指示灯
*入口参数 num   :指示灯编号, 取值范围 LED0 ~LED7
*返回值   无
*注意事项 无
************************************************************/
void BSP_LED_Off(LED_INDEX num)
{
 if( Leds[num]. Level == HIGH_LEVEL) // 高电平驱动
 {
 HAL_GPIO_WritePin( Leds[num]. Port, Leds[num]. Pin, GPIO_PIN_RESET );
 }
 else // 低电平驱动
 {
 HAL_GPIO_WritePin( Leds[num]. Port, Leds[num]. Pin, GPIO_PIN_SET );
 }
}
/************************************************************
*函数名称 BSP_LED_Toggle
*函数功能 翻转指定的指示灯
*入口参数 num   :指示灯编号, 取值范围 LED0 ~LED7
*返回值   无
*注意事项 无
************************************************************/
void BSP_LED_Toggle(LED_INDEX num)
{
 HAL_GPIO_TogglePin( Leds[num]. Port, Leds[num]. Pin );
}