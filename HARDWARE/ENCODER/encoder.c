#include "encoder.h"

/**************************************************************************
Function: Initialize TIM2 as the encoder interface mode
Input   : none
Output  : none
函数功能：把TIM2初始化为编码器接口模式
入口参数：无
返 回 值：无
**************************************************************************/
void Encoder_Init_TIM2(void)
{
	TIM_TimeBaseInitTypeDef TIM_TimeBaseStructure;  
	TIM_ICInitTypeDef TIM_ICInitStructure;  
	GPIO_InitTypeDef GPIO_InitStructure;
	
	//Enable the timer 2 clock //使能定时器2的时钟
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2, ENABLE);
	//Enable PinA, PinB port clocks //使能PinA、PinB端口时钟
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA|RCC_APB2Periph_GPIOB, ENABLE);
	//Enable reuse //启用复用功能
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO, ENABLE); 
	//Disable JTAG to enable SWD //关闭JTAG，使能SWD
	GPIO_PinRemapConfig(GPIO_Remap_SWJ_JTAGDisable, ENABLE);
	//Pin remapping //引脚重映射
	GPIO_PinRemapConfig(GPIO_PartialRemap1_TIM2, ENABLE);	 
	
	//Port configuration, PA15 //端口配置，PA15
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_15;	
	//Float input //浮空输入
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING; 
	//Initialize GPIOA with the set parameters //根据设定参数初始化GPIOA
	GPIO_Init(GPIOA, &GPIO_InitStructure);					      
  
	//Port configuration, PB3 //端口配置，PB3
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_3;	
	//Float input //浮空输入
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;
  //Initialize the gpiob by setting parameters //根据设定参数初始化GPIOB	
	GPIO_Init(GPIOB, &GPIO_InitStructure);					      
	
	TIM_TimeBaseStructInit(&TIM_TimeBaseStructure);
	//Pre-divider setup //预分频器设置 
	TIM_TimeBaseStructure.TIM_Prescaler = 0x0; 
	//Set the counter to automatically reload//设定计数器自动重装值
	TIM_TimeBaseStructure.TIM_Period = ENCODER_TIM_PERIOD; 
	//Select the clock frequency division: no frequency //选择时钟分频：不分频
	TIM_TimeBaseStructure.TIM_ClockDivision = TIM_CKD_DIV1;
	//Up counting mode //向上计数模式  
	TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;
	//Initialize timer 2 //初始化定时器2
	TIM_TimeBaseInit(TIM2, &TIM_TimeBaseStructure);  
	//Use encoder mode 3 //使用编码器模式3
	TIM_EncoderInterfaceConfig(TIM2, TIM_EncoderMode_TI12, TIM_ICPolarity_Rising, TIM_ICPolarity_Rising);
	
	//Fill in each parameter in the TIM_ICInitStruct with the default value
	//把TIM_ICInitStruct 中的每一个参数按缺省值填入
	TIM_ICStructInit(&TIM_ICInitStructure);
  //Set the filter length //设置滤波器长度	
	TIM_ICInitStructure.TIM_ICFilter = 10;
	//Initialize the peripheral TIMX based on the parameter TIM_ICINITSTRUCT
  //根据 TIM_ICInitStruct 的参数初始化外设	TIMx  
	TIM_ICInit(TIM2, &TIM_ICInitStructure);
 
  //Clear the update bit for Tim //清除TIM的更新标志位
	TIM_ClearFlag(TIM2, TIM_FLAG_Update);
	//Enable the timer to interrupt //使能定时器中断
	TIM_ITConfig(TIM2, TIM_IT_Update, ENABLE);
	
	//Reset the timer count //重置定时器计数
	TIM_SetCounter(TIM2,0); 
	//Enable timer 2 //使能定时器2
	TIM_Cmd(TIM2, ENABLE); 
}

