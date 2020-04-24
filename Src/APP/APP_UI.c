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
* @date :2017/9/4 12:00
***************************************************************
*/ 
#define _APP_UI_C_
#include "APP_UI.h"
#include "main.h"
#include "Sys_State.h"


char Hardware[]="1.硬件: FY-1100M-V22";
char Software[]="2.软件: FY-1101_V22A";



void Clear_PSG(void)
{
	PressInData.PSG1 =0;PressInData.PSG2 =0;PressInData.PSG3 =0;PressInData.PSG4 =0;PressInData.PSG5 =0;PressInData.PSG6 =0;
	PressInData.PSG7 =0;PressInData.PSG8 =0;PressInData.PSG9 =0;PressInData.PSG10 =0;PressInData.PSG11 =0;PressInData.PSG12 =0;
	PressInData.PSG13 =0;PressInData.PSG14 =0;PressInData.PSG15 =0;PressInData.PSG16 =0;PressInData.PSG17 =0;PressInData.PSG18 =0;
	PressInData.PSG19 =0;PressInData.PSG19 =0;PressInData.PSG20 =0;PressInData.PSG21 =0;PressInData.PSG22 =0;PressInData.PSG23 =0;
	PressInData.PSG24=0;PressInData.PSG25=0;PressInData.PSG26 =0;PressInData.PSG27 =0;PressInData.PSG28 =0;PressInData.PSG29 =0;PressInData.PSG30 =0;	
	PressInData.PSG31=0;PressInData.PSG32=0;PressInData.PSG33 =0;PressInData.PSG34 =0;PressInData.PSG35 =0;PressInData.PSG36 =0;PressInData.PSG37 =0;
	PressInData.PSG38 =0;PressInData.PSG39 =0;PressInData.PSG40 =0;
	PressInData.PSWErr =0;
	PressInData.E2RomErr =0;
	PressInData.FirstInFlag =0;
	PressInData.correct =0;
	PressInData.password =0;
	
}


/*
 函数名称: INT16U User_Filter (INT8U BuldNum,INT8U UnitNum,INT8U FloorNum,INT8U CellNum)
 函数功能:根据用户的住址等信息筛选用户并返回用户的ID
 返回值:0没有找到相应用户;其他值表示用户的ID
 
*/
INT16U User_Filter (INT8U BuldNum,INT8U UnitNum,INT8U FloorNum,INT8U CellNum,INT16U UserNum)
{
	INT16U UserID =0;
	INT16U K =0;//循环控制变量
	INT8U Buld =BuldNum;
	INT8U Unit =UnitNum;
	INT8U Floor =FloorNum;
	INT8U Cell =CellNum;
	for ( K=0;K<UserNum;K++)
	{
		if (SysUserList.User[K].Buld ==Buld)
		{
			if(SysUserList.User[K].Unit ==Unit )
			{
				if(SysUserList.User[K].Floor ==Floor )
				{
					if(SysUserList.User[K].Cell ==Cell )
					{
						UserID =K+1;
						break;
					}
				}
			}
		}
	}
	return UserID;
}





void Disp_1_X_UserFilter(void)
{
	if (PressInData.FilterErr ==1)
	{
		Fill_VisionBUF(0,26,159,70,0);
		GUI_Rectangle_Dev(20,30,140, 68,2,1);

		DispStringM(28,35,"用户信息检索失败",0,10);
		DispStringM(40,52,"该用户不存在",0,10);
		
	}
}


void Disp_1_3_DataSaveFlag(void)
{
	if (PressInData.E2RomErr ==1)
	{

		Fill_VisionBUF(0,20,159,60,0);
		GUI_Rectangle_Dev(20,30,140, 60, 2,1);		
		DispStringM(35,35,"数据保存失败",0,11);
	}
	if (PressInData.E2RomErr ==2)
	{

		Fill_VisionBUF(0,20,159,60,0);
		GUI_Rectangle_Dev(20,30,140, 60, 2,1);		
		DispStringM(35,35,"数据保存成功",0,11);
	}

	if (PressInData.E2RomErr ==3)
	{
		Fill_VisionBUF(0,20,159,90,0);
		GUI_Rectangle_Dev(15,30,145,80, 2,1);		
		DispStringM(20,35,"终端参数保存成功",0,11);
		DispStringM(28,55,"请设置栋表参数",0,11);
	}		

	if (PressInData.E2RomErr ==4)
	{
		Fill_VisionBUF(0,20,159,90,0);
		GUI_Rectangle_Dev(15,30,145,80, 2,1);		
		DispStringM(20,35,"终端参数保存成功",0,11);
		DispStringM(42,55,"数据未更改",0,11);
	}	
	
	if (PressInData.E2RomErr ==5)
	{

		Fill_VisionBUF(0,20,159,60,0);
		GUI_Rectangle_Dev(15,30,145,60, 2,1);		
		DispStringM(20,35,"栋表参数保存成功",0,11);
	}	
}


/*
 * 密码输入错误提示
 */
void Disp_1_3_PasswordError(void)	
{

	INT16U LineSpace =27;
	INT16U FirstSpace =35;

	
	if (PressInData.PSWErr ==1)
	{
		Fill_VisionBUF(0,20,159,100,0);
		GUI_Rectangle_Dev(15,30,145, 90, 2,1);
		DispStringM(35,FirstSpace+LineSpace*0,"密码输入错误",0,11);
		DispStringM(21,FirstSpace+LineSpace*1+5,"请重新输入管理密码",0,10);
	}   
}



void Disp_1_3PassWord(void)
{

	INT16U LineSpace =27;
	INT16U FirstSpace =32;
	
	INT16U passnum =0;
	INT8U G1 =0;
	INT8U G2 =0;
	INT8U G3 =0;
	INT8U G4 =0;
	char CH1[2];
	char CH2[2];
	char CH3[2];
	char CH4[2];
    
	passnum = PressInData.password;
    
	CH1[1] ='\0';
	CH2[1] ='\0';
	CH3[1] ='\0';
	CH4[1] ='\0';

	CH1[0] =(((passnum>>12)&0X0F)>9)?('0'+7+((passnum>>12)&0X0F)):('0'+((passnum>>12)&0X0F));
	CH2[0] =(((passnum>>8)&0X0F)>9)?('0'+7+((passnum>>8)&0X0F)):('0'+((passnum>>8)&0X0F));
	CH3[0] =(((passnum>>4)&0X0F)>9)?('0'+7+((passnum>>4)&0X0F)):('0'+((passnum>>4)&0X0F));
	CH4[0] =(((passnum>>0)&0X0F)>9)?('0'+7+((passnum>>0)&0X0F)):('0'+((passnum>>0)&0X0F));
	switch (CursorRecord)
	{
		case 1: G1 =1;break;
		case 2: G2 =1;break;
		case 3: G3 =1;break;
		case 4: G4 =1;break;
		default :     break;
	}

    
	    DispStringM(32,4,"--密码验证--",0,12);
	    
	    DispStringM(27,FirstSpace+LineSpace*0,"请输入管理密码",0,11);
	    
	    DispStringM(55,FirstSpace+LineSpace*1,"[",0,11);
	    DispStringM(55+9*1,FirstSpace+LineSpace*1,CH1,G1,11);
	    DispStringM(55+9*2,FirstSpace+LineSpace*1,CH2,G2,11);
	    DispStringM(55+9*3,FirstSpace+LineSpace*1,CH3,G3,11);
	    DispStringM(55+9*4,FirstSpace+LineSpace*1,CH4,G4,11);
	    DispStringM(55+9*5,FirstSpace+LineSpace*1,"]",0,11);
	    Disp_1_3_PasswordError();

}




//开机画面
void Disp_Open(void)
{

	char TIME[30] =" ";
	char* hg="-";
	char* mh=":";
	char* kg=" ";

	RealClock_Str TimeNow =RTC_Time;

	strcat(TIME,Disp_Integer(TimeNow.Year));
	strcat(TIME,hg);

	if( (TimeNow.Month/10) ==0)
	{
		strcat(TIME,"0");
	}
	strcat(TIME,Disp_Integer(TimeNow.Month));
	
	strcat(TIME,hg);

	if( (TimeNow.Day/10) ==0)
	{
		strcat(TIME,"0");
	}
	strcat(TIME,Disp_Integer(TimeNow.Day));
	
	strcat(TIME,kg);
	strcat(TIME,kg);
	
	if( (TimeNow.Hour/10) ==0)
	{
		strcat(TIME,"0");
	}	
	strcat(TIME,Disp_Integer(TimeNow.Hour));


	strcat(TIME,mh);
	
	if( (TimeNow.Minute/10) ==0)
	{
		strcat(TIME,"0");
	}		
	strcat(TIME,Disp_Integer(TimeNow.Minute));

	strcat(TIME,mh);
	if( (TimeNow.Second/10) ==0)
	{
		strcat(TIME,"0");
	}		
	strcat(TIME,Disp_Integer(TimeNow.Second));

	Clear_VisionBUF();
	
	DispStringM(4,4,TIME,0,10);

	DispStringM(52,45,"FY-1102",0,12);
	DispStringM(32,75,"热量采集系统",0,12);
	
	DispStringM(41,140,"河北丰源智控",0,10);
	Refresh_Screen();

}









void Menu_1 (void)	
{
    if (( CursorRecord <1)||(CursorRecord>4))  //判断光标值的范围
    {
        CursorRecord =1;
    }
    if ((( Keyvalue.value ==KEY_ML)||(Keyvalue.value ==KEY_MU))&&(Keyvalue.resp ==1))      //上移   左移
    {
        Keyvalue.resp =0;
        if (( CursorRecord <1)||(CursorRecord>4))  //判断光标值的范围
        {
            CursorRecord =1;
        }
        CursorRecord-=1;
        if (CursorRecord <1)
        {
            CursorRecord =4;
        }
    }
    
    if ((( Keyvalue.value ==KEY_MD)||(Keyvalue.value ==KEY_MR))&&(Keyvalue.resp ==1))      //下移 右移
    {
        Keyvalue.resp =0;
        CursorRecord+=1;
        if (CursorRecord >4)
        {
            CursorRecord =1;
        }
    }
    
    if (( Keyvalue.value ==KEY_CA) &&(Keyvalue.resp ==1))                  //取消键
    {
        Keyvalue.resp =0;
        ScreenRecord.ra1 =0;ScreenRecord.ra2 =0;
        ScreenRecord.ra1 =0;ScreenRecord.ra3 =0;
        ScreenRecord.ra4 =0;ScreenRecord.ra5 =0;
        CursorRecord =1;
    }
    if (( Keyvalue.value ==KEY_CO) &&(Keyvalue.resp ==1))                   //确认键
    {
        Keyvalue.resp =0;
        ScreenRecord.ra2 = CursorRecord;
        CursorPRecord1 =CursorRecord;
        CursorRecord =1;
    }
}





void Menu_1_1 (void)			//二级  系统状态   按键管理
{
    if (( CursorRecord <1)||(CursorRecord>5))       //判断光标值的范围
    {
        CursorRecord =1;
    }

    if ((( Keyvalue.value ==KEY_ML)||(Keyvalue.value ==KEY_MU))&&(Keyvalue.resp ==1))      //上移   左移
    {
       Keyvalue.resp =0;
       if (( CursorRecord <1)||(CursorRecord>5))       //判断光标值的范围
       {
            CursorRecord =1;
       }
        CursorRecord-=1;
        if (CursorRecord <1)
        {
            CursorRecord =5;
        }
    }
    if ((( Keyvalue.value ==KEY_MD)||(Keyvalue.value ==KEY_MR))&&(Keyvalue.resp ==1))      //下移 右移
    {
        Keyvalue.resp =0;
        if (( CursorRecord <1)||(CursorRecord>5))       //判断光标值的范围
        {
            CursorRecord =1;
        }
        CursorRecord+=1;
        if (CursorRecord >5)
        {
            CursorRecord =1;
        }
    }
    if (( Keyvalue.value ==KEY_CA)&&(Keyvalue.resp ==1)  )                 //取消键
    {
        Keyvalue.resp =0;
        ScreenRecord.ra2 =0;
        CursorRecord =CursorPRecord1;
        Clear_PSG();
    }
    if (( Keyvalue.value ==KEY_CO)&&(Keyvalue.resp ==1) )                  //确认键
    {
        Keyvalue.resp =0;
        ScreenRecord.ra3 =CursorRecord;
        CursorPRecord2 =CursorRecord;
        CursorRecord =1;
    }
}




void Menu_1_1_1 (void)     //设备自检按键管理
{
    if (( CursorRecord <1)||(CursorRecord>2))       //判断光标值的范围
    {
        CursorRecord =1;
    }

    if ((( Keyvalue.value ==KEY_ML)||(Keyvalue.value ==KEY_MU))&&(Keyvalue.resp ==1))      //上移   左移
    {
       Keyvalue.resp =0;
       if (( CursorRecord <1)||(CursorRecord>2))       //判断光标值的范围
       {
            CursorRecord =1;
       }
        CursorRecord-=1;
        if (CursorRecord <1)
        {
            CursorRecord =2;
        }
    }
    if ((( Keyvalue.value ==KEY_MD)||(Keyvalue.value ==KEY_MR))&&(Keyvalue.resp ==1))      //下移 右移
    {
        Keyvalue.resp =0;
        if (( CursorRecord <1)||(CursorRecord>2))       //判断光标值的范围
        {
            CursorRecord =1;
        }
        CursorRecord+=1;
        if (CursorRecord >2)
        {
            CursorRecord =1;
        }
    }
    if (( Keyvalue.value ==KEY_CA)&&(Keyvalue.resp ==1)  )                 //取消键
    {
        Keyvalue.resp =0;
        ScreenRecord.ra3 =0;
      
        CursorRecord =CursorPRecord2;
        Clear_PSG();
    }
    if (( Keyvalue.value ==KEY_CO)&&(Keyvalue.resp ==1) )                  //确认键
    {
        Keyvalue.resp =0;
        ScreenRecord.ra3 = 0;
        CursorRecord =CursorPRecord2;
        Clear_PSG();
    }

}



void Menu_1_1_2 (void)			//终端状态
{
    if (( CursorRecord <1)||(CursorRecord>384))       //判断光标值的范围
    {
        CursorRecord =1;
    }
    
    if ((( Keyvalue.value ==KEY_ML))&&(Keyvalue.resp ==1))//左移
    {
       Keyvalue.resp =0;
       if (( CursorRecord <1)||(CursorRecord>384))       //判断光标值的范围
       {
            CursorRecord =1;
       }
        CursorRecord-=1;
        if (CursorRecord <1)
        {
            CursorRecord =384;
        }
    }
    
    if (((Keyvalue.value ==KEY_MR))&&(Keyvalue.resp ==1))//右移
    {
        Keyvalue.resp =0;
        if (( CursorRecord <1)||(CursorRecord>384))       //判断光标值的范围
        {
            CursorRecord =1;
        }
        CursorRecord+=1;
        if (CursorRecord >384)
        {
            CursorRecord =1;
        }
    }
    
    if (((Keyvalue.value ==KEY_MU))&&(Keyvalue.resp ==1))//上移
    {
       Keyvalue.resp =0;
       if (( CursorRecord <1)||(CursorRecord>384))       //判断光标值的范围
       {
            CursorRecord =1;
       }
        CursorRecord-=16;
        if (CursorRecord <1)
        {
            CursorRecord +=256;
        }
    }    
    if ((( Keyvalue.value ==KEY_MD)||(Keyvalue.value ==KEY_MR))&&(Keyvalue.resp ==1))      //下移
    {
        Keyvalue.resp =0;
        if (( CursorRecord <1)||(CursorRecord>384))       //判断光标值的范围
        {
            CursorRecord =1;
        }
        CursorRecord+=16;
        if (CursorRecord >384)
        {
            CursorRecord -=384;
        }
    }

    
    if (( Keyvalue.value ==KEY_CA)&&(Keyvalue.resp ==1)  )                 //取消键
    {
        Keyvalue.resp =0;
        ScreenRecord.ra3 =0;
        CursorRecord =CursorPRecord2;
        Clear_PSG();
    }
    if (( Keyvalue.value ==KEY_CO)&&(Keyvalue.resp ==1) )                  //确认键
    {
        Keyvalue.resp =0;
        ScreenRecord.ra4 =1;
        CursorPRecord3=CursorRecord;
        PressInData.Num_Dev =CursorPRecord3;
        CursorRecord =1;
    }

}





void Menu_1_1_2_1 (void)     //终端状态
{
	INT16U	BackVal =0;
	if (PressInData.FilterErr !=0)	//上一次密码输入错误，本次只清提示框
	{
		PressInData.FilterErr =0;
	}
	else
	{
		if( PressInData.FirstInFlag==0 )
		{
			if((PressInData.Num_Dev ==0)||(PressInData.Num_Dev >MAXDevice_Num))
			{
				PressInData.Num_Dev =1;
			}
			PressInData.PSG1 =PressInData.Num_Dev/100;
			PressInData.PSG2 =PressInData.Num_Dev%100/10;
			PressInData.PSG3 =PressInData.Num_Dev%10;
			PressInData.FirstInFlag=1;
			
		}
		if (( CursorRecord <1)||(CursorRecord>10))       //判断光标值的范围
		{
			CursorRecord =1;
		}
		
		if (( Keyvalue.value ==KEY_ML)&&(Keyvalue.resp ==1)) //左移
		{
		   Keyvalue.resp =0;
		   if (( CursorRecord <1)||(CursorRecord>10))          //判断光标值的范围
		   {
				CursorRecord =1;
		   }
			CursorRecord-=1;
			if (CursorRecord <1)
			{
				CursorRecord =10;
			}
		}
		
		if ((Keyvalue.value ==KEY_MR)&&(Keyvalue.resp ==1)) //右移
		{
			Keyvalue.resp =0;
			if ((CursorRecord <1)||(CursorRecord>10))       //判断光标值的范围
			{
				CursorRecord =1;
			}
			CursorRecord+=1;
			if (CursorRecord >10)
			{
				CursorRecord =1;
			}
		}
		
		if ((Keyvalue.value ==KEY_MU)&&(Keyvalue.resp ==1))//上移
		{
			Keyvalue.resp =0;
			switch ( CursorRecord)
			{
				case 1://序号百位
				{
					PressInData.PSG1++;
					if (PressInData.PSG1 >2)
					{
						PressInData.PSG1 =0;
					}
				};break;
				case 2://序号十位
				{
					PressInData.PSG2++;
					if (PressInData.PSG2 >9)
					{
						PressInData.PSG2 =0;
						PressInData.PSG1++;
						if (PressInData.PSG1 >2)
						{
							PressInData.PSG1 =0;
						}	
					}
				};break;
				case 3://序号个位
				{
					PressInData.PSG3++;
					if (PressInData.PSG3 >9)
					{
						PressInData.PSG3 =0;
						PressInData.PSG2++;
						if (PressInData.PSG2 >9)
						{
							PressInData.PSG2 =0;
							PressInData.PSG1++;
							if (PressInData.PSG1 >2)
							{
								PressInData.PSG1 =0;
							}
						}
					}
				};break;			
				
				case 4://楼号十位
				{
					PressInData.PSG4++;
					if (PressInData.PSG4 >9)
					{
						PressInData.PSG4 =0;
					}
				};break;
				case 5://楼号个位
				{
					PressInData.PSG5++;
					if (PressInData.PSG5 >9)
					{
						PressInData.PSG5 =0;
					}
				};break;

				
				 case 6://单元
				{
					PressInData.PSG6++;
					if (PressInData.PSG6 >9)
					{
						PressInData.PSG6 =1;
					}
				};break;

				
				 case 7://楼层十位
				{
					PressInData.PSG7++;
					if (PressInData.PSG7 >9)
					{
						PressInData.PSG7 =0;
					}
				};break;
				 case 8://楼层个位
				{
					PressInData.PSG8++;
					if (PressInData.PSG8 >9)
					{
						PressInData.PSG8 =0;
					}
				};break;
				
				 case 9://房间十位
				{
					PressInData.PSG9++;
					if (PressInData.PSG9 >5)
					{
						PressInData.PSG9 =0;
					}
				};break;
				 case 10://房间个位
				{
					PressInData.PSG10++;
					if (PressInData.PSG10>9)
					{
						PressInData.PSG10=0;
					}
				};break;
				default: break;
			}
		}
		if ((Keyvalue.value ==KEY_MD)&&(Keyvalue.resp ==1))      //下移
		{
			Keyvalue.resp =0;
			switch ( CursorRecord)
			{
				case 1://序号百位
				{
					if ( PressInData.PSG1 ==0)
					{
						PressInData.PSG1 =2;
					}
					else
					{
						PressInData.PSG1 --;
					}
				};break;

				case 2://序号十位
				{
					if ( PressInData.PSG2 ==0)
					{
						PressInData.PSG2 =9;
					}
					else
					{
						PressInData.PSG2 --;
					}
				}break;
				case 3://序号个位
				{
					if ( PressInData.PSG3 ==0)
					{
						PressInData.PSG3 =9;
					}
					else
					{
						PressInData.PSG3 --;
					}
					
				}break;
				case 4://楼号十位
				{
					if ( PressInData.PSG4 ==0)
					{
						PressInData.PSG4 =9;
					}
					else
					{
						PressInData.PSG4 --;
					}
				}break;
				case 5://楼号个位
				{
					if ( PressInData.PSG5 ==0)
					{
						PressInData.PSG5 =9;
					}
					else
					{
						PressInData.PSG5 --;
					}
				}break;
				case 6://单元
				{
					if ( PressInData.PSG6 ==1)
					{
						PressInData.PSG6 =9;
					}
					else
					{
						PressInData.PSG6 --;
					}
				}break;
				case 7://层号十位
				{
					if ( PressInData.PSG7 ==0)
					{
						PressInData.PSG7 =9;
					}
					else
					{
						PressInData.PSG7 --;
					}
				}break;
				case 8://层号个位
				{
					if ( PressInData.PSG8 ==0)
					{
						PressInData.PSG8 =9;
					}
					else
					{
						PressInData.PSG8 --;
					}
				}break;
				case 9://房间十位
				{
					if ( PressInData.PSG9 ==0)
					{
						PressInData.PSG9 =9;
					}
					else
					{
						PressInData.PSG9 --;
					}
				}break;
				case 10://房间个位
				{
					if ( PressInData.PSG10==0)
					{
						PressInData.PSG10=9;
					}
					else
					{
						PressInData.PSG10--;
					}
				}break;
				default:break;
			}
		}



		PressInData.Num_Dev  =PressInData.PSG1*100+PressInData.PSG2*10+PressInData.PSG3;
		
		if ( PressInData.Num_Dev>MAXDevice_Num)
		{
			PressInData.Num_Dev =MAXDevice_Num;

			PressInData.PSG1 =PressInData.Num_Dev/100;
			PressInData.PSG2 =PressInData.Num_Dev%100/10;
			PressInData.PSG3 =PressInData.Num_Dev%10;
		}
		if ( PressInData.Num_Dev<1)
		{
			PressInData.Num_Dev=1;
			PressInData.PSG1 =0;
			PressInData.PSG2 =0;
			PressInData.PSG3 =1;
		}
		
		PressInData.Buld=PressInData.PSG4*10+PressInData.PSG5;
		if ( PressInData.Buld >99)
		{
			PressInData.Buld =99;
			PressInData.PSG4 =9;
			PressInData.PSG5 =9;
		}
		if ( PressInData.Buld <1)
		{
			PressInData.Buld =1;
			PressInData.PSG4 =0;
			PressInData.PSG5 =1;
		}
		
		PressInData.Unit=PressInData.PSG6;
		if ( PressInData.Unit>9)
		{
			PressInData.Unit =9;
			PressInData.PSG6 =9;
		}
		if ( PressInData.Unit<1)
		{
			PressInData.Unit =1;
			PressInData.PSG6 =1;
		}

		
		PressInData.Floor=PressInData.PSG7*10 +PressInData.PSG8;
		if ( PressInData.Floor>60)
		{
			PressInData.Floor=60;
			PressInData.PSG7 =6;
			PressInData.PSG8 =0;
		}
		if ( PressInData.Floor<1)
		{
			PressInData.Floor=1;
			PressInData.PSG7 =0;
			PressInData.PSG8 =1;
		}
		
		PressInData.Cell=PressInData.PSG9*10+PressInData.PSG10;
		if ( PressInData.Cell>10)
		{
			PressInData.Cell=10;
			PressInData.PSG9 =1;
			PressInData.PSG10 =0;
		}
		
		if ( PressInData.Cell<1)
		{
			PressInData.Cell=1;
			PressInData.PSG9 =0;
			PressInData.PSG10 =1;
		}




		

		if (( Keyvalue.value ==KEY_CA)&&(Keyvalue.resp ==1)  )                 //取消键
		{
			Keyvalue.resp =0;
			ScreenRecord.ra4 =0;
			CursorRecord =PressInData.Num_Dev;
			PressInData.FirstInFlag=0;
		}
		if (( Keyvalue.value ==KEY_CO)&&(Keyvalue.resp ==1) )                  //确认键
		{
			Keyvalue.resp =0;
			PressInData.FirstInFlag=0;
			if (CursorRecord >3)
			{
				BackVal=User_Filter(PressInData.Buld,PressInData.Unit,PressInData.Floor,PressInData.Cell,SysPara.UserNum);//楼号  单元号 楼层号  房间号    房间数量

				if (( BackVal ==0)||( BackVal >SysPara.UserNum))
				{
					PressInData.FilterErr =1;
					CursorRecord =4;
				}
				else
				{
					INT16U DevNum =0;
					GetMeters_Num_FromUserID(SysUserList.User[BackVal-1].User_ID,&DevNum);
					PressInData.Num_Dev =DevNum +=1;
					PressInData.PSG1 =PressInData.Num_Dev/100;
					PressInData.PSG2 =PressInData.Num_Dev%100/10;
					PressInData.PSG3 =PressInData.Num_Dev%10;
				}
			}
		}
	}
}





void Menu_1_1_3(void)     //热表状态
{

	if (( CursorRecord !=1))       //判断光标值的范围
	{
		CursorRecord =1;
	}
	if (((Keyvalue.value ==KEY_MU)||( Keyvalue.value ==KEY_ML))&&(Keyvalue.resp ==1))//上移
	{
		Keyvalue.resp =0;
		switch ( CursorRecord)
		{
			case 1://序号
			{
				PressInData.PSG1++;
				if (PressInData.PSG1 >SysPara.BuldMeterNum)
				{
					PressInData.PSG1 =1;
				}
			};break;
			default: break;
		}
	}
	if (((Keyvalue.value ==KEY_MD)||(Keyvalue.value ==KEY_MR))&&(Keyvalue.resp ==1))      //下移
	{
		Keyvalue.resp =0;
		switch ( CursorRecord)
		{
			case 1://序号
			{
				if ( PressInData.PSG1 ==1)
				{
					PressInData.PSG1 =SysPara.BuldMeterNum;
				}
				else
				{
					PressInData.PSG1 --;
				}
			};break;

			default:break;
		}
	}

	PressInData.Num_BuldMeter  =PressInData.PSG1;
	
	if ( PressInData.Num_BuldMeter>SysPara.BuldMeterNum)
	{
		PressInData.Num_BuldMeter=SysPara.BuldMeterNum;
		PressInData.PSG1 =SysPara.BuldMeterNum;
	}
	
	if ( PressInData.Num_BuldMeter<1)
	{
		PressInData.Num_BuldMeter=1;
		PressInData.PSG1 =1;
	}

	if (( Keyvalue.value ==KEY_CA)&&(Keyvalue.resp ==1)  )                 //取消键
	{
	        Keyvalue.resp =0;
	        ScreenRecord.ra3=0;
	        CursorRecord =CursorPRecord2;
	        Clear_PSG();
	}
	
	if (( Keyvalue.value ==KEY_CO)&&(Keyvalue.resp ==1) )                  //确认键
	{
	        Keyvalue.resp =0;
	        ScreenRecord.ra3=0;
	        CursorRecord =CursorPRecord2;
	        Clear_PSG();
	}

}

void Menu_1_1_4 (void)     //版本信息按键管理
{

    if (( CursorRecord <1)||(CursorRecord>2))       //判断光标值的范围
    {
        CursorRecord =1;
    }

    if ((( Keyvalue.value ==KEY_ML)||(Keyvalue.value ==KEY_MU))&&(Keyvalue.resp ==1))      //上移   左移
    {
       Keyvalue.resp =0;
       if (( CursorRecord <1)||(CursorRecord>2))       //判断光标值的范围
       {
            CursorRecord =1;
       }
        CursorRecord-=1;
        if (CursorRecord <1)
        {
            CursorRecord =2;
        }
    }
    if ((( Keyvalue.value ==KEY_MD)||(Keyvalue.value ==KEY_MR))&&(Keyvalue.resp ==1))      //下移 右移
    {
        Keyvalue.resp =0;
        if (( CursorRecord <1)||(CursorRecord>2))       //判断光标值的范围
        {
            CursorRecord =1;
        }
        CursorRecord+=1;
        if (CursorRecord >2)
        {
            CursorRecord =1;
        }
    }
    if (( Keyvalue.value ==KEY_CA)&&(Keyvalue.resp ==1)  )                 //取消键
    {
        Keyvalue.resp =0;
        ScreenRecord.ra3 =0;
      
        CursorRecord =CursorPRecord2;
        Clear_PSG();
    }
    if (( Keyvalue.value ==KEY_CO)&&(Keyvalue.resp ==1) )                  //确认键
    {
        Keyvalue.resp =0;
        ScreenRecord.ra3 = 0;
        CursorRecord =CursorPRecord2;
        Clear_PSG();
    }

}


void Menu_1_1_5 (void)     //版本信息按键管理
{

    if (( CursorRecord <1)||(CursorRecord>2))       //判断光标值的范围
    {
        CursorRecord =1;
    }

    if ((( Keyvalue.value ==KEY_ML)||(Keyvalue.value ==KEY_MU))&&(Keyvalue.resp ==1))      //上移   左移
    {
       Keyvalue.resp =0;
       if (( CursorRecord <1)||(CursorRecord>2))       //判断光标值的范围
       {
            CursorRecord =1;
       }
        CursorRecord-=1;
        if (CursorRecord <1)
        {
            CursorRecord =2;
        }
    }
    if ((( Keyvalue.value ==KEY_MD)||(Keyvalue.value ==KEY_MR))&&(Keyvalue.resp ==1))      //下移 右移
    {
        Keyvalue.resp =0;
        if (( CursorRecord <1)||(CursorRecord>2))       //判断光标值的范围
        {
            CursorRecord =1;
        }
        CursorRecord+=1;
        if (CursorRecord >2)
        {
            CursorRecord =1;
        }
    }
    if (( Keyvalue.value ==KEY_CA)&&(Keyvalue.resp ==1)  )                 //取消键
    {
        Keyvalue.resp =0;
        ScreenRecord.ra3 =0;
      
        CursorRecord =CursorPRecord2;
        Clear_PSG();
    }
    if (( Keyvalue.value ==KEY_CO)&&(Keyvalue.resp ==1) )                  //确认键
    {
        Keyvalue.resp =0;
        ScreenRecord.ra3 = 0;
        CursorRecord =CursorPRecord2;
        Clear_PSG();
    }

}




void Menu_1_2 (void)			//二级  用户信息   按键管理
{
    if (( CursorRecord <1)||(CursorRecord>3))       //判断光标值的范围
    {
        CursorRecord =1;
    }
    if ((( Keyvalue.value ==KEY_ML)||(Keyvalue.value ==KEY_MU))&&(Keyvalue.resp ==1))      //上移   左移
    {
       Keyvalue.resp =0;
       if (( CursorRecord <1)||(CursorRecord>3))       //判断光标值的范围
       {
            CursorRecord =1;
       }
        CursorRecord-=1;
        if (CursorRecord <1)
        {
            CursorRecord =3;
        }
    }
    if ((( Keyvalue.value ==KEY_MD)||(Keyvalue.value ==KEY_MR))&&(Keyvalue.resp ==1))      //下移 右移
    {
        Keyvalue.resp =0;
        if (( CursorRecord <1)||(CursorRecord>3))       //判断光标值的范围
        {
            CursorRecord =1;
        }
        CursorRecord+=1;
        if (CursorRecord >3)
        {
            CursorRecord =1;
        }
    }
    if (( Keyvalue.value ==KEY_CA)&&(Keyvalue.resp ==1)  )                 //取消键
    {
        Keyvalue.resp =0;
        ScreenRecord.ra2 =0;
        CursorRecord =CursorPRecord1;
        Clear_PSG();
    }
    if (( Keyvalue.value ==KEY_CO)&&(Keyvalue.resp ==1) )                  //确认键
    {
        Keyvalue.resp =0;
        ScreenRecord.ra3 = CursorRecord;
        CursorPRecord2 =CursorRecord;
        CursorRecord =1;
    }

}




void Menu_1_2_1 (void)     //用户参数
{
	INT16U	BackVal =0;

	
	if (PressInData.FilterErr !=0)	//上一次密码输入错误，本次只清提示框
	{
		PressInData.FilterErr =0;
	}
	else
	{
		if (( CursorRecord <1)||(CursorRecord>10))       //判断光标值的范围
		{
			CursorRecord =1;
		}
		
		if (( Keyvalue.value ==KEY_ML)&&(Keyvalue.resp ==1)) //左移
		{
			Keyvalue.resp =0;
			if (( CursorRecord <1)||(CursorRecord>10))    //判断光标值的范围
			{
				CursorRecord =1;
			}
			CursorRecord-=1;
			if (CursorRecord <1)
			{
				CursorRecord =10;
			}
		}
		if ((Keyvalue.value ==KEY_MR)&&(Keyvalue.resp ==1)) //右移
		{
			Keyvalue.resp =0;
			if ((CursorRecord <1)||(CursorRecord>10))       //判断光标值的范围
			{
				CursorRecord =1;
			}
			CursorRecord+=1;
			if (CursorRecord >10)
			{
				CursorRecord =1;
			}
		}
		
		if ((Keyvalue.value ==KEY_MU)&&(Keyvalue.resp ==1))//上移
		{
			Keyvalue.resp =0;
			switch ( CursorRecord)
			{
				case 1://序号百位
				{
					PressInData.PSG1++;
					if (PressInData.PSG1 >2)
					{
						PressInData.PSG1 =0;
					}
				};break;
				case 2://序号十位
				{
					PressInData.PSG2++;
					if (PressInData.PSG2 >9)
					{
						PressInData.PSG2 =0;
						PressInData.PSG1++;
						if (PressInData.PSG1 >2)
						{
							PressInData.PSG1 =0;
						}	
					}
				};break;
				case 3://序号个位
				{
					PressInData.PSG3++;
					if (PressInData.PSG3 >9)
					{
						PressInData.PSG3 =0;
						PressInData.PSG2++;
						if (PressInData.PSG2 >9)
						{
							PressInData.PSG2 =0;
							PressInData.PSG1++;
							if (PressInData.PSG1 >2)
							{
								PressInData.PSG1 =0;
							}
						}
					}
				};break;
				case 4://楼号十位
				{
					PressInData.PSG4++;
					if (PressInData.PSG4 >9)
					{
						PressInData.PSG4 =0;
					}
				};break;
				case 5://楼号个位
				{
					PressInData.PSG5++;
					if (PressInData.PSG5 >9)
					{
						PressInData.PSG5 =0;
					}
				};break;
				 case 6://单元
				{
					PressInData.PSG6++;
					if (PressInData.PSG6 >9)
					{
						PressInData.PSG6 =1;
					}
				};break;
				
				 case 7://楼层十位
				{
					PressInData.PSG7++;
					if (PressInData.PSG7 >9)
					{
						PressInData.PSG7 =0;
					}
				};break;
				
				 case 8://楼层个位
				{
					PressInData.PSG8++;
					if (PressInData.PSG8 >9)
					{
						PressInData.PSG8 =0;
					}
				};break;
				
				 case 9://房间十位
				{
					PressInData.PSG9++;
					if (PressInData.PSG9 >5)
					{
						PressInData.PSG9 =0;
					}
				};break;
				 case 10://房间个位
				{
					PressInData.PSG10++;
					if (PressInData.PSG10>9)
					{
						PressInData.PSG10=0;
					}
				};break;
				default: break;
			}
		}
		
		if ((Keyvalue.value ==KEY_MD)&&(Keyvalue.resp ==1))      //下移
		{
			Keyvalue.resp =0;
			switch ( CursorRecord)
			{
				case 1://序号百位
				{
					if ( PressInData.PSG1 ==0)
					{
						PressInData.PSG1 =2;
					}
					else
					{
						PressInData.PSG1 --;
					}
				};break;

				case 2://序号十位
				{
					if ( PressInData.PSG2 ==0)
					{
						PressInData.PSG2 =9;
					}
					else
					{
						PressInData.PSG2 --;
					}
				}break;
				case 3://序号个位
				{
					if ( PressInData.PSG3 ==0)
					{
						PressInData.PSG3 =9;
					}
					else
					{
						PressInData.PSG3 --;
					}
				}break;
				case 4://楼号十位
				{
					if ( PressInData.PSG4 ==0)
					{
						PressInData.PSG4 =9;
					}
					else
					{
						PressInData.PSG4 --;
					}
				}break;
				case 5://楼号个位
				{
					if ( PressInData.PSG5 ==0)
					{
						PressInData.PSG5 =9;
					}
					else
					{
						PressInData.PSG5 --;
					}
				}break;
				case 6://单元
				{
					if ( PressInData.PSG6 ==1)
					{
						PressInData.PSG6 =9;
					}
					else
					{
						PressInData.PSG6 --;
					}
				}break;
				case 7://层号十位
				{
					if ( PressInData.PSG7 ==0)
					{
						PressInData.PSG7 =9;
					}
					else
					{
						PressInData.PSG7 --;
					}
				}break;
				case 8://层号个位
				{
					if ( PressInData.PSG8 ==0)
					{
						PressInData.PSG8 =9;
					}
					else
					{
						PressInData.PSG8 --;
					}
				}break;
				case 9://房间十位
				{
					if ( PressInData.PSG9 ==0)
					{
						PressInData.PSG9 =9;
					}
					else
					{
						PressInData.PSG9 --;
					}
				}break;
				case 10://房间个位
				{
					if ( PressInData.PSG10==0)
					{
						PressInData.PSG10=9;
					}
					else
					{
						PressInData.PSG10--;
					}
				}break;
				default:break;
			}
		}


		//用户序号
		PressInData.Num_User  =PressInData.PSG1*100+PressInData.PSG2*10+PressInData.PSG3;
		if ( PressInData.Num_User>SysPara.UserNum)
		{
			PressInData.Num_User=1;
			PressInData.PSG1 =0;
			PressInData.PSG2 =0;
			PressInData.PSG3 =1;
		}
		if ( PressInData.Num_User<1)
		{
			PressInData.Num_User=1;
			PressInData.PSG1 =0;
			PressInData.PSG2 =0;
			PressInData.PSG3 =1;
		}

		//楼号
		PressInData.Buld=PressInData.PSG4*10+PressInData.PSG5;
		if ( PressInData.Buld >99)
		{
			PressInData.Buld =99;
			PressInData.PSG4 =9;
			PressInData.PSG5 =9;
		}
		if ( PressInData.Buld <1)
		{
			PressInData.Buld =1;
			PressInData.PSG4 =0;
			PressInData.PSG5 =1;
		}

		//单元号
		PressInData.Unit=PressInData.PSG6;
		if ( PressInData.Unit>9)
		{
			PressInData.Unit =9;
			PressInData.PSG6 =9;
		}
		if ( PressInData.Unit<1)
		{
			PressInData.Unit =1;
			PressInData.PSG6 =1;
		}

		//楼层号
		PressInData.Floor=PressInData.PSG7*10 +PressInData.PSG8;
		if ( PressInData.Floor>60)
		{
			PressInData.Floor=60;
			PressInData.PSG7 =6;
			PressInData.PSG8 =0;
		}
		if ( PressInData.Floor<1)
		{
			PressInData.Floor=1;
			PressInData.PSG7 =0;
			PressInData.PSG8 =1;
		}
		//房间号
		PressInData.Cell=PressInData.PSG9*10+PressInData.PSG10;
		if ( PressInData.Cell>10)
		{
			PressInData.Cell=10;
			PressInData.PSG9 =1;
			PressInData.PSG10 =0;
		}
		if ( PressInData.Cell<1)
		{
			PressInData.Cell=1;
			PressInData.PSG9 =0;
			PressInData.PSG10 =1;
		}
		if (( Keyvalue.value ==KEY_CA)&&(Keyvalue.resp ==1)  )                 //取消键
		{
			Keyvalue.resp =0;
			ScreenRecord.ra3 =0;
			CursorRecord =CursorPRecord2;
			
		}
		if (( Keyvalue.value ==KEY_CO)&&(Keyvalue.resp ==1) )                  //确认键
		{
			Keyvalue.resp =0;
			if (CursorRecord >3)
			{
				BackVal=User_Filter(PressInData.Buld,PressInData.Unit,PressInData.Floor,PressInData.Cell,SysPara.UserNum);//楼号  单元号 楼层号  房间号    房间数量

				if (( BackVal ==0)||( BackVal >SysPara.UserNum))
				{
					PressInData.FilterErr =1;
					CursorRecord =4;
				}
				else
				{
					PressInData.Num_User= BackVal;	//传递用户序号
					PressInData.PSG1 =PressInData.Num_User/100;
					PressInData.PSG2 =PressInData.Num_User%100/10;
					PressInData.PSG3 =PressInData.Num_User%10;
					
				}
			}
		}
	}

}











