/******************************************************************************
  * @file  LPC1768_fnd.h
  * @author  Huins Embbeded Team  by HyunKH
  * @version V1.0.0
  * @date    2015. 02. 10
  * @brief   LPC1768 FND Driver Header Fild
  ******************************************************************************/

/* Includes ------------------------------------------------------------------- */
#include "lpc17xx_gpio.h"
#include "LPC17xx.h"
#include "lpc_types.h"
#include "LPC1768_Huins.h"
#include "lpc17xx_pinsel.h"
#include "lpc17xx_exti.h"
#include "lpc17xx_uart.h"


#define	FND_A		(1<<23)	//	FND A
#define	FND_B		(1<<24)	//	FND B
#define	FND_C		(1<<21)	//	FND C
#define	FND_D		(1<<11)	//	FND D
#define	FND_E		(1<<12)	//	FND E
#define	FND_F		(1<<13)	//	FND F
#define	FND_G		(1<<25)	//	FND G
#define	FND_DP	(1<<26)	//	FND DP

void FND_Init (void);
void EXT_IO_A_CS(void);
void EXT_IO_B_CS(void);
void EXT_IO_C_CS(void);
void FND_Data_Reset(void);
void FND_Data_CS(void);
void FND_COM_CS(void);
void FND_DATA_Select(uint8_t dataNum);
void FND_COM_Select(uint8_t	comNum);
void FND_COM_DATA_Select(uint8_t dataNum, uint8_t comNum);
void FND_COM_Init(void);
