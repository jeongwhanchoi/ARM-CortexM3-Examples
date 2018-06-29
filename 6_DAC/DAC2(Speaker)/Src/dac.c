/******************************************************************************
  * @file  DAC.c
  * @author  Huins Embbeded Team  by HyunKH
  * @version V1.0.0
  * @date    2015. 02. 09
  * @brief   DAC(Digital to Analog Converter)  Control
  ******************************************************************************/
	
/* Includes ------------------------------------------------------------------*/
#include "lpc17xx_dac.h"
#include "LPC1768_utility.h"

int main(void)
{
	uint32_t value;
	float rate = 0;
	
	AF_ConfigPin(GPIO_PORT_0,PINSEL_PIN_26,PINSEL_FUNC_2);
	DAC_Init(LPC_DAC); //DAC initialization
	
	while(1)
	{
		for(value = 0; value < 1024; value++) 
		DAC_UpdateValue(LPC_DAC,value*rate); //Update DAC value
		
		rate += 0.1; //Increase DAC coefficient value
		
		if(rate == 1) //When DAC coefficient value is reached limit
			rate = 0; //Reset DAC coefficient value
	}
}
