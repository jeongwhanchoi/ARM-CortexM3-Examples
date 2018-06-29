/******************************************************************************
  * @file  DAC.c
  * @author  Huins Embbeded Team  by HyunKH
  * @version V1.0.0
  * @date    2015. 02. 09
  * @brief   DAC(Digital to Analog Converter)  Control
  ******************************************************************************/
	
/* Includes ----------------------------------------------------------*/
#include "lpc17xx_dac.h"
#include "dac.h"
#include "lpc17xx_gpdma.h"
#include "debug_frmwrk.h"
#include "LPC1768_utility.h"

/* Private struct ---------------------------------------------------------*/
	GPDMA_LLI_Type DMA_LLI_Struct;
	GPDMA_Channel_CFG_Type GPDMACfg;
	
/* Private function ---------------------------------------------------------*/
	void DMA_Init(void);

/* Private variables ---------------------------------------------------------*/
	/* UART0 Start �޼���*/
	uint8_t menu1[] =
	"********************************************************************\n\r"
	"\t Hello - Huins Embbeded Team \r\n"
	"\t UART0 Init / DAC Interrupt Example\r\n"
	"\t - MCU: LPC1768 \r\n"
	"\t - Communicate via: UART0 - 115200 bps \r\n"
	"********************************************************************\n\r";
	uint8_t i,option;	//	Wave ���� ����
	uint32_t dac_lut[NUM_SAMPLE];
	
int main(void)
{
	DAC_CONVERTER_CFG_Type DAC_ConverterConfigStruct;

	uint32_t tmp;

	uint32_t sin_0_to_90_11_samples[11]={0,1045,3090,4067,5877,6691,8090,8660,9510,9781,10000};

	Uart0_Init();	// UART0 �ʱ�ȭ
	
	UARTPuts(LPC_UART0,menu1);	//	UART0(RS232)�� �޼��� ���

	AF_ConfigPin(GPIO_PORT_0,PINSEL_PIN_26,PINSEL_FUNC_2);	//	P0.26 Pin AF Configuration (DAC)
	
	while(1)
	{
		/* DAC Wave ���� �޼��� */
		UARTPuts(LPC_UART0,"Please choose signal type:\n\r");
		UARTPuts(LPC_UART0,"\t1) Sine wave.\n\r");
		UARTPuts(LPC_UART0,"\t2) Triangle wave.\n\r");
		UARTPuts(LPC_UART0,"\t3) Escalator wave.\n\r");
		
		option = DAC_GENERATE_NONE;	//	Wave ���� �ʱ�ȭ

		while(option == DAC_GENERATE_NONE)	// Wave ������ ���� �ʾ���	�� 
		{
			switch(UARTGetChar(LPC_UART0))	// ����� �Է��� �޾ƿ´�.
			{
			case '1': option = DAC_GENERATE_SINE; break;							// �Է��� 1���̶�� Sine
			case '2': option = DAC_GENERATE_TRIANGLE; break;			//	�Է��� 2���̶�� Triangle
			case '3': option = DAC_GENERATE_ESCALATOR; break;	//	�Է��� 3���̶�� Escalator
			default:
				UARTPuts(LPC_UART0,"Wrong choice! Please select 1 or 2 or 3 only!\n\r");	//	�ٸ� Ű�� �Է��� ���
				option = DAC_GENERATE_NONE;
				break;
			}
		}

		switch(option)	// Wave ������ �Ǻ�
		{
		case DAC_GENERATE_SINE:	//	1�� Sine
			UARTPuts(LPC_UART0,"\n\rDAC is generating 60Hz sine wave...");
			for(i=0;i<NUM_SAMPLE_SINE;i++)	//	Sine wave �����
			{
				if(i<=15)
				{
					dac_lut[i] = 512 + 512*sin_0_to_90_11_samples[i]/10000;
					if(i==15) dac_lut[i]= 1023;
				}
				else if(i<=30)
				{
					dac_lut[i] = 512 + 512*sin_0_to_90_11_samples[30-i]/10000;
				}
				else if(i<=45)
				{
					dac_lut[i] = 512 - 512*sin_0_to_90_11_samples[i-30]/10000;
				}
				else
				{
					dac_lut[i] = 512 - 512*sin_0_to_90_11_samples[60-i]/10000;
				}
				dac_lut[i] = (dac_lut[i]<<6);
			}
			break;
			
		case DAC_GENERATE_TRIANGLE:	//	2�� Triangle
			UARTPuts(LPC_UART0,"\n\rDAC is generating 60Hz triangle wave...");
			for(i=0;i<NUM_SAMPLE;i++)	//	Triangle wave �����
			{
				if(i<32) dac_lut[i]= 32*i;
				else if (i==32) dac_lut[i]= 1023;
				else dac_lut[i] = 32*(NUM_SAMPLE-i);
				dac_lut[i] = (dac_lut[i]<<6);
			}
			break;
			
		case DAC_GENERATE_ESCALATOR:	//	3��	Escalator
			UARTPuts(LPC_UART0,"\n\rDAC is generating 60Hz escalator wave...");
			for(i=0;i<NUM_SAMPLE;i++)	//	Escalator wave �����
			{
				dac_lut[i] = (1023/3)*(i/16);
				dac_lut[i] = (dac_lut[i]<<6);
			}
			break;
		default: break;
		}
		
		DMA_Init();
		
		DAC_ConverterConfigStruct.CNT_ENA =SET;	//	�ڵ� ����� Reload
		DAC_ConverterConfigStruct.DMA_ENA = SET;	// DAC DMA ��� Enable
		DAC_Init(LPC_DAC);
		
		/* set time out for DAC*/
		tmp = (PCLK_DAC_IN_MHZ*1000000)/(SIGNAL_FREQ_IN_HZ*((option==DAC_GENERATE_SINE)?NUM_SAMPLE_SINE:NUM_SAMPLE));
		DAC_SetDMATimeOut(LPC_DAC,tmp);
		DAC_ConfigDAConverterControl(LPC_DAC, &DAC_ConverterConfigStruct); // ���� ����

		GPDMA_ChannelCmd(0, ENABLE);	// DMA 0 Channel Ȱ��ȭ
		UARTPuts(LPC_UART0,"\n\rPreass ESC if you want to terminate!");
		
		while(UARTGetChar(LPC_UART0)!=27);	// ESC Ű�� ������ �� ���� ������. (ASCII �ڵ� ����)

		GPDMA_ChannelCmd(0, DISABLE);	// DMA 0 Channel �� Ȱ��ȭ
	}
}

