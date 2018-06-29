/**********************************************************************
* $Id$		adc_dma_test.c			2010-05-21
*//**
* @file		adc_dma_test.c
* @brief	This example describes how to use ADC conversions and
* 			transfer converted data by using DMA
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
#include "lpc17xx_adc.h"
#include "lpc17xx_libcfg.h"
#include "lpc17xx_pinsel.h"
#include "lpc17xx_nvic.h"
#include "lpc17xx_gpdma.h"
#include "debug_frmwrk.h"

/* Example group ----------------------------------------------------------- */
/** @defgroup ADC_DMA	DMA
 * @ingroup ADC_Examples
 * @{
 */
/************************** PRIVATE DEFINITIONS *************************/
#define MCB_LPC_1768
//#define IAR_LPC_1768

#ifdef MCB_LPC_1768
#define _ADC_INT		ADC_ADINTEN2
#define _ADC_CHANNEL	ADC_CHANNEL_2
#elif defined(IAR_LPC_1768)
#define _ADC_INT		ADC_ADINTEN5
#define _ADC_CHANNEL	ADC_CHANNEL_5
#endif

/** DMA size of transfer */
#define DMA_SIZE		1

/************************** PRIVATE VARIABLES *************************/
uint8_t  menu1[] =
		"********************************************************************************\n\r"
		"Hello NXP Semiconductors \n\r"
		" ADC demo \n\r"
		"\t - MCU: LPC17xx \n\r"
		"\t - Core: ARM CORTEX-M3 \n\r"
		"\t - Communicate via: UART0 - 115200bps \n\r"
		" DMA testing : ADC peripheral to memory\n\r"
		" Use ADC with 12-bit resolution rate of 200KHz\n\r"
		" Value ADC channel is displayed by UART, this value is taken from destination memory value of DMA function \n\r"
		" Turn the potentiometer to see how ADC value changes\n\r"
		"********************************************************************************\n\r";
#ifdef MCB_LPC_1768
uint8_t menu2[] = "ADC value on channel 2: ";
#elif defined(IAR_LPC_1768)
uint8_t menu2[] = "ADC value on channel 5: ";
#endif

/* Terminal Counter flag for Channel 0 */
__IO uint32_t Channel0_TC;

/* Error Counter flag for Channel 0 */
__IO uint32_t Channel0_Err;

/************************** PRIVATE FUNCTION *************************/
void DMA_IRQHandler (void);

void print_menu(void);

/*----------------- INTERRUPT SERVICE ROUTINES --------------------------*/
/*********************************************************************//**
 * @brief		GPDMA interrupt handler sub-routine
 * @param[in]	None
 * @return 		None
 **********************************************************************/
void DMA_IRQHandler (void)
{
	// check GPDMA interrupt on channel 0
	if (GPDMA_IntGetStatus(GPDMA_STAT_INT, 0)){
		// Check counter terminal status
		if(GPDMA_IntGetStatus(GPDMA_STAT_INTTC, 0)){
			// Clear terminate counter Interrupt pending
			GPDMA_ClearIntPending (GPDMA_STATCLR_INTTC, 0);
				Channel0_TC++;
		}
		// Check error terminal status
		if (GPDMA_IntGetStatus(GPDMA_STAT_INTERR, 0)){
			// Clear error counter Interrupt pending
			GPDMA_ClearIntPending (GPDMA_STATCLR_INTERR, 0);
			Channel0_Err++;
		}
	}
}

/*-------------------------PRIVATE FUNCTIONS------------------------------*/
/*********************************************************************//**
 * @brief		Print menu
 * @param[in]	None
 * @return 		None
 **********************************************************************/
void print_menu(void)
{
	_DBG(menu1);
}

/*-------------------------MAIN FUNCTION------------------------------*/
/*********************************************************************//**
 * @brief		c_entry: Main ADC program body
 * @param[in]	None
 * @return 		int
 **********************************************************************/
