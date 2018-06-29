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
	Led_Init(LED_ALL);	//	LED ��ü �ʱ�ȭ

	TIMER0_Config();	//	Timer �� ���� �Լ�

	TIM_Init(LPC_TIM0, TIM_TIMER_MODE,&TIM_ConfigStruct);	//  TIM_ConfigStruct ���� ����
	TIM_ConfigMatch(LPC_TIM0,&TIM_MatchConfigStruct);		// TIM_MatchConfigStruct ���� ����
	NVIC_EnableIRQ(TIMER0_IRQn);	//	TIMER0 Interrupt Ȱ��ȭ
	TIM_Cmd(LPC_TIM0, ENABLE);	//	Timer Start

	while(1)
	{
		if(Led_Status > 9)
		{
			Led_All_Off();
			Led_Status = 1;	// LED ��ġ 1������ ����
		}
	}
}

// Interrupt Reqeust Timer ��ġ�� �� ����
void TIMER0_IRQHandler(void)
{
	TIM_ClearIntPending(LPC_TIM0, TIM_MR0_INT); //TIM0 interrupt clear
	Led_On(Led_Status);
	Led_Status++;
}

void TIMER0_Config(void)
{
	TIM_ConfigStruct.PrescaleOption = TIM_PRESCALE_USVAL;	//	us(microsecond) �������� Prescale ����
	TIM_ConfigStruct.PrescaleValue	= 100;	//	100us
	TIM_MatchConfigStruct.MatchChannel = 0;	//	0�� ä�� ���
	TIM_MatchConfigStruct.IntOnMatch = ENABLE;	//	Timer�� ��ġ�� ��  Interrupt �߻� Enable
	TIM_MatchConfigStruct.ResetOnMatch = ENABLE;	//	Timer�� ��ġ�� ��  Reset Enable
	TIM_MatchConfigStruct.StopOnMatch = DISABLE;	//	Timer�� ��ġ�� �� Timer Stop Disable
	TIM_MatchConfigStruct.ExtMatchOutputType = TIM_EXTMATCH_NOTHING;	//	Timer ��ġ�Ҷ� �ƹ��� �ܺ� ��� ���� ���� (�ܺη� ������� �ʱ� ������ GPIO�� �������� �ʾƵ� ��.)
	TIM_MatchConfigStruct.MatchValue = 10000;	// Timer ��ġ �� ���� 100us * 10000�� = 1��
}
