/******************************************************************************
  * @file  LPC1768_motor.c
  * @author  Huins Embbeded Team  by HyunKH
  * @version V1.0.0
  * @date    2015. 02. 10
  * @brief   LPC1768 Servo Motor Driver	C File
  ******************************************************************************/

/* Includes ------------------------------------------------------------------- */
#include "LPC1768_motor.h"
#include "LPC1768_utility.h"
/**
  * @brief  Servo Motor Initialization
  * @param  None
  * @retval None
  */
void Motor_Init(void)
{
	GPIO_SetDir(GPIO_PORT_0,(1<<4)|(1<<5)|(1<<10)|(1<<11)|(1<<19)|(1<<20)|(1<<21)|(1<<23) |(1<<24),OUTPUT);
	GPIO_SetDir(GPIO_PORT_1,(1<<21),OUTPUT);
	GPIO_SetDir(GPIO_PORT_2,(1<<11)|(1<<12)|(1<<13),OUTPUT);
	GPIO_SetDir(GPIO_PORT_3,(1<<25)|(1<<26),OUTPUT);
}

void StepMotor_Cycle(uint8_t cycle)
{
	uint32_t count = 0;
	
		for(count = 0; count < cycle * 24; count++)
		{
			GPIO_SetValue(GPIO_PORT_0,GPIO_PIN_5);
			GPIO_ClearValue(GPIO_PORT_0,GPIO_PIN_10);
			GPIO_SetValue(GPIO_PORT_0,GPIO_PIN_23);
			GPIO_ClearValue(GPIO_PORT_0,GPIO_PIN_24);
			Delay(SEC_1/300);
	
			GPIO_ClearValue(GPIO_PORT_0,GPIO_PIN_5);
			GPIO_SetValue(GPIO_PORT_0,GPIO_PIN_10);
			GPIO_SetValue(GPIO_PORT_0,GPIO_PIN_23);
			GPIO_ClearValue(GPIO_PORT_0,GPIO_PIN_24);
			Delay(SEC_1/300);
		
			GPIO_ClearValue(GPIO_PORT_0,GPIO_PIN_5);
			GPIO_SetValue(GPIO_PORT_0,GPIO_PIN_10);
			GPIO_ClearValue(GPIO_PORT_0,GPIO_PIN_23);
			GPIO_SetValue(GPIO_PORT_0,GPIO_PIN_24);
			Delay(SEC_1/300);
		
			GPIO_SetValue(GPIO_PORT_0,GPIO_PIN_5);
			GPIO_ClearValue(GPIO_PORT_0,GPIO_PIN_10);
			GPIO_ClearValue(GPIO_PORT_0,GPIO_PIN_23);
			GPIO_SetValue(GPIO_PORT_0,GPIO_PIN_24);
			Delay(SEC_1/300);
		}
}
