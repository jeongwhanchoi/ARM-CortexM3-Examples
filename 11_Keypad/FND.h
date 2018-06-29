				   
#ifndef __FND_H__
#define __FND_H__

void FND_init(){
/* LEDs on PORT0 defined as Output    */
  	LPC_GPIO0->FIODIR |= (1<<4)|(1<<5)|(1<<10)|(1<<11)|(1<<19)|(1<<23)|(1<<24) ;
  	/* LEDs on PORT1 defined as Output    */
  	LPC_GPIO1->FIODIR |= (1<<21);
  	/* LEDs on PORT2 defined as Output    */
  	LPC_GPIO2->FIODIR |= (1<<11)|(1<<12)|(1<<13);
  	/* LEDs on PORT3 defined as Output    */
  	LPC_GPIO3->FIODIR |= (1<<25)|(1<<26);
}
void EXT_IO_A_CS(){
	/* EXT_IO_A, DIR nOE setting B->A*/
    LPC_GPIO0->FIOPIN &= ~(1<<4);  // DIR B->A
	LPC_GPIO0->FIOPIN &= ~(1<<19); // EXT_IO_A On
	LPC_GPIO0->FIOPIN |= (1<<20);  // EXT_IO_B Off 
	LPC_GPIO0->FIOPIN |= (1<<21);  // EXT_IO_C Off
}
void EXT_IO_B_CS(){
	/* EXT_IO_B, DIR nOE setting B->A*/
    LPC_GPIO0->FIOPIN &= ~(1<<4);  	// DIR B->A
	LPC_GPIO0->FIOPIN |= (1<<19); 	// EXT_IO_A Off
	LPC_GPIO0->FIOPIN &= ~(1<<20);  // EXT_IO_B On 
	LPC_GPIO0->FIOPIN |= (1<<21);  	// EXT_IO_C Off
}
void EXT_IO_C_CS(){
	/* EXT_IO_C, DIR nOE setting B->A*/
    LPC_GPIO0->FIOPIN &= ~(1<<4);  	// DIR B->A
	LPC_GPIO0->FIOPIN |= (1<<19); 	// EXT_IO_A Off
	LPC_GPIO0->FIOPIN |= (1<<20); 	// EXT_IO_B Off 
	LPC_GPIO0->FIOPIN &= ~(1<<21);  // EXT_IO_C On
}
void FND_Data_Reset(){
	// FND Data setting 
	LPC_GPIO0->FIOPIN |= (1<<23); // FND A
	LPC_GPIO0->FIOPIN |= (1<<24); // FND B
	LPC_GPIO1->FIOPIN |= (1<<21); // FND C
	LPC_GPIO2->FIOPIN |= (1<<11); // FND D
	LPC_GPIO2->FIOPIN |= (1<<12); // FND E
	LPC_GPIO2->FIOPIN |= (1<<13); // FND F
	LPC_GPIO3->FIOPIN |= (1<<25); // FND G
	LPC_GPIO3->FIOPIN |= (1<<26); // FND DP
}

void FND_Data_Set_0(){
	// FND Data setting 
	LPC_GPIO0->FIOPIN &= ~(1<<23); // FND A
	LPC_GPIO0->FIOPIN &= ~(1<<24); // FND B
	LPC_GPIO1->FIOPIN &= ~(1<<21); // FND C
	LPC_GPIO2->FIOPIN &= ~(1<<11); // FND D
	LPC_GPIO2->FIOPIN &= ~(1<<12); // FND E
	LPC_GPIO2->FIOPIN &= ~(1<<13); // FND F
	LPC_GPIO3->FIOPIN |= (1<<25); // FND G
	LPC_GPIO3->FIOPIN |= (1<<26); // FND DP
}

