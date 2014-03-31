//
//********************************************************************************************************
// 	Date		: 	April 5, 2013	                                              	
//********************************************************************************************************
//	FILE		:	M95256DRV_V10.C 
// 
//	TARGET	:	AT90CAN128/ATmega128
//
//	VERSION	:	1.0
//
//	NOTE		:	
//
//********************************************************************************************************
//

#include "includes.h"

//--------------------------------------------------------------------------------------------------------
//	SPI Driver by AT90CAN128/ATmega128 GPIO
//--------------------------------------------------------------------------------------------------------
unsigned char Spi8Driver(unsigned char data)
{
	unsigned char read;
	SPDR = data;
	while((SPSR & 0x80) == 0x00);
	read = SPDR;
	return read;
}

//--------------------------------------------------------------------------------------------------------
//    Read Data from Eeprom
//--------------------------------------------------------------------------------------------------------
unsigned char ReadEeprom(unsigned int address)
{
	unsigned char out;

	EEPROM_CS_ON();

	Spi8Driver(READ_EEPROM);
	Spi8Driver(ADDRESS_HIGH(address));
	Spi8Driver(ADDRESS_LOW(address));
	out = Spi8Driver(DUMMY_EEPROM);
	
	EEPROM_CS_OFF();

	return out;
}

//--------------------------------------------------------------------------------------------------------
//    Address Write Data to Eeprom
//--------------------------------------------------------------------------------------------------------
void WriteEeprom(unsigned int address, unsigned char data)
{
	EEPROM_CS_ON();

	Spi8Driver(WRITE_EEPROM);
	Spi8Driver(ADDRESS_HIGH(address));
	Spi8Driver(ADDRESS_LOW(address));
	Spi8Driver(data);
	
	EEPROM_CS_OFF();

	while(ReadStatusRegisterEeprom() & 0x01);
}

//--------------------------------------------------------------------------------------------------------
//    Page Write Data to Eeprom
//--------------------------------------------------------------------------------------------------------
void PWriteEeprom(unsigned int page, unsigned int *start_addr)
{
	unsigned int address,n;
	address = page * 128;

	EEPROM_CS_ON();

	Spi8Driver(WRITE_EEPROM);
	Spi8Driver(ADDRESS_HIGH(address));
	Spi8Driver(ADDRESS_LOW(address));
	for(n=0;n<128;n++){
		Spi8Driver(start_addr[n]);
	}

	EEPROM_CS_OFF();

	while(ReadStatusRegisterEeprom() & 0x0001);
}

//--------------------------------------------------------------------------------------------------------
//    Write Enable
//--------------------------------------------------------------------------------------------------------
void WriteEnableEeprom(void)
{
	EEPROM_CS_ON();

	Spi8Driver(WREN_EEPROM);

	EEPROM_CS_OFF();
}

//--------------------------------------------------------------------------------------------------------
//    Write Disable
//--------------------------------------------------------------------------------------------------------
void WriteDisableEeprom(void)
{
	EEPROM_CS_ON();

	Spi8Driver(WRDI_EEPROM);

	EEPROM_CS_OFF();
}

//--------------------------------------------------------------------------------------------------------
//    Read Status Register from Eeprom
//--------------------------------------------------------------------------------------------------------
unsigned char ReadStatusRegisterEeprom(void)
{
	unsigned char out;

	EEPROM_CS_ON();

	Spi8Driver(RDSR_EEPROM);
	out = Spi8Driver(DUMMY_EEPROM);

	EEPROM_CS_OFF();

	return out;
}

/*---------------------------------------------------------------------------
	Proto Type :	void WriteStatusRegisterEeprom(Uint state_register)
	Function   : 	Write Status Register
	Parameta   : 	state_register
					x--- ---- ; SRWD is don't care in our case
					-000 ---- ; Not Used
					---- 0--- ; Clear BP1
					---- -0-- ; Clear BP2
					---- --R- ; Write Enable Latch Bit,Read Only,Enable == 1
					---- ---R ; Write In Progress Bit,Read Only,Progress == 1
	Return     :	None
---------------------------------------------------------------------------*/
void WriteStatusRegisterEeprom(unsigned char StatusRegister)
{
	EEPROM_CS_ON();

	Spi8Driver(WRSR_EEPROM);
	Spi8Driver(StatusRegister);

	EEPROM_CS_OFF();

	while(ReadStatusRegisterEeprom() & 0x01);
}



void InitEeprom(void)
{

/*---------------------------------------------------------------------------
	1. WREN
---------------------------------------------------------------------------*/
	while(ReadStatusRegisterEeprom() & 0x01);
	
	WriteEnableEeprom();
	
/*---------------------------------------------------------------------------
	2. WRSR
	2.1 DISABLE PROTECT AREA BP0=0,BP1=0
---------------------------------------------------------------------------*/
	WriteStatusRegisterEeprom(STATUS_REG_EEPROM);
}

unsigned char ApiVersionEeprom(void)
{
	unsigned char version = M95256_API_VERSION;
	return version;
}

unsigned char ApiVersionHexEeprom(void)
{
	unsigned char version = M95256_API_VERSION_HEX;
	return version;
}

/*======================================================================
	End of file.
======================================================================*/

