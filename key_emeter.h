//
//********************************************************************************************************
// 	Date: 	Dec 05, 2013	                                              	
//********************************************************************************************************
//	FILE:	key_emeter.h 
// 
//	TITLE:	Key Subroutine for E-Metering
//********************************************************************************************************
//


#ifndef KEY_EMETER_H
#define KEY_EMETER_H

#define  KEY_BUF_SIZE               10      	// Ű���� ������ ũ��    

#define  KEY_MAX_ROWS                1     	// Ű������ �ִ� ��(row) �� 
#define  KEY_MAX_COLS                4     	// Ű������ �ִ� ��(column) ��
//#define  KEY_MAX_ROWS                5     	// Ű������ �ִ� ��(row) ��                                
//#define  KEY_MAX_COLS                6     	// Ű������ �ִ� ��(column) ��                                                               

#define  KEY_RPT_DLY                10      	// �ڵ� �ݺ������ �ٽ� ����Ǳ� ���� ��ĵŸ�� ��          
#define  KEY_RPT_START_DLY          50      	// �ڵ� �ݺ������ ����Ǳ������ ��ĵŸ�� ��              

#define  KEY_SCAN_TASK_DLY          20      	// Ű�� ��ĵ�ϴ� �ð� ���� (ms)

#define  KEY_ALL_ROWS             0xF8      	// ��� ���� ���� (��, ��� ���� 1�� ���)                                               


/*
*********************************************************************************************************
*                                             �Լ� ����
*********************************************************************************************************
*/
void		KeyBufIn(INT8U code);     			// ��ĵ�ڵ带 Ű���� ���ۿ� �����Ѵ�                       
INT8U	KeyDecode(void);          			// ���� ������ Ű������ ��ĵ�ڵ带 ��´�                  
BOOLEAN	KeyIsKeyDown(void);       			// Ű�� ������ �ִ� ���� Ȯ���Ѵ�                          
void		KeyScanTask(void);  				// Ű���� ��ĳ�� �½�ũ  
INT8U 	KeyGetKey(void);    
BOOLEAN	KeyHit(void);                           // Ű�� ������ �ִ� ���� Ȯ��(�������� TRUE, �׷��� ������FALSE)   
void 	KeySelRow(INT8U row);				// ���� �����Ѵ�                                                

void 	KeyFlush(void);
void 	KeyInit(void);   

#define KEY_MODE	3
#define KEY_UP		2
#define KEY_DOWN	1
#define KEY_ENT	0


#endif		// KEY_EMETER_H
   


