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
* @brief :键盘API接口
* 
* 
* 
*
* @author :许伟
* @date :2017/8/26 15:03
***************************************************************
*/ 
#ifndef _KEYBOARDAPP_H_
#define _KEYBOARDAPP_H_


#include "Typedef.h"
#include "Keyboard.h"
#include "IndepKEY.h"



#include "cmsis_os.h"


 
#ifdef _KEYBOARDAPP_C_
#define KEYBOARDAPP_EXT
#else
#define KEYBOARDAPP_EXT extern
#endif
 

#define BUTTONMSG_Q_NUM		8	//定义按键消息队列的数量

typedef struct
{
	INT8U Button_Num;				//触发状态  用于引导键值
}KEY_OUT_Stru;

KEYBOARDAPP_EXT KEY_OUT_Stru KeyOutArray[BUTTONMSG_Q_NUM];
KEYBOARDAPP_EXT INT8U KeyOutRecord;	//入栈计数器


#define DATAMSG_Q_NUM			4	//发送数据的消息队列的数量

KEYBOARDAPP_EXT QueueHandle_t KEY_OUT_Msg;				//按键输出队列

 

KEYBOARDAPP_EXT IndepKEY_Stru* KEY1;
KEYBOARDAPP_EXT IndepKEY_Stru* KEY2;
KEYBOARDAPP_EXT IndepKEY_Stru* KEY3;
KEYBOARDAPP_EXT IndepKEY_Stru* KEY4;
KEYBOARDAPP_EXT IndepKEY_Stru* KEY5;
KEYBOARDAPP_EXT IndepKEY_Stru* KEY6;


KEYBOARDAPP_EXT void KeyboardApp_Init(void);



 
#ifdef _KEYBOARDAPP_C_




#endif
 




 
 




 
#endif
/* END */
/*  
 @copy COPYRIGHT 2016 Foryon     
*/  
 




 
