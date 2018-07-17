#include "Inc/LcdDriver.h"

static void transfer(uint8_t data1);
static void stop_flag(void);
static void start_flag(void);
#define delay(n) HAL_Delay(n)
extern void LCD_ClearScreen(void);
void LCD_Init(void)
{	
	LCD_REST(0); //低电平复位
	delay(100);
	LCD_REST(1); //复位完毕
	delay(800);
	transfer_command(0xe2); //软复位
	delay(200);
	transfer_command(0x2f); //打开内部升压
	delay(200);
	transfer_command(0x81); //微调对比度
	transfer_command(0x56); //微调对比度的值，可设置范围 0x00～0xFF
	transfer_command(0xeb); //1/9 偏压比（bias）
	transfer_command(0xc4); //行列扫描顺序：从上到下 oxc2
	transfer_command(0xaf); //开显示
	
	LCD_ClearScreen();
}
void transfer_command(uint8_t com)
{
	start_flag();
	transfer(0x7c);
	transfer(com);
	stop_flag();
}

void transfer_data(uint8_t dat)
{
	start_flag();
	transfer(0x7e);
	transfer(dat);
	stop_flag();
}
static void stop_flag(void)
{
	LCD_SCL(1); /*STOP FLAG*/
	LCD_SDA(0); /*STOP FLAG*/
	LCD_SDA(1); /*STOP FLAG*/
}

static void start_flag(void)
{
	LCD_SCL(1); /*START FLAG*/
	LCD_SDA(1); /*START FLAG*/
	LCD_SDA(0); /*START FLAG*/
}

/********************************************************************
 *@bref 
 *     
 *@ret 
***********************************************************************/
void transfer(uint8_t data1)
{
	int i;
	for(i=0;i<8;i++)
	{
		LCD_SCL(0);
		if(data1&0x80)LCD_SDA(1);
		else LCD_SDA(0);
		LCD_SCL(1);
		LCD_SCL(0);
		data1=data1<<1;
	}
	LCD_SDA(0);
	LCD_SCL(1);
	LCD_SCL(0);
}

