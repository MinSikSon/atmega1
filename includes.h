//
//********************************************************************************************************
// 	Date: 	Jan 01, 2013	                                              	
//********************************************************************************************************
//	FILE:	includes.h 
// 
//	TITLE:	Include Definition
//********************************************************************************************************
//

#ifndef AVR_INCLUDE_H
#define AVR_INCLUDE_H

#include <stdio.h>
#include <math.h>
#include <avr/io.h>
#include <avr/interrupt.h>
#include <avr/eeprom.h>

#ifndef AVR_DATA_TYPES
#define AVR_DATA_TYPES

typedef unsigned char  BOOLEAN;
typedef unsigned char  INT8U;                    /* Unsigned  8 bit quantity                            */
typedef signed   char  INT8S;                    /* Signed    8 bit quantity                            */
typedef unsigned int   INT16U;                   /* Unsigned 16 bit quantity                            */
typedef signed   int   INT16S;                   /* Signed   16 bit quantity                            */
typedef unsigned long  INT32U;                   /* Unsigned 32 bit quantity                            */
typedef signed   long  INT32S;                   /* Signed   32 bit quantity                            */
typedef float          FP32;                     /* Single precision floating point                     */    

typedef unsigned char byte;
//typedef unsigned char bool;

#endif

#define TRUE	1
#define FALSE	0   

#define SET	1
#define CLR	0            

#define OS_ENTER_CRITICAL()  cli(); 
#define OS_EXIT_CRITICAL()   sei();

#define CR	0x0D
#define LF     0x0A

#define STX	0x02
#define ETX	0x03   
//#define STX	'$'
//#define ETX	'%' 


#include "sub_emeter.h"
#include "key_emeter.h"
#include "CLCDDRV_AVR_V10a.H"
#include "M95256DRV_V10.h"
#include "COMMBGND_AVR_V15a.h"

#include "sub_emeter.c"
#include "key_emeter.c"
#include "CLCDDRV_AVR_V10a.c"
#include "M95256DRV_V10.c"
#include "COMMBGND_AVR_V15a.C"

#endif


