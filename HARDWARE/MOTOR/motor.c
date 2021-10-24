#include "motor.h"

/**************************************************************************
Function: Motor orientation pin initialization
Input   : none
Output  : none
函数功能：电机方向引脚初始化
入口参数：无
返回  值：无
**************************************************************************/
void MiniBalance_Motor_Init(void)
{
  GPIO_InitTypeDef GPIO_InitStructure;
	
	//Enable port clock //使能端口时钟
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE); 
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC, ENABLE);
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOE, ENABLE);

	//Port configuration //端口配置
	GPIO_InitStructure.GPIO_Pin = IN1_PIN_A;
  //Push-pull output //推挽输出	
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;	
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;	//50M
	//Initialize GPIO with the specified parameters   //根据设定参数初始化GPIO
	GPIO_Init(IN1_PORTA, &GPIO_InitStructure);			
	
	//Port configuration //端口配置
	GPIO_InitStructure.GPIO_Pin = IN2_PIN_A;		
	//Push-pull output //推挽输出	
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;	
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;	//50M
	//Initialize GPIO with the specified parameters   //根据设定参数初始化GPIO
	GPIO_Init(IN2_PORTA, &GPIO_InitStructure);		
	
	//Port configuration //端口配置
	GPIO_InitStructure.GPIO_Pin = IN1_PIN_B;	
	//Push-pull output //推挽输出	
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;	//50M
	//Initialize GPIO with the specified parameters   //根据设定参数初始化GPIO
	GPIO_Init(IN1_PORTB, &GPIO_InitStructure);	
	
	//Port configuration //端口配置
	GPIO_InitStructure.GPIO_Pin = IN2_PIN_B;	
	//Push-pull output //推挽输出	
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;	//50M
	//Initialize GPIO with the specified parameters   //根据设定参数初始化GPIO
	GPIO_Init(IN2_PORTB, &GPIO_InitStructure);		
	
	//Port configuration //端口配置
	GPIO_InitStructure.GPIO_Pin = IN1_PIN_C;
	//Push-pull output //推挽输出	
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;	
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;	//50M
	//Initialize GPIO with the specified parameters   //根据设定参数初始化GPIO
	GPIO_Init(IN1_PORTC, &GPIO_InitStructure);		
	
	//Port configuration //端口配置
	GPIO_InitStructure.GPIO_Pin = IN2_PIN_C;	
	//Push-pull output //推挽输出	
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;	
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;	//50M
	//Initialize GPIO with the specified parameters   //根据设定参数初始化GPIO
	GPIO_Init(IN2_PORTC, &GPIO_InitStructure);		
	
	//Port configuration //端口配置
	GPIO_InitStructure.GPIO_Pin = IN1_PIN_D;		
	//Push-pull output //推挽输出	
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;	//50M
	//Initialize GPIO with the specified parameters   //根据设定参数初始化GPIO
	GPIO_Init(IN1_PORTD, &GPIO_InitStructure);		
	
	//Port configuration //端口配置
	GPIO_InitStructure.GPIO_Pin = IN2_PIN_D;	
	//Push-pull output //推挽输出	
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;	//50M
	//Initialize GPIO with the specified parameters   //根据设定参数初始化GPIO
	GPIO_Init(IN2_PORTD, &GPIO_InitStructure);		

  //IO output 0to prevent motor transfer
  //IO输出0，防止电机乱转
	GPIO_ResetBits(IN1_PORTA,IN1_PIN_A);	
	GPIO_ResetBits(IN2_PORTA,IN2_PIN_A);
	GPIO_ResetBits(IN1_PORTB,IN1_PIN_B);
	GPIO_ResetBits(IN2_PORTB,IN2_PIN_B);
	GPIO_ResetBits(IN1_PORTC,IN1_PIN_C);
	GPIO_ResetBits(IN2_PORTC,IN2_PIN_C);
	GPIO_ResetBits(IN1_PORTD,IN1_PIN_D);
	GPIO_ResetBits(IN2_PORTD,IN2_PIN_D);
}
/**************************************************************************
Function: The motor PWM initialization
Input   : arr: Automatic reload value, psc: clock preset frequency
Output  : none
函数功能：电机PWM引脚初始化
入口参数：arr：自动重装值  psc：时钟预分频数 
返回  值：无
**************************************************************************/
void MiniBalance_PWM_Init(u16 arr,u16 psc)
{		 					 
	GPIO_InitTypeDef GPIO_InitStructure;
	TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;
	TIM_OCInitTypeDef  TIM_OCInitStructure;
	
	//Enable timer 8 //使能定时器8 
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_TIM8, ENABLE);  
	//Enable GPIO peripheral clock //使能GPIO外设时钟
 	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC, ENABLE); 
	
	//Port configuration //端口配置
	GPIO_InitStructure.GPIO_Pin = PWM_PIN_A;
  //Reuse push-pull output //复用推挽输出  
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;      
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz; //50M
	//Initialize GPIO with the specified parameters   //根据设定参数初始化GPIO
	GPIO_Init(PWM_PORTA, &GPIO_InitStructure);
	
	//Port configuration //端口配置
	GPIO_InitStructure.GPIO_Pin = PWM_PIN_B;  
	//Reuse push-pull output //复用推挽输出  
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;      
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz; //50M
	//Initialize GPIO with the specified parameters   //根据设定参数初始化GPIO
	GPIO_Init(PWM_PORTB, &GPIO_InitStructure);
	
	//Port configuration //端口配置
	GPIO_InitStructure.GPIO_Pin = PWM_PIN_C; 
	//Reuse push-pull output //复用推挽输出  
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;      
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz; //50M
	//Initialize GPIO with the specified parameters   //根据设定参数初始化GPIO
	GPIO_Init(PWM_PORTC, &GPIO_InitStructure);
	
	//Port configuration //端口配置
	GPIO_InitStructure.GPIO_Pin = PWM_PIN_D;  
	//Reuse push-pull output //复用推挽输出  
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;      
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz; //50M
	//Initialize GPIO with the specified parameters   //根据设定参数初始化GPIO
	GPIO_Init(PWM_PORTD, &GPIO_InitStructure);
	
	//Sets the value of the auto-reload register cycle for the next update event load activity
	//设置在下一个更新事件装入活动的自动重装载寄存器周期的值	 
	TIM_TimeBaseStructure.TIM_Period = arr; 
	//Sets the pre-divider value used as the TIMX clock frequency divisor
	//设置用来作为TIMx时钟频率除数的预分频值
	TIM_TimeBaseStructure.TIM_Prescaler =psc; 
	//Set the clock split :TDTS = Tck_tim
	//设置时钟分割:TDTS = Tck_tim
	TIM_TimeBaseStructure.TIM_ClockDivision = 1; 
	//Up counting mode 
	//向上计数模式  
	TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;  
	//Initializes the timebase unit for TIMX based on the parameter specified in TIM_TIMEBASEINITSTRUCT
	//根据TIM_TimeBaseInitStruct中指定的参数初始化TIMx的时间基数单位
	TIM_TimeBaseInit(TIM8, &TIM_TimeBaseStructure); 

  //Select Timer mode :TIM Pulse Width Modulation mode 1
  //选择定时器模式:TIM脉冲宽度调制模式1
 	TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM1; 
	//Compare output enablement
	//比较输出使能
	TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable; 
	//Set the pulse value of the capture comparison register to be loaded
	//设置待装入捕获比较寄存器的脉冲值
	TIM_OCInitStructure.TIM_Pulse = 0; 
  //Output polarity :TIM output polarity is higher	
  //输出极性:TIM输出比较极性高	
	TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_High;     
	TIM_OCInitStructure.TIM_OCNIdleState = TIM_OCNIdleState_Set;
	//Initialize the peripheral TIMX based on the parameter specified in TIM_OCINITSTRUCT
  //根据TIM_OCInitStruct中指定的参数初始化外设TIMx	
	TIM_OC1Init(TIM8, &TIM_OCInitStructure);  
	//CH1 is pre-loaded and enabled
	//CH1预装载使能	 
	TIM_OC1PreloadConfig(TIM8, TIM_OCPreload_Enable);  
	
	//Select Timer mode :TIM Pulse Width Modulation mode 1
  //选择定时器模式:TIM脉冲宽度调制模式1
	TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM1;
	//Compare output enablement
	//比较输出使能
	TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable;
  //Set the pulse value of the capture comparison register to be loaded
	//设置待装入捕获比较寄存器的脉冲值	
	TIM_OCInitStructure.TIM_Pulse = 0;       
  //Output polarity :TIM output polarity is higher	
  //输出极性:TIM输出比较极性高		
	TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_High;    
	TIM_OCInitStructure.TIM_OCNIdleState = TIM_OCNIdleState_Set; 
	//Initialize the peripheral TIMX based on the parameter specified in TIM_OCINITSTRUCT
  //根据TIM_OCInitStruct中指定的参数初始化外设TIMx	
	TIM_OC2Init(TIM8, &TIM_OCInitStructure); 
	//CH2 is pre-loaded and enabled
	//CH2预装载使能	
	TIM_OC2PreloadConfig(TIM8, TIM_OCPreload_Enable);  
	
	//Select Timer mode :TIM Pulse Width Modulation mode 1
  //选择定时器模式:TIM脉冲宽度调制模式1
	TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM1; 
	//Compare output enablement
	//比较输出使能
	TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable; 
	//Set the pulse value of the capture comparison register to be loaded
	//设置待装入捕获比较寄存器的脉冲值	
	TIM_OCInitStructure.TIM_Pulse = 0;       
  //Output polarity :TIM output polarity is higher	
  //输出极性:TIM输出比较极性高		
	TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_High;    
	TIM_OCInitStructure.TIM_OCNIdleState = TIM_OCNIdleState_Set; 
	//Initialize the peripheral TIMX based on the parameter specified in TIM_OCINITSTRUCT
  //根据TIM_OCInitStruct中指定的参数初始化外设TIMx
	TIM_OC3Init(TIM8, &TIM_OCInitStructure);
  //CH3 is pre-loaded and enabled
	//CH3预装载使能	  
	TIM_OC3PreloadConfig(TIM8, TIM_OCPreload_Enable); 
	
	//Select Timer mode :TIM Pulse Width Modulation mode 1
  //选择定时器模式:TIM脉冲宽度调制模式1
	TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM1;
	//Compare output enablement
	//比较输出使能
	TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable; 
	//Set the pulse value of the capture comparison register to be loaded
	//设置待装入捕获比较寄存器的脉冲值	
	TIM_OCInitStructure.TIM_Pulse = 0;  
  //Output polarity :TIM output polarity is higher	
  //输出极性:TIM输出比较极性高		
	TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_High;     
	TIM_OCInitStructure.TIM_OCNIdleState = TIM_OCNIdleState_Set; 
	//Initialize the peripheral TIMX based on the parameter specified in TIM_OCINITSTRUCT
  //根据TIM_OCInitStruct中指定的参数初始化外设TIMx
	TIM_OC4Init(TIM8, &TIM_OCInitStructure);  
	//CH4 is pre-loaded and enabled
	//CH4预装载使能	
	TIM_OC4PreloadConfig(TIM8, TIM_OCPreload_Enable);	

  // Enable the TIMX preloaded register on the ARR
  //使能TIMx在ARR上的预装载寄存器	
	TIM_ARRPreloadConfig(TIM8, ENABLE); 
	
	//Enable TIM8
	//使能TIM8
	TIM_Cmd(TIM8, ENABLE);  
	
	// Advanced timer output must be enabled
	//高级定时器输出必须使能这句		
	TIM_CtrlPWMOutputs(TIM8,ENABLE); 
} 

