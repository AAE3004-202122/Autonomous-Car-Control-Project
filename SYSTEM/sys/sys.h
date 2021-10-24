#ifndef __SYS_H
#define __SYS_H	
#include "stm32f10x.h"

//0,Does not support OS //0,不支持os
//1,support OS          //1,支持os
#define SYSTEM_SUPPORT_OS		1		//Define whether the system folder supports OS //定义系统文件夹是否支持OS

//Bit band operation to achieve 51 similar GPIO control function
//Refer to < / p > < p >;&lt;CM3 Authoritative Guide &gt;&gt;Chapter 5 (pp. 87 ~92).
//IO port operation macro definition
//位带操作,实现51类似的GPIO控制功能
//具体实现思想,参考<<CM3权威指南>>第五章(87页~92页).
//IO口操作宏定义
#define BITBAND(addr, bitnum) ((addr & 0xF0000000)+0x2000000+((addr &0xFFFFF)<<5)+(bitnum<<2)) 
#define MEM_ADDR(addr)  *((volatile unsigned long  *)(addr)) 
#define BIT_ADDR(addr, bitnum)   MEM_ADDR(BITBAND(addr, bitnum)) 

//IO port address mapping //IO口地址映射
#define GPIOA_ODR_Addr    (GPIOA_BASE+12) //0x4001080C 
#define GPIOB_ODR_Addr    (GPIOB_BASE+12) //0x40010C0C 
#define GPIOC_ODR_Addr    (GPIOC_BASE+12) //0x4001100C 
#define GPIOD_ODR_Addr    (GPIOD_BASE+12) //0x4001140C 
#define GPIOE_ODR_Addr    (GPIOE_BASE+12) //0x4001180C 
#define GPIOF_ODR_Addr    (GPIOF_BASE+12) //0x40011A0C    
#define GPIOG_ODR_Addr    (GPIOG_BASE+12) //0x40011E0C    

#define GPIOA_IDR_Addr    (GPIOA_BASE+8) //0x40010808 
#define GPIOB_IDR_Addr    (GPIOB_BASE+8) //0x40010C08 
#define GPIOC_IDR_Addr    (GPIOC_BASE+8) //0x40011008 
#define GPIOD_IDR_Addr    (GPIOD_BASE+8) //0x40011408 
#define GPIOE_IDR_Addr    (GPIOE_BASE+8) //0x40011808 
#define GPIOF_IDR_Addr    (GPIOF_BASE+8) //0x40011A08 
#define GPIOG_IDR_Addr    (GPIOG_BASE+8) //0x40011E08 
 
//IO port operation, only single IO port!
//make sure n is less than 16!
//IO口操作,只对单一的IO口!
//确保n的值小于16!
#define PAout(n)   BIT_ADDR(GPIOA_ODR_Addr,n)  //Output //输出 
#define PAin(n)    BIT_ADDR(GPIOA_IDR_Addr,n)  //Input  //输入 

#define PBout(n)   BIT_ADDR(GPIOB_ODR_Addr,n)  //Output //输出 
#define PBin(n)    BIT_ADDR(GPIOB_IDR_Addr,n)  //Input  //输入 

#define PCout(n)   BIT_ADDR(GPIOC_ODR_Addr,n)  //Output //输出 
#define PCin(n)    BIT_ADDR(GPIOC_IDR_Addr,n)  //Input  //输入 

#define PDout(n)   BIT_ADDR(GPIOD_ODR_Addr,n)  //Output //输出 
#define PDin(n)    BIT_ADDR(GPIOD_IDR_Addr,n)  //Input  //输入 

#define PEout(n)   BIT_ADDR(GPIOE_ODR_Addr,n)  //Output //输出 
#define PEin(n)    BIT_ADDR(GPIOE_IDR_Addr,n)  //Input  //输入

#define PFout(n)   BIT_ADDR(GPIOF_ODR_Addr,n)  //Output //输出 
#define PFin(n)    BIT_ADDR(GPIOF_IDR_Addr,n)  //Input  //输入

#define PGout(n)   BIT_ADDR(GPIOG_ODR_Addr,n)  //Output //输出 
#define PGin(n)    BIT_ADDR(GPIOG_IDR_Addr,n)  //Input  //输入

void Stm32_Clock_Init(u8 PLL); //Clock initialization //时钟初始化  
void Sys_Soft_Reset(void);     //System soft reset    //系统软复位
void Sys_Standby(void);        //Standby mode         //待机模式 	
void MY_NVIC_SetVectorTable(u32 NVIC_VectTab, u32 Offset); //Set the offset address //设置偏移地址
void MY_NVIC_PriorityGroupConfig(u8 NVIC_Group); //Set the NVIC grouping //设置NVIC分组
void MY_NVIC_Init(u8 NVIC_PreemptionPriority,u8 NVIC_SubPriority,u8 NVIC_Channel,u8 NVIC_Group); //Set interrupt //设置中断
void Ex_NVIC_Config(u8 GPIOx,u8 BITx,u8 TRIM); //External interrupt configuration function (gpioA ~G only) //外部中断配置函数(只对GPIOA~G)
void JTAG_Set(u8 mode);

//The following are assembler functions //以下为汇编函数
void WFI_SET(void);		   //Execute the WFI instruction //执行WFI指令
void INTX_DISABLE(void); //Turn off all interrupts //关闭所有中断
void INTX_ENABLE(void);	 //Enables all interrupts  //开启所有中断
void MSR_MSP(u32 addr);	 //Set the stack address   //设置堆栈地址

//JTAG mode setting definition
//JTAG模式设置定义
#define JTAG_SWD_DISABLE   0X02
#define SWD_ENABLE         0X01
#define JTAG_SWD_ENABLE    0X00	
void JTAG_Set(u8 mode);
#endif
