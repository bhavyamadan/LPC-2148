#include  <lpc214x.h>		 //Includes LPC2148 register definitions

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
   while((U0LSR&0x40)==0);	    
}


void  UART0_TX_STR(unsigned char *str)	 //A function to send a string on UART0
{  int i=0;
   while(str[i] != '\0')
   {  
      
      UART0_TX_CHAR(str[i]);
	  _delay_ms(10);
i++;		 
   }
}

char UART0_REC_CHAR ()
{
 while ((U0LSR&0x01)==0);
 return U0RBR;
}

unsigned char received_data;

int  main(void)
{  
 char ch; 
   PINSEL0 = 0x00050005;
   IO0DIR=0XFFFFFFFF;		    // Enable UART0 Rx and Tx pins
   //PINSEL1 = 0x00000000;
   //PINSEL2 = 0x00000000;

   INIT_UART0();
	
   while(1)
   {	    ch=UART0_REC_CHAR();
   if(ch=='a')
   {
   IO0CLR=0XFFFFFFFF;
	   UART0_TX_CHAR('P');
	   _delay_ms(1000);
	   UART0_TX_STR("Hello");
	
	}
	   /*received_data=UART0_REC_CHAR();
	
	   UART1_TX_CHAR(received_data);   */
   }
   return(0);
}
