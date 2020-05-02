#include "rtx_cli.h"
#include "string.h"
#include <stdarg.h>
#include <ctype.h>
#include <stdlib.h>
#include "FreeRTOS.h"
#include "kfifo.h"

#include "debug.h"
#include "Sys_State.h"

#include "watchdog.h"

#define MICO_CLI_ENABLE


#ifdef DEBUG    
int os_debug_enabled = 1;
int os_debug_level = DEFAULT_DEBUG_LEVEL;
#else 
int os_debug_enabled = 0;
#endif

EventBits_t cli_dog;									//软件看门狗
#define CLIFEEDDOGINTERVAL			5000				//喂狗间隔（单位毫秒）
#define CLIDOGTIMEOUT				60 				    //看门狗超时时间（单位秒）


#ifdef MICO_CLI_ENABLE
int cli_getchar(char *inbuf);

/// CLI ///
#define RX_WAIT   MICO_WAIT_FOREVER
#define SEND_WAIT MICO_WAIT_FOREVER

#define RET_CHAR				'\n'
#define END_CHAR				'\r'
#define BACKSPACE				0x08
#define DEL                     0x7f
#define PROMPT                  "\r\n[foryon@app]# "
#define EXIT_MSG				"exit"
#define NUM_BUFFERS             1
#define MAX_COMMANDS			50
#define INBUF_SIZE				512
#define OUTBUF_SIZE             (2048)

//#define SYSTEM_VERSION              20191020            //采集器软件版本号（32位无符号整数）

struct cli_st 
{
    int initialized;
    unsigned int bp;	           /* buffer pointer */
    char inbuf[INBUF_SIZE];
    char outbuf[OUTBUF_SIZE];
    const struct cli_command *commands[MAX_COMMANDS];
    unsigned int num_commands;
    int echo_disabled;
  
};



static struct cli_st *pCli = NULL;

/* Find the command 'name' in the cli commands table.
* If len is 0 then full match will be performed else upto len bytes.
* Returns: a pointer to the corresponding cli_command struct or NULL.
*/
static const struct cli_command *lookup_command(char *name, int len)
{
	int i = 0;
	int n = 0;

    while (i < MAX_COMMANDS && n < pCli->num_commands) 
    {
        if (pCli->commands[i]->name == NULL) 
        {
            i++;
            continue;
        }
        /* See if partial or full match is expected */
        if (len != 0) 
        {
            if (!strncmp(pCli->commands[i]->name, name, len))
            {
                return pCli->commands[i];        
            }

        } 
        else 
        {
            if (!strcmp(pCli->commands[i]->name, name))
            {
                return pCli->commands[i];        
            }

        }
        i++;
        n++;
    }
    return NULL;
}


