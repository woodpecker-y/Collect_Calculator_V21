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
* @date :2016-11-24 18:15
***************************************************************
*/ 
#define _UC1698_C_
#include "UC1698.h"
#include "math.h"





const uint8_t BitTable[8]={0x01,0x02,0x04,0x08,0x10,0x20,0x40,0x80};

const uint8_t BitTab[8]={0x80,0x40,0x20,0x10,0x08,0x04,0x02,0x01};


/*有参数延时函数*/
void delay(__IO uint32_t nCount)
{
  for (; nCount != 0; nCount--);
}


/*
该函数移植雨标准库 用于读取 某个管脚寄存器组的数据

*/
INT16U GPIO_ReadOutputData(GPIO_TypeDef* GPIOx)
{
	/* Check the parameters */
	return ((INT16U)GPIOx->ODR);
}



/*
该函数移植雨标准库 用于设置 某个管脚寄存器组的数据

*/
void GPIO_Write(GPIO_TypeDef* GPIOx, INT16U PortVal)
{

	GPIOx->ODR = PortVal;
}







/*
函数名称:LCD_REST
函数功能:对液晶进行硬件复位 


*/
void LCD_REST(void)
{
	osDelay(50);
	LCD_RST_0;
	osDelay(5);
	LCD_RST_1;
	osDelay(5);
}


/*
函数名称:LCD_IOInit
函数功能:对LCD功能模块的管脚进行连接 模式初始化

*/
void LCD_IOInit(void)
{
	GPIO_InitTypeDef  LCD_IOInitStructure;

    /* 使能LCD对应GPIO的Clock时钟 */

   	__HAL_RCC_GPIOA_CLK_ENABLE();
   	__HAL_RCC_GPIOB_CLK_ENABLE();
	__HAL_RCC_GPIOC_CLK_ENABLE();
	__HAL_RCC_GPIOD_CLK_ENABLE();
	__HAL_RCC_GPIOE_CLK_ENABLE();



	/* 初始化LCD的A0管脚，配置为推挽输出 */
	LCD_IOInitStructure.Pin = LCD_A0_Bit;
	LCD_IOInitStructure.Mode = GPIO_MODE_OUTPUT_PP;
	LCD_IOInitStructure.Speed = GPIO_SPEED_FREQ_HIGH;
	HAL_GPIO_Init(LCD_A0_Group, &LCD_IOInitStructure);	


	/* 初始化LCD的WR管脚，配置为推挽输出 */
	LCD_IOInitStructure.Pin = LCD_WR_Bit;
	LCD_IOInitStructure.Mode = GPIO_MODE_OUTPUT_PP;
	LCD_IOInitStructure.Speed = GPIO_SPEED_FREQ_HIGH;
	HAL_GPIO_Init(LCD_WR_Group, &LCD_IOInitStructure);	



	/* 初始化LCD的RD管脚，配置为推挽输出 */
	LCD_IOInitStructure.Pin = LCD_RD_Bit;
	LCD_IOInitStructure.Mode = GPIO_MODE_OUTPUT_PP;
	LCD_IOInitStructure.Speed = GPIO_SPEED_FREQ_HIGH;
	HAL_GPIO_Init(LCD_RD_Group, &LCD_IOInitStructure);	


	/* 初始化LCD的CS管脚，配置为推挽输出 */
	LCD_IOInitStructure.Pin = LCD_CS_Bit;
	LCD_IOInitStructure.Mode = GPIO_MODE_OUTPUT_PP;
	LCD_IOInitStructure.Speed = GPIO_SPEED_FREQ_HIGH;
	HAL_GPIO_Init(LCD_CS_Group, &LCD_IOInitStructure);	



	
	
	/* 初始化LCD的RST管脚，配置为推挽输出 */
	LCD_IOInitStructure.Pin = LCD_RST_Bit;
	LCD_IOInitStructure.Mode = GPIO_MODE_OUTPUT_PP;
	LCD_IOInitStructure.Speed = GPIO_SPEED_FREQ_HIGH;
	HAL_GPIO_Init(LCD_RST_Group, &LCD_IOInitStructure);	
	LCD_RST_1;


	
	/* 初始化LCD的BL管脚，配置为推挽输出 */
	LCD_IOInitStructure.Pin = LCD_BL_Bit;
	LCD_IOInitStructure.Mode = GPIO_MODE_OUTPUT_PP;
	LCD_IOInitStructure.Speed = GPIO_SPEED_FREQ_HIGH;
	HAL_GPIO_Init(LCD_BL_Group, &LCD_IOInitStructure);	
	LCD_BL_ON;

    /* 初始化LCD的DATA管脚，配置为推挽输出 */				  //设置端口
    LCD_IOInitStructure.Pin = LCD_DATA0_Bit | LCD_DATA1_Bit | LCD_DATA2_Bit |LCD_DATA3_Bit | LCD_DATA4_Bit | LCD_DATA5_Bit | LCD_DATA6_Bit| LCD_DATA7_Bit;   
	LCD_IOInitStructure.Mode = GPIO_MODE_OUTPUT_PP;
	LCD_IOInitStructure.Speed = GPIO_SPEED_FREQ_HIGH;
	HAL_GPIO_Init(LCD_DATA_PORT, &LCD_IOInitStructure);		
}





/*
 函数名称:	对GPIO端口寄存器更新指定连续8位数据(并行)，不影响其他位
 LowBit:	最低位
 data	：	数据字节

*/
void PutData8(GPIO_TypeDef * PORT,uint8_t LowBit,uint8_t data)
{
	uint16_t DataBuf =0;
	uint16_t value =data;
	DataBuf=GPIO_ReadOutputData(PORT);
	value =(value<<LowBit);
	DataBuf &=~(0XFF<<LowBit);
	value =value|DataBuf;
	GPIO_Write(PORT,value);
}



/*
函数名称：void LCD_WriteCmd(uint8_t cmd)
函数功能：向LCD驱动IC写入一个字节的控制指令


*/
void LCD_WriteCmd(uint8_t Cmd)
	
{
//	LCD_XCS=0;
//	GPIO_ResetBits(LCD_CS_Group,LCD_CS_Bit);
	LCD_CS_0;
	
//	LCD_A0=0;
//	GPIO_ResetBits(LCD_A0_Group,LCD_A0_Bit);
	LCD_A0_0;
	
//	LCD_RD=1;
//	GPIO_SetBits(LCD_RD_Group,LCD_RD_Bit);
	LCD_RD_1;
	
//	LCD_WR=0;
//	GPIO_ResetBits(LCD_WR_Group,LCD_WR_Bit);
	LCD_WR_0;
	
//	port=cmd;
	PutData8(LCD_DATA_PORT,LCD_DATA_LowBit,Cmd);
	
//	LCD_WR=1;
//	GPIO_SetBits(LCD_WR_Group,LCD_WR_Bit);
	LCD_WR_1;
	
//	LCD_XCS=1;
//	GPIO_SetBits(LCD_CS_Group,LCD_CS_Bit);
	LCD_CS_1;
	
	
}

