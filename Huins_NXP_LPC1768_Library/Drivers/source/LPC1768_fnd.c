/******************************************************************************
  * @file  LPC1768_fnd.c
  * @author  Huins Embbeded Team  by HyunKH
  * @version V1.0.0
  * @date    2015. 02. 10
  * @brief   LPC1768 FND Driver	C File
  ******************************************************************************/

/* Includes ------------------------------------------------------------------- */
#include "LPC1768_fnd.h"


/**
  * @brief FND Initialization
  * @param  None
  * @retval None
  */
void FND_Init (void)
{
	GPIO_SetDir(GPIO_PORT_0,(1<<4)|(1<<5)|(1<<10)|(1<<11)|(1<<19)|(1<<20)|(1<<21)|(1<<23)|(1<<24),OUTPUT);
	GPIO_SetDir(GPIO_PORT_1,(1<<21),OUTPUT);
	GPIO_SetDir(GPIO_PORT_2,(1<<11)|(1<<12)|(1<<13),OUTPUT);
	GPIO_SetDir(GPIO_PORT_3,(1<<25)|(1<<26),OUTPUT);
}

/**
  * @brief FND Com Initialization
  * @param  None
  * @retval None
  */
void FND_COM_Init()
{
	GPIO_ClearValue(GPIO_PORT_0,(1<<23));	//	COM1
	GPIO_ClearValue(GPIO_PORT_0,(1<<24));	//	COM2
	GPIO_ClearValue(GPIO_PORT_1,(1<<21));	//	COM3
	GPIO_ClearValue(GPIO_PORT_2,(1<<11));	//	COM4
	GPIO_ClearValue(GPIO_PORT_2,(1<<12));	//	COM5
	GPIO_ClearValue(GPIO_PORT_2,(1<<13));	//	COM6
	GPIO_ClearValue(GPIO_PORT_3,(1<<25));	//	COM7
	GPIO_ClearValue(GPIO_PORT_3,(1<<26));	//	COM8
}

/**
  * @brief FND DATA CS Setting
  * @param  None
  * @retval None
  */
void FND_Data_CS()
{
	GPIO_SetValue(GPIO_PORT_0,(1<<5));		
	GPIO_ClearValue(GPIO_PORT_0,(1<<5));	
}

/**
  * @brief FND COM CS Setting
  * @param  None
  * @retval None
  */
void FND_COM_CS()
{
	LPC_GPIO0->FIOPIN |= (1<<10);
	LPC_GPIO0->FIOPIN &= ~(1<<10);
}

/**
  * @brief FND Data Pin Reset
  * @param  None
  * @retval None
  */
void FND_Data_Reset()
{
	/* FND Data setting */
	GPIO_SetValue(GPIO_PORT_0,(1<<23));	//	FND A
	GPIO_SetValue(GPIO_PORT_0,(1<<24));	//	FND B
	GPIO_SetValue(GPIO_PORT_1,(1<<21));	//	FND C
	GPIO_SetValue(GPIO_PORT_2,(1<<11));	//	FND D
	GPIO_SetValue(GPIO_PORT_2,(1<<12));	//	FND E
	GPIO_SetValue(GPIO_PORT_2,(1<<13));	//	FND F
	GPIO_SetValue(GPIO_PORT_3,(1<<25));	//	FND G
	GPIO_SetValue(GPIO_PORT_3,(1<<26));	//	FND DP

	FND_Data_CS();	//	Clock 
}

/**
  * @brief FND Data Select
  * @param  dataNum (0 ~ 9)
  * @retval None
  */
