/******************************************************************************
  * @file  MCPWM.c
  * @author  Huins Embbeded Team  by HyunKH
  * @version V1.0.0
  * @date    2015. 02. 04
  * @brief   PWM Control 
  ******************************************************************************/

/* Includes ------------------------------------------------------------------*/
#include "LPC1768_utility.h"
#include "lpc17xx_pwm.h"


int main(void)
{
	PWM_TIMERCFG_Type	PWMTimerSetup;
	PWM_MATCHCFG_Type PWMMatchSetup;
	
	Led_Init(LED_ALL); // LED 전체 초기화
	
	// 단순 GPIO 기능이 아닌 Alternate Function을 사용하기 위해 설정
	AF_ConfigPin(GPIO_PORT_2, PINSEL_PIN_2, PINSEL_FUNC_1);  // P1.20 PWM 2.2  Alternate Fucntion으로 설정
	AF_ConfigPin(GPIO_PORT_2, PINSEL_PIN_3, PINSEL_FUNC_1);  // P1.21 PWM 2.3  Alternate Fucntion으로 설정
	AF_ConfigPin(GPIO_PORT_2, PINSEL_PIN_4, PINSEL_FUNC_1);  // P1.23 PWM 2.4  Alternate Fucntion으로 설정
	AF_ConfigPin(GPIO_PORT_2, PINSEL_PIN_5, PINSEL_FUNC_1);  // P1.24 PWM 2.5  Alternate Fucntion으로 설정
	
	PWMTimerSetup.PrescaleOption = PWM_TIMER_PRESCALE_USVAL;	//	us(microsecond) 기준으로 Prescale 설정
	PWMTimerSetup.PrescaleValue = 1; // 1us
	
	PWM_Init(LPC_PWM1, PWM_MODE_TIMER, (void *) &PWMTimerSetup);	

	PWM_MatchUpdate(LPC_PWM1, 0, 500, PWM_MATCH_UPDATE_NOW);
	PWMMatchSetup.IntOnMatch = DISABLE;
	PWMMatchSetup.MatchChannel = 0;
	PWMMatchSetup.ResetOnMatch = ENABLE;
	PWMMatchSetup.StopOnMatch = DISABLE;
	PWM_ConfigMatch(LPC_PWM1, &PWMMatchSetup);
	
	PWM_ChannelConfig(LPC_PWM1, 3, PWM_CHANNEL_SINGLE_EDGE);	// PWM Timer 3 Channel SINGLE_EDGE MODE
	PWM_ChannelConfig(LPC_PWM1, 4, PWM_CHANNEL_SINGLE_EDGE);	// PWM Timer 4 Channel SINGLE_EDGE MODE
	PWM_ChannelConfig(LPC_PWM1, 5, PWM_CHANNEL_SINGLE_EDGE);	// PWM Timer 5 Channel SINGLE_EDGE MODE
	PWM_ChannelConfig(LPC_PWM1, 6, PWM_CHANNEL_SINGLE_EDGE);	// PWM Timer 6 Channel SINGLE_EDGE MODE

	PWM_MatchUpdate(LPC_PWM1, 3, 	50, PWM_MATCH_UPDATE_NOW);
	PWM_MatchUpdate(LPC_PWM1, 4, 150, PWM_MATCH_UPDATE_NOW);
	PWM_MatchUpdate(LPC_PWM1, 5, 250, PWM_MATCH_UPDATE_NOW);
	PWM_MatchUpdate(LPC_PWM1, 6, 350, PWM_MATCH_UPDATE_NOW);
	
	PWMMatchSetup.IntOnMatch = DISABLE;	// Timer 일치했을 때 Interrupt 발생 여부 
	PWMMatchSetup.MatchChannel = 3;	//	채널 선택
	PWMMatchSetup.ResetOnMatch = DISABLE;	//	Timer 일치했을 때 Reset 여부
	PWMMatchSetup.StopOnMatch = DISABLE;		//	Timer 일치했을 때 Stop 여부
	PWM_ConfigMatch(LPC_PWM1, &PWMMatchSetup);	// 설정 적용 

	//	다른 Channel 항목만 바꾼 후 설정 적용
	PWMMatchSetup.MatchChannel = 4;
	PWM_ConfigMatch(LPC_PWM1, &PWMMatchSetup);

	//	다른 Channel 항목만 바꾼 후 설정 적용
	PWMMatchSetup.MatchChannel = 5;
	PWM_ConfigMatch(LPC_PWM1, &PWMMatchSetup);
	
	//	다른 Channel 항목만 바꾼 후 설정 적용
	PWMMatchSetup.MatchChannel = 6;
	PWM_ConfigMatch(LPC_PWM1, &PWMMatchSetup);

	PWM_ChannelCmd(LPC_PWM1, 3, ENABLE);	// PWM 3 채널 활성화
	PWM_ChannelCmd(LPC_PWM1, 4, ENABLE);	// PWM 4 채널 활성화
	PWM_ChannelCmd(LPC_PWM1, 5, ENABLE);	// PWM 5 채널 활성화
	PWM_ChannelCmd(LPC_PWM1, 6, ENABLE);	// PWM 6 채널 활성화
	
 	PWM_ResetCounter(LPC_PWM1);	//	Counter 초기화 
	PWM_CounterCmd(LPC_PWM1, ENABLE);	//	Counter Start

	while(1)
	{	
	}
}