/*
函数名称:void LCD_WriteOneByte(uint8_t Data)
函数功能:向液晶驱动IC写入一个字节的数据/指令
Data：数据内容
*/

void LCD_WriteOneByte(uint8_t Data)
{
//	LCD_XCS=0;
//	GPIO_ResetBits(LCD_CS_Group,LCD_CS_Bit);
	LCD_CS_0;
	
//	LCD_A0=1;
//	GPIO_SetBits(LCD_A0_Group,LCD_A0_Bit);
	LCD_A0_1;
	
//	LCD_RD=1;
//	GPIO_SetBits(LCD_RD_Group,LCD_RD_Bit);
	LCD_RD_1;
	
//	LCD_WR=0;
//	GPIO_ResetBits(LCD_WR_Group,LCD_WR_Bit);
	LCD_WR_0;
	
//	port=dat;
	PutData8(LCD_DATA_PORT,LCD_DATA_LowBit,Data);
	
//	LCD_WR=1;
//	GPIO_SetBits(LCD_WR_Group,LCD_WR_Bit);
	LCD_WR_1;
	
//	LCD_XCS=1;
//	GPIO_SetBits(LCD_CS_Group,LCD_CS_Bit);
	LCD_CS_1;
}


/*
	函数名称:对液晶进行初始化
	函数说明:此液晶只针对由深圳同华实业提供的TG160160B-18系列液晶，该函数也由官方提供 采用的驱动芯片为UC1698
	注意事项:在使用该函数之前应进行液晶的上电复位操作  把RST管脚拉低  然后再抬高
*/
void Lcd_Init(void)
{
	
	//写指令函数     // (指令表中的多少条指令)   指令英文名和参数   指令中文解释
	LCD_WriteCmd(0xE2); // (23) SYSTEM RESET    系统复位

	LCD_WriteCmd(0xC8);// (19)SET N-LINE INVERSION
 	LCD_WriteCmd(0x13);
 	
 	LCD_WriteCmd(0xA0);//(14)SET LINE rate
 	
	LCD_WriteCmd(0XEB); // (26) SET LCD BIAS RATIO   0xE8:5  0xE9:10  0xEA:11  0xEB:12     设置LCD的偏压比

	LCD_WriteCmd(0x81); // (10) SET VBIAS POTENTIOMETER     设置VOP指令
	LCD_WriteCmd(120); //  set  vop  0~255  d8:17.0v               给定具体的VOP值  值越大显示越深	//b8:16.2v

	LCD_WriteCmd(0xaf); // (17) SET DISPLAY ENABLE

	LCD_WriteCmd(0xf4); //  (30) SET WINDOW PROGRAM STARTING COLUMN ADDRESS  设置显示窗口（即显示RAM）的最左边第一条竖线对应IC的SEG位置
	LCD_WriteCmd(0x25); //     设置  3x27（0x25）=111  LCD  内部逻辑将最左边的第一条竖线对应UC1698的SEG112。
				 //     上面的3x27中的3含义是  UC1698是彩屏IC  一个彩色点是用三个单色的R G B 点组成，
				 //     现在我们将三个单色的R G B 点分别用来表示三个单色的黑白点

	LCD_WriteCmd(0xf5); //  (31) SET WINDOW PROGRAM STARTING ROW ADDRESS    设置显示窗口（即显示RAM）的最上边第一条横线对应IC的COM位置
	LCD_WriteCmd(0x00); //      设置  0(0x00)           LCD  内部逻辑将最上边的第一条横线对应UC1698的COM1。

	LCD_WriteCmd(0xf6); //  (32) SET WINDOW PROGRAM ENDING COLUMN ADDRESS    设置显示窗口（即显示RAM）的最右边最后一条竖线对应IC的SEG位置
	LCD_WriteCmd(0x5A); //      设置  3x90（0x5A）=270  LCD  内部逻辑将最右边的最后一条竖线对应UC1698的SEG271。   270 - 111 = 160（刚好160条竖线）

	LCD_WriteCmd(0xf7); //  (33) SET WINDOW PROGRAM ENDING ROW ADDRESS      设置显示窗口（即显示RAM）的最下边最下边一条横线对应IC的COM位置
	LCD_WriteCmd(0xa0); //      设置  160(0xa0)         LCD  内部逻辑将最下边一条横线对应UC1698的COM160
                 //   点阵图    显存大小包含标记为'-'和'+'区域 ，而我没的TG160160 显示窗口仅包含标记为'+'区域,标记为'-'区域能往里写数据，但我们的屏上看不到
                 //        seg1 seg2  seg3 ... seg111 seg112 seg113 ... seg269 seg270 seg271 ... seg384
                 //  com160  -   -     -    -    -      +      +     +     +     +       -    -     -
                 //  com159  -   -     -    -    -      +      +     +     +     +       -    -     -
                 //  com158  -   -     -    -    -      +      +     +     +     +       -    -     -
                 //  ...     -   -     -    -    -      +      +     +     +     +       -    -     -
                 //  com2    -   -     -    -    -      +      +     +     +     +       -    -     -
                 //  com1    -   -     -    -    -      +      +     +     +     +       -    -     -


	LCD_WriteCmd(0xf8); //  (34) SET WINDOW PROGRAM MODE  设置显示窗口的编程模式 设置成内部模式（ac3=0），
                 //      使写显示数据时，显存的地址指针能依据上面设置的窗口命令（0xf4  0xf5 0xf6 0xf7）为边界自动换行
	LCD_WriteCmd(0xd1); //  (20) SET COLOR PATTERN 设置色彩样式 ，即RGB和SEG的对应关系
                 //       设置(0xd1) RGB和SEG的对应关系为  SEG1->R SEG2->G SEG3->B SEG4->R ......  SEG111->R 循环
	LCD_WriteCmd(0xd5); //  (21) SET COLOR MODE   设置色彩模式
                 //       设置 (0xd5)  LC[7:6] = 01b  ( RRRR-GGGG-BBBB, 4K-color（4K色）)
                 //       8位接口写数据字节顺序      DB7 DB6 DB5 DB4 DB3 DB2 DB1 DB0 每个字节对应位的颜色关系（我们的屏为单色，但也要注意顺序）
                 //         写第一个字节数据         R3  R2  R1  R0  G3  G2  G1  G0
                 //         写第二个字节数据         B3  B2  B1  B0  R3  R2  R1  R0
                 //         写第三个字节数据         G3  G2  G1  G0  B3  B2  B1  B0
                 //         写第四个字节数据         R3  R2  R1  R0  G3  G2  G1  G0   循环 同第一个字节数据
                 //         R3R2R1R0  G3G2G1G0  B3B2B1B0  分别代表红绿蓝R G B 三个色点，每个点由4位表示，即每个点可以有16级灰度，
                 //         如是彩色共有16（R）x 16（G）X 16（B）= 4096 (4K色)
                 //   特别注意   此处表明连续写三个字节才对应显示屏上的6个点，即平均写2个字对应1个点
                 //   特别注意   写显存一行的字节数一定是3的倍数，不然写进去的数据会显示不全，少一两个点
                 //              我们的屏一行1-160，160不是3的倍数，如要写满一行需要从左到右写162（刚好3的倍数）个点即81个字节数据
                 //              图片取膜时一定要将图片大小设置成162（seg）X 160（com） 切记不能做成160（seg）X 160（com），这样会右侧显示不全或乱码
	LCD_WriteCmd(0xC4); //  (18) SET LCD MAPPING CONTROL   设置LCD屏和IC RAM 的对应关系
                 //       通过修改此指令可以实现显示画面的左右上下镜像 而不改变显存内容，但实际上我们的SEG左右不对称。
}
 