void FND_DATA_Select(uint8_t dataNum)
{
	FND_Data_Reset();
	switch(dataNum)
	{
		case 0:
			GPIO_ClearValue(GPIO_PORT_0,FND_A | FND_B);	
			GPIO_ClearValue(GPIO_PORT_1,FND_C);	
			GPIO_ClearValue(GPIO_PORT_2,FND_D | FND_E | FND_F);	
			break;
		
		case 1:
			GPIO_ClearValue(GPIO_PORT_0,FND_B);
			GPIO_ClearValue(GPIO_PORT_1,FND_C);
			break;
	
		case 2:
			GPIO_ClearValue(GPIO_PORT_0,FND_A | FND_B);	
			GPIO_ClearValue(GPIO_PORT_2,FND_D | FND_E);
			GPIO_ClearValue(GPIO_PORT_3,FND_G);
			break;

		case 3:
			GPIO_ClearValue(GPIO_PORT_0,FND_A | FND_B);
			GPIO_ClearValue(GPIO_PORT_1,FND_C);	
			GPIO_ClearValue(GPIO_PORT_2,FND_D);	
			GPIO_ClearValue(GPIO_PORT_3,FND_G);	
			break;

		case 4:
			GPIO_ClearValue(GPIO_PORT_0,FND_B);	
			GPIO_ClearValue(GPIO_PORT_1,FND_C);	
			GPIO_ClearValue(GPIO_PORT_2,FND_F);	
			GPIO_ClearValue(GPIO_PORT_3,FND_G);
			break;

		case 5:
			GPIO_ClearValue(GPIO_PORT_0,FND_A);	
			GPIO_ClearValue(GPIO_PORT_1,FND_C);	
			GPIO_ClearValue(GPIO_PORT_2,FND_D | FND_F);
			GPIO_ClearValue(GPIO_PORT_3,FND_G);				
			break;

		case 6:
			GPIO_ClearValue(GPIO_PORT_0,FND_A);
			GPIO_ClearValue(GPIO_PORT_1,FND_C);
			GPIO_ClearValue(GPIO_PORT_2,FND_D | FND_E | FND_F);
			GPIO_ClearValue(GPIO_PORT_3,FND_G);
			break;

		case 7:
			GPIO_ClearValue(GPIO_PORT_0,FND_A | FND_B);
			GPIO_ClearValue(GPIO_PORT_1,FND_C);
			break;

		case 8:
			GPIO_ClearValue(GPIO_PORT_0,FND_A | FND_B);
			GPIO_ClearValue(GPIO_PORT_1,FND_C);	
			GPIO_ClearValue(GPIO_PORT_2,FND_D | FND_E | FND_F);
			GPIO_ClearValue(GPIO_PORT_3,FND_G);
			break;

		case 9:
			GPIO_ClearValue(GPIO_PORT_0,FND_A | FND_B);
			GPIO_ClearValue(GPIO_PORT_1,FND_C);
			GPIO_ClearValue(GPIO_PORT_2,FND_F);	
			GPIO_ClearValue(GPIO_PORT_3,FND_G);	
			break;
	}
	FND_Data_CS();	//	Clock 
}

/**
  * @brief FND COM Select
  * @param  comNum (1 ~ 8  Line Number)
  * @retval None
  */
void FND_COM_Select(uint8_t comNum)
{
	FND_COM_Init();
	switch(comNum)
	{
		case 1:
			GPIO_SetValue(GPIO_PORT_0,(1<<23));	//	DIC 
			break;
		
		case 2:
			GPIO_SetValue(GPIO_PORT_0,(1<<24));	//	DIC 2
			break;
		
		case 3:
			GPIO_SetValue(GPIO_PORT_1,(1<<21));	//	DIC 3
			break;
		
		case 4:
			GPIO_SetValue(GPIO_PORT_2,(1<<11));	//	DIC 4
			break;
		
		case 5:
			GPIO_SetValue(GPIO_PORT_2,(1<<12));	//	DIC 5
			break;
		
		case 6:
			GPIO_SetValue(GPIO_PORT_2,(1<<13));	//	DIC 6
			break;
		
		case 7:
			GPIO_SetValue(GPIO_PORT_3,(1<<25));	//	DIC 7
			break;
		
		case 8:
			GPIO_SetValue(GPIO_PORT_3,(1<<26));	//	DIC 8
			break;		
	}
	FND_COM_CS();	
}


/**
  * @brief FND COM / DATA Select
  * @param  comNum (1 ~ 8  Line Number)
  * @param  dataNum (0 ~ 9)
  * @retval None
  */
void FND_COM_DATA_Select(uint8_t comNum, uint8_t dataNum)
{
	FND_COM_Select(comNum);	
	FND_DATA_Select(dataNum);
}

