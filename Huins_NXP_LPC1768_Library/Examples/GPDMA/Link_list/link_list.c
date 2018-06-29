/**********************************************************************
* $Id$		link_list.c  				2010-06-16
*//**
* @file		link_list.c
* @brief	This example used to test GPDMA Link list function
* @version	1.0
* @date		16. June. 2010
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
#include "lpc17xx_gpdma.h"
#include "lpc17xx_libcfg.h"
#include "debug_frmwrk.h"

/* Example group ----------------------------------------------------------- */
/** @defgroup GPDMA_Link_list	Link_list
 * @ingroup GPDMA_Examples
 * @{
 */

/************************** PRIVATE DEFINTIONS*************************/
/** DMA transfer size */
#define DMA_SIZE		32

/************************** PRIVATE VARIABLES *************************/
uint8_t menu[]=
	"********************************************************************************\n\r"
	"Hello NXP Semiconductors \n\r"
	"GPDMA demo \n\r"
	"\t - MCU: LPC17xx \n\r"
	"\t - Core: ARM CORTEX-M3 \n\r"
	"\t - Communicate via: UART0 - 115200 bps \n\r"
	"This example used to test GPDMA link list function \n\r"
	"********************************************************************************\n\r";
uint8_t menu2[] = "Demo terminated! \n\r";
uint8_t err_menu[] = "Buffer Check fail!\n\r";
uint8_t compl_menu[] = "Buffer Check success!\n\r";

uint32_t DMADest_Buffer[DMA_SIZE];

#if (defined (__ICCARM__))
#pragma location = "data_init"
uint32_t const DMASrc_Buffer1[DMA_SIZE/2] =
#else
uint32_t DMASrc_Buffer1[DMA_SIZE/2] __attribute__((at(0x2007C000))) =
#endif
{
	0x01020304,0x05060708,0x090A0B0C,0x0D0E0F10,
	0x11121314,0x15161718,0x191A1B1C,0x1D1E1F20,
	0x21222324,0x25262728,0x292A2B2C,0x2D2E2F30,
	0x31323334,0x35363738,0x393A3B3C,0x3D3E3F40
};

// Terminal Counter flag for Channel 0
__IO uint32_t Channel0_TC;

// Error Counter flag for Channel 0
__IO uint32_t Channel0_Err;

#if (defined (__ICCARM__))
#pragma location = "data_init"
uint32_t const DMASrc_Buffer2[DMA_SIZE/2] =
#else
uint32_t DMASrc_Buffer2[DMA_SIZE/2] __attribute__((at(0x2007C200)))=
#endif
{
	0x41424344,0x45464748,0x494A4B4C,0x4D4E4F50,
	0x51525354,0x55565758,0x595A5B5C,0x5D5E5F60,
	0x61626364,0x65666768,0x696A6B6C,0x6D6E6F70,
	0x71727374,0x75767778,0x797A7B7C,0x7D7E7F80
};

/*-------------------------MAIN FUNCTION------------------------------*/
void DMA_IRQHandler (void);

void print_menu(void);
void Error_Loop(void);

/*----------------- INTERRUPT SERVICE ROUTINES --------------------------*/
/*********************************************************************//**
 * @brief		GPDMA interrupt handler sub-routine
 * @param[in]	None
 * @return 		None
 **********************************************************************/
void DMA_IRQHandler (void)
{
	// check GPDMA interrupt on channel 0
	if (GPDMA_IntGetStatus(GPDMA_STAT_INT, 0)){ //check interrupt status on channel 0
		// Check counter terminal status
		if(GPDMA_IntGetStatus(GPDMA_STAT_INTTC, 0)){
			// Clear terminate counter Interrupt pending
			GPDMA_ClearIntPending (GPDMA_STATCLR_INTTC, 0);
				Channel0_TC++;
		}
		if (GPDMA_IntGetStatus(GPDMA_STAT_INTERR, 0)){
			// Clear error counter Interrupt pending
			GPDMA_ClearIntPending (GPDMA_STATCLR_INTERR, 0);
			Channel0_Err++;
		}
	}
}

/*-------------------------PRIVATE FUNCTIONS-----------------------------*/
/*********************************************************************//**
 * @brief		Print Welcome menu
 * @param[in]	none
 * @return 		None
 **********************************************************************/
void print_menu(void)
{
	_DBG(menu);
}


/*********************************************************************//**
 * @brief		Verify buffer
 * @param[in]	none
 * @return 		None
 **********************************************************************/