void Menu_1_2_2 (void)     //用户状态
{
	INT16U	BackVal =0;
	if (PressInData.FilterErr !=0)	//上一次密码输入错误，本次只清提示框
	{
		PressInData.FilterErr =0;
	}
	else
	{	
		if (( CursorRecord <1)||(CursorRecord>10))       //判断光标值的范围
		{
			CursorRecord =1;
		}
		
		if (( Keyvalue.value ==KEY_ML)&&(Keyvalue.resp ==1)) //左移
		{
			Keyvalue.resp =0;
			if (( CursorRecord <1)||(CursorRecord>10))    //判断光标值的范围
			{
				CursorRecord =1;
			}
			CursorRecord-=1;
			if (CursorRecord <1)
			{
				CursorRecord =10;
			}
		}
		if ((Keyvalue.value ==KEY_MR)&&(Keyvalue.resp ==1)) //右移
		{
			Keyvalue.resp =0;
			if ((CursorRecord <1)||(CursorRecord>10))       //判断光标值的范围
			{
				CursorRecord =1;
			}
			CursorRecord+=1;
			if (CursorRecord >10)
			{
				CursorRecord =1;
			}
		}
		
		if ((Keyvalue.value ==KEY_MU)&&(Keyvalue.resp ==1))//上移
		{
			Keyvalue.resp =0;
			switch ( CursorRecord)
			{
				case 1://序号百位
				{
					PressInData.PSG1++;
					if (PressInData.PSG1 >2)
					{
						PressInData.PSG1 =0;
					}
				};break;
				case 2://序号十位
				{
					PressInData.PSG2++;
					if (PressInData.PSG2 >9)
					{
						PressInData.PSG2 =0;
						PressInData.PSG1++;
						if (PressInData.PSG1 >2)
						{
							PressInData.PSG1 =0;
						}	
					}
				};break;
				case 3://序号个位
				{
					PressInData.PSG3++;
					if (PressInData.PSG3 >9)
					{
						PressInData.PSG3 =0;
						PressInData.PSG2++;
						if (PressInData.PSG2 >9)
						{
							PressInData.PSG2 =0;
							PressInData.PSG1++;
							if (PressInData.PSG1 >2)
							{
								PressInData.PSG1 =0;
							}
						}
					}
				};break;


				
				case 4://楼号十位
				{
					PressInData.PSG4++;
					if (PressInData.PSG4 >9)
					{
						PressInData.PSG4 =0;
					}
				};break;
				case 5://楼号个位
				{
					PressInData.PSG5++;
					if (PressInData.PSG5 >9)
					{
						PressInData.PSG5 =0;
					}
				};break;

				
				 case 6://单元
				{
					PressInData.PSG6++;
					if (PressInData.PSG6 >9)
					{
						PressInData.PSG6 =1;
					}
				};break;
				 case 7://楼层十位
				{
					PressInData.PSG7++;
					if (PressInData.PSG7 >9)
					{
						PressInData.PSG7 =0;
					}
				};break;
				 case 8://楼层个位
				{
					PressInData.PSG8++;
					if (PressInData.PSG8 >9)
					{
						PressInData.PSG8 =0;
					}
				};break;
				
				 case 9://房间十位
				{
					PressInData.PSG9++;
					if (PressInData.PSG9 >5)
					{
						PressInData.PSG9 =0;
					}
				};break;
				 case 10://房间个位
				{
					PressInData.PSG10++;
					if (PressInData.PSG10>9)
					{
						PressInData.PSG10=0;
					}
				};break;
				default: break;
			}
		}
		if ((Keyvalue.value ==KEY_MD)&&(Keyvalue.resp ==1))      //下移
		{
			Keyvalue.resp =0;
			switch ( CursorRecord)
			{
				case 1://序号百位
				{
					if ( PressInData.PSG1 ==0)
					{
						PressInData.PSG1 =2;
					}
					else
					{
						PressInData.PSG1 --;
					}
				};break;

				case 2://序号十位
				{
					if ( PressInData.PSG2 ==0)
					{
						PressInData.PSG2 =9;
					}
					else
					{
						PressInData.PSG2 --;
					}
				}break;
				case 3://序号个位
				{
					if ( PressInData.PSG3 ==0)
					{
						PressInData.PSG3 =9;
					}
					else
					{
						PressInData.PSG3 --;
					}
				}break;
				case 4://楼号十位
				{
					if ( PressInData.PSG4 ==0)
					{
						PressInData.PSG4 =9;
					}
					else
					{
						PressInData.PSG4 --;
					}
				}break;
				case 5://楼号个位
				{
					if ( PressInData.PSG5 ==0)
					{
						PressInData.PSG5 =9;
					}
					else
					{
						PressInData.PSG5 --;
					}
				}break;
				case 6://单元
				{
					if ( PressInData.PSG6 ==1)
					{
						PressInData.PSG6 =9;
					}
					else
					{
						PressInData.PSG6 --;
					}
				}break;
				case 7://层号十位
				{
					if ( PressInData.PSG7 ==0)
					{
						PressInData.PSG7 =9;
					}
					else
					{
						PressInData.PSG7 --;
					}
				}break;
				case 8://层号个位
				{
					if ( PressInData.PSG8 ==0)
					{
						PressInData.PSG8 =9;
					}
					else
					{
						PressInData.PSG8 --;
					}
				}break;
				case 9://房间十位
				{
					if ( PressInData.PSG9 ==0)
					{
						PressInData.PSG9 =9;
					}
					else
					{
						PressInData.PSG9 --;
					}
				}break;
				case 10://房间个位
				{
					if ( PressInData.PSG10==0)
					{
						PressInData.PSG10=9;
					}
					else
					{
						PressInData.PSG10--;
					}
				}break;
				default:break;
			}
		}

		PressInData.Num_User  =PressInData.PSG1*100+PressInData.PSG2*10+PressInData.PSG3;
		if ( PressInData.Num_User>SysPara.UserNum)
		{
			PressInData.Num_User=1;
			PressInData.PSG1 =0;
			PressInData.PSG2 =0;
			PressInData.PSG3 =1;
		}
		if ( PressInData.Num_User<1)
		{
			PressInData.Num_User=1;
			PressInData.PSG1 =0;
			PressInData.PSG2 =0;
			PressInData.PSG3 =1;
		}
		
		PressInData.Buld=PressInData.PSG4*10+PressInData.PSG5;
		if ( PressInData.Buld >99)
		{
			PressInData.Buld =99;
			PressInData.PSG4 =9;
			PressInData.PSG5 =9;
		}
		if ( PressInData.Buld <1)
		{
			PressInData.Buld =1;
			PressInData.PSG4 =0;
			PressInData.PSG5 =1;
		}
		
		PressInData.Unit=PressInData.PSG6;
		if ( PressInData.Unit>9)
		{
			PressInData.Unit =9;
			PressInData.PSG6 =9;
		}
		if ( PressInData.Unit<1)
		{
			PressInData.Unit =1;
			PressInData.PSG6 =1;
		}

		
		PressInData.Floor=PressInData.PSG7*10 +PressInData.PSG8;
		if ( PressInData.Floor>60)
		{
			PressInData.Floor=60;
			PressInData.PSG7 =6;
			PressInData.PSG8 =0;
		}
		if ( PressInData.Floor<1)
		{
			PressInData.Floor=1;
			PressInData.PSG7 =0;
			PressInData.PSG8 =1;
		}
		
		PressInData.Cell=PressInData.PSG9*10+PressInData.PSG10;
		if ( PressInData.Cell>10)
		{
			PressInData.Cell=10;
			PressInData.PSG9 =1;
			PressInData.PSG10 =0;
		}
		
		if ( PressInData.Cell<1)
		{
			PressInData.Cell=1;
			PressInData.PSG9 =0;
			PressInData.PSG10 =1;
		}


		if (( Keyvalue.value ==KEY_CA)&&(Keyvalue.resp ==1)  )                 //取消键
		{
			Keyvalue.resp =0;
			ScreenRecord.ra3 =0;
			CursorRecord =CursorPRecord2;
		}
		if (( Keyvalue.value ==KEY_CO)&&(Keyvalue.resp ==1) )                  //确认键
		{
			Keyvalue.resp =0;
			if (CursorRecord >3)
			{
				BackVal=User_Filter(PressInData.Buld,PressInData.Unit,PressInData.Floor,PressInData.Cell,SysPara.UserNum);//楼号  单元号 楼层号  房间号    房间数量
				if (( BackVal ==0)||( BackVal >SysPara.UserNum))
				{
					PressInData.FilterErr =1;
					CursorRecord =4;
				}
				else
				{
					PressInData.Num_User= BackVal;	//传递用户序号
					PressInData.PSG1 =PressInData.Num_User/100;
					PressInData.PSG2 =PressInData.Num_User%100/10;
					PressInData.PSG3 =PressInData.Num_User%10;
				}
			}
		}
	}
}




void Menu_1_2_3 (void)     //计量信息
{
	INT16U	BackVal =0;
	if (PressInData.FilterErr !=0)	//上一次密码输入错误，本次只清提示框
	{
		PressInData.FilterErr =0;
	}
	else
	{
		if (( CursorRecord <1)||(CursorRecord>10))       //判断光标值的范围
		{
			CursorRecord =1;
		}
		
		if (( Keyvalue.value ==KEY_ML)&&(Keyvalue.resp ==1)) //左移
		{
			Keyvalue.resp =0;
			if (( CursorRecord <1)||(CursorRecord>10))    //判断光标值的范围
			{
				CursorRecord =1;
			}
			CursorRecord-=1;
			if (CursorRecord <1)
			{
				CursorRecord =10;
			}
		}
		
		if ((Keyvalue.value ==KEY_MR)&&(Keyvalue.resp ==1)) //右移
		{
			Keyvalue.resp =0;
			if ((CursorRecord <1)||(CursorRecord>10))       //判断光标值的范围
			{
				CursorRecord =1;
			}
			CursorRecord+=1;
			if (CursorRecord >10)
			{
				CursorRecord =1;
			}
		}
		
		if ((Keyvalue.value ==KEY_MU)&&(Keyvalue.resp ==1))//上移
		{
			Keyvalue.resp =0;
			switch ( CursorRecord)
			{
				case 1://序号百位
				{
					PressInData.PSG1++;
					if (PressInData.PSG1 >2)
					{
						PressInData.PSG1 =0;
					}
				};break;
				case 2://序号十位
				{
					PressInData.PSG2++;
					if (PressInData.PSG2 >9)
					{
						PressInData.PSG2 =0;
						PressInData.PSG1++;
						if (PressInData.PSG1 >2)
						{
							PressInData.PSG1 =0;
						}	
					}
				};break;
				case 3://序号个位
				{
					PressInData.PSG3++;
					if (PressInData.PSG3 >9)
					{
						PressInData.PSG3 =0;
						PressInData.PSG2++;
						if (PressInData.PSG2 >9)
						{
							PressInData.PSG2 =0;
							PressInData.PSG1++;
							if (PressInData.PSG1 >2)
							{
								PressInData.PSG1 =0;
							}
						}
					}
				};break;
				case 4://楼号十位
				{
					PressInData.PSG4++;
					if (PressInData.PSG4 >9)
					{
						PressInData.PSG4 =0;
					}
				};break;
				case 5://楼号个位
				{
					PressInData.PSG5++;
					if (PressInData.PSG5 >9)
					{
						PressInData.PSG5 =0;
					}
				};break;

				
				 case 6://单元
				{
					PressInData.PSG6++;
					if (PressInData.PSG6 >9)
					{
						PressInData.PSG6 =1;
					}
				};break;

				
				 case 7://楼层十位
				{
					PressInData.PSG7++;
					if (PressInData.PSG7 >9)
					{
						PressInData.PSG7 =0;
					}
				};break;
				 case 8://楼层个位
				{
					PressInData.PSG8++;
					if (PressInData.PSG8 >9)
					{
						PressInData.PSG8 =0;
					}
				};break;
				
				 case 9://房间十位
				{
					PressInData.PSG9++;
					if (PressInData.PSG9 >5)
					{
						PressInData.PSG9 =0;
					}
				};break;
				 case 10://房间个位
				{
					PressInData.PSG10++;
					if (PressInData.PSG10>9)
					{
						PressInData.PSG10=0;
					}
				};break;
				default: break;
			}
		}
		if ((Keyvalue.value ==KEY_MD)&&(Keyvalue.resp ==1))      //下移
		{
			Keyvalue.resp =0;
			switch ( CursorRecord)
			{
				case 1://序号百位
				{
					if ( PressInData.PSG1 ==0)
					{
						PressInData.PSG1 =2;
					}
					else
					{
						PressInData.PSG1 --;
					}
				};break;

				case 2://序号十位
				{
					if ( PressInData.PSG2 ==0)
					{
						PressInData.PSG2 =9;
					}
					else
					{
						PressInData.PSG2 --;
					}
				}break;
				case 3://序号个位
				{
					if ( PressInData.PSG3 ==0)
					{
						PressInData.PSG3 =9;
					}
					else
					{
						PressInData.PSG3 --;
					}
				}break;
				case 4://楼号十位
				{
					if ( PressInData.PSG4 ==0)
					{
						PressInData.PSG4 =9;
					}
					else
					{
						PressInData.PSG4 --;
					}
				}break;
				case 5://楼号个位
				{
					if ( PressInData.PSG5 ==0)
					{
						PressInData.PSG5 =9;
					}
					else
					{
						PressInData.PSG5 --;
					}
				}break;
				case 6://单元
				{
					if ( PressInData.PSG6 ==1)
					{
						PressInData.PSG6 =9;
					}
					else
					{
						PressInData.PSG6 --;
					}
				}break;
				case 7://层号十位
				{
					if ( PressInData.PSG7 ==0)
					{
						PressInData.PSG7 =9;
					}
					else
					{
						PressInData.PSG7 --;
					}
				}break;
				case 8://层号个位
				{
					if ( PressInData.PSG8 ==0)
					{
						PressInData.PSG8 =9;
					}
					else
					{
						PressInData.PSG8 --;
					}
				}break;
				case 9://房间十位
				{
					if ( PressInData.PSG9 ==0)
					{
						PressInData.PSG9 =9;
					}
					else
					{
						PressInData.PSG9 --;
					}
				}break;
				case 10://房间个位
				{
					if ( PressInData.PSG10==0)
					{
						PressInData.PSG10=9;
					}
					else
					{
						PressInData.PSG10--;
					}
				}break;
				default:break;
			}
		}

		PressInData.Num_User  =PressInData.PSG1*100+PressInData.PSG2*10+PressInData.PSG3;
		if ( PressInData.Num_User>SysPara.UserNum)
		{
			PressInData.Num_User=1;
			PressInData.PSG1 =0;
			PressInData.PSG2 =0;
			PressInData.PSG3 =1;
		}
		if ( PressInData.Num_User<1)
		{
			PressInData.Num_User=1;
			PressInData.PSG1 =0;
			PressInData.PSG2 =0;
			PressInData.PSG3 =1;
		}
		
		PressInData.Buld=PressInData.PSG4*10+PressInData.PSG5;
		if ( PressInData.Buld >99)
		{
			PressInData.Buld =99;
			PressInData.PSG4 =9;
			PressInData.PSG5 =9;
		}
		if ( PressInData.Buld <1)
		{
			PressInData.Buld =1;
			PressInData.PSG4 =0;
			PressInData.PSG5 =1;
		}
		
		PressInData.Unit=PressInData.PSG6;
		if ( PressInData.Unit>9)
		{
			PressInData.Unit =9;
			PressInData.PSG6 =9;
		}
		if ( PressInData.Unit<1)
		{
			PressInData.Unit =1;
			PressInData.PSG6 =1;
		}

		
		PressInData.Floor=PressInData.PSG7*10 +PressInData.PSG8;
		if ( PressInData.Floor>60)
		{
			PressInData.Floor=60;
			PressInData.PSG7 =6;
			PressInData.PSG8 =0;
		}
		if ( PressInData.Floor<1)
		{
			PressInData.Floor=1;
			PressInData.PSG7 =0;
			PressInData.PSG8 =1;
		}
		
		PressInData.Cell=PressInData.PSG9*10+PressInData.PSG10;
		if ( PressInData.Cell>10)
		{
			PressInData.Cell=10;
			PressInData.PSG9 =1;
			PressInData.PSG10 =0;
		}
		
		if ( PressInData.Cell<1)
		{
			PressInData.Cell=1;
			PressInData.PSG9 =0;
			PressInData.PSG10 =1;
		}


		if (( Keyvalue.value ==KEY_CA)&&(Keyvalue.resp ==1)  )                 //取消键
		{
			Keyvalue.resp =0;
			ScreenRecord.ra3 =0;
			CursorRecord =CursorPRecord2;
		}
		if (( Keyvalue.value ==KEY_CO)&&(Keyvalue.resp ==1) )                  //确认键
		{
			Keyvalue.resp =0;
			if (CursorRecord >3)
			{
				BackVal=User_Filter(PressInData.Buld,PressInData.Unit,PressInData.Floor,PressInData.Cell,SysPara.UserNum);//楼号  单元号 楼层号  房间号    房间数量

				if (( BackVal ==0)||( BackVal >SysPara.UserNum))
				{
					PressInData.FilterErr =1;
					CursorRecord =4;
				}
				else
				{
					PressInData.Num_User= BackVal;	//传递用户序号
					PressInData.PSG1 =PressInData.Num_User/100;
					PressInData.PSG2 =PressInData.Num_User%100/10;
					PressInData.PSG3 =PressInData.Num_User%10;
				}
			}
		}

	}
}



void Menu_1_3 (void)			//二级  系统设置   按键管理
{
    if (( CursorRecord <1)||(CursorRecord>7))       //判断光标值的范围
    {
        CursorRecord =1;
    }
    if ((( Keyvalue.value ==KEY_ML)||(Keyvalue.value ==KEY_MU))&&(Keyvalue.resp ==1))      //上移   左移
    {
       Keyvalue.resp =0;
       if (( CursorRecord <1)||(CursorRecord>7))       //判断光标值的范围
       {
            CursorRecord =1;
       }
        CursorRecord-=1;
        if (CursorRecord <1)
        {
            CursorRecord =5;
        }
    }
    if ((( Keyvalue.value ==KEY_MD)||(Keyvalue.value ==KEY_MR))&&(Keyvalue.resp ==1))      //下移 右移
    {
        Keyvalue.resp =0;
        if (( CursorRecord <1)||(CursorRecord>7))       //判断光标值的范围
        {
            CursorRecord =1;
        }
        CursorRecord+=1;
        if (CursorRecord >5)
        {
            CursorRecord =1;
        }
    }
    if (( Keyvalue.value ==KEY_CA)&&(Keyvalue.resp ==1)  )                 //取消键
    {
        Keyvalue.resp =0;
        ScreenRecord.ra2 =0;
        CursorRecord =CursorPRecord1;
    }
    if (( Keyvalue.value ==KEY_CO)&&(Keyvalue.resp ==1) )                  //确认键
    {
        Keyvalue.resp =0;
        ScreenRecord.ra3 = CursorRecord;
        CursorPRecord2 =CursorRecord;
        CursorRecord =1;
    }

}





void Menu_1_3_PassWord (void)     //参数密码输入界面
{
    if (PressInData.PSWErr !=0)	//上一次密码输入错误，本次只清提示框
    {
        PressInData.PSWErr =0;
    }
    else
    {
        
        if (( CursorRecord <1)||(CursorRecord>4))       //判断光标值的范围
        {
            CursorRecord =1;
        }
        if (( Keyvalue.value ==KEY_ML)&&(Keyvalue.resp ==1))    //左移
        {
            Keyvalue.resp =0;
            PressInData.PSWErr =0;
            if (( CursorRecord <1)||(CursorRecord>4))          //判断光标值的范围
            {
                CursorRecord =1;
            }
            CursorRecord-=1;
            if (CursorRecord <1)
            {
                CursorRecord =4;
            }
        }
        if ((Keyvalue.value ==KEY_MR)&&(Keyvalue.resp ==1))     //右移
        {
            Keyvalue.resp =0;
            PressInData.PSWErr =0;
            if (( CursorRecord <1)||(CursorRecord>4))       //判断光标值的范围
            {
                CursorRecord =1;
            }
            CursorRecord+=1;
            if (CursorRecord >4)
            {
                CursorRecord =1;
            }
        }
        if ((Keyvalue.value ==KEY_MU)&&(Keyvalue.resp ==1))     //上移
        {
            Keyvalue.resp =0;
            PressInData.PSWErr =0;
            switch ( CursorRecord)
            {
                case 1:
                {
                    PressInData.PSG1++;
                    if (PressInData.PSG1 >15)
                    {
                        PressInData.PSG1 =0;
                    }
                };break;
                case 2:
                {
                    PressInData.PSG2++;
                    if (PressInData.PSG2 >15)
                    {
                        PressInData.PSG2 =0;
                    }
                };break;
                case 3:
                {
                    PressInData.PSG3++;
                    if (PressInData.PSG3 >15)
                    {
                        PressInData.PSG3 =0;
                    }
                };break;
                case 4:
                {
                    PressInData.PSG4++;
                    if (PressInData.PSG4 >15)
                    {
                        PressInData.PSG4 =0;
                    }
                };break;
                default: break;
            }
        }
        if ((Keyvalue.value ==KEY_MD)&&(Keyvalue.resp ==1))     //下移
        {
            Keyvalue.resp =0;
            PressInData.PSWErr =0;
            switch ( CursorRecord)
            {
                case 1:
                {
                    if ( PressInData.PSG1 ==0)
                    {
                        PressInData.PSG1 =15;
                    }
                    else
                    {
                        PressInData.PSG1 --;
                    }
                };break;

                case 2:
                {
                    if ( PressInData.PSG2 ==0)
                    {
                        PressInData.PSG2 =15;
                    }
                    else
                    {
                        PressInData.PSG2 --;
                    }
                };break;
                case 3:
                {
                    if ( PressInData.PSG3 ==0)
                    {
                        PressInData.PSG3 =15;
                    }
                    else
                    {
                        PressInData.PSG3 --;
                    }
                };break;
                case 4:
                {
                    if ( PressInData.PSG4 ==0)
                    {
                        PressInData.PSG4 =15;
                    }
                    else
                    {
                        PressInData.PSG4 --;
                    }
                };break;
            }  
        }
        PressInData.password =  (PressInData.PSG1<<12)+ (PressInData.PSG2<<8)+(PressInData.PSG3<<4)+ PressInData.PSG4;
        
        if (( Keyvalue.value ==KEY_CA)&&(Keyvalue.resp ==1)  )                 //取消键
        {
            Keyvalue.resp =0;
            if ( PressInData.PSWErr !=0)	//上一次密码输入错误，本次只清提示框
            {
                PressInData.PSWErr =0;
            }
            else
            {

			ScreenRecord.ra3 =0;
			CursorRecord =CursorPRecord2;
			PressInData.password =0;
			PressInData.correct =0;
			Clear_PSG();
            }
        }
        if (( Keyvalue.value ==KEY_CO)&&(Keyvalue.resp ==1) )                  //确认键
        {
            Keyvalue.resp =0;
            if ( PressInData.PSWErr !=0)	//上一次密码输入错误，本次只清提示框
            {
                PressInData.PSWErr =0;
            }
            else
            {
                if ( PressInData.password ==0X1100)		//超级用户
                {
                    PressInData.correct =1;
                    PressInData.password =0;
                    CursorRecord =1;
        //            Clear_PSG();
                }
                else if ( PressInData.password ==SysPara.PassWord)	//普通用户
                {
                    PressInData.correct =1;
                    PressInData.password =0;
                    CursorRecord =1;
      //              Clear_PSG();
                }
                else
                {
                    PressInData.correct =0;
                    PressInData.PSWErr =1;
//					Clear_PSG();
                }
            }
        }
    }   
}


void Menu_1_3_1 (void)     //通信设置 按键处理
{
	INT8U Reflag =0X00;
	
	Reflag =Reflag;
	if (PressInData.E2RomErr !=0)	//上一次密码输入错误，本次只清提示框
	{
		PressInData.E2RomErr =0;
	}
	else
	{
		if (PressInData.FirstInFlag ==0 )
		{
		
			PressInData.IP1 =SysPara.IP1;
			PressInData.PSG1 =PressInData.IP1/100 ;
			PressInData.PSG2 =PressInData.IP1 %100/10;
			PressInData.PSG3 =PressInData.IP1 %10;
			
			PressInData.IP2 =SysPara.IP2;
			PressInData.PSG4 =PressInData.IP2/100 ;
			PressInData.PSG5 =PressInData.IP2 %100/10;
			PressInData.PSG6 =PressInData.IP2 %10;	
			
			PressInData.IP3 =SysPara.IP3;
			PressInData.PSG7 =PressInData.IP3/100 ;
			PressInData.PSG8 =PressInData.IP3 %100/10;
			PressInData.PSG9 =PressInData.IP3 %10;
			
			PressInData.IP4 =SysPara.IP4;
			PressInData.PSG10 =PressInData.IP4/100 ;
			PressInData.PSG11 =PressInData.IP4 %100/10;
			PressInData.PSG12 =PressInData.IP4 %10;	
			
			PressInData.PORT =SysPara.PortNum;
			PressInData.PSG13 =PressInData.PORT/10000;
			PressInData.PSG14 =PressInData.PORT%10000/1000;
			PressInData.PSG15 =PressInData.PORT%1000 /100;
			PressInData.PSG16 =PressInData.PORT%100/10;
			PressInData.PSG17 =PressInData.PORT%10;
			
			PressInData.FirstInFlag =1;
			
			
		}
		if (( CursorRecord <1)||(CursorRecord>23))       //判断光标值的范围
		{
			CursorRecord =1;
		}
		
		if (( Keyvalue.value ==KEY_ML)&&(Keyvalue.resp ==1)) //左移
		{
			Keyvalue.resp =0;
			if (( CursorRecord <1)||(CursorRecord>17))    //判断光标值的范围
			{
				CursorRecord =1;
			}
			CursorRecord-=1;
			if (CursorRecord <1)
			{
				CursorRecord =17;
			}
		}
		
		if ((Keyvalue.value ==KEY_MR)&&(Keyvalue.resp ==1)) //右移
		{
			Keyvalue.resp =0;
			if ((CursorRecord <1)||(CursorRecord>17))       //判断光标值的范围
			{
				CursorRecord =1;
			}
			CursorRecord+=1;
			if (CursorRecord >17)
			{
				CursorRecord =1;
			}
		}
		
		if ((Keyvalue.value ==KEY_MU)&&(Keyvalue.resp ==1))//上移
		{
			Keyvalue.resp =0;
			switch ( CursorRecord)
			{
				case 1://IP1百位
				{
					PressInData.PSG1++;
					if (PressInData.PSG1 >2)
					{
						PressInData.PSG1 =0;
					}
				};break;
				case 2://IP1十位
				{
					PressInData.PSG2++;
					if (PressInData.PSG2 >9)
					{
						PressInData.PSG2 =0;
					}
				};break;
				case 3://IP1个位
				{
					PressInData.PSG3++;
					if (PressInData.PSG3 >9)
					{
						PressInData.PSG3 =0;
					}
				};break;


				
				case 4://IP2百位
				{
					PressInData.PSG4++;
					if (PressInData.PSG4 >2)
					{
						PressInData.PSG4 =0;
					}
				};break;
				case 5://IP2十位
				{
					PressInData.PSG5++;
					if (PressInData.PSG5 >9)
					{
						PressInData.PSG5 =0;
					}
				};break;
				 case 6://IP2个位
				{
					PressInData.PSG6++;
					if (PressInData.PSG6 >9)
					{
						PressInData.PSG6 =0;
					}
				};break;

				case 7://IP3百位
				{
					PressInData.PSG7++;
					if (PressInData.PSG7 >2)
					{
						PressInData.PSG7 =0;
					}
				};break;
				case 8://IP3十位
				{
					PressInData.PSG8++;
					if (PressInData.PSG8 >9)
					{
						PressInData.PSG8 =0;
					}
				};break;
				 case 9://IP3个位
				{
					PressInData.PSG9++;
					if (PressInData.PSG9 >9)
					{
						PressInData.PSG9 =0;
					}
				};break;	
				
				case 10://IP4百位
				{
					PressInData.PSG10++;
					if (PressInData.PSG10 >2)
					{
						PressInData.PSG10 =0;
					}
				};break;
				case 11://IP4十位
				{
					PressInData.PSG11++;
					if (PressInData.PSG11 >9)
					{
						PressInData.PSG11 =0;
					}
				};break;
				 case 12://IP4个位
				{
					PressInData.PSG12++;
					if (PressInData.PSG12 >9)
					{
						PressInData.PSG12 =0;
					}
				};break;	

				 case 13://PORT
				{
					PressInData.PSG13++;
					if (PressInData.PSG13 >6)
					{
						PressInData.PSG13 =0;
					}
				};break;	
				
				case 14://PORT
				{
					PressInData.PSG14++;
					if (PressInData.PSG14 >9)
					{
						PressInData.PSG14 =0;
					}
				};break;
				
				case 15://PORT
				{
					PressInData.PSG15++;
					if (PressInData.PSG15 >9)
					{
						PressInData.PSG15 =0;
					}
				};break;
				case 16://PORT
				{
					PressInData.PSG16++;
					if (PressInData.PSG16 >9)
					{
						PressInData.PSG16 =0;
					}
				};break;	
				
				case 17://PORT
				{
					PressInData.PSG17++;
					if (PressInData.PSG17 >9)
					{
						PressInData.PSG17 =0;
					}
				};break;				

				default: break;
			}
		}
		if ((Keyvalue.value ==KEY_MD)&&(Keyvalue.resp ==1))      //下移
		{
			Keyvalue.resp =0;
			switch ( CursorRecord)
			{
				case 1://IP1
				{
					if ( PressInData.PSG1 ==0)
					{
						PressInData.PSG1 =2;
					}
					else
					{
						PressInData.PSG1 --;
					}
				};break;

				case 2://IP1
				{
					if ( PressInData.PSG2 ==0)
					{
						PressInData.PSG2 =9;
					}
					else
					{
						PressInData.PSG2 --;
					}
				}break;
				case 3://IP1
				{
					if ( PressInData.PSG3 ==0)
					{
						PressInData.PSG3 =9;
					}
					else
					{
						PressInData.PSG3 --;
					}
				}break;
				case 4://IP2
				{
					if ( PressInData.PSG4 ==0)
					{
						PressInData.PSG4 =2;
					}
					else
					{
						PressInData.PSG4 --;
					}
				}break;
				case 5://IP2
				{
					if ( PressInData.PSG5 ==0)
					{
						PressInData.PSG5 =9;
					}
					else
					{
						PressInData.PSG5 --;
					}
				}break;
				case 6://IP2
				{
					if ( PressInData.PSG6 ==0)
					{
						PressInData.PSG6 =9;
					}
					else
					{
						PressInData.PSG6 --;
					}
				}break;
				case 7://IP3
				{
					if ( PressInData.PSG7 ==0)
					{
						PressInData.PSG7 =2;
					}
					else
					{
						PressInData.PSG7 --;
					}
				}break;
				case 8://IP3
				{
					if ( PressInData.PSG8 ==0)
					{
						PressInData.PSG8 =9;
					}
					else
					{
						PressInData.PSG8 --;
					}
				}break;
				case 9://IP3
				{
					if ( PressInData.PSG9 ==0)
					{
						PressInData.PSG9 =9;
					}
					else
					{
						PressInData.PSG9 --;
					}
				}break;
				case 10://IP4
				{
					if ( PressInData.PSG10==0)
					{
						PressInData.PSG10=2;
					}
					else
					{
						PressInData.PSG10--;
					}
				}break;
				
				case 11://IP4
				{
					if ( PressInData.PSG11 ==0)
					{
						PressInData.PSG11 =9;
					}
					else
					{
						PressInData.PSG11 --;
					}
				};break;

				case 12://IP4
				{
					if ( PressInData.PSG12 ==0)
					{
						PressInData.PSG12 =9;
					}
					else
					{
						PressInData.PSG12 --;
					}
				}break;
				
				case 13://PORT
				{
					if ( PressInData.PSG13 ==0)
					{
						PressInData.PSG13 =6;
					}
					else
					{
						PressInData.PSG13 --;
					}
				}break;
				case 14://PORT
				{
					if ( PressInData.PSG14 ==0)
					{
						PressInData.PSG14 =9;
					}
					else
					{
						PressInData.PSG14 --;
					}
				}break;
				case 15://PORT
				{
					if ( PressInData.PSG15 ==0)
					{
						PressInData.PSG15 =9;
					}
					else
					{
						PressInData.PSG15 --;
					}
				}break;
				case 16://PORT
				{
					if ( PressInData.PSG16 ==0)
					{
						PressInData.PSG16 =9;
					}
					else
					{
						PressInData.PSG16 --;
					}
				}break;
				
				case 17://PORT
				{
					if ( PressInData.PSG17 ==0)
					{
						PressInData.PSG17 =9;
					}
					else
					{
						PressInData.PSG17 --;
					}
				}break;			
				default:break;
			}
		}

		PressInData.IP1 =PressInData.PSG1*100+PressInData.PSG2*10+PressInData.PSG3;
		if (PressInData.IP1 >255)
		{
			PressInData.IP1 =255;
			PressInData.PSG1 =2;
			PressInData.PSG2 =5;
			PressInData.PSG3 =5;
		}
		PressInData.IP2 =PressInData.PSG4*100+PressInData.PSG5*10+PressInData.PSG6;
		if (PressInData.IP2 >255)
		{
			PressInData.IP2 =255;
			PressInData.PSG4 =2;
			PressInData.PSG5 =5;
			PressInData.PSG6 =5;
		}
		
		PressInData.IP3 =PressInData.PSG7*100+PressInData.PSG8*10+PressInData.PSG9;
		if (PressInData.IP3 >255)
		{
			PressInData.IP3 =255;
			PressInData.PSG7 =2;
			PressInData.PSG8 =5;
			PressInData.PSG9 =5;
		}

		PressInData.IP4 =PressInData.PSG10*100+PressInData.PSG11*10+PressInData.PSG12;
		if (PressInData.IP4 >255)
		{
			PressInData.IP4 =255;
			PressInData.PSG10 =2;
			PressInData.PSG11 =5;
			PressInData.PSG12 =5;
		}
		
		PressInData.PORT=PressInData.PSG13*10000+PressInData.PSG14*1000+PressInData.PSG15*100+PressInData.PSG16*10+PressInData.PSG17;
		if (PressInData.PORT >65535 )
		{
			PressInData.PORT =65535;
			PressInData.PSG13 =6;
			PressInData.PSG14 =5;
			PressInData.PSG15 =5;
			PressInData.PSG16 =3;
			PressInData.PSG17 =5;
		}





		if (( Keyvalue.value ==KEY_CA)&&(Keyvalue.resp ==1)  )                 //取消键
		{
			Keyvalue.resp =0;
			ScreenRecord.ra3 =0;
			CursorRecord =CursorPRecord2;
			PressInData.correct =0;
			Clear_PSG();
		}
		if (( Keyvalue.value ==KEY_CO)&&(Keyvalue.resp ==1) )                  //确认键
		{
			Keyvalue.resp =0;
			{
				UART_TO_FY1000_QueueSend_Stru SendBuffer;
				SysPara.IP1 =PressInData.IP1;
				SysPara.IP2 =PressInData.IP2;
				SysPara.IP3 =PressInData.IP3;
				SysPara.IP4 =PressInData.IP4;
				SysPara.PortNum =PressInData.PORT;

				SendBuffer.SendData.Pack_0X40.COMFlag=0X8877665544332211;
				SendBuffer.SendData.Pack_0X40.IP1 =SysPara.IP1;
				SendBuffer.SendData.Pack_0X40.IP2 =SysPara.IP2;
				SendBuffer.SendData.Pack_0X40.IP3 =SysPara.IP3;
				SendBuffer.SendData.Pack_0X40.IP4 =SysPara.IP4;
				SendBuffer.SendData.Pack_0X40.PortNum=SysPara.PortNum;
				FY_1000Send_Code_QInput(&SendBuffer,0X40);
				
	
				
				if(SysPara_Update() ==HAL_OK)      //写参数
				{
					PressInData.FirstInFlag =0;
					PressInData.E2RomErr =0;
					ScreenRecord.ra3 =0;
					CursorRecord =CursorPRecord2;
					Clear_PSG();
				}
				else
				{
					CursorRecord =1;
					PressInData.E2RomErr =1;
				}			
			}
		}
	}
}


