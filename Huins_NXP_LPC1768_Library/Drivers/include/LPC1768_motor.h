/******************************************************************************
  * @file  LPC1768_motor.h
  * @author  Huins Embbeded Team  by HyunKH
  * @version V1.0.0
  * @date    2015. 02. 10
  * @brief   LPC1768 Servo Motor Driver	Header File
  ******************************************************************************/

/* Includes ------------------------------------------------------------------- */
#include "lpc17xx_gpio.h"
#include "LPC17xx.h"
#include "lpc_types.h"
#include "LPC1768_Huins.h"
#include "lpc17xx_pinsel.h"
#include "lpc17xx_exti.h"
#include "lpc17xx_uart.h"

void Motor_Init (void);
void StepMotor_Cycle(uint8_t cycle);

