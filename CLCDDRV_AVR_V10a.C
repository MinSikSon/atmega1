//
//********************************************************************************************************
// 	Date: 	March 25, 2013	                                              	
//********************************************************************************************************
//	FILE:	CLCDDRV_AVR_V10a.C 
// 
//	TITLE:	Character LCD Subroutine
//********************************************************************************************************
//

//#include "includes.h"
//#include "CLCDDRV_AVR_V10a.h"

void LCD_command(unsigned char command)		/* write a command(instruction) to text LCD */
{ // 입력하고픈 character의 위치를 결정
     PORTC &= ~_BV(0); 			// E = 0, Rs = 0  
     PORTC &= ~_BV(1); 
     PORTA  = command;			// output command
	PORTC |= _BV(0);  			// E = 1
     asm volatile(" PUSH  R0 ");	// delay for about 250 ns
     asm volatile(" POP   R0 ");
     PORTC &= ~_BV(0); 			// E = 0
     Delay_us(50);
}

void LCD_data(unsigned char data)		/* display a character on text LCD */
{ // 입력하고픈 character를 결정.
     PORTC &= ~_BV(0); 			// E = 0, Rs = 1 
     PORTC |=  _BV(1); 
     PORTA = data;				// output data
	PORTC |= _BV(0); 			// E = 1
     asm volatile(" PUSH  R0 ");	// delay for about 250 ns
     asm volatile(" POP   R0 ");
     PORTC &= ~_BV(0); 			// E = 0
     Delay_us(50);
}


void LCD_string(char command, char *string) /* display a string on LCD */
{ // String을 display.
     LCD_command(command);			// start position of string
     while(*string != '\0') {			// display string
        LCD_data(*string);
        string++;
     }
}

void LCD_initialize(void)			/* initialize text LCD module */
{ // LCD에 표현되는 문자의 크기 등을 설정.
     LCD_command(0x38);				// function set(8 bit, 2 line, 5x7 dot)
     LCD_command(0x0C);				// display control(display ON, cursor OFF)
     LCD_command(0x06);				// entry mode set(increment, not shift) // shift는 글자가 옆으로 움직이는 것처럼 보이게 하는 것임.
     LCD_command(0x01);				// clear display
     Delay_ms(2);
}

void LCD_2d(unsigned int number)
{ // 십진수를 2자리로 표시
     unsigned int i;
     i = number / 10;
     if(i == 0) LCD_data(' ');
     else LCD_data(i + '0');
      
     i = number % 10;
     LCD_data(i + '0');
} 

void LCD_2hex(unsigned int number)
{ // 십육진수를 2자리로 표시
     unsigned int i;
     
	i = (number >> 4) & 0x0F;
     if(i <= 9) LCD_data(i + '0');
     else       LCD_data(i - 10 + 'A');
     
     i = number & 0x0F;
     if(i <= 9) LCD_data(i + '0');
     else       LCD_data(i - 10 + 'A');
} 

void LCD_1d2(float fnumber)			/* display X.XX number on LCD */
{ 
     int i, number;

     number = (fabs(fnumber) + 0.005) * 100;
 	
 	i = number / 100;
     LCD_data(i + '0');
     
     LCD_data('.');
     
     number = number % 100;
     i = number / 10; 
     LCD_data(i + '0');
     
     i = number % 10;
     LCD_data(i + '0');

}   


void LCD_2d1(float number)			/* display XX.X number on LCD */
{ 
     int i;

 //    number = fabs(number) + 0.05;
     i = (int)(number/10.);
     LCD_data(i + '0');

     i = (int)(number - i * 10);
     LCD_data(i + '0');

     LCD_data('.');

     i = (int)((number - (int)number) * 10.);
     LCD_data(i + '0');
}   

void LCD_3d(unsigned int number)
{
     unsigned int i,flag;
     flag = 0;
     i = number / 100;
     if(i == 0) LCD_data(' ');
     else {   LCD_data(i + '0');
              flag = 1;
          }
      
     number = number % 100;
     i = number / 10; 
     if((i == 0) && (flag == 0)) LCD_data(' ');
     else {   LCD_data(i + '0');
              flag = 1;
          }
     
     i = number % 10;
     LCD_data(i + '0');
}  