int setServerIP( uint8_t IP1, uint8_t IP2, uint8_t IP3, uint8_t IP4, uint16_t PORT )
{
	UART_TO_FY1000_QueueSend_Stru SendBuffer;

	/* 将服务器地址信息保存到参数区 */
	SysPara.IP1 = IP1;
	SysPara.IP2 = IP2;
	SysPara.IP3 = IP3;
	SysPara.IP4 = IP4;
	SysPara.PortNum = PORT;

	if(SysPara_Update() != HAL_OK)      //写参数
	{
		return -3;
	}

	/* 设置GSM模块地址 */
	SendBuffer.SendData.Pack_0X40.COMFlag=0X8877665544332211;
	SendBuffer.SendData.Pack_0X40.IP1 =SysPara.IP1;
	SendBuffer.SendData.Pack_0X40.IP2 =SysPara.IP2;
	SendBuffer.SendData.Pack_0X40.IP3 =SysPara.IP3;
	SendBuffer.SendData.Pack_0X40.IP4 =SysPara.IP4;
	SendBuffer.SendData.Pack_0X40.PortNum=SysPara.PortNum;
	if(pdTRUE != FY_1000Send_Code_QInput(&SendBuffer,0X40))
	{
		return -4;
	}

	return 0;
}

APP_UI_EXT void getServerIP( uint8_t *IP1, uint8_t *IP2, uint8_t *IP3, uint8_t *IP4, uint16_t *PORT )
{
	*IP1 = SysPara.IP1;
	*IP2 = SysPara.IP2;
	*IP3 = SysPara.IP3;
	*IP4 = SysPara.IP4;
	*PORT = SysPara.PortNum;
}


void Menu_1_3_4 (void)     //时间设置输入界面
{
    INT8U Reflag =0X00;
	if ( PressInData.E2RomErr !=0)
	{
		PressInData.E2RomErr =0;
	}
	else
	{
		if (PressInData.FirstInFlag ==0 )
		{
			PressInData.C_Year =RTC_Time.Year -2000;         	//传递年份
			if (PressInData.C_Year>99)						//范围判断
			{
				PressInData.C_Year =0;
			}
			PressInData.PSG1 =PressInData.C_Year/10;
			PressInData.PSG2 =PressInData.C_Year%10;

			PressInData.C_Month =RTC_Time.Month ;		        //传递月份数据
			if((PressInData.C_Month>12)	||(PressInData.C_Month ==0))	//范围判断
			{
				PressInData.C_Month=1;
			}
			PressInData.PSG3 =PressInData.C_Month/10;
			PressInData.PSG4 =PressInData.C_Month%10;

			PressInData.C_Day =RTC_Time.Day;		            //传递日定值
			if ((PressInData.C_Day>31)||(PressInData.C_Day ==0))		//范围判断
			{
				PressInData.C_Day =1;
			}
			PressInData.PSG5 =PressInData.C_Day/10;
			PressInData.PSG6 =PressInData.C_Day%10;

			PressInData.C_Hour =RTC_Time.Hour;		            	//传递时定值
			if ((PressInData.C_Hour>23))		//范围判断
			{
				PressInData.C_Hour =0;
			}
			PressInData.PSG7 =PressInData.C_Hour/10;
			PressInData.PSG8 =PressInData.C_Hour%10;

			PressInData.C_Minute =RTC_Time.Minute;		            //传递分定值
			if ((PressInData.C_Minute>59))		//范围判断
			{
				PressInData.C_Minute =0;
			}
			PressInData.PSG9 =PressInData.C_Minute/10;
			PressInData.PSG10 =PressInData.C_Minute%10;

			PressInData.C_Second =RTC_Time.Second;		            //传递秒定值
			if ((PressInData.C_Second>59))		//范围判断
			{
				PressInData.C_Second =0;
			}
			PressInData.PSG11 =PressInData.C_Second/10;
			PressInData.PSG12 =PressInData.C_Second%10;

			PressInData.C_Week =RTC_Time.Week;						//传递周定值
			if ( PressInData.C_Week >6)
			{
				PressInData.C_Week =0;
			}
			PressInData.PSG13 =PressInData.C_Week;



			//供暖开始时间设置
			PressInData.S_Year =SysPara.StartTime.Year-2000;			//传递起始年份
			if (PressInData.S_Year>99)								//范围判断
			{
				PressInData.S_Year =0;
			}
			PressInData.PSG14 =PressInData.S_Year/10;
			PressInData.PSG15 =PressInData.S_Year%10;

			PressInData.S_Month =SysPara.StartTime.Month;			//传递月份数据
			if((PressInData.S_Month>12)	||(PressInData.S_Month ==0))		//范围判断
			{
				PressInData.S_Month=1;
			}
			PressInData.PSG16 =PressInData.S_Month/10;
			PressInData.PSG17 =PressInData.S_Month%10;

			PressInData.S_Day =SysPara.StartTime.Day;			//传递日定值
			if ((PressInData.S_Day>31)||(PressInData.S_Day ==0))		//范围判断
			{
				PressInData.S_Day =1;
			}
			PressInData.PSG18 =PressInData.S_Day/10;
			PressInData.PSG19 =PressInData.S_Day%10;

		//供暖结束时间设置
			PressInData.F_Year =SysPara.FinalTime.Year-2000;		//传递起始年份
			if (PressInData.F_Year>99)							//范围判断
			{
				PressInData.F_Year =0;
			}
			PressInData.PSG20 =PressInData.F_Year/10;
			PressInData.PSG21 =PressInData.F_Year%10;


			PressInData.F_Month =SysPara.FinalTime.Month;			//传递月份数据
			if((PressInData.F_Month>12)	||(PressInData.F_Month ==0))		//范围判断
			{
				PressInData.F_Month=1;
			}
			PressInData.PSG22 =PressInData.F_Month/10;
			PressInData.PSG23 =PressInData.F_Month%10;


			PressInData.F_Day =SysPara.FinalTime.Day;			//传递日定值
			if ((PressInData.F_Day>31)||(PressInData.F_Day ==0))		//范围判断
			{
				PressInData.F_Day =1;
			}
			PressInData.PSG24 =PressInData.F_Day/10;
			PressInData.PSG25 =PressInData.F_Day%10;

			PressInData.FirstInFlag =1;		//标志置位，下次不再计算
		}

		if (( CursorRecord <1)||(CursorRecord>25))       //判断光标值的范围
		{
			CursorRecord =1;
		}
		
		if (( Keyvalue.value ==KEY_ML)&&(Keyvalue.resp ==1)) //左移
		{
		   Keyvalue.resp =0;
		   if (( CursorRecord <1)||(CursorRecord>25))          //判断光标值的范围
		   {
				CursorRecord =1;
		   }
			CursorRecord-=1;
			if (CursorRecord <1)
			{
				CursorRecord =25;
			}
		}
		
		if ((Keyvalue.value ==KEY_MR)&&(Keyvalue.resp ==1)) //右移
		{
			Keyvalue.resp =0;
			if ((CursorRecord <1)||(CursorRecord>24))       //判断光标值的范围
			{
				CursorRecord =1;
			}
			CursorRecord+=1;
			if (CursorRecord >25)
			{
				CursorRecord =1;
			}
		}
		if ((Keyvalue.value ==KEY_MU)&&(Keyvalue.resp ==1))      //上移
		{
			Keyvalue.resp =0;
			switch ( CursorRecord)
			{
				case 1:
				{
					PressInData.PSG1++;
					if (PressInData.PSG1 >9)
					{
						PressInData.PSG1 =0;
					}
				};break;
				case 2:
				{
					PressInData.PSG2++;
					if (PressInData.PSG2 >9)
					{
						PressInData.PSG2 =0;
					}
				};break;
				case 3:
				{
					PressInData.PSG3++;
					if (PressInData.PSG3 >1)
					{
						PressInData.PSG3 =0;
					}
				};break;
				case 4:
				{
					PressInData.PSG4++;
					if (PressInData.PSG4 >9)
					{
						PressInData.PSG4 =0;
					}
				};break;
				case 5:
				{
					PressInData.PSG5++;
					if (PressInData.PSG5 >3)
					{
						PressInData.PSG5 =0;
					}
				};break;
				 case 6:
				{
					PressInData.PSG6++;
					if (PressInData.PSG6 >9)
					{
						PressInData.PSG6 =0;
					}
				};break;
				 case 7:
				{
					PressInData.PSG7++;
					if (PressInData.PSG7 >2)
					{
						PressInData.PSG7 =0;
					}
				};break;
				 case 8:
				{
					PressInData.PSG8++;
					if (PressInData.PSG8 >9)
					{
						PressInData.PSG8 =0;
					}
				};break;
				 case 9:
				{
					PressInData.PSG9++;
					if (PressInData.PSG9 >5)
					{
						PressInData.PSG9 =0;
					}
				};break;
				 case 10:
				{
					PressInData.PSG10++;
					if (PressInData.PSG10 >9)
					{
						PressInData.PSG10 =0;
					}
				};break;
				 case 11:
				{
					PressInData.PSG11++;
					if (PressInData.PSG11 >5)
					{
						PressInData.PSG11 =0;
					}
				};break;
				 case 12:
				{
					PressInData.PSG12++;
					if (PressInData.PSG12 >9)
					{
						PressInData.PSG12 =0;
					}
				};break;
				 case 13:
				{
					PressInData.PSG13++;
					if (PressInData.PSG13 >6)
					{
						PressInData.PSG13 =0;
					}
				};break;

				case 14:
				{
					PressInData.PSG14++;
					if (PressInData.PSG14 >9)
					{
						PressInData.PSG14 =0;
					}
				};break;
				case 15:
				{
					PressInData.PSG15++;
					if (PressInData.PSG15 >9)
					{
						PressInData.PSG15 =0;
					}
				};break;
				case 16:
				{
					PressInData.PSG16++;
					if (PressInData.PSG16 >1)
					{
						PressInData.PSG16 =0;
					}
				};break;
				case 17:
				{
					PressInData.PSG17++;
					if (PressInData.PSG17 >9)
					{
						PressInData.PSG17 =0;
					}
				};break;
				case 18:
				{
					PressInData.PSG18++;
					if (PressInData.PSG18 >3)
					{
						PressInData.PSG18 =0;
					}
				};break;
				 case 19:
				{
					PressInData.PSG19++;
					if (PressInData.PSG19 >9)
					{
						PressInData.PSG19 =0;
					}
				};break;

				case 20:
				{
					PressInData.PSG20++;
					if (PressInData.PSG20 >9)
					{
						PressInData.PSG20 =0;
					}
				};break;
				case 21:
				{
					PressInData.PSG21++;
					if (PressInData.PSG21 >9)
					{
						PressInData.PSG21 =0;
					}
				};break;
				case 22:
				{
					PressInData.PSG22++;
					if (PressInData.PSG22 >1)
					{
						PressInData.PSG22 =0;
					}
				};break;
				case 23:
				{
					PressInData.PSG23++;
					if (PressInData.PSG23 >9)
					{
						PressInData.PSG23 =0;
					}
				};break;
				case 24:
				{
					PressInData.PSG24++;
					if (PressInData.PSG24 >3)
					{
						PressInData.PSG24 =0;
					}
				};break;
				 case 25:
				{
					PressInData.PSG25++;
					if (PressInData.PSG25 >9)
					{
						PressInData.PSG25 =0;
					}
				};break;				
				default: break;
			}
		}
		if ((Keyvalue.value ==KEY_MD)&&(Keyvalue.resp ==1))      //下移
		{
			Keyvalue.resp =0;
			switch ( CursorRecord)
			{
				case 1:
				{
					if ( PressInData.PSG1 ==0)
					{
						PressInData.PSG1 =9;
					}
					else
					{
						PressInData.PSG1 --;
					}
				};break;

				case 2:
				{
					if ( PressInData.PSG2 ==0)
					{
						PressInData.PSG2 =9;
					}
					else
					{
						PressInData.PSG2 --;
					}
				}break;
				case 3:
				{
					if ( PressInData.PSG3 ==0)
					{
						PressInData.PSG3 =1;
					}
					else
					{
						PressInData.PSG3 --;
					}
				}break;
				case 4:
				{
					if ( PressInData.PSG4 ==0)
					{
						PressInData.PSG4 =9;
					}
					else
					{
						PressInData.PSG4 --;
					}
				}break;
				case 5:
				{
					if ( PressInData.PSG5 ==0)
					{
						PressInData.PSG5 =3;
					}
					else
					{
						PressInData.PSG5 --;
					}
				}break;
				case 6:
				{
					if ( PressInData.PSG6 ==0)
					{
						PressInData.PSG6 =9;
					}
					else
					{
						PressInData.PSG6 --;
					}
				}break;
				case 7:
				{
					if ( PressInData.PSG7 ==0)
					{
						PressInData.PSG7 =2;
					}
					else
					{
						PressInData.PSG7 --;
					}
				}break;
				case 8:
				{
					if ( PressInData.PSG8 ==0)
					{
						PressInData.PSG8 =9;
					}
					else
					{
						PressInData.PSG8 --;
					}
				}break;
				case 9:
				{
					if ( PressInData.PSG9 ==0)
					{
						PressInData.PSG9 =5;
					}
					else
					{
						PressInData.PSG9 --;
					}
				}break;
				case 10:
				{
					if ( PressInData.PSG10 ==0)
					{
						PressInData.PSG10 =9;
					}
					else
					{
						PressInData.PSG10 --;
					}
				}break;
				case 11:
				{
					if ( PressInData.PSG11 ==0)
					{
						PressInData.PSG11 =5;
					}
					else
					{
						PressInData.PSG11 --;
					}
				}break;
				case 12:
				{
					if ( PressInData.PSG12 ==0)
					{
						PressInData.PSG12 =9;
					}
					else
					{
						PressInData.PSG12 --;
					}
				}break;
				case 13:
				{
					if ( PressInData.PSG13 ==0)
					{
						PressInData.PSG13 =6;
					}
					else
					{
						PressInData.PSG13 --;
					}
				}break;

				case 14:
				{
					if ( PressInData.PSG14 ==0)
					{
						PressInData.PSG14 =9;
					}
					else
					{
						PressInData.PSG14 --;
					}
				};break;

				case 15:
				{
					if ( PressInData.PSG15 ==0)
					{
						PressInData.PSG15 =9;
					}
					else
					{
						PressInData.PSG15 --;
					}
				}break;
				case 16:
				{
					if ( PressInData.PSG16 ==0)
					{
						PressInData.PSG16 =1;
					}
					else
					{
						PressInData.PSG16 --;
					}
				}break;
				case 17:
				{
					if ( PressInData.PSG17 ==0)
					{
						PressInData.PSG17 =9;
					}
					else
					{
						PressInData.PSG17 --;
					}
				}break;
				case 18:
				{
					if ( PressInData.PSG18 ==0)
					{
						PressInData.PSG18 =3;
					}
					else
					{
						PressInData.PSG18 --;
					}
				}break;
				case 19:
				{
					if ( PressInData.PSG19 ==0)
					{
						PressInData.PSG19 =9;
					}
					else
					{
						PressInData.PSG19 --;
					}
				}break;


				case 20:
				{
					if ( PressInData.PSG20 ==0)
					{
						PressInData.PSG20 =9;
					}
					else
					{
						PressInData.PSG20 --;
					}
				};break;

				case 21:
				{
					if ( PressInData.PSG21 ==0)
					{
						PressInData.PSG21 =9;
					}
					else
					{
						PressInData.PSG21 --;
					}
				}break;
				case 22:
				{
					if ( PressInData.PSG22 ==0)
					{
						PressInData.PSG22 =1;
					}
					else
					{
						PressInData.PSG22 --;
					}
				}break;
				case 23:
				{
					if ( PressInData.PSG23 ==0)
					{
						PressInData.PSG23 =9;
					}
					else
					{
						PressInData.PSG23 --;
					}
				}break;
				case 24:
				{
					if ( PressInData.PSG24 ==0)
					{
						PressInData.PSG24 =3;
					}
					else
					{
						PressInData.PSG24--;
					}
				}break;
				case 25:
				{
					if ( PressInData.PSG25 ==0)
					{
						PressInData.PSG25 =9;
					}
					else
					{
						PressInData.PSG25 --;
					}
				}break;
				
				default:break;
			}
		}

		PressInData.C_Year  =PressInData.PSG1*10+PressInData.PSG2;
		if (( PressInData.C_Year>99)||( PressInData.C_Year<15))
		{
			PressInData.C_Year=15;
			PressInData.PSG1 =1;
			PressInData.PSG2 =5;
		}
		PressInData.C_Month  =PressInData.PSG3*10+PressInData.PSG4;
		if (( PressInData.C_Month >12)||( PressInData.C_Month <1))
		{
			PressInData.C_Month =01;
			PressInData.PSG3 =0;
			PressInData.PSG4 =1;
		}
		PressInData.C_Day =PressInData.PSG5*10+PressInData.PSG6;
		if (( PressInData.C_Day >31)||( PressInData.C_Day <1))
		{
			PressInData.C_Day =1;
			PressInData.PSG5 =0;
			PressInData.PSG6 =1;
		}
		PressInData.C_Hour =PressInData.PSG7*10 +PressInData.PSG8;
		if ( PressInData.C_Hour >23)
		{
			PressInData.C_Hour =00;
			PressInData.PSG7 =0;
			PressInData.PSG8 =0;
		}
		PressInData.C_Minute =PressInData.PSG9*10+PressInData.PSG10;
		if ( PressInData.C_Minute >59)
		{
			PressInData.C_Minute =00;
			PressInData.PSG9 =0;
			PressInData.PSG10 =0;
		}
		PressInData.C_Second =PressInData.PSG11*10+PressInData.PSG12;
		if ( PressInData.C_Second >59)
		{
			PressInData.C_Second =00;
			PressInData.PSG11 =0;
			PressInData.PSG12 =0;
		}
		PressInData.C_Week = PressInData.PSG13;
		if( PressInData.C_Week>6)
		{
			PressInData.C_Week =0;
			PressInData.PSG13 =0;
		}

		PressInData.S_Year  =PressInData.PSG14*10+PressInData.PSG15;
		if (( PressInData.S_Year>99)||( PressInData.S_Year<15))
		{
			PressInData.S_Year=15;
			PressInData.PSG14 =1;
			PressInData.PSG15 =5;
		}
		PressInData.S_Month  =PressInData.PSG16*10+PressInData.PSG17;
		if (( PressInData.S_Month >12)||( PressInData.S_Month <1))
		{
			PressInData.S_Month =01;
			PressInData.PSG16 =0;
			PressInData.PSG17 =1;
		}
		PressInData.S_Day =PressInData.PSG18*10+PressInData.PSG19;
		if (( PressInData.S_Day >31)||( PressInData.S_Day <1))
		{
			PressInData.S_Day =1;
			PressInData.PSG18 =0;
			PressInData.PSG19 =1;
		}

		PressInData.F_Year  =PressInData.PSG20*10+PressInData.PSG21;
		if (( PressInData.F_Year>99)||( PressInData.F_Year<15))
		{
			PressInData.F_Year=15;
			PressInData.PSG20 =1;
			PressInData.PSG21 =5;
		}
		PressInData.F_Month  =PressInData.PSG22*10+PressInData.PSG23;
		if (( PressInData.F_Month >12)||( PressInData.F_Month <1))
		{
			PressInData.F_Month =01;
			PressInData.PSG22 =0;
			PressInData.PSG23 =1;
		}
		PressInData.F_Day =PressInData.PSG24*10+PressInData.PSG25;
		if (( PressInData.F_Day >31)||( PressInData.F_Day <1))
		{
			PressInData.F_Day =1;
			PressInData.PSG24 =0;
			PressInData.PSG25 =1;
		}


		if (( Keyvalue.value ==KEY_CA)&&(Keyvalue.resp ==1)  )                 //取消键
		{
			Keyvalue.resp =0;
			PressInData.FirstInFlag =0;
			ScreenRecord.ra3 =0;
			CursorRecord =CursorPRecord2;
			Clear_PSG();
		}
		
		if (( Keyvalue.value ==KEY_CO)&&(Keyvalue.resp ==1) )                  //确认键
		{
			Keyvalue.resp =0;
			PressInData.FirstInFlag =0;

			RTC_Time.Year =PressInData.C_Year+2000;
			RTC_Time.Month =PressInData.C_Month;
			RTC_Time.Day =PressInData.C_Day;
			RTC_Time.Hour =PressInData.C_Hour;
			RTC_Time.Minute =PressInData.C_Minute;
			RTC_Time.Second =PressInData.C_Second;
			RTC_Time.Week =PressInData.C_Week;

			Reflag = PCF8563_Set(&RTC_Time);
			if (Reflag==0 )
			{
				SysPara.StartTime.Year =PressInData.S_Year+2000;
				SysPara.StartTime.Month=PressInData.S_Month;
				SysPara.StartTime.Day=PressInData.S_Day;
				SysPara.StartTime.Hour =0;
				SysPara.StartTime.Minute=0;
				SysPara.StartTime.Second=0;

				SysPara.FinalTime.Year =PressInData.F_Year+2000;
				SysPara.FinalTime.Month=PressInData.F_Month;
				SysPara.FinalTime.Day=PressInData.F_Day;
				SysPara.FinalTime.Hour =0;
				SysPara.FinalTime.Minute=0;
				SysPara.FinalTime.Second=0;				
				if(SysPara_Update() ==HAL_OK)
				{
					ScreenRecord.ra3 =0;
					CursorRecord =CursorPRecord2;
					Clear_PSG();
				}
				else
				{
					PressInData.E2RomErr =1;
				}
			}
			else
			{
				PressInData.E2RomErr =1;
			}
		}
	}
}





void Menu_1_3_5 (void)     //密码设置输入界面
{
	if (PressInData.PSWErr !=0)	//上一次密码输入错误，本次只清提示框
	{
		PressInData.PSWErr =0;
	}
	else
	{
		INT8U Reflag =0X00;
		Reflag=Reflag;
		if ( PressInData.FirstInFlag ==0)
		{
			PressInData.PSG1 =PressInData.PSG2 =PressInData.PSG3 =PressInData.PSG4 =PressInData.PSG5 =PressInData.PSG6 =PressInData.PSG7 =PressInData.PSG8 =0;
			PressInData.FirstInFlag =1;
		}
		if (( CursorRecord <1)||(CursorRecord>8))       //判断光标值的范围
		{
			CursorRecord =1;
		}
		if (( Keyvalue.value ==KEY_ML)&&(Keyvalue.resp ==1)) //左移
		{
			PressInData.PSWErr =0;
			Keyvalue.resp =0;
			if (( CursorRecord <1)||(CursorRecord>8))          //判断光标值的范围
			{
				CursorRecord =1;
			}
			CursorRecord-=1;
			if (CursorRecord <1)
			{
				CursorRecord =8;
			}
		}
		if ((Keyvalue.value ==KEY_MR)&&(Keyvalue.resp ==1))         //右移
		{
			PressInData.PSWErr =0;
			Keyvalue.resp =0;
			if ((CursorRecord <1)||(CursorRecord>8))                //判断光标值的范围
			{
				CursorRecord =1;
			}
			CursorRecord+=1;
			if (CursorRecord >8)
			{
				CursorRecord =1;
			}
		}
		if ((Keyvalue.value ==KEY_MU)&&(Keyvalue.resp ==1))      //上移
		{
			Keyvalue.resp =0;
			PressInData.PSWErr =0;
			switch ( CursorRecord)
			{
				case 1:
				{
					PressInData.PSG1++;
					if (PressInData.PSG1 >15)
					{
						PressInData.PSG1 =0;
					}
				};break;
				case 2:
				{
					PressInData.PSG2++;
					if (PressInData.PSG2 >15)
					{
						PressInData.PSG2 =0;
					}
				};break;
				case 3:
				{
					PressInData.PSG3++;
					if (PressInData.PSG3 >15)
					{
						PressInData.PSG3 =0;
					}
				};break;
				case 4:
				{
					PressInData.PSG4++;
					if (PressInData.PSG4 >15)
					{
						PressInData.PSG4 =0;
					}
				};break;
				case 5:
				{
					PressInData.PSG5++;
					if (PressInData.PSG5 >15)
					{
						PressInData.PSG5 =0;
					}
				};break;
				 case 6:
				{
					PressInData.PSG6++;
					if (PressInData.PSG6 >15)
					{
						PressInData.PSG6 =0;
					}
				};break;
				 case 7:
				{
					PressInData.PSG7++;
					if (PressInData.PSG7 >15)
					{
						PressInData.PSG7 =0;
					}
				};break;
				 case 8:
				{
					PressInData.PSG8++;
					if (PressInData.PSG8 >15)
					{
						PressInData.PSG8 =0;
					}
				};break;
				default: break;
			}
		}
		if ((Keyvalue.value ==KEY_MD)&&(Keyvalue.resp ==1))      //下移
		{
			Keyvalue.resp =0;
			PressInData.PSWErr =0;
			switch ( CursorRecord)
			{
				case 1:
				{
					if ( PressInData.PSG1 ==0)
					{
						PressInData.PSG1 =15;
					}
					else
					{
						PressInData.PSG1 --;
					}
				};break;

				case 2:
				{
					if ( PressInData.PSG2 ==0)
					{
						PressInData.PSG2 =15;
					}
					else
					{
						PressInData.PSG2 --;
					}
				}break;
				case 3:
				{
					if ( PressInData.PSG3 ==0)
					{
						PressInData.PSG3 =15;
					}
					else
					{
						PressInData.PSG3 --;
					}
				}break;
				case 4:
				{
					if ( PressInData.PSG4 ==0)
					{
						PressInData.PSG4 =15;
					}
					else
					{
						PressInData.PSG4 --;
					}
				}break;
				case 5:
				{
					if ( PressInData.PSG5 ==0)
					{
						PressInData.PSG5 =15;
					}
					else
					{
						PressInData.PSG5 --;
					}
				}break;
				case 6:
				{
					if ( PressInData.PSG6 ==0)
					{
						PressInData.PSG6 =15;
					}
					else
					{
						PressInData.PSG6 --;
					}
				}break;
				case 7:
				{
					if ( PressInData.PSG7 ==0)
					{
						PressInData.PSG7 =15;
					}
					else
					{
						PressInData.PSG7 --;
					}
				}break;
				case 8:
				{
					if ( PressInData.PSG8 ==0)
					{
						PressInData.PSG8 =15;
					}
					else
					{
						PressInData.PSG8 --;
					}
				}break;
				default:break;
			}
		}
		PressInData.PSW1  =(PressInData.PSG1<<12)+ (PressInData.PSG2<<8)+(PressInData.PSG3<<4)+ PressInData.PSG4;
		PressInData.PSW2  =(PressInData.PSG5<<12)+ (PressInData.PSG6<<8)+(PressInData.PSG7<<4)+ PressInData.PSG8;
		
		if (( Keyvalue.value ==KEY_CA)&&(Keyvalue.resp ==1)  )                 //取消键
		{
			Keyvalue.resp =0;
			if ( PressInData.PSWErr !=0)	//上一次密码输入错误，本次只清提示框
			{
				PressInData.PSWErr =0;
			}
			else
			{
//				PressInData.FirstInFlag =0;
				ScreenRecord.ra3 =0;
				CursorRecord =CursorPRecord2;
	//			PressInData.correct =0;
				Clear_PSG();				
			}
		}
		if (( Keyvalue.value ==KEY_CO)&&(Keyvalue.resp ==1) )                  //确认键
		{
			Keyvalue.resp =0;
			if ( PressInData.PSWErr !=0)	//上一次密码输入错误，本次只清提示框
			{
				PressInData.PSWErr =0;
			}
			else
			{
				if (( PressInData.PSW1 ==PressInData.PSW2))    //上下两段密码正确且不为零
				{
				
					SysPara.PassWord= PressInData.PSW1;
					if(SysPara_Update() ==HAL_OK)       	//写系统参数
					{
						
						
						//密码设置后应该返回密码输入前界面（验证重复登录）
						ScreenRecord.ra3 =0;
						PressInData.correct =0;
						PressInData.password =0;
						CursorRecord =CursorPRecord2;
						Clear_PSG();
					}
					else
					{
						CursorRecord =1;
						PressInData.PSWErr =1;
					}
				}
				else
				{
					CursorRecord =1;
					PressInData.PSWErr =1;
				}
			}
		}
	}
}







void Menu_1_3_6(void)
{
	HAL_StatusTypeDef Reflag =HAL_OK;
	if (( CursorRecord <1)||(CursorRecord>2))            //判断光标值的范围
	{
		CursorRecord =1;
	}
	
	if ((( Keyvalue.value ==KEY_ML)||(Keyvalue.value ==KEY_MU))&&(Keyvalue.resp ==1))      //上移   左移
	{
		Keyvalue.resp =0;
		if (( CursorRecord <1)||(CursorRecord>2))       //判断光标值的范围
		{
			CursorRecord =1;
		}
		CursorRecord-=1;
		if (CursorRecord <1)
		{
			CursorRecord =2;
		}
	}
	
	if ((( Keyvalue.value ==KEY_MD)||(Keyvalue.value ==KEY_MR))&&(Keyvalue.resp ==1))      //下移 右移
	{
		Keyvalue.resp =0;
		if (( CursorRecord <1)||(CursorRecord>2))//判断光标值的范围
		{
    			CursorRecord =1;
    		}
		CursorRecord+=1;
		if (CursorRecord >2)
		{
			CursorRecord =1;
		}
	}
	if (( Keyvalue.value ==KEY_CA)&&(Keyvalue.resp ==1)) //取消键
	{
		Keyvalue.resp =0;
		ScreenRecord.ra3 =0;
		CursorRecord =CursorPRecord2;
		Clear_PSG();
		PressInData.password =0;
		PressInData.correct =0;
	}
	
	if (( Keyvalue.value ==KEY_CO)&&(Keyvalue.resp ==1))//确认键
	{
		Keyvalue.resp =0;
		if (CursorRecord ==1)
		{
			Reflag = SysPara_Reset();		//系统参数初始化
			if (Reflag ==HAL_OK)
			{
				
				Reflag = SysUserList_Reset();	//用户参数列表初始化
				if (Reflag ==HAL_OK)
				{
					
					Reflag =UserData_ResetALL(MAXUser_Num);
					if(Reflag ==HAL_OK)		//用户数据初始化
					{
						
						Reflag =SysDevData_ResetALL(MAXDevice_Num);	//系统设备数据初始化
						if(Reflag ==HAL_OK)
						{
						
							Reflag =SysDeviceList_Reset();						
						}
					}
				}
			}
			if (Reflag==HAL_OK)
			{
				ScreenRecord.ra3 =0;
				CursorRecord =CursorPRecord2;
				Clear_PSG();
			}
			else
			{
				CursorRecord =0;
				PressInData.E2RomErr =1;
				
			}
		}
		else
		{
			ScreenRecord.ra3 =0;
			CursorRecord =CursorPRecord2;
			Clear_PSG();
			PressInData.password =0;
			PressInData.correct =0;
		}

	}

}



void Menu_1_3_7 (void)     //设备类型设置界面
{
    HAL_StatusTypeDef Reflag =HAL_OK;
	if ( PressInData.E2RomErr !=0)
	{
		PressInData.E2RomErr =0;
	}
	else
	{
		if (PressInData.FirstInFlag ==0 )
		{
			PressInData.DeviceType =SysPara.DeviceType;     //传递设备类型
			if ((PressInData.DeviceType>3)||(PressInData.DeviceType==0))	//范围判断
			{
				PressInData.DeviceType =0;
			}
			PressInData.Device_SN =SysPara.Device_SN;
			
			PressInData.PSG1 =(PressInData.Device_SN>>28)&0X0F;
			PressInData.PSG2 =(PressInData.Device_SN>>24)&0X0F;
			
			PressInData.PSG3 =(PressInData.Device_SN>>20)&0X0F;
			PressInData.PSG4 =(PressInData.Device_SN>>16)&0X0F;
			
			PressInData.PSG5 =(PressInData.Device_SN>>12)&0X0F;
			PressInData.PSG6 =(PressInData.Device_SN>>8)&0X0F;
			
			PressInData.PSG7 =(PressInData.Device_SN>>4)&0X0F;
			PressInData.PSG8 =(PressInData.Device_SN>>0)&0X0F;
			CursorRecord =1;
			PressInData.FirstInFlag =1;		//标志置位，下次不再计算
		}

		if (( CursorRecord <1)||(CursorRecord>9))       //判断光标值的范围
		{
			CursorRecord =1;
		}

		if (( Keyvalue.value ==KEY_ML)&&(Keyvalue.resp ==1)) //左移
		{
			Keyvalue.resp =0;
			if (( CursorRecord <1)||(CursorRecord>9))       //判断光标值的范围
			{
				CursorRecord =1;
			}
			CursorRecord-=1;
			if (CursorRecord <1)
			{
				CursorRecord =9;
			}
		}
		
		if ((Keyvalue.value ==KEY_MR)&&(Keyvalue.resp ==1)) //右移
		{
			Keyvalue.resp =0;
			CursorRecord+=1;
			if (CursorRecord >9)
			{
				CursorRecord =1;
			}
		}
		if ((Keyvalue.value ==KEY_MU)&&(Keyvalue.resp ==1)) //上移
		{
			Keyvalue.resp =0;
			switch ( CursorRecord)
			{
				case 1:
				{
					PressInData.DeviceType++;
					if (PressInData.DeviceType >3)
					{
						PressInData.DeviceType =1;
					}
				};break;
				
				case 2://设备编号1
				{
					PressInData.PSG1++;
					if (PressInData.PSG1 >9)
					{
						PressInData.PSG1 =0;
					}
				};break;
				case 3://设备编号2
				{
					PressInData.PSG2++;
					if (PressInData.PSG2 >9)
					{
						PressInData.PSG2 =0;
					}
				};break;
				case 4://设备编号3
				{
					PressInData.PSG3++;
					if (PressInData.PSG3 >9)
					{
						PressInData.PSG3 =0;
					}
				};break;
				case 5://设备编号4
				{
					PressInData.PSG4++;
					if (PressInData.PSG4 >9)
					{
						PressInData.PSG4 =0;
					}
				};break;
				
				case 6://设备编号5
				{
					PressInData.PSG5++;
					if (PressInData.PSG5 >9)
					{
						PressInData.PSG5 =0;
					}
				};break;
				 case 7://设备编号6
				{
					PressInData.PSG6++;
					if (PressInData.PSG6 >9)
					{
						PressInData.PSG6 =0;
					}
				};break;
				case 8://设备编号7
				{
					PressInData.PSG7++;
					if (PressInData.PSG7 >9)
					{
						PressInData.PSG7 =0;
					}
				};break;
				case 9://设备编号8
				{
					PressInData.PSG8++;
					if (PressInData.PSG8 >9)
					{
						PressInData.PSG8 =0;
					}
				};break;
				default: break;
				
			}

			
		}
		if ((Keyvalue.value ==KEY_MD)&&(Keyvalue.resp ==1))      //下移
		{
			Keyvalue.resp =0;
			switch ( CursorRecord)
			{
				case 1:
				{
					if ( PressInData.DeviceType ==1)
					{
						PressInData.DeviceType =3;
					}
					else
					{
						PressInData.DeviceType --;
					}
				};break;

				case 2: //设备编号1
				{
					if ( PressInData.PSG1 ==0)
					{
						PressInData.PSG1 =9;
					}
					else
					{
						PressInData.PSG1 --;
					}
				}break;
				case 3: //设备编号2
				{
					if ( PressInData.PSG2 ==0)
					{
						PressInData.PSG2 =9;
					}
					else
					{
						PressInData.PSG2 --;
					}
				}break;
				case 4: //设备编号3
				{
					if ( PressInData.PSG3 ==0)
					{
						PressInData.PSG3 =9;
					}
					else
					{
						PressInData.PSG3 --;
					}
				}break;
				case 5: //设备编号4
				{
					if ( PressInData.PSG4 ==0)
					{
						PressInData.PSG4 =9;
					}
					else
					{
						PressInData.PSG4 --;
					}
				}break;
				
				case 6: //设备编号5
				{
					if ( PressInData.PSG5 ==0)
					{
						PressInData.PSG5 =9;
					}
					else
					{
						PressInData.PSG5 --;
					}
				}break;
				case 7: //设备编号6
				{
					if ( PressInData.PSG6 ==0)
					{
						PressInData.PSG6 =9;
					}
					else
					{
						PressInData.PSG6 --;
					}
				}break;
				case 8: //设备编号7
				{
					if ( PressInData.PSG7 ==0)
					{
						PressInData.PSG7 =9;
					}
					else
					{
						PressInData.PSG7 --;
					}
				}break;
				case 9: //设备编号8
				{
					if ( PressInData.PSG8 ==0)
					{
						PressInData.PSG8 =9;
					}
					else
					{
						PressInData.PSG8 --;
					}
				}break;

				default:break;
			}

		}
		PressInData.Device_SN =(PressInData.PSG1<<28)+(PressInData.PSG2<<24)+(PressInData.PSG3<<20)+(PressInData.PSG4<<16)+(PressInData.PSG5<<12)+(PressInData.PSG6<<8)+(PressInData.PSG7<<4)+(PressInData.PSG8<<0);
		if (( Keyvalue.value ==KEY_CA)&&(Keyvalue.resp ==1))   //取消键
		{
			Keyvalue.resp =0;
			ScreenRecord.ra3 =0;
			CursorRecord =CursorPRecord2;
			Clear_PSG();
		}
		
		if (( Keyvalue.value ==KEY_CO)&&(Keyvalue.resp ==1))  //确认键
		{
			Keyvalue.resp =0;
			SysPara.DeviceType = PressInData.DeviceType; //传递设备类型
			SysPara.Device_SN = PressInData.Device_SN;
			Reflag =SysPara_Update();   //数据保存;
			if (Reflag==HAL_OK )
			{
				ScreenRecord.ra3 =0;
				CursorRecord =CursorPRecord2;
				Clear_PSG();
			}
			else
			{
				PressInData.E2RomErr =1;
			}
		}
	}
}


