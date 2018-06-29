/******************************************************************************
  * @file  GPIO1.c
  * @author  Huins Embbeded Team  by HyunKH
  * @version V1.0.0
  * @date    2015. 02. 03
  * @brief   GPIO LED Control   
  ******************************************************************************/

/* Includes ------------------------------------------------------------------*/
#include "LPC1768_utility.h"

int main (void) 
{
	uint8_t Led_Count = 0;  // 현재 LED
	uint8_t Led_Status = 0; // LED 증 / 감 상태
	
	Led_Init(LED_ALL); // LED 전체 초기화 

	while(1)
	{
		if(Led_Count == 1)	Led_Status = 0;  //	1번째 LED에 도달하면 Led_Status를 변경하여 증가 Loop 진입
		if(Led_Count == 8)	Led_Status = 1;	// 8번째 LED에 도달하면 Led_Status를 변경하여 감소 Loop 진입

		if(Led_Status == 1)		//	8번째 LED 부터 감소
		{ 
			Led_Count--;
			Led_On(Led_Count);		// 해당 LED를 On
			Delay(SEC_1/2);					// Delay 1 sec / 2 = 0.5 sec
			Led_Off(Led_Count);		// 해당 LED를 Off
		}
    else if(Led_Status == 0)	// 1번째 LED 부터 증가
		{
			Led_Count++;
			Led_On(Led_Count);		// 해당 LED를 On
			Delay(SEC_1/2);					// Delay 1 sec / 2 = 0.5 sec
			Led_Off(Led_Count);		// 해당 LED를 Off
		}
  }
}