void FND_Data_Set_1(){
	// FND Data setting 
	LPC_GPIO0->FIOPIN |= (1<<23); // FND A
	LPC_GPIO0->FIOPIN &= ~(1<<24); // FND B
	LPC_GPIO1->FIOPIN &= ~(1<<21); // FND C
	LPC_GPIO2->FIOPIN |= (1<<11); // FND D
	LPC_GPIO2->FIOPIN |= (1<<12); // FND E
	LPC_GPIO2->FIOPIN |= (1<<13); // FND F
	LPC_GPIO3->FIOPIN |= (1<<25); // FND G
	LPC_GPIO3->FIOPIN |= (1<<26); // FND DP
}
void FND_Data_Set_2(){
	// FND Data setting 
	LPC_GPIO0->FIOPIN &= ~(1<<23); // FND A
	LPC_GPIO0->FIOPIN &= ~(1<<24); // FND B
	LPC_GPIO1->FIOPIN |= (1<<21); // FND C
	LPC_GPIO2->FIOPIN &= ~(1<<11); // FND D
	LPC_GPIO2->FIOPIN &= ~(1<<12); // FND E
	LPC_GPIO2->FIOPIN |= (1<<13); // FND F
	LPC_GPIO3->FIOPIN &= ~(1<<25); // FND G
	LPC_GPIO3->FIOPIN |= (1<<26); // FND DP
}
void FND_Data_Set_3(){
	// FND Data setting 
	LPC_GPIO0->FIOPIN &= ~(1<<23); // FND A
	LPC_GPIO0->FIOPIN &= ~(1<<24); // FND B
	LPC_GPIO1->FIOPIN &= ~(1<<21); // FND C
	LPC_GPIO2->FIOPIN &= ~(1<<11); // FND D
	LPC_GPIO2->FIOPIN |= (1<<12); // FND E
	LPC_GPIO2->FIOPIN |= (1<<13); // FND F
	LPC_GPIO3->FIOPIN &= ~(1<<25); // FND G
	LPC_GPIO3->FIOPIN |= (1<<26); // FND DP
}
void FND_Data_Set_4(){
	// FND Data setting 
	LPC_GPIO0->FIOPIN |= (1<<23); // FND A
	LPC_GPIO0->FIOPIN &= ~(1<<24); // FND B
	LPC_GPIO1->FIOPIN &= ~(1<<21); // FND C
	LPC_GPIO2->FIOPIN |= (1<<11); // FND D
	LPC_GPIO2->FIOPIN |= (1<<12); // FND E
	LPC_GPIO2->FIOPIN &= ~(1<<13); // FND F
	LPC_GPIO3->FIOPIN &= ~(1<<25); // FND G
	LPC_GPIO3->FIOPIN |= (1<<26); // FND DP
}
void FND_Data_Set_5(){
	// FND Data setting 
	LPC_GPIO0->FIOPIN &= ~(1<<23); // FND A
	LPC_GPIO0->FIOPIN |= (1<<24); // FND B
	LPC_GPIO1->FIOPIN &= ~(1<<21); // FND C
	LPC_GPIO2->FIOPIN &= ~(1<<11); // FND D
	LPC_GPIO2->FIOPIN |= (1<<12); // FND E
	LPC_GPIO2->FIOPIN &= ~(1<<13); // FND F
	LPC_GPIO3->FIOPIN &= ~(1<<25); // FND G
	LPC_GPIO3->FIOPIN |= (1<<26); // FND DP
}
void FND_Data_Set_6(){
	// FND Data setting 
	LPC_GPIO0->FIOPIN &= ~(1<<23); // FND A
	LPC_GPIO0->FIOPIN |= (1<<24); // FND B
	LPC_GPIO1->FIOPIN &= ~(1<<21); // FND C
	LPC_GPIO2->FIOPIN &= ~(1<<11); // FND D
	LPC_GPIO2->FIOPIN &= ~(1<<12); // FND E
	LPC_GPIO2->FIOPIN &= ~(1<<13); // FND F
	LPC_GPIO3->FIOPIN &= ~(1<<25); // FND G
	LPC_GPIO3->FIOPIN |= (1<<26); // FND DP
}
void FND_Data_Set_7(){
	// FND Data setting 
	LPC_GPIO0->FIOPIN &= ~(1<<23); // FND A
	LPC_GPIO0->FIOPIN &= ~(1<<24); // FND B
	LPC_GPIO1->FIOPIN &= ~(1<<21); // FND C
	LPC_GPIO2->FIOPIN |= (1<<11); // FND D
	LPC_GPIO2->FIOPIN |= (1<<12); // FND E
	LPC_GPIO2->FIOPIN &= ~(1<<13); // FND F
	LPC_GPIO3->FIOPIN |= (1<<25); // FND G
	LPC_GPIO3->FIOPIN |= (1<<26); // FND DP
}
void FND_Data_Set_8(){
	// FND Data setting 
	LPC_GPIO0->FIOPIN &= ~(1<<23); // FND A
	LPC_GPIO0->FIOPIN &= ~(1<<24); // FND B
	LPC_GPIO1->FIOPIN &= ~(1<<21); // FND C
	LPC_GPIO2->FIOPIN &= ~(1<<11); // FND D
	LPC_GPIO2->FIOPIN &= ~(1<<12); // FND E
	LPC_GPIO2->FIOPIN &= ~(1<<13); // FND F
	LPC_GPIO3->FIOPIN &= ~(1<<25); // FND G
	LPC_GPIO3->FIOPIN |= (1<<26); // FND DP
}
void FND_Data_Set_9(){
	// FND Data setting 
	LPC_GPIO0->FIOPIN &= ~(1<<23); // FND A
	LPC_GPIO0->FIOPIN &= ~(1<<24); // FND B
	LPC_GPIO1->FIOPIN &= ~(1<<21); // FND C
	LPC_GPIO2->FIOPIN &= ~(1<<11); // FND D
	LPC_GPIO2->FIOPIN |= (1<<12); // FND E
	LPC_GPIO2->FIOPIN &= ~(1<<13); // FND F
	LPC_GPIO3->FIOPIN &= ~(1<<25); // FND G
	LPC_GPIO3->FIOPIN |= (1<<26); // FND DP
}
void FND_Data_CS(){
	// FND Data CS setting 
	int i;
	LPC_GPIO0->FIOPIN |= (1<<5);    
	for(i=0;i<100;i++);                          /* Delay                         */
	LPC_GPIO0->FIOPIN &= ~(1<<5);   
}
void FND_COM_Set_1(){
	// FND COM setting - 1
	LPC_GPIO0->FIOPIN |= (1<<23); // DIC 1
	LPC_GPIO0->FIOPIN &= ~(1<<24); // DIC 2
	LPC_GPIO1->FIOPIN &= ~(1<<21); // DIC 3
	LPC_GPIO2->FIOPIN &= ~(1<<11); // DIC 4
	LPC_GPIO2->FIOPIN &= ~(1<<12); // DIC 5
	LPC_GPIO2->FIOPIN &= ~(1<<13); // DIC 6
	LPC_GPIO3->FIOPIN &= ~(1<<25); // DIC 7
	LPC_GPIO3->FIOPIN &= ~(1<<26); // DIC 8
}
void FND_COM_Set_2(){
	// FND COM setting - 2
	LPC_GPIO0->FIOPIN &= ~(1<<23); // DIC 1
	LPC_GPIO0->FIOPIN |= (1<<24); // DIC 2
	LPC_GPIO1->FIOPIN &= ~(1<<21); // DIC 3
	LPC_GPIO2->FIOPIN &= ~(1<<11); // DIC 4
	LPC_GPIO2->FIOPIN &= ~(~1<<12); // DIC 5
	LPC_GPIO2->FIOPIN &= ~(1<<13); // DIC 6
	LPC_GPIO3->FIOPIN &= ~(1<<25); // DIC 7
	LPC_GPIO3->FIOPIN &= ~(1<<26); // DIC 8
}
void FND_COM_Set_3(){
	// FND COM setting - 3
	LPC_GPIO0->FIOPIN &= ~(1<<23); // DIC 1
	LPC_GPIO0->FIOPIN &= ~(1<<24); // DIC 2
	LPC_GPIO1->FIOPIN |= (1<<21); // DIC 3
	LPC_GPIO2->FIOPIN &= ~(1<<11); // DIC 4
	LPC_GPIO2->FIOPIN &= ~(1<<12); // DIC 5
	LPC_GPIO2->FIOPIN &= ~(1<<13); // DIC 6
	LPC_GPIO3->FIOPIN &= ~(1<<25); // DIC 7
	LPC_GPIO3->FIOPIN &= ~(1<<26); // DIC 8
}
void FND_COM_Set_4(){
	// FND COM setting - 4
	LPC_GPIO0->FIOPIN &= ~(1<<23); // DIC 1
	LPC_GPIO0->FIOPIN &= ~(1<<24); // DIC 2
	LPC_GPIO1->FIOPIN &= ~(1<<21); // DIC 3
	LPC_GPIO2->FIOPIN |= (1<<11); // DIC 4
	LPC_GPIO2->FIOPIN &= ~(1<<12); // DIC 5
	LPC_GPIO2->FIOPIN &= ~(1<<13); // DIC 6
	LPC_GPIO3->FIOPIN &= ~(1<<25); // DIC 7
	LPC_GPIO3->FIOPIN &= ~(1<<26); // DIC 8
}
void FND_COM_Set_5(){
	// FND COM setting - 5
	LPC_GPIO0->FIOPIN &= ~(1<<23); // DIC 1
	LPC_GPIO0->FIOPIN &= ~(1<<24); // DIC 2
	LPC_GPIO1->FIOPIN &= ~(1<<21); // DIC 3
	LPC_GPIO2->FIOPIN &= ~(1<<11); // DIC 4
	LPC_GPIO2->FIOPIN |= (1<<12); // DIC 5
	LPC_GPIO2->FIOPIN &= ~(1<<13); // DIC 6
	LPC_GPIO3->FIOPIN &= ~(1<<25); // DIC 7
	LPC_GPIO3->FIOPIN &= ~(1<<26); // DIC 8
}
void FND_COM_Set_6(){
	// FND COM setting - 6
	LPC_GPIO0->FIOPIN &= ~(1<<23); // DIC 1
	LPC_GPIO0->FIOPIN &= ~(1<<24); // DIC 2
	LPC_GPIO1->FIOPIN &= ~(1<<21); // DIC 3
	LPC_GPIO2->FIOPIN &= ~(1<<11); // DIC 4
	LPC_GPIO2->FIOPIN &= ~(1<<12); // DIC 5
	LPC_GPIO2->FIOPIN |= (1<<13); // DIC 6
	LPC_GPIO3->FIOPIN &= ~(1<<25); // DIC 7
	LPC_GPIO3->FIOPIN &= ~(1<<26); // DIC 8
}
void FND_COM_Set_7(){
	// FND COM setting - 7
	LPC_GPIO0->FIOPIN &= ~(1<<23); // DIC 1
	LPC_GPIO0->FIOPIN &= ~(1<<24); // DIC 2
	LPC_GPIO1->FIOPIN &= ~(1<<21); // DIC 3
	LPC_GPIO2->FIOPIN &= ~(1<<11); // DIC 4
	LPC_GPIO2->FIOPIN &= ~(1<<12); // DIC 5
	LPC_GPIO2->FIOPIN &= ~(1<<13); // DIC 6
	LPC_GPIO3->FIOPIN |= (1<<25); // DIC 7
	LPC_GPIO3->FIOPIN &= ~(1<<26); // DIC 8
}
void FND_COM_Set_8(){
	// FND COM setting - 8
	LPC_GPIO0->FIOPIN &= ~(1<<23); // DIC 1
	LPC_GPIO0->FIOPIN &= ~(1<<24); // DIC 2
	LPC_GPIO1->FIOPIN &= ~(1<<21); // DIC 3
	LPC_GPIO2->FIOPIN &= ~(1<<11); // DIC 4
	LPC_GPIO2->FIOPIN &= ~(1<<12); // DIC 5
	LPC_GPIO2->FIOPIN &= ~(1<<13); // DIC 6
	LPC_GPIO3->FIOPIN &= ~(1<<25); // DIC 7
	LPC_GPIO3->FIOPIN |= (1<<26); // DIC 8
}


