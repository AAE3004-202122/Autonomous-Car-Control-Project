#include "ioi2c.h"
#include "sys.h"
#include "delay.h"

/**************************************************************************
Function: IIC pin initialization
Input   : none
Output  : none
函数功能：IIC引脚初始化
入口参数：无
返回  值：无
**************************************************************************/
void IIC_Init(void)
{			
	GPIO_InitTypeDef  GPIO_InitStructure;
	
	//Enable PinB port clock //使能PinB端口时钟
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB,ENABLE);	
	
	//Port configuration, PB8 //端口配置，PB8
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_8;
	//Push-pull output //推挽输出	
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;	//50M
	//Initialize GPIO with the specified parameters   //根据设定参数初始化GPIO
	GPIO_Init(GPIOB, &GPIO_InitStructure);	 
	
	//Port configuration, PB9 //端口配置，PB9
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_9;
	//Push-pull output //推挽输出	
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP; 		
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;	//50M
	//Initialize GPIO with the specified parameters   //根据设定参数初始化GPIO
	GPIO_Init(GPIOB, &GPIO_InitStructure);
	
	GPIO_SetBits(GPIOB,GPIO_Pin_8|GPIO_Pin_9);
}
/**************************************************************************
Function: Simulate IIC start signal
Input   : none
Output  : none
函数功能：模拟IIC起始信号
入口参数：无
返回  值：无
**************************************************************************/
void IIC_Start(void)
{
	SDA_OUT();    
	IIC_SDA=1;	  	  
	IIC_SCL=1;
	delay_us(4);
	//START:when CLK is high,DATA change form high to low 
 	IIC_SDA=0;
	delay_us(4);
	IIC_SCL=0;
}	  
/**************************************************************************
Function: Analog IIC end signal
Input   : none
Output  : none
函数功能：模拟IIC结束信号
入口参数：无
返回  值：无
**************************************************************************/
void IIC_Stop(void)
{
	SDA_OUT();
	IIC_SCL=0;
	IIC_SDA=0;
 	delay_us(4);
	IIC_SCL=1; 
	IIC_SDA=1;
	delay_us(4);							   	
}
/**************************************************************************
Function: IIC generates the response signal
Input   : none
Output  : none
函数功能：IIC产生应答信号
入口参数：无
返回  值：无
**************************************************************************/
unsigned char IIC_Wait_Ack(void)
{
	u8 ucErrTime=0;
	SDA_IN();      
	IIC_SDA=1;delay_us(1);	   
	IIC_SCL=1;delay_us(1);	 
	while(READ_SDA)
	{
		ucErrTime++;
		if(ucErrTime>250)
		{
			IIC_Stop();
			return 1;
		}
	}
	IIC_SCL=0;  
	return 0;  
} 
/**************************************************************************
Function: IIC response
Input   : none
Output  : none
函数功能：IIC应答
入口参数：无
返回  值：无
**************************************************************************/
void IIC_Ack(void)
{
	IIC_SCL=0;
	SDA_OUT();
	IIC_SDA=0;
	delay_us(2);
	IIC_SCL=1;
	delay_us(2);
	IIC_SCL=0;
}
/**************************************************************************
Function: IIC don't reply
Input   : none
Output  : none
函数功能：IIC不应答
入口参数：无
返回  值：无
**************************************************************************/ 
void IIC_NAck(void)
{
	IIC_SCL=0;
	SDA_OUT();
	IIC_SDA=1;
	delay_us(2);
	IIC_SCL=1;
	delay_us(2);
	IIC_SCL=0;
}					 				     
/**************************************************************************
Function: IIC sends a bit
Input   : none
Output  : none
函数功能：IIC发送一个位
入口参数：无
返回  值：无
**************************************************************************/
void IIC_Send_Byte(u8 txd)
{                        
    u8 t;   
	SDA_OUT(); 	    
    IIC_SCL=0;
    for(t=0;t<8;t++)
    {              
        IIC_SDA=(txd&0x80)>>7;
        txd<<=1; 	  
		delay_us(2);   
		IIC_SCL=1;
		delay_us(2); 
		IIC_SCL=0;	
		delay_us(2);
    }	 
} 	    
/**************************************************************************
Function: IIC reads a bit
Input   : none
Output  : none
函数功能：IIC读取一个位
入口参数：无
返回  值：无
**************************************************************************/
unsigned char IIC_Read_Byte(unsigned char ack)
{
	unsigned char i,receive=0;
	SDA_IN();
    for(i=0;i<8;i++ )
	{
        IIC_SCL=0; 
        delay_us(2);
		IIC_SCL=1;
        receive<<=1;
        if(READ_SDA)receive++;   
		delay_us(1); 
    }					 
    if (!ack)
        IIC_NAck();
    else
        IIC_Ack();
    return receive;
}

