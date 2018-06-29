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
	
	Led_Init(LED_ALL); // LED ��ü �ʱ�ȭ
	
	// �ܼ� GPIO ����� �ƴ� Alternate Function�� ����ϱ� ���� ����
	AF_ConfigPin(GPIO_PORT_2, PINSEL_PIN_2, PINSEL_FUNC_1);  // P1.20 PWM 2.2  Alternate Fucntion���� ����
	AF_ConfigPin(GPIO_PORT_2, PINSEL_PIN_3, PINSEL_FUNC_1);  // P1.21 PWM 2.3  Alternate Fucntion���� ����
	AF_ConfigPin(GPIO_PORT_2, PINSEL_PIN_4, PINSEL_FUNC_1);  // P1.23 PWM 2.4  Alternate Fucntion���� ����
	AF_ConfigPin(GPIO_PORT_2, PINSEL_PIN_5, PINSEL_FUNC_1);  // P1.24 PWM 2.5  Alternate Fucntion���� ����
	
	PWMTimerSetup.PrescaleOption = PWM_TIMER_PRESCALE_USVAL;	//	us(microsecond) �������� Prescale ����
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
	
	PWMMatchSetup.IntOnMatch = DISABLE;	// Timer ��ġ���� �� Interrupt �߻� ���� 
	PWMMatchSetup.MatchChannel = 3;	//	ä�� ����
	PWMMatchSetup.ResetOnMatch = DISABLE;	//	Timer ��ġ���� �� Reset ����
	PWMMatchSetup.StopOnMatch = DISABLE;		//	Timer ��ġ���� �� Stop ����
	PWM_ConfigMatch(LPC_PWM1, &PWMMatchSetup);	// ���� ���� 

	//	�ٸ� Channel �׸� �ٲ� �� ���� ����
	PWMMatchSetup.MatchChannel = 4;
	PWM_ConfigMatch(LPC_PWM1, &PWMMatchSetup);

	//	�ٸ� Channel �׸� �ٲ� �� ���� ����
	PWMMatchSetup.MatchChannel = 5;
	PWM_ConfigMatch(LPC_PWM1, &PWMMatchSetup);
	
	//	�ٸ� Channel �׸� �ٲ� �� ���� ����
	PWMMatchSetup.MatchChannel = 6;
	PWM_ConfigMatch(LPC_PWM1, &PWMMatchSetup);

	PWM_ChannelCmd(LPC_PWM1, 3, ENABLE);	// PWM 3 ä�� Ȱ��ȭ
	PWM_ChannelCmd(LPC_PWM1, 4, ENABLE);	// PWM 4 ä�� Ȱ��ȭ
	PWM_ChannelCmd(LPC_PWM1, 5, ENABLE);	// PWM 5 ä�� Ȱ��ȭ
	PWM_ChannelCmd(LPC_PWM1, 6, ENABLE);	// PWM 6 ä�� Ȱ��ȭ
	
 	PWM_ResetCounter(LPC_PWM1);	//	Counter �ʱ�ȭ 
	PWM_CounterCmd(LPC_PWM1, ENABLE);	//	Counter Start

	while(1)
	{	
	}
}
