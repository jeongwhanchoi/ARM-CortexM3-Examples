/**********************************************************************
* $Id$		spi_master.c					2010-05-21
*//**
* @file		spi_master.c
* @brief	This example describes how to use SPI in master mode
* @version	2.0
* @date		21. May. 2010
* @author	NXP MCU SW Application Team
*
* Copyright(C) 2010, NXP Semiconductor
* All rights reserved.
*
***********************************************************************
* Software that is described herein is for illustrative purposes only
* which provides customers with programming information regarding the
* products. This software is supplied "AS IS" without any warranties.
* NXP Semiconductors assumes no responsibility or liability for the
* use of the software, conveys no license or title under any patent,
* copyright, or mask work right to the product. NXP Semiconductors
* reserves the right to make changes in the software without
* notification. NXP Semiconductors also make no representation or
* warranty that such application will be suitable for the specified
* use without further testing or modification.
* Permission to use, copy, modify, and distribute this software and its
* documentation is hereby granted, under NXP Semiconductors'
* relevant copyright in the software, without fee, provided that it
* is used in conjunction with NXP Semiconductors microcontrollers.  This
* copyright, permission, and disclaimer notice must appear in all copies of
* this code.
**********************************************************************/
#include "lpc17xx_spi.h"
#include "lpc17xx_libcfg.h"
#include "lpc17xx_pinsel.h"
#include "debug_frmwrk.h"
#include "lpc17xx_gpio.h"

/* Example group ----------------------------------------------------------- */
/** @defgroup SPI_Master	Master
 * @ingroup SPI_Examples
 * @{
 */

/************************** PRIVATE DEFINITIONS *********************/
// PORT number that /CS pin assigned on
#define CS_PORT_NUM		0
// PIN number that  /CS pin assigned on
#define CS_PIN_NUM		16
#define SPI_DATABIT_SIZE 		10

/** Max buffer length */
#define BUFFER_SIZE			0x40

/************************** PRIVATE VARIABLES *************************/
uint8_t menu1[] =
"********************************************************************************\n\r"
"Hello NXP Semiconductors \n\r"
"SPI demo \n\r"
"\t - MCU: LPC17xx \n\r"
"\t - Core: ARM Cortex-M3 \n\r"
"\t - Communicate via: UART0 - 115200bps \n\r"
"\t An example of SPI using interrupt mode to test the SPI driver \n\r"
" This example uses SPI in master mode to communicate with SPI slave device \n\r"
" The master and slave transfer together a number of data byte \n\r"
"********************************************************************************\n\r";
uint8_t menu2[] = "Demo terminated! \n\r";

// SPI Configuration structure variable
SPI_CFG_Type SPI_ConfigStruct;

#if (SPI_DATABIT_SIZE == 8)
uint8_t Tx_Buf[BUFFER_SIZE];
uint8_t Rx_Buf[BUFFER_SIZE];
#else
uint16_t Tx_Buf[BUFFER_SIZE];
uint16_t Rx_Buf[BUFFER_SIZE];
#endif

/************************** PRIVATE FUNCTIONS *************************/
void CS_Init(void);
void CS_Force(int32_t state);
void print_menu(void);
void Buffer_Init(void);
void Error_Loop(void);
void Buffer_Verify(void);

/*-------------------------PRIVATE FUNCTIONS------------------------------*/
/*********************************************************************//**
 * @brief 		Initialize CS pin as GPIO function to drive /CS pin
 * 				due to definition of CS_PORT_NUM and CS_PORT_NUM
 * @param		None
 * @return		None
 ***********************************************************************/
void CS_Init(void)
{
	GPIO_SetDir(CS_PORT_NUM, (1<<CS_PIN_NUM), 1);
	GPIO_SetValue(CS_PORT_NUM, (1<<CS_PIN_NUM));
}


/*********************************************************************//**
 * @brief 		Drive CS output pin to low/high level to select slave device
 * 				via /CS pin state
 * @param[in]	state State of CS output pin that will be driven:
 * 				- 0: Drive CS pin to low level
 * 				- 1: Drive CS pin to high level
 * @return		None
 ***********************************************************************/
void CS_Force(int32_t state)
{
	if (state){
		GPIO_SetValue(CS_PORT_NUM, (1<<CS_PIN_NUM));
	}else{
		GPIO_ClearValue(CS_PORT_NUM, (1<<CS_PIN_NUM));
	}
}

/*********************************************************************//**
 * @brief		Initialize buffer
 * @param[in]	None
 * @return 		None
 **********************************************************************/
void Buffer_Init(void)
{
	uint32_t i;
    for (i = 0; i < BUFFER_SIZE; i++) {
    		Tx_Buf[i] = i;
    		Rx_Buf[i] = 0;
    	}
}

/*********************************************************************//**
 * @brief		Error Loop (called by Buffer_Verify() if any error)
 * @param[in]	none
 * @return 		None
 **********************************************************************/
void Error_Loop(void)
{
	/* Loop forever */
	while (1);
}

/*********************************************************************//**
 * @brief		Verify buffer
 * @param[in]	none
 * @return 		None
 **********************************************************************/
void Buffer_Verify(void)
{
	uint32_t i;
    for ( i = 0; i < BUFFER_SIZE; i++ )
    	{
    		if ( Tx_Buf[i] != Rx_Buf[i] )
    		{
    			/* Call Error Loop */
    			_DBG_("Verify error");
    			Error_Loop();
    		}
    	}
}

