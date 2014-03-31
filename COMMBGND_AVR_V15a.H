/*
*********************************************************************************************************
*                                     Embedded Systems Building Blocks
*                                  Complete and Ready-to-Use Modules in C
*
*                                    Asynchronous Serial Communications
*                                          Buffered Serial I/O
*                                     (Foreground/Background Systems)
*
* Filename   : COMMBGND_AVR_V15a.H
* Date       : 01/30/2013
* Programmer : Modified by Joonik Son
* Note       : COMM_NUM is used for selecting the number of channels.
*********************************************************************************************************               
*/

/*
*********************************************************************************************************
*                                              설정상수
*********************************************************************************************************
*/

#ifndef	_COMMBGND_AVR_V15A_H
#define	_COMMBGND_AVR_V15A_H

//#ifndef  CFG_H

#define  COMM_RX_BUF_SIZE	256               /* 수신용 링 버퍼의 데이터 개수                       */
#define  COMM_TX_BUF_SIZE     256               /* 송신용 링 퍼버의 데이터 개수                       */

//#endif

/*
*********************************************************************************************************
*                                                상수
*********************************************************************************************************
*/

#ifndef  NUL
#define  NUL                 0x00
#endif

#define  COMM_NUM			  2				// channel 수 지정

#define  COMM1                  1
#define  COMM2                  2

                                                 /* 에러코드                                           */
#define  COMM_NO_ERR            0                /* 함수 호출이 성공적으로 수행되었음                  */
#define  COMM_BAD_CH            1                /* 무효한 채널을 지정했음                             */
#define  COMM_RX_EMPTY          2                /* 수신 버퍼가 비었음. 데이터가 없음                  */
#define  COMM_TX_FULL           3                /* 송신 버퍼가 완전히 찼음. 데이터를 저장할 수 없음   */
#define  COMM_TX_EMPTY          4                /* 송신 버퍼가 비었음                                 */


//#ifdef   COMM_GLOBALS
//#define  COMM_EXT
//#else
//#define  COMM_EXT  extern
//#endif

/*
*********************************************************************************************************
*                                              함수원형
*********************************************************************************************************
*/
void	CommTxIntEn(INT8U ch);		// 송신 인터럽트 인에이블 

INT8U    CommGetChar(INT8U ch, INT8U *err);
INT8U    CommGetTxChar(INT8U ch, INT8U *err);
void     CommInit(void);
BOOLEAN  CommIsEmpty(INT8U ch);
BOOLEAN  CommIsFull(INT8U ch);
INT8U    CommPutChar(INT8U ch, INT8U c);
void     CommPutRxChar(INT8U ch, INT8U c); 
void	    CommTxIntEn(INT8U ch);			 	// 송신 인터럽트 인에이블    

#endif	/* _COMMBGND_AVR_V15A_H */

