#include<lpc213x.h>

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

int main()
{
	int i,j;
	IO0DIR=0x0000FFFF;
	while(1)
	{
		int a[]={0x0000C104,0x0000C920,0x0000B618};
		for(j=0;j<8;j++)
		{
			for(i=0;i<350;i++)
			{
				IO0SET=a[0];
				delay(1);
				IO0CLR=0x0000ffff;
				IO0SET=a[1];
				delay(1);
				IO0CLR=0x0000ffff;
				IO0SET=a[2];
				delay(1);
				IO0CLR=0x0000ffff;
			}
			a[0]=a[0]/2;
			a[1]=a[1]/2;
			a[2]=a[2]/2;
		}
		IO0CLR=0x0000ffff;
		/*for(i=0;i<350;i++)
		{
			IO0SET=0x00008024;
			delay(1);
			IO0CLR=0x0000ffff;
			IO0SET=0x0000F718;
			delay(1);
			IO0CLR=0x0000ffff;
		}
		IO0CLR=0x0000ffff;
		for(i=0;i<350;i++)
		{
			IO0SET=0x00008024;
			delay(1);
			IO0CLR=0x0000ffff;
			IO0SET=0x0000F618;
			delay(1);
			IO0CLR=0x0000ffff;
		}
		IO0CLR=0x0000ffff;
		for(i=0;i<350;i++)
		{
			IO0SET=0x0000E022;
			delay(1);
			IO0CLR=0x0000ffff;
			IO0SET=0x0000DF14;
			delay(1);
			IO0CLR=0x0000ffff;
			IO0SET=0x0000BF08;
			delay(1);
			IO0CLR=0x0000ffff;
		}
		IO0CLR=0x0000ffff;
		for(i=0;i<350;i++)
		{
			IO0SET=0x0000FD44;
			delay(1);
			IO0CLR=0x0000ffff;
			IO0SET=0x0000FB28;
			delay(1);
			IO0CLR=0x0000ffff;
			IO0SET=0x00008710;
			delay(1);
			IO0CLR=0x0000ffff;
		}
		IO0CLR=0x0000ffff;
		for(i=0;i<350;i++)
		{
			IO0SET=0x00008024;
			delay(1);
			IO0CLR=0x0000ffff;
			IO0SET=0x0000F618;
			delay(1);
			IO0CLR=0x0000ffff;
		}
		IO0CLR=0x0000ffff;*/
	}
}