void Menu_1_4 (void)			//二级  热表信息   按键管理
{
    if (( PressInData.PSG1 <1)||(PressInData.PSG1>SysPara.BuldMeterNum))       //判断光标值的范围
    {
        CursorRecord =1;
    }
    if ((( Keyvalue.value ==KEY_MD)||(Keyvalue.value ==KEY_MR))&&(Keyvalue.resp ==1))      //下移 右移
    {
		Keyvalue.resp =0;
		if (( PressInData.PSG1 <1)||(PressInData.PSG1>SysPara.BuldMeterNum))       //判断光标值的范围
		{
		    PressInData.PSG1 =1;
		}
		PressInData.PSG1-=1;
		if (PressInData.PSG1 <1)
		{
		    PressInData.PSG1 =SysPara.BuldMeterNum;
		}
    }

    
    if ((( Keyvalue.value ==KEY_ML)||(Keyvalue.value ==KEY_MU))&&(Keyvalue.resp ==1))      //左移 上移
    {
        Keyvalue.resp =0;
        if (( PressInData.PSG1 <1)||(PressInData.PSG1>SysPara.BuldMeterNum))       //判断光标值的范围
        {
            PressInData.PSG1 =1;
        }
        PressInData.PSG1+=1;
        if (PressInData.PSG1 >SysPara.BuldMeterNum)
        {
            PressInData.PSG1 =1;
        }
    }

	PressInData.Num_BuldMeter =PressInData.PSG1;
	if((PressInData.Num_BuldMeter <1)||(PressInData.Num_BuldMeter>SysPara.BuldMeterNum))
	{
		PressInData.Num_BuldMeter =1;
		PressInData.PSG1 =1;
	}
	
    
    if (( Keyvalue.value ==KEY_CA)&&(Keyvalue.resp ==1)  )                 //取消键
    {
        Keyvalue.resp =0;
        ScreenRecord.ra2 =0;
        CursorRecord =CursorPRecord1;
        Clear_PSG();
    }
    
    if (( Keyvalue.value ==KEY_CO)&&(Keyvalue.resp ==1) )                  //确认键
    {
        Keyvalue.resp =0;
        ScreenRecord.ra3 = 1;
        CursorPRecord2 =1;
        CursorRecord =1;
    }

}


void Menu_1_4_1 (void)			//二级  热表信息   按键管理
{
	if (( PressInData.PSG1 <1)||(PressInData.PSG1>SysPara.BuldMeterNum))       //判断光标值的范围
	{
		CursorRecord =1;
	}
	if ((( Keyvalue.value ==KEY_MD)||(Keyvalue.value ==KEY_MR))&&(Keyvalue.resp ==1))      //下移 右移
	{
		Keyvalue.resp =0;
		if (( PressInData.PSG1 <1)||(PressInData.PSG1>SysPara.BuldMeterNum))       //判断光标值的范围
		{
			PressInData.PSG1 =1;
		}
		PressInData.PSG1-=1;
		if (PressInData.PSG1 <1)
		{
			 PressInData.PSG1 =SysPara.BuldMeterNum;
		}
	 }

	if ((( Keyvalue.value ==KEY_ML)||(Keyvalue.value ==KEY_MU))&&(Keyvalue.resp ==1))      //左移 上移
	{
		Keyvalue.resp =0;
		if (( PressInData.PSG1 <1)||(PressInData.PSG1>SysPara.BuldMeterNum))       //判断光标值的范围
		{
			PressInData.PSG1 =1;
		 }
		PressInData.PSG1+=1;
		if (PressInData.PSG1 >SysPara.BuldMeterNum)
		{
			PressInData.PSG1 =1;
		}
	}

	PressInData.Num_BuldMeter =PressInData.PSG1;
	if((PressInData.Num_BuldMeter <1)||(PressInData.Num_BuldMeter>SysPara.BuldMeterNum))
	{
		PressInData.Num_BuldMeter =1;
		PressInData.PSG1 =1;
	}

	if (( Keyvalue.value ==KEY_CA)&&(Keyvalue.resp ==1)  )                 //取消键
	{
		Keyvalue.resp =0;
		ScreenRecord.ra3 =0;
	}
    
	if (( Keyvalue.value ==KEY_CO)&&(Keyvalue.resp ==1) )                  //确认键
	{
		Keyvalue.resp =0;
		ScreenRecord.ra3 =0;	
		PressInData.Num_BuldMeter =1;
		PressInData.PSG1 =1;
    }

}





void Menu_KeyManager(void)
{
    if (ScreenRecord.ra1 ==0)
    {
        if (( Keyvalue.value !=0)&&(Keyvalue.resp ==1))    //KEY_CA
        {
            Keyvalue.resp =0;
            
            ScreenRecord.ra1 =1;
        }
    }
	
    if((ScreenRecord.ra1 ==1)&&(ScreenRecord.ra2 ==0))  //主菜单界面按键管理
    {
        Menu_1();
    }
    if ( ScreenRecord.ra1 ==1)
    {
    	switch ( ScreenRecord.ra2 )
    	{
    		case 1:		//系统状态
    		{
                if ( ScreenRecord.ra3 ==0)		//系统状态
                {
                    Menu_1_1();
                }
                if ( ScreenRecord.ra3 ==1)//设备自检
                {
					Menu_1_1_1();
                }  
                if ( ScreenRecord.ra3 ==2)//终端状态
                {
                	if (ScreenRecord.ra4 ==0)	//终端状态
                	{
                		Menu_1_1_2();
                	}
                	if (ScreenRecord.ra4 ==1)	//终端状态
                	{
                		Menu_1_1_2_1();
                	}                	
                }
                if ( ScreenRecord.ra3 ==3)//热表状态
                {
                	Menu_1_1_3();
                }
                
    		    if ( ScreenRecord.ra3 ==4)//版本信息
                {
                	Menu_1_1_4();
                }
    		    if ( ScreenRecord.ra3 ==5)//系统数据
                {
                	Menu_1_1_5();
                }                
    		}break;
    		case 2:		//用户信息
    		{
                if ( ScreenRecord.ra3 ==0)//用户信息
                {
                    Menu_1_2 ();
                }
                if ( ScreenRecord.ra3 ==1)
                {
					Menu_1_2_1();
                }
                if ( ScreenRecord.ra3 ==2)
                {
					Menu_1_2_2();
                }    

                if ( ScreenRecord.ra3 ==3)
                {
					Menu_1_2_3();
                }                  
    		}break;
    		case 3:		//系统设置
    		{
                if ( ScreenRecord.ra3 ==0)//系统设置菜单
                {
                    Menu_1_3 ();
                }
                if (( ScreenRecord.ra3 !=0)&&(PressInData.correct ==0))//系统设置密码输入界面
                {
                    Menu_1_3_PassWord ();
                }
                if (( ScreenRecord.ra3 ==1)&&(PressInData.correct ==1))//通信设置
                {
                    Menu_1_3_1();
                }       
                if (( ScreenRecord.ra3 ==2)&&(PressInData.correct ==1))//时间设置
                {
					Menu_1_3_4();
                }                
                if (( ScreenRecord.ra3 ==3)&&(PressInData.correct ==1))//密码设置
                {
					Menu_1_3_5();

                }       
                if (( ScreenRecord.ra3 ==4)&&(PressInData.correct ==1))//出厂设置
                {
					Menu_1_3_6();
                }                  
                if (( ScreenRecord.ra3 ==5)&&(PressInData.correct ==1))//设备类型
                {
                    Menu_1_3_7();
                }                   
    		}break;     	
    		case 4:		//热表信息
    		{
    			if ( ScreenRecord.ra3 ==0)//热表信息
                {
                    Menu_1_4();
                }
                if (ScreenRecord.ra3 ==1)
                {
                	Menu_1_4_1();
                }
    		}break;
    		default: break;
    	}
    }
  
}    
















//主菜单子函数
void Disp_1(void)
{
	INT16U LineSpace =32;
	INT16U FirstSpace =29;
    INT8U SU1 =0;
    INT8U SU2 =0;
    INT8U SU3 =0;
    INT8U SU4 =0;
    
    if (( CursorRecord ==0)||( CursorRecord ==1))
    {
      CursorRecord =0;
      SU1 =1;
    }
    if ( CursorRecord ==2)
    {
      SU2 =1;
    }
    if ( CursorRecord ==3)
    {
      SU3 =1;
    }
    if ( CursorRecord ==4)
    {
      SU4 =1;
    }
    
    DispStringM(32,4,"--主 菜 单--",0,12);
    DispStringM(42,LineSpace*0+FirstSpace,"1.系统状态",SU1,11);
    DispStringM(42,LineSpace*1+FirstSpace,"2.用户信息",SU2,11);
    DispStringM(42,LineSpace*2+FirstSpace,"3.系统设置",SU3,11);
    DispStringM(42,LineSpace*3+FirstSpace,"4.栋表数据",SU4,11);
	
}







void Disp_1_1(void)//系统状态菜单子函数
{
	INT16U LineSpace =28;
	INT16U FirstSpace =29;
	INT8U SU1 =0;
	INT8U SU2 =0;
	INT8U SU3 =0;
	INT8U SU4 =0;
	INT8U SU5 =0;
	if (( CursorRecord ==0)||( CursorRecord ==1))
	{
		CursorRecord =0;
		SU1 =1;
	}
	if ( CursorRecord ==2)
	{
		SU2 =1;
	}
	if ( CursorRecord ==3)
	{
	  	SU3 =1;
	}
	if ( CursorRecord ==4)
	{
	  	SU4 =1;
	}
	if ( CursorRecord ==5)
	{
	  	SU5 =1;
	}	
    
	DispStringM(32,4,"--系统状态--",0,12);
	DispStringM(42,LineSpace*0+FirstSpace,"1.设备自检",SU1,11);
	DispStringM(42,LineSpace*1+FirstSpace,"2.系统终端",SU2,11);
	DispStringM(42,LineSpace*2+FirstSpace,"3.栋表状态",SU3,11);
	DispStringM(42,LineSpace*3+FirstSpace,"4.版本信息",SU4,11);
	DispStringM(42,LineSpace*4+FirstSpace,"5.系统数据",SU5,11);
}





void Disp_1_1_3(void)
{
	INT16U LineSpace =19;
	INT16U FirstSpace =26;
	INT16U User_ID =PressInData.PSG1-1;

	
	char CH1[2];	//序号
	char CH2[12];	//SN
	
	char CH6[9];	//工作状态
	
	char DATA1[30] =" ";
	char DATA2[30] =" ";
	char DATA3[30] =" ";

	
	INT16U DA1 =PressInData.PSG1;	//键入序号
	
	
	
	INT32U DA2 = 0;
	INT8U  Meter_State =0;
	INT16U Com_Lump = 0;
	INT16U Com_Success = 0;	
	INT16U ComFaultNum = 0;

	DA2 =SysDeviceList.Device[User_ID].ID;
	if(SysDeviceList.Device[User_ID].Type ==Meter_B)
	{
		
		Meter_State =SysDevStatusErr[User_ID];					//栋表状态
		Com_Lump =SysDevStatus[User_ID].Device1.ComTolNum; 		//设备通信总次数
		Com_Success =SysDevStatus[User_ID].Device1.ComSucNum;	//通信成功次数
		ComFaultNum =SysDevStatus[User_ID].Device1.ComFauNum;	//通信失败次数
	}
#ifdef Meter_H_ENABLE
	else if(SysDeviceList.Device[User_ID].Type ==Meter_H)
	{
		
		Meter_State =SysDevStatusErr[User_ID];					//栋表状态
		Com_Lump =SysDevStatus[User_ID].Device5.ComTolNum; 		//设备通信总次数
		Com_Success =SysDevStatus[User_ID].Device5.ComSucNum;	//通信成功次数
		ComFaultNum =SysDevStatus[User_ID].Device5.ComFauNum;	//通信失败次数
	}
#endif
	strcat(DATA1,"通信总数: ");
	strcat(DATA1,Disp_Integer(Com_Lump));

	strcat(DATA2,"通信成功: ");
	strcat(DATA2,Disp_Integer(Com_Success));

	strcat(DATA3,"通信失败: ");
	strcat(DATA3,Disp_Integer(ComFaultNum));

	

	CH1[0] ='0'+DA1;
	CH1[1] ='\0';
	CH2[0] ='S';
	CH2[1] ='N';
	CH2[2] =':';
	CH2[3] ='0'+((DA2>>28)&0X0F);
	CH2[4] ='0'+((DA2>>24)&0X0F);
	CH2[5] ='0'+((DA2>>20)&0X0F);
	CH2[6] ='0'+((DA2>>16)&0X0F);
	CH2[7] ='0'+((DA2>>12)&0X0F);
	CH2[8] ='0'+((DA2>>8)&0X0F);
	CH2[9] ='0'+((DA2>>4)&0X0F);
	CH2[10] ='0'+((DA2>>0)&0X0F);
	CH2[11] ='\0';





	CH6[0]='0'+((Meter_State&0X80)>>7);
	CH6[1]='0'+((Meter_State&0X40)>>6);
	CH6[2]='0'+((Meter_State&0X20)>>5);
	CH6[3]='0'+((Meter_State&0X10)>>4);
	CH6[4]='0'+((Meter_State&0X08)>>3);
	CH6[5]='0'+((Meter_State&0X04)>>2);
	CH6[6]='0'+((Meter_State&0X02)>>1);
	CH6[7]='0'+((Meter_State&0X01)>>0);
	CH6[8] ='\0';
	DispStringM(32,4,"--栋表状态--",0,12);

	DispStringM(4,LineSpace*0+FirstSpace,   "序号:",0,10);//序号
	DispStringM(4+15*2+7,LineSpace*0+FirstSpace,   CH1,1,10);

	DispStringM(4,LineSpace*1+FirstSpace-5, CH2,0,11);	//序列号


     
	if( Meter_State==0)
	{
		DispStringM(4,LineSpace*2+FirstSpace, "1.栋表状态:正常",0,10);
	}
	else
	{
		DispStringM(4,LineSpace*2+FirstSpace, "1.栋表状态:",0,10);
		DispStringM(4+75,LineSpace*2+FirstSpace, CH6,0,10);
	}
     



	DispStringM(4,LineSpace*3+FirstSpace, DATA1,0,10);

	DispStringM(4,LineSpace*4+FirstSpace, DATA2,0,10);

	DispStringM(4,LineSpace*5+FirstSpace, DATA3,0,10);



}










void Disp_1_1_4A(void)
{
	INT16U LineSpace =20;
	INT16U FirstSpace =26;
	INT32U Device_SN =SysPara.Device_SN;		//出厂编号
	INT8U DeviceType =SysPara.DeviceType;		//设备类型
	
	INT16U UserNum =MAXUser_Num;			//用户数量
	INT16U BuldMeterNum =MAXBuldMeter_Num;			//栋表数量
	char CH1[9];//出厂编号
	char CH2[4];//用户数量
	char CH3[2];//栋表数量
	CH1[0] ='0'+((Device_SN>>28)&0X0F);//出厂编号
	CH1[1] ='0'+((Device_SN>>24)&0X0F);
	CH1[2] ='0'+((Device_SN>>20)&0X0F);
	CH1[3] ='0'+((Device_SN>>16)&0X0F);
	CH1[4] ='0'+((Device_SN>>12)&0X0F);
	CH1[5] ='0'+((Device_SN>>8)&0X0F);
	CH1[6] ='0'+((Device_SN>>4)&0X0F);
	CH1[7] ='0'+((Device_SN>>0)&0X0F);
	CH1[8] ='\0';

	
	CH2[0] ='0'+(UserNum/100);
	CH2[1] ='0'+(UserNum%100/10);
	CH2[2] ='0'+(UserNum%10);
	CH2[3] ='\0';

	CH3[0] ='0'+(BuldMeterNum%10);
	CH3[1] ='\0';
	
    DispStringM(32,4,"--版本信息--",0,12);
    DispStringM(4,LineSpace*0+FirstSpace, Hardware,0,10);
    DispStringM(4,LineSpace*1+FirstSpace, Software,0,10);
    DispStringM(4,LineSpace*2+FirstSpace, "3.出厂编号:",0,10);
    DispStringM(77,LineSpace*2+FirstSpace, CH1,0,10);
    
    DispStringM(4,LineSpace*3+FirstSpace, "4.设备类型",0,10);
    
	
	if(DeviceType ==1)
	{
		DispStringM(4,LineSpace*4+FirstSpace ,"  热量表采集系统",0,10);
	}
	else if(DeviceType ==2)
	{
		DispStringM(4,LineSpace*4+FirstSpace ,"  温控计量一体化系统",0,10);
	}
    else if(DeviceType ==3)
    {
		DispStringM(4,LineSpace*4+FirstSpace ,"  通断时间面积计量系统",0,10);
    }
    else
    {
		DispStringM(4,LineSpace*4+FirstSpace ,"  系统类型未设定",0,10);
    }
    DispStringM(4,LineSpace*5+FirstSpace ,"5.用户容量:",0,10);
    DispStringM(77,LineSpace*5+FirstSpace ,CH2,0,10);
    
    DispStringM(4,LineSpace*6+FirstSpace ,"6.栋表容量:",0,10);
	DispStringM(77,LineSpace*6+FirstSpace ,CH3,0,10);

}










void Disp_1_1_4B(void)
{
	INT16U LineSpace =20;
	INT16U FirstSpace =26;
	INT32U WorkTime =SystemTick_ms/1000/60;	//工作时间 分钟
	char TIME[21];
	char TIME_S[21];
	char TIME_F[21];
	
	char TIME_H[6];
	char TIME_M[21];
	INT16U WorkTime_H =WorkTime/60;
	INT8U WorkTime_M =WorkTime%60;
	TIME[0] =' ';
	TIME[1] ='0'+(RTC_Time.Year/1000);
	TIME[2] ='0'+(RTC_Time.Year%1000/100);
	TIME[3] ='0'+(RTC_Time.Year%100/10);
	TIME[4] ='0'+(RTC_Time.Year%10);
	TIME[5] ='-';

	TIME[6] ='0'+(RTC_Time.Month/10);
	TIME[7] ='0'+(RTC_Time.Month%10);
	TIME[8] ='-';
    
	TIME[9] ='0'+(RTC_Time.Day/10);
	TIME[10] ='0'+(RTC_Time.Day%10);
	TIME[11] =' ';

	TIME[12] ='0'+(RTC_Time.Hour/10);
	TIME[13] ='0'+(RTC_Time.Hour%10);
	TIME[14] =':';

	TIME[15] ='0'+(RTC_Time.Minute/10);
	TIME[16] ='0'+(RTC_Time.Minute%10);
	TIME[17] =':';

	TIME[18] ='0'+(RTC_Time.Second/10);
	TIME[19] ='0'+(RTC_Time.Second%10);
	TIME[20] ='\0';


	TIME_S[0] =' ';
	TIME_S[1] ='0'+(SysPara.StartTime.Year/1000);
	TIME_S[2] ='0'+(SysPara.StartTime.Year%1000/100);
	TIME_S[3] ='0'+(SysPara.StartTime.Year%100/10);
	TIME_S[4] ='0'+(SysPara.StartTime.Year%10);
	TIME_S[5] ='-';

	TIME_S[6] ='0'+(SysPara.StartTime.Month/10);
	TIME_S[7] ='0'+(SysPara.StartTime.Month%10);
	TIME_S[8] ='-';
    
	TIME_S[9] ='0'+(SysPara.StartTime.Day/10);
	TIME_S[10] ='0'+(SysPara.StartTime.Day%10);
	TIME_S[11] =' ';

	TIME_S[12] ='0'+(SysPara.StartTime.Hour/10);
	TIME_S[13] ='0'+(SysPara.StartTime.Hour%10);
	TIME_S[14] =':';

	TIME_S[15] ='0'+(SysPara.StartTime.Minute/10);
	TIME_S[16] ='0'+(SysPara.StartTime.Minute%10);
	TIME_S[17] =':';

	TIME_S[18] ='0'+(SysPara.StartTime.Second/10);
	TIME_S[19] ='0'+(SysPara.StartTime.Second%10);
	TIME_S[20] ='\0';

	TIME_F[0] =' ';
	TIME_F[1] ='0'+(SysPara.FinalTime.Year/1000);
	TIME_F[2] ='0'+(SysPara.FinalTime.Year%1000/100);
	TIME_F[3] ='0'+(SysPara.FinalTime.Year%100/10);
	TIME_F[4] ='0'+(SysPara.FinalTime.Year%10);
	TIME_F[5] ='-';

	TIME_F[6] ='0'+(SysPara.FinalTime.Month/10);
	TIME_F[7] ='0'+(SysPara.FinalTime.Month%10);
	TIME_F[8] ='-';
    
	TIME_F[9] ='0'+(SysPara.FinalTime.Day/10);
	TIME_F[10] ='0'+(SysPara.FinalTime.Day%10);
	TIME_F[11] =' ';

	TIME_F[12] ='0'+(SysPara.FinalTime.Hour/10);
	TIME_F[13] ='0'+(SysPara.FinalTime.Hour%10);
	TIME_F[14] =':';

	TIME_F[15] ='0'+(SysPara.FinalTime.Minute/10);
	TIME_F[16] ='0'+(SysPara.FinalTime.Minute%10);
	TIME_F[17] =':';

	TIME_F[18] ='0'+(SysPara.FinalTime.Second/10);
	TIME_F[19] ='0'+(SysPara.FinalTime.Second%10);
	TIME_F[20] ='\0';

	TIME_H[0] ='0'+(WorkTime_H/10000);
	TIME_H[1] ='0'+(WorkTime_H%10000/1000);
	TIME_H[2] ='0'+(WorkTime_H%1000/100);
	TIME_H[3] ='0'+(WorkTime_H%100/10);
	TIME_H[4] ='0'+(WorkTime_H%10);
	TIME_H[5] ='\0';

	TIME_M[0] ='0'+(WorkTime_M/10);
	TIME_M[1] ='0'+(WorkTime_M%10);
	TIME_M[2] ='\0';	

    DispStringM(32,4,"--版本信息--",0,12);
    DispStringM(4, LineSpace*0+FirstSpace, "7.系统时间",0,10);
    DispStringM(13,LineSpace*1+FirstSpace, TIME,0,10);
    
    DispStringM(20, LineSpace*2+FirstSpace, "连续运行:",0,10);
	DispStringM(20+59,LineSpace*2+FirstSpace, TIME_H,0,10);
	DispStringM(20+59+35,LineSpace*2+FirstSpace, "时",0,10);
	DispStringM(20+59+35+13,LineSpace*2+FirstSpace, TIME_M,0,10);
	DispStringM(20+59+35+13+14,LineSpace*2+FirstSpace,"分",0,10);
    
    DispStringM(4, LineSpace*3+FirstSpace, "8.供暖开始时间",0,10);
    DispStringM(13,LineSpace*4+FirstSpace, TIME_S,0,10);

    
	DispStringM(4, LineSpace*5+FirstSpace, "9.供暖结束时间",0,10);
	DispStringM(13,LineSpace*6+FirstSpace, TIME_F,0,10);

}






void Disp_1_1_5A(void)
{
	
	char DATA1[30] =" ";
	char DATA2[30] =" ";
	char DATA3[30] =" ";
	char DATA4[30] =" ";
	
	INT16U LineSpace =20;
	INT16U FirstSpace =26;

	strcat(DATA1,"__用户数量: ");
	strcat(DATA1,Disp_Integer(SysPara.UserNum));

   	strcat(DATA2,"__栋表数量: ");
	strcat(DATA2,Disp_Integer(SysPara.BuldMeterNum));

   	strcat(DATA3,"__用户终端数量: ");
	strcat(DATA3,Disp_Integer(SysPara.DevNum));

   	strcat(DATA4,"__系统终端容量: ");
	strcat(DATA4,Disp_Integer(MAXDevice_Num));


    DispStringM(32,4,"--系统数据--",0,12);
    
    DispStringM(4,LineSpace*0+FirstSpace, DATA1,0,10);

  	DispStringM(4,LineSpace*1+FirstSpace, DATA2,0,10);
    
    DispStringM(4,LineSpace*2+FirstSpace, DATA3,0,10);
    
    DispStringM(4,LineSpace*3+FirstSpace, DATA4,0,10);

}





void Disp_1_1_1A(void)
{
	INT16U LineSpace =18;
	INT16U FirstSpace =26;
    INT8U SD_State =0;//SD_CardWork_State.HealthState;
    INT32U TotalSize = 0;//SD_CardWork_State.Total_Size;
    INT32U FreeSize = 0;//SD_CardWork_State.Free_Size;
    char Total[7]; //总容量
    char Free[7];  //剩余容量
	Total[0] ='0'+(TotalSize%100000/10000);
	Total[1] ='0'+(TotalSize%10000/1000);
	Total[2] ='0'+(TotalSize%1000/100);
	Total[3] ='0'+(TotalSize%100/10);	
	Total[4] ='0'+(TotalSize%10);
	Total[5] ='M';
	Total[6] ='\0';
	
	Free[0] ='0'+(FreeSize%100000/10000);
	Free[1] ='0'+(FreeSize%10000/1000);
	Free[2] ='0'+(FreeSize%1000/100);
	Free[3] ='0'+(FreeSize%100/10);
	Free[4] ='0'+(FreeSize%10);
	Free[5] ='M';
	Free[6] ='\0';
	
	
    DispStringM(32,4,"--设备自检--",0,12);
    DispStringM(4,LineSpace*0+FirstSpace, "1.设备参数  : 正常",0,9);
    DispStringM(4,LineSpace*1+FirstSpace, "2.设备数据  : 正常",0,9);
	DispStringM(4,LineSpace*2+FirstSpace, "3.GPRS状态  : 正常",0,9);
    DispStringM(4,LineSpace*3+FirstSpace ,"4.M-BUS状态 : 正常",0,9);
    DispStringM(4,LineSpace*4+FirstSpace ,"5.存储器状态: 正常",0,9);
    if(SD_State ==0X00)
    {
		DispStringM(4,LineSpace*5+FirstSpace ,"6.存储卡状态: 正常",0,9);
    }
    else
    {
		DispStringM(4,LineSpace*5+FirstSpace ,"6.存储卡状态: 异常",0,9);
    }
    	DispStringM(4,LineSpace*6+FirstSpace ,"总容量:",0,9);
    	DispStringM(48,LineSpace*6+FirstSpace ,Total,1,9);
    	DispStringM(48+36,LineSpace*6+FirstSpace ," 剩余:",0,9);
    	DispStringM(48+36+36,LineSpace*6+FirstSpace ,Free,1,9);

}




void Disp_1_1_1B(void)
{
	INT16U LineSpace =18;
	INT16U FirstSpace =26;
	INT8U loop =0;
	INT8U Buffer =0;
	INT8U CSQ1 =GPRS_State.CSQ1;
	INT8U CSQ2 =GPRS_State.CSQ2;
	
	INT8U IPA1 =GPRS_State.IPA1;
	INT8U IPA2 =GPRS_State.IPA2;
	INT8U IPA3 =GPRS_State.IPA3;
	INT8U IPA4 =GPRS_State.IPA4;
	INT16U Port =GPRS_State.Port;
	
	
	char CSQ[6];
	char IP[22];
	char CCID[21];
    INT8U SIMCard_State =GPRS_State.SIMCard_State;

    CSQ[0] ='0'+(CSQ1%100/10);
    CSQ[1] ='0'+(CSQ1%10);
    CSQ[2] =',';
    CSQ[3] ='0'+(CSQ2%100/10);
    CSQ[4] ='0'+(CSQ2%10);
    CSQ[5] ='\0';

	IP[0] ='0'+IPA1%1000/100;
	IP[1] ='0'+IPA1%100/10;
	IP[2] ='0'+IPA1%10;
	IP[3] ='.';
	IP[4] ='0'+IPA2%1000/100;
	IP[5] ='0'+IPA2%100/10;
	IP[6] ='0'+IPA2%10;
	IP[7] ='.';	
	IP[8] ='0'+IPA3%1000/100;
	IP[9] ='0'+IPA3%100/10;
	IP[10] ='0'+IPA3%10;
	IP[11] ='.';	
	IP[12] ='0'+IPA4%1000/100;
	IP[13] ='0'+IPA4%100/10;
	IP[14] ='0'+IPA4%10;
	IP[15] =':';
	IP[16] ='0'+Port%100000/10000;
	IP[17] ='0'+Port%10000/1000;
	IP[18] ='0'+Port%1000/100;
	IP[19] ='0'+Port%100/10;
	IP[20] ='0'+Port%10;
	IP[21] ='\0';

	for(loop =0;loop<20;loop++)
	{
		Buffer=GPRS_State.CCID[loop];
		if(Buffer<10)
		{
			CCID[loop]='0'+Buffer;
		}
		else
		{
			Buffer =Buffer-10;
			CCID[loop]='A'+Buffer;
		}
	}
	CCID[20]='\0';

    DispStringM(32,4,"--设备自检--",0,12);
    DispStringM(4,LineSpace*0+FirstSpace, "7.GPRS通信状态",0,9);
    
    DispStringM(4+12,LineSpace*1+FirstSpace, "信号:",0,9);
    DispStringM(4+12+34,LineSpace*1+FirstSpace, CSQ,0,9);
    
	DispStringM(4+12,LineSpace*2+FirstSpace, "主站IP:",0,9);
	DispStringM(4+12,LineSpace*3+FirstSpace, IP,0,9);
	
    DispStringM(4+12,LineSpace*4+FirstSpace ,"CCID:",0,9);
    DispStringM(4+12,LineSpace*5+FirstSpace ,CCID,0,9);
    
    
    if(SIMCard_State ==0X00)
    {
		DispStringM(4+12,LineSpace*6+FirstSpace ,"SIM卡状态: 异常",0,9);
    }
    else
    {
		DispStringM(4+12,LineSpace*6+FirstSpace ,"SIM卡状态: 正常",0,9);
    }
}