/**************************************************************************
Function: Enable switch pin initialization
Input   : none
Output  : none
函数功能：使能开关引脚初始化
入口参数：无
返回  值：无 
**************************************************************************/
void Enable_Pin(void)
{
  GPIO_InitTypeDef GPIO_InitStructure;
	
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOE, ENABLE); //Enable port clock  //使能端口时钟
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0;             //Port configuration //端口配置
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;         //Pull up input      //上拉输入
  GPIO_Init(GPIOE, &GPIO_InitStructure);					      //Initialize GPIO with the specified parameters //根据设定参数初始化GPIO
} 

/**************************************************************************
Function: Model aircraft three channel remote control pin and steering gear PWM pin initialization
Input   : ARR: Automatic reload value  PSC: clock preset frequency
Output  : none
函数功能：航模三通道遥控引脚与舵机PWM引脚初始化
入口参数：arr：自动重装值  psc：时钟预分频数 
返回  值：无
**************************************************************************/
void Servo_PWM_Init(u16 arr,u16 psc)	
{ 
	GPIO_InitTypeDef GPIO_InitStructure;
	TIM_TimeBaseInitTypeDef TIM_TimeBaseStructure;
	NVIC_InitTypeDef NVIC_InitStructure;
	TIM_ICInitTypeDef TIM_ICInitStructure;
	TIM_OCInitTypeDef  TIM_OCInitStructure;

	//Enable reuse //启用复用功能
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO, ENABLE);
	//Pin remapping //引脚重映射
	GPIO_PinRemapConfig(GPIO_FullRemap_TIM1,ENABLE);
	//Enable timer 1 //使能定时器1
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_TIM1, ENABLE); 
  //Enable GPIO peripheral clock //使能GPIO外设时钟	
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOE, ENABLE); 

	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_9 | GPIO_Pin_11 | GPIO_Pin_13; //Port configuration //端口配置
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPD; //Pull-down input //下拉输入     
	GPIO_Init(GPIOE, &GPIO_InitStructure);

	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_14; //Port configuration //端口配置
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;   //Reuse push-pull output //复用推挽输出
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz; //50M
	GPIO_Init(GPIOE, &GPIO_InitStructure);

  /***Initialize timer TIM1***/
	/***初始化定时器 TIM1***/
	//Set the counter to automatically reload //设定计数器自动重装值 
	TIM_TimeBaseStructure.TIM_Period = arr;
	//Pre-divider //预分频器 
	TIM_TimeBaseStructure.TIM_Prescaler = psc;
  //Set the clock split :TDTS = Tck_tim //设置时钟分割:TDTS = Tck_tim	
	TIM_TimeBaseStructure.TIM_ClockDivision = TIM_CKD_DIV1;
  //TIM up count mode //TIM向上计数模式	
	TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;  
	//Initializes the timebase unit for TIMX based on the parameter specified in TIM_TIMEBASEINITSTRUCT
	//根据TIM_TimeBaseInitStruct中指定的参数初始化TIMx的时间基数单位
	TIM_TimeBaseInit(TIM1, &TIM_TimeBaseStructure); 

  /*** initializes TIM1 input capture parameter, channel 1 ***/
	/*** 初始化TIM1输入捕获参数，通道1 *************************/
	//CC1S=01 Select input port
	//CC1S=01   选择输入端 
	TIM_ICInitStructure.TIM_Channel = TIM_Channel_1;
	//Rising edge capture
	//上升沿捕获
	TIM_ICInitStructure.TIM_ICPolarity = TIM_ICPolarity_Rising;  
	TIM_ICInitStructure.TIM_ICSelection = TIM_ICSelection_DirectTI;
	//Configure input frequency division, regardless of frequency
  //配置输入分频,不分频 	
	TIM_ICInitStructure.TIM_ICPrescaler = TIM_ICPSC_DIV1; 
	//IC1F=0000 configuration input filter is not filtered
  //IC1F=0000 配置输入滤波器 不滤波	
	TIM_ICInitStructure.TIM_ICFilter = 0x11;    
	TIM_ICInit(TIM1, &TIM_ICInitStructure);

  /*** initializes TIM1 input capture parameter, channel 2 ***/
	/*** 初始化TIM1输入捕获参数，通道2 *************************/
	//CC1S=01 Select input port
	//CC1S=01   选择输入端
	TIM_ICInitStructure.TIM_Channel = TIM_Channel_2;  
	//Rising edge capture
	//上升沿捕获
	TIM_ICInitStructure.TIM_ICPolarity = TIM_ICPolarity_Rising; 
	TIM_ICInitStructure.TIM_ICSelection = TIM_ICSelection_DirectTI; 
	//Configure input frequency division, regardless of frequency
  //配置输入分频,不分频 
	TIM_ICInitStructure.TIM_ICPrescaler = TIM_ICPSC_DIV1;
	//IC1F=0000 configuration input filter is not filtered
  //IC1F=0000 配置输入滤波器 不滤波	
	TIM_ICInitStructure.TIM_ICFilter = 0x11;   
	TIM_ICInit(TIM1, &TIM_ICInitStructure);

  /*** initializes TIM1 input capture parameter, channel 3 ***/
	/*** 初始化TIM1输入捕获参数，通道3 *************************/
	//CC1S=01 Select input port
	//CC1S=01   选择输入端
	TIM_ICInitStructure.TIM_Channel = TIM_Channel_3; 
	//Rising edge capture
	//上升沿捕获
	TIM_ICInitStructure.TIM_ICPolarity = TIM_ICPolarity_Rising;  
	TIM_ICInitStructure.TIM_ICSelection = TIM_ICSelection_DirectTI; 
	//Configure input frequency division, regardless of frequency
  //配置输入分频,不分频 
	TIM_ICInitStructure.TIM_ICPrescaler = TIM_ICPSC_DIV1;  
	//IC1F=0000 configuration input filter is not filtered
  //IC1F=0000 配置输入滤波器 不滤波	
	TIM_ICInitStructure.TIM_ICFilter = 0x00;   
	TIM_ICInit(TIM1, &TIM_ICInitStructure);

  //  /*** initializes TIM1 input capture parameter, channel 4(Ackerman trolleys do not initialize channel 4 for input capture) ***/
	//  /*** 初始化TIM1输入捕获参数，通道4(阿克曼小车不初始化通道4为输入捕获) ************************************************/
	//  //CC1S=01 Select input port
	//  //CC1S=01   选择输入端
	//  TIM_ICInitStructure.TIM_Channel = TIM_Channel_4;
	//  //Rising edge capture
	//  //上升沿捕获
	//  TIM_ICInitStructure.TIM_ICPolarity = TIM_ICPolarity_Rising; 
	//  TIM_ICInitStructure.TIM_ICSelection = TIM_ICSelection_DirectTI; 、
	//  //Configure input frequency division, regardless of frequency
  //  //配置输入分频,不分频 
	//  TIM_ICInitStructure.TIM_ICPrescaler = TIM_ICPSC_DIV1;   
	//  //IC1F=0000 configuration input filter is not filtered
  //  //IC1F=0000 配置输入滤波器 不滤波	
	//  TIM_ICInitStructure.TIM_ICFilter = 0x11;  
	//  TIM_ICInit(TIM1, &TIM_ICInitStructure); 
  
	/*** Ackerman trolleys do not initialize channel 4 for PWM output ***/
	/*** 阿克曼小车不初始化通道4为PWM输出 ***/
	//Select Timer mode :TIM Pulse Width Modulation mode 1
	//选择定时器模式:TIM脉冲宽度调制模式1
	TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM1; 
	//Compare output enablement
	//比较输出使能
	TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable; 
	//Set the pulse value of the capture comparison register to be loaded
	//设置待装入捕获比较寄存器的脉冲值
	TIM_OCInitStructure.TIM_Pulse = 0;  
	//Output polarity :TIM output polarity is higher
  //输出极性:TIM输出比较极性高	
	TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_High;     
	TIM_OCInitStructure.TIM_OCNIdleState = TIM_OCNIdleState_Set; 
	//Initialize the peripheral TIMX based on the parameter specified in TIM_OCINITSTRUCT
	//根据TIM_OCInitStruct中指定的参数初始化外设TIMx
	TIM_OC4Init(TIM1, &TIM_OCInitStructure); 
	//CH4 is pre-loaded to enable
  //CH4预装载使能  	
	TIM_OC4PreloadConfig(TIM1, TIM_OCPreload_Enable);  

  //  //TIM1 interrupts //TIM1中断
	//  NVIC_InitStructure.NVIC_IRQChannel = TIM1_UP_IRQn;
  //  //Preempt priority 0 //先占优先级0级  
	//  NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;  
	//  //Level 0 from priority //从优先级0级
	//  NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;  
	//  //The IRQ channel is enabled //IRQ通道被使能
	//  NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE; 
	//  //Initialize the peripheral NVIC register according to the parameters specified in NVIC_INITSTRUCT
	//  //根据NVIC_InitStruct中指定的参数初始化外设NVIC寄存器 
	//  NVIC_Init(&NVIC_InitStructure);   

	/*** //Interrupt packet initialization //中断分组初始化 ***/
	//Tim1 input captures interrupts //TIM1输入捕获中断
	NVIC_InitStructure.NVIC_IRQChannel = TIM1_CC_IRQn;  
	//Preempt priority 0 //先占优先级0级
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 1;  
	//Level 0 from priority //从优先级0级
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;  
	//The IRQ channel is enabled //IRQ通道被使能
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE; 
	//Initialize the peripheral NVIC register according to the parameters specified in NVIC_INITSTRUCT 
	//根据NVIC_InitStruct中指定的参数初始化外设NVIC寄存器
	NVIC_Init(&NVIC_InitStructure);   

  //Allow CC1IE,CC2IE,CC3IE,CC4IE to catch interrupts
  //不允许更新中断，允许CC1IE,CC2IE,CC3IE,CC4IE捕获中断
	TIM_ITConfig(TIM1, TIM_IT_CC1|TIM_IT_CC2|TIM_IT_CC3,  ENABLE);    
	// Advanced timer output must be enabled
  //高级定时器输出必须使能这句 	
	TIM_CtrlPWMOutputs(TIM1,ENABLE);   
	//Enable timer
  //使能定时器	
	TIM_Cmd(TIM1, ENABLE);     
}

