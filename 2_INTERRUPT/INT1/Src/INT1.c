/******************************************************************************
  * @file  INT1.c
  * @author  Huins Embbeded Team  by HyunKH
  * @version V1.0.0
  * @date    2015. 02. 04
  * @brief   External Interrupt Control
  ******************************************************************************/

/* Includes ------------------------------------------------------------------*/
#include "LPC1768_utility.h"

/* Private variables ---------------------------------------------------------*/
uint8_t Led_Count = 1;  // ���� LED 
	
int main (void) 
{
	EXTI_Init();	// EXTI �ʱ�ȭ
	Led_Init(LED_ALL); // LED ��ü �ʱ�ȭ 
	AF_ConfigPin(GPIO_PORT_2, PINSEL_PIN_10, PINSEL_FUNC_1);	// �ܼ� GPIO ����� �ƴ� Alternate Function�� ����ϱ� ���� ����
	EXTI_ConfigPin(EXTI_EINT0); // EXTI0 ����
	NVIC_EnableIRQ(EINT0_IRQn); // EXTI0 Ȱ��ȭ
	
	while(1)
	{   	
		Delay(SEC_1/10);
		if(Led_Count	> 8)	//	LED8  -> LED1
		{
			Led_Count = 1;
		}
		Led_On(Led_Count);
  }
}

// Interrupt Request   ��ư�� ������ ����
void EINT0_IRQHandler(void)
{
	EXTI_ClearEXTIFlag(EXTI_EINT0);	// Interrupt ������ Ŭ���� �Ͽ� �ٽ� ��� ���·� �ٲ۴�.
	Led_Count++;	//	LED ����
	Led_All_Off();	//	��� LED Off
}

