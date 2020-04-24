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
* @brief :该文件用于管理采集器所辖用户的参数/状态数据
* 
* 
* 
*
* @author :许伟
* @date :2017/8/29 14:51
***************************************************************
*/ 
#define _USERPARA_C_
#include "UserPara.h"







/*
	系统用户列表初始化
	用于系统上电后从Flash更新到内存区域
*/
HAL_StatusTypeDef SysUserList_Init(void)
{
	HAL_StatusTypeDef Errstate =HAL_OK;

	Errstate = ReadData_SPIFlash(SysUserList_Addr,(INT8U*)&SysUserList,sizeof(SysUserList_Stru));
	return Errstate;
}
 



 /*
	系统用户列表更新
	用于当系统参数发生变化后 将内存数据更新至存储器
*/
HAL_StatusTypeDef SysUserList_Update(void)
{
	HAL_StatusTypeDef Errstate =HAL_OK;

	Errstate = WriteData_SPIFlash(SysUserList_Addr,(INT8U*)&SysUserList,sizeof(SysUserList_Stru));
	return Errstate;
}



 /*
	系统用户列表默认设置
	将系统参数回复默认设置，并且更新至存储器
*/
HAL_StatusTypeDef SysUserList_Reset(void)
{
	HAL_StatusTypeDef Errstate =HAL_OK;

	for( INT16U i=0;i<MAXUser_Num;i++)
	{
		SysUserList.User[i].User_ID=0;
		SysUserList.User[i].Reserved=0;
		SysUserList.User[i].Buld =0;
		SysUserList.User[i].Unit=0;
		SysUserList.User[i].Floor=0;
		SysUserList.User[i].Cell=0;
		SysUserList.User[i].CellArea=0;
		SysUserList.User[i].BuildMeter_ID=0;
	}
	Errstate = SysUserList_Update();
	return Errstate;
	
}






/*

函数功能:从存储器读取单一用户数据
*/
HAL_StatusTypeDef UserData_Read(INT16U ListNum,UserData_Stru* Value)
{
	HAL_StatusTypeDef ErrFlg =HAL_OK;
	INT16U Mem_Addr =ListNum*(sizeof(UserData_Stru))+UserData_Addr;   //存储器地址运算
	INT16U Data_Size =sizeof(UserData_Stru);//用户参数数据传递
	UserData_Stru Data;
	
	if(ListNum>MAXUser_Num)
	{
		ErrFlg =HAL_ERROR;
		return ErrFlg;
	}
	if(ReadData_FRAM(Mem_Addr,(INT8U*)&Data,Data_Size) ==0)
	{
		memcpy((INT8U*)Value,  (INT8U*)&Data,Data_Size);//将参数数据传递给参数指针
		ErrFlg =HAL_OK;
	}
	else
	{
		ErrFlg =HAL_ERROR;
	}
	return ErrFlg;

}



/*
函数功能:向存储器写入单一用户的数据

*/

HAL_StatusTypeDef UserData_Update(INT16U ListNum,UserData_Stru* Value)
{
	HAL_StatusTypeDef ErrFlg =HAL_OK;		//错误标志声明
	INT16U Mem_Addr =ListNum*(sizeof(UserData_Stru))+UserData_Addr;   //存储器地址运算
	INT16U Data_Size =sizeof(UserData_Stru);//用户参数数据传递

	if(ListNum>MAXUser_Num)
	{
		ErrFlg =HAL_ERROR;
		return ErrFlg;
	}
	if(WriteData_FRAM(Mem_Addr, (INT8U*)Value, Data_Size)==0)//写入参数数据
	{
		ErrFlg =HAL_OK;
	}
	else
	{
		ErrFlg =HAL_ERROR;
	}
	return ErrFlg;
}


/*

	函数功能将内存数据更新到存储器 
	在更新之前请保证内存数据的正确
*/
HAL_StatusTypeDef UserData_Save(INT16U ListNum)
{
	HAL_StatusTypeDef ErrFlg =HAL_OK;		//错误标志声明

	UserData_Stru UserPara_WriteBuf;
	if (ListNum>MAXUser_Num)
	{
		ErrFlg =HAL_ERROR;
		return ErrFlg;
	}
	UserPara_WriteBuf =UserData[ListNum];
	ErrFlg =UserData_Update( ListNum,&UserPara_WriteBuf);
	return ErrFlg;
}






/*
函数名称:UserDara_InitALL(INT16U UserNum)
函数功能:对系统参数进行上电初始化 (从存储器的指定位置读取参数,并将数据填充入用户数据)
参数:空
返回值:  正常0X00;其他值  异常
*/
HAL_StatusTypeDef UserData_InitALL(INT16U UserNum)
{
	HAL_StatusTypeDef ErrFlg =HAL_OK;
	UserData_Stru UserDataB;

	if (UserNum>MAXUser_Num)
	{
		ErrFlg =HAL_ERROR;
		return ErrFlg;
	}
	for (INT16U i =0; i<UserNum;i++)
	{
		ErrFlg=UserData_Read(i,&UserDataB);
		if (ErrFlg ==HAL_OK )
		{
			UserData[i] =UserDataB;
		}
		else
		{
			ErrFlg =HAL_ERROR;
			break;
		}
	}
	return ErrFlg;
	
}





/*
函数功能:将用户数据回复出厂设置
*/
HAL_StatusTypeDef UserData_ResetALL(INT16U UserNum)
{
	HAL_StatusTypeDef ErrFlg =HAL_OK;
	UserData_Stru DataBuffer;
	
	
	DataBuffer.Remain_Heat =0;		//剩余热量
	DataBuffer.Total_Heat =0;		//用户购入热量
	DataBuffer.Apportion_Energy =0;	//分摊热量 /当前表底
	DataBuffer.Total_Time =0;		//开阀时间
	
	for(INT16U i =0; i<UserNum;i++)
	{
		DataBuffer =UserData[i] =DataBuffer;
		ErrFlg=UserData_Update(i,&DataBuffer);
		
		if ( ErrFlg==HAL_OK)
		{
			continue;
		}
		else
		{
			ErrFlg =HAL_ERROR;
		}
	}
	
	return ErrFlg;
	
}




/*
	根据用户的ID 获取用户列表下标
*/
HAL_StatusTypeDef GetUser_Num(INT32U ID,INT16U* Num)
{
	for( INT16U A=0;A<MAXUser_Num;A++)
	{

		if(SysUserList.User[A].User_ID ==ID)
		{
			*Num =A;
			return HAL_OK;
		}
	}
	
	return HAL_ERROR;
	
}








/* END */
/*
 @copy COPYRIGHT 2016 Foryon     
*/
 




 
