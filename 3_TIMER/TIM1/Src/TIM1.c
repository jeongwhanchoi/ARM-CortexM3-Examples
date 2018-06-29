/******************************************************************************
  * @file  TIM1.c
  * @author  Huins Embbeded Team  by HyunKH
  * @version V1.0.0
  * @date    2015. 02. 04
  * @brief   Timer Control
  ******************************************************************************/

/* Includes ------------------------------------------------------------------*/
#include "lpc17xx_timer.h"
#include "LPC1768_utility.h"

/* Private variables ---------------------------------------------------------*/
uint8_t Led_Status = 0;

/* Private function ---------------------------------------------------------*/
void TIMER0_Config(void);

/* Private struct ---------------------------------------------------------*/
TIM_TIMERCFG_Type TIM_ConfigStruct;
TIM_MATCHCFG_Type TIM_MatchConfigStruct ;

int main(void)
{
	Led_Init(LED_ALL);	//	LED 전체 초기화

	TIMER0_Config();	//	Timer 번 설정 함수

	TIM_Init(LPC_TIM0, TIM_TIMER_MODE,&TIM_ConfigStruct);	//  TIM_ConfigStruct 설정 적용
	TIM_ConfigMatch(LPC_TIM0,&TIM_MatchConfigStruct);		// TIM_MatchConfigStruct 설정 적용
	NVIC_EnableIRQ(TIMER0_IRQn);	//	TIMER0 Interrupt 활성화
	TIM_Cmd(LPC_TIM0, ENABLE);	//	Timer Start

	while(1)
	{
		if(Led_Status > 9)
		{
			Led_All_Off();
			Led_Status = 1;	// LED 위치 1번으로 변경
		}
	}
}

// Interrupt Reqeust Timer 일치할 때 진입
void TIMER0_IRQHandler(void)
{
	TIM_ClearIntPending(LPC_TIM0, TIM_MR0_INT); //TIM0 interrupt clear
	Led_On(Led_Status);
	Led_Status++;
}

void TIMER0_Config(void)
{
	TIM_ConfigStruct.PrescaleOption = TIM_PRESCALE_USVAL;	//	us(microsecond) 기준으로 Prescale 설정
	TIM_ConfigStruct.PrescaleValue	= 100;	//	100us
	TIM_MatchConfigStruct.MatchChannel = 0;	//	0번 채널 사용
	TIM_MatchConfigStruct.IntOnMatch = ENABLE;	//	Timer가 일치할 때  Interrupt 발생 Enable
	TIM_MatchConfigStruct.ResetOnMatch = ENABLE;	//	Timer가 일치할 때  Reset Enable
	TIM_MatchConfigStruct.StopOnMatch = DISABLE;	//	Timer가 일치할 때 Timer Stop Disable
	TIM_MatchConfigStruct.ExtMatchOutputType = TIM_EXTMATCH_NOTHING;	//	Timer 일치할때 아무런 외부 출력 하지 않음 (외부로 출력하지 않기 때문에 GPIO를 설정하지 않아도 됨.)
	TIM_MatchConfigStruct.MatchValue = 10000;	// Timer 일치 값 설정 100us * 10000번 = 1초
}
