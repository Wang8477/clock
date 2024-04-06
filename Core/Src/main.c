/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.c
  * @brief          : Main program body
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2024 STMicroelectronics.
  * All rights reserved.
  *
  * This software is licensed under terms that can be found in the LICENSE file
  * in the root directory of this software component.
  * If no LICENSE file comes with this software, it is provided AS-IS.
  *
  ******************************************************************************
  */
/* USER CODE END Header */
/* Includes ------------------------------------------------------------------*/
#include "main.h"
#include "adc.h"
#include "dma.h"
#include "i2c.h"
#include "spi.h"
#include "tim.h"
#include "gpio.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
#include "time.h"
#include "LED.h"
#include "LM75AD.h"
#include "MY_OLED.h"

/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN PTD */

/* USER CODE END PTD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */

/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */

/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/

/* USER CODE BEGIN PV */
double temperature=0;//�¶�
volatile  float voltage=0;
char buffer[100];		//�ַ���������
/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
/* USER CODE BEGIN PFP */

/* USER CODE END PFP */

/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */

struct Button btn1;
struct Button btn2;
struct Button btn3;
struct Button btn4;

/* USER CODE END 0 */

/**
  * @brief  The application entry point.
  * @retval int
  */
int main(void)
{

  /* USER CODE BEGIN 1 */

  /* USER CODE END 1 */

  /* MCU Configuration--------------------------------------------------------*/

  /* Reset of all peripherals, Initializes the Flash interface and the Systick. */
  HAL_Init();

  /* USER CODE BEGIN Init */

  /* USER CODE END Init */

  /* Configure the system clock */
  SystemClock_Config();

  /* USER CODE BEGIN SysInit */

  /* USER CODE END SysInit */

  /* Initialize all configured peripherals */
  MX_GPIO_Init();
  MX_DMA_Init();
  MX_ADC1_Init();
  MX_I2C1_Init();
  MX_SPI1_Init();
  MX_TIM10_Init();
  MX_TIM11_Init();
  /* USER CODE BEGIN 2 */
		__HAL_TIM_CLEAR_IT(&htim10,TIM_IT_UPDATE);//��ն�ʱ��10�жϱ�־����ʱ��
	HAL_TIM_Base_Start_IT(&htim10);//������ʱ��
	__HAL_TIM_CLEAR_IT(&htim11,TIM_IT_UPDATE);//��ն�ʱ��4�жϱ�־����ⰴ����
	HAL_TIM_Base_Start_IT(&htim11);//������ʱ��
	
	
	clock_init();                         //ʱ���ʼ��

	button_init(&btn1, read_button_GPIO, 0, 0);
	button_init(&btn2, read_button_GPIO, 0, 1);
	button_init(&btn3, read_button_GPIO, 0, 2);
	button_init(&btn4, read_button_GPIO, 0, 3);    //��ʼ������
	LM75AD_Init();																			//��ʼ���¶�
	OLED_Init();
	OLED_DisPlay_On();
	button_attach(&btn1, SINGLE_CLICK, BTN1_SINGLE_Click_Handler);
	button_attach(&btn2, PRESS_DOWN, BTN2_SINGLE_Click_Handler);
	button_attach(&btn3, SINGLE_CLICK, BTN3_SINGLE_Click_Handler);
	button_attach(&btn3, LONG_PRESS_START, BTN3_LONG_PRESS_START_Handler);
	button_attach(&btn4, PRESS_UP, BTN4_SINGLE_Click_Handler);
	button_start(&btn1);
	button_start(&btn2);
	button_start(&btn3);
	button_start(&btn4);

  /* USER CODE END 2 */

  /* Infinite loop */
  /* USER CODE BEGIN WHILE */
  while (1)
  {
    /* USER CODE END WHILE */

    /* USER CODE BEGIN 3 */
 /*****************��ȡ��ѹ************************/
		HAL_ADC_Start(&hadc1);	
		HAL_ADC_PollForConversion(&hadc1, 50);   //�ȴ�ת����ɣ�50Ϊ���ȴ�ʱ�䣬��λΪms
		if(HAL_IS_BIT_SET(HAL_ADC_GetState(&hadc1), HAL_ADC_STATE_REG_EOC))
		{
		voltage = HAL_ADC_GetValue(&hadc1)*3.3f/4096;   //��ȡADֵ
		}
/******************��ȡ�¶�************************/
		temperature = LM75AD_GetTemp();
/******************��ʾ��****************************/		
		if(setflag )
		{
			HAL_GPIO_WritePin (LED3_GPIO_Port ,LED3_Pin ,GPIO_PIN_SET );
			if(set==0)
			{HAL_GPIO_WritePin (LED0_GPIO_Port ,LED0_Pin ,GPIO_PIN_SET );
			HAL_GPIO_WritePin (LED1_GPIO_Port ,LED1_Pin ,GPIO_PIN_RESET );
			HAL_GPIO_WritePin (LED2_GPIO_Port ,LED2_Pin ,GPIO_PIN_RESET );}
			else if(set==1)
			{HAL_GPIO_WritePin (LED1_GPIO_Port ,LED1_Pin ,GPIO_PIN_SET );
			HAL_GPIO_WritePin (LED0_GPIO_Port ,LED0_Pin ,GPIO_PIN_RESET );
			HAL_GPIO_WritePin (LED2_GPIO_Port ,LED2_Pin ,GPIO_PIN_RESET );}
			else 
			{HAL_GPIO_WritePin (LED2_GPIO_Port ,LED2_Pin ,GPIO_PIN_SET );
			HAL_GPIO_WritePin (LED1_GPIO_Port ,LED1_Pin ,GPIO_PIN_RESET );
			HAL_GPIO_WritePin (LED0_GPIO_Port ,LED0_Pin ,GPIO_PIN_RESET );}
		}
		else 
		{	
			HAL_GPIO_WritePin (LED3_GPIO_Port ,LED3_Pin ,GPIO_PIN_RESET );
			HAL_GPIO_WritePin (LED0_GPIO_Port ,LED0_Pin ,GPIO_PIN_RESET );
			HAL_GPIO_WritePin (LED1_GPIO_Port ,LED1_Pin ,GPIO_PIN_RESET );
			HAL_GPIO_WritePin (LED2_GPIO_Port ,LED2_Pin ,GPIO_PIN_RESET );
		}
/********************������************************/
		if(clock.alarm_flag )
			{HAL_GPIO_WritePin (BEEP_GPIO_Port ,BEEP_Pin ,GPIO_PIN_SET);}
		else HAL_GPIO_WritePin (BEEP_GPIO_Port ,BEEP_Pin ,GPIO_PIN_RESET);
/*******************��ʾ��*************************/	
		OLED_Refresh();
		if(select==0 )
		{
			OLED_ShowChinese (0,0,27,16);
			OLED_ShowChinese (16,0,28,16);
		  sprintf(buffer,"%.2d",clock.time_hour);
			OLED_ShowStringPro(16,23,buffer,24);
			OLED_ShowStringPro(43,23,"_",16);
			sprintf(buffer,"%.2d",clock.time_minute);
			OLED_ShowStringPro(53,23,buffer,24);
			OLED_ShowStringPro(80,23,"_",16);
			sprintf(buffer,"%.2d",clock.time_second  );
			OLED_ShowStringPro(90,23,buffer,24);
		}
		else 
		{
			OLED_ShowChinese (0,0,31,16);
			OLED_ShowChinese (16,0,32,16);
			sprintf(buffer,"%.2d",clock.alarm_hour);
			OLED_ShowStringPro(16,23,buffer,24);
			OLED_ShowStringPro(43,23,"_",16);
			sprintf(buffer,"%.2d",clock.alarm_minute);
			OLED_ShowStringPro(53,23,buffer,24);
			OLED_ShowStringPro(80,23,"_",16);
			sprintf(buffer,"%.2d",clock.alarm_second  );
			OLED_ShowStringPro(90,23,buffer,24);
		}
		
		sprintf(buffer,"%.2f",voltage);
		OLED_ShowStringPro(25,49,buffer,16);
		OLED_ShowStringPro(10,49,"V:",16);//��ʾ��ѹ
		OLED_ShowStringPro(70,49,"T:",16);//��ʾ�¶�
		sprintf(buffer,"%.1f",temperature);
		OLED_ShowStringPro(85,49,buffer,16);
		OLED_ShowChinese (96,0,44,16);
		OLED_ShowChinese (112,0,45,16);
	
  }
  /* USER CODE END 3 */
}

