/******************************************************************************
  * @file  LPC1768_utility.c
  * @author  Huins Embbeded Team  by HyunKH
  * @version V1.0.0
  * @date    2015. 02. 03
  * @brief   LPC1768 Function utility C File
  ******************************************************************************/

/* Includes ------------------------------------------------------------------- */
#include "LPC1768_utility.h"

uint8_t ledStatus1, ledStatus2, ledStatus3, ledStatus4, ledStatus5, ledStatus6, ledStatus7, ledStatus8;
/**
  * @brief  Delay Loop
  * @param  Hz
  * @retval None
  */
void Delay(unsigned long d_t)
{
	long k;
	for(k=0; k<d_t; k++); //sytem clock speed = 12MHz, 1 loop delay = 1/12,000,000 sec
}


/**
  * @brief  LED Initialization
  * @param  LED Number (LED1, LED2, LED3, LED4, LED5, LED6, LED7, LED8, LED_ALL)
  * @retval None
  */
void Led_Init(uint8_t Led)
{
	switch(Led)
	{
		case LED1:
			GPIO_SetDir(GPIO_PORT_1, GPIO_PIN_28, OUTPUT); 	
			GPIO_ClearValue(GPIO_PORT_1,GPIO_PIN_28);
			break;
		
		case LED2:
			GPIO_SetDir(GPIO_PORT_1, GPIO_PIN_29, OUTPUT);
			GPIO_ClearValue(GPIO_PORT_1,GPIO_PIN_29);		
			break;

		case LED3:
			GPIO_SetDir(GPIO_PORT_1, GPIO_PIN_31, OUTPUT);
			GPIO_ClearValue(GPIO_PORT_1,GPIO_PIN_31);		
			break;

		case LED4:
			GPIO_SetDir(GPIO_PORT_2, GPIO_PIN_2, OUTPUT);
			GPIO_ClearValue(GPIO_PORT_2,GPIO_PIN_2);		
			break;

		case LED5:
			GPIO_SetDir(GPIO_PORT_2, GPIO_PIN_3, OUTPUT);
			GPIO_ClearValue(GPIO_PORT_2,GPIO_PIN_3);		
			break;
		
		case LED6:
			GPIO_SetDir(GPIO_PORT_2, GPIO_PIN_4, OUTPUT);
			GPIO_ClearValue(GPIO_PORT_2,GPIO_PIN_4);		
			break;

		case LED7:
			GPIO_SetDir(GPIO_PORT_2, GPIO_PIN_5, OUTPUT);
			GPIO_ClearValue(GPIO_PORT_2,GPIO_PIN_5);		
			break;

		case LED8:
			GPIO_SetDir(GPIO_PORT_2, GPIO_PIN_6, OUTPUT);
			GPIO_ClearValue(GPIO_PORT_2,GPIO_PIN_6);		
			break;
		
		case LED_ALL:	//	LED_ALL
			GPIO_SetDir(GPIO_PORT_1, (1<<28) | (1<<29) | (1<<31), OUTPUT); 
			GPIO_SetDir(GPIO_PORT_2, (1<<2) | (1<<3) | (1<<4) | (1<<5) | (1<<6), OUTPUT); 
		
		//	GPIO_ClearValue(GPIO_PORT_1,  (1<<28) | (1<<29) | (1<<31));		
		//	GPIO_ClearValue(GPIO_PORT_2,  (1<<2) | (1<<3) | (1<<4) | (1<<5) | (1<<6));		
			break;
	}
}

/**
  * @brief  LED On
  * @param  LED Number
  * @retval None
  */
void Led_On(uint8_t Led)
{
	switch(Led)
	{
		case LED1 :
			GPIO_SetValue(GPIO_PORT_1,GPIO_PIN_28);
			break;
		
		case LED2 :
			GPIO_SetValue(GPIO_PORT_1,GPIO_PIN_29);
			break;
		
		case LED3 :
			GPIO_SetValue(GPIO_PORT_1,GPIO_PIN_31);
			break;
		
		case LED4  :
			GPIO_SetValue(GPIO_PORT_2,GPIO_PIN_2);			
			break;
		
		case LED5 :
			GPIO_SetValue(GPIO_PORT_2,GPIO_PIN_3);			
			break;
		
		case LED6 :
			GPIO_SetValue(GPIO_PORT_2,GPIO_PIN_4);			
			break;
		
		case LED7 :
			GPIO_SetValue(GPIO_PORT_2,GPIO_PIN_5);			
			break;
		
		case LED8 :
			GPIO_SetValue(GPIO_PORT_2,GPIO_PIN_6);			
			break;	
		
		case LED_ALL  :
			GPIO_SetValue(GPIO_PORT_1, (1<<28) | (1<<29) | (1<<31));
			GPIO_SetValue(GPIO_PORT_2, (1<<2) | (1<<3) | (1<<4) | (1<<5) | (1<<6));		
			break;			
	}
}


