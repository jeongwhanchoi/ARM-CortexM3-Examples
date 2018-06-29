/******************************************************************************
  * @file  LPC1768_utility.h
  * @author  Huins Embbeded Team  by HyunKH
  * @version V1.0.0
  * @date    2015. 02. 03
  * @brief   LPC1768 Function utility Header
  ******************************************************************************/
	
/* Includes ------------------------------------------------------------------- */
#include "lpc17xx_gpio.h"
#include "LPC17xx.h"
#include "lpc_types.h"
#include "LPC1768_Huins.h"
#include "lpc17xx_pinsel.h"
#include "lpc17xx_exti.h"
#include "lpc17xx_uart.h"

/* Delay - LPC1768 CPU clock 12Mhz */
#define SEC_1 	SystemCoreClock/4  
#define SEC_2 	SystemCoreClock/2
#define SEC_4 	SystemCoreClock

void Delay(unsigned long d_t);
void Led_Init(uint8_t Led);
void Led_On(uint8_t Led);
void Led_Off(uint8_t Led);
void Led_Toggle(uint8_t Led);
void Led_All_On(void);
void Led_All_Off(void);