/* Parse input line and locate arguments (if any), keeping count of the number
* of arguments and their locations.  Look up and call the corresponding cli
* function if one is found and pass it the argv array.
*
* Returns: 0 on success: the input line contained at least a function name and
*          that function exists and was called.
*          1 on lookup failure: there is no corresponding function for the
*          input line.
*          2 on invalid syntax: the arguments list couldn't be parsed
*/
static int handle_input(char *inbuf)
{
    struct 
    {
        unsigned inArg:1;
        unsigned inQuote:1;
        unsigned done:1;
    } stat;

    static char *argv[16];
    int argc = 0;
    int i = 0;

    const struct cli_command *command = NULL;
    const char *p;
    memset((void *)&argv, 0, sizeof(argv));
    memset(&stat, 0, sizeof(stat));
    do 
    {
        switch (inbuf[i]) 
        {

            case '\0':
            {
                if (stat.inQuote)
                {
                    return 2;
                }                
                stat.done = 1;                       
            }break; 

            case '"':
            {
                if (i > 0 && inbuf[i - 1] == '\\' && stat.inArg) 
                {
                    memcpy(&inbuf[i - 1], &inbuf[i],strlen(&inbuf[i]) + 1);
                    --i;
                    break;
                }

                if (!stat.inQuote && stat.inArg)
                {
                    break;            
                }

                if (stat.inQuote && !stat.inArg)
                {
                    return 2;
                }

                if (!stat.inQuote && !stat.inArg) 
                {
                    stat.inArg = 1;
                    stat.inQuote = 1;
                    argc++;
                    argv[argc - 1] = &inbuf[i + 1];
                } 
                else if (stat.inQuote && stat.inArg) 
                {
                    stat.inArg = 0;
                    stat.inQuote = 0;
                    inbuf[i] = '\0';
                }
                                
            }break;

            case ' ':
            {
                if (i > 0 && inbuf[i - 1] == '\\' && stat.inArg) 
                {
                    memcpy(&inbuf[i - 1], &inbuf[i],strlen(&inbuf[i]) + 1);
                    --i;
                    break;
                }
                if (!stat.inQuote && stat.inArg) 
                {
                    stat.inArg = 0;
                    inbuf[i] = '\0';
                }
            }break; 

        
            default:
            {
                if (!stat.inArg) 
                {
                    stat.inArg = 1;
                    argc++;
                    argv[argc - 1] = &inbuf[i];
                }      
            }break;  
        }
    } 

    while (!stat.done && ++i < INBUF_SIZE);
    
    if (stat.inQuote)
    {
        return 2;
    }
    if (argc < 1)
    {
        return 0;
    }

    if (!pCli->echo_disabled)
    {
        cli_printf("\r\n");
    }
    
  
    /*
    * Some comamands can allow extensions like foo.a, foo.b and hence
    * compare commands before first dot.
    */
    i = ((p = strchr(argv[0], '.')) == NULL) ? 0 :(p - argv[0]);
    command = lookup_command(argv[0], i);

    if (command == NULL)
    {
        return 1;
    }
    memset(pCli->outbuf, 0, OUTBUF_SIZE);
    cli_printf("\r\n");
    command->function(pCli->outbuf, OUTBUF_SIZE, argc, argv);
    cli_printf("%s",pCli->outbuf);
    return 0;
}

/* Perform basic tab-completion on the input buffer by string-matching the
* current input line against the cli functions table.  The current input line
* is assumed to be NULL-terminated. */
static void tab_complete(char *inbuf, unsigned int *bp)
{

    int i, n, m;
    const char *fm = NULL;
    cli_printf("\r\n");
  
    /* show matching commands */
    for (i = 0, n = 0, m = 0; i < MAX_COMMANDS && n < pCli->num_commands;i++) 
    {
        if (pCli->commands[i]->name != NULL) 
        {
            if (!strncmp(inbuf, pCli->commands[i]->name, *bp)) 
            {
                m++;
                if (m == 1)
                {
                    fm = pCli->commands[i]->name;
                }
                else if (m == 2)
                {
                    cli_printf("%s %s ", fm,
                    pCli->commands[i]->name);                    
                }
                else
                {
                    cli_printf("%s ",
                    pCli->commands[i]->name);                    
                }
            }
            n++;
        }
    }
  
    /* there's only one match, so complete the line */
    if (m == 1 && fm) 
    {
        n = strlen(fm) - *bp;
        if (*bp + n < INBUF_SIZE) 
        {
            memcpy(inbuf + *bp, fm + *bp, n);
            *bp += n;
            inbuf[(*bp)++] = ' ';
            inbuf[*bp] = '\0';
        }
    }
  
    /* just redraw input line */
    cli_printf("%s%s", PROMPT, inbuf);
}

