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
* @date :2017/9/15 12:59
***************************************************************
*/ 
#define _FS_APP_C_
#include "FS_APP.h"
 



extern char SD_Path[4];					// SD卡逻辑设备路径

FATFS fs;							// FatFs文件系统对象
FIL file; 							// 文件对象
FRESULT f_res;						//文件操作结果 
UINT fnum;						//文件成功读写数量
BYTE ReadBuffer[4096]={0};        		//读缓冲区
BYTE WriteBuffer[4096]= "欢迎使用，该文件用于测试FATFS文件系统\r\n";//写缓冲区  





 



/*
函数名称:Get_SDCard_CAP
函数功能:获取SD卡的容量信息

@para *TotalSize 总容量
@para *FreeSize	剩余容量
@retval Norn
*/

void Get_SDCard_CAP(INT32U *TotalSize ,INT32U*FreeSize)
{
	FATFS fs;
	FATFS *pfs;
	INT32U fre_clust;
	INT32U Total;
	INT32U Free;
	INT32U res;
	pfs=&fs;
	f_mount(&fs,"", 1);  //挂载文件系统
	res = f_getfree("", &fre_clust, &pfs);
	if (res) 
	{	
		return; 		//如果函数运行不正确，返回错误值
	}
	else 				//如果接收正确
	{
		Total = (pfs->n_fatent - 2) * pfs->csize/2; // 单位Kbyte
		Total = Total/1024;	//单位 Mbyte
		
		Free = fre_clust * pfs->csize/2; // 单位kbyte
		Free = Free/1024;		//单位 Mbyte
	}
	*TotalSize =Total;
	*FreeSize =Free;
	f_mount(0, 0, 1);// 卸载文件系统
	
}


void Test(void)
{
	
		f_res = f_mount(&fs,(TCHAR const*)SD_Path,1);		//在SD卡挂载文件系统，文件系统挂载时会对SD卡初始化
		

		WriteBuffer[512] = 'f';
		WriteBuffer[1024] = 'u';
		WriteBuffer[512+1024] = 'c';
		WriteBuffer[2048] = 'k';


		if(f_res == FR_NO_FILESYSTEM)					//如果没有文件系统就格式化创建创建文件系统
		{
			printf(">>该SD卡还没有文件系统，即将进行格式化...\r\n");
			f_res=f_mkfs((TCHAR const*)SD_Path,0,0);			//格式化 			
		  
			if(f_res == FR_OK)
			{
				printf("》SD卡已成功格式化文件系统。\r\n");
				
				f_res = f_mount(NULL,(TCHAR const*)SD_Path,1);			// 格式化后，先取消挂载SD卡
				
				f_res = f_mount(&fs,(TCHAR const*)SD_Path,1);			// 重新挂载SD卡
			}
			else
			{
				printf(">>>>>格式化失败");
				while(1);
			}
		}
		else if(f_res!=FR_OK)
		{
			printf("！！SD卡挂载文件系统失败。(%d)\r\n",f_res);
			while(1)
			{
				
			}
		}
		else
		{
			printf(">>>>文件系统挂载成功，请放心使用....");
		}

		
		// ********************************文件写入测试******************************************
		printf("****** 即将进行文件写入测试... ******\r\n");		// 打开文件，如果文件不存在则创建它
		
		f_res = f_open(&file, "02345.txt",FA_CREATE_ALWAYS | FA_WRITE );
		if ( f_res == FR_OK )
		{
			printf("02345.txt文件打开成功，向文件写入数据...");

			f_res=f_write(&file,WriteBuffer,sizeof(WriteBuffer),&fnum); 		//将指定存储区内容写入到文件内
			if(f_res==FR_OK)
			{
				printf(">>>>>>文件写入成功，写入字节数据：%d\r\n",fnum);
				printf(">>>>>>向文件写入的数据为：\r\n%s\r\n",WriteBuffer);
			}
			else
			{
				printf("！！文件写入失败：(%d)\r\n",f_res);
			}    
		  
		  	f_close(&file);		//关闭文件
		}
		else
		{		 
			printf("！！打开/创建文件失败。\r\n");
			while(1);
		}
		
		//------------------- 文件读取测试 ------
		printf("****** 即将进行文件读取测试... ******\r\n");
		f_res = f_open(&file, "02345.txt", FA_OPEN_EXISTING | FA_READ); 		 
		if(f_res == FR_OK)
		{
			printf(">>>>文件打开成功....");
			memset(ReadBuffer,0x00,4096);
			f_res = f_read(&file, ReadBuffer, sizeof(ReadBuffer), &fnum); 
			if(f_res==FR_OK)
			{
				  printf(">>>>>>文件读取成功,读到字节数据：%d\r\n",fnum);
				  printf(">>>>>>读取得的文件数据为：\r\n%s \r\n", ReadBuffer);
					printf("%c",ReadBuffer[512]);	
					printf("%c",ReadBuffer[1024]);
					printf("%c",ReadBuffer[512+1024]);
					printf("%c",ReadBuffer[2048]);  
			}
			else
			{
				printf("！！文件读取失败：(%d)\r\n",f_res);
			} 			   
		}
		else
		{
	   		printf("！！打开文件失败...");
			while(1);
		}
		f_close(&file);							//不再读写，关闭文件 
		printf("文件关闭....");
		f_res = f_mount(NULL,(TCHAR const*)SD_Path,1);// 不再使用，取消挂载
		printf("文件系统卸载完成....");
		
	


}




 
/* END */
/*
 @copy COPYRIGHT 2016 Foryon     
*/
 




 
