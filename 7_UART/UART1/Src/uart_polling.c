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
	uint8_t aTxBuffer[10];	// ���ڿ� ���� ����
	uint8_t count =	0;	// ���� Write ���� ��ġ
	
	Led_Init(LED_ALL);	// LED ��ü �ʱ�ȭ
	
	Uart0_Init();	// UART0 �ʱ�ȭ
	UARTPuts(LPC_UART0,"\r\n Enter the Content, 1~8 LED Toggle\r\n");
	
	while(1)
	{
		ch = UART_ReceiveByte(LPC_UART0);	// Polling���� Data �о����
		
		if(ch)	// Data�� �����Ѵٸ�..
		{
			aTxBuffer[count] = ch;	// ���ۿ� ����

			UARTPuts(LPC_UART0,&ch);	// �������͹̳η� ����� Data ���

			if(aTxBuffer[count] == 0x0D)	// Enter�� ������ ��� (0x0D ASCII Code)
			{
				if(strlen((char *)aTxBuffer) > 2)
				{
					UARTPuts(LPC_UART0,"Error !! \r\nInsert Key Range 1 ~ 8 \r\n");
				}
				else
				{
					UARTPuts(LPC_UART0,"\r\n");	// CR(Carriage Return), LF(Line Feed) ����
					if(aTxBuffer[0] == '1')	Led_Toggle(LED1);	// '1' �� ��� LED1 Toggle
					if(aTxBuffer[0] == '2')	Led_Toggle(LED2);	// '2' �� ��� LED2 Toggle
					if(aTxBuffer[0] == '3')	Led_Toggle(LED3);	// '3' �� ��� LED3 Toggle
					if(aTxBuffer[0] == '4')	Led_Toggle(LED4);	// '4' �� ��� LED4 Toggle
					if(aTxBuffer[0] == '5')	Led_Toggle(LED5);	// '5' �� ��� LED5 Toggle
					if(aTxBuffer[0] == '6')	Led_Toggle(LED6);	// '6' �� ��� LED6 Toggle
					if(aTxBuffer[0] == '7')	Led_Toggle(LED7);	// '7' �� ��� LED7 Toggle
					if(aTxBuffer[0] == '8')	Led_Toggle(LED8);	// '8' �� ��� LED8 Toggle
				}
				count = 0;	 // ���� ��ġ �ʱ�ȭ
				memset(aTxBuffer, 0x00, sizeof(aTxBuffer)); // Buffer Ŭ����			
			}
			else
			count++;	// ���� ���� ��ġ��
		}
	}
} 
