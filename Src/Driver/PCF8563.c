/*  
***************************************************************
*****************Tools Version 20161020************************
* @copy  COPYRIGHT 2016 Foryon*******************************  
*
* @file :
* @version :
* @function :
* 
* 
* 
* 
* 
* 
* @brief :
* 
* 
* 
*
* @author :许伟
* @date :2017/8/25 10:45
***************************************************************
*/ 
#define _PCF8563_C_
#include "PCF8563.h"
 







/*********************************************************************************************************
** Function name:     PCF8563_Set
** Descriptions:        设置PCF8563时间
** input parameters:    NONE
** Output parameters:   NONE
** Returned value:      NONE
*********************************************************************************************************/


HAL_StatusTypeDef PCF8563_Set_DEV(RealClock_Str* RealTime)
{
	HAL_StatusTypeDef ErrFlg =HAL_OK;
	INT8U temp[7];
	INT8U year;
	INT8U i;
	
	//数据有效性判断
    if((RealTime->Second >= 60) || (RealTime->Minute >= 60) || (RealTime->Hour >= 24) || (RealTime->Day > 31) || (RealTime->Week > 7) || (RealTime->Month > 12) )
    {
        return HAL_ERROR;
    }
    
    temp[0] = HexToBcd(RealTime->Second);
    temp[1] = HexToBcd(RealTime->Minute);
    temp[2] = HexToBcd(RealTime->Hour);
    temp[3] = HexToBcd(RealTime->Day);
    temp[4] = HexToBcd(RealTime->Week);
    temp[5] = HexToBcd(RealTime->Month);
	if (RealTime->Year >= 2000)
	{
		temp[5] |= 0x80;
		year = RealTime->Year -2000;
		temp[6] = HexToBcd(year);
	}
	else
	{
		year = RealTime->Year -1900;
		temp[6] = HexToBcd(year);
	}

	i = 0;
	ErrFlg = HAL_ERROR;
	//				    句柄  设备地址		寄存器地址	地址长度			数据指针	   数据长度 溢出时间
	if(HAL_I2C_Mem_Write(&hi2c2, PCF8563_ID<<1 , CON1ADD,   PCF8563_MEMADD_SIZE , &i,		1 , 	 1000) ==HAL_OK)
	{
		//				    句柄  设备地址		寄存器地址	地址长度			数据指针	   数据长度 溢出时间
		if(HAL_I2C_Mem_Write(&hi2c2, PCF8563_ID<<1 , CON2ADD,   PCF8563_MEMADD_SIZE , &i,		1 , 	 1000) ==HAL_OK)
		{				
			//				    句柄  设备地址		寄存器地址	地址长度			数据指针	   数据长度 溢出时间
			if(HAL_I2C_Mem_Write(&hi2c2, PCF8563_ID<<1 , SECADD,   PCF8563_MEMADD_SIZE , temp,		7 , 	 1000) ==HAL_OK)
			{
				ErrFlg =HAL_OK;
			}
		}
	}
    return ErrFlg;
    
}




HAL_StatusTypeDef PCF8563_Set(RealClock_Str*RealTime)
{

	getTimeTick(&RTC_TimeTicks,RealTime);
	return PCF8563_Set_DEV(RealTime);
}


/*********************************************************************************************************
** Function name:       PCF8563_Read
** Descriptions:        读取PCF8563硬件时钟
** input parameters:    struct REALCLOCK* DATA:    指向时间结构体的指针
** Output parameters:   正确或者错误标志
** 功能描述：如果读取成功则软时钟更新，读取失败软时钟年份为1000
*********************************************************************************************************/
HAL_StatusTypeDef PCF8563_Read_DEV(RealClock_Str* RealTime)
{
    RealClock_Str clock;
    
    INT8U temp[7];
    INT8U i=0;

    for(i = 0; i < 7; i++)
    {
            temp[i] = 0;
    }
    temp[0] = 0x02;

	//			 	句柄  设备地址	       存储地址   地址长度               数据指针      数据长度	溢出时间
	if(HAL_I2C_Mem_Read(&hi2c2, PCF8563_ID<<1 , SECADD,   PCF8563_MEMADD_SIZE , temp,       7 ,      1000) ==HAL_OK)
	{
	    clock.Second = BcdToHex((temp[0]&0x7F));
	    clock.Minute = BcdToHex((temp[1]&0x7F));
	    clock.Hour = BcdToHex((temp[2]&0x3F));
	    clock.Day = BcdToHex((temp[3]&0x3F));
	    clock.Week = BcdToHex((temp[4]&0x07));
	    clock.Month = BcdToHex((temp[5]&0x1F));
	    clock.Year  = BcdToHex(temp[6])+2000;
    	if((clock.Second < 60) && (clock.Minute < 60) && (clock.Hour < 24) && (clock.Day <= 31) && (clock.Month <= 12) && (clock.Day != 0) && (clock.Month != 0))
	    {
			RealTime->Second =clock.Second;
			RealTime->Minute =clock.Minute;
			RealTime->Hour =clock.Hour;
			RealTime->Day =clock.Day;
			RealTime->Week =clock.Week;
			RealTime->Month =clock.Month;
			RealTime->Year = clock.Year;
	    }
    	else
    	{
			//RealTime->Year =1000;
			return HAL_ERROR;
		}
    }
	else
	{
		//RealTime->Year =1000;
		return HAL_ERROR;
	}
	return HAL_OK;
}





HAL_StatusTypeDef PCF8563_Read(RealClock_Str* RealTime)
{

	HAL_StatusTypeDef ErrFlg =HAL_OK;
	ErrFlg =PCF8563_Read_DEV(RealTime);
	if( ErrFlg ==HAL_OK)
	{
		getTimeTick(&RTC_TimeTicks,RealTime);
	}
	return ErrFlg;
	
}







 
/* END */
/*
 @copy COPYRIGHT 2016 Foryon     
*/
 




 
