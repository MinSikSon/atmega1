//
//********************************************************************************************************
// 	Date: 	Jan 01, 2013	                                              	
//********************************************************************************************************
//	FILE:	sub_emeter.c 
// 
//	TITLE:	I/O Direction Definition & Delay Function
//********************************************************************************************************
//

//#include "includes.h"
//#include "sub_emeter.h"

void MCU_init(void)			
{ 
     // -------------------------------------------------------------------------------------------
     // MCU initialize 
     // -------------------------------------------------------------------------------------------
     MCUCR = 0x00;	
   	XMCRA = 0x00; 
   	XMCRB = 0x00; 

   	DDRA	 = 0xFF;			// PORTA Data Direction ( 1:out, 0:in )
   	PORTA = 0x00;             
   						// PORTA.0 (O) : LCD DATA0
     					// PORTA.1 (O) : LCD DATA1
     					// PORTA.2 (O) : LCD DATA2
     					// PORTA.3 (O) : LCD DATA3
     					// PORTA.4 (O) : LCD DATA4
     					// PORTA.5 (O) : LCD DATA5
     					// PORTA.6 (O) : LCD DATA6
     					// PORTA.7 (O) : LCD DATA7 
   	
   	DDRB  = 0x00;  		// PORTB Data Direction ( 1:out, 0:in ) 
     PORTB = 0x00;            
     					// PORTB.0 (I) : M95512 /CS
     					// PORTB.1 (I) : M95512 SCK (SCK for ISP)
     					// PORTB.2 (I) : M95512 SI
     					// PORTB.3 (I) : M95512 SO
     					// PORTB.4 (I) : KEY0 SET
     					// PORTB.5 (I) : KEY1 DOWN
     					// PORTB.6 (I) : KEY2 UP
     					// PORTB.7 (I) : KEY3 MODE
     					
     DDRC  = 0xF3;  		// PORTC Data Direction ( 1:out, 0:in ) 
     PORTC = 0xF0;            
     					// PORTC.0 (O) : LCD_E
     					// PORTC.1 (O) : LCD_RS
     					// PORTC.2 (I) : Not Used
     					// PORTC.3 (I) : Not Used
     					// PORTC.4 (O) : LED U4
     					// PORTC.5 (O) : LED U5
     					// PORTC.6 (O) : LED U6
     					// PORTC.7 (O) : LED U7
     										     
     DDRD	 = 0x00;			// PORTD Data Direction ( 1:out, 0:in )
   	PORTD = 0x00;            //  										     
     					// PORTD.0 (I) : Not Used
     					// PORTD.1 (I) : Not Used
     					// PORTD.2 (I) : RXD1
     					// PORTD.3 (I) : TXD1
     					// PORTD.4 (O) : Not Used 
     					// PORTD.5 (O) : Not Used
     					// PORTD.6 (O) : Not Used
     					// PORTD.7 (O) : Not Used
     					
    	DDRE  = 0xF8;  		// PORTE Data Direction ( 1:out, 0:in )  
     PORTE = 0x00;            
     					// PORTE.0 (I) : RXD0
     					// PORTE.1 (I) : TXD0
     					// PORTE.2 (I) : Not Used
     					// PORTE.3 (O) : PWM1
     					// PORTE.4 (O) : PWM2
     					// PORTE.5 (O) : TP1(PWM3)
     					// PORTE.6 (O) : TP2
     					// PORTE.7 (O) : TP3

     DDRF  = 0x00;  		// PORTF Data Direction ( 1:out, 0:in )  
     PORTF = 0x00;             
     					// PORTF.0 (I) : ADC0
     					// PORTF.1 (I) : ADC1
     					// PORTF.2 (I) : ADC2
     					// PORTF.3 (I) : ADC3
     					// PORTF.4 (I) : VR1 
     					// PORTF.5 (I) : VR2
     					// PORTF.6 (I) : Not Used
     					// PORTF.7 (I) : Not Used  
     					
     DDRG  = 0x07;            // PORTG Data Direction ( 1:out, 0:in )   
     PORTG = 0x00;
     					// PORTG.0 (O) : RTC RST
     					// PORTG.1 (O) : RTC SCLK 					
     					// PORTG.2 (O) : RTC IO
     					// PORTG.3 (I) : Not Used				     
     					// PORTG.4 (I) : Not Used

}

void Delay_us(unsigned char time_us)		/* time delay for us */
{ 
     register unsigned char i;

     for(i = 0; i < time_us; i++) {     // 4 cycle +      
        asm volatile(" PUSH  R0 ");     		// 2 cycle +       
        asm volatile(" POP   R0 ");       		// 2 cycle + = 8 cycle = 1 us for 8MHz
     }
}

void Delay_ms(unsigned int time_ms)       	/* time delay for ms */
{ 
     register unsigned int i;

     for(i = 0; i < time_ms; i++) {
        Delay_us(250);
        Delay_us(250);
        Delay_us(250);
        Delay_us(250);
     }
}  

