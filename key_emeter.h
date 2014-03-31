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

#define  KEY_BUF_SIZE               10      	// 키보드 버퍼의 크기    

#define  KEY_MAX_ROWS                1     	// 키보드의 최대 행(row) 수 
#define  KEY_MAX_COLS                4     	// 키보드의 최대 열(column) 수
//#define  KEY_MAX_ROWS                5     	// 키보드의 최대 행(row) 수                                
//#define  KEY_MAX_COLS                6     	// 키보드의 최대 열(column) 수                                                               

#define  KEY_RPT_DLY                10      	// 자동 반복기능이 다시 수행되기 전의 스캔타임 값          
#define  KEY_RPT_START_DLY          50      	// 자동 반복기능이 수행되기까지의 스캔타임 값              

#define  KEY_SCAN_TASK_DLY          20      	// 키를 스캔하는 시간 간격 (ms)

#define  KEY_ALL_ROWS             0xF8      	// 모든 행을 선택 (즉, 모든 행은 1로 출력)                                               


/*
*********************************************************************************************************
*                                             함수 원형
*********************************************************************************************************
*/
void		KeyBufIn(INT8U code);     			// 스캔코드를 키보드 버퍼에 저장한다                       
INT8U	KeyDecode(void);          			// 현재 눌려진 키보드의 스캔코드를 얻는다                  
BOOLEAN	KeyIsKeyDown(void);       			// 키가 눌려져 있는 지를 확인한다                          
void		KeyScanTask(void);  				// 키보드 스캐닝 태스크  
INT8U 	KeyGetKey(void);    
BOOLEAN	KeyHit(void);                           // 키가 눌려져 있는 지를 확인(눌렸으면 TRUE, 그렇지 않으면FALSE)   
void 	KeySelRow(INT8U row);				// 행을 선택한다                                                

void 	KeyFlush(void);
void 	KeyInit(void);   

#define KEY_MODE	3
#define KEY_UP		2
#define KEY_DOWN	1
#define KEY_ENT	0


#endif		// KEY_EMETER_H
   


