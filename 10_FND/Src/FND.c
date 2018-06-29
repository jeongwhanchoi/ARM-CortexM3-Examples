/******************************************************************************
  * @file  FND.c
  * @author  Huins Embbeded Team  by HyunKH
  * @version V1.0.0
  * @date    2015. 02. 10
  * @brief   FND Control (StopWatch)
  ******************************************************************************/

/* Includes ------------------------------------------------------------------*/           
#include "LPC1768_fnd.h"
#include "lpc17xx_timer.h"
#include "LPC1768_utility.h"

/* Private variables ---------------------------------------------------------*/
uint8_t time_10m =0 ;
uint8_t time_1m =0 ;
uint8_t time_10s = 0;
uint8_t time_1s = 0;

uint8_t lap_time_10m =0 ;
uint8_t lap_time_1m =0 ;
uint8_t lap_time_10s = 0;
uint8_t lap_time_1s = 0;

/* Private function ---------------------------------------------------------*/
void TIMER0_Config(void);

/* Private struct ---------------------------------------------------------*/
TIM_TIMERCFG_Type TIM_ConfigStruct;
TIM_MATCHCFG_Type TIM_MatchConfigStruct ;

int main (void)    /* Main Program */
{
	
	FND_Init();	// FND ��� PIN �ʱ�ȭ
	
	EXTI_Init();	// EXTI �ʱ�ȭ
	AF_ConfigPin(GPIO_PORT_2, PINSEL_PIN_10, PINSEL_FUNC_1);	// �ܼ� GPIO ����� �ƴ� Alternate Function�� ����ϱ� ���� ����
	EXTI_ConfigPin(EXTI_EINT0); // EXTI0 ����
	NVIC_EnableIRQ(EINT0_IRQn); // EXTI0 Ȱ��ȭ
	
	TIMER0_Config();
	TIM_Init(LPC_TIM0, TIM_TIMER_MODE,&TIM_ConfigStruct);	//  TIM_ConfigStruct ���� ����
	TIM_ConfigMatch(LPC_TIM0,&TIM_MatchConfigStruct);		// TIM_MatchConfigStruct ���� ����
	NVIC_EnableIRQ(TIMER0_IRQn);	//	TIMER0 Interrupt Ȱ��ȭ
	TIM_Cmd(LPC_TIM0, ENABLE);	//	Timer Start
	
  while(1) 
	{
		/* ���� Time ǥ�� */
		FND_COM_DATA_Select(8,time_1s);	// 8��°(������ �� ��) ���׸�Ʈ�� time_1s �� ǥ��
		Delay(5000);
		FND_COM_DATA_Select(7,time_10s);	
		Delay(5000);
		FND_COM_DATA_Select(6,time_1m);	
		Delay(5000);
		FND_COM_DATA_Select(5,time_10m);	
		Delay(5000);
		
		/* Lap Time ǥ�� */
		FND_COM_DATA_Select(4,lap_time_1s);	
		Delay(5000);
		FND_COM_DATA_Select(3,lap_time_10s);	
		Delay(5000);
		FND_COM_DATA_Select(2,lap_time_1m);	
		Delay(5000);
		FND_COM_DATA_Select(1,lap_time_10m);	
		Delay(5000);
	}
}


void TIMER0_IRQHandler(void)	// 1�ʿ� �ѹ� �� ����
{
	TIM_ClearIntPending(LPC_TIM0, TIM_MR0_INT); //TIM0 interrupt clear
	
	// �� : 1�� �ڸ� , 10�� �ڸ� / �� : 1�� �ڸ�, 10�� �ڸ�
	time_1s++;
	if(time_1s == 10)
	{
		time_10s++;
		time_1s=0;
	}
	if(time_10s == 6)
	{
		time_1m++;
		time_10s = 0;
	}
	if(time_1m == 10)
	{
		time_10m++;
		time_1m = 0;
	}	
	if(time_10m == 6)
	{
		time_10m =0 ;
		time_1m =0 ;
		time_10s = 0;
		time_1s = 0;
	}	
}

// INT ��ư�� ������ ����
void EINT0_IRQHandler(void)
{
	EXTI_ClearEXTIFlag(EXTI_EINT0);	// Interrupt ������ Ŭ���� �Ͽ� �ٽ� ��� ���·� �ٲ۴�.
	lap_time_10m = time_10m;	// ���� �ð� ���� 
	lap_time_1m = time_1m;
	lap_time_1s = time_1s;
	lap_time_10s = time_10s;
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
