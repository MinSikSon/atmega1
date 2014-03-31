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
*                                              �������
*********************************************************************************************************
*/

#ifndef	_COMMBGND_AVR_V15A_H
#define	_COMMBGND_AVR_V15A_H

//#ifndef  CFG_H

#define  COMM_RX_BUF_SIZE	256               /* ���ſ� �� ������ ������ ����                       */
#define  COMM_TX_BUF_SIZE     256               /* �۽ſ� �� �۹��� ������ ����                       */

//#endif

/*
*********************************************************************************************************
*                                                ���
*********************************************************************************************************
*/

#ifndef  NUL
#define  NUL                 0x00
#endif

#define  COMM_NUM			  2				// channel �� ����

#define  COMM1                  1
#define  COMM2                  2

                                                 /* �����ڵ�                                           */
#define  COMM_NO_ERR            0                /* �Լ� ȣ���� ���������� ����Ǿ���                  */
#define  COMM_BAD_CH            1                /* ��ȿ�� ä���� ��������                             */
#define  COMM_RX_EMPTY          2                /* ���� ���۰� �����. �����Ͱ� ����                  */
#define  COMM_TX_FULL           3                /* �۽� ���۰� ������ á��. �����͸� ������ �� ����   */
#define  COMM_TX_EMPTY          4                /* �۽� ���۰� �����                                 */


//#ifdef   COMM_GLOBALS
//#define  COMM_EXT
//#else
//#define  COMM_EXT  extern
//#endif

/*
*********************************************************************************************************
*                                              �Լ�����
*********************************************************************************************************
*/
void	CommTxIntEn(INT8U ch);		// �۽� ���ͷ�Ʈ �ο��̺� 

INT8U    CommGetChar(INT8U ch, INT8U *err);
INT8U    CommGetTxChar(INT8U ch, INT8U *err);
void     CommInit(void);
BOOLEAN  CommIsEmpty(INT8U ch);
BOOLEAN  CommIsFull(INT8U ch);
INT8U    CommPutChar(INT8U ch, INT8U c);
void     CommPutRxChar(INT8U ch, INT8U c); 
void	    CommTxIntEn(INT8U ch);			 	// �۽� ���ͷ�Ʈ �ο��̺�    

#endif	/* _COMMBGND_AVR_V15A_H */