//--------------------------------------------------------------------------------------------------------
//	DS1302s Driver
//--------------------------------------------------------------------------------------------------------

// writes a byte on the DS1302s
void RTC_write(unsigned char command, unsigned char data)
{
	unsigned char i = 0x01;
	
	SET_CE1;
	Delay_us(1);
	IO_OUT;
	
	while(i) { //shift bit for masking
		if (i & command) {
			SET_IO1;
		} else {
			SET_IO0;
		}
		SET_SCLK1;
		Delay_us(2);
		SET_SCLK0;
		Delay_us(1);
		i <<= 1;
	}
	
	i = 0x01;
	while(i) { //shift bit for masking
		if (i & data) {
			SET_IO1;
		} else {
			SET_IO0;
		}
		SET_SCLK1;
		Delay_us(2);
		SET_SCLK0;
		Delay_us(1);
		i <<= 1;
	}
	
	SET_CE0;
}


// reads a byte form the DS1302s
unsigned char RTC_read(unsigned char command)
{
	unsigned char i = 0x01;
	unsigned char val = 0;
	
	SET_CE1;
	Delay_us(1);
	IO_OUT;
	
	while(i) { //shift bit for masking
		if (i & command) {
			SET_IO1;
		} else {
			SET_IO0;
		}
		SET_SCLK1;
		Delay_us(2);
		SET_SCLK0;
		Delay_us(1);
		i <<= 1;
	}
	
	IO_IN;
	i = 0x01;
	while(i) {
		if(GET_IO) {
			val = (val | i);
		}
		SET_SCLK1;
		Delay_us(2);
		SET_SCLK0;
		Delay_us(1);
		i <<= 1;
	}
	SET_CE0;

	return (val);
}


void connect_bt(void)
{
	
	int i, j;
     INT8U c, err;
     unsigned char *str;
     unsigned char buf[128];
     unsigned char *pbuf;
     
	
	// -------------------------------------------------------------------------------------------
	str = (unsigned char*)"AT";

	while(*str != '\0') {
		CommPutChar(COMM2,*str);
		str++;
	}
	CommPutChar(COMM2,CR);
	
	Delay_ms(500);		// wait for reply
	
	for(i=0;i<128;i++) buf[i] = 0;
	
	j = 0;
	while(1) {
        if(CommIsEmpty(COMM2) != TRUE) {
           c = CommGetChar(COMM2,&err);
           if(err == COMM_NO_ERR) {
              buf[j++] = c;  
           } 
        } else break;
        
     }  
     if(j > 127) j = 127;
	buf[j] = '\0';
	pbuf = &buf[0];
    	comm1_string((char *)pbuf);
	// -------------------------------------------------------------------------------------------
	if( (buf[2] == 'O') && (buf[3] == 'K') ) {
		
	}
	
	
	// -------------------------------------------------------------------------------------------
	str = (unsigned char*)"AT+BTINFO?";

	while(*str != '\0') {
		CommPutChar(COMM2,*str);
		//TX1_char(*str);
		str++;
	}
	CommPutChar(COMM2,CR);
	
	Delay_ms(500);		// wait for reply
	
	for(i=0;i<128;i++) buf[i] = 0;
	
	//flag_exit = 0; 
	j = 0;
	while(1) {
        if(CommIsEmpty(COMM2) != TRUE) {
           c = CommGetChar(COMM2,&err);
           if(err == COMM_NO_ERR) {
              buf[j++] = c;  
           } 
        } else break;
        
     }  
     
     if(j > 127) j = 127;
	buf[j] = '\0';
     pbuf = &buf[0];
     comm1_string((char *)pbuf);
     // -------------------------------------------------------------------------------------------
     
	
	// -------------------------------------------------------------------------------------------
	str = (unsigned char*)"AT+BTSCAN";
	while(*str != '\0') {
		CommPutChar(COMM2,*str);
		//TX1_char(*str);
		str++;
	}
	CommPutChar(COMM2,CR);
	
	Delay_ms(500);		// wait for reply
	
	for(i=0;i<128;i++) buf[i] = 0;
	
	//flag_exit = 0; 
	j = 0;
	while(1) {
        if(CommIsEmpty(COMM2) != TRUE) {
           c = CommGetChar(COMM2,&err);
           if(err == COMM_NO_ERR) {
              buf[j++] = c;  
           } 
        } else break;
        
     }  
     
     if(j > 127) j = 127;
	buf[j] = '\0';
     pbuf = &buf[0];
     comm1_string((char *)pbuf);
     // -------------------------------------------------------------------------------------------

}


void comm1_string(char *buf) 			
{
	while(*buf != '\0') {			// display string
        CommPutChar(COMM1,*buf);
        buf++;
     }
     CommPutChar(COMM1,CR);
     CommPutChar(COMM1,LF);
}



