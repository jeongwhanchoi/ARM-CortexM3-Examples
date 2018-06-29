/******************************************************************************
  * @file  uart_polling.c
  * @author  Huins Embbeded Team  by HyunKH
  * @version V1.0.0
  * @date    2015. 02. 09
  * @brief   LPC_UART0 Rx, Tx Test
  ******************************************************************************/
	
/* Includes ------------------------------------------------------------------*/
#include "LPC1768_utility.h"
#include "debug_frmwrk.h"
#include <string.h>

int main(void)
{
	uint8_t ch;	
	uint8_t aTxBuffer[10];	// 문자열 저장 버퍼
	uint8_t count =	0;	// 현재 Write 버퍼 위치
	
	Led_Init(LED_ALL);	// LED 전체 초기화
	
	Uart0_Init();	// UART0 초기화
	UARTPuts(LPC_UART0,"\r\n Enter the Content, 1~8 LED Toggle\r\n");
	
	while(1)
	{
		ch = UART_ReceiveByte(LPC_UART0);	// Polling으로 Data 읽어오기
		
		if(ch)	// Data가 존재한다면..
		{
			aTxBuffer[count] = ch;	// 버퍼에 저장

			UARTPuts(LPC_UART0,&ch);	// 하이퍼터미널로 저장된 Data 출력

			if(aTxBuffer[count] == 0x0D)	// Enter를 눌렀을 경우 (0x0D ASCII Code)
			{
				if(strlen((char *)aTxBuffer) > 2)
				{
					UARTPuts(LPC_UART0,"Error !! \r\nInsert Key Range 1 ~ 8 \r\n");
				}
				else
				{
					UARTPuts(LPC_UART0,"\r\n");	// CR(Carriage Return), LF(Line Feed) 개행
					if(aTxBuffer[0] == '1')	Led_Toggle(LED1);	// '1' 일 경우 LED1 Toggle
					if(aTxBuffer[0] == '2')	Led_Toggle(LED2);	// '2' 일 경우 LED2 Toggle
					if(aTxBuffer[0] == '3')	Led_Toggle(LED3);	// '3' 일 경우 LED3 Toggle
					if(aTxBuffer[0] == '4')	Led_Toggle(LED4);	// '4' 일 경우 LED4 Toggle
					if(aTxBuffer[0] == '5')	Led_Toggle(LED5);	// '5' 일 경우 LED5 Toggle
					if(aTxBuffer[0] == '6')	Led_Toggle(LED6);	// '6' 일 경우 LED6 Toggle
					if(aTxBuffer[0] == '7')	Led_Toggle(LED7);	// '7' 일 경우 LED7 Toggle
					if(aTxBuffer[0] == '8')	Led_Toggle(LED8);	// '8' 일 경우 LED8 Toggle
				}
				count = 0;	 // 저장 위치 초기화
				memset(aTxBuffer, 0x00, sizeof(aTxBuffer)); // Buffer 클리어			
			}
			else
			count++;	// 다음 저장 위치로
		}
	}
} 
