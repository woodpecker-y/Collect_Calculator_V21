


#ifndef _NWKMODBUS_H
#define _NWKMODBUS_H
#include "main.h"
#include "UART_RBC.h"
#include "PubDef.h"

#include "stm32f4xx_hal.h"
#include "Typedef.h "
#include "COM_Server.h"

#ifdef Valve_NWK_ENABLE
 
#ifdef _NWKmodbus_C_
#define NWK_EXT
#else
#define NWK_EXT extern
#endif
 


#define NWKPro_HeadSize				        2				    //数据包头大小
#define NWKPro_ACKProtocolCode03		    0X03				//03功能码
#define NWKPro_ACKProtocolCode06		    0X06				//06功能码
#define NWKPro_ACKProtocolCode10		    0X10				//10功能码
#define NWKPro_ACKProtocolSize  		    0X38				//反馈数据长度



#pragma pack(1)		//字节对齐
typedef struct
{
	INT8U	Addr;		//起始字符		1字节
	INT8U	CMD;		//协议类型		1字节
    
}NWK_Head_Stru;

#pragma pack()			//字节对齐


//耐威科通信协议
#pragma pack(1)			//字节对齐
/*设备类型11数据结构   耐威科楼栋单元调节阀NWKmodbus协议
该数据变动较大存储于FRAM
*/
typedef struct
{
	float	Input_Temp;                 //进水温度
	float	Output_Temp;                //回水温度
    float   EnterWater_Pressure;        //进水压力
    float   ReturnWater_Pressure;       //回水压力
    float   Room_Temp;                  //室温
    float   Current_Valve_Open;         //当前阀门开度值
    float   SetValue_Open;              //设置阀门开度值
    float   Temp_Diff;                  //温差设定值
    float   ReturnTemp_Set;             //回水温度设定值
    float   PressureDiff_Set;           //压差设定值
    INT16U  Error;                      //错误代码 0为正常，1为堵转，2为进水温度传感器开路，3.回水温度传感器开路，4.进水压力传感器开路，5回水压力传感器开路
    INT16U  Software_Version;           //软件版本号  100 则为 V1.0 
    INT16U  Run_Mode;                   //运行模式  0为开度模式；1为温差模式2为回温模式3为压差模式4.就地控制模式（电机掉电）5.4-20控制开度模式（需硬件支持）6 TIME
    INT16U  Address;                    //地址 1-247，默认为1
    INT16U  Motor_Steering;             //电机转向 0为正向阀，1为反向阀
    INT16U  Adjust_Switch;              //自动行程校正开关，0关闭，1为打开，值为1时每次上电自动校正行程
    INT16U  Adjust_Tigger;              //写0x5555触发一次
    INT16U  Dc_Motor_Speed;             //直流电机速度
}NWK_Pack_Value_t;





typedef struct
{
	NWK_Head_Stru       Head;           //01 03
    INT8U               lenth;          //寄存器长度
	NWK_Pack_Value_t    data;           //耐威科 实时数据
	INT8U	            CRC16_H;        //CRC高字节 44
	INT8U	            CRC16_L;        //CRC低字节 03
}NWK_Pack_03_ACK_Stru; //03数据结构 实时数据返回


typedef struct
{
	NWK_Head_Stru       Head;           //01 06
	NWK_Pack_Value_t    data;           //耐威科 实时数据
	INT8U	            CRC16_H;        //CRC高字节
	INT8U	            CRC16_L;        //CRC低字节
}NWK_Pack_06_ACK_Stru;//06数据结构 实时数据返回

typedef struct
{
	NWK_Head_Stru       Head;           //01 10
	NWK_Pack_Value_t    data;           //耐威科 实时数据
	INT8U	            CRC16_H;        //CRC高字节
	INT8U	            CRC16_L;        //CRC低字节
}NWK_Pack_10_ACK_Stru;//06数据结构 实时数据返回



//NWK通信协议 数据抄收 下行
typedef struct
{
	NWK_Head_Stru  Head;                    //01 03
	
	INT8U	Register_Addr_H;				//寄存器地址高字节 00
	INT8U	Register_Addr_L;				//寄存器地址低字节 00
	
	INT8U	Register_Num_H;					//寄存器数量高字节 00
	INT8U	Register_Num_L;					//寄存器数量高字节 1C = 28(D)
	
	INT8U	CRC16_H;						//CRC高字节 44
	INT8U	CRC16_L;                        //CRC低字节 03
}NWK_03_Pack_Stru;//实时数据



//NWK通信协议 数据抄收 下行
typedef struct
{
	NWK_Head_Stru  Head;                    //01 06
	
	INT16U	Register_Addr;				    //寄存器首地址
	INT16U	Register_Data;                  //寄存器个数 一个寄存器2个字节
	
	INT8U	CRC16_H;						//CRC高字节
	INT8U	CRC16_L;                        //CRC低字节
    
}NWK_06_Pack_Stru;//实时数据



//NWK通信协议 数据抄收 下行
typedef struct
{
	NWK_Head_Stru  Head;                    //01 06
	
	INT16U	Register_Addr;				//寄存器首地址
	INT16U	Register_lenth;             //寄存器个数 一个寄存器2个字节
	INT8U	Register_size;				//寄存器字节数
    
    float   DataValue;                  //数据
	
	INT8U	CRC16_H;						//CRC高字节
	INT8U	CRC16_L;                        //CRC低字节
    
}NWK_10_Pack_Stru;//实时数据






//解析
typedef union
{
    NWK_Pack_03_ACK_Stru    Pack_03_ack;
    NWK_06_Pack_Stru        Pack_06_ack;
    NWK_06_Pack_Stru        Pack_10_ack;
}NWK_Pack_Uni;


//组包
typedef union
{
    NWK_03_Pack_Stru Pack_03_cmd;
    NWK_06_Pack_Stru pack_06_cmd;
    NWK_10_Pack_Stru pack_10_cmd;
    
}NWK_Send_Uni;







#pragma pack() //字节对齐结束




 
 


#ifdef _NWKmodbus_C_

INT8U NWK_Pack_RxAnalyze_S(UART_RBC_Stru* Ctrl_Point,INT8U DataSize);
INT8U NWK_Pack_Rx_S(UART_RBC_Stru* Ctrl_Point,INT8U Protocol);

#endif
 

NWK_EXT unsigned char *bytes_reverse(unsigned char *dat, unsigned char len);

NWK_EXT void NWK_Pack_RxServer_S( UART_RBC_Stru* Ctrl_Point );
NWK_EXT INT8U NWK_Pack_TxServer_S(UART_RBC_Stru* Ctrl_Point);


 
#endif

#endif


