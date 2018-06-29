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

	angle1 = 0;			// 처음 서보 모터 각도
	angle2 = 180;	// 변경 서보 모터 각도
	
	Motor_Init();
		
	AF_ConfigPin(GPIO_PORT_3,PINSEL_PIN_25,PINSEL_FUNC_3);	//	PWM1.2
		
	PWMTimerSetup.PrescaleOption = PWM_TIMER_PRESCALE_USVAL;	//	us(microsecond) 기준으로 Prescale 설정
	PWMTimerSetup.PrescaleValue = 1;
	
	PWM_Init(LPC_PWM1, PWM_MODE_TIMER, (void *) &PWMTimerSetup);
	
	PWM_MatchUpdate(LPC_PWM1, 0, 20000, PWM_MATCH_UPDATE_NOW);
	PWMMatchSetup.IntOnMatch = ENABLE;
	PWMMatchSetup.MatchChannel = 0;
	PWMMatchSetup.ResetOnMatch = ENABLE;
	PWMMatchSetup.StopOnMatch = DISABLE;
	PWM_ConfigMatch(LPC_PWM1, &PWMMatchSetup);

	PWM_ChannelConfig(LPC_PWM1, 2, PWM_CHANNEL_SINGLE_EDGE);	// PWM Timer 2 Channel SINGLE_EDGE MODE
	
	PWMMatchSetup.IntOnMatch = DISABLE;	// Timer 일치했을 때 Interrupt 발생 여부 
	PWMMatchSetup.MatchChannel = 2;	//	채널 선택
	PWMMatchSetup.ResetOnMatch = DISABLE;	//	Timer 일치했을 때 Reset 여부
	PWMMatchSetup.StopOnMatch = DISABLE;		//	Timer 일치했을 때 Stop 여부
	PWM_ConfigMatch(LPC_PWM1, &PWMMatchSetup);	// 설정 적용 

	/* Enable PWM interrupt */
	NVIC_EnableIRQ(PWM1_IRQn);
		
	PWM_ChannelCmd(LPC_PWM1, 2, ENABLE);	// PWM 2 채널 활성화

	PWM_ResetCounter(LPC_PWM1);	//	Counter 초기화 
	PWM_CounterCmd(LPC_PWM1, ENABLE);	//	Counter Start
	
  while(1)
  {
		if(count == 100)
		{
			PWM_MatchUpdate(LPC_PWM1, 2, 600 + (10 * angle1), PWM_MATCH_UPDATE_NEXT_RST); 
			// 서보모터 각도를 -90도로 제어하기 위해 Pulse 길이를 600usec으로 설정
		}
		else if(count == 200)
		{
			PWM_MatchUpdate(LPC_PWM1, 2, 600 + (10 * angle2), PWM_MATCH_UPDATE_NEXT_RST);
      // 서보모터 각도를 +90도로 제어하기 위해 Pulse 길이를 2400usec으로 설정
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
		PWM_ClearIntPending(LPC_PWM1, PWM_INTSTAT_MR0);		// Interrupt 정보를 클리어 하여 다시 대기 상태로 바꾼다.
	}
}
