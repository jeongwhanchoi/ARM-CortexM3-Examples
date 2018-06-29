/******************************************************************************
  * @file  PWM.c
  * @author  Huins Embbeded Team  by HyunKH
  * @version V1.0.0
  * @date    2015. 02. 04
  * @brief   PWM Interrupt 
  ******************************************************************************/

/* Includes ------------------------------------------------------------------*/
#include "LPC1768_utility.h"
#include "lpc17xx_pwm.h"

/* Private function ---------------------------------------------------------*/
void PWM1_IRQHandler(void);

int main(void)
{
	PWM_TIMERCFG_Type	PWMTimerSetup;
	PWM_MATCHCFG_Type PWMMatchSetup;
	
	Led_Init(LED_ALL); // LED 전체 초기화
	
	PWMTimerSetup.PrescaleOption = PWM_TIMER_PRESCALE_USVAL;	//	us(microsecond) 기준으로 Prescale 설정
	PWMTimerSetup.PrescaleValue = 100; // 100us
	
	PWM_Init(LPC_PWM1, PWM_MODE_TIMER, (void *) &PWMTimerSetup);	

	PWM_MatchUpdate(LPC_PWM1, 2, 10000, PWM_MATCH_UPDATE_NOW);	// PWM Timer 2 Channel Count 10000 번 후 Event 발생	
	PWM_MatchUpdate(LPC_PWM1, 3, 20000, PWM_MATCH_UPDATE_NOW);	// PWM Timer 2 Channel Count 20000 번 후 Event 발생
	PWM_MatchUpdate(LPC_PWM1, 4, 30000, PWM_MATCH_UPDATE_NOW);	// PWM Timer 2 Channel Count 30000 번 후 Event 발생
	PWM_MatchUpdate(LPC_PWM1, 5, 40000, PWM_MATCH_UPDATE_NOW);	// PWM Timer 2 Channel Count 40000 번 후 Event 발생
	
	PWMMatchSetup.IntOnMatch = ENABLE;	// Timer 일치했을 때 Interrupt 발생 여부 
	PWMMatchSetup.MatchChannel = 2;	//	채널 선택
	PWMMatchSetup.ResetOnMatch = DISABLE;	//	Timer 일치했을 때 Reset 여부
	PWMMatchSetup.StopOnMatch = DISABLE;		//	Timer 일치했을 때 Stop 여부
	PWM_ConfigMatch(LPC_PWM1, &PWMMatchSetup);	// 설정 적용 

	//	다른 Channel 항목만 바꾼 후 설정 적용
	PWMMatchSetup.MatchChannel = 3;
	PWM_ConfigMatch(LPC_PWM1, &PWMMatchSetup);

	//	다른 Channel 항목만 바꾼 후 설정 적용
	PWMMatchSetup.MatchChannel = 4;
	PWM_ConfigMatch(LPC_PWM1, &PWMMatchSetup);
	
	//	다른 Channel 항목만 바꾼 후 설정 적용 (5 Channel Interrupt 발생 했을 때 Reset 설정)	
	PWMMatchSetup.MatchChannel = 5;
	PWMMatchSetup.ResetOnMatch = ENABLE;
	PWM_ConfigMatch(LPC_PWM1, &PWMMatchSetup);
	
 	NVIC_EnableIRQ(PWM1_IRQn);	// PWM1_IRQ Interrupt Enable
	
 	PWM_ResetCounter(LPC_PWM1);	//	Counter 초기화 
	PWM_CounterCmd(LPC_PWM1, ENABLE);	//	Counter Start
 
	while(1)
	{	
	}
}


// Interrupt Request  Timer 일치했을 때 진입
void PWM1_IRQHandler(void)
{
	// 몇번 채널 Interrupt 발생했는지 구별 
	if (PWM_GetIntStatus(LPC_PWM1, PWM_INTSTAT_MR2))	
	{
		// 해당 Interrupt 채널에 맞춰 LED가 켜짐
		Led_On(LED2);
		Led_Off(LED5);
		PWM_ClearIntPending(LPC_PWM1, PWM_INTSTAT_MR2);		// Interrupt 정보를 클리어 하여 다시 대기 상태로 바꾼다.
	}
	if (PWM_GetIntStatus(LPC_PWM1, PWM_INTSTAT_MR3))
	{		
		Led_On(LED3);
		Led_Off(LED2);
		PWM_ClearIntPending(LPC_PWM1, PWM_INTSTAT_MR3);	
	}
	if (PWM_GetIntStatus(LPC_PWM1, PWM_INTSTAT_MR4))
	{
		Led_On(LED4);
		Led_Off(LED3);
		PWM_ClearIntPending(LPC_PWM1, PWM_INTSTAT_MR4);	
	}
	if (PWM_GetIntStatus(LPC_PWM1, PWM_INTSTAT_MR5))
	{
		Led_On(LED5);
		Led_Off(LED4);
		PWM_ClearIntPending(LPC_PWM1, PWM_INTSTAT_MR5);	
	}
}
