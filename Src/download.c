/**
  ******************************************************************************
  * @file    IAP/src/download.c 
  * @author  MCD Application Team
  * @version V3.2.0
  * @date    04/23/2010
  * @brief   This file provides the software which allows to download an image 
  *          to internal Flash.
  ******************************************************************************
  * @copy
  *
  * THE PRESENT FIRMWARE WHICH IS FOR GUIDANCE ONLY AIMS AT PROVIDING CUSTOMERS
  * WITH CODING INFORMATION REGARDING THEIR PRODUCTS IN ORDER FOR THEM TO SAVE
  * TIME. AS A RESULT, STMICROELECTRONICS SHALL NOT BE HELD LIABLE FOR ANY
  * DIRECT, INDIRECT OR CONSEQUENTIAL DAMAGES WITH RESPECT TO ANY CLAIMS ARISING
  * FROM THE CONTENT OF SUCH FIRMWARE AND/OR THE USE MADE BY CUSTOMERS OF THE
  * CODING INFORMATION CONTAINED HEREIN IN CONNECTION WITH THEIR PRODUCTS.
  *
  * <h2><center>&copy; COPYRIGHT 2010 STMicroelectronics</center></h2>
  */ 

/** @addtogroup IAP
  * @{
  */
/* Includes ------------------------------------------------------------------*/
#include "common.h"
#include "stdio.h"
#include "debug.h"
#include "watchdog.h"

/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
extern uint8_t file_name[FILE_NAME_LENGTH];
uint8_t tab_1024[1024] =
  {
    0
  };

	
extern EventBits_t cli_dog;//Èí¼þ¿´ÃÅ¹·
/* Private function prototypes -----------------------------------------------*/
/* Private functions ---------------------------------------------------------*/

/**
  * @brief  Download a file via serial port
  * @param  None
  * @retval None
  */
uint8_t SerialDownload(void)
{
  uint8_t Number[10] = "          ";
  int32_t Size = 0;

	os_printf("Erase the download cache area...\r\n");
	feedIWDG(cli_dog);
	spiFlashErase(SysDownload_Temp_Addr,SysDownload_Temp_Size);
	feedIWDG(cli_dog);
  os_printf("Waiting for the file to be sent ... (press 'a' to abort)\n\r");
  Size = Ymodem_Receive(&tab_1024[0]);
  if (Size > 0)
  {
    os_printf("\n\n\r Download Completed Successfully!\n\r---------------------------------\r\n Name: ");
    os_printf("%s",file_name);
    Int2Str(Number, Size);
    os_printf("\n\r Size: ");
    os_printf("%s",Number);
    os_printf(" Bytes\r\n");
    os_printf("---------------------------------\r\n");
		return 0;
  }
  else if (Size == -1)
  {
    os_printf("\n\n\rThe image size is higher than the allowed space memory!\n\r");
  }
  else if (Size == -2)
  {
    os_printf("\n\n\rVerification failed!\n\r");
  }
  else if (Size == -3)
  {
    os_printf("\r\n\nAborted by user.\n\r");
  }
	else if(Size == -4)
	{
		os_printf("\r\n\nWait download timeout.\n\r");
	}
  else
  {
    os_printf("\n\rFailed to receive the file!\n\r");
  }
	return 1;
}

/**
  * @}
  */

/*******************(C)COPYRIGHT 2010 STMicroelectronics *****END OF FILE******/