/*********************************************************************//**
 * @brief		Print Welcome menu
 * @param[in]	none
 * @return 		None
 **********************************************************************/
void print_menu(void)
{
	_DBG(menu1);
}

/*-------------------------MAIN FUNCTION------------------------------*/
/*********************************************************************//**
 * @brief		c_entry: Main SPI program body
 * @param[in]	None
 * @return 		int
 **********************************************************************/
int c_entry(void)
{
	PINSEL_CFG_Type PinCfg;
	SPI_DATA_SETUP_Type xferConfig;
	uint32_t tmp;

	/*
	 * Initialize SPI pin connect
	 * P0.15 - SCK;
	 * P0.16 - SSEL - used as GPIO
	 * P0.17 - MISO
	 * P0.18 - MOSI
	 */
	PinCfg.Funcnum = 3;
	PinCfg.OpenDrain = 0;
	PinCfg.Pinmode = 0;
	PinCfg.Portnum = 0;
	PinCfg.Pinnum = 15;
	PINSEL_ConfigPin(&PinCfg);
	PinCfg.Pinnum = 17;
	PINSEL_ConfigPin(&PinCfg);
	PinCfg.Pinnum = 18;
	PINSEL_ConfigPin(&PinCfg);
	PinCfg.Pinnum = 16;
	PinCfg.Funcnum = 0;
	PINSEL_ConfigPin(&PinCfg);

	/* Initialize debug via UART0
	 * � 115200bps
	 * � 8 data bit
	 * � No parity
	 * � 1 stop bit
	 * � No flow control
	 */
	debug_frmwrk_init();

	// print welcome screen
	print_menu();

	SPI_ConfigStruct.CPHA = SPI_CPHA_SECOND;
	SPI_ConfigStruct.CPOL = SPI_CPOL_LO;
	SPI_ConfigStruct.ClockRate = 2000000;
	SPI_ConfigStruct.DataOrder = SPI_DATA_MSB_FIRST;
	#if (SPI_DATABIT_SIZE == 8)
	    SPI_ConfigStruct.Databit = SPI_DATABIT_8;
    #elif (SPI_DATABIT_SIZE == 9)
	    SPI_ConfigStruct.Databit = SPI_DATABIT_9;
    #elif (SPI_DATABIT_SIZE == 10)
	    SPI_ConfigStruct.Databit = SPI_DATABIT_10;
    #elif (SPI_DATABIT_SIZE == 11)
	    SPI_ConfigStruct.Databit = SPI_DATABIT_11;
    #elif (SPI_DATABIT_SIZE == 12)
	    SPI_ConfigStruct.Databit = SPI_DATABIT_12;
    #elif (SPI_DATABIT_SIZE == 13)
	    SPI_ConfigStruct.Databit = SPI_DATABIT_13;
    #elif (SPI_DATABIT_SIZE == 14)
	    SPI_ConfigStruct.Databit = SPI_DATABIT_14;
    #elif (SPI_DATABIT_SIZE == 15)
	    SPI_ConfigStruct.Databit = SPI_DATABIT_15;
    #elif (SPI_DATABIT_SIZE == 16)
	    SPI_ConfigStruct.Databit = SPI_DATABIT_16;
    #else
        while(1);
    #endif
	SPI_ConfigStruct.Mode = SPI_MASTER_MODE;
	// Initialize SPI peripheral with parameter given in structure above
	SPI_Init(LPC_SPI, &SPI_ConfigStruct);

	_DBG_("Press '1' to start transfer...");

	while (_DG != '1');

	_DBG_("Init buffer");
	/* Initialize Buffer */
	Buffer_Init();

	CS_Init();

	_DBG_("Start transfer...");
	CS_Force(0);
	// delay for a while
	for (tmp = 10000; tmp; tmp--);
	xferConfig.tx_data = Tx_Buf;
	xferConfig.rx_data = Rx_Buf;
	xferConfig.length = sizeof(Tx_Buf);
	SPI_ReadWrite(LPC_SPI, &xferConfig, SPI_TRANSFER_POLLING);
	// delay for a while
	for (tmp = 10000; tmp; tmp--);
	CS_Force(1);
	_DBG_("Complete!");

	// Verify buffer after transferring
	Buffer_Verify();
	_DBG_("Verify complete!");
	SPI_DeInit(LPC_SPI);
    /* Loop forever */
    while(1);
}

/* With ARM and GHS toolsets, the entry point is main() - this will
   allow the linker to generate wrapper code to setup stacks, allocate
   heap area, and initialize and copy code and data segments. For GNU
   toolsets, the entry point is through __start() in the crt0_gnu.asm
   file, and that startup code will setup stacks and data */
int main(void)
{
    return c_entry();
}


#ifdef  DEBUG
/*******************************************************************************
* @brief		Reports the name of the source file and the source line number
* 				where the CHECK_PARAM error has occurred.
* @param[in]	file Pointer to the source file name
* @param[in]    line assert_param error line source number
* @return		None
*******************************************************************************/
void check_failed(uint8_t *file, uint32_t line)
{
	/* User can add his own implementation to report the file name and line number,
	 ex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */

	/* Infinite loop */
	while(1);
}
#endif

/*
 * @}
 */
