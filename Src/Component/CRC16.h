
#ifndef _CRC16_H_
#define _CRC16_H_

#include "TypeDef.h"

#ifdef _CRC16_C_
#define CRC16_EXT
#else 
#define CRC16_EXT extern
#endif 



//静态局部变量
#ifdef _CRC16_C_

 
#endif 


//函数声明
CRC16_EXT INT16U CRC16Put(INT8U *Msg,INT16U Len);
CRC16_EXT INT8U CRC16Check(INT8U *Msg,INT16U Len);
CRC16_EXT INT16U CRC16Cal(INT8U *Msg,INT16U Len);


#endif