/**************************************************************************
Function: Initialize TIM3 as the encoder interface mode
Input   : none
Output  : none
函数功能：把TIM3初始化为编码器接口模式
入口参数：无
返回  值：无
**************************************************************************/
void Encoder_Init_TIM3(void)
{
	TIM_TimeBaseInitTypeDef TIM_TimeBaseStructure;  
  TIM_ICInitTypeDef TIM_ICInitStructure;  
  GPIO_InitTypeDef GPIO_InitStructure;
	
	//Enable the timer 3 clock //使能定时器3的时钟
  RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3, ENABLE);
	//Enable PA port clock //使能PA端口时钟
  RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);
	//Enable reuse //启用复用功能
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO, ENABLE);

	//Port configuration, PA6, PA7 //端口配置，PA6、PA7
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_6|GPIO_Pin_7;	
	//Float input //浮空输入
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;
  //Initialize GPIOA with the set parameters //根据设定参数初始化GPIOA	
  GPIO_Init(GPIOA, &GPIO_InitStructure);					      
  	
  TIM_TimeBaseStructInit(&TIM_TimeBaseStructure);
	//Set up the pre-divider //设置预分频器 
  TIM_TimeBaseStructure.TIM_Prescaler = 0x0; 
	//Set the counter to automatically reload //设定计数器自动重装值
  TIM_TimeBaseStructure.TIM_Period = ENCODER_TIM_PERIOD;
  //Select the clock frequency division: no frequency //选择时钟分频：不分频	
  TIM_TimeBaseStructure.TIM_ClockDivision = TIM_CKD_DIV1;
	//Up counting mode //向上计数模式 
  TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;
	//Initialize timer 3//初始化定时器3
  TIM_TimeBaseInit(TIM3, &TIM_TimeBaseStructure);  
	
	//Use encoder mode 3 //使用编码器模式3
  TIM_EncoderInterfaceConfig(TIM3, TIM_EncoderMode_TI12, TIM_ICPolarity_Rising, TIM_ICPolarity_Rising);
	
	//Fill in each parameter in the TIM_ICInitStruct with the default value
	//把TIM_ICInitStruct 中的每一个参数按缺省值填入
  TIM_ICStructInit(&TIM_ICInitStructure); 
	//Set the filter length //设置滤波器长度
  TIM_ICInitStructure.TIM_ICFilter = 10; 
  //Initialize the peripheral TIMX based on the parameter TIM_ICINITSTRUCT //根据 TIM_ICInitStruct 的参数初始化外设	TIMx	
  TIM_ICInit(TIM3, &TIM_ICInitStructure);
 
  //Clear the update bit for Tim //清除TIM的更新标志位
  TIM_ClearFlag(TIM3, TIM_FLAG_Update);
	//Enable the timer to interrupt //使能定时器中断
  TIM_ITConfig(TIM3, TIM_IT_Update, ENABLE);
	//Reset the timer count //重置定时器计数
	TIM_SetCounter(TIM3,0);
	//Enable timer 3 //使能定时器3
	TIM_Cmd(TIM3, ENABLE); 
}
/**************************************************************************
Function: Initialize TIM4 as the encoder interface mode
Input   : none
Output  : none
函数功能：把TIM4初始化为编码器接口模式
入口参数：无
返 回 值：无
**************************************************************************/
void Encoder_Init_TIM4(void)
{
	TIM_TimeBaseInitTypeDef TIM_TimeBaseStructure;  
	TIM_ICInitTypeDef TIM_ICInitStructure;  
	GPIO_InitTypeDef GPIO_InitStructure;
	
	//Enable timer 4 clock //使能定时器4的时钟 
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM4, ENABLE);
	//Enable pB port clock //使能PB端口时钟
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);
	
	//Port configuration, PB6, PB7 //端口配置，PB6、PB7
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_6|GPIO_Pin_7;
  //Float input //浮空输入	
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING; 
	//Initialize GPIOB with the specified parameters //根据设定参数初始化GPIOB
	GPIO_Init(GPIOB, &GPIO_InitStructure);					      
  
	TIM_TimeBaseStructInit(&TIM_TimeBaseStructure);
	//Set up the pre-divider //设置预分频器 
	TIM_TimeBaseStructure.TIM_Prescaler = 0x0; 
	//Set the counter to automatically reload //设定计数器自动重装值
	TIM_TimeBaseStructure.TIM_Period = ENCODER_TIM_PERIOD; 
	//Select the clock frequency division: no frequency //选择时钟分频：不分频	
	TIM_TimeBaseStructure.TIM_ClockDivision = TIM_CKD_DIV1;
	//Up counting mode //向上计数模式 
	TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;
	//Initialize timer 4//初始化定时器4
	TIM_TimeBaseInit(TIM4, &TIM_TimeBaseStructure);
	
	//Use encoder mode 3 //使用编码器模式3
	TIM_EncoderInterfaceConfig(TIM4, TIM_EncoderMode_TI12, TIM_ICPolarity_Rising, TIM_ICPolarity_Rising);
	
	//Fill in each parameter in the TIM_ICInitStruct with the default value
	//把TIM_ICInitStruct 中的每一个参数按缺省值填入
	TIM_ICStructInit(&TIM_ICInitStructure);
	//Set the filter length //设置滤波器长度
	TIM_ICInitStructure.TIM_ICFilter = 10;
	//Initialize the peripheral TIMX based on the parameter TIM_ICINITSTRUCT //根据 TIM_ICInitStruct 的参数初始化外设	TIMx	
	TIM_ICInit(TIM4, &TIM_ICInitStructure);
	
	//Clear the update bit for Tim //清除TIM的更新标志位
	TIM_ClearFlag(TIM4, TIM_FLAG_Update);
	//Enable the timer to interrupt //使能定时器中断
	TIM_ITConfig(TIM4, TIM_IT_Update, ENABLE);
	//Reset the timer count //重置定时器计数
	TIM_SetCounter(TIM4,0);
	//Enable timer 4 //使能定时器4
	TIM_Cmd(TIM4, ENABLE); 
}
/**************************************************************************
Function: Initialize TIM5 as the encoder interface mode
Input   : none
Output  : none
函数功能：把TIM5初始化为编码器接口模式
入口参数：无
返回  值：无
**************************************************************************/
void Encoder_Init_TIM5(void)
{
	TIM_TimeBaseInitTypeDef TIM_TimeBaseStructure;  
  TIM_ICInitTypeDef TIM_ICInitStructure;  
  GPIO_InitTypeDef GPIO_InitStructure;
	
	//Enable timer 5 clock //使能定时器5的时钟 
  RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM5, ENABLE);
	//Enable pA port clock //使能PA端口时钟
  RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);
	
	//Port configuration, PA0, PA1 //端口配置，PA0、PA1
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0|GPIO_Pin_1;	
	//Float input //浮空输入
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;
	//Initialize GPIOA with the specified parameters //根据设定参数初始化GPIOA
  GPIO_Init(GPIOA, &GPIO_InitStructure);					      
  
  TIM_TimeBaseStructInit(&TIM_TimeBaseStructure);
	//Set up the pre-divider //设置预分频器 
  TIM_TimeBaseStructure.TIM_Prescaler = 0x0; 
	//Set the counter to automatically reload //设定计数器自动重装值
  TIM_TimeBaseStructure.TIM_Period = ENCODER_TIM_PERIOD;
	//Select the clock frequency division: no frequency //选择时钟分频：不分频	
  TIM_TimeBaseStructure.TIM_ClockDivision = TIM_CKD_DIV1;
	//Up counting mode //向上计数模式 
  TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up; 
	//Initialize timer 5//初始化定时器5
  TIM_TimeBaseInit(TIM5, &TIM_TimeBaseStructure);
	
	//Use encoder mode 3 //使用编码器模式3
  TIM_EncoderInterfaceConfig(TIM5, TIM_EncoderMode_TI12, TIM_ICPolarity_Rising, TIM_ICPolarity_Rising);
	
	//Fill in each parameter in the TIM_ICInitStruct with the default value
	//把TIM_ICInitStruct 中的每一个参数按缺省值填入
  TIM_ICStructInit(&TIM_ICInitStructure); 
	//Set the filter length //设置滤波器长度
  TIM_ICInitStructure.TIM_ICFilter = 10;
	//Initialize the peripheral TIMX based on the parameter TIM_ICINITSTRUCT //根据 TIM_ICInitStruct 的参数初始化外设	TIMx	
  TIM_ICInit(TIM5, &TIM_ICInitStructure);
 
  //Clear the update bit for Tim //清除TIM的更新标志位
  TIM_ClearFlag(TIM5, TIM_FLAG_Update);
	//Enable the timer to interrupt //使能定时器中断
  TIM_ITConfig(TIM5, TIM_IT_Update, ENABLE);
	//Reset the timer count //重置定时器计数
  TIM_SetCounter(TIM5,0);
	//Enable timer 5 //使能定时器5
  TIM_Cmd(TIM5, ENABLE);  
}