/* Get an input line.
*
* Returns: 1 if there is input, 0 if the line should be ignored. */
static int get_input(char *inbuf, unsigned int *bp)
{
  
    if (inbuf == NULL) 
    {
        return 0;
    }
    while (cli_getchar(&inbuf[*bp]) == 1) 
    {
        if (inbuf[*bp] == RET_CHAR)
        {
            continue;
        }
        if (inbuf[*bp] == END_CHAR) 
        {	/* end of input line */
            inbuf[*bp] = '\0';
            *bp = 0;
            return 1;
        }
    
        if ((inbuf[*bp] == BACKSPACE)||(inbuf[*bp] == DEL)) /* backspace */
        {	
            /* DEL */
            if (*bp > 0) 
            {
                (*bp)--;
                if (!pCli->echo_disabled)
                {
                    cli_printf("%c %c", 0x08, 0x08);
                } 
            }
            continue;
        }
    
        if (inbuf[*bp] == '\t') 
        {
            inbuf[*bp] = '\0';
            tab_complete(inbuf, bp);
            continue;
        }
    
        if (!pCli->echo_disabled)
        {
            cli_printf("%c", inbuf[*bp]);
        }

        (*bp)++;

        if (*bp >= INBUF_SIZE) 
        {
            cli_printf("Error: input buffer overflow\r\n");
            cli_printf(PROMPT);
            *bp = 0;
            return 0;
        }
    
    }
	osDelay(pdMS_TO_TICKS(10));
    
    return 0;
}

/* Print out a bad command string, including a hex
* representation of non-printable characters.
* Non-printable characters show as "\0xXX".
*/
static void print_bad_command(char *cmd_string)
{
    if (cmd_string != NULL) 
    {
        char *c = cmd_string;
        cli_printf("command '");
        while (*c != '\0') 
        {
            if (isprint(*c)) 
            {
                cli_printf("%c", *c);
            } 
            else 
            {
                cli_printf("\\0x%x", *c);
            }
            ++c;
        }
        cli_printf("' not found\r\n");
    }
}

/* Main CLI processing thread
*
* Waits to receive a command buffer pointer from an input collector, and
* then processes.  Note that it must cleanup the buffer when done with it.
*
* Input collectors handle their own lexical analysis and must pass complete
* command lines to CLI.
*/
void cli_main(void)
{
	static uint32_t ticks;
	ticks = xTaskGetTickCount();
    while (1) 
    {
        int ret;
        char *msg = NULL;
        
        /* 喂狗 */
        if(xTaskGetTickCount() - ticks > pdMS_TO_TICKS(CLIFEEDDOGINTERVAL))
        {
            ticks = xTaskGetTickCount();
            feedIWDG(cli_dog);
        }

        if (!get_input(pCli->inbuf, &pCli->bp))
        {
            continue;
        }

        msg = pCli->inbuf;

        if (msg != NULL) 
        {
            if (strcmp(msg, EXIT_MSG) == 0)
            {
                break;
            }
            ret = handle_input(msg);
            if (ret == 1)
            {
                print_bad_command(msg);
            }
            else if (ret == 2)
            {
                cli_printf("syntax error\r\n");
            }
            cli_printf(PROMPT);
        }
    }
    cli_printf("CLI exited\r\n");
    vPortFree(pCli);
    pCli = NULL;
}



static void help_command(char *pcWriteBuffer, int xWriteBufferLen,int argc, char **argv);

static void clear_screen(char *pcWriteBuffer, int xWriteBufferLen,int argc, char **argv)
{
	cmd_printf("\033[H\033[J");
}

static void cli_exit_handler(char *pcWriteBuffer, int xWriteBufferLen,int argc, char **argv)
{
  // exit command not excuted
}

