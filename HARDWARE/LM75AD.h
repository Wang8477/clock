#ifndef __LM75AD_H
#define __LM75AD_H	 
#include "main.h"
#define LM75AD_ADDR 0x90   //Ä¬ÈÏµØÖ·0x90
 
void LM75AD_Init(void);
void LM75_Temp(uint8_t *temp);
double LM75AD_GetTemp(void);
		 				    
#endif

