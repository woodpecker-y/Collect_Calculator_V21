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
* @brief :键盘接口文件
* 
* 
* 
*
* @author :许伟
* @date :2017/8/26 15:03
***************************************************************
*/ 
#define _KEYBOARDAPP_C_
#include "KeyboardAPP.h"
 


 IndepKEY_State GetKeyVal_K1(void)
 {
       IndepKEY_State   Value =ReadStateOFF;
	 
       if(KEY1_Val)
       {
            Value =ReadStateOFF;
       }
       else
       {
             Value =ReadStateON;
       }
        return Value;
 }

 IndepKEY_State GetKeyVal_K2(void)
 {
       IndepKEY_State   Value =ReadStateOFF;
       if(KEY2_Val)
       {
            Value =ReadStateOFF;
       }
       else
       {
             Value =ReadStateON;
       }
        return Value;
 }

 IndepKEY_State GetKeyVal_K3(void)
 {
       IndepKEY_State   Value =ReadStateOFF;
       if(KEY3_Val)
       {
            Value =ReadStateOFF;
       }
       else
       {
             Value =ReadStateON;
       }
        return Value;
 }


 IndepKEY_State GetKeyVal_K4(void)
 {
       IndepKEY_State   Value =ReadStateOFF;
       if(KEY4_Val)
       {
            Value =ReadStateOFF;
       }
       else
       {
             Value =ReadStateON;
       }
        return Value;
 }

 IndepKEY_State GetKeyVal_K5(void)
 {
       IndepKEY_State   Value =ReadStateOFF;
       if(KEY5_Val)
       {
            Value =ReadStateOFF;
       }
       else
       {
             Value =ReadStateON;
       }
        return Value;
 }


 IndepKEY_State GetKeyVal_K6(void)
 {
       IndepKEY_State   Value =ReadStateOFF;
       if(KEY6_Val)
       {
            Value =ReadStateOFF;
       }
       else
       {
             Value =ReadStateON;
       }
        return Value;
 }


 
 
void KeyOUT_K1(void)
{
	BaseType_t err;
	err =err;
	
    KeyOutArray[KeyOutRecord].Button_Num =1;
    //发送消息
    err =	xQueueSend(KEY_OUT_Msg, KeyOutArray+KeyOutRecord, portMAX_DELAY);
	KeyOutRecord +=1;
	if(KeyOutRecord >=BUTTONMSG_Q_NUM)
	{
		KeyOutRecord =0;
	}
		
}

void KeyOUT_K2(void)
{
	BaseType_t err;
	err =err;
	
    KeyOutArray[KeyOutRecord].Button_Num =2;
    //发送消息
    err = xQueueSend(KEY_OUT_Msg, KeyOutArray+KeyOutRecord, portMAX_DELAY);
	KeyOutRecord +=1;
	if(KeyOutRecord >=BUTTONMSG_Q_NUM)
	{
		KeyOutRecord =0;
	}
		
}

void KeyOUT_K3(void)
{
	BaseType_t err;
	
	err =err;
	
    KeyOutArray[KeyOutRecord].Button_Num =3;
    //发送消息
    err = xQueueSend(KEY_OUT_Msg, KeyOutArray+KeyOutRecord, portMAX_DELAY);
	KeyOutRecord +=1;
	if(KeyOutRecord >=BUTTONMSG_Q_NUM)
	{
		KeyOutRecord =0;
	}
		
}

void KeyOUT_K4(void)
{
	BaseType_t err;
	err =err;
	
    KeyOutArray[KeyOutRecord].Button_Num =4;
    //发送消息

    err = xQueueSend(KEY_OUT_Msg, KeyOutArray+KeyOutRecord, portMAX_DELAY);
	KeyOutRecord +=1;
	if(KeyOutRecord >=BUTTONMSG_Q_NUM)
	{
		KeyOutRecord =0;
	}
		
}



void KeyOUT_K5(void)
{
	BaseType_t err;
	err =err;
	
    KeyOutArray[KeyOutRecord].Button_Num =5;
    //发送消息
    err = xQueueSend(KEY_OUT_Msg, KeyOutArray+KeyOutRecord, portMAX_DELAY);
	KeyOutRecord +=1;
	if(KeyOutRecord >=BUTTONMSG_Q_NUM)
	{
		KeyOutRecord =0;
	}
		
}


void KeyOUT_K6(void)
{
	BaseType_t err;
	err =err;
	
    KeyOutArray[KeyOutRecord].Button_Num =6;
    //发送消息
    err = xQueueSend(KEY_OUT_Msg, KeyOutArray+KeyOutRecord, portMAX_DELAY);
	KeyOutRecord +=1;
	if(KeyOutRecord >=BUTTONMSG_Q_NUM)
	{
		KeyOutRecord =0;
	}
}






void KeyboardApp_Init(void)
{

	IndepKEYPara_Stru KEYPara;
	KEYPara.FallEdge_Num =10;	//
  
    KEYPara.UpEdge_Num =10;
    KEYPara.LowLevel_NumFirst =200;
    KEYPara.LowLevel_Num =20;
    KEYPara.TrigCondition =(IndepKEY_State)(FallEdge|LowLevel);
    
    KEY1 =IndepKEY_Create(DISABLE,KEYPara,GetKeyVal_K1,KeyOUT_K1);
    IndepKEY_Enable( KEY1,ENABLE);

    KEY2 =IndepKEY_Create(DISABLE,KEYPara,GetKeyVal_K2,KeyOUT_K2);
    IndepKEY_Enable( KEY2,ENABLE);

    KEY3 =IndepKEY_Create(DISABLE,KEYPara,GetKeyVal_K3,KeyOUT_K3);
    IndepKEY_Enable( KEY3,ENABLE);

    KEY4 =IndepKEY_Create(DISABLE,KEYPara,GetKeyVal_K4,KeyOUT_K4);
    IndepKEY_Enable( KEY4,ENABLE);

    KEY5 =IndepKEY_Create(DISABLE,KEYPara,GetKeyVal_K5,KeyOUT_K5);
    IndepKEY_Enable( KEY5,ENABLE);

    KEY6 =IndepKEY_Create(DISABLE,KEYPara,GetKeyVal_K6,KeyOUT_K6);
    IndepKEY_Enable( KEY6,ENABLE);    
}
 



 
 




 
/* END */
/*
 @copy COPYRIGHT 2016 Foryon     
*/
 




 