void Disp_1_1_2A(void)
{
	TerminalSTA_Stru DataBuf[128];

	
	INT16U i =0;
	INT8U FontSpace =6;
	INT8U LineSpace =16;
	INT8U FirstSpace =26;
	INT8U UserStateBuf =0;
	INT16U UserNum =MAXDevice_Num;

	//图形字符显示
	for (i =0;i<128;i++)
	{	
		if(SysDevStatusErr[i] ==0)
		{
			UserStateBuf =0;
		}
		else
		{
			UserStateBuf =1;
		}
		
		if(i >=UserNum)
		{
			DataBuf[i].Data[0] =' ';
		}
		else
		{
			DataBuf[i].Data[0] ='0'+UserStateBuf;
		}
		DataBuf[i].Data[1] ='\0';
		DataBuf[i].Type=0;
	}
	DataBuf[CursorRecord-1].Type =1;
	
    DispStringM(32,4,"--系统终端--",0,12);
    

    DispStringM(4+FontSpace*0,LineSpace*0+FirstSpace, "001-016:",0,9);
	DispStringM(4+FontSpace*8,LineSpace*0+FirstSpace, DataBuf[0].Data,DataBuf[0].Type,9);// 1
    DispStringM(4+FontSpace*9,LineSpace*0+FirstSpace, DataBuf[1].Data,DataBuf[1].Type,9);// 2
    DispStringM(4+FontSpace*10,LineSpace*0+FirstSpace, DataBuf[2].Data,DataBuf[2].Type,9);// 3
    DispStringM(4+FontSpace*11,LineSpace*0+FirstSpace, DataBuf[3].Data,DataBuf[3].Type,9);// 4
    DispStringM(4+FontSpace*12,LineSpace*0+FirstSpace, DataBuf[4].Data,DataBuf[4].Type,9);// 5
    DispStringM(4+FontSpace*13,LineSpace*0+FirstSpace, DataBuf[5].Data,DataBuf[5].Type,9);// 6
    DispStringM(4+FontSpace*14,LineSpace*0+FirstSpace, DataBuf[6].Data,DataBuf[6].Type,9);// 7
    DispStringM(4+FontSpace*15,LineSpace*0+FirstSpace, DataBuf[7].Data,DataBuf[7].Type,9);// 8
    DispStringM(4+FontSpace*16,LineSpace*0+FirstSpace, DataBuf[8].Data,DataBuf[8].Type,9);// 9
    DispStringM(4+FontSpace*17,LineSpace*0+FirstSpace, DataBuf[9].Data,DataBuf[9].Type,9);// 10
    DispStringM(4+FontSpace*18,LineSpace*0+FirstSpace, DataBuf[10].Data,DataBuf[10].Type,9);// 11  
    DispStringM(4+FontSpace*19,LineSpace*0+FirstSpace, DataBuf[11].Data,DataBuf[11].Type,9);// 12
    DispStringM(4+FontSpace*20,LineSpace*0+FirstSpace, DataBuf[12].Data,DataBuf[12].Type,9);// 13
    DispStringM(4+FontSpace*21,LineSpace*0+FirstSpace, DataBuf[13].Data,DataBuf[13].Type,9);// 14
    DispStringM(4+FontSpace*22,LineSpace*0+FirstSpace, DataBuf[14].Data,DataBuf[14].Type,9);// 15
    DispStringM(4+FontSpace*23,LineSpace*0+FirstSpace, DataBuf[15].Data,DataBuf[15].Type,9);// 16

    
    DispStringM(4+FontSpace*0,LineSpace*1+FirstSpace, "017-032:",0,9);
    DispStringM(4+FontSpace*8,LineSpace*1+FirstSpace, DataBuf[16].Data,DataBuf[16].Type,9);// 1
    DispStringM(4+FontSpace*9,LineSpace*1+FirstSpace, DataBuf[17].Data,DataBuf[17].Type,9);// 2
    DispStringM(4+FontSpace*10,LineSpace*1+FirstSpace, DataBuf[18].Data,DataBuf[18].Type,9);// 3
    DispStringM(4+FontSpace*11,LineSpace*1+FirstSpace, DataBuf[19].Data,DataBuf[19].Type,9);// 4
    DispStringM(4+FontSpace*12,LineSpace*1+FirstSpace, DataBuf[20].Data,DataBuf[20].Type,9);// 5
    DispStringM(4+FontSpace*13,LineSpace*1+FirstSpace, DataBuf[21].Data,DataBuf[21].Type,9);// 6
    DispStringM(4+FontSpace*14,LineSpace*1+FirstSpace, DataBuf[22].Data,DataBuf[22].Type,9);// 7
    DispStringM(4+FontSpace*15,LineSpace*1+FirstSpace, DataBuf[23].Data,DataBuf[23].Type,9);// 8
    DispStringM(4+FontSpace*16,LineSpace*1+FirstSpace, DataBuf[23].Data,DataBuf[24].Type,9);// 9
    DispStringM(4+FontSpace*17,LineSpace*1+FirstSpace, DataBuf[25].Data,DataBuf[25].Type,9);// 10
    DispStringM(4+FontSpace*18,LineSpace*1+FirstSpace, DataBuf[26].Data,DataBuf[26].Type,9);// 11  
    DispStringM(4+FontSpace*19,LineSpace*1+FirstSpace, DataBuf[27].Data,DataBuf[27].Type,9);// 12
    DispStringM(4+FontSpace*20,LineSpace*1+FirstSpace, DataBuf[28].Data,DataBuf[28].Type,9);// 13
    DispStringM(4+FontSpace*21,LineSpace*1+FirstSpace, DataBuf[29].Data,DataBuf[29].Type,9);// 14
    DispStringM(4+FontSpace*22,LineSpace*1+FirstSpace, DataBuf[30].Data,DataBuf[30].Type,9);// 15
    DispStringM(4+FontSpace*23,LineSpace*1+FirstSpace, DataBuf[31].Data,DataBuf[31].Type,9);// 16

//	DispStringM(4,LineSpace*2+FirstSpace, "033-048:0000000000000000",SU3,9);
    DispStringM(4+FontSpace*0,LineSpace*2+FirstSpace, "033-048:",0,9);
    DispStringM(4+FontSpace*8,LineSpace*2+FirstSpace, DataBuf[0+16*2].Data,DataBuf[0+16*2].Type,9);// 1
    DispStringM(4+FontSpace*9,LineSpace*2+FirstSpace, DataBuf[1+16*2].Data,DataBuf[1+16*2].Type,9);// 2
    DispStringM(4+FontSpace*10,LineSpace*2+FirstSpace, DataBuf[2+16*2].Data,DataBuf[2+16*2].Type,9);// 3
    DispStringM(4+FontSpace*11,LineSpace*2+FirstSpace, DataBuf[3+16*2].Data,DataBuf[3+16*2].Type,9);// 4
    DispStringM(4+FontSpace*12,LineSpace*2+FirstSpace, DataBuf[4+16*2].Data,DataBuf[4+16*2].Type,9);// 5
    DispStringM(4+FontSpace*13,LineSpace*2+FirstSpace, DataBuf[5+16*2].Data,DataBuf[5+16*2].Type,9);// 6
    DispStringM(4+FontSpace*14,LineSpace*2+FirstSpace, DataBuf[6+16*2].Data,DataBuf[6+16*2].Type,9);// 7
    DispStringM(4+FontSpace*15,LineSpace*2+FirstSpace, DataBuf[7+16*2].Data,DataBuf[7+16*2].Type,9);// 8
    DispStringM(4+FontSpace*16,LineSpace*2+FirstSpace, DataBuf[8+16*2].Data,DataBuf[8+16*2].Type,9);// 9
    DispStringM(4+FontSpace*17,LineSpace*2+FirstSpace, DataBuf[9+16*2].Data,DataBuf[9+16*2].Type,9);// 10
    DispStringM(4+FontSpace*18,LineSpace*2+FirstSpace, DataBuf[10+16*2].Data,DataBuf[10+16*2].Type,9);// 11  
    DispStringM(4+FontSpace*19,LineSpace*2+FirstSpace, DataBuf[11+16*2].Data,DataBuf[11+16*2].Type,9);// 12
    DispStringM(4+FontSpace*20,LineSpace*2+FirstSpace, DataBuf[12+16*2].Data,DataBuf[12+16*2].Type,9);// 13
    DispStringM(4+FontSpace*21,LineSpace*2+FirstSpace, DataBuf[13+16*2].Data,DataBuf[13+16*2].Type,9);// 14
    DispStringM(4+FontSpace*22,LineSpace*2+FirstSpace, DataBuf[14+16*2].Data,DataBuf[14+16*2].Type,9);// 15
    DispStringM(4+FontSpace*23,LineSpace*2+FirstSpace, DataBuf[15+16*2].Data,DataBuf[15+16*2].Type,9);// 16
    
//    DispStringM(4,LineSpace*3+FirstSpace ,"049-064:0000000000000000",SU4,9);
    DispStringM(4+FontSpace*0,LineSpace*3+FirstSpace, "049-064:",0,9);
    DispStringM(4+FontSpace*8,LineSpace*3+FirstSpace, DataBuf[0+16*3].Data,DataBuf[0+16*3].Type,9);// 1
    DispStringM(4+FontSpace*9,LineSpace*3+FirstSpace, DataBuf[1+16*3].Data,DataBuf[1+16*3].Type,9);// 2
    DispStringM(4+FontSpace*10,LineSpace*3+FirstSpace, DataBuf[2+16*3].Data,DataBuf[2+16*3].Type,9);// 3
    DispStringM(4+FontSpace*11,LineSpace*3+FirstSpace, DataBuf[3+16*3].Data,DataBuf[3+16*3].Type,9);// 4
    DispStringM(4+FontSpace*12,LineSpace*3+FirstSpace, DataBuf[4+16*3].Data,DataBuf[4+16*3].Type,9);// 5
    DispStringM(4+FontSpace*13,LineSpace*3+FirstSpace, DataBuf[5+16*3].Data,DataBuf[5+16*3].Type,9);// 6
    DispStringM(4+FontSpace*14,LineSpace*3+FirstSpace, DataBuf[6+16*3].Data,DataBuf[6+16*3].Type,9);// 7
    DispStringM(4+FontSpace*15,LineSpace*3+FirstSpace, DataBuf[7+16*3].Data,DataBuf[7+16*3].Type,9);// 8
    DispStringM(4+FontSpace*16,LineSpace*3+FirstSpace, DataBuf[8+16*3].Data,DataBuf[8+16*3].Type,9);// 9
    DispStringM(4+FontSpace*17,LineSpace*3+FirstSpace, DataBuf[9+16*3].Data,DataBuf[9+16*3].Type,9);// 10
    DispStringM(4+FontSpace*18,LineSpace*3+FirstSpace, DataBuf[10+16*3].Data,DataBuf[10+16*3].Type,9);// 11  
    DispStringM(4+FontSpace*19,LineSpace*3+FirstSpace, DataBuf[11+16*3].Data,DataBuf[11+16*3].Type,9);// 12
    DispStringM(4+FontSpace*20,LineSpace*3+FirstSpace, DataBuf[12+16*3].Data,DataBuf[12+16*3].Type,9);// 13
    DispStringM(4+FontSpace*21,LineSpace*3+FirstSpace, DataBuf[13+16*3].Data,DataBuf[13+16*3].Type,9);// 14
    DispStringM(4+FontSpace*22,LineSpace*3+FirstSpace, DataBuf[14+16*3].Data,DataBuf[14+16*3].Type,9);// 15
    DispStringM(4+FontSpace*23,LineSpace*3+FirstSpace, DataBuf[15+16*3].Data,DataBuf[15+16*3].Type,9);// 16

//    DispStringM(4,LineSpace*4+FirstSpace ,"065-080:0000000000000000",SU3,9);
    DispStringM(4+FontSpace*0,LineSpace*4+FirstSpace, "065-080:",0,9);
    DispStringM(4+FontSpace*8,LineSpace*4+FirstSpace, DataBuf[0+16*4].Data,DataBuf[0+16*4].Type,9);// 1
    DispStringM(4+FontSpace*9,LineSpace*4+FirstSpace, DataBuf[1+16*4].Data,DataBuf[1+16*4].Type,9);// 2
    DispStringM(4+FontSpace*10,LineSpace*4+FirstSpace, DataBuf[2+16*4].Data,DataBuf[2+16*4].Type,9);// 3
    DispStringM(4+FontSpace*11,LineSpace*4+FirstSpace, DataBuf[3+16*4].Data,DataBuf[3+16*4].Type,9);// 4
    DispStringM(4+FontSpace*12,LineSpace*4+FirstSpace, DataBuf[4+16*4].Data,DataBuf[4+16*4].Type,9);// 5
    DispStringM(4+FontSpace*13,LineSpace*4+FirstSpace, DataBuf[5+16*4].Data,DataBuf[5+16*4].Type,9);// 6
    DispStringM(4+FontSpace*14,LineSpace*4+FirstSpace, DataBuf[6+16*4].Data,DataBuf[6+16*4].Type,9);// 7
    DispStringM(4+FontSpace*15,LineSpace*4+FirstSpace, DataBuf[7+16*4].Data,DataBuf[7+16*4].Type,9);// 8
    DispStringM(4+FontSpace*16,LineSpace*4+FirstSpace, DataBuf[8+16*4].Data,DataBuf[8+16*4].Type,9);// 9
    DispStringM(4+FontSpace*17,LineSpace*4+FirstSpace, DataBuf[9+16*4].Data,DataBuf[9+16*4].Type,9);// 10
    DispStringM(4+FontSpace*18,LineSpace*4+FirstSpace, DataBuf[10+16*4].Data,DataBuf[10+16*4].Type,9);// 11  
    DispStringM(4+FontSpace*19,LineSpace*4+FirstSpace, DataBuf[11+16*4].Data,DataBuf[11+16*4].Type,9);// 12
    DispStringM(4+FontSpace*20,LineSpace*4+FirstSpace, DataBuf[12+16*4].Data,DataBuf[12+16*4].Type,9);// 13
    DispStringM(4+FontSpace*21,LineSpace*4+FirstSpace, DataBuf[13+16*4].Data,DataBuf[13+16*4].Type,9);// 14
    DispStringM(4+FontSpace*22,LineSpace*4+FirstSpace, DataBuf[14+16*4].Data,DataBuf[14+16*4].Type,9);// 15
    DispStringM(4+FontSpace*23,LineSpace*4+FirstSpace, DataBuf[15+16*4].Data,DataBuf[15+16*4].Type,9);// 16
    
//    DispStringM(4,LineSpace*5+FirstSpace ,"081-096:0000000000000000",SU3,9);
    DispStringM(4+FontSpace*0,LineSpace*5+FirstSpace, "081-096:",0,9);
    DispStringM(4+FontSpace*8,LineSpace*5+FirstSpace, DataBuf[0+16*5].Data,DataBuf[0+16*5].Type,9);// 1
    DispStringM(4+FontSpace*9,LineSpace*5+FirstSpace, DataBuf[1+16*5].Data,DataBuf[1+16*5].Type,9);// 2
    DispStringM(4+FontSpace*10,LineSpace*5+FirstSpace, DataBuf[2+16*5].Data,DataBuf[2+16*5].Type,9);// 3
    DispStringM(4+FontSpace*11,LineSpace*5+FirstSpace, DataBuf[3+16*5].Data,DataBuf[3+16*5].Type,9);// 4
    DispStringM(4+FontSpace*12,LineSpace*5+FirstSpace, DataBuf[4+16*5].Data,DataBuf[4+16*5].Type,9);// 5
    DispStringM(4+FontSpace*13,LineSpace*5+FirstSpace, DataBuf[5+16*5].Data,DataBuf[5+16*5].Type,9);// 6
    DispStringM(4+FontSpace*14,LineSpace*5+FirstSpace, DataBuf[6+16*5].Data,DataBuf[6+16*5].Type,9);// 7
    DispStringM(4+FontSpace*15,LineSpace*5+FirstSpace, DataBuf[7+16*5].Data,DataBuf[7+16*5].Type,9);// 8
    DispStringM(4+FontSpace*16,LineSpace*5+FirstSpace, DataBuf[8+16*5].Data,DataBuf[8+16*5].Type,9);// 9
    DispStringM(4+FontSpace*17,LineSpace*5+FirstSpace, DataBuf[9+16*5].Data,DataBuf[9+16*5].Type,9);// 10
    DispStringM(4+FontSpace*18,LineSpace*5+FirstSpace, DataBuf[10+16*5].Data,DataBuf[10+16*5].Type,9);// 11  
    DispStringM(4+FontSpace*19,LineSpace*5+FirstSpace, DataBuf[11+16*5].Data,DataBuf[11+16*5].Type,9);// 12
    DispStringM(4+FontSpace*20,LineSpace*5+FirstSpace, DataBuf[12+16*5].Data,DataBuf[12+16*5].Type,9);// 13
    DispStringM(4+FontSpace*21,LineSpace*5+FirstSpace, DataBuf[13+16*5].Data,DataBuf[13+16*5].Type,9);// 14
    DispStringM(4+FontSpace*22,LineSpace*5+FirstSpace, DataBuf[14+16*5].Data,DataBuf[14+16*5].Type,9);// 15
    DispStringM(4+FontSpace*23,LineSpace*5+FirstSpace, DataBuf[15+16*5].Data,DataBuf[15+16*5].Type,9);// 16

//    DispStringM(4,LineSpace*6+FirstSpace ,"097-112:0000000000000000",SU3,9);
    DispStringM(4+FontSpace*0,LineSpace*6+FirstSpace, "097-112:",0,9);
    DispStringM(4+FontSpace*8,LineSpace*6+FirstSpace, DataBuf[0+16*6].Data,DataBuf[0+16*6].Type,9);// 1
    DispStringM(4+FontSpace*9,LineSpace*6+FirstSpace, DataBuf[1+16*6].Data,DataBuf[1+16*6].Type,9);// 2
    DispStringM(4+FontSpace*10,LineSpace*6+FirstSpace, DataBuf[2+16*6].Data,DataBuf[2+16*6].Type,9);// 3
    DispStringM(4+FontSpace*11,LineSpace*6+FirstSpace, DataBuf[3+16*6].Data,DataBuf[3+16*6].Type,9);// 4
    DispStringM(4+FontSpace*12,LineSpace*6+FirstSpace, DataBuf[4+16*6].Data,DataBuf[4+16*6].Type,9);// 5
    DispStringM(4+FontSpace*13,LineSpace*6+FirstSpace, DataBuf[5+16*6].Data,DataBuf[5+16*6].Type,9);// 6
    DispStringM(4+FontSpace*14,LineSpace*6+FirstSpace, DataBuf[6+16*6].Data,DataBuf[6+16*6].Type,9);// 7
    DispStringM(4+FontSpace*15,LineSpace*6+FirstSpace, DataBuf[7+16*6].Data,DataBuf[7+16*6].Type,9);// 8
    DispStringM(4+FontSpace*16,LineSpace*6+FirstSpace, DataBuf[8+16*6].Data,DataBuf[8+16*6].Type,9);// 9
    DispStringM(4+FontSpace*17,LineSpace*6+FirstSpace, DataBuf[9+16*6].Data,DataBuf[9+16*6].Type,9);// 10
    DispStringM(4+FontSpace*18,LineSpace*6+FirstSpace, DataBuf[10+16*6].Data,DataBuf[10+16*6].Type,9);// 11  
    DispStringM(4+FontSpace*19,LineSpace*6+FirstSpace, DataBuf[11+16*6].Data,DataBuf[11+16*6].Type,9);// 12
    DispStringM(4+FontSpace*20,LineSpace*6+FirstSpace, DataBuf[12+16*6].Data,DataBuf[12+16*6].Type,9);// 13
    DispStringM(4+FontSpace*21,LineSpace*6+FirstSpace, DataBuf[13+16*6].Data,DataBuf[13+16*6].Type,9);// 14
    DispStringM(4+FontSpace*22,LineSpace*6+FirstSpace, DataBuf[14+16*6].Data,DataBuf[14+16*6].Type,9);// 15
    DispStringM(4+FontSpace*23,LineSpace*6+FirstSpace, DataBuf[15+16*6].Data,DataBuf[15+16*6].Type,9);// 16
    
//    DispStringM(4,LineSpace*7+FirstSpace ,"113-128:0000000000000000",SU3,9);    
    DispStringM(4+FontSpace*0,LineSpace*7+FirstSpace, "113-128:",0,9);
    DispStringM(4+FontSpace*8,LineSpace*7+FirstSpace, DataBuf[0+16*7].Data,DataBuf[0+16*7].Type,9);// 1
    DispStringM(4+FontSpace*9,LineSpace*7+FirstSpace, DataBuf[1+16*7].Data,DataBuf[1+16*7].Type,9);// 2
    DispStringM(4+FontSpace*10,LineSpace*7+FirstSpace, DataBuf[2+16*7].Data,DataBuf[2+16*7].Type,9);// 3
    DispStringM(4+FontSpace*11,LineSpace*7+FirstSpace, DataBuf[3+16*7].Data,DataBuf[3+16*7].Type,9);// 4
    DispStringM(4+FontSpace*12,LineSpace*7+FirstSpace, DataBuf[4+16*7].Data,DataBuf[4+16*7].Type,9);// 5
    DispStringM(4+FontSpace*13,LineSpace*7+FirstSpace, DataBuf[5+16*7].Data,DataBuf[5+16*7].Type,9);// 6
    DispStringM(4+FontSpace*14,LineSpace*7+FirstSpace, DataBuf[6+16*7].Data,DataBuf[6+16*7].Type,9);// 7
    DispStringM(4+FontSpace*15,LineSpace*7+FirstSpace, DataBuf[7+16*7].Data,DataBuf[7+16*7].Type,9);// 8
    DispStringM(4+FontSpace*16,LineSpace*7+FirstSpace, DataBuf[8+16*7].Data,DataBuf[8+16*7].Type,9);// 9
    DispStringM(4+FontSpace*17,LineSpace*7+FirstSpace, DataBuf[9+16*7].Data,DataBuf[9+16*7].Type,9);// 10
    DispStringM(4+FontSpace*18,LineSpace*7+FirstSpace, DataBuf[10+16*7].Data,DataBuf[10+16*7].Type,9);// 11  
    DispStringM(4+FontSpace*19,LineSpace*7+FirstSpace, DataBuf[11+16*7].Data,DataBuf[11+16*7].Type,9);// 12
    DispStringM(4+FontSpace*20,LineSpace*7+FirstSpace, DataBuf[12+16*7].Data,DataBuf[12+16*7].Type,9);// 13
    DispStringM(4+FontSpace*21,LineSpace*7+FirstSpace, DataBuf[13+16*7].Data,DataBuf[13+16*7].Type,9);// 14
    DispStringM(4+FontSpace*22,LineSpace*7+FirstSpace, DataBuf[14+16*7].Data,DataBuf[14+16*7].Type,9);// 15
    DispStringM(4+FontSpace*23,LineSpace*7+FirstSpace, DataBuf[15+16*7].Data,DataBuf[15+16*7].Type,9);// 16

}





void Disp_1_1_2B(void)
{
	TerminalSTA_Stru DataBuf[128];

	
	INT16U i =0;
	INT8U  FontSpace =6;
	INT8U LineSpace =16;
	INT8U FirstSpace =26;
	INT8U UserStateBuf =0;
	INT16U UserNum =MAXDevice_Num;

	//图形字符显示
	for (i =128;i<256;i++)
	{	
		if(SysDevStatusErr[i] ==0)
		{
			UserStateBuf =0;
		}
		else
		{
			UserStateBuf =1;
		}
		
		if(i >=UserNum)
		{
			DataBuf[i-128].Data[0] =' ';
		}
		else
		{
			DataBuf[i-128].Data[0] ='0'+UserStateBuf;
		}
		DataBuf[i-128].Data[1] ='\0';
		DataBuf[i-128].Type=0;
	}
	DataBuf[CursorRecord-1-128].Type =1;
	
    DispStringM(32,4,"--系统终端--",0,12);
    
//    DispStringM(4,LineSpace*0+FirstSpace, "129-144:0000000000000000",SU1,9);
    DispStringM(4+FontSpace*0,LineSpace*0+FirstSpace, "129-144:",0,9);
	DispStringM(4+FontSpace*8,LineSpace*0+FirstSpace, DataBuf[0].Data,DataBuf[0].Type,9);// 1
    DispStringM(4+FontSpace*9,LineSpace*0+FirstSpace, DataBuf[1].Data,DataBuf[1].Type,9);// 2
    DispStringM(4+FontSpace*10,LineSpace*0+FirstSpace, DataBuf[2].Data,DataBuf[2].Type,9);// 3
    DispStringM(4+FontSpace*11,LineSpace*0+FirstSpace, DataBuf[3].Data,DataBuf[3].Type,9);// 4
    DispStringM(4+FontSpace*12,LineSpace*0+FirstSpace, DataBuf[4].Data,DataBuf[4].Type,9);// 5
    DispStringM(4+FontSpace*13,LineSpace*0+FirstSpace, DataBuf[5].Data,DataBuf[5].Type,9);// 6
    DispStringM(4+FontSpace*14,LineSpace*0+FirstSpace, DataBuf[6].Data,DataBuf[6].Type,9);// 7
    DispStringM(4+FontSpace*15,LineSpace*0+FirstSpace, DataBuf[7].Data,DataBuf[7].Type,9);// 8
    DispStringM(4+FontSpace*16,LineSpace*0+FirstSpace, DataBuf[8].Data,DataBuf[8].Type,9);// 9
    DispStringM(4+FontSpace*17,LineSpace*0+FirstSpace, DataBuf[9].Data,DataBuf[9].Type,9);// 10
    DispStringM(4+FontSpace*18,LineSpace*0+FirstSpace, DataBuf[10].Data,DataBuf[10].Type,9);// 11  
    DispStringM(4+FontSpace*19,LineSpace*0+FirstSpace, DataBuf[11].Data,DataBuf[11].Type,9);// 12
    DispStringM(4+FontSpace*20,LineSpace*0+FirstSpace, DataBuf[12].Data,DataBuf[12].Type,9);// 13
    DispStringM(4+FontSpace*21,LineSpace*0+FirstSpace, DataBuf[13].Data,DataBuf[13].Type,9);// 14
    DispStringM(4+FontSpace*22,LineSpace*0+FirstSpace, DataBuf[14].Data,DataBuf[14].Type,9);// 15
    DispStringM(4+FontSpace*23,LineSpace*0+FirstSpace, DataBuf[15].Data,DataBuf[15].Type,9);// 16

    
//    DispStringM(4,LineSpace*1+FirstSpace, "145-160:0000000000000000",SU2,9);
    DispStringM(4+FontSpace*0,LineSpace*1+FirstSpace, "145-160:",0,9);
    DispStringM(4+FontSpace*8,LineSpace*1+FirstSpace, DataBuf[16].Data,DataBuf[16].Type,9);// 1
    DispStringM(4+FontSpace*9,LineSpace*1+FirstSpace, DataBuf[17].Data,DataBuf[17].Type,9);// 2
    DispStringM(4+FontSpace*10,LineSpace*1+FirstSpace, DataBuf[18].Data,DataBuf[18].Type,9);// 3
    DispStringM(4+FontSpace*11,LineSpace*1+FirstSpace, DataBuf[19].Data,DataBuf[19].Type,9);// 4
    DispStringM(4+FontSpace*12,LineSpace*1+FirstSpace, DataBuf[20].Data,DataBuf[20].Type,9);// 5
    DispStringM(4+FontSpace*13,LineSpace*1+FirstSpace, DataBuf[21].Data,DataBuf[21].Type,9);// 6
    DispStringM(4+FontSpace*14,LineSpace*1+FirstSpace, DataBuf[22].Data,DataBuf[22].Type,9);// 7
    DispStringM(4+FontSpace*15,LineSpace*1+FirstSpace, DataBuf[23].Data,DataBuf[23].Type,9);// 8
    DispStringM(4+FontSpace*16,LineSpace*1+FirstSpace, DataBuf[23].Data,DataBuf[24].Type,9);// 9
    DispStringM(4+FontSpace*17,LineSpace*1+FirstSpace, DataBuf[25].Data,DataBuf[25].Type,9);// 10
    DispStringM(4+FontSpace*18,LineSpace*1+FirstSpace, DataBuf[26].Data,DataBuf[26].Type,9);// 11  
    DispStringM(4+FontSpace*19,LineSpace*1+FirstSpace, DataBuf[27].Data,DataBuf[27].Type,9);// 12
    DispStringM(4+FontSpace*20,LineSpace*1+FirstSpace, DataBuf[28].Data,DataBuf[28].Type,9);// 13
    DispStringM(4+FontSpace*21,LineSpace*1+FirstSpace, DataBuf[29].Data,DataBuf[29].Type,9);// 14
    DispStringM(4+FontSpace*22,LineSpace*1+FirstSpace, DataBuf[30].Data,DataBuf[30].Type,9);// 15
    DispStringM(4+FontSpace*23,LineSpace*1+FirstSpace, DataBuf[31].Data,DataBuf[31].Type,9);// 16

//	DispStringM(4,LineSpace*2+FirstSpace, "161-176:0000000000000000",SU3,9);
    DispStringM(4+FontSpace*0,LineSpace*2+FirstSpace, "161-176:",0,9);
    DispStringM(4+FontSpace*8,LineSpace*2+FirstSpace, DataBuf[0+16*2].Data,DataBuf[0+16*2].Type,9);// 1
    DispStringM(4+FontSpace*9,LineSpace*2+FirstSpace, DataBuf[1+16*2].Data,DataBuf[1+16*2].Type,9);// 2
    DispStringM(4+FontSpace*10,LineSpace*2+FirstSpace, DataBuf[2+16*2].Data,DataBuf[2+16*2].Type,9);// 3
    DispStringM(4+FontSpace*11,LineSpace*2+FirstSpace, DataBuf[3+16*2].Data,DataBuf[3+16*2].Type,9);// 4
    DispStringM(4+FontSpace*12,LineSpace*2+FirstSpace, DataBuf[4+16*2].Data,DataBuf[4+16*2].Type,9);// 5
    DispStringM(4+FontSpace*13,LineSpace*2+FirstSpace, DataBuf[5+16*2].Data,DataBuf[5+16*2].Type,9);// 6
    DispStringM(4+FontSpace*14,LineSpace*2+FirstSpace, DataBuf[6+16*2].Data,DataBuf[6+16*2].Type,9);// 7
    DispStringM(4+FontSpace*15,LineSpace*2+FirstSpace, DataBuf[7+16*2].Data,DataBuf[7+16*2].Type,9);// 8
    DispStringM(4+FontSpace*16,LineSpace*2+FirstSpace, DataBuf[8+16*2].Data,DataBuf[8+16*2].Type,9);// 9
    DispStringM(4+FontSpace*17,LineSpace*2+FirstSpace, DataBuf[9+16*2].Data,DataBuf[9+16*2].Type,9);// 10
    DispStringM(4+FontSpace*18,LineSpace*2+FirstSpace, DataBuf[10+16*2].Data,DataBuf[10+16*2].Type,9);// 11  
    DispStringM(4+FontSpace*19,LineSpace*2+FirstSpace, DataBuf[11+16*2].Data,DataBuf[11+16*2].Type,9);// 12
    DispStringM(4+FontSpace*20,LineSpace*2+FirstSpace, DataBuf[12+16*2].Data,DataBuf[12+16*2].Type,9);// 13
    DispStringM(4+FontSpace*21,LineSpace*2+FirstSpace, DataBuf[13+16*2].Data,DataBuf[13+16*2].Type,9);// 14
    DispStringM(4+FontSpace*22,LineSpace*2+FirstSpace, DataBuf[14+16*2].Data,DataBuf[14+16*2].Type,9);// 15
    DispStringM(4+FontSpace*23,LineSpace*2+FirstSpace, DataBuf[15+16*2].Data,DataBuf[15+16*2].Type,9);// 16
    
//    DispStringM(4,LineSpace*3+FirstSpace ,"177-192:0000000000000000",SU4,9);
    DispStringM(4+FontSpace*0,LineSpace*3+FirstSpace, "177-192:",0,9);
    DispStringM(4+FontSpace*8,LineSpace*3+FirstSpace, DataBuf[0+16*3].Data,DataBuf[0+16*3].Type,9);// 1
    DispStringM(4+FontSpace*9,LineSpace*3+FirstSpace, DataBuf[1+16*3].Data,DataBuf[1+16*3].Type,9);// 2
    DispStringM(4+FontSpace*10,LineSpace*3+FirstSpace, DataBuf[2+16*3].Data,DataBuf[2+16*3].Type,9);// 3
    DispStringM(4+FontSpace*11,LineSpace*3+FirstSpace, DataBuf[3+16*3].Data,DataBuf[3+16*3].Type,9);// 4
    DispStringM(4+FontSpace*12,LineSpace*3+FirstSpace, DataBuf[4+16*3].Data,DataBuf[4+16*3].Type,9);// 5
    DispStringM(4+FontSpace*13,LineSpace*3+FirstSpace, DataBuf[5+16*3].Data,DataBuf[5+16*3].Type,9);// 6
    DispStringM(4+FontSpace*14,LineSpace*3+FirstSpace, DataBuf[6+16*3].Data,DataBuf[6+16*3].Type,9);// 7
    DispStringM(4+FontSpace*15,LineSpace*3+FirstSpace, DataBuf[7+16*3].Data,DataBuf[7+16*3].Type,9);// 8
    DispStringM(4+FontSpace*16,LineSpace*3+FirstSpace, DataBuf[8+16*3].Data,DataBuf[8+16*3].Type,9);// 9
    DispStringM(4+FontSpace*17,LineSpace*3+FirstSpace, DataBuf[9+16*3].Data,DataBuf[9+16*3].Type,9);// 10
    DispStringM(4+FontSpace*18,LineSpace*3+FirstSpace, DataBuf[10+16*3].Data,DataBuf[10+16*3].Type,9);// 11  
    DispStringM(4+FontSpace*19,LineSpace*3+FirstSpace, DataBuf[11+16*3].Data,DataBuf[11+16*3].Type,9);// 12
    DispStringM(4+FontSpace*20,LineSpace*3+FirstSpace, DataBuf[12+16*3].Data,DataBuf[12+16*3].Type,9);// 13
    DispStringM(4+FontSpace*21,LineSpace*3+FirstSpace, DataBuf[13+16*3].Data,DataBuf[13+16*3].Type,9);// 14
    DispStringM(4+FontSpace*22,LineSpace*3+FirstSpace, DataBuf[14+16*3].Data,DataBuf[14+16*3].Type,9);// 15
    DispStringM(4+FontSpace*23,LineSpace*3+FirstSpace, DataBuf[15+16*3].Data,DataBuf[15+16*3].Type,9);// 16

//    DispStringM(4,LineSpace*4+FirstSpace ,"193-208:0000000000000000",SU3,9);
    DispStringM(4+FontSpace*0,LineSpace*4+FirstSpace, "193-208:",0,9);
    DispStringM(4+FontSpace*8,LineSpace*4+FirstSpace, DataBuf[0+16*4].Data,DataBuf[0+16*4].Type,9);// 1
    DispStringM(4+FontSpace*9,LineSpace*4+FirstSpace, DataBuf[1+16*4].Data,DataBuf[1+16*4].Type,9);// 2
    DispStringM(4+FontSpace*10,LineSpace*4+FirstSpace, DataBuf[2+16*4].Data,DataBuf[2+16*4].Type,9);// 3
    DispStringM(4+FontSpace*11,LineSpace*4+FirstSpace, DataBuf[3+16*4].Data,DataBuf[3+16*4].Type,9);// 4
    DispStringM(4+FontSpace*12,LineSpace*4+FirstSpace, DataBuf[4+16*4].Data,DataBuf[4+16*4].Type,9);// 5
    DispStringM(4+FontSpace*13,LineSpace*4+FirstSpace, DataBuf[5+16*4].Data,DataBuf[5+16*4].Type,9);// 6
    DispStringM(4+FontSpace*14,LineSpace*4+FirstSpace, DataBuf[6+16*4].Data,DataBuf[6+16*4].Type,9);// 7
    DispStringM(4+FontSpace*15,LineSpace*4+FirstSpace, DataBuf[7+16*4].Data,DataBuf[7+16*4].Type,9);// 8
    DispStringM(4+FontSpace*16,LineSpace*4+FirstSpace, DataBuf[8+16*4].Data,DataBuf[8+16*4].Type,9);// 9
    DispStringM(4+FontSpace*17,LineSpace*4+FirstSpace, DataBuf[9+16*4].Data,DataBuf[9+16*4].Type,9);// 10
    DispStringM(4+FontSpace*18,LineSpace*4+FirstSpace, DataBuf[10+16*4].Data,DataBuf[10+16*4].Type,9);// 11  
    DispStringM(4+FontSpace*19,LineSpace*4+FirstSpace, DataBuf[11+16*4].Data,DataBuf[11+16*4].Type,9);// 12
    DispStringM(4+FontSpace*20,LineSpace*4+FirstSpace, DataBuf[12+16*4].Data,DataBuf[12+16*4].Type,9);// 13
    DispStringM(4+FontSpace*21,LineSpace*4+FirstSpace, DataBuf[13+16*4].Data,DataBuf[13+16*4].Type,9);// 14
    DispStringM(4+FontSpace*22,LineSpace*4+FirstSpace, DataBuf[14+16*4].Data,DataBuf[14+16*4].Type,9);// 15
    DispStringM(4+FontSpace*23,LineSpace*4+FirstSpace, DataBuf[15+16*4].Data,DataBuf[15+16*4].Type,9);// 16
    
//    DispStringM(4,LineSpace*5+FirstSpace ,"209-224:0000000000000000",SU3,9);
    DispStringM(4+FontSpace*0,LineSpace*5+FirstSpace, "209-224:",0,9);
    DispStringM(4+FontSpace*8,LineSpace*5+FirstSpace, DataBuf[0+16*5].Data,DataBuf[0+16*5].Type,9);// 1
    DispStringM(4+FontSpace*9,LineSpace*5+FirstSpace, DataBuf[1+16*5].Data,DataBuf[1+16*5].Type,9);// 2
    DispStringM(4+FontSpace*10,LineSpace*5+FirstSpace, DataBuf[2+16*5].Data,DataBuf[2+16*5].Type,9);// 3
    DispStringM(4+FontSpace*11,LineSpace*5+FirstSpace, DataBuf[3+16*5].Data,DataBuf[3+16*5].Type,9);// 4
    DispStringM(4+FontSpace*12,LineSpace*5+FirstSpace, DataBuf[4+16*5].Data,DataBuf[4+16*5].Type,9);// 5
    DispStringM(4+FontSpace*13,LineSpace*5+FirstSpace, DataBuf[5+16*5].Data,DataBuf[5+16*5].Type,9);// 6
    DispStringM(4+FontSpace*14,LineSpace*5+FirstSpace, DataBuf[6+16*5].Data,DataBuf[6+16*5].Type,9);// 7
    DispStringM(4+FontSpace*15,LineSpace*5+FirstSpace, DataBuf[7+16*5].Data,DataBuf[7+16*5].Type,9);// 8
    DispStringM(4+FontSpace*16,LineSpace*5+FirstSpace, DataBuf[8+16*5].Data,DataBuf[8+16*5].Type,9);// 9
    DispStringM(4+FontSpace*17,LineSpace*5+FirstSpace, DataBuf[9+16*5].Data,DataBuf[9+16*5].Type,9);// 10
    DispStringM(4+FontSpace*18,LineSpace*5+FirstSpace, DataBuf[10+16*5].Data,DataBuf[10+16*5].Type,9);// 11  
    DispStringM(4+FontSpace*19,LineSpace*5+FirstSpace, DataBuf[11+16*5].Data,DataBuf[11+16*5].Type,9);// 12
    DispStringM(4+FontSpace*20,LineSpace*5+FirstSpace, DataBuf[12+16*5].Data,DataBuf[12+16*5].Type,9);// 13
    DispStringM(4+FontSpace*21,LineSpace*5+FirstSpace, DataBuf[13+16*5].Data,DataBuf[13+16*5].Type,9);// 14
    DispStringM(4+FontSpace*22,LineSpace*5+FirstSpace, DataBuf[14+16*5].Data,DataBuf[14+16*5].Type,9);// 15
    DispStringM(4+FontSpace*23,LineSpace*5+FirstSpace, DataBuf[15+16*5].Data,DataBuf[15+16*5].Type,9);// 16

//    DispStringM(4,LineSpace*6+FirstSpace ,"225-240:0000000000000000",SU3,9);
    DispStringM(4+FontSpace*0,LineSpace*6+FirstSpace, "225-240:",0,9);
    DispStringM(4+FontSpace*8,LineSpace*6+FirstSpace, DataBuf[0+16*6].Data,DataBuf[0+16*6].Type,9);// 1
    DispStringM(4+FontSpace*9,LineSpace*6+FirstSpace, DataBuf[1+16*6].Data,DataBuf[1+16*6].Type,9);// 2
    DispStringM(4+FontSpace*10,LineSpace*6+FirstSpace, DataBuf[2+16*6].Data,DataBuf[2+16*6].Type,9);// 3
    DispStringM(4+FontSpace*11,LineSpace*6+FirstSpace, DataBuf[3+16*6].Data,DataBuf[3+16*6].Type,9);// 4
    DispStringM(4+FontSpace*12,LineSpace*6+FirstSpace, DataBuf[4+16*6].Data,DataBuf[4+16*6].Type,9);// 5
    DispStringM(4+FontSpace*13,LineSpace*6+FirstSpace, DataBuf[5+16*6].Data,DataBuf[5+16*6].Type,9);// 6
    DispStringM(4+FontSpace*14,LineSpace*6+FirstSpace, DataBuf[6+16*6].Data,DataBuf[6+16*6].Type,9);// 7
    DispStringM(4+FontSpace*15,LineSpace*6+FirstSpace, DataBuf[7+16*6].Data,DataBuf[7+16*6].Type,9);// 8
    DispStringM(4+FontSpace*16,LineSpace*6+FirstSpace, DataBuf[8+16*6].Data,DataBuf[8+16*6].Type,9);// 9
    DispStringM(4+FontSpace*17,LineSpace*6+FirstSpace, DataBuf[9+16*6].Data,DataBuf[9+16*6].Type,9);// 10
    DispStringM(4+FontSpace*18,LineSpace*6+FirstSpace, DataBuf[10+16*6].Data,DataBuf[10+16*6].Type,9);// 11  
    DispStringM(4+FontSpace*19,LineSpace*6+FirstSpace, DataBuf[11+16*6].Data,DataBuf[11+16*6].Type,9);// 12
    DispStringM(4+FontSpace*20,LineSpace*6+FirstSpace, DataBuf[12+16*6].Data,DataBuf[12+16*6].Type,9);// 13
    DispStringM(4+FontSpace*21,LineSpace*6+FirstSpace, DataBuf[13+16*6].Data,DataBuf[13+16*6].Type,9);// 14
    DispStringM(4+FontSpace*22,LineSpace*6+FirstSpace, DataBuf[14+16*6].Data,DataBuf[14+16*6].Type,9);// 15
    DispStringM(4+FontSpace*23,LineSpace*6+FirstSpace, DataBuf[15+16*6].Data,DataBuf[15+16*6].Type,9);// 16



    DispStringM(4+FontSpace*0,LineSpace*7+FirstSpace, "241-256:",0,9);
    DispStringM(4+FontSpace*8,LineSpace*7+FirstSpace, DataBuf[0+16*7].Data,DataBuf[0+16*7].Type,9);// 1
    DispStringM(4+FontSpace*9,LineSpace*7+FirstSpace, DataBuf[1+16*7].Data,DataBuf[1+16*7].Type,9);// 2
    DispStringM(4+FontSpace*10,LineSpace*7+FirstSpace, DataBuf[2+16*7].Data,DataBuf[2+16*7].Type,9);// 3
    DispStringM(4+FontSpace*11,LineSpace*7+FirstSpace, DataBuf[3+16*7].Data,DataBuf[3+16*7].Type,9);// 4
    DispStringM(4+FontSpace*12,LineSpace*7+FirstSpace, DataBuf[4+16*7].Data,DataBuf[4+16*7].Type,9);// 5
    DispStringM(4+FontSpace*13,LineSpace*7+FirstSpace, DataBuf[5+16*7].Data,DataBuf[5+16*7].Type,9);// 6
    DispStringM(4+FontSpace*14,LineSpace*7+FirstSpace, DataBuf[6+16*7].Data,DataBuf[6+16*7].Type,9);// 7
    DispStringM(4+FontSpace*15,LineSpace*7+FirstSpace, DataBuf[7+16*7].Data,DataBuf[7+16*7].Type,9);// 8
    DispStringM(4+FontSpace*16,LineSpace*7+FirstSpace, DataBuf[8+16*7].Data,DataBuf[8+16*7].Type,9);// 9
    DispStringM(4+FontSpace*17,LineSpace*7+FirstSpace, DataBuf[9+16*7].Data,DataBuf[9+16*7].Type,9);// 10
    DispStringM(4+FontSpace*18,LineSpace*7+FirstSpace, DataBuf[10+16*7].Data,DataBuf[10+16*7].Type,9);// 11  
    DispStringM(4+FontSpace*19,LineSpace*7+FirstSpace, DataBuf[11+16*7].Data,DataBuf[11+16*7].Type,9);// 12
    DispStringM(4+FontSpace*20,LineSpace*7+FirstSpace, DataBuf[12+16*7].Data,DataBuf[12+16*7].Type,9);// 13
    DispStringM(4+FontSpace*21,LineSpace*7+FirstSpace, DataBuf[13+16*7].Data,DataBuf[13+16*7].Type,9);// 14
    DispStringM(4+FontSpace*22,LineSpace*7+FirstSpace, DataBuf[14+16*7].Data,DataBuf[14+16*7].Type,9);// 15
    DispStringM(4+FontSpace*23,LineSpace*7+FirstSpace, DataBuf[15+16*7].Data,DataBuf[15+16*7].Type,9);// 16
}





