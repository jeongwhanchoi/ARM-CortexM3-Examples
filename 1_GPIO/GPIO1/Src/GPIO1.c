/******************************************************************************
  * @file  GPIO1.c
  * @author  Huins Embbeded Team  by HyunKH
  * @version V1.0.0
  * @date    2015. 02. 03
  * @brief   GPIO LED Control   
  ******************************************************************************/

/* Includes ------------------------------------------------------------------*/
#include "LPC1768_utility.h"

/**
  * @brief  Main program
  * @param  None
  * @retval None
  */
int main(void)
{	
	Led_Init(LED_ALL);	//	LED 전체 초기화
	
	while(1)
	{
		Led_All_On();
		
		Delay(SEC_1); // Delay 1 sec 
		
		Led_All_Off();		
		
		Delay(SEC_1); // Dealy 1 sec 
	}
}
