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
	Led_Init(LED_ALL);	//	LED ��ü �ʱ�ȭ

	// �ܼ� GPIO ����� �ƴ� Alternate Function�� ����ϱ� ���� ����
	AF_ConfigPin(GPIO_PORT_1,PINSEL_PIN_28,PINSEL_FUNC_1);
	AF_ConfigPin(GPIO_PORT_1,PINSEL_PIN_29,PINSEL_FUNC_1);
	
	MCPWM_Config();	// MCPWM ����
	MCPWM_Start(LPC_MCPWM, DISABLE, DISABLE, ENABLE); // PWM Start (0 ~ 2)   2�� ä�θ� ENABLE

	while(1)
	{	
		if(PWMValue == PeriodValue)
		{
			PWMValue = 0;	// �ִ�ġ�� �����ϸ� �ٽ� 0����..
		}
		else
		{
			PWM_Update_Config(PWMValue);	// ���� PWMValue�� update
			PWMValue++;
		}
		Delay(SEC_1/50);
	}
}

void MCPWM_Config(void)
{
	MCPWM_Init(LPC_MCPWM); //MCPWM initialization
	PWMSetup.channelType = MCPWM_CHANNEL_EDGE_MODE; // Edge ��� ���
	PWMSetup.channelPolarity	= MCPWM_CHANNEL_PASSIVE_LO; //	Low ����
	PWMSetup.channelDeadtimeEnable = DISABLE; //	DeadTime Disable
	PWMSetup.channelDeadtimeValue = 0; 
	PWMSetup.channelUpdateEnable = ENABLE; // ���� ���� �� ���� ���
	PWMSetup.channelTimercounterValue = 0; //	Timer Counter ���� ��
	PWMSetup.channelPeriodValue = PeriodValue; // ��Ƽ�� 100%�϶��� ��
	PWMSetup.channelPulsewidthValue = PWMValue; // ���� Pulse�� ����  -> ( 1 / PeriodValue) * PWMValue = ���� ��Ƽ��
	MCPWM_ConfigChannel(LPC_MCPWM, 2, &PWMSetup); //Save MCPWM channel config parameter
}

void PWM_Update_Config(uint32_t Value)
{
		PWMSetup.channelPulsewidthValue = PWMValue; // PWMValue�� ���� �����Ͽ� ����ü�� ����
		MCPWM_WriteToShadow(LPC_MCPWM, 2, &PWMSetup); // ����ü ���� ���� ������ 
}
