#include <LPC214X.h>


//#define Fosc            20000000
#define Fosc            12000000                    
#define Fcclk           (Fosc * 5)                  
#define Fcco            (Fcclk * 2)                 
#define Fpclk           (Fcclk / 4) * 1             

#define  UART_BPS	9600	 //Set Baud Rate here

void _delay_ms(unsigned int tt)
{
    unsigned int t;
	for(;tt>0;tt--)
	 {
		for(t=0;t<12500;t++);
	 }
}

void  INIT_UART1(void)							//This function setups UART0
{  
   unsigned int Baud16;
   U1LCR = 0x83;		            			// DLAB = 1
   Baud16 = (Fpclk / 16) / UART_BPS;  
   U1DLM = Baud16 / 256;							
   U1DLL = Baud16 % 256;
   //U0DLM=0;
   //U0DLL=162;								   //any value between 160-170 can be used
   U1LCR = 0x03;
}


void  UART1_TX_CHAR(unsigned char data)	   //A function to send a byte on UART0
{  
   U1THR = data;				    
   while( (U1LSR&0x40)==0 );	    
}


void  UART1_TX_STR(const unsigned char *str)	 //A function to send a string on UART0
{  
   while(1)
   {  
      if( *str == '\0' ) break;
      UART1_TX_CHAR(*str++);
	  _delay_ms(10);	    
   }
}

char UART1_REC_CHAR ()
{
 while ((U1LSR&0x01)==0);
 return U1RBR;
}