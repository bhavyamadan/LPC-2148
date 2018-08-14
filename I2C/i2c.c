#include <LPC214X.H>
//#include "UART0.h"

/*void I2C0_Init(void);
void I2C0_Start(void);
void I2C0_Stop(void);
void I2C0_Write(unsigned char data, unsigned char status);
unsigned char I2C0_Read(void); */

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
   PINSEL0 |= 0x00000005;
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
   //U0THR = data;				    
   //while( (U0LSR&0x40)==0 );
   while (!(U0LSR&0x20));
   U0THR = data;	    
}


void  UART0_TX_STR(const unsigned char *str)	 //A function to send a string on UART0
{  
   while(1)
   {  
      if( *str == '\0' ) break;
      UART0_TX_CHAR(*str++);
	  _delay_ms(70);	    
   }
}

char UART0_REC_CHAR ()
{
 while ((U0LSR&0x01)==0);
 return U0RBR;
}  

void I2C0_Init(void)
{       
        PINSEL0 |= 0x50;                /*Initialize Pin Connect Block P0.2 as SCL0 P0.3 as SDA0*/
        I2C0CONCLR = 0x2C;      	/*Clear AA, I2C Interrupt Flag, Start Bit*/
        I2C0CONSET = 0x44;      	/*Enable I2C0*/

        /*
        PCLK = 12MHz
        I2C Frequency = 100KHz
        Formula:
        I2C Frequency = PCLK/((I2CSCLH + I2CSCLL)
        (I2CSCLH + I2CSCLL) = 12000/100 = 120   		 //Bit Rate 100Khz
        */

        I2C0SCLH = 100;
        I2C0SCLL = 100;	

		/*I2C0SCLH = 60;
        I2C0SCLL = 60;*/ 

            
}
void I2C0_Start(void)
{
  I2C0CONSET |= 0x20;                  	/*Set the Start Bit*/
  while(I2C0STAT!=0x08);  		/*Wait for the Status Set*/
}
void I2C0_Stop(void)
{
  I2C0CONSET |= 0x14;                  	/*Stop I2C*/
  I2C0CONCLR  = 0x08;
}
void I2C0_Write(unsigned char data,unsigned char status)
{
  I2C0DAT = data;
  I2C0CONSET = 0X04;					//for ack receive 
  I2C0CONCLR = 0X28;					//start condition hasbeen clr and SI flag also clr
  while(I2C0STAT!=status);            	//Wait for Status Set 
}
unsigned char I2C0_Read(void)
{
  I2C0CONSET = 0X04;
  I2C0CONCLR = 0X28;
  while (I2C0STAT!=0x00000050); 	/* Wait for Status Set - 0x50 */
  return(I2C0DAT);
}

void EEPROM24C_Write(unsigned char data,unsigned char address)
{
        I2C0_Init();
        I2C0_Start();   
        I2C0_Write(0xA0,0x18);  		//status 0x18 for slave address and read write send sucessfully
        I2C0_Write(address,0x28);       //location to which data has to be write and ack for same
        I2C0_Write(data,0x28);			//ack for data sent successfully
        I2C0_Stop();
}

unsigned char EEPROM24C_Read(unsigned char address)
{
        unsigned char read;
        I2C0_Init();
        I2C0_Start();   
        I2C0_Write(0xA0,0x18);  	 	//status 0x18 for slave address and read write send sucessfully
        I2C0_Write(address,0x28);		//location to which data has to be write and ack for same
        I2C0_Stop();            
        I2C0_Start();   
        I2C0_Write(0xA1,0x40);  		//slave address with bit(0)=1 as read mode and waiting for ack of same 
        read = I2C0_Read();
        I2C0_Stop();
        return (read);
}


int main (void)
{
unsigned char read_eeprom;
//unsigned char i;

I2C0_Init();
INIT_UART0();

UART0_TX_STR("START OF I2C\n\r");

UART0_TX_STR("Writing... \n\r");
EEPROM24C_Write('A',0x00);
UART0_TX_STR("WAIT...\n\r");
read_eeprom = EEPROM24C_Read(0x00);
UART0_TX_STR("Reading...\n\r");
UART0_TX_CHAR(read_eeprom); 
while(1);
}