#include "timer.h"

//Input the capture flag for channel 1, 
//the capture flag for the higher bits, and the overflow flag for the lower 6 bits
//通道1输入捕获标志，高两位做捕获标志，低6位做溢出标志		
u8 TIM1CH1_CAPTURE_STA = 0;	
u16 TIM1CH1_CAPTURE_UPVAL;
u16 TIM1CH1_CAPTURE_DOWNVAL;

//Input the capture flag for channel 2, 
//the capture flag for the higher bits, and the overflow flag for the lower 6 bits
//通道2输入捕获标志，高两位做捕获标志，低6位做溢出标志	
u8 TIM1CH2_CAPTURE_STA = 0;		
u16 TIM1CH2_CAPTURE_UPVAL;
u16 TIM1CH2_CAPTURE_DOWNVAL;

//Input the capture flag for channel 3, 
//the capture flag for the higher bits, and the overflow flag for the lower 6 bits
//通道3输入捕获标志，高两位做捕获标志，低6位做溢出标志	
u8 TIM1CH3_CAPTURE_STA = 0;		
u16 TIM1CH3_CAPTURE_UPVAL;
u16 TIM1CH3_CAPTURE_DOWNVAL;

//Input the capture flag for channel 4, 
//the capture flag for the higher bits, and the overflow flag for the lower 6 bits
//通道4输入捕获标志，高两位做捕获标志，低6位做溢出标志
u8 TIM1CH4_CAPTURE_STA = 0;			
u16 TIM1CH4_CAPTURE_UPVAL;
u16 TIM1CH4_CAPTURE_DOWNVAL;

u32 TIM1_T1;
u32 TIM1_T2;
u32 TIM1_T3;
u32 TIM1_T4;

//Variables related to remote control acquisition of model aircraft
//航模遥控采集相关变量
int Remoter_Ch1=1500,Remoter_Ch2=1500,Remoter_Ch3=1500,Remoter_Ch4=1500;
//Model aircraft remote control receiver variable
//航模遥控接收变量
int L_Remoter_Ch1=1500,L_Remoter_Ch2=1500,L_Remoter_Ch3=1500,L_Remoter_Ch4=1500;  

