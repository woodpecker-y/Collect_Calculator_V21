
2020.05.01 添加耐威科楼栋单元调节阀

屏幕显示版本号是：
char Hardware[]="1.硬件: FY-1100M-V22";
char Software[]="2.软件: FY-1102_V22A";



调试日志显示版本号是  20200501






	
代码大小计算：
keil编译后code，RO-data,RW-data,ZI-data含义及mcu的flash实际存储数据 这些参数的单位是Byte，几个参数分别代表含义如下： 
	Code：代码的大小 
	RO：常量所占空间 
	RW：程序中已经初始化的变量所占空间 
	ZI：未初始化的static变量和全局变量以及堆栈所占的空间 
    
上述参数和芯片Flash以及SRAM的对应关系是 
	Flash=Code+RO+RW 
	SRAM=RW+ZI



【1】芯片外设情况 CPU内部资源

    工作电源电压    : 1.8V to 3.6V    
	CPU型号        	: STM32F407VGTx / LQFP100  ARM 32-bit Cortex-M4   5.623$
	主频           	: 168MHz
	内部Flash容量	: 1024KB
	内部SRAM容量	: 192+4KB
	IO				：82
	定时器			: 最多17个定时器:最多12个16位，两个32位定时器，最多168mhz，每个定时器最多4个IC/OC/PWM或脉冲计数器和正交(增量)编码器的输入
	UART			: 3个
	SPI				: 3个
	I2C				: 3个
	ADC				: 3个独立的12位ADC 通道数量 16
	DAC				: 2×12位D / A转换器
	CAN				: 2个 CAN 2.0B
	SDIO			: 1个
	USB				: USB 2.0全速设备/主机/OTG控制器与芯片上的PHY------USB 2.0高速/全速设备/主机/OTG控制器专用DMA，片上全速PHY和ULPI


  
	

STM32F407ZGT6 ：ARM Cortex-M4 32位 MCU+FPU，210DMIPS，高达1 MB Flash/192 + 4KB RAM，USB OTG HS/FS，以太网，17 个TIM，3个ADC，15 个通信接口、摄像头。



特性：

1、内核：带有 FPU 的 ARM? 32 位 Cortex?-M4CPU、在 Flash 存储器中实现零等待状态运行性能的自适应实时加速器 (ART 加速器 ?)、主频高达 168MHz， MPU，能够实现高达210 DMIPS/1.25DMIPS/MHz (Dhrystone 2.1)的性能，具有 DSP 指令集。

2、存储器

①高达1 MB Flash：地址从0x8000000开始，大小为：0x100000即1M

②高达 192+4 KB的SRAM， 包括64-KB的CCM（内核耦合存储器）数据 RAM

    I、普通内存：地址从0x20000000开始，大小为：0x20000即128k

       这部分内存任何外设都可以访问

    II、CCM内存：地址从0x10000000开始，大小为：0x10000即64k

         这部分内存仅 CPU 可以访问，DMA 之类的不可以直接访问

   III、备份 SRAM：大小为：4 K

③具有高达 32 位数据总线的灵活外部存储控制器： SRAM、 PSRAM、 NOR/NAND存储器

3、 LCD 并行接口，兼容 8080/6800 模式
4、 时钟、复位和电源管理
– 1.8 V 到 3.6 V 供电和 I/O

– POR、 PDR、 PVD 和 BOR

– 4 至 26 MHz 晶振

– 内置经工厂调校的 16 MHz RC 振荡器（ 1% 精度）

– 带校准功能的 32 kHz RTC 振荡器

– 内置带校准功能的 32 kHz RC 振荡器

5、低功耗
– 睡眠、停机和待机模式

– VBAT 可为 RTC、 20×32 位备份寄存器 + 可选的 4 KB 备份 SRAM 供电

6、3 个 12 位、 2.4 MSPS ADC：多达 24 通道，三重交叉模式下的性能高达 7.2 MSPS
7、2 个 12 位 D/A 转换器
8、通用DMA：具有FIFO和突发支持的16路DMA控制器
9、多达17个定时器： 12个16位定时器，和2个频率高达 168 MHz 的 32 位定时器，每个定时器都带有 4 个输入捕获 / 输出比较 /PWM，或脉冲计数器与正交 ( 增量 ) 编码器输入
10、调试模式
– SWD & JTAG 接口

– Cortex-M4 跟踪宏单元 ?

11、多达 140 个具有中断功能的 I/O 端口
– 高达 136 个快速 I/O，最高 84 MHz

– 高达 138 个可耐 5 V 的 I/O

12、多达 15 个通信接口
– 多达 3 个 I2C 接口 (SMBus/PMBus)

– 高达 4 个 USART/4 个 UART（ 10.5 Mbit/s、ISO7816接口、 LIN、 IrDA、 调制解调器控制）

– 高达 3 个 SPI （ 42 Mbits/s）， 2 个具有复用的全双工 I2S， 通过内部音频 PLL 或外部时钟达到 音频级精度

– 2 个 CAN （ 2.0B 主动）以及 SDIO 接口

13、高级连接功能
– 具有片上PHY的USB 2.0全速器件/主机/OTG控制器

– 具有专用 DMA、片上全速 PHY 和 ULPI 的USB 2.0 高速 / 全速器件 / 主机 /OTG 控制器

– 具有专用 DMA 的 10/100 以太网 MAC：支持IEEE 1588v2 硬件， MII/RMII

14、8~14 位并行照相机接口：速度高达 54MB/s
15、真随机数发生器
16、 CRC 计算单元
17、RTC：亚秒级精度、硬件日历
18、 96 位唯一 ID



较之STM32F1/F2 等Cortex-M3产品，STM32F4 最大的优势，就是新增了硬件 FPU 单元以及 DSP 指令，同时， STM32F4 的主频也提高了很多，达到 168Mhz（可获得 210DMIPS 的处理能力），这使得 STM32F4 尤其适用于需要浮点运算或 DSP 处理的应用，也被称之为： DSC， 具有非常广泛的应用前景。