/**************************************************************************
Function: Read the encoder count
Input   : The timer
Output  : Encoder value (representing speed)
函数功能：读取编码器计数
入口参数：定时器
返回  值：编码器数值(代表速度)
**************************************************************************/
int Read_Encoder(u8 TIMX)
{
 int Encoder_TIM;    
 switch(TIMX)
 {
	case 2:  Encoder_TIM= (short)TIM2 -> CNT;   TIM2 -> CNT=0;  break;
	case 3:  Encoder_TIM= (short)TIM3 -> CNT;   TIM3 -> CNT=0;  break;
	case 4:  Encoder_TIM= (short)TIM4 -> CNT;   TIM4 -> CNT=0;  break;	
	case 5:  Encoder_TIM= (short)TIM5 -> CNT;   TIM5 -> CNT=0;  break;	
	default: Encoder_TIM=0;
 }
	return Encoder_TIM;
}

/**************************************************************************
Function: Tim2 interrupt service function
Input   : none
Output  : none
函数功能：TIM2中断服务函数
入口参数：无
返 回 值：无
**************************************************************************/
void TIM2_IRQHandler(void)
{ 		    		  			    
	if(TIM2->SR&0X0001) //Overflow interrupt //溢出中断
	{    				   				     	    	
	}				   
	TIM2->SR&=~(1<<0); //Clear the interrupt flag bit //清除中断标志位 	    
}
/**************************************************************************
Function: Tim3 interrupt service function
Input   : none
Output  : none
函数功能：TIM3中断服务函数
入口参数：无
返 回 值：无
**************************************************************************/
void TIM3_IRQHandler(void)
{ 		    		  			    
	if(TIM3->SR&0X0001) //Overflow interrupt //溢出中断
	{    				   				     	    	
	}				   
	TIM3->SR&=~(1<<0); //Clear the interrupt flag bit //清除中断标志位  	    
}
/**************************************************************************
Function: Tim4 interrupt service function
Input   : none
Output  : none
函数功能：TIM4中断服务函数
入口参数：无
返 回 值：无
**************************************************************************/
void TIM4_IRQHandler(void)
{ 		    		  			    
	if(TIM4->SR&0X0001) //Overflow interrupt //溢出中断
	{    				   				     	    	
	}				   
	TIM4->SR&=~(1<<0); //Clear the interrupt flag bit //清除中断标志位  	    
}

/**************************************************************************
Function: Tim5 interrupt service function
Input   : none
Output  : none
函数功能：TIM5中断服务函数
入口参数：无
返 回 值：无
**************************************************************************/
void TIM5_IRQHandler(void)
{ 		    		  			    
	if(TIM5->SR&0X0001) //Overflow interrupt //溢出中断
	{    				   				     	    	
	}				   
	TIM5->SR&=~(1<<0); //Clear the interrupt flag bit //清除中断标志位  	    
}
