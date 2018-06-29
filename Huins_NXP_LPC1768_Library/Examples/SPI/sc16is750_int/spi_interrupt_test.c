/**********************************************************************
* $Id$		spi_interrupt_test.c					2010-05-21
*//**
* @file		spi_interrupt_test.c
* @brief	This example describes how to use SPI at mode SPI master/8bit
* 			on LPC1768 to communicate with SC16IS750/760 Demo board
* 			in interrupt mode
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
/** @defgroup SPI_sc16is750_int	sc16is750_int
 * @ingroup SPI_Examples
 * @{
 */

/************************** PRIVATE DEFINTIONS *********************/
// PORT number that /CS pin assigned on
#define CS_PORT_NUM		0
// PIN number that  /CS pin assigned on
#define CS_PIN_NUM		16

/* Idle char */
#define IDLE_CHAR	0xFF

// Define macro used in command when using SPI with SC16IS740
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
"SPI demo \n\r"
"\t - MCU: LPC17xx \n\r"
"\t - Core: ARM Cortex-M3 \n\r"
"\t - Communicate via: UART0 - 115200bps \n\r"
" Communicate with SPI function on SC16IS750/760 Demo Board\n\r"
" Use IO function on SC16IS740/750/760 chip to turn ON/OFF LEDs\n\r"
"Press '1' to turn ON LEDs, '2' to turn OFF LEDs \n\r"
"********************************************************************************\n\r";
uint8_t menu2[] = "Demo terminated! \n\r";

uint8_t iocon_cfg[2] = {SC16IS740_WR_CMD(SC16IS740_IOCON_REG), 0x00};
uint8_t iodir_cfg[2] = {SC16IS740_WR_CMD(SC16IS740_IODIR_REG), 0xFF};
uint8_t iostate_on[2] = {SC16IS740_WR_CMD(SC16IS740_IOSTATE_REG), 0x00};
uint8_t iostate_off[2] = {SC16IS740_WR_CMD(SC16IS740_IOSTATE_REG), 0xFF};
uint8_t spireadbuf[2];

/* Status Flag indicates current SPI transmission complete or not */
__IO FlagStatus complete;

// SPI Configuration structure variable
SPI_CFG_Type SPI_ConfigStruct;
// SPI Data Setup structure variable
SPI_DATA_SETUP_Type xferConfig;


/************************** PRIVATE FUNCTIONS *************************/
void SPI_IRQHandler(void);

void CS_Init(void);
void CS_Force(int32_t state);
void print_menu(void);

/*----------------- INTERRUPT SERVICE ROUTINES --------------------------*/
/*********************************************************************//**
 * @brief 		SPI Interrupt used for reading and writing handler
 * @param		None
 * @return 		None
 ***********************************************************************/