/*
函数名称：uint8_t Fill_LcdRAM_1DOT(uint8_t Row,uint8_t Column,DOT)
函数功能：更新RAM某一点阵数据

Row:行号0--X
Column:列号0--Y
返回值:0 更新成功 1:行地址超标 2:列地址超标
*/

uint8_t Fill_LcdRAM_1DOT(uint8_t Row,uint8_t Column,uint8_t DOT)
{
	uint8_t X_add =Row;		//行地址
	uint8_t Y_add =Column;	//列地址
	uint8_t ColumnNum =Column/2;//字节位
	uint8_t ColumnCh =Column%2;	//高地位
	uint8_t Databuf =0;
	
	if (X_add >=LCD_Row_NUM)		//判断行地址是否超标
	{
		return 1;
	}
	if ( Y_add >=LCD_Column_NUM)	//判断列地址是否超标
	{
		return 2;
	}
	Databuf =LCD_RAM.Scan_Value[Row][ColumnNum];
	if ( DOT ==0)
	{
		if ( ColumnCh ==0)//高字节
		{
			Databuf &=0X0F;
		}
		else			  //低字节
		{
			Databuf &=0XF0;
		}
	}
	else
	{
		if ( ColumnCh ==0)//高字节
		{
			Databuf |=0XF0;
		}
		else			  //低字节
		{
			Databuf |=0X0F;
		}		
	}
	LCD_RAM.Scan_Value[Row][ColumnNum] =Databuf;
	return 0;
}

/*
 函数名称：uint8_t Update_LcdRAM_Row(uint8_t Row,uint8_t DOT)
 函数功能：对RAM某一行填黑或者清零
*/

uint8_t Fill_LcdRAM_Row(uint8_t Row,uint8_t DOT)
{
	uint8_t ErrState =0;
	uint8_t YNum =0;
	
	for ( YNum =0;YNum<LCD_Column_NUM;YNum++)
	{
		ErrState =Fill_LcdRAM_1DOT(Row,YNum,DOT);
		if ( ErrState !=0)
		{
			return 1;
		}
	}
	return 0;
}

/*
 函数名称：uint8_t Update_LcdRAM_Column(uint8_t Column,uint8_t DOT)
 函数功能：对RAM某一行填黑或者清零
*/
uint8_t Fill_LcdRAM_Column(uint8_t Column,uint8_t DOT)
{
	uint8_t ErrState =0;
	uint8_t XNum =0;
	
	for ( XNum =0;XNum<LCD_Row_NUM;XNum++)
	{
		ErrState =Fill_LcdRAM_1DOT(XNum,Column,DOT);
		if ( ErrState !=0)
		{
			return 1;
		}
	}
	return 0;
}

/*
 函数名称：uint8_t Fill_LcdRAM_Region(uint8_t Row1,uint8_t Column1,uint8_t Row2,uint8_t Column2,uint8_t DOT)
 函数功能：对RAM某一区域填黑或者清零
 Row1:起始X坐标 
 Row2:终止X坐标
 Column1:起始Y坐标
 Column2:终止Y坐标
*/
uint8_t Fill_LcdRAM_Region(uint8_t Row1,uint8_t Column1,uint8_t Row2,uint8_t Column2,uint8_t DOT)
{
	uint8_t ErrState =0;
	uint8_t XNum =Row1;
	uint8_t YNum =Column1;
	
	if (( Row1>=LCD_Row_NUM)||(Row2>=LCD_Row_NUM)||( Column1>=LCD_Column_NUM)||( Column2>=LCD_Column_NUM))
	{
		return 1;
	}
	
	for ( XNum =Row1;XNum<=Row2;XNum++)
	{
		for ( YNum =Column1;YNum<=Column2;YNum++)
		{
			ErrState =Fill_LcdRAM_1DOT(XNum,YNum,DOT);
			if ( ErrState !=0)
			{
				return 1;
			}
		}
		
	}
	return 0;
}

/*
 函数名称：uint8_t Fill_LcdRAM_Region(uint8_t Row1,uint8_t Column1,uint8_t Row2,uint8_t Column2,uint8_t DOT)
 函数功能：对RAM某一区域填黑或者清零
 Row1:起始X坐标 
 Column1:起始Y坐标
 opposite_X:偏移X坐标
 opposite_Y:偏移Y坐标
 DOT: 1点黑  0清零
*/
uint8_t Fill_LcdRAM_Region_Opposite(uint8_t Row1,uint8_t Column1,uint8_t opposite_X,uint8_t opposite_Y,uint8_t DOT)
{
	uint8_t ErrState =0;
	uint8_t RowEnd =Row1+opposite_X;
	uint8_t ColumnEnd =Column1+opposite_Y;
	ErrState =Fill_LcdRAM_Region(Row1,Column1,RowEnd,ColumnEnd,DOT);
	return ErrState;
}

/*
 函数名称：uint8_t Fill_LcdRAM_Region_ALL(uint8_t DOT)
 函数功能：对RAM全部区域填黑或者清零
 DOT: 1点黑  0清零
*/

uint8_t Fill_LcdRAM_Region_ALL(uint8_t DOT)
{
	uint8_t ErrState =0;
	uint8_t RowEnd =LCD_Row_NUM -1;
	uint8_t ColumnEnd =LCD_Column_NUM -1;
	ErrState =Fill_LcdRAM_Region(0,0,RowEnd,ColumnEnd,DOT);
	return ErrState;
}


