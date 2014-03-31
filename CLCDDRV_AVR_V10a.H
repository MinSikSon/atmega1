//
//********************************************************************************************************
// 	Date: 	March 05, 2013	                                              	
//********************************************************************************************************
//	FILE:	CLCDDRV_AVR_V10a.H 
// 
//	TITLE:	Character LCD Subroutine
//********************************************************************************************************
//

#ifndef CLCDDRV_AVR_H
#define CLCDDRV_AVR_H

void LCD_command(unsigned char command);		/* write a command(instruction) to text LCD */
void LCD_data(unsigned char data);				/* display a character on text LCD */
void LCD_string(char command, char *string); 	/* display a string on LCD */
void LCD_initialize(void);					/* initialize text LCD module */
void LCD_2d(unsigned int number);
void LCD_2hex(unsigned int number);
void LCD_1d2(float fnumber);					/* display X.XX number on LCD */
void LCD_2d1(float number);					/* display XX.X number on LCD */
void LCD_3d(unsigned int number);
void LCD_4d(unsigned int number);
void LCD_s4d(int number);
void LCD_4hex(unsigned int number);
void LCD_4d1(float number); 					/* xxxx.x */
void LCD_6d(unsigned long number);

#endif

