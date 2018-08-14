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
	IO0PIN=a<<0;
	IO1CLR=1<<RS;
	IO1CLR=1<<RW;
	IO1SET=1<<EN;
	delay(1);
	IO1CLR=1<<EN;
	delay(1);
}

void LCDdata(unsigned char a)
{
	IO0PIN=a<<0;
	IO1SET=1<<RS;
	IO1CLR=1<<RW;
	IO1SET=1<<EN;
	delay(1);
	IO1CLR=1<<EN;
	delay(1);
}

void number(unsigned char a)
{
	int b,c;
	LCDcmd(0x04);	
	b=a%10;
	LCDdata(b+48);
	a=a/10;
	c=a%10;
	LCDcmd(0x06);	
	LCDdata(c+48);
}

void String(char * str)
{
	int i=0;
    LCDcmd(0x38);
    LCDcmd(0x0E);
	while(str[i]!='\0')
	{
		LCDdata(str[i]);
		i++;
	}
}

int main()
{
	int i;
	IO0DIR=0x000000FF;
	IO1DIR=0x00070000;
	LCDcmd(0x38);
	LCDcmd(0x0E);
	while(1)
	{
		LCDcmd(0x86);
		String("UV Softs");
		for(i=0xD0;i>0xB6;i--)
		{
			LCDcmd(i);
			String("1. MATLAB ");
		}
		for(i=0xD0;i>0xB2;i--)
		{
			LCDcmd(i);
			String("2. ROBOTICS ");
		}
	}
}