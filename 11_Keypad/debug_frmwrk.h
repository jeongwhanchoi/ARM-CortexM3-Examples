/**
 * @file	: debug_frmwrk.c
 * @brief	: Contains some utilities that used for debugging through UART
 * @version	: 1.0
 * @date	: 18. Mar. 2009
 * @author	: HieuNguyen
 *----------------------------------------------------------------------------
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
 **********************************************************************/

#ifndef DEBUG_FRMWRK_H_
#define DEBUG_FRMWRK_H_

#include "lpc17xx_uart.h"

#define USED_UART_DEBUG_PORT	0

#if (USED_UART_DEBUG_PORT==0)
#define DEBUG_UART_PORT	UART0
#elif (USED_UART_DEBUG_PORT==1)
#define DEBUG_UART_PORT	UART1
#endif

#define _DBG(x)	 	_db_msg(DEBUG_UART_PORT, x)
#define _DBG_(x)	_db_msg_(DEBUG_UART_PORT, x)
#define _DBC(x)	 	_db_char(DEBUG_UART_PORT, x)
#define _DBD(x)	 	_db_dec(DEBUG_UART_PORT, x)
#define _DBD16(x)	 _db_dec_16(DEBUG_UART_PORT, x)
#define _DBD32(x)	 _db_dec_32(DEBUG_UART_PORT, x)
#define _DBH(x)	 	_db_hex(DEBUG_UART_PORT, x)
#define _DBH16(x)	 _db_hex_16(DEBUG_UART_PORT, x)
#define _DBH32(x)	 _db_hex_32(DEBUG_UART_PORT, x)
#define _DG			_db_get_char(DEBUG_UART_PORT)

extern void (*_db_msg)(UART_TypeDef *UARTx, const void *s);
extern void (*_db_msg_)(UART_TypeDef *UARTx, const void *s);
extern void (*_db_char)(UART_TypeDef *UARTx, uint8_t ch);
extern void (*_db_dec)(UART_TypeDef *UARTx, uint8_t decn);
extern void (*_db_dec_16)(UART_TypeDef *UARTx, uint16_t decn);
extern void (*_db_dec_32)(UART_TypeDef *UARTx, uint32_t decn);
extern void (*_db_hex)(UART_TypeDef *UARTx, uint8_t hexn);
extern void (*_db_hex_16)(UART_TypeDef *UARTx, uint16_t hexn);
extern void (*_db_hex_32)(UART_TypeDef *UARTx, uint32_t hexn);
extern uint8_t (*_db_get_char)(UART_TypeDef *UARTx);

void UARTPutChar (UART_TypeDef *UARTx, uint8_t ch);
void UARTPuts(UART_TypeDef *UARTx, const void *str);
void UARTPuts_(UART_TypeDef *UARTx, const void *str);
void UARTPutDec(UART_TypeDef *UARTx, uint8_t decnum);
void UARTPutDec16(UART_TypeDef *UARTx, uint16_t decnum);
void UARTPutDec32(UART_TypeDef *UARTx, uint32_t decnum);
void UARTPutHex (UART_TypeDef *UARTx, uint8_t hexnum);
void UARTPutHex16 (UART_TypeDef *UARTx, uint16_t hexnum);
void UARTPutHex32 (UART_TypeDef *UARTx, uint32_t hexnum);
uint8_t UARTGetChar (UART_TypeDef *UARTx);
void debug_frmwrk_init(void);

#endif /* DEBUG_FRMWRK_H_ */
