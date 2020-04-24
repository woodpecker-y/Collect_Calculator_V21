#include "PubDef.h"
#ifdef Valve_NWK_ENABLE

#ifndef _NWKMODBUS_H
#define _NWKMODBUS_H
#include "main.h"
#include "UART_RBC.h"

 
#ifdef _DDF2PRO_C_
#define NWK_EXT
#else
#define NWK_EXT extern
#endif
 

#define NWKPro_PackSize				UART_TO_NWKPackSize_S
#define NWKPro_HeadSize				11				    //数据包头大小
#define NWKPro_StartCode			0X68				//起始符
#define NWKPro_ProtocolCode		0X41				//版本号
#define NWKPro_EndCode				0X16				//结束符



#pragma pack(1)		//字节对齐
typedef struct
{

	INT8U	Addr;		//起始字符		1字节
	INT8U	CMD;		//协议类型		1字节
}NWK_Head_Stru;
#pragma pack()			//字节对齐


//NWK通信协议 数据抄收 下行
#pragma pack(1)			//字节对齐
typedef struct
{
	NWK_Head_Stru  Head;                    //01 03
	
	INT8U	Register_Addr_H;				//寄存器地址高字节 00
	INT8U	Register_Addr_L;				//寄存器地址低字节 00
	
	INT8U	Register_Num_H;					//寄存器数量高字节 00
	INT8U	Register_Num_L;					//寄存器数量高字节 1C = 28(D)
	
	INT8U	CRC16_H;						//CRC高字节 44
	INT8U	CRC16_L;                        //CRC低字节 03
}NWK_Pack_Stru;						//实时数据


typedef union
{
//	INT8U Data[DDF2Pro_PackSize];
//	struct
//	{
//      DDF2Pro_Head_Stru  Head;
//		INT8U	Available[DDF2Pro_PackSize-DDF2Pro_HeadSize];//有效数据
//	}DefaultPack;


	NWK_Pack_Stru Pack;
	
}NWK_Pack_Uni;


typedef union
{
    NWK_Pack_Stru Pack;
}NWK_Send_Uni;


#pragma pack()			       //字节对齐结束




 
 


#ifdef _NWKmodbus_C_

INT8U NWK_Pack_RxAnalyze_S(UART_RBC_Stru* Ctrl_Point,INT8U DataSize);
INT8U NWK_Pack_Rx_S(UART_RBC_Stru* Ctrl_Point,INT8U Protocol);

#endif
 


NWK_EXT void NWK_Pack_RxServer_S( UART_RBC_Stru* Ctrl_Point );
NWK_EXT INT8U NWK_Pack_TxServer_S(UART_RBC_Stru* Ctrl_Point);


 
#endif

#endif


