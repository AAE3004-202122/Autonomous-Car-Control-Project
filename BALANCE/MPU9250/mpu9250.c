#include "mpu9250.h"
#include "sys.h"
#include "delay.h"  

//Zero drift count
//零点漂移计数
int Deviation_Count;
//Triaxial IMU data
//三轴IMU数据
short gyro[3], accel[3],magnet[3];
// Gyro static error, raw data
//陀螺仪静差，原始数据
short Deviation_gyro[3],Original_gyro[3];    

/**************************************************************************
Function: MPU9250 task
Input   : none
Output  : none
函数功能：MPU9250任务
入口参数：无
返回  值：无
**************************************************************************/
void MPU9250_task(void *pvParameters)
{
    u32 lastWakeTime = getSysTickCnt();
    while(1)
    {	
			//This task runs at 100Hz
			//此任务以100Hz的频率运行
			vTaskDelayUntil(&lastWakeTime, F2T(RATE_100_HZ));	
			//Read the gyroscope zero before starting
      //开机前，读取陀螺仪零点			
		  if(Deviation_Count<CONTROL_DELAY)
		  {	
		  	Deviation_Count++;
			  memcpy(Deviation_gyro,gyro,sizeof(gyro));		
		  }		
			//Get acceleration sensor data //得到加速度传感器数据
			MPU_Get_Accelerometer(accel);	
			//Get gyroscope data           //得到陀螺仪数据
			MPU_Get_Gyroscope(gyro);
      //Get magnetometer data	       //得到磁力计数据	
			MPU_Get_Magnetometer(magnet);		  
    }
}  