void DMA_Init(void)
{
	//Prepare DMA link list item structure
	DMA_LLI_Struct.SrcAddr= (uint32_t)dac_lut;
	DMA_LLI_Struct.DstAddr= (uint32_t)&(LPC_DAC->DACR);
	DMA_LLI_Struct.NextLLI= (uint32_t)&DMA_LLI_Struct;
	DMA_LLI_Struct.Control= ((option==DAC_GENERATE_SINE)?DMA_SIZE_SINE:DMA_SIZE)
					| (2<<18) //source width 32 bit
					| (2<<21) //dest. width 32 bit
					| (1<<26) //source increment
					;

	GPDMA_Init();

	// channel 0
	GPDMACfg.ChannelNum = 0;
	// Source memory
	GPDMACfg.SrcMemAddr = (uint32_t)(dac_lut);
	// Destination memory - unused
	GPDMACfg.DstMemAddr = 0;
	// Transfer size
	GPDMACfg.TransferSize = ((option==DAC_GENERATE_SINE)?DMA_SIZE_SINE:DMA_SIZE);
	// Transfer width - unused
	GPDMACfg.TransferWidth = 0;
	// Transfer type
	GPDMACfg.TransferType = GPDMA_TRANSFERTYPE_M2P;
	// Source connection - unused
	GPDMACfg.SrcConn = 0;
	// Destination connection
	GPDMACfg.DstConn = GPDMA_CONN_DAC;
	// Linker List Item - unused
	GPDMACfg.DMALLI = (uint32_t)&DMA_LLI_Struct;
	// Setup channel with given parameter
	GPDMA_Setup(&GPDMACfg);	
}
