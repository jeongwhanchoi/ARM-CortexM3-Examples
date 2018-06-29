/******************************************************************************
  * @file  StepMotor.c
  * @author  Huins Embbeded Team  by HyunKH
  * @version V1.0.0
  * @date    2015. 02. 13
  * @brief   StepMotor Control (4 Step)
  ******************************************************************************/

/* Include ---------------------------------------------------------*/
#include "LPC1768_motor.h"
#include "LPC1768_utility.h"
#include "debug_frmwrk.h"
#include <string.h>

/* Private variable ---------------------------------------------------------*/
uint32_t motor_cnt = 0;

int main (void)
{   
	uint8_t ch;	
	uint8_t aTxBuffer[10];	// ���ڿ� ���� ����
	uint8_t count =	0;	// ���� Write ���� ��ġ
	
	Motor_Init();
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
					
					if(aTxBuffer[count-1] == '1')	StepMotor_Cycle(1);	// '1' �� ��� 1 Cycle
					if(aTxBuffer[count-1] == '2')	StepMotor_Cycle(2);	// '2' �� ��� 2 Cycle
					if(aTxBuffer[count-1] == '3')	StepMotor_Cycle(3);	// '3' �� ��� 3 Cycle
					if(aTxBuffer[count-1] == '4')	StepMotor_Cycle(4);	// '4' �� ��� 4 Cycle
					if(aTxBuffer[count-1] == '5')	StepMotor_Cycle(5);	// '5' �� ��� 5 Cycle
					if(aTxBuffer[count-1] == '6')	StepMotor_Cycle(6);	// '6' �� ��� 6 Cycle
					if(aTxBuffer[count-1] == '7')	StepMotor_Cycle(7);	// '7' �� ��� 7 Cycle
					if(aTxBuffer[count-1] == '8')	StepMotor_Cycle(8);	// '8' �� ��� 8 Cycle
					if(aTxBuffer[count-1] == '9')	StepMotor_Cycle(9);	// '9' �� ��� 8 Cycle
				}
				count = 0;	 // ���� ��ġ �ʱ�ȭ
				memset(aTxBuffer, 0x00, sizeof(aTxBuffer)); // Buffer Ŭ����			
			}
			else
			count++;	// ���� ���� ��ġ��
		}
	}
}
