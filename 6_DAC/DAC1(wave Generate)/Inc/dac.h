/************************** PRIVATE MACROS *************************/
/** DMA size of transfer */
#define DMA_SIZE_SINE		60
#define NUM_SAMPLE_SINE		60
#define DMA_SIZE			64
#define NUM_SAMPLE			64

#define SIGNAL_FREQ_IN_HZ	60
#define PCLK_DAC_IN_MHZ	25 //CCLK divided by 4

#define DAC_GENERATE_SINE		1
#define DAC_GENERATE_TRIANGLE	2
#define DAC_GENERATE_ESCALATOR	3
#define DAC_GENERATE_NONE		0