/**************************************************************************
Function: Model aircraft remote control initialization function, timer 1 input capture initialization
Input   : arr: Automatic reload value, psc: clock preset frequency
Output  : none
函数功能：航模遥控初始化函数，定时器1输入捕获初始化
入口参数：arr：自动重装值，psc：时钟预分频数 
返 回 值：无
**************************************************************************/ 
void TIM1_Cap_Init(u16 arr, u16 psc)
{
	GPIO_InitTypeDef GPIO_InitStructure;
	TIM_TimeBaseInitTypeDef TIM_TimeBaseStructure;
	NVIC_InitTypeDef NVIC_InitStructure;
	TIM_ICInitTypeDef TIM_ICInitStructure;
	
	//Enable the AFIO clock  //使能AFIO时钟
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO, ENABLE);
	//Enable timer 1 //使能定时器1
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_TIM1, ENABLE); 
  //Enable GPIO peripheral clock //使能GPIO外设时钟	
 	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOE, ENABLE);
  //Pin remapping //引脚重映射	
	GPIO_PinRemapConfig(GPIO_FullRemap_TIM1,ENABLE);
		
	//Port configuration //端口配置
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_9 | GPIO_Pin_11 | GPIO_Pin_13 | GPIO_Pin_14;  
	//The drop-down input //下拉输入
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPD;      
	GPIO_Init(GPIOE, &GPIO_InitStructure);

	/*** Initialize timer 1 || 初始化定时器1 ***/
	//Set the counter to automatically reload //设定计数器自动重装值 
	TIM_TimeBaseStructure.TIM_Period = arr; 
	//Pre-divider //预分频器 
	TIM_TimeBaseStructure.TIM_Prescaler = psc; 	
	//Set the clock split: TDTS = Tck_tim //设置时钟分割:TDTS = Tck_tim
	TIM_TimeBaseStructure.TIM_ClockDivision = TIM_CKD_DIV1; 
	//TIM up count mode //TIM向上计数模式	
	TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up; 
	//Initializes the timebase unit for TIMX based on the parameter specified in TIM_TimeBaseInitStruct
	//根据TIM_TimeBaseInitStruct中指定的参数初始化TIMx的时间基数单位
	TIM_TimeBaseInit(TIM1, &TIM_TimeBaseStructure); 

	/*** 初始化TIM1输入捕获参数，通道1 || Initialize TIM1 for the capture parameter, channel 1 ***/
	//Select input //选择输入端 
	TIM_ICInitStructure.TIM_Channel = TIM_Channel_1; 
  //Rising edge capture //上升沿捕获
	TIM_ICInitStructure.TIM_ICPolarity = TIM_ICPolarity_Rising;	
	TIM_ICInitStructure.TIM_ICSelection = TIM_ICSelection_DirectTI; 
	//Configure input frequency division, regardless of frequency //配置输入分频,不分频 
	TIM_ICInitStructure.TIM_ICPrescaler = TIM_ICPSC_DIV1;	
  //IC1F=0000 Configure input filter, do not filter //配置输入滤波器，不滤波  
	TIM_ICInitStructure.TIM_ICFilter = 0x0F;	  
	TIM_ICInit(TIM1, &TIM_ICInitStructure);

	/*** 初始化TIM1输入捕获参数，通道2 || Initialize TIM1 for the capture parameter, channel 2 ***/
	//CC1S=01 Select input //选择输入端 
	TIM_ICInitStructure.TIM_Channel = TIM_Channel_2;
	//Rising edge capture //上升沿捕获
	TIM_ICInitStructure.TIM_ICPolarity = TIM_ICPolarity_Rising;	
	TIM_ICInitStructure.TIM_ICSelection = TIM_ICSelection_DirectTI; 
	//Configure input frequency division, regardless of frequency //配置输入分频,不分频 
	TIM_ICInitStructure.TIM_ICPrescaler = TIM_ICPSC_DIV1;	  
	TIM_ICInitStructure.TIM_ICFilter = 0x00;	  //IC1F=0000 配置输入滤波器 不滤波
	TIM_ICInit(TIM1, &TIM_ICInitStructure);

	/*** 初始化TIM1输入捕获参数，通道3 || Initialize TIM1 for the capture parameter, channel 3 ***/
	//Select input //选择输入端 
	TIM_ICInitStructure.TIM_Channel = TIM_Channel_3;   
	//Rising edge capture //上升沿捕获
	TIM_ICInitStructure.TIM_ICPolarity = TIM_ICPolarity_Rising;
	TIM_ICInitStructure.TIM_ICSelection = TIM_ICSelection_DirectTI; 
	//Configure input frequency division, regardless of frequency //配置输入分频,不分频 
	TIM_ICInitStructure.TIM_ICPrescaler = TIM_ICPSC_DIV1;	  
	//IC1F=0000 Configure input filter, do not filter //配置输入滤波器，不滤波  
	TIM_ICInitStructure.TIM_ICFilter = 0x00;	  
	TIM_ICInit(TIM1, &TIM_ICInitStructure);

	/*** 初始化TIM1输入捕获参数，通道4 || Initialize TIM1 for the capture parameter, channel 4 ***/
	//Select input //选择输入端 
	TIM_ICInitStructure.TIM_Channel = TIM_Channel_4; 
	//Rising edge capture //上升沿捕获
	TIM_ICInitStructure.TIM_ICPolarity = TIM_ICPolarity_Rising;	
	TIM_ICInitStructure.TIM_ICSelection = TIM_ICSelection_DirectTI; 
	//Configure input frequency division, regardless of frequency //配置输入分频,不分频 
	TIM_ICInitStructure.TIM_ICPrescaler = TIM_ICPSC_DIV1;	   
	//IC1F=0000 Configure input filter, do not filter //配置输入滤波器，不滤波  
	TIM_ICInitStructure.TIM_ICFilter = 0x00;	  
	TIM_ICInit(TIM1, &TIM_ICInitStructure);

  /*** interrupt packet initialization || 中断分组初始化 ***/
  //TIM1 interrupts //TIM1中断
	NVIC_InitStructure.NVIC_IRQChannel = TIM1_CC_IRQn; 
  //Preempt priority 0 //先占优先级0级	
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;  
	//Level 0 from priority //从优先级0级
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0; 
	//IRQ channels are enabled //IRQ通道被使能
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE; 
	//Initializes the peripheral NVIC register according to the parameters specified in NVIC_InitStruct
	//根据NVIC_InitStruct中指定的参数初始化外设NVIC寄存器 
	NVIC_Init(&NVIC_InitStructure);   
	
  //Allow CC1IE,CC2IE,CC3IE,CC4IE to catch interrupts, not allowed update_interrupts
  //不允许更新中断，允许CC1IE,CC2IE,CC3IE,CC4IE捕获中断	
	TIM_ITConfig(TIM1, TIM_IT_CC1|TIM_IT_CC2|TIM_IT_CC3|TIM_IT_CC4,	ENABLE);   
	//Advanced timer output must be enabled //高级定时器输出必须使能这句	
	TIM_CtrlPWMOutputs(TIM1,ENABLE); 	
	//Enable timer //使能定时器
	TIM_Cmd(TIM1, ENABLE); 		
}
/**************************************************************************
Function: Model aircraft remote control receiving interrupt, namely timer 1 input capture interrupt
Input   : none
Output  : none
函数功能：航模遥控接收中断，即定时器1输入捕获中断
入口参数：无
返 回 值：无
**************************************************************************/ 
void TIM1_CC_IRQHandler(void)
{
	//连接航模遥遥控器后，需要推下前进杆，才可以正式航模控制小车
	//After connecting the remote controller of the model aircraft, 
	//you need to push down the forward lever to officially control the car of the model aircraft
  if(Remoter_Ch2>1600&&Remote_ON_Flag==0&&Deviation_Count>=CONTROL_DELAY)
  {
		//Model aircraft remote control mark position 1, other marks position 0
		//航模遥控标志位置1，其它标志位置0
		Remote_ON_Flag=1;
	  APP_ON_Flag=0;
		PS2_ON_Flag=0;
		CAN_ON_Flag=0;
		Usart_ON_Flag=0; 
	}
	 
	//Channel 1 //通道一
	if ((TIM1CH1_CAPTURE_STA & 0X80) == 0) 			
	{
		if (TIM_GetITStatus(TIM1, TIM_IT_CC1) != RESET) //A capture event occurred on channel 1 //通道1发生捕获事件
		{
			TIM_ClearITPendingBit(TIM1, TIM_IT_CC1); //Clear the interrupt flag bit //清除中断标志位
			if (TIM1CH1_CAPTURE_STA & 0X40)	//A falling edge is caught //捕获到一个下降沿
			{
				TIM1CH1_CAPTURE_DOWNVAL = TIM_GetCapture1(TIM1); //Record the timer value at this point //记录下此时的定时器计数值
				if (TIM1CH1_CAPTURE_DOWNVAL < TIM1CH1_CAPTURE_UPVAL)
				{
					TIM1_T1 = 9999;
				}
				else
					TIM1_T1 = 0;
				Remoter_Ch1 = TIM1CH1_CAPTURE_DOWNVAL - TIM1CH1_CAPTURE_UPVAL + TIM1_T1;	//Time to get the total high level //得到总的高电平的时间
				if(abs(Remoter_Ch1-L_Remoter_Ch1)>500) Remoter_Ch1=L_Remoter_Ch1; //Filter //滤波
					 L_Remoter_Ch1=Remoter_Ch1;
				
				TIM1CH1_CAPTURE_STA = 0; //Capture flag bit to zero	//捕获标志位清零
				TIM_OC1PolarityConfig(TIM1, TIM_ICPolarity_Rising); //Set to rising edge capture //设置为上升沿捕获		  
			}
			else 
			{
				//When the capture time occurs but not the falling edge, the first time the rising edge is captured, record the timer value at this time
				//发生捕获时间但不是下降沿，第一次捕获到上升沿，记录此时的定时器计数值
				TIM1CH1_CAPTURE_UPVAL = TIM_GetCapture1(TIM1); //Obtain rising edge data //获取上升沿数据
				TIM1CH1_CAPTURE_STA |= 0X40; //The flag has been caught on the rising edge //标记已捕获到上升沿
				TIM_OC1PolarityConfig(TIM1, TIM_ICPolarity_Falling); //Set to Falling Edge Capture //设置为下降沿捕获
			}
		}
	}
  //Channel 2 //通道二
	if ((TIM1CH2_CAPTURE_STA & 0X80) == 0)		
	{
		if (TIM_GetITStatus(TIM1, TIM_IT_CC2) != RESET)	//A capture event occurred on channel 2 //通道2发生捕获事件
		{
			TIM_ClearITPendingBit(TIM1, TIM_IT_CC2); //Clear the interrupt flag bit //清除中断标志位
			if (TIM1CH2_CAPTURE_STA & 0X40)	//A falling edge is caught //捕获到一个下降沿
			{
				TIM1CH2_CAPTURE_DOWNVAL = TIM_GetCapture2(TIM1); //Record the timer value at this point //记录下此时的定时器计数值
				if (TIM1CH2_CAPTURE_DOWNVAL < TIM1CH2_CAPTURE_UPVAL)
				{
					TIM1_T2 = 9999;
				}
				else
					TIM1_T2 = 0;
				Remoter_Ch2 = TIM1CH2_CAPTURE_DOWNVAL - TIM1CH2_CAPTURE_UPVAL + TIM1_T2; //Time to get the total high level //得到总的高电平的时间
				if(abs(Remoter_Ch2-L_Remoter_Ch2)>500)Remoter_Ch2=L_Remoter_Ch2; //Filter //滤波
				L_Remoter_Ch2=Remoter_Ch2;
				
				TIM1CH2_CAPTURE_STA = 0; //Capture flag bit to zero	//捕获标志位清零
				TIM_OC2PolarityConfig(TIM1, TIM_ICPolarity_Rising); //Set to rising edge capture //设置为上升沿捕获		  
			}
			else 
			{
				//When the capture time occurs but not the falling edge, the first time the rising edge is captured, record the timer value at this time
				//发生捕获时间但不是下降沿，第一次捕获到上升沿，记录此时的定时器计数值
				TIM1CH2_CAPTURE_UPVAL = TIM_GetCapture2(TIM1); //Obtain rising edge data //获取上升沿数据
				TIM1CH2_CAPTURE_STA |= 0X40; //The flag has been caught on the rising edge //标记已捕获到上升沿
				TIM_OC2PolarityConfig(TIM1, TIM_ICPolarity_Falling); //Set to Falling Edge Capture //设置为下降沿捕获
			}
		}
	}
  //Channel 3 //通道三
	if ((TIM1CH3_CAPTURE_STA & 0X80) == 0)			
	{
		if (TIM_GetITStatus(TIM1, TIM_IT_CC3) != RESET)	//A capture event occurred on channel 3 //通道3发生捕获事件
		{
			TIM_ClearITPendingBit(TIM1, TIM_IT_CC3); //Clear the interrupt flag bit //清除中断标志位
			if (TIM1CH3_CAPTURE_STA & 0X40)	//A falling edge is caught //捕获到一个下降沿
			{
				TIM1CH3_CAPTURE_DOWNVAL = TIM_GetCapture3(TIM1); //Record the timer value at this point //记录下此时的定时器计数值
				if (TIM1CH3_CAPTURE_DOWNVAL < TIM1CH3_CAPTURE_UPVAL)
				{
					TIM1_T3 = 9999;
				}
				else
					TIM1_T3 = 0;
				Remoter_Ch3 = TIM1CH3_CAPTURE_DOWNVAL - TIM1CH3_CAPTURE_UPVAL + TIM1_T3; //Time to get the total high level //得到总的高电平的时间
				if(abs(Remoter_Ch3-L_Remoter_Ch3)>500)Remoter_Ch3=L_Remoter_Ch3; //Filter //滤波
									L_Remoter_Ch3=Remoter_Ch3;
				TIM1CH3_CAPTURE_STA = 0; //Capture flag bit to zero	//捕获标志位清零
				TIM_OC3PolarityConfig(TIM1, TIM_ICPolarity_Rising); //Set to rising edge capture //设置为上升沿捕获		  
			}
			else 
			{
				//When the capture time occurs but not the falling edge, the first time the rising edge is captured, record the timer value at this time
				//发生捕获时间但不是下降沿，第一次捕获到上升沿，记录此时的定时器计数值
				TIM1CH3_CAPTURE_UPVAL = TIM_GetCapture3(TIM1); //Obtain rising edge data //获取上升沿数据
				TIM1CH3_CAPTURE_STA |= 0X40; //The flag has been caught on the rising edge //标记已捕获到上升沿
				TIM_OC3PolarityConfig(TIM1, TIM_ICPolarity_Falling); //Set to Falling Edge Capture //设置为下降沿捕获
			}
		}
	}
	
	if(Car_Mode!=Akm_Car) //Ackerman car uses channel 4 of timer 1 as the PWM output control Servo //阿克曼小车把定时器1的通道4用作了PWM输出控制舵机
	{
		//Channel 4 //通道四
		if ((TIM1CH4_CAPTURE_STA & 0X80) == 0)		
		{
			if (TIM_GetITStatus(TIM1, TIM_IT_CC4) != RESET)	//A capture event occurred on channel 4 //通道4发生捕获事件
			{
				TIM_ClearITPendingBit(TIM1, TIM_IT_CC4); //Clear the interrupt flag bit //清除中断标志位
				if (TIM1CH4_CAPTURE_STA & 0X40)	//A falling edge is caught //捕获到一个下降沿
				{
					TIM1CH4_CAPTURE_DOWNVAL = TIM_GetCapture4(TIM1); //Record the timer value at this point //记录下此时的定时器计数值
					if (TIM1CH4_CAPTURE_DOWNVAL < TIM1CH4_CAPTURE_UPVAL)
					{
						TIM1_T4 = 9999;
					}
					else
						TIM1_T4 = 0;
					Remoter_Ch4 = TIM1CH4_CAPTURE_DOWNVAL - TIM1CH4_CAPTURE_UPVAL + TIM1_T4; //Time to get the total high level //得到总的高电平的时间
					if(abs(Remoter_Ch4-L_Remoter_Ch4)>500)Remoter_Ch4=L_Remoter_Ch4; //Filter //滤波
					L_Remoter_Ch4=Remoter_Ch4;				
					TIM1CH4_CAPTURE_STA = 0; //Capture flag bit to zero	//捕获标志位清零
					TIM_OC4PolarityConfig(TIM1, TIM_ICPolarity_Rising); //Set to rising edge capture //设置为上升沿捕获		  
				}
				else 
				{
					//When the capture time occurs but not the falling edge, the first time the rising edge is captured, record the timer value at this time
				  //发生捕获时间但不是下降沿，第一次捕获到上升沿，记录此时的定时器计数值
					TIM1CH4_CAPTURE_UPVAL = TIM_GetCapture4(TIM1); //Obtain rising edge data //获取上升沿数据
					TIM1CH4_CAPTURE_STA |= 0X40; //The flag has been caught on the rising edge //标记已捕获到上升沿
					TIM_OC4PolarityConfig(TIM1, TIM_ICPolarity_Falling); //Set to Falling Edge Capture //设置为下降沿捕获
				}
			}
		}
  }
}
/**************************************************************************
Function: TIM1 Update Interrupt
Input   : none
Output  : none
函数功能：定时器1更新中断
入口参数：无
返回  值：无 
**************************************************************************/
void TIM1_UP_IRQHandler(void) 
{ 
	//Clear the interrupt flag bit
	//清除中断标志位 
  TIM1->SR&=~(1<<0);	    
}