void LCD_4d(unsigned int number)
{
     unsigned int i,flag;
     flag = 0;
     i = number / 1000;
     if(i == 0) LCD_data(' ');
     else {   LCD_data(i + '0');
              flag = 1;
          }
      
     number = number % 1000;
     i = number / 100; 
     if((i == 0) && (flag == 0)) LCD_data(' ');
     else {   LCD_data(i + '0');
              flag = 1;
          }
     
     number = number % 100;
     i = number / 10;
     if((i == 0) && (flag == 0)) LCD_data(' ');
     else LCD_data(i + '0');
     
     i = number % 10;
     LCD_data(i + '0');
}    

void LCD_s4d(int number)
{
     unsigned int i, flag;
     flag = 0;      
     
     if(number < 0) {
     	number = number * (-1);
     	LCD_data('-');
     } else {
     	if(number == 0) LCD_data(' ');
     	else            LCD_data('+');
     }
     
     i = number / 1000;
     if(i == 0) LCD_data(' ');
     else {   LCD_data(i + '0');
              flag = 1;
          }
      
     number = number % 1000;
     i = number / 100; 
     if((i == 0) && (flag == 0)) LCD_data(' ');
     else {   LCD_data(i + '0');
              flag = 1;
          }
     
     number = number % 100;
     i = number / 10;
     if((i == 0) && (flag == 0)) LCD_data(' ');
     else LCD_data(i + '0');
     
     i = number % 10;
     LCD_data(i + '0');  
}  
   

void LCD_4hex(unsigned int number)
{
     unsigned int i;
     
     i = number >>12;
     if(i <= 9) LCD_data(i + '0');
     else       LCD_data(i - 10 + 'A');
     
     i = (number >> 8) & 0x000F;
     if(i <= 9) LCD_data(i + '0');
     else       LCD_data(i - 10 + 'A');
     
     i = (number >> 4) & 0x000F;
     if(i <= 9) LCD_data(i + '0');
     else       LCD_data(i - 10 + 'A');
     
     i = number & 0x000F;
     if(i <= 9) LCD_data(i + '0');
     else       LCD_data(i - 10 + 'A');
}  

void LCD_4d1(float number) 	/* xxxx.x */
{
     unsigned int i,j,flag;  
     flag = 0;
     
     j = (int)(number*10. + 0.5);
     i = j/10000; 
     if(i == 0) LCD_data(' ');					/* 10^3 */
     else {   LCD_data(i + '0');     
              flag = 1;
          }
     
     j = j % 10000;				
     i = j / 1000;                       			/* 10^2 */
     if((i == 0) && (flag == 0)) LCD_data(' ');
     else {   LCD_data(i + '0');
              flag = 1;
          }       
     
     j = j % 1000;				
     i = j / 100;                       			/* 10^1 */
     if((i == 0) && (flag == 0)) LCD_data(' ');
     else {   LCD_data(i + '0');
              flag = 1;
          }
     
     j = j % 100;				
     i = j / 10;                       				/* 10^0 */
     LCD_data(i + '0');

     LCD_data('.');     
     
     i = j % 10;								/* 10^-1 */
     LCD_data(i + '0');
}   

void LCD_6d(unsigned long number)
{
     unsigned int i,flag;  
     
     flag = 0; 
     i = number / 100000;                              /* 10^5 */
     if(i == 0) LCD_data(' ');
     else {   LCD_data(i + '0');
              flag = 1;
          } 
                     
     number = number % 100000;                		/* 10^4 */
     i = number / 10000;
     if((i == 0) && (flag == 0)) LCD_data(' ');
     else {   LCD_data(i + '0');
              flag = 1;
          }      
     
     number = number % 10000;                		/* 10^3 */
     i = number / 1000;
     if((i == 0) && (flag == 0)) LCD_data(' ');
     else {   LCD_data(i + '0');
              flag = 1;
          }   
          
     number = number % 1000;                			/* 10^2 */
     i = number / 100;
     if((i == 0) && (flag == 0)) LCD_data(' ');
     else {   LCD_data(i + '0');
              flag = 1;
          }   
          
     number = number % 100;                			/* 10^1 */
     i = number / 10;
     if((i == 0) && (flag == 0)) LCD_data(' ');
     else {   LCD_data(i + '0');
              flag = 1;
          }        
          
     i = number % 10;     						/* 10^0 */
     LCD_data(i + '0');   
}   

