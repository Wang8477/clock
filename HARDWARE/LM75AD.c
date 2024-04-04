#include "LM75AD.h"
extern I2C_HandleTypeDef hi2c1;//IIC1句柄
//#include "IIC.h"
 
//	 
/*
0x00  Temperature Register      
0x01  Configuration register  器件模式 写00普通模式(100ms更新一次温度值) 写01为ShutDown模式
0x02  Hysteresis register
0x03  Over_temperature shutdown register
Temp Register 
MSByte                LSByte
7   6  5  4  3  2  1  0  7  6  5  4 3 2 1 0
D10 D9 D8 D7 D6 D5 D4 D3 D2 D1 D0 X X X X X
D10=0    ℃=+(Temp Data×0.125) 	
D10=1    ℃=-(Temp Data×0.125)
Address Table
MSB          LSB
1 0 0 1 A2 A1 A0
1 0 0 1 0  0  1 0/1       =0x92
*/
 
 
//LM75AD IO初始化
void LM75AD_Init(void)
{
		uint8_t *data;
	uint8_t iic_data = 0x00;
  data = &iic_data;
	HAL_I2C_Mem_Write(&hi2c1,LM75AD_ADDR,0x01,I2C_MEMADD_SIZE_8BIT,data,1,100);
//    I2C_WriteByte(0x01,0x00,LM75AD_ADDR);
}
 
//float LM75_Temp(void)
//{
//    float tempture;
//    int temp;
//    temp=I2C_ReadByte(0x00,LM75AD_ADDR,2);
//    tempture=temp>>5;
//    return tempture*0.125;	
//}
//温度获取函数
void LM75_Temp(uint8_t *temp)
{
	HAL_I2C_Mem_Read(&hi2c1,LM75AD_ADDR,0x00,I2C_MEMADD_SIZE_8BIT,temp,2,100);
}

//温度处理函数
double LM75AD_GetTemp(void)
{
	uint8_t temper[2]={0};
	double temperature;
    LM75_Temp(temper);
	if ((temper[0]>>7) == 0)  //0度以上
	{
		int tep = temper[0]*8;
		int tep_1 = temper[1];
		tep_1 = tep_1>>5;
		tep = tep+tep_1;
		temperature = tep*0.125;
	}
	if ((temper[0]>>7) == 1)  //0度以上
	{
		int tep = (temper[0]-128)*8;
		int tep_1 = temper[1];
		tep_1 = tep_1>>5;
		tep = tep+tep_1;
		temperature = tep*0.125;
	}
	return temperature;
}
