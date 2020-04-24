#include "watchdog.h"



void IWDG_Guard(void *argument);

EventGroupHandle_t iwdgEventGroup;
uint8_t iwdgCount;
IWDG_Wait_t waitTimes[MAXEVENTCOUNT];

TaskHandle_t guard_Handle = NULL;
osMutexId iwdgMutexHandle;

/* 看门狗互斥锁初始化 */
int iwdg_MetexInit(void)
{
	osMutexDef(iwdgMutex);
	iwdgMutexHandle = osMutexCreate(osMutex(iwdgMutex));
	
	if(iwdgMutexHandle == NULL)
	{
		return -1;
	}
	return 0;
}

/* 软件看门狗初始化
此函数只可开机调用一次
*/
int dogInit(void)
{
	BaseType_t thread_res;
#ifdef IWDG_ENABLE
	
	iwdgEventGroup = NULL;
	iwdgCount = 0;
	int iwdg_Metex_Res;
	
	memset(waitTimes,0x00,sizeof(waitTimes));
	
	iwdg_Metex_Res = iwdg_MetexInit();
	if(-1 == iwdg_Metex_Res)
	{
		dbg_printf(DEBUG_ERR, "IWDG Metex create fail...");
		return -1;
	}
	
	/* 创建喂狗事件组 */
	iwdgEventGroup = xEventGroupCreate();
	if(NULL == iwdgEventGroup)
	{
		dbg_printf(DEBUG_ERR, "IWDG Event Group Create fail...");
		return -1;
	}
	
#endif
	
	/* 启动守护进程 */
	thread_res = xTaskCreate(IWDG_Guard,"IWDG Guard",128,NULL,10,&guard_Handle);	
	if(pdTRUE != thread_res)
	{
		return -1;
	}
	
	return 0;
}

/** 创建一个软件看门狗
@event 事件标志
@millisec 最长喂狗间隔
**/
int createIWDG(EventBits_t *event, uint32_t sec)
{
	
#ifdef IWDG_ENABLE
	
	osMutexWait(iwdgMutexHandle, osWaitForever);
	
	if(iwdgCount >= MAXEVENTCOUNT)
	{
		return -1;
	}
	
	*event = 1 << iwdgCount;
	waitTimes[iwdgCount].ticks = 0;
	waitTimes[iwdgCount].waitTime = 1000*sec/GUARDINTERVAL;
	iwdgCount++;
	
	osMutexRelease(iwdgMutexHandle);

#endif
	return 0;
}

/* 喂狗 */
void feedIWDG(EventBits_t iwdg)
{
#ifdef IWDG_ENABLE
	xEventGroupSetBits(iwdgEventGroup,iwdg);
#endif
}

/* 守护进程 */
void IWDG_Guard(void *argument)
{

#ifdef IWDG_ENABLE	

	EventBits_t iwdgBits;
	static EventBits_t iwdgBitscp;
	int isDead;
	
	for(;;)
	{
		osMutexWait(iwdgMutexHandle, osWaitForever);
		
		/* 没有注册软件看门狗 */
		if(0 == iwdgCount)
		{
			dbg_printf(DEBUG_ERR, "Have not any iwdg create...");
			for(;;)
			{
				SP706_Toggle;
				osDelay(pdMS_TO_TICKS(GUARDINTERVAL));
			}
		}
		
		EventBits_t iwdg_Bit_All;
		iwdg_Bit_All = (0xFFFFFFFF<<iwdgCount)^0xFFFFFFFF;
		iwdgBits = xEventGroupWaitBits(iwdgEventGroup, iwdg_Bit_All, pdTRUE, pdFALSE, 1);
		iwdgBitscp =iwdgBits;					//2017年12月4日
		/* 判断有没有线程没有在超时时间内喂狗并对已经喂狗的清除超时计数 */
		isDead = 0;
		for(int i=0;i<iwdgCount;i++)
		{
			iwdgBits = iwdgBitscp >> i;		//2017年12月4日
			if(0x01 == (0x01 & iwdgBits))
			{
				waitTimes[i].ticks = 0;
			}
			else
			{
				waitTimes[i].ticks++;
			}
			if(waitTimes[i].ticks >= waitTimes[i].waitTime)
			{
				/* 有线程未喂狗 */
				isDead++;
			}
		}
		osMutexRelease(iwdgMutexHandle);
		
		if(0 == isDead)
		{
			SP706_Toggle;
		}
		else
		{
			dbg_printf(DEBUG_ERR, "Have thread is dead...");
			NVIC_SystemReset();
		}
		osDelay(pdMS_TO_TICKS(GUARDINTERVAL));
	}

#else
	for(;;)
	{
		SP706_Toggle;
		osDelay(pdMS_TO_TICKS(GUARDINTERVAL));
	}
#endif	

}