void Buffer_Verify(void)
{
	uint8_t i;
	uint32_t *src_addr = (uint32_t *)DMASrc_Buffer1;
	uint32_t *dest_addr = (uint32_t *)DMADest_Buffer;

	for ( i = 0; i < DMA_SIZE/2; i++ )
	{
		if ( *src_addr++ != *dest_addr++ )
		{
			/* Call Error Loop */
			Error_Loop();
		}
	}
	src_addr = (uint32_t *)DMASrc_Buffer2;
	for ( i = 0; i < DMA_SIZE/2; i++ )
	{
		if ( *src_addr++ != *dest_addr++ )
		{
			/* Call Error Loop */
			Error_Loop();
		}
	}
}


/*********************************************************************//**
 * @brief		Error Loop (called by Buffer_Verify() if any error)
 * @param[in]	none
 * @return 		None
 **********************************************************************/
void Error_Loop(void)
{
	_DBG(err_menu);

	/* Loop forever */
	while (1);
}


/*-------------------------MAIN FUNCTION--------------------------------*/
/*********************************************************************//**
 * @brief		c_entry: Main program body
 * @param[in]	None
 * @return 		int
 **********************************************************************/
int c_entry(void)
{
	GPDMA_Channel_CFG_Type GPDMACfg;
	GPDMA_LLI_Type DMA_LLI_Struct[2];

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

	/* GPDMA block section -------------------------------------------- */
    /* Disable GPDMA interrupt */
    NVIC_DisableIRQ(DMA_IRQn);
    /* preemption = 1, sub-priority = 1 */
    NVIC_SetPriority(DMA_IRQn, ((0x01<<3)|0x01));

    /* Initialize GPDMA controller */
	GPDMA_Init();

	/* Init GPDMA link list */
	DMA_LLI_Struct[0].SrcAddr = (uint32_t)&DMASrc_Buffer1;
	DMA_LLI_Struct[0].DstAddr = (uint32_t)&DMADest_Buffer;
	DMA_LLI_Struct[0].NextLLI = (uint32_t)&DMA_LLI_Struct[1];
	DMA_LLI_Struct[0].Control = (DMA_SIZE/2)
								| (2<<18) //source width 32 bit
								| (2<<21) //dest. width 32 bit
								| (1<<26) //source increment
								| (1<<27)
								;
	DMA_LLI_Struct[1].SrcAddr = (uint32_t)&DMASrc_Buffer2;
	DMA_LLI_Struct[1].DstAddr = ((uint32_t)&DMADest_Buffer) + (DMA_SIZE/2)*4;
	DMA_LLI_Struct[1].NextLLI = 0;
	DMA_LLI_Struct[1].Control = (DMA_SIZE/2)
								| (2<<18) //source width 32 bit
								| (2<<21) //dest. width 32 bit
								| (1<<26) //source increment
								| (1<<27)
								;

	// Setup GPDMA channel --------------------------------
	// channel 0
	GPDMACfg.ChannelNum = 0;
	// Source memory
	GPDMACfg.SrcMemAddr = (uint32_t)DMASrc_Buffer1;
	// Destination memory
	GPDMACfg.DstMemAddr = (uint32_t)DMADest_Buffer;
	// Transfer size
	GPDMACfg.TransferSize = DMA_SIZE;
	// Transfer width
	GPDMACfg.TransferWidth = GPDMA_WIDTH_WORD;
	// Transfer type
	GPDMACfg.TransferType = GPDMA_TRANSFERTYPE_M2M;
	// Source connection - unused
	GPDMACfg.SrcConn = 0;
	// Destination connection - unused
	GPDMACfg.DstConn = 0;
	// Linker List Item
	GPDMACfg.DMALLI = (uint32_t)&DMA_LLI_Struct[0];
	// Setup channel with given parameter
	GPDMA_Setup(&GPDMACfg);

	/* Reset terminal counter */
	Channel0_TC = 0;
	/* Reset Error counter */
	Channel0_Err = 0;

	_DBG_("Start transfer...");

	// Enable GPDMA channel 0
	GPDMA_ChannelCmd(0, ENABLE);

	/* Enable GPDMA interrupt */
	NVIC_EnableIRQ(DMA_IRQn);

	/* Wait for GPDMA processing complete */
	while ((Channel0_TC == 0) && (Channel0_Err == 0));

	/* Verify buffer */
	Buffer_Verify();

	_DBG(compl_menu);

    /* Loop forever */
    while(1);
}

/* With ARM and GHS toolsets, the entry point is main() - this will
 allow the linker to generate wrapper code to setup stacks, allocate
 heap area, and initialize and copy code and data segments. For GNU
 toolsets, the entry point is through __start() in the crt0_gnu.asm
 file, and that startup code will setup stacks and data */
int main(void) {
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
void check_failed(uint8_t *file, uint32_t line) {
	/* User can add his own implementation to report the file name and line number,
	 ex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */

	/* Infinite loop */
	while (1)
		;
}
#endif

/*
 * @}
 */
