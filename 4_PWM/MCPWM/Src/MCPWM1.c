/******************************************************************************
  * @file  MCPWM.c
  * @author  Huins Embbeded Team  by HyunKH
  * @version V1.0.0
  * @date    2015. 02. 09
  * @brief   MC(Motor Control) PWM Control - LED Dimming
  ******************************************************************************/
	
/* Includes ------------------------------------------------------------------*/
#include "lpc17xx_mcpwm.h"
#include "LPC1768_utility.h"

/* Private struct ---------------------------------------------------------*/
MCPWM_CHANNEL_CFG_Type PWMSetup;

/* Private function ---------------------------------------------------------*/
void MCPWM_Config(void);
void PWM_Update_Config(uint32_t Value);

/* Private variables ---------------------------------------------------------*/
uint32_t PWMValue = 0;
uint32_t PeriodValue = 300;

int main(void)
{
	Led_Init(LED_ALL);	//	LED 전체 초기화

	// 단순 GPIO 기능이 아닌 Alternate Function을 사용하기 위해 설정
	AF_ConfigPin(GPIO_PORT_1,PINSEL_PIN_28,PINSEL_FUNC_1);
	AF_ConfigPin(GPIO_PORT_1,PINSEL_PIN_29,PINSEL_FUNC_1);
	
	MCPWM_Config();	// MCPWM 설정
	MCPWM_Start(LPC_MCPWM, DISABLE, DISABLE, ENABLE); // PWM Start (0 ~ 2)   2번 채널만 ENABLE

	while(1)
	{	
		if(PWMValue == PeriodValue)
		{
			PWMValue = 0;	// 최대치에 도달하면 다시 0으로..
		}
		else
		{
			PWM_Update_Config(PWMValue);	// 현재 PWMValue를 update
			PWMValue++;
		}
		Delay(SEC_1/50);
	}
}

void MCPWM_Config(void)
{
	MCPWM_Init(LPC_MCPWM); //MCPWM initialization
	PWMSetup.channelType = MCPWM_CHANNEL_EDGE_MODE; // Edge 모드 사용
	PWMSetup.channelPolarity	= MCPWM_CHANNEL_PASSIVE_LO; //	Low 감지
	PWMSetup.channelDeadtimeEnable = DISABLE; //	DeadTime Disable
	PWMSetup.channelDeadtimeValue = 0; 
	PWMSetup.channelUpdateEnable = ENABLE; // 동작 설정 값 갱신 허용
	PWMSetup.channelTimercounterValue = 0; //	Timer Counter 시작 값
	PWMSetup.channelPeriodValue = PeriodValue; // 듀티비가 100%일때의 값
	PWMSetup.channelPulsewidthValue = PWMValue; // 현재 Pulse의 길이  -> ( 1 / PeriodValue) * PWMValue = 현재 듀티비
	MCPWM_ConfigChannel(LPC_MCPWM, 2, &PWMSetup); //Save MCPWM channel config parameter
}

void PWM_Update_Config(uint32_t Value)
{
		PWMSetup.channelPulsewidthValue = PWMValue; // PWMValue의 값을 수정하여 구조체에 저장
		MCPWM_WriteToShadow(LPC_MCPWM, 2, &PWMSetup); // 구조체 저장 값을 재적용 
}
