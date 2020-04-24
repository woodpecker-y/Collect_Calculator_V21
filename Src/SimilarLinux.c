#include "rtx_cli.h"
#include "similarlinux.h"

extern EventBits_t cli_dog;//软件看门狗


/* 显示当前所有正在运行的任务 */
void ps_a(void)
{
    INT32U TotalRunTime;
    UBaseType_t ArraySize;
    TaskStatus_t *StatusArray;
    uint32_t buffsize;

    portENTER_CRITICAL();

    ArraySize=uxTaskGetNumberOfTasks();
    buffsize = ArraySize*sizeof(TaskStatus_t);
    StatusArray = pvPortMalloc(buffsize);
    if(StatusArray!=NULL)
    {
        memset(StatusArray, 0x00, buffsize);
        ArraySize=uxTaskGetSystemState((TaskStatus_t *)StatusArray, (UBaseType_t)ArraySize,(uint32_t *)&TotalRunTime);
        os_printf("%-20s%-20s%-20s%-20s\r\n\r\n", "PID", "Priority", "Times", "Name");
        for(int i=0;i<ArraySize;i++)
        {
            os_printf("%-20d%-20d%-20u%-20s\r\n", (int)StatusArray[i].xTaskNumber, (int)StatusArray[i].uxCurrentPriority, StatusArray[i].ulRunTimeCounter, StatusArray[i].pcTaskName);
        }
        vPortFree(StatusArray);
    }

    portEXIT_CRITICAL();
}

void ps_p(int PID)
{
    INT32U TotalRunTime;
    UBaseType_t ArraySize;
    TaskStatus_t *StatusArray;
    char TaskInfo[10];
    uint32_t buffsize;

    portENTER_CRITICAL();

    ArraySize = uxTaskGetNumberOfTasks();
    buffsize = ArraySize*sizeof(TaskStatus_t);
    StatusArray = pvPortMalloc(buffsize);
    if(StatusArray!=NULL)
    {
        memset(StatusArray, 0x00, buffsize);
        ArraySize=uxTaskGetSystemState((TaskStatus_t *)StatusArray, (UBaseType_t)ArraySize,(uint32_t *)&TotalRunTime);
        /* 根据taskNumber查询TaskHandle */
        for(int i=0;i<ArraySize;i++)
        {
            if(PID == (int)StatusArray[i].xTaskNumber)
            {

                TaskStatus_t TaskStatus;
                //获取的任务信息
                vTaskGetInfo((TaskHandle_t	)StatusArray[i].xHandle, 		//任务句柄
                                (TaskStatus_t*	)&TaskStatus, 		            //任务信息结构体
                                (BaseType_t	)pdTRUE,			            //允许统计任务堆栈历史最小剩余大小
                                (eTaskState	)eInvalid);			            //函数自己获取任务运行壮态
                memset(TaskInfo,0,10);						
                switch((int)TaskStatus.eCurrentState)
                {
                    case 0:
                        sprintf(TaskInfo,"Running");
                        break;
                    case 1:
                        sprintf(TaskInfo,"Ready");
                        break;
                    case 2:
                        sprintf(TaskInfo,"Suspend");
                        break;
                    case 3:
                        sprintf(TaskInfo,"Delete");
                        break;
                    case 4:
                        sprintf(TaskInfo,"Invalid");
                        break;
                }
                //通过串口打印出指定任务的有关信息
                os_printf("Name:                       %-s\r\n",TaskStatus.pcTaskName);
                os_printf("PID:                        %-d\r\n",(int)TaskStatus.xTaskNumber);
                os_printf("Status:                     %s\r\n",TaskInfo);
                os_printf("Current priority:           %d\r\n",(int)TaskStatus.uxCurrentPriority);
                os_printf("Base priority:              %d\r\n",(int)TaskStatus.uxBasePriority);
                os_printf("Stack base:                 %#x\r\n",(int)TaskStatus.pxStackBase);
                os_printf("Stack high water mark:      %d\r\n",TaskStatus.usStackHighWaterMark);
            }
        }
        vPortFree(StatusArray);
    }

    portEXIT_CRITICAL();
}


void ps_A(void)
{
    UBaseType_t ArraySize;
    int bufSize = 0;
    char *InfoBuffer;
    
    ArraySize = uxTaskGetNumberOfTasks();
    bufSize = ArraySize * 50;
    InfoBuffer = pvPortMalloc(bufSize);
    if(InfoBuffer!= NULL)
    {
        memset(InfoBuffer,0x00,bufSize);
        portENTER_CRITICAL();
        os_printf("%-31s%-8s%-8s%-7s%-7s\r\n\r\n", "Name", "STA", "PRIY", "  STK", "  PID");
        vTaskList(InfoBuffer);//获取所有任务的信息
        os_printf("%s\r\n",InfoBuffer);//通过串口打印所有任务的信息
        portEXIT_CRITICAL();
        vPortFree(InfoBuffer);
    }
}
void ps_none(void)
{
    UBaseType_t ArraySize;
    char c;
    char *InfoBuffer;
    int bufSize = 0;
    int taskCount = 0;

    ArraySize = uxTaskGetNumberOfTasks();
    bufSize = ArraySize * 50;
    InfoBuffer = pvPortMalloc(bufSize);
    if(InfoBuffer!= NULL)
    {
        for(;;)
        {
			feedIWDG(cli_dog);
            taskCount = uxTaskGetNumberOfTasks();
            portENTER_CRITICAL();
            memset(InfoBuffer,0,bufSize);			//信息缓冲区清零
            vTaskGetRunTimeStats(InfoBuffer);		//获取任务运行时间信息
            
            os_printf("Name\t\t\t\tTimes\t\tCPU\r\n\r\n");
            os_printf("%s",InfoBuffer);
            portEXIT_CRITICAL();

            /* 监测用户按下取消键 */
            int i;
            for(i=0;i<3;i++)
            {
                c = getchar();
                if(ETX == c)
                {
                    break;
                }
                osDelay(1000);
            }
            if(3 != i)
            {
                break;
            }

            /* 回退光标 */	
            for(int i=0;i<taskCount+2;i++)
            {
                os_printf("\033[1A");//光标上移一行
                os_printf("\33[K");//清除从光标到行尾的内容
            }

        }
        vPortFree(InfoBuffer);
    }
}

void freecmd(void)
{
    /* 查询当前内存状态 */
    size_t freeSize = xPortGetFreeHeapSize();
    os_printf("%-16s%-16s%-16s\r\n", "Total", "used", "free");
    os_printf("%-16d%-16d%-16d\r\n", configTOTAL_HEAP_SIZE, configTOTAL_HEAP_SIZE - freeSize, freeSize);
}