//static const struct cli_command built_ins[] = 
//{
//	{"help","          Show all command-------------------------(帮助)",				    		                help_command},
//	{"version","       Show firmware version--------------------(软件版本号)",			    		                get_version},
//	{"exit","          Cli exit---------------------------------(关闭调试功能 谨慎操作，重启后恢复)",                 cli_exit_handler}, 
//	{"reboot","        Reboot system----------------------------(重启)",					    	                reboot},
//	{"time","          System tick time-------------------------(Systick)",				    		                uptime_Command},
//    
//	{"clear","         Clear screen-----------------------------(清除)",					    		            clear_screen},
//	{"printenv","      Print system env-------------------------(系统参数信息)",				    		            printenv},
//	{"setenv","        Set env parameter------------------------(导入bin文件)",				    	                setEnvParameter},
//	{"setip","         Set server ip and port-------------------(设置IP地址和端口号)",		    	    	        setServer},
//	{"printip","       Print server ip and port-----------------(IP地址和端口号)",		    	    	            printServer},
//	{"ps","            Show task status-------------------------(系统运行状态)",				    		            ps},
//	{"userpa","        Show user para---------------------------(用户参数)",				    	    	            userpara},
//	{"devpa","         Show device para-------------------------(设备参数)",				    		                devicepara},
//	{"userda","        Show user data---------------------------(用户数据)",				    	    	            userdata},
//	{"devda","         Show device data-------------------------(设备参数)",				    		                devicedata},
//	{"devcom","        Show device com status-------------------(从机通信状况)",    			    	                devicestatus},
//	{"sysparst","      System Para reset------------------------(重置系统参数配置)",			    		            systemparareset},
//	{"userparst","     User Para reset--------------------------(重置用户参数)", 				    		        userparareset},
//	{"devparst","      Device Para reset------------------------(重置设备参数)",					                    deviceparareset},  
//	{"userdarst","     User Dara Reset--------------------------(重置用户数据)", 		  				            userdatareset},
//	{"devdarst","      Device Dara reset------------------------(重置设备参数)",					                    devicedatareset},
//	{"sysdarst","      Reset All the system data----------------(重置系统数据配置)",		    		                sysdataresetall},
//	{"settime","       Set The Systemtime-----------------------(设置系统时间)", 		    			            settime},
//	{"setstime","      Set The Start time-----------------------(设置供暖期起始时间)", 		     			        settime_s},
//	{"setftime","      Set The Final time-----------------------(设置供暖期结束时间)", 		  	    		        settime_f},
//	{"mem","           Show system heap status------------------(内存状态)", 		    		                    mem},
//	{"systype","       Set The System Type----------------------(系统类型 1:热量表 2:温控计量 3:通断)",               setsystype},
//	{"savedata","      Save data to excel-----------------------(保存数据到SD卡)", 		  	    		            saveData},
//	{"devchange","     Change the deviceID----------------------(修改设备编号、类型)", 		  	    		        devchange},
//	{"alarm","         Show all alarm---------------------------(闹钟)", 		  			    	                alarm},
//	{"changeloop","    Change device loop num-------------------(改变抄收顺序)", 		    	                    changedevnum}, 
//	{"setsn","         Set the system SN------------------------(设置采集计算器编号)",					            setsn},
//	{"setread","       Set the Client device Read Space ms------(设置抄表时间间隔)", 	                            setread}, 
//	{"setsend","       Set the Client Report mode and Space ms--(设置上报模式及终端上报间隔)",                        setsend}, 
//	{"setshare","      Set the Share Space Minute---------------(设置分摊周期)", 			                        setshare},
//	{"relay","         Ctrl the power relay on/off--------------(远程断送电功能)", 			                        powrelayctrl},
//	{"ddf2ct","        Ctrl the DDF2 on/off---------------------(手动打开/关闭功能)", 			                    ddf2ctrl},
//	{"clirate","       Set the debug cli com rate---------------(设置调试串口波特率功能)", 			                ClirateSet},
//	
//	
//};

