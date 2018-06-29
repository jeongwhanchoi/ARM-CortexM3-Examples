/******************************************************************************/
/* BLINKY.C: LED Flasher                                                      */
/******************************************************************************/
/* This file is part of the uVision/ARM development tools.                    */
/* Copyright (c) 2008 Keil Software. All rights reserved.                     */
/* This software may only be used under the terms of a valid, current,        */
/* end user licence from KEIL for a compatible version of KEIL software       */
/* development tools. Nothing else gives you the right to use this software.  */
/******************************************************************************/
                  
#include "LPC17xx.H"                    /* LPC17xx definitions                */
#include "LED.H"
#include "Keypad.H"                    	/* FND definitions           	       */

void Keypad_test(){
  uint8_t Keypad_Value=0;
  Keypad_Value = Keypad('C');
  if (Keypad_Value & 0x01) LPC_GPIO2->FIOPIN |= (1<<6); // LED 1 ON
  else LPC_GPIO2->FIOPIN &= ~(1<<6);
  if (Keypad_Value >> 1 & 0x01 ) LPC_GPIO2->FIOPIN |= (1<<5); // LED 2 ON
  else LPC_GPIO2->FIOPIN &= ~(1<<5);
  if (Keypad_Value >> 2 & 0x01 ) LPC_GPIO2->FIOPIN |= (1<<4); // LED 3 ON
  else LPC_GPIO2->FIOPIN &= ~(1<<4);
  if (Keypad_Value >> 3 & 0x01 ) LPC_GPIO2->FIOPIN |= (1<<3); // LED 4 ON
  else LPC_GPIO2->FIOPIN &= ~(1<<3);
  if (Keypad_Value >> 4 & 0x01 ) LPC_GPIO2->FIOPIN |= (1<<2); // LED 5 ON
  else LPC_GPIO2->FIOPIN &= ~(1<<2);
  if (Keypad_Value >> 5 & 0x01 ) LPC_GPIO1->FIOPIN |= (1UL<<31); // LED 6 ON
  else LPC_GPIO1->FIOPIN &= ~(1UL<<31);
  if (Keypad_Value >> 6 & 0x01 ) LPC_GPIO1->FIOPIN |= (1<<29); // LED 7 ON
  else LPC_GPIO1->FIOPIN &= ~(1<<29);
  if (Keypad_Value >> 7 & 0x01 ) LPC_GPIO1->FIOPIN |= (1<<28); // LED 8 ON
  else LPC_GPIO1->FIOPIN &= ~(1<<28);
}
	
int main (void) {                       /* Main Program                       */	
  SystemInit();
  LED_init();
  EXT_IO_init();
  Keypad_DIR_Input();	   			/* Keypad direction = input */

  for (;;) {    /* Loop forever                       */
		Keypad_test();
  }
}
