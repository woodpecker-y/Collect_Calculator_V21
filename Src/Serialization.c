#include "serialization.h"


extern char SD_Path[4];					// SD卡逻辑设备路径
volatile uint32_t SD_Live = 0;
extern HAL_SD_CardInfoTypeDef SDCardInfo;

/* 内部函数定义 */


/* 根据设备类型生成不同的文件名 */
RTC_EXT RealClock_Str RTC_Time;//实时时钟
void CreateFileName(char *buf, SysDEV_Type type)
{
    /* 生成文件名 */
    uint32_t tick = HAL_GetTick();
    char typeName[8];
    switch(type)
    {
        case Meter_B:
        sprintf(typeName,"MB");
        break;
        case Meter_U:
        sprintf(typeName,"MU");
        break;
        case Valve_U:
        sprintf(typeName,"VU");
        break;
        case Valve_UH:
        sprintf(typeName,"VUH");
        break;
#ifdef Meter_H_ENABLE
        case Meter_H:
        sprintf(typeName,"MH");

        break;
#endif
        default:
        break;
    }

    sprintf(buf,"%04d%02d%02d%02d%02d%02d-%s-%d.csv",RTC_Time.Year,RTC_Time.Month,RTC_Time.Day,RTC_Time.Hour,RTC_Time.Minute,RTC_Time.Second,typeName,tick);
    dbg_printf(DEBUG_INFO,"Create CSV fileName:%s",buf);
}


/* 读取SDCard信息，用于判断SD卡是否存在 */
static int checkCard(void)
{
    HAL_StatusTypeDef res;
    res = SD_GetCardInfo(&SDCardInfo);
    if(HAL_OK == res)
    {
        LEDSD_ON;
        dbg_printf(DEBUG_INFO,"Get SDCard Info Success...");
        dbg_printf(DEBUG_INFO,"CardType:     %d",SDCardInfo.CardType);
        dbg_printf(DEBUG_INFO,"CardVersion:  %d",SDCardInfo.CardVersion);
        dbg_printf(DEBUG_INFO,"Class:        %d",SDCardInfo.Class);
        dbg_printf(DEBUG_INFO,"RelCardAdd:   %d",SDCardInfo.RelCardAdd);
        dbg_printf(DEBUG_INFO,"BlockNbr:     %d",SDCardInfo.BlockNbr);
        dbg_printf(DEBUG_INFO,"BlockSize:    %d",SDCardInfo.BlockSize);
        dbg_printf(DEBUG_INFO,"LogBlockNbr:  %d",SDCardInfo.LogBlockNbr);
        dbg_printf(DEBUG_INFO,"LogBlockSize: %d",SDCardInfo.LogBlockSize);
        return 0;
    }
    else
    {
        LEDSD_OFF;
        dbg_printf(DEBUG_WARNING,"Get SDCard Info Fail...");
        return -1;
    }
}

/* 挂载文件系统 */
static FRESULT MountFS(void)
{
    static FATFS fs;							// FatFs文件系统对象
    FRESULT f_res;						//文件操作结果 

    f_res = f_mount(&fs,(TCHAR const*)SD_Path,1);		//在SD卡挂载文件系统，文件系统挂载时会对SD卡初始化
    
    if(f_res == FR_NO_FILESYSTEM)					//如果没有文件系统就格式化创建创建文件系统
    {
        dbg_printf(DEBUG_WARNING,"该SD卡还没有文件系统，即将进行格式化...");
        f_res = f_mkfs((TCHAR const*)SD_Path,0,0);			//格式化 			
      
        if(f_res == FR_OK)
        {
            dbg_printf(DEBUG_INFO,"SD卡已成功格式化文件系统...");
            f_res = f_mount(NULL,(TCHAR const*)SD_Path,1);			// 格式化后，先取消挂载SD卡
            f_res = f_mount(&fs,(TCHAR const*)SD_Path,1);			// 重新挂载SD卡
            return f_res;
        }
        else
        {
            dbg_printf(DEBUG_ERR,"格式化失败...");
            return f_res;
        }
    }
    else if(f_res != FR_OK)
    {
        dbg_printf(DEBUG_WARNING,"SD卡挂载文件系统失败。(%d)...",f_res);
        return f_res;
    }
    else
    {
        dbg_printf(DEBUG_INFO,"文件系统挂载成功，请放心使用...");
        return f_res;
    }
}