/**************************************************************************
Function: Initialize MPU9250
Input   : none
Output  : 0: success, others: error code (Errors are usually caused by device addresses, or by misaligned IIC pins)
函数功能：初始化MPU9250
入口参数：无
返回  值：0:成功, 其他:错误代码 (错误一般都是器件地址引起的，或者IIC引脚不对等)
**************************************************************************/
u8 MPU9250_Init(void)
{
  u8 res=0;
  //IIC_Init();  //Initialize the IIC bus //初始化IIC总线
  MPU_Write_Byte(MPU9250_ADDR,MPU_PWR_MGMT1_REG,0X80); //Reset MPU9250 //复位MPU9250
  delay_ms(100); //Delay 100 ms //延时100ms
  MPU_Write_Byte(MPU9250_ADDR,MPU_PWR_MGMT1_REG,0X00); //Wake mpu9250 //唤醒MPU9250
	
  MPU_Set_Gyro_Fsr(1);  //Gyroscope sensor              //陀螺仪传感器,±500dps=±500°/s ±32768 (gyro/32768*500)*PI/180(rad/s)=gyro/3754.9(rad/s)
	MPU_Set_Accel_Fsr(0);	//Acceleration sensor           //加速度传感器,±2g=±2*9.8m/s^2 ±32768 accel/32768*19.6=accel/1671.84
  MPU_Set_Rate(50);			//Set the sampling rate to 50Hz //设置采样率50Hz

  MPU_Write_Byte(MPU9250_ADDR,MPU_INT_EN_REG,0X00);    //Turn off all interrupts //关闭所有中断
	MPU_Write_Byte(MPU9250_ADDR,MPU_USER_CTRL_REG,0X00); //The I2C main mode is off //I2C主模式关闭
	MPU_Write_Byte(MPU9250_ADDR,MPU_FIFO_EN_REG,0X00);	 //Close the FIFO //关闭FIFO
	//The INT pin is low, enabling bypass mode to read the magnetometer directly
	//INT引脚低电平有效，开启bypass模式，可以直接读取磁力计
	MPU_Write_Byte(MPU9250_ADDR,MPU_INTBP_CFG_REG,0X82); 
	//Read the ID of MPU9250 
	//读取MPU9250的ID
  res=MPU_Read_Byte(MPU9250_ADDR,MPU_DEVICE_ID_REG);   
  if(res==MPU6500_ID) //The device ID is correct, The correct device ID depends on the AD pin //器件ID正确, 器件ID的正确取决于AD引脚
    {
       MPU_Write_Byte(MPU9250_ADDR,MPU_PWR_MGMT1_REG,0X01); //Set CLKSEL,PLL X axis as reference //设置CLKSEL,PLL X轴为参考
       MPU_Write_Byte(MPU9250_ADDR,MPU_PWR_MGMT2_REG,0X00); //Acceleration and gyroscope both work //加速度与陀螺仪都工作
		   MPU_Set_Rate(50);						       	                //Set the sampling rate to 50Hz //设置采样率为50Hz   
    }
	else return 1;
 
  res=MPU_Read_Byte(AK8963_ADDR,MAG_WIA); //Read AK8963ID //读取AK8963ID   
  if(res==AK8963_ID)
    {
       MPU_Write_Byte(AK8963_ADDR,MAG_CNTL1,0X11); //Set AK8963 to single measurement mode //设置AK8963为单次测量模式
    }
	else return 1;

  return 0;
}
/**************************************************************************
Function: Set the full range of the MPU9250 gyroscope sensor
Input   : fsr:0,±250dps;1,±500dps;2,±1000dps;3,±2000dps
Output  : 0: Settings successful, others: Settings failed
函数功能：设置MPU9250陀螺仪传感器满量程范围
入口参数：fsr:0,±250dps;1,±500dps;2,±1000dps;3,±2000dps
返回  值：0:设置成功, 其他:设置失败
**************************************************************************/
u8 MPU_Set_Gyro_Fsr(u8 fsr)
{
	return MPU_Write_Byte(MPU9250_ADDR,MPU_GYRO_CFG_REG,fsr<<3); //Set the full scope of the gyroscope//设置陀螺仪满量程范围  
}
/**************************************************************************
Function: Initialize TIM2 as the encoder interface mode
Input   : fsr:0,±2g;1,±4g;2,±8g;3,±16g
Output  : 0: Settings successful, others: Settings failed
函数功能：设置MPU9250加速度传感器满量程范围
入口参数：fsr:0,±2g;1,±4g;2,±8g;3,±16g
返回  值：0:设置成功, 其他:设置失败
**************************************************************************/
u8 MPU_Set_Accel_Fsr(u8 fsr)
{
	return MPU_Write_Byte(MPU9250_ADDR,MPU_ACCEL_CFG_REG,fsr<<3); //Set the full range of the acceleration sensor//设置加速度传感器满量程范围  
}
/**************************************************************************
Function: Initialize TIM2 as the encoder interface mode
Input   : LPF: Digital low-pass filtering frequency (Hz)
Output  : 0: Settings successful, others: Settings failed
函数功能：设置MPU9250的数字低通滤波器
入口参数：lpf:数字低通滤波频率(Hz)
返回  值：0:设置成功, 其他:设置失败
**************************************************************************/
u8 MPU_Set_LPF(u16 lpf)
{
	u8 data=0;
	if(lpf>=188)data=1;
	else if(lpf>=98)data=2;
	else if(lpf>=42)data=3;
	else if(lpf>=20)data=4;
	else if(lpf>=10)data=5;
	else data=6; 
	return MPU_Write_Byte(MPU9250_ADDR,MPU_CFG_REG,data); //Set the digital lowpass filter//设置数字低通滤波器  
}
/**************************************************************************
Function: Initialize TIM2 as the encoder interface mode
Input   : rate:4~1000(Hz)
Output  : 0: Settings successful, others: Settings failed
函数功能：设置MPU9250的采样率(假定Fs=1KHz)
入口参数：rate:4~1000(Hz)
返回  值：0:设置成功, 其他:设置失败
**************************************************************************/
u8 MPU_Set_Rate(u16 rate)
{
	u8 data;
	if(rate>1000)rate=1000;
	if(rate<4)rate=4;
	data=1000/rate-1;
	data=MPU_Write_Byte(MPU9250_ADDR,MPU_SAMPLE_RATE_REG,data);	//Set the digital lowpass filter//设置数字低通滤波器  
 	return MPU_Set_LPF(rate/2);	//Automatically sets LPF to half of the sampling rate //自动设置LPF为采样率的一半
}
/**************************************************************************
Function: Initialize TIM2 as the encoder interface mode
Input   : none
Output  : 0: Settings successful, others: Settings failed
函数功能：获得温度值
入口参数：无
返回  值：温度值(扩大了100倍)
**************************************************************************/
short MPU_Get_Temperature(void)
{
    u8 buf[2]; 
    short raw;
	  float temp;
	  MPU_Read_Len(MPU9250_ADDR,MPU_TEMP_OUTH_REG,2,buf); 
    raw=((u16)buf[0]<<8)|buf[1];  
    temp=21+((double)raw)/333.87;  
    return temp*100;;
}
/**************************************************************************
Function: Initialize TIM2 as the encoder interface mode
Input   : Gx, Gy, Gz: raw readings (plus or minus) of the x,y, and z axes of the gyroscope
Output  : 0: success, others: error code
函数功能：获得陀螺仪值(原始值)
入口参数：gx,gy,gz:陀螺仪x,y,z轴的原始读数(带正负)
返回  值：0:成功, 其他:错误代码
**************************************************************************/
u8 MPU_Get_Gyroscope(short *gyro)
{
  u8 buf[6],res; 
	res=MPU_Read_Len(MPU9250_ADDR,MPU_GYRO_XOUTH_REG,6,buf);
	if(res==0)
	{
		if(Deviation_Count<CONTROL_DELAY) // 10 seconds before starting //开机前10秒
		{
			//Read the gyroscope zero //读取陀螺仪零点
			gyro[0] =(((u16)buf[0]<<8)|buf[1]);  
			gyro[1] =(((u16)buf[2]<<8)|buf[3]);  
			gyro[2]= (((u16)buf[4]<<8)|buf[5]);
			Led_Count=1; //LED high frequency flashing //LED高频闪烁
			Flag_Stop=1; //The software fails to flag location 1 //软件失能标志位置1		
		}
		else //10 seconds after starting //开机10秒后
		{  
			if(Deviation_Count==CONTROL_DELAY)
				Flag_Stop=0; //The software fails to flag location 0 //软件失能标志位置0
			Led_Count=300; //The LED returns to normal flicker frequency //LED恢复正常闪烁频率	
			
			//Save the raw data to update zero by clicking the user button
			//保存原始数据用于单击用户按键更新零点
			Original_gyro[0] =(((u16)buf[0]<<8)|buf[1]);  
			Original_gyro[1] =(((u16)buf[2]<<8)|buf[3]);  
			Original_gyro[2]= (((u16)buf[4]<<8)|buf[5]);			
			
			//Removes zero drift data
			//去除零点漂移的数据
			gyro[0] =Original_gyro[0]-Deviation_gyro[0];  
			gyro[1] =Original_gyro[1]-Deviation_gyro[1];  
			gyro[2]= Original_gyro[2]-Deviation_gyro[2];
		}
	} 	
  return res;;
}
/**************************************************************************
Function: Initialize TIM2 as the encoder interface mode
Input   : Ax, Ay, Az: The original reading of the accelerometer on the x,y, and z axes (plus or minus)
Output  : 0: success, others: error code
函数功能：得到加速度值(原始值)
入口参数：ax,ay,az:加速度计x,y,z轴的原始读数(带正负)
返回  值：0:成功, 其他:错误代码
**************************************************************************/
u8 MPU_Get_Accelerometer(short *accel)
{
    u8 buf[6],res;  
	res=MPU_Read_Len(MPU9250_ADDR,MPU_ACCEL_XOUTH_REG,6,buf);
	if(res==0)
{
		accel[0] =((u16)buf[0]<<8)|buf[1];  
		accel[1] =((u16)buf[2]<<8)|buf[3];  
		accel[2] =((u16)buf[4]<<8)|buf[5];
	} 	
    return res;
}
/**************************************************************************
Function: Initialize TIM2 as the encoder interface mode
Input   : Mx,my,mz: raw reading (plus or minus) of the x,y, and z axes of the magnetometer
Output  : 0: success, others: error code
函数功能：得到磁力计值(原始值)
入口参数：mx,my,mz:磁力计x,y,z轴的原始读数(带正负)
返回  值：0:成功, 其他:错误代码
**************************************************************************/
u8 MPU_Get_Magnetometer(short *magnet)
{
    u8 buf[6],res;  
	res=MPU_Read_Len(AK8963_ADDR,MAG_XOUT_L,6,buf);
	if(res==0)
	{
		magnet[0]=((u16)buf[1]<<8)|buf[0];  
		magnet[1]=((u16)buf[3]<<8)|buf[2];  
		magnet[2]=((u16)buf[5]<<8)|buf[4];
	} 	
	
	//The AK8963 needs to be reset to single measurement mode after each reading
	//AK8963每次读完以后都需要重新设置为单次测量模式
  MPU_Write_Byte(AK8963_ADDR,MAG_CNTL1,0X11);  
  return res;;
}
/**************************************************************************
Function: Initialize TIM2 as the encoder interface mode
Input   : Addr: device address, reg: register address, len: write length, buf: data area
Output  : 0: success, others: error code
函数功能：IIC连续写
入口参数：addr:器件地址, reg:寄存器地址, len:写入长度, buf:数据区
返回  值：0:成功, 其他:错误代码
**************************************************************************/
u8 MPU_Write_Len(u8 addr,u8 reg,u8 len,u8 *buf)
{
    u8 i;
    IIC_Start();
    IIC_Send_Byte((addr<<1)|0); //Send the device address + write the command //发送器件地址+写命令
    if(IIC_Wait_Ack())          //wait for an answer //等待应答
    {
        IIC_Stop();
        return 1;
    }
    IIC_Send_Byte(reg);         //Write the register address //写寄存器地址
    IIC_Wait_Ack();             //wait for an answer //等待应答
    for(i=0;i<len;i++)
    {
        IIC_Send_Byte(buf[i]);  //Send data //发送数据
        if(IIC_Wait_Ack())      //wait for an ACK //等待ACK
        {
            IIC_Stop();
            return 1;
        }
    }
    IIC_Stop();
    return 0;
} 
/**************************************************************************
Function: Initialize TIM2 as the encoder interface mode
Input   : Addr: device address, reg: register address to read, len: length to read, buf: data storage area to read
Output  : 0: success, others: error code
函数功能：IIC连续读
入口参数：addr:器件地址, reg:要读取的寄存器地址, len:要读取的长度, buf:读取到的数据存储区
返回  值：0:成功, 其他:错误代码
**************************************************************************/
u8 MPU_Read_Len(u8 addr,u8 reg,u8 len,u8 *buf)
{ 
    IIC_Start();
    IIC_Send_Byte((addr<<1)|0); //Send the device address + write the command //发送器件地址+写命令
    if(IIC_Wait_Ack())          //wait for an answer //等待应答
    {
        IIC_Stop();
        return 1;
    }
    IIC_Send_Byte(reg);         //Write the register address //写寄存器地址
    IIC_Wait_Ack();             //wait for an answer //等待应答
	  IIC_Start();                
    IIC_Send_Byte((addr<<1)|1); //Send the device address + write the command //发送器件地址+写命令
    IIC_Wait_Ack();             //wait for an answer //等待应答
    while(len)
    {
			if(len==1)*buf=IIC_Read_Byte(0); //Read data and send nACK //读数据,发送nACK 
			else *buf=IIC_Read_Byte(1);	   	 //Read the data and send the ACK //读数据,发送ACK  
			len--;
			buf++;  
    }
    IIC_Stop(); //Generates a stop condition //产生一个停止条件
    return 0;       
}
/**************************************************************************
Function: Initialize TIM2 as the encoder interface mode
Input   : Devaddr: device IIC address, reg: register address, data
Output  : 0: success, others: error code
函数功能：IIC写一个字节 
入口参数：devaddr:器件IIC地址, reg:寄存器地址, data:数据
返回  值：0:成功, 其他:错误代码
**************************************************************************/
u8 MPU_Write_Byte(u8 addr,u8 reg,u8 data)
{
    IIC_Start();
    IIC_Send_Byte((addr<<1)|0); //Send the device address + write the command //发送器件地址+写命令
    if(IIC_Wait_Ack())          //wait for an answer //等待应答
    {
        IIC_Stop();
        return 1;
    }
    IIC_Send_Byte(reg);         //Write the register address //写寄存器地址
    IIC_Wait_Ack();             //wait for an answer //等待应答
    IIC_Send_Byte(data);        //Send data //发送数据
    if(IIC_Wait_Ack())          //wait for an ACK //等待ACK
    {
        IIC_Stop();
        return 1;
    }
    IIC_Stop();
    return 0;
}
/**************************************************************************
Function: Initialize TIM2 as the encoder interface mode
Input   : Devaddr: device IIC address, reg: register address, data
Output  : The data read
函数功能：IIC读一个字节  
入口参数：devaddr:器件IIC地址, reg:寄存器地址, data:数据
返回  值：读到的数据
**************************************************************************/
u8 MPU_Read_Byte(u8 addr,u8 reg)
{
    u8 res;
    IIC_Start();
    IIC_Send_Byte((addr<<1)|0); //Send the device address + write the command //发送器件地址+写命令
    IIC_Wait_Ack();             //wait for an answer //等待应答
    IIC_Send_Byte(reg);         //Write the register address //写寄存器地址
    IIC_Wait_Ack();             //wait for an answer //等待应答
	  IIC_Start();                
    IIC_Send_Byte((addr<<1)|1); //Send device address + read command //发送器件地址+读命令
    IIC_Wait_Ack();             //wait for an answer //等待应答
    res=IIC_Read_Byte(0);		    //Read data and send nACK //读数据,发送nACK  
    IIC_Stop();                 //Generates a stop condition //产生一个停止条件
    return res;  
}