static const struct cli_command built_ins[] = 
{
	{"help","          (帮助)",				    		                    help_command},
	{"version","       (软件版本号)",			    		                get_version},
	{"exit","          (关闭调试功能 谨慎操作，重启后恢复)",                  cli_exit_handler}, 
	{"reboot","        (重启)",					    	                    reboot},
	{"time","          (Systick)",				    		                uptime_Command},
    
	{"clear","         (清除)",					    		                clear_screen},
	{"printenv","      (系统参数信息)",				    		            printenv},
	{"setenv","        (导入bin文件)",				    	                setEnvParameter},
	{"setip","         (设置IP地址和端口号)",		    	    	        setServer},
	{"printip","       (IP地址和端口号)",		    	    	            printServer},
	{"ps","            (系统运行状态)",				    		            ps},
	{"userpa","        (用户参数)",				    	    	            userpara},
	{"devpa","         (设备参数)",				    		                devicepara},
	{"userda","        (用户数据)",				    	    	            userdata},
	{"devda","         (设备参数)",				    		                devicedata},
	{"devcom","        (从机通信状况)",    			    	                devicestatus},
	{"sysparst","      (重置系统参数配置)",			    		            systemparareset},
	{"userparst","     (重置用户参数)", 				    		            userparareset},
	{"devparst","      (重置设备参数)",					                    deviceparareset},  
	{"userdarst","     (重置用户数据)", 		  				                userdatareset},
	{"devdarst","      (重置设备参数)",					                    devicedatareset},
	{"sysdarst","      (重置系统数据配置)",		    		                sysdataresetall},
	{"settime","       (设置系统时间)", 		    			                settime},
	{"setstime","      (设置供暖期起始时间)", 		     			        settime_s},
	{"setftime","      (设置供暖期结束时间)", 		  	    		        settime_f},
	{"mem","           (内存状态)", 		    		                        mem},
	{"systype","       (系统类型 1:热量表 2:温控计量 3:通断)",               setsystype},
	{"savedata","      (保存数据到SD卡)",                                   saveData},
	{"devchange","     (修改设备编号、类型)",                                devchange},
	{"alarm","         (闹钟)", 		  			    	                alarm},
	{"changeloop","    (改变抄收顺序)", 		    	                        changedevnum}, 
	{"setsn","         (设置采集计算器编号)",					            setsn},
	{"setread","       (设置抄表时间间隔)", 	                                setread}, 
	{"setsend","       (设置上报模式及终端上报间隔)",                        setsend}, 
	{"setshare","      (设置分摊周期)", 			                            setshare},
	{"relay","         (远程断送电功能)", 			                        powrelayctrl},
	{"ddf2ct","        (手动打开/关闭功能)", 			                    ddf2ctrl},
	{"clirate","       (设置调试串口波特率功能)", 			                ClirateSet},
    
};




/* Built-in "help" command: prints all registered commands and their help
* text string, if any. */
static void help_command(char *pcWriteBuffer, int xWriteBufferLen,int argc, char **argv)
{
    int i, n;
    uint32_t build_in_count = sizeof(built_ins)/sizeof(struct cli_command);
  
    #if (DEBUG)
    build_in_count++; //For command: rtxdebug
    #endif

    cmd_printf( "====Build-in Commands====\r\n" );
    for (i = 0, n = 0; i < MAX_COMMANDS && n < pCli->num_commands; i++) 
    {
        if (pCli->commands[i]->name) 
        {
            cmd_printf("%s: %s\r\n", pCli->commands[i]->name,pCli->commands[i]->help ?pCli->commands[i]->help : "");
            n++;
            if( n == build_in_count )
            {
                cmd_printf("\r\n====User Commands====\r\n");
            }
        }
    }
}

int cli_register_command(const struct cli_command *command)
{
    int i;
    if (!command->name || !command->function)
    {
        return 1;
    }
    
    if (pCli->num_commands < MAX_COMMANDS) 
    {
        /* Check if the command has already been registered.
        * Return 0, if it has been registered.
        */
        for (i = 0; i < pCli->num_commands; i++) 
        {
            if (pCli->commands[i] == command)
            return 0;
        }
        pCli->commands[pCli->num_commands++] = command;
        return 0;
    }
    return 1;
}