/**
  * @brief  LED Off
  * @param  LED Number
  * @retval None
  */
void Led_Off(uint8_t Led)
{
	switch(Led)
	{
		case 1 :
			GPIO_ClearValue(GPIO_PORT_1,GPIO_PIN_28);
			break;
		
		case 2 :
			GPIO_ClearValue(GPIO_PORT_1,GPIO_PIN_29);
			break;
		
		case 3 :
			GPIO_ClearValue(GPIO_PORT_1,GPIO_PIN_31);
			break;
		
		case 4 :
			GPIO_ClearValue(GPIO_PORT_2,GPIO_PIN_2);			
			break;
		
		case 5 :
			GPIO_ClearValue(GPIO_PORT_2,GPIO_PIN_3);			
			break;
		
		case 6 :
			GPIO_ClearValue(GPIO_PORT_2,GPIO_PIN_4);			
			break;
		
		case 7 :
			GPIO_ClearValue(GPIO_PORT_2,GPIO_PIN_5);			
			break;
		
		case 8 :
			GPIO_ClearValue(GPIO_PORT_2,GPIO_PIN_6);			
			break;		
	}
}


/**
  * @brief  LED Toggle
  * @param  LED Number
  * @retval None
  */
void Led_Toggle(uint8_t Led)
{
	
	
	switch(Led)
	{
		case 1 :
			if(ledStatus1 ==0)
			{				
				Led_On(LED1);
				ledStatus1 = 1;
			}
			else
			{
				Led_Off(LED1);
				ledStatus1 = 0;
			}				
			break;
		
		case 2 :
			if(ledStatus2 ==0)
			{				
				Led_On(LED2);
				ledStatus2 = 1;
			}
			else
			{
				Led_Off(LED2);
				ledStatus2 = 0;
			}				
			break;
		
		case 3 :
			if(ledStatus3 ==0)
			{				
				Led_On(LED3);
				ledStatus3 = 1;
			}
			else
			{
				Led_Off(LED3);
				ledStatus3 = 0;
			}				
			break;
		
		case 4 :
			if(ledStatus4 ==0)
			{				
				Led_On(LED4);
				ledStatus4 = 1;
			}
			else
			{
				Led_Off(LED4);
				ledStatus4 = 0;
			}				
			break;
		
		case 5 :
			if(ledStatus5 ==0)
			{				
				Led_On(LED5);
				ledStatus5 = 1;
			}
			else
			{
				Led_Off(LED5);
				ledStatus5 = 0;
			}				
			break;
		
		case 6 :
			if(ledStatus6 ==0)
			{				
				Led_On(LED6);
				ledStatus6 = 1;
			}
			else
			{
				Led_Off(LED6);
				ledStatus6 = 0;
			}				
			break;
		
		case 7 :
			if(ledStatus7 ==0)
			{				
				Led_On(LED7);
				ledStatus7 = 1;
			}
			else
			{
				Led_Off(LED7);
				ledStatus7 = 0;
			}				
			break;
		
		case 8 :
			if(ledStatus8 ==0)
			{				
				Led_On(LED8);
				ledStatus8 = 1;
			}
			else
			{
				Led_Off(LED8);
				ledStatus8 = 0;
			}				
			break;		
	}
}


/**
  * @brief  On All LED  
  * @param  None
  * @retval None
  */
void Led_All_On(void)
{
	GPIO_SetValue(GPIO_PORT_1,GPIO_PIN_28);
	GPIO_SetValue(GPIO_PORT_1,GPIO_PIN_29);
	GPIO_SetValue(GPIO_PORT_1,GPIO_PIN_31);
	GPIO_SetValue(GPIO_PORT_2,GPIO_PIN_2);			
	GPIO_SetValue(GPIO_PORT_2,GPIO_PIN_3);			
	GPIO_SetValue(GPIO_PORT_2,GPIO_PIN_4);			
	GPIO_SetValue(GPIO_PORT_2,GPIO_PIN_5);			
	GPIO_SetValue(GPIO_PORT_2,GPIO_PIN_6);			
}

/**
  * @brief  Off All LED  
  * @param  None
  * @retval None
  */
void Led_All_Off(void)
{
	GPIO_ClearValue(GPIO_PORT_1,GPIO_PIN_28);
	GPIO_ClearValue(GPIO_PORT_1,GPIO_PIN_29);
	GPIO_ClearValue(GPIO_PORT_1,GPIO_PIN_31);
	GPIO_ClearValue(GPIO_PORT_2,GPIO_PIN_2);			
	GPIO_ClearValue(GPIO_PORT_2,GPIO_PIN_3);			
	GPIO_ClearValue(GPIO_PORT_2,GPIO_PIN_4);			
	GPIO_ClearValue(GPIO_PORT_2,GPIO_PIN_5);			
	GPIO_ClearValue(GPIO_PORT_2,GPIO_PIN_6);			
}
