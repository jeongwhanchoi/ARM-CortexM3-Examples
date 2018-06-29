/**********************************************************************
* $Id$		sc16is750_polling.c				2010-05-21
*//**
* @file		sc16is750_polling.c
* @brief	This example describes how to use SPP using polling mode,
* 			SSP frame format to communicate with SC16IS750/760 Demo board
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
#include "lpc17xx_ssp.h"
#include "lpc17xx_libcfg.h"
#include "lpc17xx_pinsel.h"
#include "debug_frmwrk.h"
#include "lpc17xx_gpio.h"

/* Example group ----------------------------------------------------------- */
/** @defgroup SSP_sc16is750_polling	sc16is750_polling
 * @ingroup SSP_Examples
 * @{
 */


/************************** PRIVATE DEFINITIONS ***********************/
// PORT number that /CS pin assigned on
#define CS_PORT_NUM		0
// PIN number that  /CS pin assigned on
#define CS_PIN_NUM		16

// Define macro used in command when using SSP with SC16IS740
#define SC16IS740_WR_CMD(x)		((uint8_t) (x << 3))
#define SC16IS740_RD_CMD(x)		((uint8_t) ((x << 3) | 0x80))

// Define register address of SC16IS740
#define SC16IS740_IODIR_REG		0x0A
#define SC16IS740_IOSTATE_REG	0x0B
#define SC16IS740_IOCON_REG		0x0E


/************************** PRIVATE VARIABLES *************************/
uint8_t menu1[] =
"********************************************************************************\n\r"
"Hello NXP Semiconductors \n\r"
"SSP demo \n\r"
"\t - MCU: LPC17xx \n\r"
"\t - Core: ARM Cortex-M3 \n\r"
"\t - Communicate via: UART0 - 9.6 kbps \n\r"
" Communicate with SSP0 function on SC16IS750/760 Demo Board\n\r"
" in polling mode\n\r"
" Use IO function on SC16IS740/750/760 chip to turn ON/OFF LEDs\n\r"
" Press '1' to turn ON LEDs, '2' to turn OFF LEDs \n\r"
"********************************************************************************\n\r";
uint8_t menu2[] = "Demo terminated! \n\r";

// SSP Configuration structure variable
SSP_CFG_Type SSP_ConfigStruct;

uint8_t iocon_cfg[2] = {SC16IS740_WR_CMD(SC16IS740_IOCON_REG), 0x00};
uint8_t iodir_cfg[2] = {SC16IS740_WR_CMD(SC16IS740_IODIR_REG), 0xFF};
uint8_t iostate_on[2] = {SC16IS740_WR_CMD(SC16IS740_IOSTATE_REG), 0x00};
uint8_t iostate_off[2] = {SC16IS740_WR_CMD(SC16IS740_IOSTATE_REG), 0xFF};
uint8_t sspreadbuf[2];

/************************** PRIVATE FUNCTIONS *************************/
void CS_Init(void);
void CS_Force(int32_t state);
void print_menu(void);

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
 * @brief		c_entry: Main SSP program body
 * @param[in]	None
 * @return 		int
 **********************************************************************/
int c_entry(void)
{
	uint8_t tmpchar[2] = {0, 0};
	PINSEL_CFG_Type PinCfg;
	__IO FlagStatus exitflag;
	SSP_DATA_SETUP_Type xferConfig;

	/*
	 * Initialize SPI pin connect
	 * P0.15 - SCK
	 * P0.16 - SSEL - used as GPIO
	 * P0.17 - MISO
	 * P0.18 - MOSI
	 */
	PinCfg.Funcnum = 2;
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

	// initialize SSP configuration structure to default
	SSP_ConfigStructInit(&SSP_ConfigStruct);
	// Initialize SSP peripheral with parameter given in structure above
	SSP_Init(LPC_SSP0, &SSP_ConfigStruct);

	// Initialize /CS pin to GPIO function
	CS_Init();

	// Enable SSP peripheral
	SSP_Cmd(LPC_SSP0, ENABLE);

	/* First, send some command to reset SC16IS740 chip via SSP bus interface
	 * note driver /CS pin to low state before transferring by CS_Enable() function
	 */
	CS_Force(0);
	xferConfig.tx_data = iocon_cfg;
	xferConfig.rx_data = sspreadbuf;
	xferConfig.length = sizeof (iocon_cfg);
	SSP_ReadWrite(LPC_SSP0, &xferConfig, SSP_TRANSFER_POLLING);
	CS_Force(1);

	CS_Force(0);
	xferConfig.tx_data = iodir_cfg;
	xferConfig.rx_data = sspreadbuf;
	xferConfig.length = sizeof (iodir_cfg);
	SSP_ReadWrite(LPC_SSP0, &xferConfig, SSP_TRANSFER_POLLING);
	CS_Force(1);

	// Reset exit flag
	exitflag = RESET;

	/* Read some data from the buffer */
	while (exitflag == RESET)
	{
		while((tmpchar[0] = _DG) == 0);

		if (tmpchar[0] == 27){
			/* ESC key, set exit flag */
			_DBG_(menu2);
			exitflag = SET;
		}
		else if (tmpchar[0] == 'r'){
			print_menu();
		} else {
			if (tmpchar[0] == '1')
			{
				// LEDs are ON now...
				CS_Force(0);
				xferConfig.tx_data = iostate_on;
				xferConfig.rx_data = sspreadbuf;
				xferConfig.length = sizeof (iostate_on);
				SSP_ReadWrite(LPC_SSP0, &xferConfig, SSP_TRANSFER_POLLING);
				CS_Force(1);
			}
			else if (tmpchar[0] == '2')
			{
				// LEDs are OFF now...
				CS_Force(0);
				xferConfig.tx_data = iostate_off;
				xferConfig.rx_data = sspreadbuf;
				xferConfig.length = sizeof (iostate_off);
				SSP_ReadWrite(LPC_SSP0, &xferConfig, SSP_TRANSFER_POLLING);
				CS_Force(1);
			}
			/* Then Echo it back */
			_DBG_(tmpchar);
		}
	}

    // wait for current transmission complete - THR must be empty
    while (UART_CheckBusy(LPC_UART0) == SET);

    // DeInitialize UART0 peripheral
    UART_DeInit(LPC_UART0);

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
