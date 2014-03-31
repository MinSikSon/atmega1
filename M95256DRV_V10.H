//
//********************************************************************************************************
// 	Date		: 	April 5, 2013	                                              	
//********************************************************************************************************
//	FILE		:	M95256DRV_V10.H 
// 
//	TARGET	:	AT90CAN128/ATmega128
//
//	VERSION	:	1.0
//
//	NOTE		:	
//
//********************************************************************************************************
//

#ifndef M95256DRV_H
#define M95256DRV_H

#define M95256_API_VERSION		10
#define M95256_API_VERSION_HEX	0x10

#define WREN_EEPROM			0x06
#define WRDI_EEPROM			0x04
#define RDSR_EEPROM			0x05
#define WRSR_EEPROM			0x01
#define READ_EEPROM			0x03
#define WRITE_EEPROM		0x02
#define DUMMY_EEPROM		0xAA
#define STATUS_REG_EEPROM	0x00

#define ADDRESS_HIGH(w)	((w>>8) & 0x00ff)
#define ADDRESS_LOW(w)	((w) & 0x00ff)


#define EEPROM_CS_ON()		PORTB&=~0x01
#define EEPROM_CS_OFF()		PORTB|=0x01


unsigned char Spi8Driver(unsigned char data);
void InitEeprom(void);
void WriteStatusRegisterEeprom(unsigned char StatusRegister);
unsigned char ReadStatusRegisterEeprom(void);
void WriteDisableEeprom(void);
void WriteEnableEeprom(void);
void WriteEeprom(unsigned int address, unsigned char data);
void PWriteEeprom(unsigned int Page, unsigned int *start_addr);
unsigned char ReadEeprom(unsigned int address);
unsigned char ApiVersionEeprom(void);
unsigned char ApiVersionHexEeprom(void);

#endif

/*======================================================================
	End of file.
======================================================================*/

