//rs, rw, en with P).16-18
//D4-7 with P0.19-22



#define RS 16
#define RW 17
#define EN 18
void lcd_cmd  (unsigned char);

void lcd_data (unsigned char);

void lcd_initialize (void);

void lcd_display (void);

void LCD4_Convert(unsigned char);

void delay(unsigned int n)

{

  	T0CTCR = 0;
	T0PR = 60000; //60000 clock cycles = 1 mS @ 60Mhz

	T0TCR = 0x02; //Reset Timer
	T0TC = 0;
	T0TCR = 0x01; //Enable timer
	
	while(T0TC < n); //wait until timer counter reaches the desired delay
	
	T0TCR = 0x00; //Disable timer

} 

unsigned char cmd[6] = {0x33,0x32,0x28,0x0c,0x06,0x01};           


void lcd_cmd(unsigned char data)

{

   IOCLR0   |= 1<<RS;         //0x1000;      //RS

   IOCLR0   |= 1<<RW;         //0x2000;      //RW

   LCD4_Convert(data);

}

 

void lcd_initialize(void)

{

   int i;
   IOCLR0 = 0xF << 19; 

   for(i=0;i<6;i++)

   {
	  lcd_cmd(cmd[i]);

      delay(15);

   }

}

 

void lcd_data (unsigned char data)

{

     IOSET0   |= 1<<RS;         //0x1000;      //RS

   IOCLR0   |= 1<<RW;         //0x2000;      //RW

   LCD4_Convert(data);

}

 


void LCD4_Convert(unsigned char c)

{
	 
   
   if(c & 0x80) IOSET0 = 1 << 22; else IOCLR0 = 1 << 22;

   if(c & 0x40) IOSET0 = 1 << 21; else IOCLR0 = 1 << 21;

   if(c & 0x20) IOSET0 = 1 << 20; else IOCLR0 = 1 << 20;

   if(c & 0x10) IOSET0 = 1 << 19; else IOCLR0 = 1 << 19;

   IOSET0   = 1<<EN;

   delay(8);

   IOCLR0   = 1<<EN;

 

  if(c & 0x08) IOSET0 = 1 << 22; else IOCLR0 = 1 << 22;

   if(c & 0x04) IOSET0 = 1 << 21; else IOCLR0 = 1 << 21;

   if(c & 0x02) IOSET0 = 1 << 20; else IOCLR0 = 1 << 20;

   if(c & 0x01) IOSET0 = 1 << 19; else IOCLR0 = 1 << 19;

 

   IOSET0   = 1<<EN;

   delay(8);

   IOCLR0   = 1<<EN;
}