#include<lpc213x.h>

#define RS 16
#define RW 17
#define EN 18
#define lcd 8-15
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
	IO0PIN=a;
	IO1CLR=1<<RS;
	IO1CLR=1<<RW;
	IO1SET=1<<EN;
	delay(1);
	IO1CLR=1<<EN;
	delay(1);
}

void LCDdata(unsigned char a)
{
	IO0PIN=a;
	IO1SET=1<<RS;
	IO1CLR=1<<RW;
  IO1SET=1<<EN;
	delay(1);
	IO1CLR=1<<EN;
	delay(1);
}

int main()
{
	IO0DIR=0x0000FF00;
	IO1DIR=0xFFFFFFFF;
	while(1)
	{
		LCDcmd(0x38);
		LCDcmd(0x0E);
		LCDcmd(0x81);
		LCDdata('p');
	}
	return 0;
}