/*
 函数名称：Update_LcdRAM_ALL(void)
 函数功能：刷新 LCDRAM显示区
*/
void Update_LcdRAM_ALL(void)
{

	uint32_t i=0;

		            // 设置(0x25)显存竖线地址指针开始位置，显存竖线地址和显示屏的竖线地址对应，即不写标记为'-'区域，直接写标记为'+'区域
	LCD_WriteCmd(0x05);	//  set column adress LSB CA3 CA2 CA1 CA0  =05  //05
	LCD_WriteCmd(0x12); //  set column adress MSB CA6 CA5 =02          // 12
						// 设置(0x00)显存横线地址指针开始位置，显存横线地址和显示屏的横线地址对应，即不写标记为'-'区域，直接写标记为'+'区域
	LCD_WriteCmd(0X60); //  set ROW adress LSB RA3 RA2 RA1 RA0  =00//60
	LCD_WriteCmd(0x70); //  set ROW adress MSB RA7 RA6 RA5 RA4  =00//70


	for ( i =0;i<LCD_Row_NUM*LCD_Column_Byte;i++)
	{
	
		LCD_WriteOneByte(LCD_RAM.data_S[i]);   //a byte per a pixel   写一个字节数据
		
	}

}


/*
 函数名称：Update_LcdRAM_Row(void)
 函数功能：刷新 LCDRAM显示区(显示某些行)
 注意事项：StartRow为数据刷新起始行数
				 Rows为要数据刷新的行数
*/
void Update_LcdRAM_Row(uint8_t StartRow,uint8_t Rows)
{

	 uint32_t i=0;
		            // 设置(0x25)显存竖线地址指针开始位置，显存竖线地址和显示屏的竖线地址对应，即不写标记为'-'区域，直接写标记为'+'区域
	LCD_WriteCmd(0x05);	//  set column adress LSB CA3 CA2 CA1 CA0  =05
	LCD_WriteCmd(0x12); //  set column adress MSB CA6 CA5 =02
						// 设置(0x00)显存横线地址指针开始位置，显存横线地址和显示屏的横线地址对应，即不写标记为'-'区域，直接写标记为'+'区域
	LCD_WriteCmd(0x60|(StartRow&0x0f)); //  set ROW adress LSB RA3 RA2 RA1 RA0  =00      设置y地址
    LCD_WriteCmd(0x70|(StartRow>>4));   //  set ROW adress MSB RA7 RA6 RA5 RA4  =00
	for ( i =StartRow*LCD_Column_Byte;i<(StartRow+Rows)*LCD_Column_Byte;i++)
	{
		LCD_WriteOneByte(LCD_RAM.data_S[i]);   //a byte per a pixel   写一个字节数据

	}
}


/*
 函数名称:FindZMStation(uint16_t Code)
 函数功能:在汉字库里查找相应汉字的位置并通过返回值递交字模定位
*/

INT16U FindZMStation(uint16_t Code)
{
  uint16_t Counter;
  for(Counter=0;;Counter++)
    {
      uint16_t tmp = ZKIndex[Counter++] << 8;
      tmp += ZKIndex[Counter];
      if( tmp==0xFFFF)
        {
          return 0;
        }
      else
        {
          if( tmp==Code)
            {
              return Counter/2;
            }
        }
    }
};


void DispArray(uint16_t XAdd,uint16_t YAdd,uint16_t Width,uint16_t Hight,uint8_t DispMode,const unsigned char *Array)
{
	uint8_t	DataBuff =0;
	uint8_t DeelData =0;
	uint16_t XCount =0;
	uint16_t YCount =0;
	uint16_t ArrayWidth =0;
	if((XAdd+Width)>LCD_Width)
    {
		return;
    }
	if(YAdd>LCD_Hight)
    {
		return;
    }
	ArrayWidth=((Width%8)>0)?((Width/8)+1):(Width/8);	//算出字符宽度所占字节数量

	if(DispMode==0)/*正常显示  白底黑字*/
    {
		for(YCount=0;YCount<Hight;YCount++)
        {
			for(XCount=0;XCount<Width;XCount++)
            {
				DeelData=*(Array+(XCount/8)+YCount*ArrayWidth);	//算出点阵所在字模的的字节位置
				DataBuff = VisionBuf[YAdd+YCount].ColBuf[(XAdd+XCount)/8];	//取出点阵所在显示缓存区对应的字节
				
				if ((DeelData&BitTab[XCount%8])==0)
				{
					VisionBuf[YAdd+YCount].ColBuf[(XAdd+XCount)/8]= DataBuff&(~(BitTab[((XAdd+XCount)%8)]));
				}
				else
                {
					VisionBuf[YAdd+YCount].ColBuf[(XAdd+XCount)/8] = DataBuff|(BitTab[((XAdd+XCount)%8)]);
                }
            }
        }
    }
	
	else	/*反向显示  黑底白字*/
	{
		for(YCount=0;YCount<Hight;YCount++)
        {
			for(XCount=0;XCount<Width;XCount++)
            {
				DeelData=*(Array+(XCount/8)+YCount*ArrayWidth);	//算出点阵所在字模的的字节位置
				DataBuff = VisionBuf[YAdd+YCount].ColBuf[(XAdd+XCount)/8];	//取出点阵所在显示缓存区对应的字节
				
				if ((DeelData&BitTab[XCount%8])==0)
                {
					VisionBuf[YAdd+YCount].ColBuf[(XAdd+XCount)/8] = DataBuff|(BitTab[((XAdd+XCount)%8)]);

                }
				else
                {
					VisionBuf[YAdd+YCount].ColBuf[(XAdd+XCount)/8]= DataBuff&(~(BitTab[((XAdd+XCount)%8)]));
                }
            }
        }
    }
};


