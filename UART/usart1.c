#include  <lpc214x.h>		 //Includes LPC2148 register definitions
#include "uasrt1.h"

unsigned char received_data;

int  main(void)
{  
 char ch; 
   PINSEL0 = 0x00000005;
   IO0DIR=0XFFFFFFFF;		    // Enable UART0 Rx and Tx pins
   //PINSEL1 = 0x00000000;
   //PINSEL2 = 0x00000000;

   INIT_UART1();
	
   while(1)
   {	    ch=UART1_REC_CHAR();
   if(ch=='a')
   {
   IO0CLR=0XFFFFFFFF;
	   UART1_TX_STR("ARM7 UART");
	   _delay_ms(1000);
	   UART1_TX_STR("\n\r");
	
	}
	   /*received_data=UART0_REC_CHAR();
	
	   UART1_TX_CHAR(received_data);   */
   }
   return(0);
}
