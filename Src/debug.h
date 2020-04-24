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
* @date :2018/3/11 15:28
***************************************************************
*/ 
#ifndef _DEBUG_H_
#define _DEBUG_H_


#include "FreeRTOS.h"
#include "cmsis_os.h"
#include "stdio.h"
#include "string.h"

#ifdef _DEBUG_C_
#define DEBUG_EXT
#else
#define DEBUG_EXT extern
#endif




#ifdef _DEBUG_C_




#endif





#define DEBUG					1


/* 打印级别定义 */
#define DEBUG_EMERG 			0
#define DEBUG_ALERT 			1
#define DEBUG_CRIT				2
#define DEBUG_ERR				3
#define DEBUG_WARNING			4
#define DEBUG_NOTICE			5
#define DEBUG_INFO				6
#define DEBUG_DEBUG			    7

#define DEFAULT_DEBUG_LEVEL		DEBUG_WARNING

// ==== LOGGING ====
#ifdef __GNUC__
#define SHORT_FILE strrchr(__FILE__, '/') ? strrchr(__FILE__, '/') + 1 : __FILE__
#else
#define SHORT_FILE strrchr(__FILE__, '\\') ? strrchr(__FILE__, '\\') + 1 : __FILE__
#endif

extern int os_debug_enabled;
extern int os_debug_level;
extern osMutexId printMutexHandle;


#define os_printf(M, ...) do {	osMutexWait(printMutexHandle, osWaitForever);\
							printf(M, ##__VA_ARGS__);\
							osMutexRelease(printMutexHandle);}\
							while(0==1)

#define dbg_printf(N, M, ...) do {	if (os_debug_enabled==0 || N > os_debug_level)break;\
									osMutexWait(printMutexHandle, osWaitForever);\
									printf("\r\n[%u] [%d] [ %s->%4d ]  "M"\r\n", osKernelSysTick(), N, SHORT_FILE, __LINE__, ##__VA_ARGS__);\
									osMutexRelease(printMutexHandle);}\
									while(0==1)




DEBUG_EXT void get_version(char *pcWriteBuffer, int xWriteBufferLen,int argc, char **argv);
DEBUG_EXT void uptime_Command(char *pcWriteBuffer, int xWriteBufferLen,int argc, char **argv);
DEBUG_EXT void reboot(char *pcWriteBuffer, int xWriteBufferLen,int argc, char **argv);
DEBUG_EXT void setEnvParameter(char *pcWriteBuffer, int xWriteBufferLen,int argc, char **argv);
DEBUG_EXT void setServer(char *pcWriteBuffer, int xWriteBufferLen,int argc, char **argv);
DEBUG_EXT void printServer(char *pcWriteBuffer, int xWriteBufferLen,int argc, char **argv);
DEBUG_EXT void ps(char *pcWriteBuffer, int xWriteBufferLen,int argc, char **argv);
DEBUG_EXT void saveData(char *pcWriteBuffer, int xWriteBufferLen,int argc, char **argv);
DEBUG_EXT void mem(char *pcWriteBuffer, int xWriteBufferLen,int argc, char **argv);
DEBUG_EXT void alarm(char *pcWriteBuffer, int xWriteBufferLen,int argc, char **argv);
DEBUG_EXT void changedevnum(char *pcWriteBuffer, int xWriteBufferLen,int argc, char **argv);










																	
#endif
									/* END */
									/*	
									 @copy COPYRIGHT 2016 Foryon	 
									*/	
									 

