/******************************************************************************
  * @file  servo_motor.c
  * @author  Huins Embbeded Team  by HyunKH
  * @version V1.0.0
  * @date    2015. 02. 10
  * @brief   servo motor PWM Control
  ******************************************************************************/
 
/* Includes ------------------------------------------------------------------*/        
#include "LPC1768_motor.h"
#include "LPC1768_utility.h"
#include "lpc17xx_pwm.h"

/* Private function ---------------------------------------------------------*/
void PWM1_IRQHandler(void);

/* Private variable ---------------------------------------------------------*/
uint32_t count = 0;

int main (void)
{	  
	uint8_t angle1, angle2;

	PWM_TIMERCFG_Type	PWMTimerSetup;
	PWM_MATCHCFG_Type PWMMatchSetup;

	angle1 = 0;			// ó�� ���� ���� ����
	angle2 = 180;	// ���� ���� ���� ����
	
	Motor_Init();
		
	AF_ConfigPin(GPIO_PORT_3,PINSEL_PIN_25,PINSEL_FUNC_3);	//	PWM1.2
		
	PWMTimerSetup.PrescaleOption = PWM_TIMER_PRESCALE_USVAL;	//	us(microsecond) �������� Prescale ����
	PWMTimerSetup.PrescaleValue = 1;
	
	PWM_Init(LPC_PWM1, PWM_MODE_TIMER, (void *) &PWMTimerSetup);
	
	PWM_MatchUpdate(LPC_PWM1, 0, 20000, PWM_MATCH_UPDATE_NOW);
	PWMMatchSetup.IntOnMatch = ENABLE;
	PWMMatchSetup.MatchChannel = 0;
	PWMMatchSetup.ResetOnMatch = ENABLE;
	PWMMatchSetup.StopOnMatch = DISABLE;
	PWM_ConfigMatch(LPC_PWM1, &PWMMatchSetup);

	PWM_ChannelConfig(LPC_PWM1, 2, PWM_CHANNEL_SINGLE_EDGE);	// PWM Timer 2 Channel SINGLE_EDGE MODE
	
	PWMMatchSetup.IntOnMatch = DISABLE;	// Timer ��ġ���� �� Interrupt �߻� ���� 
	PWMMatchSetup.MatchChannel = 2;	//	ä�� ����
	PWMMatchSetup.ResetOnMatch = DISABLE;	//	Timer ��ġ���� �� Reset ����
	PWMMatchSetup.StopOnMatch = DISABLE;		//	Timer ��ġ���� �� Stop ����
	PWM_ConfigMatch(LPC_PWM1, &PWMMatchSetup);	// ���� ���� 

	/* Enable PWM interrupt */
	NVIC_EnableIRQ(PWM1_IRQn);
		
	PWM_ChannelCmd(LPC_PWM1, 2, ENABLE);	// PWM 2 ä�� Ȱ��ȭ

	PWM_ResetCounter(LPC_PWM1);	//	Counter �ʱ�ȭ 
	PWM_CounterCmd(LPC_PWM1, ENABLE);	//	Counter Start
	
  while(1)
  {
		if(count == 100)
		{
			PWM_MatchUpdate(LPC_PWM1, 2, 600 + (10 * angle1), PWM_MATCH_UPDATE_NEXT_RST); 
			// �������� ������ -90���� �����ϱ� ���� Pulse ���̸� 600usec���� ����
		}
		else if(count == 200)
		{
			PWM_MatchUpdate(LPC_PWM1, 2, 600 + (10 * angle2), PWM_MATCH_UPDATE_NEXT_RST);
      // �������� ������ +90���� �����ϱ� ���� Pulse ���̸� 2400usec���� ����
		}
	}
}

void PWM1_IRQHandler(void)
{
	if (PWM_GetIntStatus(LPC_PWM1, PWM_INTSTAT_MR0))	
	{
		if(count == 300)
		{
			count = 0;
		}
		count++;
		PWM_ClearIntPending(LPC_PWM1, PWM_INTSTAT_MR0);		// Interrupt ������ Ŭ���� �Ͽ� �ٽ� ��� ���·� �ٲ۴�.
	}
}
