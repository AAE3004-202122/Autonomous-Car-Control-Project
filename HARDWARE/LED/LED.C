#include "led.h"

int Led_Count; //LED flicker time control //LED闪烁时间控制

/**************************************************************************
Function: LED interface initialization
Input   : none
Output  : none
函数功能：LED接口初始化
入口参数：无 
返回  值：无
**************************************************************************/
void LED_Init(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOE, ENABLE); //Enable port clock //使能端口时钟
	
	GPIO_InitStructure.GPIO_Pin = LED_PIN; //Port configuration //端口配置
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;	//Push-pull output //推挽输出
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;	//50M
	GPIO_Init(LED_PORT, &GPIO_InitStructure);	//Initialize GPIO with the specified parameters //根据设定参数初始化GPIO
	GPIO_SetBits(LED_PORT,LED_PIN);
}
/**************************************************************************
Function: Buzzer interface initialized
Input   : none
Output  : none
函数功能：蜂鸣器接口初始化
入口参数：无 
返回  值：无
**************************************************************************/
void Buzzer_Init(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE); //Enable port clock //使能端口时钟
	
	GPIO_InitStructure.GPIO_Pin = Buzzer_PIN;	//Port configuration //端口配置
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;	//Push-pull output //推挽输出
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz; //50M
	GPIO_Init(Buzzer_PORT, &GPIO_InitStructure);	//Initialize GPIO with the specified parameters //根据设定参数初始化GPIO
	GPIO_ResetBits(Buzzer_PORT,Buzzer_PIN);
}
/**************************************************************************
Function: LED light flashing task
Input   : none
Output  : none
函数功能：LED灯闪烁任务
入口参数：无 
返回  值：无
**************************************************************************/
void led_task(void *pvParameters)
{
    while(1)
    {
			//The status of the LED is reversed. 0 is on and 1 is off
			//LED状态取反，0是点亮，1是熄灭    
      LED=~LED;              
      //The LED flicker task is very simple, requires low frequency accuracy, and uses the relative delay function	
      //LED闪烁任务非常简单，对频率精度要求低，使用相对延时函数			
      vTaskDelay(Led_Count); 
    }
}  

/**************************************************************************
Function: The LED flashing
Input   : none
Output  : blink time
函数功能：LED闪烁
入口参数：闪烁时间
返 回 值：无
**************************************************************************/
void Led_Flash(u16 time)
{
	  static int temp;
	  if(0==time) LED=0;
	  else		if(++temp==time)	LED=~LED,temp=0;
}