void Disp_1_1_2C(void)
{
	TerminalSTA_Stru DataBuf[128];

	
	INT16U i =0;
	INT8U FontSpace =6;
	INT8U LineSpace =16;
	INT8U FirstSpace =26;
	INT8U UserStateBuf =0;
	INT16U UserNum =MAXDevice_Num;

	//图形字符显示
	for (i =256;i<384;i++)
	{	
		if(SysDevStatusErr[i] ==0)
		{
			UserStateBuf =0;
		}
		else
		{
			UserStateBuf =1;
		}
		
		if(i >=UserNum)
		{
			DataBuf[i-256].Data[0] =' ';
		}
		else
		{
			DataBuf[i-256].Data[0] ='0'+UserStateBuf;
		}
		DataBuf[i-256].Data[1] ='\0';
		DataBuf[i-256].Type=0;
	}
	DataBuf[CursorRecord-1-256].Type =1;
	
    DispStringM(32,4,"--系统终端--",0,12);
    
//    DispStringM(4,LineSpace*0+FirstSpace, "129-144:0000000000000000",SU1,9);
    DispStringM(4+FontSpace*0,LineSpace*0+FirstSpace, "257-272:",0,9);
	DispStringM(4+FontSpace*8,LineSpace*0+FirstSpace, DataBuf[0].Data,DataBuf[0].Type,9);// 1
    DispStringM(4+FontSpace*9,LineSpace*0+FirstSpace, DataBuf[1].Data,DataBuf[1].Type,9);// 2
    DispStringM(4+FontSpace*10,LineSpace*0+FirstSpace, DataBuf[2].Data,DataBuf[2].Type,9);// 3
    DispStringM(4+FontSpace*11,LineSpace*0+FirstSpace, DataBuf[3].Data,DataBuf[3].Type,9);// 4
    DispStringM(4+FontSpace*12,LineSpace*0+FirstSpace, DataBuf[4].Data,DataBuf[4].Type,9);// 5
    DispStringM(4+FontSpace*13,LineSpace*0+FirstSpace, DataBuf[5].Data,DataBuf[5].Type,9);// 6
    DispStringM(4+FontSpace*14,LineSpace*0+FirstSpace, DataBuf[6].Data,DataBuf[6].Type,9);// 7
    DispStringM(4+FontSpace*15,LineSpace*0+FirstSpace, DataBuf[7].Data,DataBuf[7].Type,9);// 8
    DispStringM(4+FontSpace*16,LineSpace*0+FirstSpace, DataBuf[8].Data,DataBuf[8].Type,9);// 9
    DispStringM(4+FontSpace*17,LineSpace*0+FirstSpace, DataBuf[9].Data,DataBuf[9].Type,9);// 10
    DispStringM(4+FontSpace*18,LineSpace*0+FirstSpace, DataBuf[10].Data,DataBuf[10].Type,9);// 11  
    DispStringM(4+FontSpace*19,LineSpace*0+FirstSpace, DataBuf[11].Data,DataBuf[11].Type,9);// 12
    DispStringM(4+FontSpace*20,LineSpace*0+FirstSpace, DataBuf[12].Data,DataBuf[12].Type,9);// 13
    DispStringM(4+FontSpace*21,LineSpace*0+FirstSpace, DataBuf[13].Data,DataBuf[13].Type,9);// 14
    DispStringM(4+FontSpace*22,LineSpace*0+FirstSpace, DataBuf[14].Data,DataBuf[14].Type,9);// 15
    DispStringM(4+FontSpace*23,LineSpace*0+FirstSpace, DataBuf[15].Data,DataBuf[15].Type,9);// 16

    
//    DispStringM(4,LineSpace*1+FirstSpace, "145-160:0000000000000000",SU2,9);
    DispStringM(4+FontSpace*0,LineSpace*1+FirstSpace, "273-288:",0,9);
    DispStringM(4+FontSpace*8,LineSpace*1+FirstSpace, DataBuf[16].Data,DataBuf[16].Type,9);// 1
    DispStringM(4+FontSpace*9,LineSpace*1+FirstSpace, DataBuf[17].Data,DataBuf[17].Type,9);// 2
    DispStringM(4+FontSpace*10,LineSpace*1+FirstSpace, DataBuf[18].Data,DataBuf[18].Type,9);// 3
    DispStringM(4+FontSpace*11,LineSpace*1+FirstSpace, DataBuf[19].Data,DataBuf[19].Type,9);// 4
    DispStringM(4+FontSpace*12,LineSpace*1+FirstSpace, DataBuf[20].Data,DataBuf[20].Type,9);// 5
    DispStringM(4+FontSpace*13,LineSpace*1+FirstSpace, DataBuf[21].Data,DataBuf[21].Type,9);// 6
    DispStringM(4+FontSpace*14,LineSpace*1+FirstSpace, DataBuf[22].Data,DataBuf[22].Type,9);// 7
    DispStringM(4+FontSpace*15,LineSpace*1+FirstSpace, DataBuf[23].Data,DataBuf[23].Type,9);// 8
    DispStringM(4+FontSpace*16,LineSpace*1+FirstSpace, DataBuf[23].Data,DataBuf[24].Type,9);// 9
    DispStringM(4+FontSpace*17,LineSpace*1+FirstSpace, DataBuf[25].Data,DataBuf[25].Type,9);// 10
    DispStringM(4+FontSpace*18,LineSpace*1+FirstSpace, DataBuf[26].Data,DataBuf[26].Type,9);// 11  
    DispStringM(4+FontSpace*19,LineSpace*1+FirstSpace, DataBuf[27].Data,DataBuf[27].Type,9);// 12
    DispStringM(4+FontSpace*20,LineSpace*1+FirstSpace, DataBuf[28].Data,DataBuf[28].Type,9);// 13
    DispStringM(4+FontSpace*21,LineSpace*1+FirstSpace, DataBuf[29].Data,DataBuf[29].Type,9);// 14
    DispStringM(4+FontSpace*22,LineSpace*1+FirstSpace, DataBuf[30].Data,DataBuf[30].Type,9);// 15
    DispStringM(4+FontSpace*23,LineSpace*1+FirstSpace, DataBuf[31].Data,DataBuf[31].Type,9);// 16

//	DispStringM(4,LineSpace*2+FirstSpace, "161-176:0000000000000000",SU3,9);
    DispStringM(4+FontSpace*0,LineSpace*2+FirstSpace, "289-304:",0,9);
    DispStringM(4+FontSpace*8,LineSpace*2+FirstSpace, DataBuf[0+16*2].Data,DataBuf[0+16*2].Type,9);// 1
    DispStringM(4+FontSpace*9,LineSpace*2+FirstSpace, DataBuf[1+16*2].Data,DataBuf[1+16*2].Type,9);// 2
    DispStringM(4+FontSpace*10,LineSpace*2+FirstSpace, DataBuf[2+16*2].Data,DataBuf[2+16*2].Type,9);// 3
    DispStringM(4+FontSpace*11,LineSpace*2+FirstSpace, DataBuf[3+16*2].Data,DataBuf[3+16*2].Type,9);// 4
    DispStringM(4+FontSpace*12,LineSpace*2+FirstSpace, DataBuf[4+16*2].Data,DataBuf[4+16*2].Type,9);// 5
    DispStringM(4+FontSpace*13,LineSpace*2+FirstSpace, DataBuf[5+16*2].Data,DataBuf[5+16*2].Type,9);// 6
    DispStringM(4+FontSpace*14,LineSpace*2+FirstSpace, DataBuf[6+16*2].Data,DataBuf[6+16*2].Type,9);// 7
    DispStringM(4+FontSpace*15,LineSpace*2+FirstSpace, DataBuf[7+16*2].Data,DataBuf[7+16*2].Type,9);// 8
    DispStringM(4+FontSpace*16,LineSpace*2+FirstSpace, DataBuf[8+16*2].Data,DataBuf[8+16*2].Type,9);// 9
    DispStringM(4+FontSpace*17,LineSpace*2+FirstSpace, DataBuf[9+16*2].Data,DataBuf[9+16*2].Type,9);// 10
    DispStringM(4+FontSpace*18,LineSpace*2+FirstSpace, DataBuf[10+16*2].Data,DataBuf[10+16*2].Type,9);// 11  
    DispStringM(4+FontSpace*19,LineSpace*2+FirstSpace, DataBuf[11+16*2].Data,DataBuf[11+16*2].Type,9);// 12
    DispStringM(4+FontSpace*20,LineSpace*2+FirstSpace, DataBuf[12+16*2].Data,DataBuf[12+16*2].Type,9);// 13
    DispStringM(4+FontSpace*21,LineSpace*2+FirstSpace, DataBuf[13+16*2].Data,DataBuf[13+16*2].Type,9);// 14
    DispStringM(4+FontSpace*22,LineSpace*2+FirstSpace, DataBuf[14+16*2].Data,DataBuf[14+16*2].Type,9);// 15
    DispStringM(4+FontSpace*23,LineSpace*2+FirstSpace, DataBuf[15+16*2].Data,DataBuf[15+16*2].Type,9);// 16
    
//    DispStringM(4,LineSpace*3+FirstSpace ,"177-192:0000000000000000",SU4,9);
    DispStringM(4+FontSpace*0,LineSpace*3+FirstSpace, "305-320:",0,9);
    DispStringM(4+FontSpace*8,LineSpace*3+FirstSpace, DataBuf[0+16*3].Data,DataBuf[0+16*3].Type,9);// 1
    DispStringM(4+FontSpace*9,LineSpace*3+FirstSpace, DataBuf[1+16*3].Data,DataBuf[1+16*3].Type,9);// 2
    DispStringM(4+FontSpace*10,LineSpace*3+FirstSpace, DataBuf[2+16*3].Data,DataBuf[2+16*3].Type,9);// 3
    DispStringM(4+FontSpace*11,LineSpace*3+FirstSpace, DataBuf[3+16*3].Data,DataBuf[3+16*3].Type,9);// 4
    DispStringM(4+FontSpace*12,LineSpace*3+FirstSpace, DataBuf[4+16*3].Data,DataBuf[4+16*3].Type,9);// 5
    DispStringM(4+FontSpace*13,LineSpace*3+FirstSpace, DataBuf[5+16*3].Data,DataBuf[5+16*3].Type,9);// 6
    DispStringM(4+FontSpace*14,LineSpace*3+FirstSpace, DataBuf[6+16*3].Data,DataBuf[6+16*3].Type,9);// 7
    DispStringM(4+FontSpace*15,LineSpace*3+FirstSpace, DataBuf[7+16*3].Data,DataBuf[7+16*3].Type,9);// 8
    DispStringM(4+FontSpace*16,LineSpace*3+FirstSpace, DataBuf[8+16*3].Data,DataBuf[8+16*3].Type,9);// 9
    DispStringM(4+FontSpace*17,LineSpace*3+FirstSpace, DataBuf[9+16*3].Data,DataBuf[9+16*3].Type,9);// 10
    DispStringM(4+FontSpace*18,LineSpace*3+FirstSpace, DataBuf[10+16*3].Data,DataBuf[10+16*3].Type,9);// 11  
    DispStringM(4+FontSpace*19,LineSpace*3+FirstSpace, DataBuf[11+16*3].Data,DataBuf[11+16*3].Type,9);// 12
    DispStringM(4+FontSpace*20,LineSpace*3+FirstSpace, DataBuf[12+16*3].Data,DataBuf[12+16*3].Type,9);// 13
    DispStringM(4+FontSpace*21,LineSpace*3+FirstSpace, DataBuf[13+16*3].Data,DataBuf[13+16*3].Type,9);// 14
    DispStringM(4+FontSpace*22,LineSpace*3+FirstSpace, DataBuf[14+16*3].Data,DataBuf[14+16*3].Type,9);// 15
    DispStringM(4+FontSpace*23,LineSpace*3+FirstSpace, DataBuf[15+16*3].Data,DataBuf[15+16*3].Type,9);// 16

//    DispStringM(4,LineSpace*4+FirstSpace ,"193-208:0000000000000000",SU3,9);
    DispStringM(4+FontSpace*0,LineSpace*4+FirstSpace, "321-336:",0,9);
    DispStringM(4+FontSpace*8,LineSpace*4+FirstSpace, DataBuf[0+16*4].Data,DataBuf[0+16*4].Type,9);// 1
    DispStringM(4+FontSpace*9,LineSpace*4+FirstSpace, DataBuf[1+16*4].Data,DataBuf[1+16*4].Type,9);// 2
    DispStringM(4+FontSpace*10,LineSpace*4+FirstSpace, DataBuf[2+16*4].Data,DataBuf[2+16*4].Type,9);// 3
    DispStringM(4+FontSpace*11,LineSpace*4+FirstSpace, DataBuf[3+16*4].Data,DataBuf[3+16*4].Type,9);// 4
    DispStringM(4+FontSpace*12,LineSpace*4+FirstSpace, DataBuf[4+16*4].Data,DataBuf[4+16*4].Type,9);// 5
    DispStringM(4+FontSpace*13,LineSpace*4+FirstSpace, DataBuf[5+16*4].Data,DataBuf[5+16*4].Type,9);// 6
    DispStringM(4+FontSpace*14,LineSpace*4+FirstSpace, DataBuf[6+16*4].Data,DataBuf[6+16*4].Type,9);// 7
    DispStringM(4+FontSpace*15,LineSpace*4+FirstSpace, DataBuf[7+16*4].Data,DataBuf[7+16*4].Type,9);// 8
    DispStringM(4+FontSpace*16,LineSpace*4+FirstSpace, DataBuf[8+16*4].Data,DataBuf[8+16*4].Type,9);// 9
    DispStringM(4+FontSpace*17,LineSpace*4+FirstSpace, DataBuf[9+16*4].Data,DataBuf[9+16*4].Type,9);// 10
    DispStringM(4+FontSpace*18,LineSpace*4+FirstSpace, DataBuf[10+16*4].Data,DataBuf[10+16*4].Type,9);// 11  
    DispStringM(4+FontSpace*19,LineSpace*4+FirstSpace, DataBuf[11+16*4].Data,DataBuf[11+16*4].Type,9);// 12
    DispStringM(4+FontSpace*20,LineSpace*4+FirstSpace, DataBuf[12+16*4].Data,DataBuf[12+16*4].Type,9);// 13
    DispStringM(4+FontSpace*21,LineSpace*4+FirstSpace, DataBuf[13+16*4].Data,DataBuf[13+16*4].Type,9);// 14
    DispStringM(4+FontSpace*22,LineSpace*4+FirstSpace, DataBuf[14+16*4].Data,DataBuf[14+16*4].Type,9);// 15
    DispStringM(4+FontSpace*23,LineSpace*4+FirstSpace, DataBuf[15+16*4].Data,DataBuf[15+16*4].Type,9);// 16
    
//    DispStringM(4,LineSpace*5+FirstSpace ,"209-224:0000000000000000",SU3,9);
    DispStringM(4+FontSpace*0,LineSpace*5+FirstSpace, "337-352:",0,9);
    DispStringM(4+FontSpace*8,LineSpace*5+FirstSpace, DataBuf[0+16*5].Data,DataBuf[0+16*5].Type,9);// 1
    DispStringM(4+FontSpace*9,LineSpace*5+FirstSpace, DataBuf[1+16*5].Data,DataBuf[1+16*5].Type,9);// 2
    DispStringM(4+FontSpace*10,LineSpace*5+FirstSpace, DataBuf[2+16*5].Data,DataBuf[2+16*5].Type,9);// 3
    DispStringM(4+FontSpace*11,LineSpace*5+FirstSpace, DataBuf[3+16*5].Data,DataBuf[3+16*5].Type,9);// 4
    DispStringM(4+FontSpace*12,LineSpace*5+FirstSpace, DataBuf[4+16*5].Data,DataBuf[4+16*5].Type,9);// 5
    DispStringM(4+FontSpace*13,LineSpace*5+FirstSpace, DataBuf[5+16*5].Data,DataBuf[5+16*5].Type,9);// 6
    DispStringM(4+FontSpace*14,LineSpace*5+FirstSpace, DataBuf[6+16*5].Data,DataBuf[6+16*5].Type,9);// 7
    DispStringM(4+FontSpace*15,LineSpace*5+FirstSpace, DataBuf[7+16*5].Data,DataBuf[7+16*5].Type,9);// 8
    DispStringM(4+FontSpace*16,LineSpace*5+FirstSpace, DataBuf[8+16*5].Data,DataBuf[8+16*5].Type,9);// 9
    DispStringM(4+FontSpace*17,LineSpace*5+FirstSpace, DataBuf[9+16*5].Data,DataBuf[9+16*5].Type,9);// 10
    DispStringM(4+FontSpace*18,LineSpace*5+FirstSpace, DataBuf[10+16*5].Data,DataBuf[10+16*5].Type,9);// 11  
    DispStringM(4+FontSpace*19,LineSpace*5+FirstSpace, DataBuf[11+16*5].Data,DataBuf[11+16*5].Type,9);// 12
    DispStringM(4+FontSpace*20,LineSpace*5+FirstSpace, DataBuf[12+16*5].Data,DataBuf[12+16*5].Type,9);// 13
    DispStringM(4+FontSpace*21,LineSpace*5+FirstSpace, DataBuf[13+16*5].Data,DataBuf[13+16*5].Type,9);// 14
    DispStringM(4+FontSpace*22,LineSpace*5+FirstSpace, DataBuf[14+16*5].Data,DataBuf[14+16*5].Type,9);// 15
    DispStringM(4+FontSpace*23,LineSpace*5+FirstSpace, DataBuf[15+16*5].Data,DataBuf[15+16*5].Type,9);// 16

//    DispStringM(4,LineSpace*6+FirstSpace ,"225-240:0000000000000000",SU3,9);
    DispStringM(4+FontSpace*0,LineSpace*6+FirstSpace, "353-368:",0,9);
    DispStringM(4+FontSpace*8,LineSpace*6+FirstSpace, DataBuf[0+16*6].Data,DataBuf[0+16*6].Type,9);// 1
    DispStringM(4+FontSpace*9,LineSpace*6+FirstSpace, DataBuf[1+16*6].Data,DataBuf[1+16*6].Type,9);// 2
    DispStringM(4+FontSpace*10,LineSpace*6+FirstSpace, DataBuf[2+16*6].Data,DataBuf[2+16*6].Type,9);// 3
    DispStringM(4+FontSpace*11,LineSpace*6+FirstSpace, DataBuf[3+16*6].Data,DataBuf[3+16*6].Type,9);// 4
    DispStringM(4+FontSpace*12,LineSpace*6+FirstSpace, DataBuf[4+16*6].Data,DataBuf[4+16*6].Type,9);// 5
    DispStringM(4+FontSpace*13,LineSpace*6+FirstSpace, DataBuf[5+16*6].Data,DataBuf[5+16*6].Type,9);// 6
    DispStringM(4+FontSpace*14,LineSpace*6+FirstSpace, DataBuf[6+16*6].Data,DataBuf[6+16*6].Type,9);// 7
    DispStringM(4+FontSpace*15,LineSpace*6+FirstSpace, DataBuf[7+16*6].Data,DataBuf[7+16*6].Type,9);// 8
    DispStringM(4+FontSpace*16,LineSpace*6+FirstSpace, DataBuf[8+16*6].Data,DataBuf[8+16*6].Type,9);// 9
    DispStringM(4+FontSpace*17,LineSpace*6+FirstSpace, DataBuf[9+16*6].Data,DataBuf[9+16*6].Type,9);// 10
    DispStringM(4+FontSpace*18,LineSpace*6+FirstSpace, DataBuf[10+16*6].Data,DataBuf[10+16*6].Type,9);// 11  
    DispStringM(4+FontSpace*19,LineSpace*6+FirstSpace, DataBuf[11+16*6].Data,DataBuf[11+16*6].Type,9);// 12
    DispStringM(4+FontSpace*20,LineSpace*6+FirstSpace, DataBuf[12+16*6].Data,DataBuf[12+16*6].Type,9);// 13
    DispStringM(4+FontSpace*21,LineSpace*6+FirstSpace, DataBuf[13+16*6].Data,DataBuf[13+16*6].Type,9);// 14
    DispStringM(4+FontSpace*22,LineSpace*6+FirstSpace, DataBuf[14+16*6].Data,DataBuf[14+16*6].Type,9);// 15
    DispStringM(4+FontSpace*23,LineSpace*6+FirstSpace, DataBuf[15+16*6].Data,DataBuf[15+16*6].Type,9);// 16



    DispStringM(4+FontSpace*0,LineSpace*7+FirstSpace, "369-384:",0,9);
    DispStringM(4+FontSpace*8,LineSpace*7+FirstSpace, DataBuf[0+16*7].Data,DataBuf[0+16*7].Type,9);// 1
    DispStringM(4+FontSpace*9,LineSpace*7+FirstSpace, DataBuf[1+16*7].Data,DataBuf[1+16*7].Type,9);// 2
    DispStringM(4+FontSpace*10,LineSpace*7+FirstSpace, DataBuf[2+16*7].Data,DataBuf[2+16*7].Type,9);// 3
    DispStringM(4+FontSpace*11,LineSpace*7+FirstSpace, DataBuf[3+16*7].Data,DataBuf[3+16*7].Type,9);// 4
    DispStringM(4+FontSpace*12,LineSpace*7+FirstSpace, DataBuf[4+16*7].Data,DataBuf[4+16*7].Type,9);// 5
    DispStringM(4+FontSpace*13,LineSpace*7+FirstSpace, DataBuf[5+16*7].Data,DataBuf[5+16*7].Type,9);// 6
    DispStringM(4+FontSpace*14,LineSpace*7+FirstSpace, DataBuf[6+16*7].Data,DataBuf[6+16*7].Type,9);// 7
    DispStringM(4+FontSpace*15,LineSpace*7+FirstSpace, DataBuf[7+16*7].Data,DataBuf[7+16*7].Type,9);// 8
    DispStringM(4+FontSpace*16,LineSpace*7+FirstSpace, DataBuf[8+16*7].Data,DataBuf[8+16*7].Type,9);// 9
    DispStringM(4+FontSpace*17,LineSpace*7+FirstSpace, DataBuf[9+16*7].Data,DataBuf[9+16*7].Type,9);// 10
    DispStringM(4+FontSpace*18,LineSpace*7+FirstSpace, DataBuf[10+16*7].Data,DataBuf[10+16*7].Type,9);// 11  
    DispStringM(4+FontSpace*19,LineSpace*7+FirstSpace, DataBuf[11+16*7].Data,DataBuf[11+16*7].Type,9);// 12
    DispStringM(4+FontSpace*20,LineSpace*7+FirstSpace, DataBuf[12+16*7].Data,DataBuf[12+16*7].Type,9);// 13
    DispStringM(4+FontSpace*21,LineSpace*7+FirstSpace, DataBuf[13+16*7].Data,DataBuf[13+16*7].Type,9);// 14
    DispStringM(4+FontSpace*22,LineSpace*7+FirstSpace, DataBuf[14+16*7].Data,DataBuf[14+16*7].Type,9);// 15
    DispStringM(4+FontSpace*23,LineSpace*7+FirstSpace, DataBuf[15+16*7].Data,DataBuf[15+16*7].Type,9);// 16
}




void Disp_1_1_2_1(void)
{
	INT8U Fontspace =13;
	INT16U LineSpace =19;
	INT16U FirstSpace =26;
	
	INT8U G1 =0;
	INT8U G2 =0;
	INT8U G3 =0;
	INT8U G4 =0;
	INT8U G5 =0;
	INT8U G6 =0;
	INT8U G7 =0;
	INT8U G8 =0;
	INT8U G9 =0;
	INT8U G10 =0;
	
	char CH1[2];
	char CH2[2];
	char CH3[2];
	char CH4[2];
	char CH5[2];
	char CH6[2];
	char CH7[2];
	char CH8[2];
	char CH9[2];
	char CH10[2];
	
	char DATA1[30] =" ";
	char DATA2[30] =" ";
	char DATA3[30] =" ";

	INT16U DEvNum =PressInData.Num_Dev -1;
	
	INT8U Buld;		//楼栋号
	INT8U Unit;		//单元号
	INT8U Floor;		//楼层号
	INT8U Cell;		//房间号
	
	INT32U STA1 = 0;	//通信总次数
	INT32U STA2 = 0;	//通信成功次数
	INT32U STA3 = 0;	//通信失败次数

	CH1[1] ='\0';
	CH2[1] ='\0';
	CH3[1] ='\0';
	CH4[1] ='\0';
	CH5[1] ='\0';
	CH6[1] ='\0';
	CH7[1] ='\0';
	CH8[1] ='\0';
	CH9[1] ='\0';
	CH10[1] ='\0';


	if ( CursorRecord >3)
	{
		Buld = PressInData.Buld;//终端楼号
		Unit = PressInData.Unit;//终端单元号
		Floor = PressInData.Floor;//终端楼层号
		Cell = PressInData.Cell;//终端房间号
	}
	else		//光标位置在设备序号
	{
		INT32U U_ID =0;
		INT16U U_Num =0;

		//根据设备序号检索到用户序号
		U_ID =SysDeviceList.Device[DEvNum].UserKEY;
		if( GetUser_Num( U_ID,&U_Num) ==HAL_OK)
		{
			Buld =PressInData.Buld =SysUserList.User[U_Num].Buld;//终端楼号
			Unit =PressInData.Unit =SysUserList.User[U_Num].Unit;//终端单元号
			Floor =PressInData.Floor =SysUserList.User[U_Num].Floor;//终端楼层号
			Cell = PressInData.Cell =SysUserList.User[U_Num].Cell;//终端房间号
		}
		else
		{
			Buld =0;//终端楼号
			Unit =0;//终端单元号
			Floor =0;//终端楼层号
			Cell = 0;//终端房间号
		}
		
		//用户序号回传
		PressInData.PSG1 =PressInData.Num_Dev/100;
		PressInData.PSG2 =PressInData.Num_Dev%100/10;
		PressInData.PSG3 =PressInData.Num_Dev%10;

		PressInData.PSG4 =PressInData.Buld/10;
		PressInData.PSG5 =PressInData.Buld%10;

		PressInData.PSG6 =PressInData.Unit%10;

		PressInData.PSG7 =PressInData.Floor/10;
		PressInData.PSG8 =PressInData.Floor%10;

		PressInData.PSG9 =PressInData.Cell/10;
		PressInData.PSG10 =PressInData.Cell%10;
		
	}

	INT8U DevType =SysDeviceList.Device[DEvNum].Type;
	switch (DevType)
	{
		case Meter_B :
		{
			STA1 =SysDevStatus[DEvNum].Device1.ComSucNum;		//热表通信成功次数
			STA2 =SysDevStatus[DEvNum].Device1.ComTolNum;		//热表通信总次数
			STA3 =SysDevStatus[DEvNum].Device1.ComFauNum; 	//热表通信失败次数

		}break;


		case Meter_U :
		{
			STA1 =SysDevStatus[DEvNum].Device2.ComSucNum;		//热表通信成功次数
			STA2 =SysDevStatus[DEvNum].Device2.ComTolNum;		//热表通信总次数
			STA3 =SysDevStatus[DEvNum].Device2.ComFauNum; 	//热表通信失败次数

		}break;

		case Valve_U :
		{
			STA1 =SysDevStatus[DEvNum].Device3.ComSucNum;		//热表通信成功次数
			STA2 =SysDevStatus[DEvNum].Device3.ComTolNum;		//热表通信总次数
			STA3 =SysDevStatus[DEvNum].Device3.ComFauNum; 	//热表通信失败次数		
		}break;

		case Valve_UH :
		{
			STA1 =SysDevStatus[DEvNum].Device4.ComSucNum;		//热表通信成功次数
			STA2 =SysDevStatus[DEvNum].Device4.ComTolNum;		//热表通信总次数
			STA3 =SysDevStatus[DEvNum].Device4.ComFauNum; 	//热表通信失败次数		
		}break;
#ifdef Meter_H_ENABLE
		case Meter_H :
		{
			STA1 =SysDevStatus[DEvNum].Device5.ComSucNum;		//热表通信成功次数
			STA2 =SysDevStatus[DEvNum].Device5.ComTolNum;		//热表通信总次数
			STA3 =SysDevStatus[DEvNum].Device5.ComFauNum; 	//热表通信失败次数
		}break;	
#endif
		default :break;

	}
	


	strcat(DATA1,"通信总数: ");
	strcat(DATA1,Disp_Integer(STA2));

	strcat(DATA2,"通信成功: ");
	strcat(DATA2,Disp_Integer(STA1));

	strcat(DATA3,"通信失败: ");
	strcat(DATA3,Disp_Integer(STA3));


	switch (CursorRecord)
	{
		case 1: G1 =1;break;
		case 2: G2 =1;break;
		case 3: G3 =1;break;
		case 4: G4 =1;break;
		case 5: G5 =1;break;
		case 6: G6 =1;break;
		case 7: G7 =1;break;
		case 8: G8 =1;break;
		case 9: G9 =1;break;
		case 10: G10 =1;break;
		default: break;
	}

	CH1[1] ='\0';
	CH2[1] ='\0';
	CH3[1] ='\0';
	CH4[1] ='\0';
	CH5[1] ='\0';
	CH6[1] ='\0';
	CH7[1] ='\0';
	CH8[1] ='\0';
	CH9[1] ='\0';
	CH10[1] ='\0';
	
	CH1[0] ='0'+(PressInData.Num_Dev /100);
	CH2[0] ='0'+(PressInData.Num_Dev%100/10);
	CH3[0] ='0'+(PressInData.Num_Dev %10);

	
	CH4[0] ='0'+(Buld/10);
	CH5[0] ='0'+(Buld%10);

	
	CH6[0] ='0'+(Unit%10);

	
	CH7[0] ='0'+(Floor/10);
	CH8[0] ='0'+(Floor%10);

	
	CH9[0] ='0'+(Cell/10);
	CH10[0] ='0'+(Cell%10);


    
	DispStringM(32,4,"--用户状态--",0,12);
	DispStringM(4,LineSpace*0+FirstSpace, "序号:   ",0,10);
	DispStringM(4+Fontspace*2+7,LineSpace*0+FirstSpace, CH1,G1,10);
	DispStringM(4+Fontspace*2+7+7,LineSpace*0+FirstSpace, CH2,G2,10);
	DispStringM(4+Fontspace*2+7+7+7,LineSpace*0+FirstSpace, CH3,G3,10);

	DispStringM(4,LineSpace*1+FirstSpace, CH4,G4,10);
	DispStringM(4+7,LineSpace*1+FirstSpace, CH5,G5,10);
	DispStringM(4+7+7,LineSpace*1+FirstSpace, "号楼",0,10);
	DispStringM(4+7+7+Fontspace*2,LineSpace*1+FirstSpace, CH6,G6,10);
	DispStringM(4+7+7+Fontspace*2+7,LineSpace*1+FirstSpace, "单元",0,10);
	DispStringM(4+7+7+Fontspace*2+7+Fontspace*2,LineSpace*1+FirstSpace,CH7,G7,10);
	DispStringM(4+7+7+Fontspace*2+7+Fontspace*2+7,LineSpace*1+FirstSpace,CH8,G8,10);
	DispStringM(4+7+7+Fontspace*2+7+Fontspace*2+7+7,LineSpace*1+FirstSpace,"层",0,10);
	DispStringM(4+7+7+Fontspace*2+7+Fontspace*3+7+7,LineSpace*1+FirstSpace,CH9,G9,10);
	DispStringM(4+7+7+Fontspace*2+7+Fontspace*3+7+7+7,LineSpace*1+FirstSpace,CH10,G10,10);



	DispStringM(4,LineSpace*3+FirstSpace+8, DATA1,0,10);
	DispStringM(4,LineSpace*4+FirstSpace+8 ,DATA2,0,10);
	DispStringM(4,LineSpace*5+FirstSpace+8 ,DATA3,0,10);


	
	Disp_1_X_UserFilter();

}



void Disp_1_2(void)
{
	INT16U LineSpace =32;
	INT16U FirstSpace =29;
    INT8U SU1 =0;
    INT8U SU2 =0;
    INT8U SU3 =0;
    
    if (( CursorRecord ==0)||( CursorRecord ==1))
    {
      CursorRecord =0;
      SU1 =1;
    }
    if ( CursorRecord ==2)
    {
      SU2 =1;
    }
    if ( CursorRecord ==3)
    {
      SU3 =1;
    }
    DispStringM(32,4,"--用户信息--",0,12);
    DispStringM(42,LineSpace*0+FirstSpace,"1.参数查看",SU1,11);
    DispStringM(42,LineSpace*1+FirstSpace,"2.实时数据",SU2,11);
    DispStringM(42,LineSpace*2+FirstSpace,"3.计量信息",SU3,11);
}



