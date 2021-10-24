#include "adc.h"

float Voltage,Voltage_Count,Voltage_All; //Variables related to battery voltage sampling //电池电压采样相关的变量  
const float Revise=1.03;

/**************************************************************************
Function: ADC initializes battery voltage detection
Input   : none
Output  : none
函数功能：ADC初始化电池电压检测
入口参数：无
返回  值：无
**************************************************************************/
void  Adc_Init(void)
{    
 	ADC_InitTypeDef ADC_InitStructure; 
	GPIO_InitTypeDef GPIO_InitStructure;
	
	//Enable ADC1 channel clock
	//使能ADC1通道时钟
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC |RCC_APB2Periph_ADC1	, ENABLE );	 
	//Set ADC frequency dividing factor 6 72M/6=12, and the maximum ADC time shall not exceed 14M
  //设置ADC分频因子6 72M/6=12,ADC最大时间不能超过14M	
	RCC_ADCCLKConfig(RCC_PCLK2_Div6);   

	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_4;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AIN; //Power supply voltage analog input pin //电源电压模拟输入引脚
	GPIO_Init(GPIOC, &GPIO_InitStructure);	
	
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AIN;	//Potentiometer analog input pin, used to switch car model //电位器模拟输入引脚，用于切换小车型号
	GPIO_Init(GPIOB, &GPIO_InitStructure);

	//Reset ADC1. Reset all registers of peripheral ADC1 to their default values
	//复位ADC1,将外设 ADC1 的全部寄存器重设为缺省值
	ADC_DeInit(ADC1); 
  //ADC working mode :ADC1 and ADC2 work in standalone mode	
	//ADC工作模式:ADC1和ADC2工作在独立模式
	ADC_InitStructure.ADC_Mode = ADC_Mode_Independent;	
	//The analog-to-digital conversion works in single-channel mode
	//模数转换工作在单通道模式
	ADC_InitStructure.ADC_ScanConvMode = DISABLE;	
	//A to D conversion works in single conversion mode
	//模数转换工作在单次转换模式
	ADC_InitStructure.ADC_ContinuousConvMode = DISABLE;	
	//The transformation is initiated by software rather than an external trigger
	//转换由软件而不是外部触发启动
	ADC_InitStructure.ADC_ExternalTrigConv = ADC_ExternalTrigConv_None;	
	//Right aligned ADC data
	//ADC数据右对齐
	ADC_InitStructure.ADC_DataAlign = ADC_DataAlign_Right;
	//The number of ADC channels that are sequentially converted to a rule
  //顺序进行规则转换的ADC通道的数目	
	ADC_InitStructure.ADC_NbrOfChannel = 1;	
	//Initialize the external ADCX register according to the parameters specified in ADC_INITSTRUCT
	//根据ADC_InitStruct中指定的参数初始化外设ADCx的寄存器   
	ADC_Init(ADC1, &ADC_InitStructure);	
	//Enable the specified ADC1
	//使能指定的ADC1
	ADC_Cmd(ADC1, ENABLE);
	//Enable reset calibration
  //使能复位校准 	
	ADC_ResetCalibration(ADC1);	 
  //Wait for the reset calibration to finish	
	//等待复位校准结束
	while(ADC_GetResetCalibrationStatus(ADC1));	
	//Enable AD calibration
  //开启AD校准	
	ADC_StartCalibration(ADC1);
	//Wait for the calibration to finish
  //等待校准结束	
	while(ADC_GetCalibrationStatus(ADC1));	 
}		
/**************************************************************************
Function: The AD sampling
Input   : The ADC channels
Output  : AD conversion results
函数功能：AD采样
入口参数：ADC的通道
返回  值：AD转换结果
**************************************************************************/
u16 Get_Adc(u8 ch)   
{
	//Sets the specified ADC rule group channel, one sequence, and sampling time
	//设置指定ADC的规则组通道，一个序列，采样时间
	
	//ADC1,ADC通道,采样时间为239.5周期
	//ADC1,ADC通道,采样时间为239.5周期
	ADC_RegularChannelConfig(ADC1, ch, 1, ADC_SampleTime_239Cycles5 );
  //Enable the specified ADC1 software transformation startup function	
  //使能指定的ADC1的软件转换启动功能	
	ADC_SoftwareStartConvCmd(ADC1, ENABLE);	
	//Wait for the conversion to finish
  //等待转换结束	
	while(!ADC_GetFlagStatus(ADC1, ADC_FLAG_EOC ));
	//Returns the result of the last ADC1 rule group conversion
	//返回最近一次ADC1规则组的转换结果
	return ADC_GetConversionValue(ADC1);	
}

/**************************************************************************
Function: Collect multiple ADC values to calculate the average function
Input   : ADC channels and collection times
Output  : AD conversion results
函数功能：采集多次ADC值求平均值函数
入口参数：ADC通道和采集次数
返 回 值：AD转换结果
**************************************************************************/
u16 Get_adc_Average(u8 chn, u8 times)
{
  u32 temp_val=0;
	u8 t;
	for(t=0;t<times;t++)
	{
		temp_val+=Get_Adc(chn);
		delay_ms(5);
	}
	return temp_val/times;
}

/**************************************************************************
Function: Read the battery voltage
Input   : none
Output  : Battery voltage in mV
函数功能：读取电池电压 
入口参数：无
返回  值：电池电压，单位mv
**************************************************************************/
float Get_battery_volt(void)   
{  
	float Volt;
	
	//The resistance partial voltage can be obtained by simple analysis according to the schematic diagram
	//电阻分压，具体根据原理图简单分析可以得到	
	Volt=Get_Adc(Battery_Ch)*3.3*11.0*Revise/1.0/4096;	
	return Volt;
}




