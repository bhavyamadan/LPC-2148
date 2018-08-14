#include<lpc214x.h>

#include "timer.h"

#define Fosc            12000000                    
#define Fcclk           (Fosc * 5)                  
#define Fcco            (Fcclk * 2)                 
#define Fpclk           (Fcclk / 4) * 1             
#define  UART_BPS	9600	 //Set Baud Rate here

void  INIT_UART0(void)		 //This function setups UART0
{  
   unsigned int Baud16;
   U0LCR = 0x83;		            			// DLAB = 1
   Baud16 = (Fpclk / 16) / UART_BPS;  
   U0DLM = Baud16 / 256;							
   U0DLL = Baud16 % 256;
   //U0DLM=0;
   //U0DLL=162;		 //any value between 160-170 can be used
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
	    delay_ms(10);
      i++;		 
   }
}

char UART0_RX_CHAR ()
{
 while ((U0LSR&0x01)==0);
 return U0RBR;
}

char* UART0_RX_STR()	 //A function to send a string on UART0
{  
	 char *str;
   int i=0;
   while(str[i] != '\0')
   {  
      
      str[i]=UART0_RX_CHAR();
      delay_ms(10);
      i++;		 
   }
   return str;

}