/*

函数功能:字符串调用并显示API接口，通过该接口可以在屏幕指定位置显示一串字符或者汉字
输入参数  Xadd横坐标（左—>右）;Yadd纵坐标（上—>下）;Lettersp 字符串的地址 ;Mode 显示模式 0白底黑字 1黑底白字;  FontType:字体大小  此函数目前可支持宋体 9 10 11 12四种
*/
void DispStringM(uint16_t Xadd,uint16_t Yadd,  const char*   Lettersp,uint8_t Mode,uint8_t FontType)   //字体的选择及黑底白字或白底黑字的选择
{
    uint8_t number;	//ASCII码计数器
    uint16_t CurryX;//当前横坐标
    uint16_t  Temp1;//字模地址
	uint8_t *Letters;//字模首址
    CurryX=Xadd;
    Letters = (uint8_t *)Lettersp;
    for(number=0;*(Letters+number)!='\0';)
    {
        if(Letters[number]<128)  //字符
        {
            if (FontType==9) 	 //宋体9号
            {
                DispArray(CurryX,Yadd,6,12,Mode,ASCII12[Letters[number]-0x20]);
                CurryX=CurryX+6;
            }
            else if(FontType==10) //宋体10号
            {
                DispArray(CurryX,Yadd,7,13,Mode,ASCII13[Letters[number]-0x20]);
                CurryX=CurryX+7;
            }
            else if(FontType==11) //宋体11号
            {
                DispArray(CurryX,Yadd,8,15,Mode,ASCII15[Letters[number]-0x20]);
                CurryX=CurryX+8;
            }
            else if(FontType==12) //宋体12号
            {
                DispArray(CurryX,Yadd,8,16,Mode,ASCII16[Letters[number]-0x20]);
                CurryX=CurryX+8;
            }
            number++;
        }
        else //汉字
        {
            Temp1=FindZMStation(( Letters[number] << 8 )+ Letters[number+1] );
            if(Temp1!=0xFFFF)
            {
                if (FontType==9) //宋体9号
                {
                    DispArray(CurryX,Yadd,12,12,Mode,Zkarry12[Temp1]);
                }
                else if (FontType==10)//宋体10号
                {
                    DispArray(CurryX,Yadd,13,13,Mode,Zkarry13[Temp1]);
                }
                else if (FontType==11)//宋体11号
                {
                    DispArray(CurryX,Yadd,15,15,Mode,Zkarry15[Temp1]);
                }
                else if (FontType==12)//宋体12号
                {
                    DispArray(CurryX,Yadd,16,16,Mode,Zkarry16[Temp1]);
                }
            }
            if (FontType==9)//宋体9号
            {
                CurryX=CurryX+12;
            }
            else if (FontType==10)//宋体10号
            {
                CurryX=CurryX+13;
            }
            else if (FontType==11)//宋体11号
            {
                CurryX=CurryX+15;
            }
            else if (FontType==12)//宋体12号
            {
                CurryX=CurryX+16;
            }			
            number+=2;
        }
    }
};


/*
 函数名称：void Update_VisionBuf_TO_LcdRAM(void) 
 函数功能：视觉缓冲区到LCD_RAM缓冲区的景象子涵
 功能描述：通过视觉缓冲区每行的每个点阵字节对应LCD_RAM缓冲区的四个字节

 注意此驱动为小端模式!!!!!!!

*/

void Update_VisionBuf_TO_LcdRAM(void) 
{	
	uint8_t VisBuf =0;	//显示缓冲区当前字节
	uint32_t LcdBuf =0;	//LCD缓冲区当前字节
	uint8_t CUX =0;		//操作列字节
	uint8_t CUY =0;		//操作行坐标

	for ( CUY =0;CUY<LCD_Hight;CUY++)		//行扫描
	{
		for (CUX =0;CUX<20;CUX++)			//列字节扫描
		{
			VisBuf =VisionBuf[CUY].ColBuf[CUX];	//读取当前列字节
			
			LcdBuf =LCD_RAM.group[CUY].Word[CUX];//原数据读取
			
			if ( (VisBuf&0X80) ==0)	//左数第一位,实际为低第1字节高><2
			{
				LcdBuf &=0XFFFFFF0F;
			}
			else
			{
				LcdBuf |=0X000000F0;
			}
			
			if ( (VisBuf&0X40) ==0)//左数第二位,实际为低第1字节低><1
			{
				LcdBuf &=0XFFFFFFF0;
			}
			else
			{
				LcdBuf |=0X0000000F;
			}
			
			
			if ( (VisBuf&0X20) ==0)//左数第三位,实际为低第2字节高><4
			{
				LcdBuf &=0XFFFF0FFF;
			}
			else
			{
				LcdBuf |=0X0000F000;
			}
			
			if ( (VisBuf&0X10) ==0)//左数第四位,实际为低第2字节低><3
			{
				LcdBuf &=0XFFFFF0FF;
			}
			else
			{
				LcdBuf |=0X0000F00;
			}
	
			if ( (VisBuf&0X08) ==0)//左数第五位,实际为低第3字节高><6
			{
				LcdBuf &=0XFF0FFFFF;
			}
			else
			{
				LcdBuf |=0X00F00000;
			}
			
			if ( (VisBuf&0X04) ==0)//左数第六位,实际为低第3字节低><5
			{
				LcdBuf &=0XFFF0FFFF;
			}
			else
			{
				LcdBuf |=0X000F0000;
			}
			
			if ( (VisBuf&0X02) ==0)//左数第七位,实际为低第4字节高><8
			{
				LcdBuf &=0X0FFFFFFF;
			}
			else
			{
				LcdBuf |=0XF0000000;
			}
			
			if ( (VisBuf&0X01) ==0)//左数第八位,实际为低第4字节低><7
			{
				LcdBuf &=0XF0FFFFFF;
			}
			else
			{
				LcdBuf |=0X0F000000;
			}
			LCD_RAM.group[CUY].Word[CUX] =LcdBuf;	//运算后数据回传
			
		}
	}
	
}


/* 函数名称：Clear_VisionBUF()
 * 函数功能：清除显示缓存器
 * 功能描述：用于定时刷新显示缓存器，使用此函数后显示缓存器清零
 */
void Clear_VisionBUF(void)
{
  	INT16U x =0;
	INT16U y =0;
	for ( y=0;y<LCD_Row_NUM;y++)
	 {
		 for ( x=0;x<LCD_Column_Word;x++)
		 {
			 VisionBuf[y].ColBuf[x]=0X00;
		}
    }
    
}



/* 
//函 数 名: GUI_Point() 
//功 能：	在指定位置上画点
//入口参数：  X		指定点所在横坐标的位置
//            Y		指定点所在纵坐标的位置
//            color	显示颜色(为0时灭，为1时显示)
//出口参数： 无
//返 回 值： 返回值为0时表示操作成功
			  返回值为1时表示横坐标超限
			  返回值为0时表示纵坐标超限

*/
INT8U  GUI_Point(INT8U X, INT8U Y, INT8U Color)
{ 
	INT8U ErrFlg =0;
	INT8U X_add =X;		//列地址
	INT8U Y_add =Y;		//行地址
	INT8U Databuf =X_add/8;
	INT8U DatabufDot =X_add%8;
	if (X_add >=LCD_Width)	//判断列地址是否超标
	{
		ErrFlg =1;
		return ErrFlg;
	}
	if ( Y_add >=LCD_Hight)	//判断行地址是否超标
	{
		ErrFlg =2;
		return ErrFlg;
	}
	
    	// 设置缓冲区相应的点
	if (Color )    
	{
		VisionBuf[Y_add].ColBuf[Databuf]|=BitTab[DatabufDot];
	}
	else
	{
		VisionBuf[Y_add].ColBuf[Databuf]&=(~BitTab[DatabufDot]);
	}
	return ErrFlg;
    
}


 //============================================================================= 