void Disp_1_2_1(void)
{
	INT8U  Fontspace =13;
	INT16U LineSpace =21;
	INT16U FirstSpace =30;
	INT16U UserID =0;

	HAL_StatusTypeDef  Backs =HAL_OK;
	INT16U DevNum =0;;
	INT8U G1 =0;
	INT8U G2 =0;
	INT8U G3 =0;
	INT8U G4 =0;
	INT8U G5 =0;
	INT8U G6 =0;
	INT8U G7 =0;
	INT8U G8 =0;
	INT8U G9 =0;
	INT8U G10 =0;
	
	char CH1[2];
	char CH2[2];
	char CH3[2];

	char CH4[2];
	char CH5[2];

	char CH6[2];

	char CH7[2];
	char CH8[2];

	char CH9[2];
	char CH10[2];

	char CH11[12];	//SN热表
	char CH12[12];	//SN阀门
	char CH13[7];	//建筑面积
	char CH14[12];	//用户ID


	
	INT8U Buld;
	INT8U Unit;
	INT8U Floor;
	INT8U Cell;
	
	INT32U USERID =0;
	INT16U SN2 =PressInData.Num_User;//终端序号
	INT16U CellArea = 0;//房间面积
	INT32U Meter_ID = 0;//热表序号
	INT32U Valve_ID = 0;//阀门序号


	UserID =PressInData.Num_User -1;
	

	if ( CursorRecord >3)
	{
		Buld = PressInData.Buld;//终端楼号
		Unit = PressInData.Unit;//终端单元号
		Floor = PressInData.Floor;//终端楼层号
		Cell = PressInData.Cell;//终端房间号
	}
	else
	{
		Buld =PressInData.Buld =	SysUserList.User[UserID].Buld;//终端楼号
		Unit =PressInData.Unit = 	SysUserList.User[UserID].Unit;//终端单元号
		Floor =PressInData.Floor =	SysUserList.User[UserID].Floor;//终端楼层号
		Cell = PressInData.Cell =	SysUserList.User[UserID].Cell;//终端房间号

		//用户序号回传
		PressInData.PSG1 =PressInData.Num_User/100;
		PressInData.PSG2 =PressInData.Num_User%100/10;
		PressInData.PSG3 =PressInData.Num_User%10;

		PressInData.PSG4 =PressInData.Buld/10;
		PressInData.PSG5 =PressInData.Buld%10;

		PressInData.PSG6 =PressInData.Unit%10;

		PressInData.PSG7 =PressInData.Floor/10;
		PressInData.PSG8 =PressInData.Floor%10;

		PressInData.PSG9 =PressInData.Cell/10;
		PressInData.PSG10 =PressInData.Cell%10;
	}

	Backs =GetDeviceNum( UserID,Meter_U,&DevNum);//热量表序列号
	Meter_ID =0;
	if(Backs ==HAL_OK)
	{
         Meter_ID =SysDeviceList.Device[DevNum].ID;
	}

	Backs =GetDeviceNum( UserID,Valve_U,&DevNum);//通断阀序列号
	Valve_ID =0;
	if(Backs ==HAL_OK)
	{
         Valve_ID =SysDeviceList.Device[DevNum].ID;
	}
	
	CellArea = SysUserList.User[UserID].CellArea;//房间面积

	USERID =SysUserList.User[UserID].User_ID;

	CH1[1] ='\0';
	CH2[1] ='\0';
	CH3[1] ='\0';
	
	CH4[1] ='\0';
	CH5[1] ='\0';
	
	CH6[1] ='\0';
	
	CH7[1] ='\0';
	CH8[1] ='\0';
	
	CH9[1] ='\0';
	CH10[1] ='\0';

	CH11[11] ='\0'; //SN热表
	CH12[11] ='\0'; //SN阀门
	CH13[6] ='\0'; //建筑面积
	CH14[11] ='\0'; //用户ID
	
	
	CH1[0] ='0'+(SN2 /100);
	CH2[0] ='0'+(SN2%100/10);
	CH3[0] ='0'+(SN2 %10);

	
	CH4[0] ='0'+(Buld/10);
	CH5[0] ='0'+(Buld%10);

	
	CH6[0] ='0'+(Unit%10);

	
	CH7[0] ='0'+(Floor/10);
	CH8[0] ='0'+(Floor%10);

	
	CH9[0] ='0'+(Cell/10);
	CH10[0] ='0'+(Cell%10);


	CH11[0] ='S';
	CH11[1] ='N';
	CH11[2] =':';
	CH11[3] ='0'+((Meter_ID>>28)&0X0F);
	CH11[4] ='0'+((Meter_ID>>24)&0X0F);
	CH11[5] ='0'+((Meter_ID>>20)&0X0F);
	CH11[6] ='0'+((Meter_ID>>16)&0X0F);
	CH11[7] ='0'+((Meter_ID>>12)&0X0F);
	CH11[8] ='0'+((Meter_ID>>8)&0X0F);
	CH11[9] ='0'+((Meter_ID>>4)&0X0F);
	CH11[10] ='0'+((Meter_ID>>0)&0X0F);	


	CH12[0] ='S';
	CH12[1] ='N';
	CH12[2] =':';
	CH12[3] ='0'+((Valve_ID>>28)&0X0F);
	CH12[4] ='0'+((Valve_ID>>24)&0X0F);
	CH12[5] ='0'+((Valve_ID>>20)&0X0F);
	CH12[6] ='0'+((Valve_ID>>16)&0X0F);
	CH12[7] ='0'+((Valve_ID>>12)&0X0F);
	CH12[8] ='0'+((Valve_ID>>8)&0X0F);
	CH12[9] ='0'+((Valve_ID>>4)&0X0F);
	CH12[10] ='0'+((Valve_ID>>0)&0X0F);	

	CH13[0] ='0'+(CellArea/10000);
	CH13[1] ='0'+(CellArea%10000/1000);
	CH13[2] ='0'+(CellArea%1000/100);
	CH13[3] ='.';
	
	CH13[4] ='0'+(CellArea%100/10);	
	CH13[5] ='0'+(CellArea%10);		


	CH14[0] ='I';
	CH14[1] ='D';
	CH14[2] =':';
	CH14[3] ='0'+((USERID>>28)&0X0F);
	CH14[4] ='0'+((USERID>>24)&0X0F);
	CH14[5] ='0'+((USERID>>20)&0X0F);
	CH14[6] ='0'+((USERID>>16)&0X0F);
	CH14[7] ='0'+((USERID>>12)&0X0F);
	CH14[8] ='0'+((USERID>>8)&0X0F);
	CH14[9] ='0'+((USERID>>4)&0X0F);
	CH14[10] ='0'+((USERID>>0)&0X0F);	


	switch (CursorRecord)
	{
		case 1: G1 =1;break;
		case 2: G2 =1;break;
		case 3: G3 =1;break;
		case 4: G4 =1;break;
		case 5: G5 =1;break;
		case 6: G6 =1;break;
		case 7: G7 =1;break;
		case 8: G8 =1;break;
		case 9: G9 =1;break;
		case 10: G10 =1;break;
		default: break;
	}
    
	DispStringM(32,4,"--用户参数--",0,12);
	DispStringM(4,LineSpace*0+FirstSpace, "序号:   ",0,10);
	DispStringM(4+Fontspace*2+7,LineSpace*0+FirstSpace, CH1,G1,10);
	DispStringM(4+Fontspace*2+7+7,LineSpace*0+FirstSpace, CH2,G2,10);
	DispStringM(4+Fontspace*2+7+7+7,LineSpace*0+FirstSpace, CH3,G3,10);

	DispStringM(4,LineSpace*1+FirstSpace, CH4,G4,10);
	DispStringM(4+7,LineSpace*1+FirstSpace, CH5,G5,10);
	DispStringM(4+7+7,LineSpace*1+FirstSpace, "号楼",0,10);
	DispStringM(4+7+7+Fontspace*2,LineSpace*1+FirstSpace, CH6,G6,10);
	DispStringM(4+7+7+Fontspace*2+7,LineSpace*1+FirstSpace, "单元",0,10);
	DispStringM(4+7+7+Fontspace*2+7+Fontspace*2,LineSpace*1+FirstSpace,CH7,G7,10);
	DispStringM(4+7+7+Fontspace*2+7+Fontspace*2+7,LineSpace*1+FirstSpace,CH8,G8,10);
	DispStringM(4+7+7+Fontspace*2+7+Fontspace*2+7+7,LineSpace*1+FirstSpace,"层",0,10);
	DispStringM(4+7+7+Fontspace*2+7+Fontspace*3+7+7,LineSpace*1+FirstSpace,CH9,G9,10);
	DispStringM(4+7+7+Fontspace*2+7+Fontspace*3+7+7+7,LineSpace*1+FirstSpace,CH10,G10,10);
	
	DispStringM(4,LineSpace*2+FirstSpace+4, "用户",0,10);//用户ID
	DispStringM(4+26,LineSpace*2+FirstSpace+4, CH14,0,10);//用户ID


	DispStringM(4,LineSpace*3+FirstSpace+4, "热表",0,10);//SN热表
	DispStringM(4+26,LineSpace*3+FirstSpace+4, CH11,0,10);//SN热表

	DispStringM(4,LineSpace*4+FirstSpace+4, "阀门",0,10);//SN阀门
	DispStringM(4+26,LineSpace*4+FirstSpace+4, CH12,0,10);//SN阀门
    
	DispStringM(4,LineSpace*5+FirstSpace+4,"建筑面积(平米):",0,10);//建筑面积
	DispStringM(4+7*3+Fontspace*6,LineSpace*5+FirstSpace+4,CH13,0,10);//建筑面积
	
    
	Disp_1_X_UserFilter();
}





void Disp_1_2_2(void)
{
	INT16U Fontspace =12;
	INT16U LineSpace =15;
	INT16U FirstSpace =21;
	INT32U USERID =0;
	HAL_StatusTypeDef Backs =HAL_OK;
	INT16U DevNum =0;
	INT8U G1 =0;
	INT8U G2 =0;
	INT8U G3 =0;
	INT8U G4 =0;
	INT8U G5 =0;
	INT8U G6 =0;
	INT8U G7 =0;
	INT8U G8 =0;
	INT8U G9 =0;
	INT8U G10 =0;
	
	char CH1[2];
	char CH2[2];
	char CH3[2];
	
	char CH4[2];
	char CH5[2];
	
	char CH6[2];
	
	char CH7[2];
	char CH8[2];
	
	char CH9[2];
	char CH10[2];
	
	char CH11[6];	//设定温度
	char CH12[6];	//室内温度
	char CH13[6];	//平均温度
	char CH14[6];	//进水温度
	char CH15[6];	//回水温度	
	char CH16[9];	//当前采集序号
	char CH17[12];	//用户ID
	

	INT16U SN2 =PressInData.Num_User;//终端序号
	INT16U UserID =PressInData.Num_User -1;
	
	INT8U Buld;
	INT8U Unit;
	INT8U Floor;
	INT8U Cell;
	INT16U Set_Temp =0;			//设定温度
	INT16U Cur_Temp =0 ;		//当前室内温度
	INT16U Ave_Temp =0;			//平均温度
	INT16U Input_Temp =0;		//进水温度
	INT16U Output_Temp =0;		//回水温度
	INT8U Valve_POS =Valve_Mid;	//阀门状态
	INT32U OpenTime =0;
	
	if ( CursorRecord >3)
	{
		Buld = PressInData.Buld;//终端楼号
		Unit = PressInData.Unit;//终端单元号
		Floor = PressInData.Floor;//终端楼层号
		Cell = PressInData.Cell;//终端房间号
	}
	else
	{
		Buld =PressInData.Buld =SysUserList.User[UserID].Buld;//终端楼号
		Unit =PressInData.Unit = SysUserList.User[UserID].Unit;//终端单元号
		Floor =PressInData.Floor = SysUserList.User[UserID].Floor;//终端楼层号
		Cell = PressInData.Cell =  SysUserList.User[UserID].Cell;//终端房间号

		//用户序号回传
		PressInData.PSG1 =PressInData.Num_User/100;
		PressInData.PSG2 =PressInData.Num_User%100/10;
		PressInData.PSG3 =PressInData.Num_User%10;

		PressInData.PSG4 =PressInData.Buld/10;
		PressInData.PSG5 =PressInData.Buld%10;

		PressInData.PSG6 =PressInData.Unit%10;

		PressInData.PSG7 =PressInData.Floor/10;
		PressInData.PSG8 =PressInData.Floor%10;

		PressInData.PSG9 =PressInData.Cell/10;
		PressInData.PSG10 =PressInData.Cell%10;
	}	
	
	
	if( SysPara.DeviceType !=Type_Valve)		//用户设备含有热量表
	{
		Backs =GetDeviceNum( UserID,Meter_U,&DevNum);//获取热量表序列号
		if(Backs ==HAL_OK)
		{
			Input_Temp = SysDevData[DevNum].Device2.Input_Temp;
			Output_Temp =SysDevData[DevNum].Device2.Output_Temp;
		}
		Backs =GetDeviceNum( UserID,Valve_U,&DevNum);	//通断控制器编号
		if(Backs ==HAL_OK)
		{
			Set_Temp =SysDevData[DevNum].Device3.Set_Temp;
			Cur_Temp = SysDevData[DevNum].Device3.Cur_Temp;
			Ave_Temp = SysDevData[DevNum].Device3.Ave_Temp;
			Valve_POS = SysDevData[DevNum].Device3.ValvePosition;
			OpenTime = SysDevData[DevNum].Device3.Cycle_OpTim;
		}
		USERID =SysUserList.User[UserID].User_ID;

	}
	else
	{
		Backs =GetDeviceNum( UserID,Valve_U,&DevNum);//通断控制器编号
		if(Backs ==HAL_OK)
		{
			Input_Temp = SysDevData[DevNum].Device3.Input_Temp;
			Output_Temp =SysDevData[DevNum].Device3.Output_Temp;
			Set_Temp =SysDevData[DevNum].Device3.Set_Temp;
			Cur_Temp = SysDevData[DevNum].Device3.Cur_Temp;
			Ave_Temp = SysDevData[DevNum].Device3.Ave_Temp;
			Valve_POS = SysDevData[DevNum].Device3.ValvePosition;
			OpenTime = SysDevData[DevNum].Device3.Cycle_OpTim;
			USERID =SysUserList.User[UserID].User_ID;
		}	
	}
	
	CH1[1] ='\0';
	CH2[1] ='\0';
	CH3[1] ='\0';
	
	CH4[1] ='\0';
	CH5[1] ='\0';
	
	CH6[1] ='\0';
	
	CH7[1] ='\0';
	CH8[1] ='\0';
	
	CH9[1] ='\0';
	CH10[1] ='\0';

	CH11[5] ='\0';
	CH12[5] ='\0';	
	CH13[5] ='\0';
	CH14[5] ='\0';
	CH15[5] ='\0';	
	CH16[8] ='\0';	
	CH17[11] ='\0'; //用户ID

	
	CH1[0] ='0'+(SN2 /100);//序号
	CH2[0] ='0'+(SN2%100/10);//序号
	CH3[0] ='0'+(SN2 %10);//序号

	CH4[0] ='0'+(Buld/10);//楼号
	CH5[0] ='0'+(Buld%10);//楼号

	
	CH6[0] ='0'+(Unit%10);//单元号

	
	CH7[0] ='0'+(Floor/10);//楼层号
	CH8[0] ='0'+(Floor%10);//楼层号

	
	CH9[0] ='0'+(Cell/10);//房间号
	CH10[0] ='0'+(Cell%10);//房间号

	//设定温度
	CH11[0] ='0'+(Set_Temp/1000);
	CH11[1] ='0'+(Set_Temp%1000/100);
	CH11[2] ='.';
	CH11[3] ='0'+(Set_Temp%100/10);
	CH11[4] ='0'+(Set_Temp%10);

	//室内温度
	CH12[0] ='0'+(Cur_Temp/1000);
	CH12[1] ='0'+(Cur_Temp%1000/100);
	CH12[2] ='.';
	CH12[3] ='0'+(Cur_Temp%100/10);
	CH12[4] ='0'+(Cur_Temp%10);

	//平均温度
	CH13[0] ='0'+(Ave_Temp/1000);
	CH13[1] ='0'+(Ave_Temp%1000/100);
	CH13[2] ='.';
	CH13[3] ='0'+(Ave_Temp%100/10);
	CH13[4] ='0'+(Ave_Temp%10);

	//进水温度
	CH14[0] ='0'+(Input_Temp/1000);
	CH14[1] ='0'+(Input_Temp%1000/100);
	CH14[2] ='.';
	CH14[3] ='0'+(Input_Temp%100/10);
	CH14[4] ='0'+(Input_Temp%10);

	//回水温度
	CH15[0] ='0'+(Output_Temp/1000);
	CH15[1] ='0'+(Output_Temp%1000/100);
	CH15[2] ='.';
	CH15[3] ='0'+(Output_Temp%100/10);
	CH15[4] ='0'+(Output_Temp%10);

	//当前用户开阀时间

	OpenTime =OpenTime/36;
	CH16[0] ='0'+(OpenTime/1000000);
	CH16[1] ='0'+(OpenTime%1000000/100000);
	CH16[2] ='0'+(OpenTime%100000/10000);
	CH16[3] ='0'+(OpenTime%10000/1000);
	
	CH16[4] ='0'+(OpenTime%1000/100);
	CH16[5] ='.';
	CH16[6] ='0'+(OpenTime%100/10);
	CH16[7] ='0'+(OpenTime%10);



	CH17[0] ='I';
	CH17[1] ='D';
	CH17[2] =':';
	CH17[3] ='0'+((USERID>>28)&0X0F);
	CH17[4] ='0'+((USERID>>24)&0X0F);
	CH17[5] ='0'+((USERID>>20)&0X0F);
	CH17[6] ='0'+((USERID>>16)&0X0F);
	CH17[7] ='0'+((USERID>>12)&0X0F);
	CH17[8] ='0'+((USERID>>8)&0X0F);
	CH17[9] ='0'+((USERID>>4)&0X0F);
	CH17[10] ='0'+((USERID>>0)&0X0F);	




  	switch (CursorRecord)
    {
        case 1: G1 =1;break;
        case 2: G2 =1;break;
        case 3: G3 =1;break;
        case 4: G4 =1;break;
        case 5: G5 =1;break;
        case 6: G6 =1;break;
        case 7: G7 =1;break;
        case 8: G8 =1;break;
        case 9: G9 =1;break;
        case 10: G10 =1;break;
        default: break;
    }

    DispStringM(32,4,"--实时数据--",0,12);
    DispStringM(4,LineSpace*0+FirstSpace, "序号:   ",0,9);
    DispStringM(4+Fontspace*2+6,LineSpace*0+FirstSpace, CH1,G1,9);
    DispStringM(4+Fontspace*2+6+6,LineSpace*0+FirstSpace, CH2,G2,9);
    DispStringM(4+Fontspace*2+6+6+6,LineSpace*0+FirstSpace, CH3,G3,9);

	DispStringM(4+52,LineSpace*0+FirstSpace, CH4,G4,9);
	DispStringM(4+6+52,LineSpace*0+FirstSpace, CH5,G5,9);
	DispStringM(4+6+6+52,LineSpace*0+FirstSpace, "号楼",0,9);
	DispStringM(4+6+6+Fontspace*2+52,LineSpace*0+FirstSpace, CH6,G6,9);
	DispStringM(4+6+6+Fontspace*2+6+52,LineSpace*0+FirstSpace, "单元",0,9);
	DispStringM(4+6+6+Fontspace*2+6+Fontspace*2+52,LineSpace*0+FirstSpace,CH7,G7,9);
	DispStringM(4+6+6+Fontspace*2+6+Fontspace*2+6+52,LineSpace*0+FirstSpace,CH8,G8,9);
	DispStringM(4+6+6+Fontspace*2+6+Fontspace*2+6+6+52,LineSpace*0+FirstSpace,"层",0,9);
	DispStringM(4+6+6+Fontspace*2+6+Fontspace*3+6+6+52,LineSpace*0+FirstSpace,CH9,G9,9);
	DispStringM(4+6+6+Fontspace*2+6+Fontspace*3+6+6+6+52,LineSpace*0+FirstSpace,CH10,G10,9);


	DispStringM(4,LineSpace*1+FirstSpace, "用户",0,10);//用户ID
	DispStringM(4+26,LineSpace*1+FirstSpace, CH17,0,10);//用户ID

   
	DispStringM(4,LineSpace*2+FirstSpace+4,"1.设定温度:",0,9);
	DispStringM(4+6*3+12*4,LineSpace*2+FirstSpace+4,CH11,0,9);
    
    DispStringM(4,LineSpace*3+FirstSpace+4,"2.室内温度:",0,9);
    DispStringM(4+6*3+12*4,LineSpace*3+FirstSpace+4,CH12,0,9);
    
    DispStringM(4,LineSpace*4+FirstSpace+4,"3.平均温度:",0,9);
    DispStringM(4+6*3+12*4,LineSpace*4+FirstSpace+4,CH13,0,9);
    
    DispStringM(4,LineSpace*5+FirstSpace+4,"4.进水温度:",0,9);
    DispStringM(4+6*3+12*4,LineSpace*5+FirstSpace+4,CH14,0,9);
    
    DispStringM(4,LineSpace*6+FirstSpace+4,"5.回水温度:",0,9);
    DispStringM(4+6*3+12*4,LineSpace*6+FirstSpace+4,CH15,0,9);

    if ( Valve_POS ==0X0A)
    {
    	DispStringM(4,LineSpace*7+FirstSpace+4,"6.阀门状态:开启",0,9);
    }
    else if( Valve_POS ==0XA0)
    {
    	DispStringM(4,LineSpace*7+FirstSpace+4,"6.阀门状态:关闭",0,9);
    }
    else
    {
		DispStringM(4,LineSpace*7+FirstSpace+4,"6.阀门状态:  ",0,9);
    }

	DispStringM(4,LineSpace*8+FirstSpace+4,"7.开阀时间(小时):  ",0,9);
	DispStringM(4+6*5+12*6,LineSpace*8+FirstSpace+4,CH16,0,9);
    
    Disp_1_X_UserFilter();
    
}





void Disp_1_2_3(void)
{
	static INT16U DevNum =0;
	HAL_StatusTypeDef BackVals =HAL_OK;
	HAL_StatusTypeDef Backs =HAL_OK;
	INT16U Fontspace =12;
	INT16U LineSpace =16;
	INT16U FirstSpace =25;
	INT8U G1 =0;
	INT8U G2 =0;
	INT8U G3 =0;
	INT8U G4 =0;
	INT8U G5 =0;
	INT8U G6 =0;
	INT8U G7 =0;
	INT8U G8 =0;
	INT8U G9 =0;
	INT8U G10 =0;
	INT32U USERID =0;
	
	char CH1[2];
	char CH2[2];
	char CH3[2];
	
	char CH4[2];
	char CH5[2];
	
	char CH6[2];
	
	char CH7[2];
	char CH8[2];
	
	char CH9[2];
	char CH10[2];

	
	char CH12[10];	//开阀时间
	char CH13[14];	//瞬时流量
	char CH14[12];	//累计流量
	char CH15[12];	//瞬时热量
	char CH16[13];	//累计热量
	char CH18[13];	//剩余热量

	char CH19[12];	//用户ID
	
	INT16U SN2 =PressInData.Num_User;//用户序号
	INT16U UserID =PressInData.Num_User -1;
	INT8U Buld;	//楼栋号
	INT8U Unit;	//单元号
	INT8U Floor;	//楼层号
	INT8U Cell ;	//房间号
	

	INT32U DATA2 = 0;		//开阀时间
	INT32U DATA3 = 0;		//瞬时流量
	INT32U DATA4 = 0;		//累计流量
	INT32U DATA5 = 0;		//瞬时热量
	INT32U DATA6 = 0;		//累计热量
	INT32S DATA8 = 0;		//剩余热量





	
	if ( CursorRecord >3)
	{
		Buld = PressInData.Buld;//终端楼号
		Unit = PressInData.Unit;//终端单元号
		Floor = PressInData.Floor;//终端楼层号
		Cell = PressInData.Cell;//终端房间号
	}
	else
	{
		Buld =PressInData.Buld = SysUserList.User[UserID].Buld;//终端楼号
		Unit =PressInData.Unit = SysUserList.User[UserID].Unit;//终端单元号
		Floor =PressInData.Floor = SysUserList.User[UserID].Floor;//终端楼层号
		Cell = PressInData.Cell = SysUserList.User[UserID].Cell;//终端房间号

		//用户序号回传
		PressInData.PSG1 =PressInData.Num_User/100;
		PressInData.PSG2 =PressInData.Num_User%100/10;
		PressInData.PSG3 =PressInData.Num_User%10;

		PressInData.PSG4 =PressInData.Buld/10;
		PressInData.PSG5 =PressInData.Buld%10;

		PressInData.PSG6 =PressInData.Unit%10;

		PressInData.PSG7 =PressInData.Floor/10;
		PressInData.PSG8 =PressInData.Floor%10;

		PressInData.PSG9 =PressInData.Cell/10;
		PressInData.PSG10 =PressInData.Cell%10;
	}



	if(SysPara.DeviceType ==Type_Valve)	//通断时间面积法热计量系统
	{

		Backs =GetDeviceNum( UserID,Valve_U,&DevNum);//通断控制器编号
		if(Backs ==HAL_OK)
		{
			DATA2 = SysDevData[DevNum].Device3.Cycle_OpTim;
		}	
		
		//顺时流量
		DATA3 =0;
		//累计流量
		DATA4 =0;
		//瞬时热量
		DATA5 =0;
	}
	else
	{
		BackVals =GetDeviceNum( UserID, Meter_U,&DevNum);		//获取用户热量表序号
		if(BackVals ==HAL_OK)	//成功获取用户热量表序号
		{
			//瞬时流量
			DATA3 =SysDevData[DevNum].Device2.Instant_Current;
			//累计流量
			DATA4 =SysDevData[DevNum].Device2.Total_Current;
			//瞬时热量
			DATA5 =SysDevData[DevNum].Device2.Instant_Energy;
			//累计热量
			DATA6 =SysDevData[DevNum].Device2.Total_Energy;
		}
	}

	
	//分摊热量/累计热量
	DATA6 =UserData[UserID].Apportion_Energy;		//该数据取自用户数据
	//剩余热量
	DATA8 =UserData[UserID].Remain_Heat;		//该数据取自用户数据





	
	CH1[1] ='\0';
	CH2[1] ='\0';
	CH3[1] ='\0';
	
	CH4[1] ='\0';
	CH5[1] ='\0';
	
	CH6[1] ='\0';
	
	CH7[1] ='\0';
	CH8[1] ='\0';
	
	CH9[1] ='\0';
	CH10[1] ='\0';


	CH12[7] ='\0';	
	CH13[7] ='\0';
	CH14[10] ='\0';
	CH16[12] ='\0';	

	
	CH1[0] ='0'+(SN2/100);//序号
	CH2[0] ='0'+(SN2%100/10);//序号
	CH3[0] ='0'+(SN2 %10);//序号

	CH4[0] ='0'+(Buld/10);//楼号
	CH5[0] ='0'+(Buld%10);//楼号

	
	CH6[0] ='0'+(Unit%10);//单元号

	
	CH7[0] ='0'+(Floor/10);//楼层号
	CH8[0] ='0'+(Floor%10);//楼层号

	
	CH9[0] ='0'+(Cell/10);//房间号
	CH10[0] ='0'+(Cell%10);//房间号

	INT32U OpenTime =0;


	//开阀时间	
	OpenTime =DATA2/36;
	CH12[0] ='0'+(OpenTime/1000000);
	CH12[1] ='0'+(OpenTime%1000000/100000);
	CH12[2] ='0'+(OpenTime%100000/10000);
	CH12[3] ='0'+(OpenTime%10000/1000);
	
	CH12[4] ='0'+(OpenTime%1000/100);
	CH12[5] ='.';
	CH12[6] ='0'+(OpenTime%100/10);
	CH12[7] ='0'+(OpenTime%10);

	CH12[8] ='h';
	CH12[9] ='\0';

	
	//瞬时流量
	CH13[0] ='0'+(DATA3/10000000);
	CH13[1] ='0'+(DATA3%10000000/1000000);
	CH13[2] ='0'+(DATA3%1000000/100000);
	CH13[3] ='0'+(DATA3%100000/10000);
	CH13[4] ='.';
	CH13[5] ='0'+(DATA3%10000/1000);
	CH13[6] ='0'+(DATA3%1000/100);
	CH13[7] ='0'+(DATA3%100/10);
	CH13[8] ='0'+(DATA3%10);
	
	CH13[9] ='m';
	CH13[10] ='3';
	CH13[11] ='/';
	CH13[12] ='h';
	CH13[13] ='\0';	

	//累计流量
	CH14[0] ='0'+(DATA4/10000000);
	CH14[1] ='0'+(DATA4%10000000/1000000);
	CH14[2] ='0'+(DATA4%1000000/100000);
	CH14[3] ='0'+(DATA4%100000/10000);
	CH14[4] ='0'+(DATA4%10000/1000);
	CH14[5] ='0'+(DATA4%1000/100);
	CH14[6] ='.';
	CH14[7] ='0'+(DATA4%100/10);
	CH14[8] ='0'+(DATA4%10);
	
	CH14[9] ='m';
	CH14[10] ='3';
	CH14[11] ='\0';	

	//瞬时热量
	CH15[0] ='0'+(DATA5/10000000);
	CH15[1] ='0'+(DATA5%10000000/1000000);
	CH15[2] ='0'+(DATA5%1000000/100000);
	CH15[3] ='0'+(DATA5%100000/10000);
	CH15[4] ='0'+(DATA5%10000/1000);
	CH15[5] ='0'+(DATA5%1000/100);
	CH15[6] ='.';
	CH15[7] ='0'+(DATA5%100/10);
	CH15[8] ='0'+(DATA5%10);
	
	CH15[9] ='k';
	CH15[10] ='W';
	CH15[11] ='\0';	
	
	//累计热量	
	CH16[0] ='0'+(DATA6/10000000);
	CH16[1] ='0'+(DATA6%10000000/1000000);
	CH16[2] ='0'+(DATA6%1000000/100000);
	CH16[3] ='0'+(DATA6%100000/10000);
	CH16[4] ='0'+(DATA6%10000/1000);
	CH16[5] ='0'+(DATA6%1000/100);
	CH16[6] ='.';
	CH16[7] ='0'+(DATA6%100/10);
	CH16[8] ='0'+(DATA6%10);
	CH16[9] ='k';
	CH16[10] ='W';
	CH16[11] ='h';
	CH16[12] ='\0';

	//剩余热量	
	CH18[0] ='0'+(DATA8/10000000);
	CH18[1] ='0'+(DATA8%10000000/1000000);
	CH18[2] ='0'+(DATA8%1000000/100000);
	CH18[3] ='0'+(DATA8%100000/10000);
	CH18[4] ='0'+(DATA8%10000/1000);
	CH18[5] ='0'+(DATA8%1000/100);
	CH18[6] ='.';
	CH18[7] ='0'+(DATA8%100/10);
	CH18[8] ='0'+(DATA8%10);
	CH18[9] ='k';
	CH18[10] ='W';
	CH18[11] ='h';	
	CH18[12] ='\0';	

	CH19[11] ='\0'; //用户ID
	USERID =SysUserList.User[UserID].User_ID;



	CH19[0] ='I';
	CH19[1] ='D';
	CH19[2] =':';
	CH19[3] ='0'+((USERID>>28)&0X0F);
	CH19[4] ='0'+((USERID>>24)&0X0F);
	CH19[5] ='0'+((USERID>>20)&0X0F);
	CH19[6] ='0'+((USERID>>16)&0X0F);
	CH19[7] ='0'+((USERID>>12)&0X0F);
	CH19[8] ='0'+((USERID>>8)&0X0F);
	CH19[9] ='0'+((USERID>>4)&0X0F);
	CH19[10] ='0'+((USERID>>0)&0X0F);	

	
	switch (CursorRecord)
	{
		case 1: G1 =1;break;
		case 2: G2 =1;break;
		case 3: G3 =1;break;
		case 4: G4 =1;break;
		case 5: G5 =1;break;
		case 6: G6 =1;break;
		case 7: G7 =1;break;
		case 8: G8 =1;break;
		case 9: G9 =1;break;
		case 10: G10 =1;break;
		default: break;
	}

	DispStringM(32,4,"--计量信息--",0,12);
	DispStringM(4,LineSpace*0+FirstSpace, "序号:   ",0,9);
	DispStringM(4+Fontspace*2+6,LineSpace*0+FirstSpace, CH1,G1,9);
	DispStringM(4+Fontspace*2+6+6,LineSpace*0+FirstSpace, CH2,G2,9);
	DispStringM(4+Fontspace*2+6+6+6,LineSpace*0+FirstSpace, CH3,G3,9);

	DispStringM(4+52,LineSpace*0+FirstSpace, CH4,G4,9);
	DispStringM(4+6+52,LineSpace*0+FirstSpace, CH5,G5,9);
	DispStringM(4+6+6+52,LineSpace*0+FirstSpace, "号楼",0,9);
	DispStringM(4+6+6+Fontspace*2+52,LineSpace*0+FirstSpace, CH6,G6,9);
	DispStringM(4+6+6+Fontspace*2+6+52,LineSpace*0+FirstSpace, "单元",0,9);
	DispStringM(4+6+6+Fontspace*2+6+Fontspace*2+52,LineSpace*0+FirstSpace,CH7,G7,9);
	DispStringM(4+6+6+Fontspace*2+6+Fontspace*2+6+52,LineSpace*0+FirstSpace,CH8,G8,9);
	DispStringM(4+6+6+Fontspace*2+6+Fontspace*2+6+6+52,LineSpace*0+FirstSpace,"层",0,9);
	DispStringM(4+6+6+Fontspace*2+6+Fontspace*3+6+6+52,LineSpace*0+FirstSpace,CH9,G9,9);
	DispStringM(4+6+6+Fontspace*2+6+Fontspace*3+6+6+6+52,LineSpace*0+FirstSpace,CH10,G10,9);


	DispStringM(4,LineSpace*1+FirstSpace, "用户",0,10);//用户ID
	DispStringM(4+26,LineSpace*1+FirstSpace, CH19,0,10);//用户ID



	DispStringM(4,LineSpace*2+FirstSpace,"1.开阀时间:",0,9);
	DispStringM(4+6*3+12*4,LineSpace*2+FirstSpace,CH12,0,9);

	DispStringM(4,LineSpace*3+FirstSpace,"2.瞬时流量:",0,9);
	DispStringM(4+6*3+12*4,LineSpace*3+FirstSpace,CH13,0,9);

	DispStringM(4,LineSpace*4+FirstSpace,"3.累计流量:",0,9);
	DispStringM(4+6*3+12*4,LineSpace*4+FirstSpace,CH14,0,9);

	DispStringM(4,LineSpace*5+FirstSpace,"4.瞬时热量:",0,9);
	DispStringM(4+6*3+12*4,LineSpace*5+FirstSpace,CH15,0,9);
	
	DispStringM(4,LineSpace*6+FirstSpace,"5.累计热量:",0,9);
	DispStringM(4+6*3+12*4,LineSpace*6+FirstSpace,CH16,0,9);	
    
	DispStringM(4,LineSpace*7+FirstSpace,"6.剩余热量:",0,9);
	DispStringM(4+6*3+12*4,LineSpace*7+FirstSpace,CH18,0,9);	
	Disp_1_X_UserFilter();
    
}




void Disp_1_3(void)
{
	INT16U LineSpace =23;
	INT16U FirstSpace =28;
    INT8U SU1 =0;
    INT8U SU2 =0; 
    INT8U SU3 =0;
    INT8U SU4 =0;
    INT8U SU5 =0;

    
    if (( CursorRecord ==0)||( CursorRecord ==1))
    {
      CursorRecord =0;
      SU1 =1;
    }
    if ( CursorRecord ==2)
    {
      SU2 =1;
    }
    if ( CursorRecord ==3)
    {
      SU3 =1;
    }
    if ( CursorRecord ==4)
    {
      SU4 =1;
    }

    if ( CursorRecord ==5)
    {
      SU5 =1;
    }
    DispStringM(32,4,"--系统设置--",0,12);
    DispStringM(42,LineSpace*0+FirstSpace,"1.通信设置",SU1,11);
	DispStringM(42,LineSpace*1+FirstSpace,"2.时间设置",SU2,11);
    DispStringM(42,LineSpace*2+FirstSpace,"3.密码修改",SU3,11);
    DispStringM(42,LineSpace*3+FirstSpace,"4.出厂设置",SU4,11);
    DispStringM(42,LineSpace*4+FirstSpace,"5.设备类型",SU5,11);
}








void Disp_1_3_1(void)
{
	INT16U LineSpace =16;
	INT16U FirstSpace =35;
	INT8U G1 =0;
	INT8U G2 =0;
	INT8U G3 =0;
	INT8U G4 =0;
	INT8U G5 =0;
	INT8U G6 =0;
	INT8U G7 =0;
	INT8U G8 =0;
	INT8U G9 =0;
	INT8U G10 =0;
	INT8U G11 =0;
	INT8U G12 =0;
	INT8U G13 =0;
	INT8U G14 =0;
	INT8U G15 =0;
	INT8U G16 =0;
	INT8U G17 =0;

	
	INT8U IP1=PressInData.IP1;
	INT8U IP2=PressInData.IP2;
	INT8U IP3=PressInData.IP3;
	INT8U IP4=PressInData.IP4;
	INT16U PORT =PressInData.PORT;


	char CH1[2];//IP1
	char CH2[2];
	char CH3[2];

	char CH4[2];//IP2
	char CH5[2];
	char CH6[2];
	
	char CH7[2];//IP3
	char CH8[2];
	char CH9[2];
	
	char CH10[2];//IP4
	char CH11[2];
	char CH12[2];
	
	char CH13[2];//PORT
	char CH14[2];
	char CH15[2];
	char CH16[2];
	char CH17[2];
	

	

	 CH1[1] ='\0';//IP1
	 CH2[1] ='\0';
	 CH3[1] ='\0';

	 CH4[1] ='\0';//IP2
	 CH5[1] ='\0';
	 CH6[1] ='\0';
	
	 CH7[1] ='\0';//IP3
	 CH8[1] ='\0';
	 CH9[1] ='\0';
	
	 CH10[1] ='\0';//IP4
	 CH11[1] ='\0';
	 CH12[1] ='\0';
	
	 CH13[1] ='\0';//PORT
	 CH14[1] ='\0';
	 CH15[1] ='\0';
	 CH16[1] ='\0';
	 CH17[1] ='\0';
	

	


	 CH1[0] ='0'+(IP1/100);//IP1
	 CH2[0] ='0'+(IP1%100/10);
	 CH3[0] ='0'+(IP1%10);

	 CH4[0] ='0'+(IP2/100);//IP2
	 CH5[0] ='0'+(IP2%100/10);
	 CH6[0] ='0'+(IP2%10);
	
	 CH7[0] ='0'+(IP3/100);//IP3
	 CH8[0] ='0'+(IP3%100/10);
	 CH9[0] ='0'+(IP3%10);
	
	 CH10[0] ='0'+(IP4/100);//IP3
	 CH11[0] ='0'+(IP4%100/10);
	 CH12[0] ='0'+(IP4%10);


	 CH13[0] ='0'+(PORT/10000);//PORT
	 CH14[0] ='0'+(PORT%10000/1000);
	 CH15[0] ='0'+(PORT%1000/100);
	 CH16[0] ='0'+(PORT%100/10); 
	 CH17[0] ='0'+(PORT%10);

	 switch (CursorRecord)
	 {
		case 1: G1=1;break;
		case 2: G2=1;break;
		case 3: G3=1;break;
		case 4: G4=1;break;
		case 5: G5=1;break;
		case 6: G6=1;break;	
		case 7: G7=1;break;
		case 8: G8=1;break;
		case 9: G9=1;break;
		case 10: G10=1;break;
		case 11: G11=1;break;
		case 12: G12=1;break;
		case 13: G13=1;break;
		case 14: G14=1;break;
		case 15: G15=1;break;
		case 16: G16=1;break;	
		case 17: G17=1;break;

		default:break;
	}
	
	DispStringM(32,4,"--通信设置--",0,12);
	DispStringM(4,LineSpace*0+FirstSpace,"通信服务器设置",0,10);
	DispStringM(8,LineSpace*1+FirstSpace+2,"  主站IP:",0,9);
	DispStringM(8+6*5+12*2+6*0,LineSpace*1+FirstSpace+2,CH1,G1,9);
	DispStringM(8+6*5+12*2+6*1,LineSpace*1+FirstSpace+2,CH2,G2,9);
	DispStringM(8+6*5+12*2+6*2,LineSpace*1+FirstSpace+2,CH3,G3,9);

	DispStringM(8+6*5+12*2+6*3,LineSpace*1+FirstSpace+2,".",0,9);

	DispStringM(8+6*5+12*2+6*4,LineSpace*1+FirstSpace+2,CH4,G4,9);
	DispStringM(8+6*5+12*2+6*5,LineSpace*1+FirstSpace+2,CH5,G5,9);
	DispStringM(8+6*5+12*2+6*6,LineSpace*1+FirstSpace+2,CH6,G6,9);

	DispStringM(8+6*5+12*2+6*7,LineSpace*1+FirstSpace+2,".",0,9);

	DispStringM(8+6*5+12*2+6*8,LineSpace*1+FirstSpace+2,CH7,G7,9);
	DispStringM(8+6*5+12*2+6*9,LineSpace*1+FirstSpace+2,CH8,G8,9);
	DispStringM(8+6*5+12*2+6*10,LineSpace*1+FirstSpace+2,CH9,G9,9);

	DispStringM(8+6*5+12*2+6*11,LineSpace*1+FirstSpace+2,".",0,9);

	DispStringM(8+6*5+12*2+6*12,LineSpace*1+FirstSpace+2,CH10,G10,9);
	DispStringM(8+6*5+12*2+6*13,LineSpace*1+FirstSpace+2,CH11,G11,9);
	DispStringM(8+6*5+12*2+6*14,LineSpace*1+FirstSpace+2,CH12,G12,9);

	DispStringM(8,LineSpace*2+FirstSpace+2,"  端口号:",0,9);
	DispStringM(8+12*3+6*3,LineSpace*2+FirstSpace+2,CH13,G13,9);
	DispStringM(8+12*3+6*4,LineSpace*2+FirstSpace+2,CH14,G14,9);
	DispStringM(8+12*3+6*5,LineSpace*2+FirstSpace+2,CH15,G15,9);
	DispStringM(8+12*3+6*6,LineSpace*2+FirstSpace+2,CH16,G16,9);
	DispStringM(8+12*3+6*7,LineSpace*2+FirstSpace+2,CH17,G17,9);
	Disp_1_3_DataSaveFlag();


    
}





