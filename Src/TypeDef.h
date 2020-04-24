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
* @brief :
* 
* 
* 
*
* @author :
* @date :2017/6/20 12:47
***************************************************************
*/ 
#ifndef _TYPEDEF_H_
#define _TYPEDEF_H_
 



 
#ifdef _TYPEDEF_C_
#define TYPEDEF_EXT
#else
#define TYPEDEF_EXT extern
#endif
 




//  定义与编译器无关的数据类型
//********************************************************************************************************
typedef	unsigned char		INT8U;		//  无符号8位整型变量
typedef	unsigned char		UINT8;		//  无符号8位整型变量
typedef	unsigned char		U8;			//  无符号8位整型变量
typedef	unsigned char		u8;			//  无符号8位整型变量

typedef	signed char			INT8S;		//  有符号8位整型变量
typedef	signed char			SINT8;		 //  有符号8位整型变量
typedef	signed char			S8;			//  有符号8位整型变量
typedef	signed char			s8;			//  有符号8位整型变量


typedef	unsigned short		INT16U;		//  无符号16位整型变量
typedef	unsigned short		UINT16;	 	//  无符号16位整型变量
//typedef	unsigned short		U16;             	//  无符号16位整型变量
typedef	unsigned short		u16;             	//  无符号16位整型变量


typedef	signed short		SINT16;		//  有符号16位整型变量
typedef	signed short		INT16S;		//  有符号16位整型变量
typedef	signed short		S16;		//  有符号16位整型变量
typedef	signed short		s16;		//  有符号16位整型变量

typedef	unsigned long		INT32U;	//  无符号32位整型变量
typedef	unsigned long		UINT32;	//  无符号32位整型变量
//typedef	unsigned long		U32;		//  无符号32位整型变量

typedef	signed long			INT32S;		 //  有符号32位整型变量
typedef	signed long			SINT32;		//  有符号32位整型变量
//typedef	signed long			S32;		//  有符号32位整型变量

typedef	unsigned long long	INT64U;	//  无符号64位整型变量      
typedef	unsigned long long	U64;		//  无符号64位整型变量      
typedef	unsigned long long	u64;		//  无符号64位整型变量      

typedef	long long			INT64S;		//  有符号64位整型变量		
typedef	long long			S64;		//  有符号64位整型变量		
typedef	long long			s64;		//  有符号64位整型变量		

typedef	float				FL32;		//  单精度浮点数（32位长度）
typedef	double				FL64;		//  双精度浮点数（64位长度）


///*********************************************************************************************************************





 
#ifdef _TYPEDEF_C_
//*************************自定义BCD TO HEX 转换数据服务类型
#pragma pack(1)
typedef union
{
	INT16U Data;
	struct 
	{
		INT8U Gr0 :4;	//十进制第1位
		INT8U Gr1 :4;	//十进制第2位
		INT8U Gr2 :4;	//十进制第3位
		INT8U Gr3 :4;	//十进制第4位
	}Data_Bytes;
}BCD_HEX_2;

typedef union
{
	INT32U Data;
	struct 
	{
		INT8U Gr0 :4;	//十进制第1位
		INT8U Gr1 :4;	//十进制第2位
		INT8U Gr2 :4;	//十进制第3位
		INT8U Gr3 :4;	//十进制第4位
		INT8U Gr4 :4;	//十进制第5位
		INT8U Gr5 :4;	//十进制第6位
		INT8U Gr6 :4;	//十进制第7位
		INT8U Gr7 :4;	//十进制第8位
	}Data_Bytes;
}BCD_HEX_4;
#pragma pack()





#endif
 




 
 

TYPEDEF_EXT INT8U HexToBcd(INT8U Byte);
TYPEDEF_EXT INT8U BcdToHex(INT8U Byte);
TYPEDEF_EXT INT16U BcdToHex2(INT16U *DATA);
TYPEDEF_EXT INT16U HexToBcd2(INT16U *DATA);
TYPEDEF_EXT INT32U BcdToHex4(INT32U *DATA);
TYPEDEF_EXT INT32U HexToBcd4(INT32U *DATA);


 
#endif
/* END */
/*  
 @copy COPYRIGHT 2016 Foryon     
*/  
 




 