//函 数 名: GUI_Line() 
//功 能:    画线子程序:为了回避复杂的浮点运算,采用了整数数字微分的方法
//			以(x列,y行)为起点,以(x1列,y1行)为终点画一条直线
//入口参数: x,y	起始坐标	x1,y1终点坐标	color:0-1 0:白线 1:黑线
//	 ┏━━━━━━━━┓
//	 ┃ x,y ------->x1 ┃
//	 ┃	|╲			   ┃
//   ┃ |  ╲		   ┃	
//	 ┃	|	 ╲		   ┃
//	 ┃	y1	  x1,y1	   ┃
//	 ┗━━━━━━━━┛
//		   zuo
//出口参数: 无 
//返 回 值: 无
//============================================================================= 

INT8U GUI_Line( int16_t x, int16_t y, int16_t x1, int16_t y1, uint8_t color) 
{ 
	INT8U ErrFlg =0;
	int16_t dx,dy,err = 0;
	if (x1 >=LCD_Width)	//判断列地址是否超标
	{
		ErrFlg =1;
		return ErrFlg;
	}
	if ( y1 >=LCD_Hight)	//判断行地址是否超标
	{
		ErrFlg =2;
		return ErrFlg;
	}

	if(y != y1)
	{
		if(y1 < y) /*这个判断语句保证了y1>=y这个前提*/
		{
			dx = y1; dy = x1;
			y1 = y;  x1 = x;
			y = dx;  x = dy;
		}
		dy = y1 - y;
		dx = x1 - x;
		GUI_Point(x ,y,color);
		
		if((x1 >= x)&&((y1 - y) <= (x1 - x)))
		{
			for(;x != x1;)
			{
				if(err < 0)
				{
					GUI_Point(x + 1,y,color);
					x += 1;
					err += dy;
				}
				else
				{
					GUI_Point(x + 1,y + 1,color);
					x += 1;
					y += 1;
					err += (dy - dx);
				}
			}
		}
		else
			if((x1 >= x)&&((y1 - y) > (x1 - x)))
			{
				for(;y != y1;)
				{
					if(err < 0)
					{
						GUI_Point(x + 1,y + 1,color);
						x += 1;
						y += 1;
						err += (dy - dx);
					}
					else
					{
						GUI_Point(x,y + 1,color);
						y += 1;
						err -= dx;
					}
				}
			}
			else
				if((x1 < x)&&((y1 - y) <= (x - x1)))
				{
					for(;x != x1;)
					{
						if(err < 0)
						{
							GUI_Point(x - 1,y,color);
							x -= 1;
							err += dy;
						}
						else
						{
							GUI_Point(x - 1,y + 1,color);
							x -= 1;
							y += 1;
							err += (dy + dx);
						}
					}
				}
				else
					if((x1 < x)&&((y1 - y) > (x1 - x)))
					{
						for(;y != y1;)
						{
							if(err < 0)
							{
								GUI_Point(x - 1,y + 1,color);
								x -= 1;
								y += 1;
								err += (dy + dx);
							}
							else
							{
								GUI_Point(x,y + 1,color);
								y += 1;
								err += dx;
							}
						}
					}
	}	
	else
	{
		dx = x; dy = x1;
		if(x < x1)
		{
			dx = x1;
			dy = x;
		}
		for(;dy < dx;dy++)
			GUI_Point(dy,y,color);

			GUI_Point(x1 ,y1,color);
	}
	return ErrFlg;
}
 //============================================================================= 
//函 数 名: GUI_Circle() 
//功 能:    指定圆心位置及半径，画圆
//入口参数: x0		圆心的x坐标值
//          y0		圆心的y坐标值
//          r       圆的半径
//          color	显示颜色
//出口参数: 无 
//返 回 值: 无
//============================================================================= 
void  GUI_Circle(uint32_t x0, uint32_t y0, uint32_t r, uint8_t color)
{ 
	int32_t  draw_x0, draw_y0;			// 刽图点坐标变量
	int32_t  draw_x1, draw_y1;	
	int32_t  draw_x2, draw_y2;	
	int32_t  draw_x3, draw_y3;	
	int32_t  draw_x4, draw_y4;	
	int32_t  draw_x5, draw_y5;	
	int32_t  draw_x6, draw_y6;	
	int32_t  draw_x7, draw_y7;	
	int32_t  xx, yy;					// 画圆控制变量
 
	int32_t  di;						// 决策变量
   
	/* 参数过滤 */
	if(0==r) return;

	/* 计算出8个特殊点(0、45、90、135、180、225、270度)，进行显示 */
	draw_x0 = draw_x1 = x0;
	draw_y0 = draw_y1 = y0 + r;
	if(draw_y0<LCD_Hight) GUI_Point(draw_x0, draw_y0, color);	// 90度

	draw_x2 = draw_x3 = x0;
	draw_y2 = draw_y3 = y0 - r;
	if(draw_y2>=0) GUI_Point(draw_x2, draw_y2, color);			// 270度
   
	
	draw_x4 = draw_x6 = x0 + r;
	draw_y4 = draw_y6 = y0;
	if(draw_x4<LCD_Width) GUI_Point(draw_x4, draw_y4, color);	// 0度

	draw_x5 = draw_x7 = x0 - r;
	draw_y5 = draw_y7 = y0;
	if(draw_x5>=0) GUI_Point(draw_x5, draw_y5, color);			// 180度   
	if(1==r) return;					// 若半径为1，则已圆画完
   
   
	/* 使用Bresenham法进行画圆 */
	di = 3 - 2*r;					// 初始化决策变量

	xx = 0;
	yy = r;	
	while(xx<yy)
	{  
		if(di<0)
		{  
			di += 4*xx + 6;	      
		}
		else
		{ 
			di += 4*(xx - yy) + 10;
			yy--;	  
			draw_y0--;
			draw_y1--;
			draw_y2++;
			draw_y3++;
			draw_x4--;
			draw_x5++;
			draw_x6--;
			draw_x7++;	 	
		}
		xx++;   
		draw_x0++;
		draw_x1--;
		draw_x2++;
		draw_x3--;
		draw_y4++;
		draw_y5++;
		draw_y6--;
		draw_y7--;
		/* 要判断当前点是否在有效范围内 */
		if( (draw_x0<=LCD_Width)&&(draw_y0>=0) )	
		{  
			GUI_Point(draw_x0, draw_y0, color);
		}	    
		if( (draw_x1>=0)&&(draw_y1>=0) )	
		{ 
			GUI_Point(draw_x1, draw_y1, color);
		}
		if( (draw_x2<=LCD_Width)&&(draw_y2<=LCD_Hight) )	
		{  
			 GUI_Point(draw_x2, draw_y2, color);   
		}
		if( (draw_x3>=0)&&(draw_y3<=LCD_Hight) )	
		{ 
			 GUI_Point(draw_x3, draw_y3, color);
		}
		if( (draw_x4<=LCD_Width)&&(draw_y4>=0) )	
		{ 
			GUI_Point(draw_x4, draw_y4, color);
		}
		if( (draw_x5>=0)&&(draw_y5>=0) )	
		{  
			GUI_Point(draw_x5, draw_y5, color);
		}
		if( (draw_x6<=LCD_Width)&&(draw_y6<=LCD_Hight) )	
		{ 
			GUI_Point(draw_x6, draw_y6, color);
		}
		if( (draw_x7>=0)&&(draw_y7<=LCD_Hight) )	
		{  
			GUI_Point(draw_x7, draw_y7, color);
		}
   }
}