void FND_COM_CS(){
	// FND COM CS Setting 
	int i;
	LPC_GPIO0->FIOPIN |= (1<<10);    
	for(i=0;i<100;i++); 
	LPC_GPIO0->FIOPIN &= ~(1<<10); 
}

void FND_Run(unsigned char EXT_IO_DIR, unsigned char fnd_num_1, unsigned char fnd_num_2, unsigned char fnd_num_3, 
             unsigned char fnd_num_4, unsigned char fnd_num_5, unsigned char fnd_num_6, unsigned char fnd_num_7,  
			 unsigned char fnd_num_8){

  	if (EXT_IO_DIR == 'A')	EXT_IO_A_CS();
	else if (EXT_IO_DIR=='B') EXT_IO_B_CS();
	else EXT_IO_C_CS();

	if (FND_Run_Cnt == 2){
		switch(fnd_num_1){
			case 0 : 
				FND_Data_Reset();
				FND_Data_CS();
				FND_Data_Set_0();
				FND_Data_CS();
				FND_COM_Set_1();
				FND_COM_CS();
				break;
			case 1 : 
				FND_Data_Reset();
				FND_Data_CS();
				FND_Data_Set_1();
				FND_Data_CS();
				FND_COM_Set_1();
				FND_COM_CS();
				break;
			case 2 : 
				FND_Data_Reset();
				FND_Data_CS();
				FND_Data_Set_2();
				FND_Data_CS();
				FND_COM_Set_1();
				FND_COM_CS();
				break;
			case 3 : 
				FND_Data_Reset();
				FND_Data_CS();
				FND_Data_Set_3();
				FND_Data_CS();
				FND_COM_Set_1();
				FND_COM_CS();
				break;
			case 4 : 
				FND_Data_Reset();
				FND_Data_CS();
				FND_Data_Set_4();
				FND_Data_CS();
				FND_COM_Set_1();
				FND_COM_CS();
				break;
			case 5 : 
				FND_Data_Reset();
				FND_Data_CS();
				FND_Data_Set_5();
				FND_Data_CS();
				FND_COM_Set_1();
				FND_COM_CS();
				break;
			case 6 : 
				FND_Data_Reset();
				FND_Data_CS();
				FND_Data_Set_6();
				FND_Data_CS();
				FND_COM_Set_1();
				FND_COM_CS();
				break;
			case 7 : 
				FND_Data_Reset();
				FND_Data_CS();
				FND_Data_Set_7();
				FND_Data_CS();
				FND_COM_Set_1();
				FND_COM_CS();
				break;
			case 8 : 
				FND_Data_Reset();
				FND_Data_CS();
				FND_Data_Set_8();
				FND_Data_CS();
				FND_COM_Set_1();
				FND_COM_CS();
				break;
			case 9 : 
				FND_Data_Reset();
				FND_Data_CS();
				FND_Data_Set_9();
				FND_Data_CS();
				FND_COM_Set_1();
				FND_COM_CS();
				break;
		} // end switch fnd_num_1
	}
	if (FND_Run_Cnt == 4){
		switch(fnd_num_2){
			case 0 : 
				FND_Data_Reset();
				FND_Data_CS();
				FND_Data_Set_0();
				FND_Data_CS();
				FND_COM_Set_2();
				FND_COM_CS();
				break;
			case 1 : 
				FND_Data_Reset();
				FND_Data_CS();
				FND_Data_Set_1();
				FND_Data_CS();
				FND_COM_Set_2();
				FND_COM_CS();
				break;
			case 2 : 
				FND_Data_Reset();
				FND_Data_CS();
				FND_Data_Set_2();
				FND_Data_CS();
				FND_COM_Set_2();
				FND_COM_CS();
				break;
			case 3 : 
				FND_Data_Reset();
				FND_Data_CS();
				FND_Data_Set_3();
				FND_Data_CS();
				FND_COM_Set_2();
				FND_COM_CS();
				break;
			case 4 : 
				FND_Data_Reset();
				FND_Data_CS();
				FND_Data_Set_4();
				FND_Data_CS();
				FND_COM_Set_2();
				FND_COM_CS();
				break;
			case 5 : 
				FND_Data_Reset();
				FND_Data_CS();
				FND_Data_Set_5();
				FND_Data_CS();
				FND_COM_Set_2();
				FND_COM_CS();
				break;
			case 6 : 
				FND_Data_Reset();
				FND_Data_CS();
				FND_Data_Set_6();
				FND_Data_CS();
				FND_COM_Set_2();
				FND_COM_CS();
				break;
			case 7 : 
				FND_Data_Reset();
				FND_Data_CS();
				FND_Data_Set_7();
				FND_Data_CS();
				FND_COM_Set_2();
				FND_COM_CS();
				break;
			case 8 : 
				FND_Data_Reset();
				FND_Data_CS();
				FND_Data_Set_8();
				FND_Data_CS();
				FND_COM_Set_2();
				FND_COM_CS();
				break;
			case 9 : 
				FND_Data_Reset();
				FND_Data_CS();
				FND_Data_Set_9();
				FND_Data_CS();
				FND_COM_Set_2();
				FND_COM_CS();
				break;
		 }
	}
	if (FND_Run_Cnt == 6){
			 switch(fnd_num_3){
				case 0 : 
					FND_Data_Reset();
					FND_Data_CS();
				FND_Data_Set_0();
				FND_Data_CS();
				FND_COM_Set_3();
				FND_COM_CS();
				break;
		 	case 1 : 
				FND_Data_Reset();
				FND_Data_CS();
				FND_Data_Set_1();
				FND_Data_CS();
				FND_COM_Set_3();
				FND_COM_CS();
				break;
			case 2 : 
				FND_Data_Reset();
				FND_Data_CS();
				FND_Data_Set_2();
				FND_Data_CS();
				FND_COM_Set_3();
				FND_COM_CS();
				break;
			case 3 : 
			 	FND_Data_Reset();
				FND_Data_CS();
				FND_Data_Set_3();
				FND_Data_CS();
				FND_COM_Set_3();
				FND_COM_CS();
				break;
			case 4 : 
				FND_Data_Reset();
				FND_Data_CS();
				FND_Data_Set_4();
				FND_Data_CS();
				FND_COM_Set_3();
				FND_COM_CS();
				break;
			case 5 : 
				FND_Data_Reset();
				FND_Data_CS();
				FND_Data_Set_5();
				FND_Data_CS();
				FND_COM_Set_3();
				FND_COM_CS();
				break;
			case 6 : 
				FND_Data_Reset();
				FND_Data_CS();
				FND_Data_Set_6();
				FND_Data_CS();
				FND_COM_Set_3();
				FND_COM_CS();
				break;
			case 7 : 
				FND_Data_Reset();
				FND_Data_CS();
				FND_Data_Set_7();
				FND_Data_CS();
				FND_COM_Set_3();
				FND_COM_CS();
				break;
			case 8 : 
				FND_Data_Reset();
				FND_Data_CS();
				FND_Data_Set_8();
				FND_Data_CS();
				FND_COM_Set_3();
				FND_COM_CS();
				break;
			case 9 : 
				FND_Data_Reset();
				FND_Data_CS();
				FND_Data_Set_9();
				FND_Data_CS();
				FND_COM_Set_3();
				FND_COM_CS();
				break;
		 }	
	}	   				
	if (FND_Run_Cnt == 8){
		 switch(fnd_num_4){
		 	case 0 : 
				FND_Data_Reset();
				FND_Data_CS();
				FND_Data_Set_0();
				FND_Data_CS();
				FND_COM_Set_4();
				FND_COM_CS();
				break;
		 	case 1 : 
				FND_Data_Reset();
				FND_Data_CS();
				FND_Data_Set_1();
				FND_Data_CS();
				FND_COM_Set_4();
				FND_COM_CS();
				break;
			case 2 : 
				FND_Data_Reset();
				FND_Data_CS();
				FND_Data_Set_2();
				FND_Data_CS();
				FND_COM_Set_4();
				FND_COM_CS();
				break;
			case 3 : 
				FND_Data_Reset();
				FND_Data_CS();
				FND_Data_Set_3();
				FND_Data_CS();
				FND_COM_Set_4();
				FND_COM_CS();
				break;
			case 4 : 
				FND_Data_Reset();
				FND_Data_CS();
				FND_Data_Set_4();
				FND_Data_CS();
				FND_COM_Set_4();
				FND_COM_CS();
				break;
			case 5 : 
				FND_Data_Reset();
				FND_Data_CS();
				FND_Data_Set_5();
				FND_Data_CS();
				FND_COM_Set_4();
				FND_COM_CS();
				break;
			case 6 : 
				FND_Data_Reset();
				FND_Data_CS();
				FND_Data_Set_6();
				FND_Data_CS();
				FND_COM_Set_4();
				FND_COM_CS();
				break;
			case 7 : 
				FND_Data_Reset();
				FND_Data_CS();
				FND_Data_Set_7();
				FND_Data_CS();
				FND_COM_Set_4();
				FND_COM_CS();
				break;
			case 8 : 
				FND_Data_Reset();
				FND_Data_CS();
				FND_Data_Set_8();
				FND_Data_CS();
				FND_COM_Set_4();
				FND_COM_CS();
				break;
			case 9 : 
				FND_Data_Reset();
				FND_Data_CS();
				FND_Data_Set_9();
				FND_Data_CS();
				FND_COM_Set_4();
				FND_COM_CS();
				break;
		 }
	}
	 if (FND_Run_Cnt == 10){
		 switch(fnd_num_5){
		 	case 0 : 
				FND_Data_Reset();
				FND_Data_CS();
				FND_Data_Set_0();
				FND_Data_CS();
				FND_COM_Set_5();
				FND_COM_CS();
				break;
		 	case 1 : 
				FND_Data_Reset();
				FND_Data_CS();
				FND_Data_Set_1();
				FND_Data_CS();
				FND_COM_Set_5();
				FND_COM_CS();
				break;
			case 2 : 
				FND_Data_Reset();
				FND_Data_CS();
				FND_Data_Set_2();
				FND_Data_CS();
				FND_COM_Set_5();
				FND_COM_CS();
				break;
			case 3 : 
				FND_Data_Reset();
				FND_Data_CS();
				FND_Data_Set_3();
				FND_Data_CS();
				FND_COM_Set_5();
				FND_COM_CS();
				break;
			case 4 : 
				FND_Data_Reset();
				FND_Data_CS();
				FND_Data_Set_4();
				FND_Data_CS();
				FND_COM_Set_5();
				FND_COM_CS();
				break;
			case 5 : 
				FND_Data_Reset();
				FND_Data_CS();
				FND_Data_Set_5();
				FND_Data_CS();
				FND_COM_Set_5();
				FND_COM_CS();
				break;
			case 6 : 
				FND_Data_Reset();
				FND_Data_CS();
				FND_Data_Set_6();
				FND_Data_CS();
				FND_COM_Set_5();
				FND_COM_CS();
				break;
			case 7 : 
				FND_Data_Reset();
				FND_Data_CS();
				FND_Data_Set_7();
				FND_Data_CS();
				FND_COM_Set_5();
				FND_COM_CS();
				break;
			case 8 : 
				FND_Data_Reset();
				FND_Data_CS();
				FND_Data_Set_8();
				FND_Data_CS();
				FND_COM_Set_5();
				FND_COM_CS();
				break;
			case 9 : 
				FND_Data_Reset();
				FND_Data_CS();
				FND_Data_Set_9();
				FND_Data_CS();
				FND_COM_Set_5();
				FND_COM_CS();
				break;
		 }
	}
	if (FND_Run_Cnt == 12){
		switch(fnd_num_6){
			case 0 : 
				FND_Data_Reset();
				FND_Data_CS();
				FND_Data_Set_0();
				FND_Data_CS();
				FND_COM_Set_6();
				FND_COM_CS();
				break;
		 	case 1 : 
				FND_Data_Reset();
				FND_Data_CS();
				FND_Data_Set_1();
				FND_Data_CS();
				FND_COM_Set_6();
				FND_COM_CS();
				break;
			case 2 : 
				FND_Data_Reset();
				FND_Data_CS();
				FND_Data_Set_2();
				FND_Data_CS();
				FND_COM_Set_6();
				FND_COM_CS();
				break;
			case 3 : 
				FND_Data_Reset();
				FND_Data_CS();
				FND_Data_Set_3();
				FND_Data_CS();
				FND_COM_Set_6();
				FND_COM_CS();
				break;
			case 4 : 
				FND_Data_Reset();
				FND_Data_CS();
				FND_Data_Set_4();
				FND_Data_CS();
				FND_COM_Set_6();
				FND_COM_CS();
				break;
			case 5 : 
				FND_Data_Reset();
				FND_Data_CS();
				FND_Data_Set_5();
				FND_Data_CS();
				FND_COM_Set_6();
				FND_COM_CS();
				break;
			case 6 : 
				FND_Data_Reset();
				FND_Data_CS();
				FND_Data_Set_6();
				FND_Data_CS();
				FND_COM_Set_6();
				FND_COM_CS();
				break;
			case 7 : 
				FND_Data_Reset();
				FND_Data_CS();
				FND_Data_Set_7();
				FND_Data_CS();
				FND_COM_Set_6();
				FND_COM_CS();
				break;
			case 8 : 
				FND_Data_Reset();
				FND_Data_CS();
				FND_Data_Set_8();
				FND_Data_CS();
				FND_COM_Set_6();
				FND_COM_CS();
				break;
			case 9 : 
				FND_Data_Reset();
				FND_Data_CS();
				FND_Data_Set_9();
				FND_Data_CS();
				FND_COM_Set_6();
				FND_COM_CS();
				break;
		 }
	}
	if (FND_Run_Cnt == 14){
		 switch(fnd_num_7){
		 	case 0 : 
				FND_Data_Reset();
				FND_Data_CS();
				FND_Data_Set_0();
				FND_Data_CS();
				FND_COM_Set_7();
				FND_COM_CS();
				break;
		 	case 1 : 
				FND_Data_Reset();
				FND_Data_CS();
				FND_Data_Set_1();
				FND_Data_CS();
				FND_COM_Set_7();
				FND_COM_CS();
				break;
			case 2 : 
				FND_Data_Reset();
				FND_Data_CS();
				FND_Data_Set_2();
				FND_Data_CS();
				FND_COM_Set_7();
				FND_COM_CS();
				break;
			case 3 : 
				FND_Data_Reset();
				FND_Data_CS();
				FND_Data_Set_3();
				FND_Data_CS();
				FND_COM_Set_7();
				FND_COM_CS();
				break;
			case 4 : 
				FND_Data_Reset();
				FND_Data_CS();
				FND_Data_Set_4();
				FND_Data_CS();
				FND_COM_Set_7();
				FND_COM_CS();
				break;
			case 5 : 
				FND_Data_Reset();
				FND_Data_CS();
				FND_Data_Set_5();
				FND_Data_CS();
				FND_COM_Set_7();
				FND_COM_CS();
				break;
			case 6 : 
				FND_Data_Reset();
				FND_Data_CS();
				FND_Data_Set_6();
				FND_Data_CS();
				FND_COM_Set_7();
				FND_COM_CS();
				break;
			case 7 : 
				FND_Data_Reset();
				FND_Data_CS();
				FND_Data_Set_7();
				FND_Data_CS();
				FND_COM_Set_7();
				FND_COM_CS();
				break;
			case 8 : 
				FND_Data_Reset();
				FND_Data_CS();
				FND_Data_Set_8();
				FND_Data_CS();
				FND_COM_Set_7();
				FND_COM_CS();
				break;
			case 9 : 
				FND_Data_Reset();
				FND_Data_CS();
				FND_Data_Set_9();
				FND_Data_CS();
				FND_COM_Set_7();
				FND_COM_CS();
				break;
		 }
	}
	if (FND_Run_Cnt == 16){
		 switch(fnd_num_8){
		 	case 0 : 
				FND_Data_Reset();
				FND_Data_CS();
				FND_Data_Set_0();
				FND_Data_CS();
				FND_COM_Set_8();
				FND_COM_CS();
				break;
		 	case 1 : 
				FND_Data_Reset();
				FND_Data_CS();
				FND_Data_Set_1();
				FND_Data_CS();
				FND_COM_Set_8();
				FND_COM_CS();
				break;
			case 2 : 
				FND_Data_Reset();
				FND_Data_CS();
				FND_Data_Set_2();
				FND_Data_CS();
				FND_COM_Set_8();
				FND_COM_CS();
				break;
			case 3 : 
				FND_Data_Reset();
				FND_Data_CS();
				FND_Data_Set_3();
				FND_Data_CS();
				FND_COM_Set_8();
				FND_COM_CS();
				break;
			case 4 : 
				FND_Data_Reset();
				FND_Data_CS();
				FND_Data_Set_4();
				FND_Data_CS();
				FND_COM_Set_8();
				FND_COM_CS();
				break;
			case 5 : 
				FND_Data_Reset();
				FND_Data_CS();
				FND_Data_Set_5();
				FND_Data_CS();
				FND_COM_Set_8();
				FND_COM_CS();
				break;
			case 6 : 
				FND_Data_Reset();
				FND_Data_CS();
				FND_Data_Set_6();
				FND_Data_CS();
				FND_COM_Set_8();
				FND_COM_CS();
				break;
			case 7 : 
				FND_Data_Reset();
				FND_Data_CS();
				FND_Data_Set_7();
				FND_Data_CS();
				FND_COM_Set_8();
				FND_COM_CS();
				break;
			case 8 : 
				FND_Data_Reset();
				FND_Data_CS();
				FND_Data_Set_8();
				FND_Data_CS();
				FND_COM_Set_8();
				FND_COM_CS();
				break;
			case 9 : 
				FND_Data_Reset();
				FND_Data_CS();
				FND_Data_Set_9();
				FND_Data_CS();
				FND_COM_Set_8();
				FND_COM_CS();
				break;
		 }
		 FND_Run_Cnt = 0;
	}
}
void FND_Test(){

  	FND_init();

	if (FND_Cnt < 1000) FND_Run('A', 0, 0, 0, 0, 0, 0, 0, 0);
	else if (FND_Cnt < 2000) FND_Run('A', 1, 1, 1, 1, 1, 1, 1, 1);
	else if (FND_Cnt < 3000) FND_Run('A', 2, 2, 2, 2, 2, 2, 2, 2);
	else if (FND_Cnt < 4000) FND_Run('A', 3, 3, 3, 3, 3, 3, 3, 3);
	else if (FND_Cnt < 5000) FND_Run('A', 4, 4, 4, 4, 4, 4, 4, 4);
	else if (FND_Cnt < 6000) FND_Run('A', 5, 5, 5, 5, 5, 5, 5, 5);
	else if (FND_Cnt < 7000) FND_Run('A', 6, 6, 6, 6, 6, 6, 6, 6);
	else if (FND_Cnt < 8000) FND_Run('A', 7, 7, 7, 7, 7, 7, 7, 7);
	else if (FND_Cnt < 9000) FND_Run('A', 8, 8, 8, 8, 8, 8, 8, 8);
	else if (FND_Cnt < 10000) FND_Run('A', 9, 9, 9, 9, 9, 9, 9, 9); 
	else FND_Cnt=0;
}

#endif  // __Delay_H__
