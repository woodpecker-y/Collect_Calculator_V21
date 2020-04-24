/*  
***************************************************************
*****************Tools Version 20161020************************
* @copy  COPYRIGHT 2016 Foryon  
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
* @brief :该文件用于管理采集器所辖用户的参数/状态/数据

* 
* 
* 
*
* @author :许伟
* @date :2017/8/29 14:51
***************************************************************
*/ 
#ifndef _USERPARA_H_
#define _USERPARA_H_
 


#include "TypeDef.h"
#include "PubDef.h"
#include "W25QXX.H"
#include "FRAM.H"




 
#ifdef _USERPARA_C_
#define USERPARA_EXT
#else
#define USERPARA_EXT extern
#endif






/*用户参数结构
存储于Flash
*/
#pragma pack(1)				//字节对齐模式 节省存储空间
typedef struct
{
	INT32U	User_ID;			//用户ID用于上位机下发的主键编码
	INT32U	Reserved;			//采集器识别的用户主键(一般是用户地址)
	
	INT8U	Buld;				//楼栋号					1
	INT8U	Unit;				//单元号					1
	INT8U	Floor;				//楼层号					1
	INT8U	Cell;				//房间号					1

	INT16U	CellArea;			//房间面积
	INT32U	BuildMeter_ID;		//所属楼栋表ID
}SysUserPara_Stru;


typedef struct
{
	SysUserPara_Stru User[MAXUser_Num];
	INT16U	CRC16;		//校验值
	
}SysUserList_Stru;
#pragma pack()		//字节对齐结束


USERPARA_EXT SysUserList_Stru SysUserList;		//系统用户列表





/* 用户数据@状态 结构
存储于FRAM
*/
#pragma pack(1)		//字节对齐模式 节省存储空间
typedef struct
{
						
	INT32S	Remain_Heat; 		//剩余热量
	INT32U	Total_Heat; 		//用户购入热量	   目前用于用户分摊的控制标志2017年12月22日
	INT32U	Apportion_Energy;	//当前(分摊)热量	//热量表表底
	INT32U	Total_Time; 		//分摊时间便于进行热量的分摊计算
	INT16U	CRC16;			    //数据校验
	
}UserData_Stru;
#pragma pack()		            //字节对齐结束
USERPARA_EXT UserData_Stru UserData[MAXUser_Num];	//用户数据列表








 
 


#ifdef _USERPARA_C_



#endif





HAL_StatusTypeDef SysUserList_Init(void);
HAL_StatusTypeDef SysUserList_Update(void);
HAL_StatusTypeDef SysUserList_Reset(void);




HAL_StatusTypeDef UserData_Read(INT16U ListNum,UserData_Stru* Value);
HAL_StatusTypeDef UserData_Update(INT16U ListNum,UserData_Stru* Value);
HAL_StatusTypeDef UserData_Save(INT16U ListNum);
HAL_StatusTypeDef UserData_InitALL(INT16U UserNum);
HAL_StatusTypeDef UserData_ResetALL(INT16U UserNum);

HAL_StatusTypeDef GetUser_Num(INT32U ID,INT16U* Num);






 
#endif
/* END */
/*  
 @copy COPYRIGHT 2016 Foryon     
*/  
 




 
