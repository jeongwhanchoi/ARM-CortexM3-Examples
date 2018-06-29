/*----------------------------------------------------------------------------
 * Name:    demo.c
 * Purpose: USB HID Demo
 * Note(s): 
 *----------------------------------------------------------------------------
 * This file is part of the uVision/ARM development tools.
 * This software may only be used under the terms of a valid, current,
 * end user licence from KEIL for a compatible version of KEIL software
 * development tools. Nothing else gives you the right to use this software.
 *
 * This software is supplied "AS IS" without warranties of any kind.
 *
 * Copyright (c) 2008-2011 Keil - An ARM Company. All rights reserved.
 *----------------------------------------------------------------------------*/

#include "LPC17xx.H"                         /* LPC17xx definitions           */

#include "type.h"

#include "usb.h"
#include "usbcfg_LPC17xx.h"
#include "usbhw_LPC17xx.h"

#include "demo.h"

U8 InReport;                                /* HID Input Report    */
                                            /*   Bit0   : Buttons  */
                                            /*   Bit1..7: Reserved */

U8 OutReport;                               /* HID Out Report      */
                                            /*   Bit0..7: LEDs     */

/*------------------------------------------------------------------------------
  Get HID Input Report -> InReport
 *------------------------------------------------------------------------------*/
void GetInReport (void) {
  uint32_t kbd_val;

  kbd_val = (LPC_GPIO1->FIOPIN >> 20) & KBD_MASK;

  InReport = 0x00;
  if ((kbd_val & KBD_UP)     == 0) InReport |= 0x01;  /* up     pressed means 0 */
  if ((kbd_val & KBD_LEFT)   == 0) InReport |= 0x02;  /* left   pressed means 0 */
  if ((kbd_val & KBD_RIGHT)  == 0) InReport |= 0x04;  /* right  pressed means 0 */
  if ((kbd_val & KBD_SELECT) == 0) InReport |= 0x08;  /* select pressed means 0 */
  if ((kbd_val & KBD_DOWN)   == 0) InReport |= 0x10;  /* down   pressed means 0 */
}

/*------------------------------------------------------------------------------
  Set HID Output Report <- OutReport
 *------------------------------------------------------------------------------*/
void SetOutReport (void) {
  static unsigned long led_mask[] = { 1<<28, 1<<29, 1UL<<31, 1<<2, 1<<3, 1<<4, 1<<5, 1<<6 };
  int i;

  for (i = 0; i < LED_NUM; i++) {
    if (OutReport & (1<<i)) {
      if (i < 3) LPC_GPIO1->FIOPIN |= led_mask[i];
      else       LPC_GPIO2->FIOPIN |= led_mask[i];
    } else {
      if (i < 3) LPC_GPIO1->FIOPIN &= ~led_mask[i];
      else       LPC_GPIO2->FIOPIN &= ~led_mask[i];
    }
  }
}

/*------------------------------------------------------------------------------
  Main Program
 *------------------------------------------------------------------------------*/
int main (void) {

	/* P1.28, P1.29, P1.31 is output (LED) */
  LPC_GPIO1->FIODIR   |= ((1UL<<28)|(1UL<<29)|(1UL<<31));
	/* P2.2..6 is output (LED) */
  LPC_GPIO2->FIODIR   |= ((1UL<< 2)|(1UL<< 3)|(1UL<< 4)|(1UL<< 5)|(1UL<< 6)) ; 
	/* P1.20, P1.23..26    is input  (Joystick) */
  LPC_GPIO1->FIODIR   &= ~((1UL<<20)|(1UL<<23)|(1UL<<24)|(1UL<<25)|(1UL<<26));

  LPC_GPIO4->FIODIR   |=  (1UL<< 28);         /* Pin P2.28 is output (GLCD BAcklight) */
  LPC_GPIO4->FIOPIN   &= ~(1UL<< 28);         /* Turn backlight off */

  USB_Init();                                 /* USB Initialization */
  USB_Connect(__TRUE);            /* USB Connect */

  while (1);                                  /* Loop forever */
}
