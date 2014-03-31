//
//********************************************************************************************************
// 	Date: 	Jan 01, 2013	                                              	
//********************************************************************************************************
//	FILE:	sub_emeter.h 
// 
//	TITLE:	I/O Direction Definition & Delay Function for E-metering
//********************************************************************************************************
//

#ifndef SUB_EMETER_H
#define SUB_EMETER_H

// physical connection:
#define	SET_CE1	PORTG|=0x01
#define	SET_CE0	PORTG&=~0x01
#define	SET_SCLK1	PORTG|=0x02
#define	SET_SCLK0	PORTG&=~0x02
#define	SET_IO1	PORTG|=0x04
#define	SET_IO0	PORTG&=~0x04
#define 	GET_IO	(PING&0x04)
#define 	IO_IN	DDRG&=~0x04
#define 	IO_OUT	DDRG|=0x04

void MCU_init(void);			
void Delay_us(unsigned char time_us);		/* time delay for us */
void Delay_ms(unsigned int time_ms);       	/* time delay for ms */

void RTC_write(unsigned char command, unsigned char data);
unsigned char RTC_read(unsigned char command);
void connect_bt(void);
void comm1_string(char *buf);

#endif

