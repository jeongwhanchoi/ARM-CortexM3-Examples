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
	uint8_t aTxBuffer[10];	// 문자열 저장 버퍼
	uint8_t count =	0;	// 현재 Write 버퍼 위치
	
	Motor_Init();
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
					
					if(aTxBuffer[count-1] == '1')	StepMotor_Cycle(1);	// '1' 일 경우 1 Cycle
					if(aTxBuffer[count-1] == '2')	StepMotor_Cycle(2);	// '2' 일 경우 2 Cycle
					if(aTxBuffer[count-1] == '3')	StepMotor_Cycle(3);	// '3' 일 경우 3 Cycle
					if(aTxBuffer[count-1] == '4')	StepMotor_Cycle(4);	// '4' 일 경우 4 Cycle
					if(aTxBuffer[count-1] == '5')	StepMotor_Cycle(5);	// '5' 일 경우 5 Cycle
					if(aTxBuffer[count-1] == '6')	StepMotor_Cycle(6);	// '6' 일 경우 6 Cycle
					if(aTxBuffer[count-1] == '7')	StepMotor_Cycle(7);	// '7' 일 경우 7 Cycle
					if(aTxBuffer[count-1] == '8')	StepMotor_Cycle(8);	// '8' 일 경우 8 Cycle
					if(aTxBuffer[count-1] == '9')	StepMotor_Cycle(9);	// '9' 일 경우 8 Cycle
				}
				count = 0;	 // 저장 위치 초기화
				memset(aTxBuffer, 0x00, sizeof(aTxBuffer)); // Buffer 클리어			
			}
			else
			count++;	// 다음 저장 위치로
		}
	}
}
