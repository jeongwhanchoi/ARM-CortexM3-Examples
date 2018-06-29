/*----------------------------------------------------------------------------
 * Name:    LED.c
 * Purpose: MCB1700 low level LED functions
 * Version: V1.00
 * Note(s):
 *----------------------------------------------------------------------------
 * This file is part of the uVision/ARM development tools.
 * This software may only be used under the terms of a valid, current,
 * end user licence from KEIL for a compatible version of KEIL software
 * development tools. Nothing else gives you the right to use this software.
 *
 * This software is supplied "AS IS" without warranties of any kind.
 *
 * Copyright (c) 2009 Keil - An ARM Company. All rights reserved.
 *----------------------------------------------------------------------------
 * History:
 *          V1.00 Initial Version
 *----------------------------------------------------------------------------*/

#include <LPC17xx.H>                    /* LPC17xx definitions                */
#include "LED.h"

const unsigned long led_mask[] = { 1<<28, 1<<29, 1UL<<31, 1<<2, 1<<3, 1<<4, 1<<5, 1<<6 };

/*----------------------------------------------------------------------------
  initialize LED Pins
 *----------------------------------------------------------------------------*/
void LED_init (void) {
  LPC_GPIO1->FIODIR |= 0xB0000000;                 /* LEDs on PORT1  */
  LPC_GPIO2->FIODIR |= 0x0000007C;                 /* LEDs on PORT2  */
}


/*----------------------------------------------------------------------------
  Switch LED on. LED = Bitposition
 *----------------------------------------------------------------------------*/
void LED_on  (unsigned char led) {
  int i;

  for (i = 0; i < LED_NUM; i++) {
    if (led & (1<<i)) {
      if (i < 3) LPC_GPIO1->FIOPIN |= led_mask[i];
      else       LPC_GPIO2->FIOPIN |= led_mask[i];
    }
  }
}

/*----------------------------------------------------------------------------
  Switch Led off. LED = Bitposition
 *----------------------------------------------------------------------------*/
void LED_off (unsigned char led) {
  int i;

  for (i = 0; i < LED_NUM; i++) {
    if (led & (1<<i)) {
      if (i < 3) LPC_GPIO1->FIOPIN &= ~led_mask[i];
      else       LPC_GPIO2->FIOPIN &= ~led_mask[i];
    }
  }
}

/*----------------------------------------------------------------------------
  Output value to LEDs
 *----------------------------------------------------------------------------*/
void LED_out (unsigned char led) {
  int i;

  for (i = 0; i < LED_NUM; i++) {
    if (led & (1<<i)) {
      if (i < 3) LPC_GPIO1->FIOPIN |= led_mask[i];
      else       LPC_GPIO2->FIOPIN |= led_mask[i];
    } else {
      if (i < 3) LPC_GPIO1->FIOPIN &= ~led_mask[i];
      else       LPC_GPIO2->FIOPIN &= ~led_mask[i];
    }
  }
}
