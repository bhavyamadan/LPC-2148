
#include <lpc214x.h>
#include"LCD.h"
#define Fosc            12000000                    
#define Fcclk           (Fosc * 5)                  
#define Fcco            (Fcclk * 2)                 
#define Fpclk           (Fcclk / 4) * 1             
#define  UART_BPS	9600	 //Set Baud Rate here
#define AD01 ((1<<24)|(0<<25))	//Select AD0.1 function for P0.28
#define AD06 ((1<<9)|(1<<8)) //Select AD0.6 function for P0.4
#define AD07 ((1<<11)|(1<<10)) //Select AD0.7 function for P0.5
#define SEL_AD01 (1<<1)
#define SEL_AD06 (1<<6)
#define SEL_AD07 (1<<7)

#define CLKDIV (15-1) // 4Mhz ADC clock (ADC_CLOCK=PCLK/CLKDIV) where "CLKDIV-1" is actually used , in our case PCLK=60mhz  
#define BURST_MODE_OFF (0<<16) // 1 for on and 0 for off
#define PowerUP (1<<21)
#define START_NOW ((0<<26)|(0<<25)|(1<<24)) //001 for starting the conversion immediately
#define ADC_DONE (1<<31)

#define VREF 3.3 //Reference Voltage at VREF pin


#define PLOCK 0x00000400
void setupPLL0(void)
{
	//Note : Assuming 12Mhz Xtal is connected to LPC2148.
	
	PLL0CON = 0x01; 
	PLL0CFG = 0x24; 
}

void feedSeq(void)
{
	PLL0FEED = 0xAA;
	PLL0FEED = 0x55;
}

void connectPLL0(void)
{
	while( !( PLL0STAT & PLOCK ));
	PLL0CON = 0x03;
}

void initClocks(void)
{
	setupPLL0();
	feedSeq(); //sequence for locking PLL to desired freq.
	connectPLL0();
	feedSeq(); //sequence for connecting the PLL as system clock
   
	//SysClock is now ticking @ 60Mhz!
       
	VPBDIV = 0x01; // PCLK is same as CCLK i.e 60Mhz

	//PLL0 Now configured!
}
void  INIT_UART0(void)							//This function setups UART0
{  
   unsigned int Baud16;
   U0LCR = 0x83;		            			// DLAB = 1
   Baud16 = (Fpclk / 16) / UART_BPS;  
   U0DLM = Baud16 / 256;							
   U0DLL = Baud16 % 256;
   //U0DLM=0;
   //U0DLL=162;								   //any value between 160-170 can be used
   U0LCR = 0x03;
}


void  UART0_TX_CHAR(unsigned char data)	   //A function to send a byte on UART0
{  
   U0THR = data;				    
   while( (U0LSR&0x40)==0 );	    
}


void  UART0_TX_STR(unsigned char *str)	 //A function to send a string on UART0
{  int i=0;
   while(str[i] != '\0')
   {  
      UART0_TX_CHAR(str[i]);
			delay(10);
			i++;		 
   }
}

char UART0_REC_CHAR ()
{
 while ((U0LSR&0x01)==0);
 return U0RBR;
}

   

int main(void)
{
char ch;
int result=0;
int i;

unsigned long AD0CR_setup = (CLKDIV<<8) | BURST_MODE_OFF | PowerUP;
initClocks(); //CCLK and PCLK @ 60Mhz
	
//IODIR0  =   0 << 4;	
	PINSEL0|= ((1<<2)|(0<<1)|(1<<0)) ;
PINSEL1 |= ((1<<24)|(0<<25)) ; //select AD0.1 for P0.28
PINSEL0 |= ((1<<9)|(1<<8)) ; //select AD0.6 for P0.4
PINSEL0 |= ((1<<11)|(1<<10)) ; //select AD0.7 for P0.5
PINSEL1 |= ((0<<18)|(1<<19)) ; //select AD0.4 for DAC
DACR	|= (1<<16);				//SETTLING DELAY FOR DAC
DACR	|= (240<<6);//DIGITAL VALUE TO BE COVERTED TO ANALOG VOLTAGE ACCORDING TO FORMULA

IODIR0  =   0xFF << 16;
    
   lcd_initialize();
lcd_data('s');

INIT_UART0();
	
	
	while(1)
	{
		
		
		//for( i=0;i<29;i++)
		{
		UART0_TX_CHAR('B');
			delay(10);
			
		}
	AD0CR =  AD0CR_setup | SEL_AD01; 
		AD0CR |= START_NOW; //Start new Conversion

		while( (AD0GDR & ADC_DONE) == 0 );
		
		result = (AD0GDR>>6) & 0x3ff;
		

lcd_cmd(0x01);
lcd_cmd(0x8e);
		lcd_data('a');

if(result==0)
lcd_data('0');
else
{
					 
while(result)
{

lcd_data((result%10)+0x30);
lcd_cmd(0x10);
lcd_cmd(0x10);
result=result/10;
delay(1000);
	delay(1000);
}
}
	
AD0CR =  AD0CR_setup | SEL_AD07; 
		AD0CR |= START_NOW; //Start new Conversion

		while( (AD0GDR & ADC_DONE) == 0 );
		
		result = (AD0GDR>>6) & 0x3ff;

lcd_cmd(0x01);
lcd_cmd(0xce);

if(result==0)
lcd_data('0');
else
{
					 
while(result)
{

lcd_data((result%10)+0x30);
lcd_cmd(0x10);
lcd_cmd(0x10);
result=result/10;
delay(1000);
	delay(1000);
}
}	
	
		delay(250); //Slowing down Updates to 4 Updates per second
	}
	
	return 0;
}
	