int c_entry(void)
{
	PINSEL_CFG_Type PinCfg;
	GPDMA_Channel_CFG_Type GPDMACfg;
	uint32_t adc_value, tmp;

	/* Initialize ADC ----------------------------------------------------*/

	/* Because the potentiometer on different boards (MCB & IAR) connect
	 * with different ADC channel, so we have to configure correct ADC channel
	 * on each board respectively.
	 * If you want to check other ADC channels, you have to wire this ADC pin directly
	 * to potentiometer pin (please see schematic doc for more reference)
	 */
#ifdef MCB_LPC_1768
	/* If using MCB1700 v.1 board
	 * select P0.25 as AD0.2
	 */
	PinCfg.Funcnum = 1;
	PinCfg.OpenDrain = 0;
	PinCfg.Pinmode = 0;
	PinCfg.Pinnum = 25;
	PinCfg.Portnum = 0;
	PINSEL_ConfigPin(&PinCfg);
#elif defined(IAR_LPC_1768)
	/* If using IAR LPC1768 KS v.A board:
	 * select P1.31 as AD0.5
	 */
	PinCfg.Funcnum = 3;
	PinCfg.OpenDrain = 0;
	PinCfg.Pinmode = 0;
	PinCfg.Pinnum = 31;
	PinCfg.Portnum = 1;
	PINSEL_ConfigPin(&PinCfg);
#endif

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

	/*  Configuration for ADC :
	 *  Select: ADC channel 2 (if using MCB1700 board)
	 *  	    ADC channel 5 (if using IAR-LPC1768 board)
	 * 	ADC conversion rate = 200KHz
	 */
	ADC_Init(LPC_ADC, 200000);
	ADC_IntConfig(LPC_ADC,_ADC_INT,ENABLE);
	ADC_ChannelCmd(LPC_ADC,_ADC_CHANNEL,ENABLE);

	/* GPDMA block section -------------------------------------------- */
	/* Disable GPDMA interrupt */
	NVIC_DisableIRQ(DMA_IRQn);
	/* preemption = 1, sub-priority = 1 */
	NVIC_SetPriority(DMA_IRQn, ((0x01<<3)|0x01));

	/* Initialize GPDMA controller */
	GPDMA_Init();

	// Setup GPDMA channel --------------------------------
	// channel 0
	GPDMACfg.ChannelNum = 0;
	// Source memory - unused
	GPDMACfg.SrcMemAddr = 0;
	// Destination memory
	GPDMACfg.DstMemAddr = (uint32_t) &adc_value;
	// Transfer size
	GPDMACfg.TransferSize = DMA_SIZE;
	// Transfer width - unused
	GPDMACfg.TransferWidth = 0;
	// Transfer type
	GPDMACfg.TransferType = GPDMA_TRANSFERTYPE_P2M;
	// Source connection
	GPDMACfg.SrcConn = GPDMA_CONN_ADC;
	// Destination connection - unused
	GPDMACfg.DstConn = 0;
	// Linker List Item - unused
	GPDMACfg.DMALLI = 0;
	GPDMA_Setup(&GPDMACfg);

	/* Reset terminal counter */
	Channel0_TC = 0;
	/* Reset Error counter */
	Channel0_Err = 0;

	/* Enable GPDMA interrupt */
	NVIC_EnableIRQ(DMA_IRQn);

	while (1) {

		// Enable GPDMA channel 0
		GPDMA_ChannelCmd(0, ENABLE);

		ADC_StartCmd(LPC_ADC,ADC_START_NOW);
		/* Wait for GPDMA processing complete */;
		while ((Channel0_TC == 0) );

		// Disable GPDMA channel 0
		GPDMA_ChannelCmd(0, DISABLE);

		//Display the result of conversion on the UART0
		_DBG(menu2);
		_DBD32(ADC_DR_RESULT(adc_value));
		_DBG_("");

		// Wait for a while
		for(tmp = 0; tmp < 1000000; tmp++);

		/* GPDMA Re-setup */
		GPDMA_Setup(&GPDMACfg);

		/* Reset terminal counter */
		Channel0_TC = 0;
		/* Reset Error counter */
		Channel0_Err = 0;
	}
}

/* Support required entry point for other toolchain */
int main (void)
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
