/******************************************************************************
  * @file  adc_interrupt.c
  * @author  Huins Embbeded Team  by HyunKH
  * @version V1.0.0
  * @date    2015. 02. 06
  * @brief   ADC Interrupt
  ******************************************************************************/

/* Includes ------------------------------------------------------------------*/
#include "lpc17xx_adc.h"
#include "LPC1768_utility.h"
#include "debug_frmwrk.h"

uint16_t adc_value;	

int main(void)
{
	/* UART0 Start �޼���*/
	uint8_t menu1[] =
	"********************************************************************\n\r"
	"\t Hello - Huins Embbeded Team \r\n"
	"\t UART0 Init / ADC Interrupt Example\r\n"
	"\t - MCU: LPC1768 \r\n"
	"\t - Communicate via: UART0 - 115200 bps \r\n"
	"********************************************************************\n\r";

	Uart0_Init();	// UART 0�� �ʱ�ȭ
	
	UARTPuts(LPC_UART0,menu1); // UART0(RS232)�� �޼��� ���

	AF_ConfigPin(GPIO_PORT_0,	PINSEL_PIN_25,PINSEL_FUNC_1);	// P0.25 Pin AF Configuration (ADC - 2 Channel)

	ADC_Init(LPC_ADC, 200000); //ADC initialization, ADC Rate -> 200kHz (����)
	ADC_IntConfig(LPC_ADC,ADC_ADINTEN2,ENABLE); //ADC 2ä�� Interrupt ����
	ADC_ChannelCmd(LPC_ADC,ADC_CHANNEL_2,ENABLE); //	ADC 2 channel Ȱ��ȭ
	NVIC_EnableIRQ(ADC_IRQn); //ADC interrupt Ȱ��ȭ
	while(1)
	{
		ADC_StartCmd(LPC_ADC,ADC_START_NOW);	// 1ȸ ADC ��ȯ (��� Restart)
		UARTPuts(LPC_UART0,"ADC value on channel 2: ");	//	UART0(RS232)�� �޼��� ���
		UARTPutDec16(LPC_UART0,adc_value);	// UART0(RS232)�� adc_value �� ���
		UARTPuts(LPC_UART0,"\r\n");	//	UART0(RS232)�� ���ΰ��� �޼��� ���
		Delay(SEC_1);	// Dealy 1 Sec
	}
}

// ADC Interrupt Reqest 
void ADC_IRQHandler(void)
{
	if (ADC_ChannelGetStatus(LPC_ADC,ADC_CHANNEL_2,ADC_DATA_DONE)) // ADC 2 Channel Ȱ��ȭ ���� Ȯ��
	{	
		ADC_ChannelCmd(LPC_ADC,ADC_CHANNEL_2,DISABLE); //	ADC 2 channel Ȱ��ȭ
		adc_value =  ADC_ChannelGetData(LPC_ADC,ADC_CHANNEL_2);	//	ADC 2 Channel�� ���� �о�� adc_value�� ����
		NVIC_DisableIRQ(ADC_IRQn);	// Interrupt ��Ȱ��ȭ (Interrupt Pending ����)
		NVIC_EnableIRQ(ADC_IRQn); // ADC Interrupt Ȱ��ȭ
		ADC_ChannelCmd(LPC_ADC,ADC_CHANNEL_2,ENABLE); //	ADC 2 channel Ȱ��ȭ
	}
}