/**
  * @brief System Clock Configuration
  * @retval None
  */
void SystemClock_Config(void)
{
  RCC_OscInitTypeDef RCC_OscInitStruct = {0};
  RCC_ClkInitTypeDef RCC_ClkInitStruct = {0};

  /** Configure the main internal regulator output voltage
  */
  __HAL_RCC_PWR_CLK_ENABLE();
  __HAL_PWR_VOLTAGESCALING_CONFIG(PWR_REGULATOR_VOLTAGE_SCALE1);

  /** Initializes the RCC Oscillators according to the specified parameters
  * in the RCC_OscInitTypeDef structure.
  */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSI;
  RCC_OscInitStruct.HSIState = RCC_HSI_ON;
  RCC_OscInitStruct.HSICalibrationValue = RCC_HSICALIBRATION_DEFAULT;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
  RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSI;
  RCC_OscInitStruct.PLL.PLLM = 8;
  RCC_OscInitStruct.PLL.PLLN = 100;
  RCC_OscInitStruct.PLL.PLLP = RCC_PLLP_DIV2;
  RCC_OscInitStruct.PLL.PLLQ = 4;
  if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
  {
    Error_Handler();
  }

  /** Initializes the CPU, AHB and APB buses clocks
  */
  RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK|RCC_CLOCKTYPE_SYSCLK
                              |RCC_CLOCKTYPE_PCLK1|RCC_CLOCKTYPE_PCLK2;
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV2;
  RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV1;

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_3) != HAL_OK)
  {
    Error_Handler();
  }
}

/* USER CODE BEGIN 4 */



/* USER CODE END 4 */

/**
  * @brief  This function is executed in case of error occurrence.
  * @retval None
  */
void Error_Handler(void)
{
  /* USER CODE BEGIN Error_Handler_Debug */
  /* User can add his own implementation to report the HAL error return state */
  __disable_irq();
  while (1)
  {
  }
  /* USER CODE END Error_Handler_Debug */
}

#ifdef  USE_FULL_ASSERT
/**
  * @brief  Reports the name of the source file and the source line number
  *         where the assert_param error has occurred.
  * @param  file: pointer to the source file name
  * @param  line: assert_param error line source number
  * @retval None
  */
void assert_failed(uint8_t *file, uint32_t line)
{
  /* USER CODE BEGIN 6 */
  /* User can add his own implementation to report the file name and line number,
     ex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */
  /* USER CODE END 6 */
}
#endif /* USE_FULL_ASSERT */
