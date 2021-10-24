#ifndef __USART_H
#define __USART_H
#include "stdio.h"	
#include "sys.h" 

#define USART_REC_LEN 200 //The maximum number of bytes received is 200 //定义最大接收字节数 200
#define EN_USART1_RX 	1		//Enable (1)/Disable (0) Serial port 1 reception //使能（1）/禁止（0）串口1接收
void usart1_init(u32 bound);	  
extern u8  USART_RX_BUF[USART_REC_LEN]; //Receive buffer, maximum USART_REC_LEN bytes.The last byte is a newline character //接收缓冲,最大USART_REC_LEN个字节.末字节为换行符 
extern u16 USART_RX_STA;  //Receive status markers //接收状态标记	
//If you want serial port interrupt reception, do not comment the following macro definitions
//如果想串口中断接收，请不要注释以下宏定义
void uart_init(u32 bound);
#endif