/*
函数名称:GUI_Rectangle(INT16U Xs, INT16U Ys,INT16U Xf, INT16U Yf,INT8U Color)
//入口参数: x,y	起始坐标	x1,y1终点坐标	color:0-1 0:白线 1:黑线
//	 ┏━━━━━━━━┓
//	 ┃ Xs,Ys ------->Xf  ┃
//	 ┃	|╲			         ┃
//    ┃  |    ╲	                 |	
//	 ┃	|	   ╲		         ┃
//	 ┃	Yf	  Xf,Yf	         ┃
//	 ┗━━━━━━━━┛
*/
INT8U GUI_Rectangle(INT16U Xs, INT16U Ys,INT16U Xf, INT16U Yf,INT8U Color)
{
	INT8U ErrFlg =0;
	if (Xf >=LCD_Width)	//判断列地址是否超标
	{
		ErrFlg =1;
		return ErrFlg;
	}
	if ( Yf >=LCD_Hight)	//判断行地址是否超标
	{
		ErrFlg =2;
		return ErrFlg;
	}
	GUI_Line(Xs,Ys ,Xf, Ys, Color);
	GUI_Line(Xs,Ys ,Xs, Yf, Color);
	GUI_Line(Xs, Yf,Xf,Yf , Color);
	GUI_Line(Xf, Ys,Xf,Yf , Color);

	return ErrFlg;
}

/*
函数名称:INT8U GUI_Rectangle_Dev(INT16U Xs, INT16U Ys,INT16U Xf, INT16U Yf,INT8U Color)

函数功能:画一个有内偏移的矩形   
//入口参数: x,y	起始坐标	x1,y1终点坐标	color:0-1 0:白线 1:黑线  DevNum 偏移量
//	 ┏━━━━━━━━┓
//	 ┃ Xs,Ys ------->Xf  ┃
//	 ┃	|╲			         ┃
//    ┃  |    ╲	                 |	
//	 ┃	|	   ╲		         ┃
//	 ┃	Yf	  Xf,Yf	         ┃
//	 ┗━━━━━━━━┛
*/
INT8U GUI_Rectangle_Dev(INT16U Xs, INT16U Ys,INT16U Xf, INT16U Yf, INT16U DevNum,INT8U Color)
{
	INT8U ErrFlg =0;
	
	if (Xf >=LCD_Width)	//判断列地址是否超标
	{
		ErrFlg =1;
		return ErrFlg;
	}
	if ( Yf >=LCD_Hight)	//判断行地址是否超标
	{
		ErrFlg =2;
		return ErrFlg;
	}
	if( (Xf-Xs )<=2*DevNum)
	{
		ErrFlg =1;
		return ErrFlg;	
	}
	if( (Yf-Ys )<=2*DevNum)
	{
		ErrFlg =2;
		return ErrFlg;	
	}
	
	GUI_Line(Xs,Ys ,Xf, Ys, Color);
	GUI_Line(Xs+DevNum,Ys+DevNum ,Xf-DevNum, Ys+DevNum, Color);
	
	GUI_Line(Xs,Ys ,Xs, Yf, Color);
	GUI_Line(Xs+DevNum,Ys+DevNum ,Xs+DevNum, Yf-DevNum, Color);

	GUI_Line(Xs, Yf,Xf,Yf , Color);
	GUI_Line(Xs+DevNum, Yf-DevNum,Xf-DevNum,Yf-DevNum , Color);

	GUI_Line(Xf, Ys,Xf,Yf , Color);
	GUI_Line(Xf-DevNum, Ys+DevNum,Xf-DevNum,Yf-DevNum , Color);
	return ErrFlg;
}





/* 函数名称：INT8U Fill_VisionBUF(INT8U X1,INT8U Y1,INT8U X2,INT8U Y2,INT8U Data)
 * 函数功能：填充视觉缓冲区
 */
INT8U Fill_VisionBUF(INT8U X1,INT8U Y1,INT8U X2,INT8U Y2,INT8U Data)
{
  	INT16U x =0;
	INT16U y =0;
	INT8U ErrFlg =0;
	if ((X2>=LCD_Width )||( Y2>=LCD_Hight))
	{
		ErrFlg=0XA0;
		return  ErrFlg;
	}
	for ( y=Y1;y<Y2;y++)
	 {
		 for ( x=X1;x<X2;x++)
		 {
			 GUI_Point(x, y, Data);
		}
	}
	return  ErrFlg;
    
}




/*
函数名称:Refresh_Screen
函数功能:更新屏幕
功能描述: 该函数应该设置为定期刷新屏幕的数据,第一步是把显示缓冲区的内容调入LCD的数据缓冲区 RAM 第二部把数据缓冲区的数据按照时序刷入液晶。
注意事项:该函数只是对显示的数据进行转化和输出。如需更改显示的内容请提前操作

*/
void Refresh_Screen(void)
{
	Update_VisionBuf_TO_LcdRAM();
	Update_LcdRAM_ALL();
}


/*
函数名称:Refresh_Screen_Row
函数功能:更新屏幕(按行更新)
功能描述: 该函数应该设置为定期刷新屏幕的数据,第一步是把显示缓冲区的内容调入LCD的数据缓冲区 RAM 第二部把数据缓冲区的数据按照时序刷入液晶。
注意事项:该函数只是对显示的数据进行转化和输出。如需更改显示的内容请提前操作
				StartRow为数据刷新起始行数
				Rows为要数据刷新的行数

*/

void Refresh_Screen_Row(uint8_t StartRow,uint8_t Rows)
{
	Update_VisionBuf_TO_LcdRAM();
	Update_LcdRAM_Row(StartRow,Rows);
}





/*
函数名称:Disp_Integer
函数功能:将整型数组转换为字符串
注意事项:Data为要转换的数据
*/
char* Disp_Integer(int Data)
{

	static char CH[32];
	sprintf(CH, "%d", Data); 
	return CH;
}






