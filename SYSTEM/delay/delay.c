#include "delay.h"
#include "sys.h"
////////////////////////////////////////////////////////////////////////////////// 	 

#if SYSTEM_SUPPORT_OS
#include "FreeRTOS.h"	//The header file used by FreeRTOS //FreeRTOS使用的头文件		  
#include "task.h"     //The header file used by FreeRTOS //FreeRTOS使用的头文件	
#endif

static u8  fac_us=0; //μs delay multiplier //μs延时倍乘数			   
static u16 fac_ms=0; //The ms delay multiple multiplier, under UCOS, represents the ms per beat //ms延时倍乘数,在ucos下,代表每个节拍的ms数
	
static u32 sysTickCnt=0;	
extern void xPortSysTickHandler(void);

/**************************************************************************
Function: Initialize the delay function
Input   : none
Output  : none
函数功能：初始化延迟函数
入口参数：无
返回  值：无
**************************************************************************/
void delay_init()
{
	u32 reload;
	
	// Select the external clock HCLK
	//选择外部时钟  HCLK
	SysTick_CLKSourceConfig(SysTick_CLKSource_HCLK);
	//Fac_us is required whether OS is used or not
	//不论是否使用OS,fac_us都需要使用
	fac_us=SystemCoreClock/1000000;
  //The number of counts per second is in M	
  //每秒钟的计数次数 单位为M 	
	reload=SystemCoreClock/1000000;	
	//Set overflow time according to configTICK_RATE_HZ
  //Reload is a 24-bit register with a maximum value of 16777216 at 72M, about 0.233s
	//根据configTICK_RATE_HZ设定溢出时间
	//reload为24位寄存器,最大值:16777216,在72M下,约合0.233s左右	
	reload*=1000000/configTICK_RATE_HZ;	
  //Represents the minimum number of units that the OS can delay	
	//代表OS可以延时的最少单位											
	fac_ms=1000/configTICK_RATE_HZ;				   

	//Enable SysStick interrupt //开启SYSTICK中断
	SysTick->CTRL|=SysTick_CTRL_TICKINT_Msk;  
	//Interrupt every 1/configTICK_RATE_HZ second
  //每1/configTICK_RATE_HZ秒中断一次 	
	SysTick->LOAD=reload; 
  //Open the SYSTICK //开启SYSTICK   	
	SysTick->CTRL|=SysTick_CTRL_ENABLE_Msk;   	 
}									    
/**************************************************************************
Function: Delay function of delay nμs
Input   : Duration of delay
Output  : none
函数功能：延时nμs的延迟函数
入口参数：延时的时长
返回  值：无
**************************************************************************/  								   
void delay_us(u32 nus)
{		
	u32 ticks;
	u32 told,tnow,tcnt=0;
	u32 reload=SysTick->LOAD;	//The value of the LOAD //LOAD的值	    	 
	ticks=nus*fac_us; 				//The number of beats required //需要的节拍数 
	told=SysTick->VAL;        //The value of the counter on entry //刚进入时的计数器值
	while(1)
	{
		tnow=SysTick->VAL;	
		if(tnow!=told)
		{	    
			if(tnow<told)tcnt+=told-tnow;	//SysStick is a decrement counter //这里注意一下SYSTICK是一个递减的计数器就可以了
			else tcnt+=reload-tnow+told;	    
			told=tnow;
			if(tcnt>=ticks)break;			//If the delay time exceeds or equals the delay time, exit //时间超过或者等于要延迟的时间,则退出
		}  
	};										    
}  
/**************************************************************************
Function: Delay function of Delay nms
Input   : Duration of delay
Output  : none
函数功能：延时nms的延迟函数
入口参数：延时的时长
返回  值：无
**************************************************************************/  
void delay_ms(u32 nms)
{	
	if(xTaskGetSchedulerState()!=taskSCHEDULER_NOT_STARTED) //The system is running //系统已经运行
	{		
		if(nms>=fac_ms)	//The duration of the delay is greater than the OS minimum duration //延时的时间大于OS的最少时间周期 
		{ 
   			vTaskDelay(nms/fac_ms);	//FreeRTOS latency //FreeRTOS延时
		}
		nms%=fac_ms;	//OS is no longer able to provide such a small delay, use normal delay //OS已经无法提供这么小的延时了,采用普通方式延时    
	}
	delay_us((u32)(nms*1000));	//Normal mode delay	//普通方式延时
}
/**************************************************************************
Function: Delay function of delay ms
Input   : Duration of delay
Output  : none
函数功能：延时ms的延迟函数
入口参数：延时的时长
返回  值：无
**************************************************************************/  
void delay_xms(u32 nms)
{
	u32 i;
	for(i=0;i<nms;i++) delay_us(1000);
}

/**************************************************************************
Function: Tick timer interrupt service function
Input   : Duration of delay
Output  : none
函数功能：滴答定时器中断服务函数
入口参数：延时的时长
返回  值：无
**************************************************************************/  
void SysTick_Handler(void)
{	
    if(xTaskGetSchedulerState()!=taskSCHEDULER_NOT_STARTED) //The system is running //系统已经运行
    {
        xPortSysTickHandler();	
    }
		else
		{
		sysTickCnt++;	//Counting before scheduling is enabled //调度开启之前计数
	}
}
/**************************************************************************
Function: Get the time of the last execution function
Input   : none
Output  : The last time the program was executed
函数功能：获取上次执行函数的时间
入口参数：无
返回  值：上一次执行程序的时间
**************************************************************************/ 
u32 getSysTickCnt(void)
{
	if(xTaskGetSchedulerState()!=taskSCHEDULER_NOT_STARTED)	//The system is running //系统已经运行
		return xTaskGetTickCount();
	else
		return sysTickCnt;
}

