#include "usart.h"	
 
//If using UCOS, include the following header file.
//如果使用ucos,则包括下面的头文件即可.
#if SYSTEM_SUPPORT_OS
#include "FreeRTOS.h"	//The header file used by FreeRTOS //FreeRTOS使用的头文件	
#endif

/*****Add the following code to support printf without having to select use MicroLIB****/
/*****加入以下代码,支持printf函数,而不需要选择use MicroLIB****/	  
#if 1
#pragma import(__use_no_semihosting)  
//Support functions required by the library
//标准库需要的支持函数                 
struct __FILE 
{ 
	int handle; 

}; 

FILE __stdout;  
//Define _sys_exit() to avoid using half-host mode
//定义_sys_exit()以避免使用半主机模式    
void _sys_exit(int x) 
{ 
	x = x; 
} 
//Redefine the fputc function
//重定义fputc函数 
int fputc(int ch, FILE *f)
{      
	while((USART2->SR&0X40)==0); //Loop to send until it is finished //循环发送,直到发送完毕   
    USART2->DR = (u8) ch;      
	return ch;
}
#endif 
/************************************************************/
 
void usart1_init(u32 bound)
{
  //GPIO port setup //GPIO端口设置
  GPIO_InitTypeDef GPIO_InitStructure;
	USART_InitTypeDef USART_InitStructure;
	 
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_USART1|RCC_APB2Periph_GPIOA, ENABLE);	//Enable USART1, GPIOA clock //使能USART1，GPIOA时钟
  
	//USART1_TX   GPIOA9
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_9; //PA9
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;	//Reuse push-pull output //复用推挽输出
  GPIO_Init(GPIOA, &GPIO_InitStructure); //Initialize GPIOA9 //初始化GPIOA9
   
  //USART1_RX	  GPIOA10
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_10;//PA10
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING; //Float input //浮空输入
  GPIO_Init(GPIOA, &GPIO_InitStructure); //Initialize GPIOA10 //初始化GPIOA10 
	
	//USART Initialization Settings
  //USART初始化设置
	USART_InitStructure.USART_BaudRate = bound; //Serial port baud rate //串口波特率
	USART_InitStructure.USART_WordLength = USART_WordLength_8b; //The word size is 8 bit data format //字长为8位数据格式
	USART_InitStructure.USART_StopBits = USART_StopBits_1; //A stop bit//一个停止位
	USART_InitStructure.USART_Parity = USART_Parity_No; //No-no parity bits //无奇偶校验位
	USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None; //Non-hardware data flow control //无硬件数据流控制
	USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;	//Receipt mode //收发模式

  USART_Init(USART1, &USART_InitStructure); //Initialize serial port 1 //初始化串口1
  USART_ITConfig(USART1, USART_IT_RXNE, DISABLE); //Open the serial port to accept interrupts //开启串口接受中断
  USART_Cmd(USART1, ENABLE); //Enable serial port 1 //使能串口1 
}

#if EN_USART1_RX //If enabled to receive //如果使能了接收
// Serial port 1 interrupt service routine
// Note that read USARTx- >;SR can avoid inexplicable errors
//串口1中断服务程序
//注意,读取USARTx->SR能避免莫名其妙的错误   	
u8 USART_RX_BUF[USART_REC_LEN]; //Receive buffer, maximum USART_REC_LEN bytes //接收缓冲,最大USART_REC_LEN个字节
//Receive status
//bit15, receive complete flag
//bit14, 0x0d received
//bit13~0, the number of valid bytes received
//接收状态
//bit15，	接收完成标志
//bit14，	接收到0x0d
//bit13~0，	接收到的有效字节数目
u16 USART_RX_STA=0; //Receive status markers //接收状态标记	  

#endif	