/* 系统上电初始化SD卡 */
static int InitSDCard(void)
{
    /* 检测SD卡是否存在 */
    int op_res;
    FRESULT mount_res;
    int try = FS_TRY_TIMES;

    while(try--)
    {
        op_res = checkCard();
        if(0 == op_res)
        {
            break;
        }
    }

    if(try <= 0)
    {
        return -1;//获取SD卡失败
    }

    /* 检测到SD卡，挂载文件系统 */
    try = FS_TRY_TIMES;
    while(try--)
    {
        mount_res = MountFS();
        if(FR_OK == mount_res)
        {
            break;
        }
    }
    
    if(try <= 0)
    {
        return -1;//挂载文件系统失败
    }

    return 0;
}

/* 卸载SD卡 */
static int DisSDCard(void)
{
    /* 卸载文件系统 */
    FRESULT res;
    res = f_mount(NULL,(TCHAR const*)SD_Path,1);// 不再使用，取消挂载
    if(FR_OK != res)
    {
        dbg_printf(DEBUG_WARNING,"Unmount FATFS fail...");
        return -1;
    }
    return 0;
}

/* 根据设备类型保存实时数据 */
const char *MeterB_Title = "设备ID,进水温度,回水温度,瞬时流量（流速）,单位,瞬时热量（功率）,单位,累计流量,单位,累计冷量,单位,累计热量,单位,周期表底,周期内分摊热量,工作时间,热表故障状态1,热表故障状态2\n";
const char *MeterU_Title = "设备ID,进水温度,回水温度,瞬时流量（流速）,单位,瞬时热量（功率）,单位,累计流量,单位,累计冷量,单位,累计热量,单位,工作时间,热表故障状态1,热表故障状态2\n";
const char *ValveU_Title = "设备ID,系统设定温度强制标志,设定温度,系统极限温度强制标志,极限设定温度,控制类型,强制控制标志,当前温度,平均温度,进水温度,回水温度,阀门位置,周期开阀时间,周期开阀比例,分摊热量,面板状态,阀门状态\n";
const char *ValveUH_Title = "设备ID,控制类型,强制控制标志,阀门位置,周期开阀时间,周期开阀比例,分摊热量,阀门状态\n";
const char *MeterH_Title = "设备ID,进水温度,回水温度,瞬时流量（流速）,单位,瞬时热量（功率）,单位,累计流量,单位,累计冷量,单位,累计热量,单位,周期表底,周期内分摊热量,工作时间,热表故障状态1,热表故障状态2\n";
DEVPARA_EXT SysDevData_Stru SysDevData[MAXDevice_Num];
DEVPARA_EXT SysDeviceList_Stru SysDeviceList;
#define WRITEBUFSIZE 2048
int SaveDeviceInfo(SysDEV_Type type)
{
    int sd_res;
    FRESULT f_res;
    FIL file;
    uint32_t writed;
    uint32_t key;
    char *writeBuf = NULL;

    /* 分配写入缓存区 */
    writeBuf = pvPortMalloc(WRITEBUFSIZE);
    if(NULL == writeBuf)
    {
        dbg_printf(DEBUG_ERR,"内存不足，SD卡数据保存失败");
        return -1;
    }
    memset(writeBuf,0x00,WRITEBUFSIZE);
    
    /*创建文件*/
    CreateFileName(writeBuf,type);//生成文件名
    /* 检测SD卡 */
    sd_res = InitSDCard();
    if(0 != sd_res)
    {
        dbg_printf(DEBUG_WARNING,"SD卡错误...");
        vPortFree(writeBuf);
        return -1;
    }
    /* 创建文件 */
    f_res = f_open(&file, writeBuf, FA_CREATE_ALWAYS | FA_WRITE );
    if(FR_OK != f_res)
    {
        vPortFree(writeBuf);
        return f_res;
    }

    /* 创建文件成功，开始写入数据 */
    /*写入标题*/
    switch(type)
    {
        case Meter_B:
        f_res = f_write(&file, MeterB_Title, strlen(MeterB_Title), &writed);
        break;
        case Meter_U:
        f_res = f_write(&file, MeterU_Title, strlen(MeterU_Title), &writed);
        break;
        case Valve_U:
        f_res = f_write(&file, ValveU_Title, strlen(ValveU_Title), &writed);
        break;
        case Valve_UH:
        f_res = f_write(&file, ValveUH_Title, strlen(ValveUH_Title), &writed);
        break;
#ifdef Meter_H_ENABLE
        case Meter_H:
        f_res = f_write(&file, MeterH_Title, strlen(MeterH_Title), &writed);
        break;
#endif
        default:
        break;
    }

    /* 循环遍历设备列表并保存到Excel */
    for(int i=0;i<MAXDevice_Num;i++)
    {
        /* 过滤设备ID为零的设备，不需要保存 */
        if(0 == SysDeviceList.Device[i].ID)
        {
            continue;
        }

        /* 非选中设备不序列化 */
        if(type != SysDeviceList.Device[i].Type)
        {
            continue;
        }

        /* 设备ID不为零且类型匹配的进行序列化 */
        memset(writeBuf,0x00,WRITEBUFSIZE);
        key = BcdToHex4(&SysDeviceList.Device[i].ID);
        switch(type)
        {
            case Meter_B:
            sprintf(writeBuf,"%u,%u,%u,%lu,%u,%lu,%u,%lu,%u,%lu,%u,%lu,%u,%lu,%lu,%lu,%u,%u\n",key,SysDevData[i].Device1.Input_Temp,SysDevData[i].Device1.Output_Temp,\
            SysDevData[i].Device1.Instant_Current,SysDevData[i].Device1.Instant_Current_Unit,SysDevData[i].Device1.Instant_Energy,\
            SysDevData[i].Device1.Instant_Energy_Unit,SysDevData[i].Device1.Total_Current,SysDevData[i].Device1.Total_Current_Unit,\
            SysDevData[i].Device1.Total_Code,SysDevData[i].Device1.Total_Code_Unit,SysDevData[i].Device1.Total_Energy,SysDevData[i].Device1.Total_Energy_Unit,\
            SysDevData[i].Device1.CycBot_Energy,SysDevData[i].Device1.Apportion_Energy,SysDevData[i].Device1.Work_Time,
            SysDevData[i].Device1.STATE1,SysDevData[i].Device1.STATE2);
            f_res = f_write(&file, writeBuf, strlen(writeBuf), &writed);
            break;
            case Meter_U:
            sprintf(writeBuf,"%u,%u,%u,%lu,%u,%lu,%u,%lu,%u,%lu,%u,%lu,%u,%lu,%u,%u\n",key,SysDevData[i].Device2.Input_Temp,SysDevData[i].Device2.Output_Temp,\
            SysDevData[i].Device2.Instant_Current,SysDevData[i].Device2.Instant_Current_Unit,SysDevData[i].Device2.Instant_Energy,\
            SysDevData[i].Device2.Instant_Energy_Unit,SysDevData[i].Device2.Total_Current,SysDevData[i].Device2.Total_Current_Unit,\
            SysDevData[i].Device2.Total_Code,SysDevData[i].Device2.Total_Code_Unit,SysDevData[i].Device2.Total_Energy,SysDevData[i].Device2.Total_Energy_Unit,\
            SysDevData[i].Device2.Work_Time,SysDevData[i].Device2.STATE1,SysDevData[i].Device2.STATE2);
            f_res = f_write(&file, writeBuf, strlen(writeBuf), &writed);
            break;
            case Valve_U:
            sprintf(writeBuf,"%u,%u,%u,%u,%u,%u,%u,%u,%u,%u,%u,%u,%lu,%u,%lu,%u,%u,\n",key,SysDevData[i].Device3.Set_TCtrlFg,SysDevData[i].Device3.Set_Temp,\
            SysDevData[i].Device3.LimtTE_Flag,SysDevData[i].Device3.LimtTE_Value,SysDevData[i].Device3.ControlType,SysDevData[i].Device3.ForceCtrlFlg,
            SysDevData[i].Device3.Cur_Temp,SysDevData[i].Device3.Ave_Temp,SysDevData[i].Device3.Input_Temp,SysDevData[i].Device3.Output_Temp,\
            SysDevData[i].Device3.ValvePosition,SysDevData[i].Device3.Cycle_OpTim,SysDevData[i].Device3.Cycle_OpRat,SysDevData[i].Device3.Apportion_Energy,
            SysDevData[i].Device3.Face_State,SysDevData[i].Device3.Valve_State);
            f_res = f_write(&file, writeBuf, strlen(writeBuf), &writed);
            break;
            case Valve_UH:
            sprintf(writeBuf,"%u,%u,%u,%u,%lu,%u,%lu,%u\n",key,SysDevData[i].Device4.ControlType,SysDevData[i].Device4.ForceCtrlFlg,SysDevData[i].Device4.ValvePosition,\
            SysDevData[i].Device4.Cycle_OpTim,SysDevData[i].Device4.Cycle_OpRat,SysDevData[i].Device4.Apportion_Energy,SysDevData[i].Device4.Valve_State);
            f_res = f_write(&file, writeBuf, strlen(writeBuf), &writed);
            break;
#ifdef Meter_H_ENABLE
            case Meter_H:
            sprintf(writeBuf,"%u,%u,%u,%lu,%u,%lu,%u,%lu,%u,%lu,%u,%lu,%u,%lu,%lu,%lu,%u,%u\n",key,SysDevData[i].Device5.Input_Temp,SysDevData[i].Device5.Output_Temp,\
            SysDevData[i].Device5.Instant_Current,SysDevData[i].Device5.Instant_Current_Unit,SysDevData[i].Device5.Instant_Energy,\
            SysDevData[i].Device5.Instant_Energy_Unit,SysDevData[i].Device5.Total_Current,SysDevData[i].Device5.Total_Current_Unit,SysDevData[i].Device5.Total_Code,\
            SysDevData[i].Device5.Total_Code_Unit,SysDevData[i].Device5.Total_Energy,SysDevData[i].Device5.Total_Energy_Unit,\
            SysDevData[i].Device5.CycBot_Energy,SysDevData[i].Device5.Apportion_Energy,SysDevData[i].Device5.Work_Time,SysDevData[i].Device5.STATE1,SysDevData[i].Device5.STATE2);
            f_res = f_write(&file, writeBuf, strlen(writeBuf), &writed);
            break;
#endif
            default:
            break;
        }
        if(FR_OK != f_res)
        {
            dbg_printf(DEBUG_WARNING,"SD卡文件写入失败");
            break;
        }
    }
    /* 写入完成，关闭文件并返回结果 */
    f_close(&file);

    /* 日志文件写入完成，释放内存并卸载文件系统 */
    sd_res = DisSDCard();
    vPortFree(writeBuf);
    return sd_res;
}