/*
函数名称:Disp_Float
函数功能:将浮点数据转换为字符串
注意事项:Data为要转换的数据
			   B为要保留的小数位数
*/
char* Disp_Float(float Data,int B)
{

	static char CH[32];
	sprintf(CH, "%.*f",B,Data); 
     
	return CH;
}


/*
函数名称:Disp_Float_Point
函数功能:将整型数据转换为浮点数据(带有小数点)的字符串
注意事项:Data为要转换的数据
			   B为要保留的小数位数
			   C为整型数据的总长度
*/
char* Disp_Float_Point(INT32U Data,int B,float C)
{
	int i;
	static char TIME[20];
	int D=(int)pow(10,(C-1));
	
	TIME[0] ='0'+(Data/D);
	for(i=1;i<=C;i++)
	{
		if(i<C-B)
		{
			TIME[i] ='0'+(Data%((int)pow(10,(C-i)))/((int)pow(10,(C-i-1))));
		}
		else if(i==C-B)
		{
			TIME[i] ='.';
		}
		else if(i==C)
		{
			TIME[i] ='0'+(Data%10);
		}
		else
		{
			TIME[i] ='0'+(Data%((int)pow(10,(C-i+1)))/((int)pow(10,(C-i-1+1))));
		}
	}
	
	return TIME;
}

/*

//将文件名列表合并为一个字符串例如：数组[a,bbb,ccc]->字符串"a,bbb,cc" author:wangchangshuai jlu  
char* combineFileNames(const char** fileNameList, const int count)  
{  
    if (count <= 0)  
    {  
        return NULL;  
    }  
    int i, length = 0;  
    for (i = 0; i < count; ++i)  
    {  
        length += strlen(fileNameList[i]);  
    }  
//加上逗号的个数  
    length += count - 1;  
  
    char* fileNamesStr = NULL;  
    if ((fileNamesStr = (char*) myMalloc(sizeof(char) * (length + 1))) == NULL)  
    {  
        myLog("Malloc heap failed!\n");  
        return NULL;  
    }  
    memset(fileNamesStr, 0, sizeof(char) * (length + 1));  
    strcpy(fileNamesStr, fileNameList[0]);  
    for (i = 1; i < count; ++i)  
    {  
        strcat(fileNamesStr, ",");  
        strcat(fileNamesStr, fileNameList[i]);  
    }  
    return fileNamesStr;  
} 

*/



 /*
函数名称:Disp_BCD_32
函数功能:将INT32U整型数据转换为BCD码的字符串
注意事项:input为要转换的数据
			   
*/
char* Disp_BCD_32(INT32U input)
{	
	int a=(input/16/16/16/16/16/16/16)*10000000+(input/16/16/16/16/16/16%16)*1000000+(input/16/16/16/16/16%16)*100000+(input/16/16/16/16%16)*10000+(input/16/16/16%16)*1000+((input/16/16)%16)*100+(input/16%16)*10 + input%16;
	static char ch4[20];

	sprintf(ch4, "%d", a);
	
	return ch4;
}
 /*
函数名称:Disp_BCD_16
函数功能:将INT16U整型数据转换为BCD码的字符串
注意事项:input为要转换的数据
			   
*/
char* Disp_BCD_16(INT16U input)
{	
	int a=(input/16/16/16)*1000+((input/16/16)%16)*100+(input/16%16)*10 + input%16;
	static char ch4[20];

	sprintf(ch4, "%d", a);
	
	return ch4;
}
 /*
函数名称:Disp_BCD_8
函数功能:将INT8U整型数据转换为BCD码的字符串
注意事项:input为要转换的数据
			   
*/
char* Disp_BCD_8(INT8U input)
{	
	int a=(input/16)*10 + input%16;
	static char ch4[20];
	sprintf(ch4, "%d", a);
	
	return ch4;
}

/*
函数名称:Disp_32_Binary
函数功能:将INT32U整型数据转换为16进制的字符串
注意事项:Data为要转换的数据
			   B为要保留的位数
			   C为是否补0，C=1不补0，C=0补0
			   D为对齐方式，D=1左对齐，D=0右对齐
*/
char* Disp_32_Binary(INT32U Data,int B,int C,int D)
{
	static char ch1[20];
	if(C==0)
	{
		if(D==1)
		{
			sprintf(ch1, "%-0*X",B,Data);
		}
		else
		{
			sprintf(ch1, "%0*X",B,Data);
		}
	}
	else
	{
		if(D==1)
		{
			sprintf(ch1, "%-*X",B,Data);
		}
		else
		{
			sprintf(ch1, "%*X",B,Data);
		}
	}
	return ch1;
}


/*
函数名称:Disp_16_Binary
函数功能:将INT16U整型数据转换为16进制的字符串
注意事项:Data为要转换的数据
			   B为要保留的位数
			   C为是否补0，C=1不补0，C=0补0
			   D为对齐方式，D=1左对齐，D=0右对齐
*/
char* Disp_16_Binary(INT16U Data,int B,int C,int D)
{
	static char ch1[20];
	if(C==0)
	{
		if(D==1)
		{
			sprintf(ch1, "%-0*X",B,Data);
		}
		else
		{
			sprintf(ch1, "%0*X",B,Data);
		}
	}
	else
	{
		if(D==1)
		{
			sprintf(ch1, "%-*X",B,Data);
		}
		else
		{
			sprintf(ch1, "%*X",B,Data);
		}
	}
	return ch1;
}


/*
函数名称:Disp_8_Binary
函数功能:将INT8U整型数据转换为16进制的字符串
注意事项:Data为要转换的数据
			   B为要保留的位数
			   C为是否补0，C=1不补0，C=0补0
			   D为对齐方式，D=1左对齐，D=0右对齐
*/
char* Disp_8_Binary(INT8U Data,int B,int C,int D)
{
	static char ch1[20];
	if(C==0)
	{
		if(D==1)
		{
			sprintf(ch1, "%-0*X",B,Data);
		}
		else
		{
			sprintf(ch1, "%0*X",B,Data);
		}
	}
	else
	{
		if(D==1)
		{
			sprintf(ch1, "%-*X",B,Data);
		}
		else
		{
			sprintf(ch1, "%*X",B,Data);
		}
	}
	return ch1;
}








/*
函数名称:strcat(str1,str2)
函数功能:将两个字符串合并为一个字符串
注意事项:str1为第一个字符串
			   str2为第二个字符串
			   strcat(str1,str2)输出为合并的字符串(字符串str2位于字符串str1后面)
			   例如:   
			   	char str1[] = {"2222"};
				char str2[] = {" China11111111111"};
				char A[]=strcat(str1,str2)={" 2222China11111111111"};
*/
/* END */
/*
 @copy COPYRIGHT 2016 Foryon     
*/





 

