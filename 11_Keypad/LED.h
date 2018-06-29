				   
#ifndef __LED_H__
#define __LED_H__

void LED_init(){
	LPC_GPIO2->FIODIR |= (1<<6); // LED 1 ON
	LPC_GPIO2->FIODIR |= (1<<5); // LED 2 ON
  LPC_GPIO2->FIODIR |= (1<<4); // LED 3 ON
  LPC_GPIO2->FIODIR |= (1<<3); // LED 4 ON
  LPC_GPIO2->FIODIR |= (1<<2); // LED 5 ON
  LPC_GPIO1->FIODIR |= (1UL<<31); // LED 6 ON
  LPC_GPIO1->FIODIR |= (1<<29); // LED 7 ON
	LPC_GPIO1->FIODIR |= (1<<28); // LED 8 ON
}

#endif  // __Keypad_H__