int cli_unregister_command(const struct cli_command *command)
{
	int i;
	if (!command->name || !command->function)
	{
		return 1;
	}
	for (i = 0; i < pCli->num_commands; i++) 
	{
		if (pCli->commands[i] == command) 
		{
		pCli->num_commands--;
		int remaining_cmds = pCli->num_commands - i;
		if (remaining_cmds > 0) 
		{
		memmove(&pCli->commands[i], &pCli->commands[i + 1],(remaining_cmds *sizeof(struct cli_command *)));
		}
		pCli->commands[pCli->num_commands] = NULL;
		return 0;
		}
	}
  
  return 1;
}

int cli_register_commands(const struct cli_command *commands, int num_commands)
{
    int i;
    for (i = 0; i < num_commands; i++)
    {
        if (cli_register_command(commands++))
        {
            return 1;
        }
    }

    return 0;
}

int cli_unregister_commands(const struct cli_command *commands,int num_commands)
{
    int i;
    for (i = 0; i < num_commands; i++)
    {
        if (cli_unregister_command(commands++))
        {
            return 1;
        }  
    }
    return 0;
}



#if (DEBUG)


extern int os_debug_enabled;

static void sysdebug_Command(char *pcWriteBuffer, int xWriteBufferLen,int argc, char **argv)
{
    if (argc != 3) 
    {
        cmd_printf("Usage: debug on/off level. System debug is currently %s level %d\r\n",os_debug_enabled ? "Enabled" : "Disabled", os_debug_level);
        return;
    }
  
    if (!strcasecmp(argv[1], "on")) 
    {
        cmd_printf("Enable System debug\r\n");
        os_debug_enabled = 1;
    } 
    else if (!strcasecmp(argv[1], "off")) 
    {
        cmd_printf("Disable System debug\r\n");
        os_debug_enabled = 0;
    }

    int level = atoi(argv[2]);
    if(0 <= level && level <= 7)
    {
        cmd_printf("Change Debug Level:%d\r\n", level);
        os_debug_level = level;
    }
	Updatedebug(os_debug_enabled, os_debug_level);
}

//static const struct cli_command user_clis[1] = 
//{
//	{"debug","         System debug on/off", 					sysdebug_Command},

//};

static const struct cli_command user_clis[1] = 
{
	{"debug","         (日志调试开关 on/off e.g.\"debug on 4\" / \"debug off 4\")",       sysdebug_Command},

};


#endif






struct kfifo *kfifo_usart1_rx = NULL;
osMutexId printMutexHandle;
int cli_sysinit(void)
{
	osMutexDef(printMutex);
  	printMutexHandle = osMutexCreate(osMutex(printMutex));
	kfifo_usart1_rx = kfifo_alloc(1024);
	if(kfifo_usart1_rx == NULL)
	{
		return -1;
	}
	return 0;
}


int cli_init(void)
{
	if(cli_sysinit() != 0)
	{
		return CLI_R_ERR;
	}
  	pCli = (struct cli_st*)pvPortMalloc(sizeof(struct cli_st));
  	if (pCli == NULL)
    return CLI_R_ERR;
  
  	memset((void *)pCli, 0, sizeof(struct cli_st));
  
	/* add our built-in commands */
	if (cli_register_commands(&built_ins[0],sizeof(built_ins) /sizeof(struct cli_command))) 
    {
        vPortFree(pCli);
        pCli = NULL;
        return CLI_R_ERR;
    }
  
#if (DEBUG)
	/* add our user  built-in commands */
	cli_register_commands(user_clis, 1);
#endif
  
    pCli->initialized = 1;
    cli_printf(PROMPT);
															
	/* 创建软件看门狗 */
	createIWDG(&cli_dog,CLIDOGTIMEOUT);//创建超时时间60秒的软件看门狗
	return CLI_R_OK;
}





/* ========= CLI input&output APIs ============ */

int cli_getchar(char *inbuf)
{
	int temp = getchar();
    if (temp != -1)
	{
		*inbuf = temp;
        return 1;
	}
    else
    {
        return 0;
    }
    
}


#endif

