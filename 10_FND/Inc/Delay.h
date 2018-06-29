#ifndef __Delay_H__
#define __Delay_H__

volatile unsigned long SysTickCnt;     /* SysTick Counter                    */
volatile unsigned long FND_Cnt=0;      /* FND_Cnt Counter                    */
volatile unsigned long FND_Run_Cnt=0;  /* FND_Run_Cont Counter  	         */

//void SysTick_Handler (void) {           /* SysTick Interrupt Handler (1ms)    */
//  SysTickCnt++;
//  FND_Cnt++;
//  FND_Run_Cnt++;
//}

//void Delay (unsigned long tick) {       /* Delay Function                     */
//  unsigned long systickcnt;

//  systickcnt = SysTickCnt;
//  while ((SysTickCnt - systickcnt) < tick);
//}

#endif  // __Delay_H__
