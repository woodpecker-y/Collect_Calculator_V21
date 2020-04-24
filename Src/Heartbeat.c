#include "heartbeat.h"


EventGroupHandle_t HbEventGroup;
volatile TickType_t lastRevOrSend;

/* 
心跳检测功能模块初始化
*/
int HbInit(void)
{
#ifdef HEARTBEAT_ENABLE
    HbEventGroup = NULL;
	
	/* 创建心跳事件组 */
	HbEventGroup = xEventGroupCreate();
	if(NULL == HbEventGroup)
	{
		dbg_printf(DEBUG_ERR, "Heartbeat Event Group Create fail...");
		return -1;
    }
    lastRevOrSend = xTaskGetTickCount();
#endif
	return 0;
}

/* TCP 发送数据事件 */
void tcpSendEvent(void)
{
#ifdef HEARTBEAT_ENABLE
	xEventGroupSetBits(HbEventGroup,TCPSEND_EVENT);
#endif
}

/* TCP 接收数据事件 */
void tcpRevEvent(void)
{
#ifdef HEARTBEAT_ENABLE
	xEventGroupSetBits(HbEventGroup,TCPREV_EVENT);
#endif
}

/* 心跳处理任务 */
void HbMainTask(void)
{
    
#ifdef HEARTBEAT_ENABLE	

    EventBits_t HbBits;
    static int trytimes = 0;
    int op_res;


    /* 判断是否有TCP接收或发送事件 */
    HbBits = xEventGroupWaitBits(HbEventGroup, TCPSEND_EVENT | TCPREV_EVENT, pdTRUE, pdFALSE, 1);

    if(0 < (HbBits & (TCPSEND_EVENT | TCPREV_EVENT)))
    {
        /*发生TCP数据接收事件*/
        lastRevOrSend = xTaskGetTickCount();
        trytimes = 0;
        dbg_printf(DEBUG_DEBUG,"Socket send or receive event.");
    }

    /* 判断是否需要发送心跳 */
    if(xTaskGetTickCount() - lastRevOrSend > HEARTBEAT_TIMEOUT)
    {

        lastRevOrSend = xTaskGetTickCount();
        trytimes++;

        /* 判断尝试次数是否超限 */
        if(trytimes > HEARTBEAT_TRYTIMES)
        {
            /* TCP连接已死，重启DTU连接 */
            dbg_printf(DEBUG_WARNING,"TCP连接失效...");
            trytimes = 0;
            op_res = setServerIP(SysPara.IP1,SysPara.IP2,SysPara.IP3,SysPara.IP4,SysPara.PortNum);
            if(0 != op_res)
            {
                dbg_printf(DEBUG_WARNING,"DTU重启失败...");
            }
            else
            {
                dbg_printf(DEBUG_INFO,"DTU重启成功...");
            }
        }
        else
        {
            /* 发送心跳 */
            UART_TO_FY1000_QueueSend_Stru SendBuffer;
            FY_1000Send_Code_QInput(&SendBuffer,0X11);
        }
    }

#endif	

}



