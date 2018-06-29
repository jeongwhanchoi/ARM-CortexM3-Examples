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
	uint8_t Led_Count = 0;  // ���� LED
	uint8_t Led_Status = 0; // LED �� / �� ����
	
	Led_Init(LED_ALL); // LED ��ü �ʱ�ȭ 

	while(1)
	{
		if(Led_Count == 1)	Led_Status = 0;  //	1��° LED�� �����ϸ� Led_Status�� �����Ͽ� ���� Loop ����
		if(Led_Count == 8)	Led_Status = 1;	// 8��° LED�� �����ϸ� Led_Status�� �����Ͽ� ���� Loop ����

		if(Led_Status == 1)		//	8��° LED ���� ����
		{ 
			Led_Count--;
			Led_On(Led_Count);		// �ش� LED�� On
			Delay(SEC_1/2);					// Delay 1 sec / 2 = 0.5 sec
			Led_Off(Led_Count);		// �ش� LED�� Off
		}
    else if(Led_Status == 0)	// 1��° LED ���� ����
		{
			Led_Count++;
			Led_On(Led_Count);		// �ش� LED�� On
			Delay(SEC_1/2);					// Delay 1 sec / 2 = 0.5 sec
			Led_Off(Led_Count);		// �ش� LED�� Off
		}
  }
}