void Disp_1_3_4(void)    //时间设置
{
	INT8U LineSpace =23;
	INT8U FirstSpace =32;
	
	INT8U GA1 =0;
	INT8U GA2 =0;
	INT8U GA3 =0;
	INT8U GA4 =0;
	INT8U GA5 =0;
	INT8U GA6 =0;
	INT8U GA7 =0;
	INT8U GA8 =0;
	INT8U GA9 =0;
	INT8U GA10 =0;
	INT8U GA11 =0;
	INT8U GA12 =0;
	INT8U GA13 =0;
	
	INT8U GB1 =0;
	INT8U GB2 =0;
	INT8U GB3 =0;
	INT8U GB4 =0;
	INT8U GB5 =0;
	INT8U GB6 =0;

	INT8U GC1 =0;
	INT8U GC2 =0;
	INT8U GC3 =0;
	INT8U GC4 =0;
	INT8U GC5 =0;
	INT8U GC6 =0;

	char CH1[2];
	char CH2[2];
	char CH3[2];
	char CH4[2];
	char CH5[2];
	char CH6[2];
	char CH7[2];
	char CH8[2];
	char CH9[2];
	char CH10[2];
	char CH11[2];
	char CH12[2];
	
	char CH14[2];
	char CH15[2];
	char CH16[2];
	char CH17[2];
	char CH18[2];
	char CH19[2];
	
	char CH20[2];
	char CH21[2];
	char CH22[2];
	char CH23[2];
	char CH24[2];
	char CH25[2];

	INT16U Nian = PressInData.C_Year;
	INT8U Yue  =PressInData.C_Month;
	INT8U Ri = PressInData.C_Day;
	INT8U Shi = PressInData.C_Hour;
	INT8U Fen = PressInData.C_Minute;
	INT8U Miao = PressInData.C_Second;
	INT8U Zhou = PressInData.C_Week;

	INT16U S_Nian =PressInData.S_Year;
	INT8U S_Yue =PressInData.S_Month;
	INT8U S_Ri =PressInData.S_Day;

	INT16U F_Nian =PressInData.F_Year;
	INT8U F_Yue =PressInData.F_Month;
	INT8U F_Ri =PressInData.F_Day;
	

	CH1[1] ='\0';
	CH2[1] ='\0';
	CH3[1] ='\0';
	CH4[1] ='\0';
	CH5[1] ='\0';
	CH6[1] ='\0';
	CH7[1] ='\0';
	CH8[1] ='\0';
	CH9[1] ='\0';
	CH10[1] ='\0';
	CH11[1] ='\0';
	CH12[1] ='\0';

	CH14[1] ='\0';
	CH15[1] ='\0';
	CH16[1] ='\0';
	CH17[1] ='\0';
	CH18[1] ='\0';
	CH19[1] ='\0';

	CH20[1] ='\0';
	CH21[1] ='\0';
	CH22[1] ='\0';
	CH23[1] ='\0';
	CH24[1] ='\0';
	CH25[1] ='\0';

	CH1[0] ='0'+(Nian/10);
	CH2[0] ='0'+(Nian%10);

	CH3[0] ='0'+(Yue/10);
	CH4[0] ='0'+(Yue%10);

	CH5[0] ='0'+(Ri/10);
	CH6[0] ='0'+(Ri%10);

	CH7[0] ='0'+(Shi/10);
	CH8[0] ='0'+(Shi%10);

	CH9[0] ='0'+(Fen/10);
	CH10[0] ='0'+(Fen%10);

	CH11[0] ='0'+(Miao/10);
	CH12[0] ='0'+(Miao%10);
	
	CH14[0] ='0'+(S_Nian/10);
	CH15[0] ='0'+(S_Nian%10);

	CH16[0] ='0'+(S_Yue/10);
	CH17[0] ='0'+(S_Yue%10);

	CH18[0] ='0'+(S_Ri/10);
	CH19[0] ='0'+(S_Ri%10);

	CH20[0] ='0'+(F_Nian/10);
	CH21[0] ='0'+(F_Nian%10);

	CH22[0] ='0'+(F_Yue/10);
	CH23[0] ='0'+(F_Yue%10);

	CH24[0] ='0'+(F_Ri/10);
	CH25[0] ='0'+(F_Ri%10);


	switch (CursorRecord)
	{
		case 1: GA1 =1;break;
		case 2: GA2 =1;break;
		case 3: GA3 =1;break;
		case 4: GA4 =1;break;
		case 5: GA5 =1;break;
		case 6: GA6 =1;break;
		case 7: GA7 =1;break;
		case 8: GA8 =1;break;
		case 9: GA9 =1;break;
		case 10: GA10 =1;break;
		case 11: GA11 =1;break;
		case 12: GA12 =1;break;
		case 13: GA13 =1;break;
		
		case 14: GB1 =1;break;
		case 15: GB2 =1;break;
		case 16: GB3 =1;break;
		case 17: GB4 =1;break;
		case 18: GB5 =1;break;
		case 19: GB6 =1;break;

		case 20: GC1 =1;break;
		case 21: GC2 =1;break;
		case 22: GC3 =1;break;
		case 23: GC4 =1;break;
		case 24: GC5 =1;break;
		case 25: GC6 =1;break;
		
		default :  break;
	}


	DispStringM(32,4,"--时间设置--",0,12);
	DispStringM(14,LineSpace*0+FirstSpace,"20",0,10);
	DispStringM(14+7*2,LineSpace*0+FirstSpace,CH1,GA1,10);
	DispStringM(14+7*3,LineSpace*0+FirstSpace,CH2,GA2,10);
	DispStringM(14+7*4,LineSpace*0+FirstSpace,"年",0,10);
	DispStringM(14+7*4+13*1,LineSpace*0+FirstSpace,CH3,GA3,10);
	DispStringM(14+7*5+13*1,LineSpace*0+FirstSpace,CH4,GA4,10);
	DispStringM(14+7*6+13*1,LineSpace*0+FirstSpace,"月",0,10);
	DispStringM(14+7*6+13*2,LineSpace*0+FirstSpace,CH5,GA5,10);
	DispStringM(14+7*7+13*2,LineSpace*0+FirstSpace,CH6,GA6,10);
	DispStringM(14+7*8+13*2,LineSpace*0+FirstSpace,"日",0,10);

    
   
	DispStringM(14,LineSpace*1+FirstSpace,CH7,GA7,10);
	DispStringM(14+7*1,LineSpace*1+FirstSpace,CH8,GA8,10);
	DispStringM(14+7*2,LineSpace*1+FirstSpace,"时",0,10);
	DispStringM(14+7*2+13*1,LineSpace*1+FirstSpace,CH9,GA9,10);
	DispStringM(14+7*3+13*1,LineSpace*1+FirstSpace,CH10,GA10,10);
	DispStringM(14+7*4+13*1,LineSpace*1+FirstSpace,"分",0,10);
	DispStringM(14+7*4+13*2,LineSpace*1+FirstSpace,CH11,GA11,10);
	DispStringM(14+7*5+13*2,LineSpace*1+FirstSpace,CH12,GA12,10);
	DispStringM(14+7*6+13*2,LineSpace*1+FirstSpace,"秒",0,10);
    
	if (Zhou ==0)
	{
		DispStringM(14,LineSpace*2+FirstSpace,"星期",GA13,10);
		DispStringM(14+13*2,LineSpace*2+FirstSpace,"日",GA13,10);
	}
    	else if ( Zhou ==1)
	{
		DispStringM(14,LineSpace*2+FirstSpace,"星期",GA13,10);
		DispStringM(14+13*2,LineSpace*2+FirstSpace,"一",GA13,10);
	}
	 else if ( Zhou ==2)
	{
		DispStringM(14,LineSpace*2+FirstSpace,"星期",GA13,10);
		DispStringM(14+13*2,LineSpace*2+FirstSpace,"二",GA13,10);
	}
	else if ( Zhou ==3)
	 {
		DispStringM(14,LineSpace*2+FirstSpace,"星期",GA13,10);
		DispStringM(14+13*2,LineSpace*2+FirstSpace,"三",GA13,10);
	 }
	 else if ( Zhou ==4)
	{
		DispStringM(14,LineSpace*2+FirstSpace,"星期",GA13,10);
		DispStringM(14+13*2,LineSpace*2+FirstSpace,"四",GA13,10);
	}
	 else if ( Zhou ==5)
	 {
		DispStringM(14,LineSpace*2+FirstSpace,"星期",GA13,10);
		DispStringM(14+13*2,LineSpace*2+FirstSpace,"五",GA13,10);
	 }
    	else if ( Zhou ==6)
	{
		DispStringM(14,LineSpace*2+FirstSpace,"星期",GA13,10);
		DispStringM(14+13*2,LineSpace*2+FirstSpace,"六",GA13,10);
	}
   	 else
	{
		DispStringM(14,LineSpace*2+FirstSpace,"星期",GA13,10);
		DispStringM(14+13*2,LineSpace*2+FirstSpace,"日",GA13,10);
	}
	DispStringM(14,LineSpace*3+FirstSpace,"供暖开始:20",0,10);
	DispStringM(14+13*5+7*1,LineSpace*3+FirstSpace,CH14,GB1,10);
	DispStringM(14+13*5+7*2,LineSpace*3+FirstSpace,CH15,GB2,10);
	
	DispStringM(14+13*5+7*3,LineSpace*3+FirstSpace,"-",0,10);
	
	DispStringM(14+13*5+7*4,LineSpace*3+FirstSpace,CH16,GB3,10);
	DispStringM(14+13*5+7*5,LineSpace*3+FirstSpace,CH17,GB4,10);

	DispStringM(14+13*5+7*6,LineSpace*3+FirstSpace,"-",0,10);
	
	DispStringM(14+13*5+7*7,LineSpace*3+FirstSpace,CH18,GB5,10);
	DispStringM(14+13*5+7*8,LineSpace*3+FirstSpace,CH19,GB6,10);

	
	DispStringM(14,LineSpace*4+FirstSpace,"供暖结束:20",0,10);
	DispStringM(14+13*5+7*1,LineSpace*4+FirstSpace,CH20,GC1,10);
	DispStringM(14+13*5+7*2,LineSpace*4+FirstSpace,CH21,GC2,10);
	
	DispStringM(14+13*5+7*3,LineSpace*4+FirstSpace,"-",0,10);
	
	DispStringM(14+13*5+7*4,LineSpace*4+FirstSpace,CH22,GC3,10);
	DispStringM(14+13*5+7*5,LineSpace*4+FirstSpace,CH23,GC4,10);

	DispStringM(14+13*5+7*6,LineSpace*4+FirstSpace,"-",0,10);
	
	DispStringM(14+13*5+7*7,LineSpace*4+FirstSpace,CH24,GC5,10);
	DispStringM(14+13*5+7*8,LineSpace*4+FirstSpace,CH25,GC6,10);
	
	Disp_1_3_DataSaveFlag();
    
};





void Disp_1_3_5(void)    //密码设置
{

	INT16U LineSpace =25;
	INT16U FirstSpace =35;
	INT8U G1 =0;
	INT8U G2 =0;
	INT8U G3 =0;
	INT8U G4 =0;
	INT8U G5 =0;
	INT8U G6 =0;
	INT8U G7 =0;
	INT8U G8 =0;

	char CH1[2];
	char CH2[2];
	char CH3[2];
	char CH4[2];
	char CH5[2];
	char CH6[2];
	char CH7[2];
	char CH8[2];


	INT16U PSWX = PressInData.PSW1;
	INT16U PSWQ  =PressInData.PSW2;

	CH1[1] ='\0';
	CH2[1] ='\0';
	CH3[1] ='\0';
	CH4[1] ='\0';
	CH5[1] ='\0';
	CH6[1] ='\0';
	CH7[1] ='\0';
	CH8[1] ='\0';

	CH1[0] =(((PSWX>>12)&0X0F)>9)?('0'+7+((PSWX>>12)&0X0F)):('0'+((PSWX>>12)&0X0F));
	CH2[0] =(((PSWX>>8)&0X0F)>9)?('0'+7+((PSWX>>8)&0X0F)):('0'+((PSWX>>8)&0X0F));
	CH3[0] =(((PSWX>>4)&0X0F)>9)?('0'+7+((PSWX>>4)&0X0F)):('0'+((PSWX>>4)&0X0F));
	CH4[0] =(((PSWX>>0)&0X0F)>9)?('0'+7+((PSWX>>0)&0X0F)):('0'+((PSWX>>0)&0X0F));

	CH5[0] =(((PSWQ>>12)&0X0F)>9)?('0'+7+((PSWQ>>12)&0X0F)):('0'+((PSWQ>>12)&0X0F));
	CH6[0] =(((PSWQ>>8)&0X0F)>9)?('0'+7+((PSWQ>>8)&0X0F)):('0'+((PSWQ>>8)&0X0F));
	CH7[0] =(((PSWQ>>4)&0X0F)>9)?('0'+7+((PSWQ>>4)&0X0F)):('0'+((PSWQ>>4)&0X0F));
	CH8[0] =(((PSWQ>>0)&0X0F)>9)?('0'+7+((PSWQ>>0)&0X0F)):('0'+((PSWQ>>0)&0X0F));    

	switch (CursorRecord)
	{
		case 1: G1 =1;break;
		case 2: G2 =1;break;
		case 3: G3 =1;break;
		case 4: G4 =1;break;
		case 5: G5 =1;break;
		case 6: G6 =1;break;
		case 7: G7 =1;break;
		case 8: G8 =1;break;
		default :    break;
	}

	DispStringM(32,4,"--密码设置--",0,12);
	DispStringM(10,LineSpace*0+FirstSpace,"密码修改:[",0,11);
	DispStringM(10+15*4+8*2,LineSpace*0+FirstSpace,CH1,G1,11);
	DispStringM(10+15*4+8*3,LineSpace*0+FirstSpace,CH2,G2,11);
	DispStringM(10+15*4+8*4,LineSpace*0+FirstSpace,CH3,G3,11);
	DispStringM(10+15*4+8*5,LineSpace*0+FirstSpace,CH4,G4,11);
	DispStringM(10+15*4+8*6,LineSpace*0+FirstSpace,"]",0,11);

	DispStringM(10,LineSpace*1+FirstSpace+5,"密码确认:[",0,11);
	DispStringM(10+15*4+8*2,LineSpace*1+FirstSpace+5,CH5,G5,11);
	DispStringM(10+15*4+8*3,LineSpace*1+FirstSpace+5,CH6,G6,11);
	DispStringM(10+15*4+8*4,LineSpace*1+FirstSpace+5,CH7,G7,11);
	DispStringM(10+15*4+8*5,LineSpace*1+FirstSpace+5,CH8,G8,11);
	DispStringM(10+15*4+8*6,LineSpace*1+FirstSpace+5,"]",0,11);
	Disp_1_3_PasswordError();

};




void Disp_1_3_6(void)
{
	INT16U LineSpace =25;
	INT16U FirstSpace =35;
	INT8U G1 =0;
	INT8U G2 =0;
	
	switch (CursorRecord)
	{
	    case 1: G1 =1;break;
	    case 2: G2 =1;break;
	    default:break;
	}

    DispStringM(32,4,"--出厂设置--",0,12);
    DispStringM(6,LineSpace*0+FirstSpace,"清除装置所有数据",0,9);
    DispStringM(35,LineSpace*1+FirstSpace+5,"确认",G1,11);
    DispStringM(35+15*2+8*4,LineSpace*1+FirstSpace+5,"取消",G2,11);
    Disp_1_3_DataSaveFlag();
}







void Disp_1_3_7(void)
{
	INT16U LineSpace =25;
	INT16U FirstSpace =38;
	INT8U G1 =0;
	INT8U G2 =0;
	INT8U G3 =0;
	INT8U G4 =0;
	INT8U G5 =0;
	INT8U G6 =0;	
	INT8U G7 =0;
	INT8U G8 =0;
	INT8U G9 =0;
	INT32U Device_SN =PressInData.Device_SN;//序列号 用户热量表
	INT8U DeviceType = PressInData.DeviceType;

	char CH1[2];
	char CH2[2];
	char CH3[2];
	char CH4[2];
	char CH5[2];
	char CH6[2];
	char CH7[2];
	char CH8[2];

	CH1[1] ='\0';
	CH2[1] ='\0';
	CH3[1] ='\0';
	CH4[1] ='\0';
	CH5[1] ='\0';
	CH6[1] ='\0';
	CH7[1] ='\0';
	CH8[1] ='\0';

	CH1[0] ='0'+((Device_SN>>28)&0X0F);//设备编号 序列号
	CH2[0] ='0'+((Device_SN>>24)&0X0F);
	CH3[0] ='0'+((Device_SN>>20)&0X0F);
	CH4[0] ='0'+((Device_SN>>16)&0X0F);
	CH5[0] ='0'+((Device_SN>>12)&0X0F);
	CH6[0] ='0'+((Device_SN>>8)&0X0F);
	CH7[0] ='0'+((Device_SN>>4)&0X0F);
	CH8[0] ='0'+((Device_SN>>0)&0X0F);
	
	
	
	switch (CursorRecord)
	{
	    case 1: G1 =1;break;
	    case 2: G2 =1;break;
	    case 3: G3 =1;break;
	    case 4: G4 =1;break;
	    case 5: G5 =1;break;
	    case 6: G6 =1;break;	
	    case 7: G7 =1;break;
	    case 8: G8 =1;break;
	    case 9: G9 =1;break;	    
	    default:break;
	}

    DispStringM(32,4,"--设备类型--",0,12);
    DispStringM(10,LineSpace*0+FirstSpace,"请配置设备类型",0,11);
	if( DeviceType ==1)
	{
		DispStringM(34,LineSpace*1+FirstSpace+5,"热量表采集系统",G1,10);
	}
	else if( DeviceType ==2)
	{
		DispStringM(21,LineSpace*1+FirstSpace+5,"温控计量一体化系统",G1,10);
	}
	else if( DeviceType ==3)
	{
		DispStringM(15,LineSpace*1+FirstSpace+5,"通断时间面积计量系统",G1,10);
	}
	else
	{
		DispStringM(34,LineSpace*1+FirstSpace+5,"系统类型未设定",G1,10);
	}
    
	DispStringM(4,LineSpace*2+FirstSpace,"  设备编号:",0,10);
	DispStringM(4+7*11,LineSpace*2+FirstSpace,CH1,G2,10);
	DispStringM(4+7*12,LineSpace*2+FirstSpace,CH2,G3,10);
	DispStringM(4+7*13,LineSpace*2+FirstSpace,CH3,G4,10);
	DispStringM(4+7*14,LineSpace*2+FirstSpace,CH4,G5,10);
	DispStringM(4+7*15,LineSpace*2+FirstSpace,CH5,G6,10);
	DispStringM(4+7*16,LineSpace*2+FirstSpace,CH6,G7,10);
	DispStringM(4+7*17,LineSpace*2+FirstSpace,CH7,G8,10);
	DispStringM(4+7*18,LineSpace*2+FirstSpace,CH8,G9,10);
}




void Disp_1_4(void)
{
	INT16U LineSpace =23;
	INT16U FirstSpace =29;
	char CH1[2];
	char CH2[9];
//	char CH3[4];
	char CH4[4];
	
	INT16U SN1=PressInData.Num_BuldMeter-1;//热表序号
	INT32U SN=PressInData.Meter_ID = BuildMeters[SN1].ID;//热表序列号
	INT16U ChannelUserNum =PressInData.ChannelUserNum = BuildMeters[SN1].Users;//管路用户数量
	
	CH1[1] ='\0';
	CH2[8] ='\0';
//	CH3[3] ='\0';
	CH4[3] ='\0';

	CH1[0] ='0'+SN1+1;			//热表序号
	
	CH2[0] ='0'+((SN>>28)&0X0F);//热表SN
	CH2[1] ='0'+((SN>>24)&0X0F);
	CH2[2] ='0'+((SN>>20)&0X0F);
	CH2[3] ='0'+((SN>>16)&0X0F);
	CH2[4] ='0'+((SN>>12)&0X0F);
	CH2[5] ='0'+((SN>>8)&0X0F);
	CH2[6] ='0'+((SN>>4)&0X0F);
	CH2[7] ='0'+((SN>>0)&0X0F);
	

	CH4[0] ='0'+(ChannelUserNum/100);	//通道用户数量
	CH4[1] ='0'+(ChannelUserNum%100/10);
	CH4[2] ='0'+(ChannelUserNum%10); 


	

    DispStringM(32,4,"--热表信息--",0,12);
    DispStringM(4,LineSpace*0+FirstSpace, "  热表序号:",0,11);
    DispStringM(4+15*4+8*3,LineSpace*0+FirstSpace,CH1,1,11);
    
    DispStringM(4,LineSpace*1+FirstSpace+4, "1.热表SN:",0,11);
    DispStringM(4+15*2+8*5,LineSpace*1+FirstSpace+4,CH2,0,11);

 //   DispStringM(4,LineSpace*2+FirstSpace+4, "2.起始用户序号:",0,11);
  //  DispStringM(4+15*6+8*3,LineSpace*2+FirstSpace+4, CH3,0,11);

    DispStringM(4,LineSpace*3+FirstSpace+4, "2.管路用户数量:",0,11);
    DispStringM(4+15*6+8*3,LineSpace*3+FirstSpace+4,CH4,0,11);
	
    DispStringM(4,LineSpace*4+FirstSpace+4,"3.当前热表状态->>>",0,11);
}





void Disp_1_4_1(void)
{
	INT16U LineSpace =15;
	INT16U FirstSpace =24;
	char CH1[2];		//热表序号
	char CH2[7];		//进水温度
	char CH3[7];		//回水温度
	char CH4[14];		//瞬时流量
	char CH5[13];		//瞬时能量
	char CH6[10];		//累计流量
	char CH7[13];		//累计能量
	char CH8[13];		//分摊能量
	char CH9[9];		//运行时间

	INT16U SN1=PressInData.Num_BuldMeter-1;		//热表序号

	INT16U Input_Temp = 0;		//进水温度
	INT16U Output_Temp =0;		//回水温度

	INT32U Instant_Current =0;		//瞬时流量
	
	
	INT32U Instant_Energy =0;		//瞬时热量
	INT8U Instant_Energy_Unit =0;	//瞬时流量单位

	INT32U Total_Current =0;		//累计流量

	INT32U Total_Energy =0;		//累计热量
	INT8U Total_Energy_Unit =0;
	
	INT32U Apportion_Energy =0;	//分摊热量
	INT32U Working_Time =0;		//工作时间 

	if(SysDeviceList.Device[SN1].Type ==Meter_B)
	{
		Input_Temp = SysDevData[SN1].Device1.Input_Temp;			//进水温度
		Output_Temp =SysDevData[SN1].Device1.Output_Temp;			//回水温度

		Instant_Current =SysDevData[SN1].Device1.Instant_Current;		//瞬时流量		
		
		Instant_Energy =SysDevData[SN1].Device1.Instant_Energy;			//瞬时热量
		Instant_Energy_Unit =SysDevData[SN1].Device1.Instant_Energy_Unit;	//瞬时流量单位

		Total_Current =SysDevData[SN1].Device1.Total_Current;			//累计流量

		Total_Energy =SysDevData[SN1].Device1.Total_Energy;			//累计热量
		Total_Energy_Unit =SysDevData[SN1].Device1.Total_Energy_Unit;

		Apportion_Energy =SysDevData[SN1].Device1.Apportion_Energy;		//周期热量
		Working_Time =SysDevData[SN1].Device1.Work_Time;  			//工作时间 
	}
#ifdef Meter_H_ENABLE
	else if( SysDeviceList.Device[SN1].Type ==Meter_H)
	{

		Input_Temp = SysDevData[SN1].Device5.Input_Temp;			//进水温度
		Output_Temp =SysDevData[SN1].Device5.Output_Temp;			//回水温度

		Instant_Current =SysDevData[SN1].Device5.Instant_Current;		//瞬时流量
		
		Instant_Energy =SysDevData[SN1].Device5.Instant_Energy;			//瞬时热量
		Instant_Energy_Unit =SysDevData[SN1].Device5.Instant_Energy_Unit;	//瞬时流量单位

		Total_Current =SysDevData[SN1].Device5.Total_Current;			//累计流量

		Total_Energy =SysDevData[SN1].Device5.Total_Energy;			//累计热量
		Total_Energy_Unit =SysDevData[SN1].Device5.Total_Energy_Unit;

		Apportion_Energy =SysDevData[SN1].Device5.Apportion_Energy;		//周期热量
		Working_Time =SysDevData[SN1].Device5.Work_Time;  			//工作时间 
	}
#endif


	CH1[2-1] ='\0'; 	//热表序号
	CH2[7-1] ='\0'; 	//进水温度
	CH3[7-1] ='\0'; 	//回水温度
	CH4[14-1] ='\0'; 	//瞬时流量
	CH5[13-1] ='\0'; 	//瞬时能量
	CH6[10-1] ='\0'; 	//累计流量
	CH7[13-1] ='\0'; 	//累计能量
	CH8[13-1] ='\0'; 	//分摊能量
	CH9[9-1] ='\0'; 	//运行时间

	CH1[0] ='0'+(SN1%10)+1; //热表序号
	
	CH2[0] ='0'+(Input_Temp/10000); //进水温度
	CH2[1] ='0'+(Input_Temp%10000/1000); //进水温度
	CH2[2] ='0'+(Input_Temp%1000/100);  //进水温度
	CH2[3] ='.';//进水温度
	CH2[4] ='0'+(Input_Temp%100/10); //进水温度
	CH2[5] ='0'+(Input_Temp%10); //进水温度	
	
	CH3[0] ='0'+(Output_Temp/10000); //回水温度
	CH3[1] ='0'+(Output_Temp%10000/1000); //回水温度
	CH3[2] ='0'+(Output_Temp%1000/100); //回水温度
	CH3[3] ='.'; //回水温度	
	CH3[4] ='0'+(Output_Temp%100/10); //回水温度
	CH3[5] ='0'+(Output_Temp%10); //回水温度	

	CH4[0] ='0'+(Instant_Current/10000000); //流速
	CH4[1] ='0'+(Instant_Current%10000000/1000000);  //流速
	CH4[2] ='0'+(Instant_Current%1000000/100000); //流速
	CH4[3] ='0'+(Instant_Current%100000/10000); //流速
	CH4[4] ='.'; 
	CH4[5] ='0'+(Instant_Current%10000/1000); //流速		
	CH4[6] ='0'+(Instant_Current%1000/100); //流速
	CH4[7] ='0'+(Instant_Current%100/10); //流速
	CH4[8] ='0'+(Instant_Current%10); //流速
	CH4[9] ='m'; 
	CH4[10] ='0'+3; 
	CH4[11] ='/'; 
	CH4[12] ='h'; 
	
	CH5[0] ='0'+(Instant_Energy/10000000); //瞬时热量  热功率
	CH5[1] ='0'+(Instant_Energy%10000000/1000000); //瞬时能量	
	CH5[2] ='0'+(Instant_Energy%1000000/100000); //瞬时能量
	CH5[3] ='0'+(Instant_Energy%100000/10000); //瞬时能量
	CH5[4] ='0'+(Instant_Energy%10000/1000); //瞬时能量	
	CH5[5] ='0'+(Instant_Energy%1000/100); //瞬时能量
	CH5[6] ='.'; //瞬时能量
	CH5[7] ='0'+(Instant_Energy%100/10); //瞬时能量
	CH5[8] ='0'+(Instant_Energy%10); //瞬时能量

	if( Instant_Energy_Unit ==MW)
	{
		CH5[9] ='M'; //瞬时能量	
		CH5[10] ='W'; //瞬时能量
		CH5[11] ='\0'; //瞬时能量
	}
	else
	{
		CH5[9] ='k'; //瞬时能量	
		CH5[10] ='W'; //瞬时能量
		CH5[11] ='\0'; //瞬时能量
	}
	
	CH6[0] ='0'+(Total_Current/10000000); //累计流量
	CH6[1] ='0'+(Total_Current%10000000/1000000); //累计流量
	CH6[2] ='0'+(Total_Current%1000000/100000); //累计流量
	CH6[3] ='0'+(Total_Current%100000/10000); //累计流量
	CH6[4] ='0'+(Total_Current%10000/1000); //累计流量
	CH6[5] ='0'+(Total_Current%1000/100); //累计流量
	CH6[6] ='.'; //累计流量
	CH6[7] ='0'+(Total_Current%100/10); //累计流量
	CH6[8] ='0'+(Total_Current%10); //累计流量


	
	CH7[0] ='0'+(Total_Energy/10000000); //累计热量
	CH7[1] ='0'+(Total_Energy%10000000/1000000); //累计热量
	CH7[2] ='0'+(Total_Energy%1000000/100000); //累计热量
	CH7[3] ='0'+(Total_Energy%100000/10000); //累计热量
	CH7[4] ='0'+(Total_Energy%10000/1000); //累计热量
	CH7[5] ='0'+(Total_Energy%1000/100); //累计热量
	CH7[6] ='.'; //累计热量
	CH7[7] ='0'+(Total_Energy%100/10); //累计热量
	CH7[8] ='0'+(Total_Energy%10); //累计热量

	
	if( Total_Energy_Unit ==MW_h)
	{
		CH7[9] ='M'; //累计热量
		CH7[10] ='W'; //累计热量
		CH7[11] ='h'; //累计热量

		
		CH8[9] ='M'; //分摊热量
		CH8[10] ='W'; //分摊热量
		CH8[11] ='h'; //分摊热量
	}
	else
	{
	
		CH7[9] ='k'; //累计热量
		CH7[10] ='W'; //累计热量
		CH7[11] ='h'; //累计热量

		CH8[9] ='k'; //分摊热量
		CH8[10] ='W'; //分摊热量
		CH8[11] ='h'; //分摊热量
	}

	CH8[0] ='0'+(Apportion_Energy/10000000); //分摊热量
	CH8[1] ='0'+(Apportion_Energy%10000000/1000000); //分摊热量
	CH8[2] ='0'+(Apportion_Energy%1000000/100000); //分摊热量
	CH8[3] ='0'+(Apportion_Energy%100000/10000); //分摊热量
	CH8[4] ='0'+(Apportion_Energy%10000/1000); //分摊热量
	CH8[5] ='0'+(Apportion_Energy%1000/100); //分摊热量
	CH8[6] ='.'; //分摊热量
	CH8[7] ='0'+(Apportion_Energy%100/10); //分摊热量
	CH8[8] ='0'+(Apportion_Energy%10); //分摊热量

	


	CH9[0] ='0'+(Working_Time/10000000); //运行时间
	CH9[1] ='0'+(Working_Time%10000000/1000000); //运行时间
	CH9[2] ='0'+(Working_Time%1000000/100000); //运行时间
	CH9[3] ='0'+(Working_Time%100000/10000); //运行时间
	CH9[4] ='0'+(Working_Time%10000/1000); //运行时间
	CH9[5] ='0'+(Working_Time%1000/100); //运行时间
	CH9[6] ='0'+(Working_Time%100/10); //运行时间
	CH9[7] ='0'+(Working_Time%10); //运行时间

    DispStringM(32,4,"--热表状态--",0,12);
    DispStringM(4,LineSpace*0+FirstSpace, "  热表序号:",0,9);
    DispStringM(4+12*4+6*3,LineSpace*0+FirstSpace,CH1,1,9);
    
    DispStringM(4,LineSpace*1+FirstSpace, "1.进水温度:",0,9);
    DispStringM(4+12*4+6*3,LineSpace*1+FirstSpace, CH2,0,9);
    
    DispStringM(4,LineSpace*2+FirstSpace, "2.回水温度:",0,9);
    DispStringM(4+12*4+6*3,LineSpace*2+FirstSpace, CH3,0,9);
    
	DispStringM(4,LineSpace*3+FirstSpace, "3.瞬时流量:",0,9);
	DispStringM(4+12*4+6*3,LineSpace*3+FirstSpace, CH4,0,9);
	
    DispStringM(4,LineSpace*4+FirstSpace ,"4.瞬时热量:",0,9);
    DispStringM(4+12*4+6*3,LineSpace*4+FirstSpace ,CH5,0,9);
    
    DispStringM(4,LineSpace*5+FirstSpace ,"5.累计流量:",0,9);
    DispStringM(4+12*4+6*3,LineSpace*5+FirstSpace ,CH6,0,9);
    DispStringM(4+12*4+6*12,LineSpace*5+FirstSpace ,"m3",0,9);
    
    DispStringM(4,LineSpace*6+FirstSpace ,"6.累计热量:",0,9);
    DispStringM(4+12*4+6*3,LineSpace*6+FirstSpace ,CH7,0,9);

    
    DispStringM(4,LineSpace*7+FirstSpace ,"7.周期热量:",0,9);
	DispStringM(4+12*4+6*3,LineSpace*7+FirstSpace ,CH8,0,9);
    
    DispStringM(4,LineSpace*8+FirstSpace ,"8.运行时间:",0,9);
    DispStringM(4+12*4+6*3,LineSpace*8+FirstSpace ,CH9,0,9);
    DispStringM(4+12*4+6*12,LineSpace*8+FirstSpace ,"小时",0,9);
    


    
}





/*
 * 函数名称：void DisplayManager()
 * 函数功能：实时显示由按键操作引起的显示更新
 * 触发源：  按键响应2017090500011


 */
void DisplayManager(void)
{
	if ( ScreenRecord.ra1 ==0)
	{
		Clear_VisionBUF();  // 清空显存
		Disp_Open();
	}

	else if( ScreenRecord.ra1 ==1)
	{
		Clear_VisionBUF();  				// 清空显存
			
		if (ScreenRecord.ra2 ==0 )			// 主菜单1
		{
			Disp_1();  
		}
		else if (ScreenRecord.ra2 ==1 )     //系统状态
        {
            switch ( ScreenRecord.ra3)
            {
                case 0:  
                {
					Disp_1_1();
                };break;
                case 1:      //设备自检
                {
                	if(CursorRecord ==1)
                	{
						Disp_1_1_1A();
                	}
                	else
                	{
						Disp_1_1_1B();
                	}
                };break;
                case 2:     // 终端状态
                {
                	if (ScreenRecord.ra4 ==0)//终端状态 总览
                	{
	                	if ((CursorRecord<=128)&&(CursorRecord>0))
	                	{
	                		Disp_1_1_2A();
	                	}
	                	else if((CursorRecord<=256)&&(CursorRecord>128))
	                	{
	                		Disp_1_1_2B();
	                	}
	                   	else if(CursorRecord>256)
	                	{
	                		Disp_1_1_2C();
	                	}
	                }
	                else if(ScreenRecord.ra4 ==1)//终端状态细节
	                {
	                	Disp_1_1_2_1();
	                }
					
                };break;
                case 3:     // 热表状态
                {
					Disp_1_1_3();
                };break;
                
                case 4:     // 版本信息
                {
                	if(CursorRecord ==1)
                	{
						Disp_1_1_4A();
                	}
                	else
                	{
						Disp_1_1_4B();
                	}
					
                };break;	

				case 5:     // 版本信息
                {
                	if(CursorRecord ==1)
                	{
						Disp_1_1_5A();
                	}
                	else
                	{
						
                	}
					
                };break;	            

                
                default :break;
            }
        }
	        else if (ScreenRecord.ra2 ==2 )	//用户信息
	        {
	            if ( ScreenRecord.ra3 ==0)		//用户信息
	            {
	            	Disp_1_2 ();
	            }
	            else if ( ScreenRecord.ra3 ==1) //用户参数
	            {
	            	Disp_1_2_1();
	            }
	            else if ( ScreenRecord.ra3 ==2) //用户状态
	            {
					Disp_1_2_2();
	            }
	            else if ( ScreenRecord.ra3 ==3) //计量信息
	            {
					Disp_1_2_3();
	            }
	        }
	        
	        else if (ScreenRecord.ra2 ==3 )	//系统设置
	        {
	            if ( ScreenRecord.ra3 ==0)		//系统设置
	            {
	                Disp_1_3 ();
	            }
	            if (( ScreenRecord.ra3 !=0)&&(PressInData.correct ==0))//系统设置密码输入界面
	            {
	            	Disp_1_3PassWord();
	            }
	            if  (( ScreenRecord.ra3 ==1)&&(PressInData.correct ==1))	//通信设置
	            {
					Disp_1_3_1();
				}
	            if  (( ScreenRecord.ra3 ==2)&&(PressInData.correct ==1))	//时间设置
	            {
					Disp_1_3_4();
				}
	            if  (( ScreenRecord.ra3 ==3)&&(PressInData.correct ==1))	//密码设置
	            {
					Disp_1_3_5();
				}
	            if  (( ScreenRecord.ra3 ==4)&&(PressInData.correct ==1))	//出厂设置
	            {
					Disp_1_3_6();
				}
				
	            if  (( ScreenRecord.ra3 ==5)&&(PressInData.correct ==1))	//设备类型
	            {
					Disp_1_3_7();
				}				
	        }
	        
	        else if (ScreenRecord.ra2 ==4 )	//热表信息
	        {
	            if ( ScreenRecord.ra3 ==0)		//热表信息
	            {
	                Disp_1_4();
	            }		
			if ( ScreenRecord.ra3 ==1)		//热表状态
			{
				 Disp_1_4_1();
	        }	
		}
	}
}





 
/* END */
/*
 @copy COPYRIGHT 2016 Foryon     
*/
 




 
