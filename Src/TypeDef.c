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
* @brief :ÐíÎ°
* 
* 
* 
*
* @author :
* @date :2017/6/20 12:47
***************************************************************
*/ 
#define _TYPEDEF_C_
#include "TypeDef.h"

 



INT8U HexToBcd(INT8U Byte)
{
		INT8U byte2;
		byte2 =(Byte / 10)* 16+(Byte % 10);
		return byte2;
}

INT8U BcdToHex(INT8U Byte)
{
	INT8U Byte2;

	Byte2 =(Byte >>4)* 10+(Byte & 0x0f);

	return Byte2;
}

INT16U BcdToHex2(INT16U *DATA)
{
	INT16U Databack =0;
	BCD_HEX_2 DataBuf;
	DataBuf.Data =*DATA;
	
	Databack +=DataBuf.Data_Bytes.Gr0;
	Databack +=DataBuf.Data_Bytes.Gr1*10;
	Databack +=DataBuf.Data_Bytes.Gr2*100;
	Databack +=DataBuf.Data_Bytes.Gr3*1000;
	return Databack;
}

INT16U HexToBcd2(INT16U *DATA)
{
	BCD_HEX_2 DataBuf;
	INT16U Data =*DATA;
	
	DataBuf.Data_Bytes.Gr3 =Data/1000;
	DataBuf.Data_Bytes.Gr2 =Data%1000/100;
	DataBuf.Data_Bytes.Gr1 =Data%100/10;
	DataBuf.Data_Bytes.Gr0 =Data%10;

	Data =DataBuf.Data;
	
	return Data;
}



INT32U BcdToHex4(INT32U *DATA)
{
	INT32U Databack =0;
	BCD_HEX_4 DataBuf;
	DataBuf.Data =*DATA;
	
	
	Databack +=DataBuf.Data_Bytes.Gr0;
	Databack +=DataBuf.Data_Bytes.Gr1*10;
	Databack +=DataBuf.Data_Bytes.Gr2*100;
	Databack +=DataBuf.Data_Bytes.Gr3*1000;
	Databack +=DataBuf.Data_Bytes.Gr4*10000;
	Databack +=DataBuf.Data_Bytes.Gr5*100000;
	Databack +=DataBuf.Data_Bytes.Gr6*1000000;
	Databack +=DataBuf.Data_Bytes.Gr7*10000000;	
	return Databack;
}


INT32U HexToBcd4(INT32U *DATA)
{
	BCD_HEX_4 DataBuf;
	INT32U Data =*DATA;
	
	DataBuf.Data_Bytes.Gr7 =Data/10000000;
	DataBuf.Data_Bytes.Gr6 =Data%10000000/1000000;
	DataBuf.Data_Bytes.Gr5 =Data%1000000/100000;
	DataBuf.Data_Bytes.Gr4 =Data%100000/10000;
	DataBuf.Data_Bytes.Gr3 =Data%10000/1000;
	DataBuf.Data_Bytes.Gr2 =Data%1000/100;
	DataBuf.Data_Bytes.Gr1 =Data%100/10;
	DataBuf.Data_Bytes.Gr0 =Data%10;	
	Data =DataBuf.Data;
	
	return Data;
}

 
 






 
/* END */
/*
 @copy COPYRIGHT 2016 Foryon     
*/
 




 
