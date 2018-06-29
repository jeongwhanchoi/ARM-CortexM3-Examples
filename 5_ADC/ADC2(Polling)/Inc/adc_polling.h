//ADC2 Example

#include "lpc17xx_adc.h"
#include "lpc17xx_uart.h"
#include "lpc17xx_timer.h"
#include "lpc17xx_libcfg.h"
#include "lpc17xx_pinsel.h"
#include "debug_frmwrk.h"

uint8_t menu1[] =
"********************************************************************************\n\r"
"Hello NXP Semiconductors \n\r"
" LPC_ADC demo \n\r"
"\t - MCU: LPC17xx \n\r"
"\t - ARM COTEX \n\r"
"\t - Communicate via: UART0 - 115200 bps \n\r"
" Use LPC_ADC with 12-bit resolution at freq = 1MHz, read in polling mode\n\r"
" To get LPC_ADC0 value on channel 2 and display via UART0\n\r"
" Turn the potentiometer to see how LPC_ADC value changes\n\r"
"********************************************************************************\n\r";
TIM_TIMERCFG_Type TIM_ConfigStruct;
TIM_MATCHCFG_Type TIM_MatchConfigStruct ;

void print_menu(void);
void Timer_Wait(uint32_t time);

void print_menu(void)
{
	_DBG(menu1); //display initial message
}

void Timer_Wait(uint32_t time)
{
	/* Initialize timer 0, prescale count time of 1000uS */
	TIM_ConfigStruct.PrescaleOption = TIM_PRESCALE_USVAL;
	TIM_ConfigStruct.PrescaleValue	= 1000;
	
	TIM_MatchConfigStruct.MatchChannel = 0; //use channel 0, MR0
	TIM_MatchConfigStruct.IntOnMatch = ENABLE; //Enable interrupt when MR0 matches the Value in TC Register
	TIM_MatchConfigStruct.ResetOnMatch = DISABLE; //Disable to reset on MR0: TIMER will reset if MR0 matches it
	TIM_MatchConfigStruct.StopOnMatch = ENABLE; //Enable to stop on MR0 if MR0 matches it
	TIM_MatchConfigStruct.ExtMatchOutputType = TIM_EXTMATCH_NOTHING; //No output MR0.0 pin if MR0 matches it
	TIM_MatchConfigStruct.MatchValue = time; //Set Match Value, count Value of time (time * 1000uS = time msec --> 1/time Hz)

	/* Set configuration for Tim_config and Tim_MatchConfig */
	TIM_Init(LPC_TIM0, TIM_TIMER_MODE,&TIM_ConfigStruct);
	TIM_ConfigMatch(LPC_TIM0,&TIM_MatchConfigStruct);

	TIM_Cmd(LPC_TIM0,ENABLE); //Start TIM0
	
	while ( !(TIM_GetIntStatus(LPC_TIM0,TIM_MR0_INT))); //Wait until TIM0 channel 0 interrupt flag bit is set
	TIM_ClearIntPending(LPC_TIM0,TIM_MR0_INT); //Clear TIM0 channel 0 interrupt flag bit
}

int main (void)
{
	PINSEL_CFG_Type PinCfg;

	uint32_t LPC_ADC_value;
	
	SystemInit(); //system initialization

	debug_frmwrk_init(); //Debug framework initialization

	print_menu(); //display initial message

	PinCfg.Portnum = 0; //Set port number as 0
	PinCfg.Pinnum = 25; //Set pin number as 25
	PinCfg.Funcnum = 1; //Set function number as ADC
	PinCfg.Pinmode = 0; //Set internal pull up
	PinCfg.OpenDrain = 0; //Set no open drain
	
	PINSEL_ConfigPin(&PinCfg); //Save PinCfg parameter

	ADC_Init(LPC_ADC, 200000); //ADC initialization 200kHz
	ADC_IntConfig(LPC_ADC,ADC_ADINTEN2,DISABLE); //ADC channel2 interrupt configuration
	ADC_ChannelCmd(LPC_ADC,ADC_CHANNEL_2,ENABLE); //Enable ADC channel2

	while(1)
	{
		ADC_StartCmd(LPC_ADC,ADC_START_NOW); //Start conversion 1 time

		while (!(ADC_ChannelGetStatus(LPC_ADC,ADC_CHANNEL_2,ADC_DATA_DONE))); //Check ADC is comlete
		LPC_ADC_value = ADC_ChannelGetData(LPC_ADC,ADC_CHANNEL_2); //Get ADC channel 2 raw data

		_DBG("LPC_ADC value on channel 2: "); //Display string
		_DBD32(LPC_ADC_value); //Display ADC raw value
		_DBG_(""); //Display string

		Timer_Wait(1000); //Delay = 1sec
	}
}
