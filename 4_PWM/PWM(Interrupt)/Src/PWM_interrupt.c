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
	
	Led_Init(LED_ALL); // LED ��ü �ʱ�ȭ
	
	PWMTimerSetup.PrescaleOption = PWM_TIMER_PRESCALE_USVAL;	//	us(microsecond) �������� Prescale ����
	PWMTimerSetup.PrescaleValue = 100; // 100us
	
	PWM_Init(LPC_PWM1, PWM_MODE_TIMER, (void *) &PWMTimerSetup);	

	PWM_MatchUpdate(LPC_PWM1, 2, 10000, PWM_MATCH_UPDATE_NOW);	// PWM Timer 2 Channel Count 10000 �� �� Event �߻�	
	PWM_MatchUpdate(LPC_PWM1, 3, 20000, PWM_MATCH_UPDATE_NOW);	// PWM Timer 2 Channel Count 20000 �� �� Event �߻�
	PWM_MatchUpdate(LPC_PWM1, 4, 30000, PWM_MATCH_UPDATE_NOW);	// PWM Timer 2 Channel Count 30000 �� �� Event �߻�
	PWM_MatchUpdate(LPC_PWM1, 5, 40000, PWM_MATCH_UPDATE_NOW);	// PWM Timer 2 Channel Count 40000 �� �� Event �߻�
	
	PWMMatchSetup.IntOnMatch = ENABLE;	// Timer ��ġ���� �� Interrupt �߻� ���� 
	PWMMatchSetup.MatchChannel = 2;	//	ä�� ����
	PWMMatchSetup.ResetOnMatch = DISABLE;	//	Timer ��ġ���� �� Reset ����
	PWMMatchSetup.StopOnMatch = DISABLE;		//	Timer ��ġ���� �� Stop ����
	PWM_ConfigMatch(LPC_PWM1, &PWMMatchSetup);	// ���� ���� 

	//	�ٸ� Channel �׸� �ٲ� �� ���� ����
	PWMMatchSetup.MatchChannel = 3;
	PWM_ConfigMatch(LPC_PWM1, &PWMMatchSetup);

	//	�ٸ� Channel �׸� �ٲ� �� ���� ����
	PWMMatchSetup.MatchChannel = 4;
	PWM_ConfigMatch(LPC_PWM1, &PWMMatchSetup);
	
	//	�ٸ� Channel �׸� �ٲ� �� ���� ���� (5 Channel Interrupt �߻� ���� �� Reset ����)	
	PWMMatchSetup.MatchChannel = 5;
	PWMMatchSetup.ResetOnMatch = ENABLE;
	PWM_ConfigMatch(LPC_PWM1, &PWMMatchSetup);
	
 	NVIC_EnableIRQ(PWM1_IRQn);	// PWM1_IRQ Interrupt Enable
	
 	PWM_ResetCounter(LPC_PWM1);	//	Counter �ʱ�ȭ 
	PWM_CounterCmd(LPC_PWM1, ENABLE);	//	Counter Start
 
	while(1)
	{	
	}
}


// Interrupt Request  Timer ��ġ���� �� ����
void PWM1_IRQHandler(void)
{
	// ��� ä�� Interrupt �߻��ߴ��� ���� 
	if (PWM_GetIntStatus(LPC_PWM1, PWM_INTSTAT_MR2))	
	{
		// �ش� Interrupt ä�ο� ���� LED�� ����
		Led_On(LED2);
		Led_Off(LED5);
		PWM_ClearIntPending(LPC_PWM1, PWM_INTSTAT_MR2);		// Interrupt ������ Ŭ���� �Ͽ� �ٽ� ��� ���·� �ٲ۴�.
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