/* 保存日志 */
int SaveLog(void)
{
    int res;

    SDIO_Cfg();//SDIO功能端口初始化

    res = SaveDeviceInfo(Meter_B);
    if(0 != res)
    {
        dbg_printf(DEBUG_WARNING,"Save device:%d data fail...",Meter_B);
        return -1;
    }
    else
    {
        dbg_printf(DEBUG_NOTICE,"Save device:%d data success...",Meter_B);
    }

    res = SaveDeviceInfo(Meter_U);
    if(0 != res)
    {
        dbg_printf(DEBUG_WARNING,"Save device:%d data fail...",Meter_U);
        return -1;
    }
    else
    {
        dbg_printf(DEBUG_NOTICE,"Save device:%d data success...",Meter_U);
    }
    res = SaveDeviceInfo(Valve_U);
    if(0 != res)
    {
        dbg_printf(DEBUG_WARNING,"Save device:%d data fail...",Valve_U);
        return -1;
    }
    else
    {
        dbg_printf(DEBUG_NOTICE,"Save device:%d data success...",Valve_U);
    }
    res = SaveDeviceInfo(Valve_UH);
    if(0 != res)
    {
        dbg_printf(DEBUG_WARNING,"Save device:%d data fail...",Valve_UH);
        return -1;
    }
    else
    {
        dbg_printf(DEBUG_NOTICE,"Save device:%d data success...",Valve_UH);
    }
#ifdef Meter_H_ENABLE
    res = SaveDeviceInfo(Meter_H);
    if(0 != res)
    {
        dbg_printf(DEBUG_WARNING,"Save device:%d data fail...",Meter_H);
        return -1;
    }
    else
    {
        dbg_printf(DEBUG_NOTICE,"Save device:%d data success...",Meter_H);
    }
#endif
    return res;
}


