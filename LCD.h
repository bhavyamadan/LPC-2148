#include<lpc213x.h>

#define RS 16
#define RW 17
#define EN 18

void delay(unsigned int a)
{
	int b,c;
	for(b=0;b<a;b++)
	{
		for(c=0;c<1000;c++)
		{
		}
	}
}


void LCDcmd(unsigned char a)
{
	IO0PIN=a<<15;
	IO0CLR=1<<RS;
	IO0CLR=1<<RW;
	IO0SET=1<<EN;
	delay(1);
	IO0CLR=1<<EN;
	delay(1);
}

void LCDcmd4(unsigned char a)
{
	int y;
	y=a&0xf0;
	LCDcmd(y);
	y=(a<<4)&0xf0;
	LCDcmd(y);
}

void LCDdata(unsigned char a)
{
	IO0PIN=a<<15;
	IO0SET=1<<RS;
	IO0CLR=1<<RW;
	IO0SET=1<<EN;
	delay(1);
	IO0CLR=1<<EN;
	delay(1);
}

void LCDdata4(unsigned char a)
{
	int y;
	y=a&0xf0;
	LCDdata(y);
	y=(a<<4)&0xf0;
	LCDdata(y);
}

void number(unsigned char a)
{
	int b,c;
	LCDcmd4(0x04);	
	b=a%10;
	LCDdata4(b+48);
	a=a/10;
	c=a%10;
	LCDcmd4(0x06);	
	LCDdata4(c+48);
}

void String(char* str)
{
	int i=0;
   ////LCDcmd4(0x38);
   //LCDcmd4(0x0E);
	while(str[i]!='\0')
	{
		LCDdata4(str[i]);
		i++;
	}
}

