#include<lpc214x.h>
#define PLOCK 0x00000400		//10th bit in PLLSTAT register
#define PRESCALE 60000

void initTimer0(void)
{   
    T0CTCR = 0x0;					// Disabled counter in TCR(timer Control Register)
    T0PR = PRESCALE-1; 		//Set PR=59999
    T0TCR = 0x02; 				//Counter reset: TC and PC are reset at next +ve edge of PCLK
}


void setupPLL0(void)
{
    PLL0CON = 0x01;				//Enabled the PLL0 but didn't connect it
    PLL0CFG = 0x24;				//Set divider value(P)=2 and M=5
}

void feedSeq(void)				//Feed Sequence is send
{
    PLL0FEED = 0xAA;
    PLL0FEED = 0x55;
}

void connectPLL0(void)
{
   while( !( PLL0STAT & PLOCK ));	//Loop stays till PLOCK reaches the desired freq and is locked
   PLL0CON = 0x03;								//Counter enabled and connected
   }
void initClocks(void)
{
    setupPLL0();
    feedSeq(); 
    connectPLL0();
    feedSeq();   
    VPBDIV = 0x01; 
 }	

void delay_ms(unsigned int milliseconds) 
{
    T0TCR = 0x02;				//Counter Reset
    T0TCR = 0x01; 			//Counter Enable
   
    while(T0TC < milliseconds); 
   
    T0TCR = 0x00; 			//Counter disabled and reset
}

