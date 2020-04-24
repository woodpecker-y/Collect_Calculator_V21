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
* @author :
* @date :2018/3/11 15:28
***************************************************************
*/ 
#define _DEBUG_C_
#include "debug.h"
#include "rtx_cli.h"
#include "pubdef.h"
#include "similarlinux.h"
#include "updateparm.h"





/*
*  Command buffer API
*/

void get_version(char *pcWriteBuffer, int xWriteBufferLen,int argc, char **argv)
{
	cmd_printf("version: %u\r\n", SYSTEM_VERSION);
}


void uptime_Command(char *pcWriteBuffer, int xWriteBufferLen,int argc, char **argv)
{
	cmd_printf("UP time %ld\r\n", SystemTick_ms);
}



void reboot(char *pcWriteBuffer, int xWriteBufferLen,int argc, char **argv)
{
	cli_printf("rebootting...\r\n");
	NVIC_SystemReset();
}



void setEnvParameter(char *pcWriteBuffer, int xWriteBufferLen,int argc, char **argv)
{
	if(0 == down_env_data())
	{
		cmd_printf("Update parameter success");
	}
	else
	{
		cmd_printf("Update parameter fail");
	}
}

void setServer(char *pcWriteBuffer, int xWriteBufferLen,int argc, char **argv)
{
	int setRes;
	/* 判断参数数量是否合法 */
	if(argc != 3)
	{
		goto WRONGCMD;
	}
  
	/* 设置服务器地址 */
	setRes = updateServerIP(argv);
	if (0 == setRes)
	{
		cmd_printf("Set server parameter success");
	}
	else if(-1 == setRes)
	{
		cmd_printf("port error");
	}
	else if(-2 == setRes)
	{
		cmd_printf("ip error");
	}
	else if(-3 == setRes)
	{
		cmd_printf("save to flash error");
	}
	else if(-4 == setRes)
	{
		cmd_printf("save to dtu error");
	}
	return;
	
    WRONGCMD:
    cmd_printf("Usage: setip <ip> <port>\r\n");
}

void printServer(char *pcWriteBuffer, int xWriteBufferLen,int argc, char **argv)
{
	Server_Parm serverIP;
	printServerIP(&serverIP);
	cmd_printf("IP: %d.%d.%d.%d:%d\r\n",serverIP.IP1, serverIP.IP2, serverIP.IP3, serverIP.IP4, serverIP.Port);
}

void ps(char *pcWriteBuffer, int xWriteBufferLen,int argc, char **argv)
{
	if(1 == argc)
	{
		ps_none();
	}
  	else if(2 == argc)
	{
		if(NULL == strcmp(argv[1], "-a"))
		{
			ps_a();
		}
		else if(NULL == strcmp(argv[1], "-A"))
		{
			ps_A();
		}
		else
		{
		  	goto WRONGCMD;
		}
	}
	else if(3 == argc)
	{
		int PID = atoi(argv[2]);
		if(0 != PID)
		{
			ps_p(PID);
		}
		else
		{
			goto WRONGCMD;
		}
	}
	return;

	WRONGCMD:
	cmd_printf("Usage:\r\n ps [options]\r\n -a Task System State\r\n -A all Task List\r\n -p Task Information by PID");
}


void saveData(char *pcWriteBuffer, int xWriteBufferLen,int argc, char **argv)
{
	int res;
	res = SaveLog();
	
	if(0 == res)
	{
		cmd_printf("write success");
	}
	else
	{
		cmd_printf("write fial");
	}
}

void mem(char *pcWriteBuffer, int xWriteBufferLen,int argc, char **argv)
{
	freecmd();
}

void alarm(char *pcWriteBuffer, int xWriteBufferLen,int argc, char **argv)
{
	printAllAlarm();
}


void changedevnum(char *pcWriteBuffer, int xWriteBufferLen,int argc, char **argv)
{
	if(2 != argc)
	{
		cmd_printf("Usage: changedevnum -num");
		return;
	}
	int num = atoi(argv[1]);
	
	if(num < 0)
	{
		cmd_printf("Usage: changedevnum -num");
		return;
	}
	changeDeviceNum(num);
}





 
/* END */
/*
 @copy COPYRIGHT 2016 Foryon     
*/
 




 
