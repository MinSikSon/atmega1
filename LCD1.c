//
//********************************************************************************************************
// 	Date: 	Jan 01, 2013	                                              	
//********************************************************************************************************
//	FILE:	EX4_3_2.c 
// 	VERSION:	1.00
//	TITLE:	example code for e-metering 
//
//	Note: 	1. 수치데이터 표출
//			2. 
//			3. Link option: -Wl,-u,vfprintf -lprintf_flt -lm
//
//********************************************************************************************************
//
//
#include "includes.h"
#define LCD_PORT PORTC // ><

static int LCD_putchar(char c, FILE *stream);
static FILE device = FDEV_SETUP_STREAM(LCD_putchar, NULL, _FDEV_SETUP_WRITE);

void _LCD_data(unsigned char data)		/* display a character on text LCD */
{ // 입력하고픈 character를 결정.
     PORTC &= ~_BV(0); 			// E = 0, Rs = 1  // _BV()는 bit value의 약자
     PORTC |=  _BV(1); 
     PORTA = data;				// output data
	PORTC |= _BV(0); 			// E = 1
     asm volatile(" PUSH  R0 ");	// delay for about 250 ns
     asm volatile(" POP   R0 ");
     PORTC &= ~_BV(0); 			// E = 0
     Delay_us(50);
}

static int LCD_putchar(char c, FILE *stream)
{
	if((c >= 0x20) && (c <= 0x7e)) // 이게 아마 저장 되어 있는 문자만 표현하도록 해놓은 것인거 같다.
	// 0x20은 00100000, 0x7e는 01111110
		_LCD_data(c);
	return 0;
}
/*
	11111 	 			11000
	11111	 			11000
	00011 	 			11000
	00011	 			11000
	00011	 			11000
	00011	 			11000
	00011	 			11111
	00011	 			11111

	50/50/50/FF/FF		FF/FF/03/03/03
*/

static void write_command(char command) // ><
{
	char temp; // 임시 변수

	// 상위니블 출력
	temp = (command & 0xF0) | 0x04;
	LCD_PORT = temp;			// RS=0, RW=0, E=1;
	LCD_PORT = temp & ~0x04;	// RS=0, RW=0, E=0;

	// 하위니블 출력
	temp = (command << 4) | 0x04;
	LCD_PORT = temp;
	LCD_PORT = temp & ~0x04;
}



void LCD_xy(char x, char y)
{
	if(x == 0) LCD_command(0x80+y); // LCD_command(0x80+y);
	else if(x==1) LCD_command(0xC0+y); // LCD_command(0xC0+y);
}


int	main(void)
{
	int i = 0;
	i = i;
     
	MCU_init(); 
	
	stdout = &device;
     
	Delay_ms(300);
     
	LCD_initialize();  

       		 		   //0123456789012345
	LCD_xy(0,0); printf(" [HiTechLogic]  ");
	LCD_xy(1,0); printf("Smart E-Meter v1");
     
  	return 0;
  	
}     



