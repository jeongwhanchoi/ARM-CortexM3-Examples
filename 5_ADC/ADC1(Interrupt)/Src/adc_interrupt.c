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
	/* UART0 Start 메세지*/
	uint8_t menu1[] =
	"********************************************************************\n\r"
	"\t Hello - Huins Embbeded Team \r\n"
	"\t UART0 Init / ADC Interrupt Example\r\n"
	"\t - MCU: LPC1768 \r\n"
	"\t - Communicate via: UART0 - 115200 bps \r\n"
	"********************************************************************\n\r";

	Uart0_Init();	// UART 0번 초기화
	
	UARTPuts(LPC_UART0,menu1); // UART0(RS232)로 메세지 출력

	AF_ConfigPin(GPIO_PORT_0,	PINSEL_PIN_25,PINSEL_FUNC_1);	// P0.25 Pin AF Configuration (ADC - 2 Channel)

	ADC_Init(LPC_ADC, 200000); //ADC initialization, ADC Rate -> 200kHz (권장)
	ADC_IntConfig(LPC_ADC,ADC_ADINTEN2,ENABLE); //ADC 2채널 Interrupt 설정
	ADC_ChannelCmd(LPC_ADC,ADC_CHANNEL_2,ENABLE); //	ADC 2 channel 활성화
	NVIC_EnableIRQ(ADC_IRQn); //ADC interrupt 활성화
	while(1)
	{
		ADC_StartCmd(LPC_ADC,ADC_START_NOW);	// 1회 ADC 변환 (계속 Restart)
		UARTPuts(LPC_UART0,"ADC value on channel 2: ");	//	UART0(RS232)로 메세지 출력
		UARTPutDec16(LPC_UART0,adc_value);	// UART0(RS232)로 adc_value 값 출력
		UARTPuts(LPC_UART0,"\r\n");	//	UART0(RS232)로 라인갱신 메세지 출력
		Delay(SEC_1);	// Dealy 1 Sec
	}
}

// ADC Interrupt Reqest 
void ADC_IRQHandler(void)
{
	if (ADC_ChannelGetStatus(LPC_ADC,ADC_CHANNEL_2,ADC_DATA_DONE)) // ADC 2 Channel 활성화 상태 확인
	{	
		ADC_ChannelCmd(LPC_ADC,ADC_CHANNEL_2,DISABLE); //	ADC 2 channel 활성화
		adc_value =  ADC_ChannelGetData(LPC_ADC,ADC_CHANNEL_2);	//	ADC 2 Channel의 값을 읽어와 adc_value에 저장
		NVIC_DisableIRQ(ADC_IRQn);	// Interrupt 비활성화 (Interrupt Pending 역할)
		NVIC_EnableIRQ(ADC_IRQn); // ADC Interrupt 활성화
		ADC_ChannelCmd(LPC_ADC,ADC_CHANNEL_2,ENABLE); //	ADC 2 channel 활성화
	}
}