void SPI_IRQHandler(void)
{
	SPI_DATA_SETUP_Type *xf_setup;
	uint16_t tmp;
	uint8_t dataword;

	xf_setup = &xferConfig;

	if(SPI_GetDataSize(LPC_SPI) == 8)
		dataword = 0;
	else dataword = 1;

	/* Dummy read to clear SPI interrupt flag */
	SPI_ClearIntPending(LPC_SPI);

	// save status
	tmp = SPI_GetStatus(LPC_SPI);
	xf_setup->status = tmp;
	// Check for error
	if (tmp & (SPI_SPSR_ABRT | SPI_SPSR_MODF | SPI_SPSR_ROVR | SPI_SPSR_WCOL)){
		xf_setup->status |= SPI_STAT_ERROR;
		// Disable Interrupt and call call-back
		SPI_IntCmd(LPC_SPI, DISABLE);
		// Set Complete Flag
		complete = SET;
		return;
	}

	/* Check SPI complete flag */
	if (tmp & SPI_SPSR_SPIF){
	   // Read data from SPI data
		tmp = SPI_ReceiveData(LPC_SPI);
		if (xf_setup->rx_data != NULL)
		{
			if (dataword == 0){
				*(uint8_t *)((uint8_t *)(xf_setup->rx_data) + xf_setup->counter) = (uint8_t) tmp;
			} else {
				*(uint16_t *)((uint8_t *)(xf_setup->rx_data) + xf_setup->counter) = (uint8_t) tmp;
			}
		}
		// Increase counter
		if (dataword == 0){
			xf_setup->counter++;
		} else {
			xf_setup->counter += 2;
		}
	}

	if (xf_setup->counter < xf_setup->length){
		// Write data to buffer
		if(xf_setup->tx_data == NULL){
			if (dataword == 0){
				SPI_SendData(LPC_SPI, 0xFF);
			} else {
				SPI_SendData(LPC_SPI, 0xFFFF);
			}
		} else {
			if (dataword == 0){
				SPI_SendData(LPC_SPI, (*(uint8_t *)((uint8_t *)(xf_setup->tx_data) + xf_setup->counter)));
			} else {
				SPI_SendData(LPC_SPI, (*(uint16_t *)((uint8_t *)(xf_setup->tx_data) + xf_setup->counter)));
			}
		}
	}
	// No more data to send
	else {
		xf_setup->status |= SPI_STAT_DONE;
		// Disable Interrupt and call call-back
		SPI_IntCmd(LPC_SPI, DISABLE);
		// Set Complete Flag
		complete = SET;
	}
}

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
 * @brief		c_entry: Main SPI program body
 * @param[in]	None
 * @return 		int
 **********************************************************************/
int c_entry(void)
{
	uint8_t tmpchar[2] = {0, 0};
	PINSEL_CFG_Type PinCfg;
	__IO FlagStatus exitflag;

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

	// initialize SPI configuration structure to default
	SPI_ConfigStructInit(&SPI_ConfigStruct);
	// Initialize SPI peripheral with parameter given in structure above
	SPI_Init(LPC_SPI, &SPI_ConfigStruct);

	// Initialize /CS pin to GPIO function
	CS_Init();

    /* preemption = 1, sub-priority = 1 */
    NVIC_SetPriority(SPI_IRQn, ((0x01<<3)|0x01));
    /* Enable SSP0 interrupt */
    NVIC_EnableIRQ(SPI_IRQn);

	/* First, send some command to reset SC16IS740 chip via SPI bus interface
	 * note driver /CS pin to low state before transferring by CS_Enable() function
	 */
	complete = RESET;
	CS_Force(0);
	xferConfig.tx_data = iocon_cfg;
	xferConfig.rx_data = spireadbuf;
	xferConfig.length = sizeof (iocon_cfg);
	SPI_ReadWrite(LPC_SPI, &xferConfig, SPI_TRANSFER_INTERRUPT);
	while (complete == RESET);
	CS_Force(1);

	complete = RESET;
	CS_Force(0);
	xferConfig.tx_data = iodir_cfg;
	xferConfig.rx_data = spireadbuf;
	xferConfig.length = sizeof (iodir_cfg);
	SPI_ReadWrite(LPC_SPI, &xferConfig, SPI_TRANSFER_INTERRUPT);
	while (complete == RESET);
	CS_Force(1);

	// Reset exit flag
	exitflag = RESET;

	// Start to use SPI polling mode
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
				xferConfig.rx_data = spireadbuf;
				xferConfig.length = sizeof (iostate_on);
				SPI_ReadWrite(LPC_SPI, &xferConfig, SPI_TRANSFER_POLLING);
				CS_Force(1);
			}
			else if (tmpchar[0] == '2')
			{
				// LEDs are OFF now...
				CS_Force(0);
				xferConfig.tx_data = iostate_off;
				xferConfig.rx_data = spireadbuf;
				xferConfig.length = sizeof (iostate_off);
				SPI_ReadWrite(LPC_SPI, &xferConfig, SPI_TRANSFER_POLLING);
				CS_Force(1);
			}
			/* Then Echo it back */
			_DBG_(tmpchar);
		}
	}
    // DeInitialize UART0 peripheral
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
