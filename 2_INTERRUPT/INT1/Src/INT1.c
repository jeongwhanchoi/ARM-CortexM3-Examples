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
uint8_t Led_Count = 1;  // 현재 LED 
	
int main (void) 
{
	EXTI_Init();	// EXTI 초기화
	Led_Init(LED_ALL); // LED 전체 초기화 
	AF_ConfigPin(GPIO_PORT_2, PINSEL_PIN_10, PINSEL_FUNC_1);	// 단순 GPIO 기능이 아닌 Alternate Function을 사용하기 위해 설정
	EXTI_ConfigPin(EXTI_EINT0); // EXTI0 설정
	NVIC_EnableIRQ(EINT0_IRQn); // EXTI0 활성화
	
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

// Interrupt Request   버튼을 누르면 진입
void EINT0_IRQHandler(void)
{
	EXTI_ClearEXTIFlag(EXTI_EINT0);	// Interrupt 정보를 클리어 하여 다시 대기 상태로 바꾼다.
	Led_Count++;	//	LED 증가
	Led_All_Off();	//	모든 LED Off
}

