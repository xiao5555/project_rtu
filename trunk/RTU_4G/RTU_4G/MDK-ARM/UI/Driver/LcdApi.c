#include "DRIVER/LcdApi.h"
#include "LIB/Font/font.h"
#include <stdarg.h>
static void rom_out_pin_out(void);
static void rom_out_pin_in(void);

void lcd_address(uint8_t page,uint8_t column)
{
	column=column-1; //我们平常所说的第 1 列，在 LCD 驱动 IC 里是第 0 列。所以在这里减去 1.
	page=page-1;
	transfer_command(0xb0+page); //设置页地址。每页是 8 行。一个画面的 64 行被分成 8 个页。我们平常所说的第 1 页，在 LCD 驱动 IC 里是第 0 页，所以在这里减去 1
	transfer_command(((column>>4)&0x0f)+0x10); //设置列地址的高 4 位
	transfer_command(column&0x0f); //设置列地址的低 4 位
}
//全屏清屏
void LCD_ClearScreen(void)
{
	unsigned char i,j;
	for(i=0;i<8;i++)
	{
		lcd_address(1+i,1);
		for(j=0;j<192;j++)
		{
			transfer_data(0x00);
		}
	}
}
void LCD_ClearRectangle(uint8_t start_x,uint8_t start_y,uint8_t end_x,uint8_t end_y)
{
	unsigned char i,j;
	for(i=start_x;i<=end_x;i++)
	{
		lcd_address(1+i,start_y);
		for(j=start_y;j<end_y;j++)
		{
			transfer_data(0x00);
		}
	}
}
void LCD_display_graphic_192x64(uint8_t *dp)
{
	uint8_t i,j;
	for(i=0;i<8;i++)
	{
		lcd_address(i+1,1);
		for(j=0;j<192;j++)
		{
			transfer_data(*dp);
			dp++;
		}
	}
}

/********************************************************************
 *@bref //==================display a piture of 128*64 dots================
 *     
 *@ret 
***********************************************************************/
void LCD_full_display(uint8_t data_left,uint8_t data_right)
{
	uint8_t i,j;
	for(i=0;i<8;i++)
	{
		lcd_address(i+1,1);
		for(j=0;j<96;j++)
		{
			transfer_data(data_left);
			transfer_data(data_right);
		}
	}
}
/********************************************************************
 *@bref //显示 32x32 点阵图像、汉字、生僻字或 32x32 点阵的其他图标
 *     
 *@ret 
***********************************************************************/
void display_graphic_32x32(uint8_t page,uint8_t column,uint8_t *dp)
{
	uint8_t i,j;
	for(j=0;j<4;j++)
	{
		lcd_address(page+j,column);
		for (i=0;i<31;i++)
		{
			transfer_data(*dp); //写数据到 LCD,每写完一个 8 位的数据后列地址自动加 1
			dp++;
		}
	}
}
/********************************************************************
 *@bref //显示 16x16 点阵图像、汉字、生僻字或 16x16 点阵的其他图标
 *     
 *@ret 
***********************************************************************/
void display_graphic_16x16(uint8_t page,uint8_t column,uint8_t *dp)
{
	uint8_t i,j;
	for(j=0;j<2;j++)
	{
		lcd_address(page+j,column);
		for (i=0;i<16;i++)
		{
			transfer_data(*dp); //写数据到 LCD,每写完一个 8 位的数据后列地址自动加 1
			dp++;
		}
	}
}
/********************************************************************
 *@bref //显示 8x16 点阵图像、ASCII, 或 8x16 点阵的自造字符、其他图标
 *     
 *@ret 
***********************************************************************/
void display_graphic_8x16(uint8_t page,uint8_t column,uint8_t *dp)
{
	uint8_t i,j;
	for(j=0;j<2;j++)
	{
		lcd_address(page+j,column);
			for (i=0;i<8;i++)
		{
			transfer_data(*dp); //写数据到 LCD,每写完一个 8 位的数据后列地址自动加 1
			dp++;
		}
	}
}
/********************************************************************
 *@bref 
 *     
 *@ret 
***********************************************************************/
void display_string_8x16(uint16_t page,uint16_t column,uint8_t *text)
{
	uint16_t i=0,j,k,n;
	while(text[i]>0x00)
	{
		if((text[i]>=0x20)&&(text[i]<=0x7e))
		{
			j=text[i]-0x20;
			for(n=0;n<2;n++)
			{
				lcd_address(page+n,column);
				for(k=0;k<8;k++)
				{
					transfer_data(ascii_table_8x16[j][k+8*n]);//显示 5x7 的 ASCII 字到 LCD 上， y 为页地址，x 为列地址，最后为数据
				}
			}
			i++;
			column+=8;
		}
		else
		i++;
		}
}
//显示一串 5x8 点阵的字符串
//括号里的参数分别为（页，列，是否反显，数据指针）
void display_string_5x8(uint16_t page,uint16_t column,uint8_t reverse,uint8_t *text)
{
	uint8_t i=0,j,k,data1;
	while(text[i]>0x00)
	{
		if((text[i]>=0x20)&&(text[i]<=0x7e))
		{
			j=text[i]-0x20;
			lcd_address(page,column);
			for(k=0;k<5;k++)
			{
				if(reverse==1) data1=~ascii_table_5x8[j][k];
				else data1=ascii_table_5x8[j][k];
				transfer_data(data1);
			}
			if(reverse==1) transfer_data(0xff);
			else transfer_data(0x00);
			i++;
			column+=6;
		}
		else
		i++;
	}
}
void display_string_5x8_1(uint16_t page,uint16_t column,uint8_t *text)
{
	uint16_t i=0,j,k;
	while(text[i]>0x00)
	{
		if((text[i]>=0x20)&&(text[i]<0x7e))
		{
			j=text[i]-0x20;
			lcd_address(page,column);
			for(k=0;k<5;k++)
			{
				transfer_data(ascii_table_5x8[j][k]);//显示 5x7 的 ASCII 字到 LCD 上，y 为页地址，x 为列地址，最后为数据
			}
			i++;
			column+=6;
		}
		else
		i++;
	}
}
/****送指令到晶联讯字库 IC***/

void send_command_to_ROM( uint8_t datu )
{
	uint8_t i;
	for(i=0;i<8;i++ )
	{
		if(datu&0x80)
			LCD_FONT_SI(1);
		else
		LCD_FONT_SI(0);
		datu = datu<<1;
		LCD_FONT_SCLK(0);
		LCD_FONT_SCLK(1);
	}
}
/****从晶联讯字库 IC 中取汉字或字符数据（1 个字节）***/
static uint8_t get_data_from_ROM( )
{
	uint8_t i;
	uint8_t ret_data=0;
	LCD_FONT_SCLK(1);
	for(i=0;i<8;i++)
	{
		rom_out_pin_out();
		LCD_FONT_SO(1);
		LCD_FONT_SCLK(0);
		ret_data=ret_data<<1;
		rom_out_pin_in();
		if(LCD_FONT_Read_SO())/*********wcg_bug*********/
			ret_data=ret_data+1;
		else
			ret_data=ret_data+0;
		LCD_FONT_SCLK(1);
	}
	return(ret_data);
}

static GPIO_InitTypeDef GPIO_InitStruct;
void rom_out_pin_out(void)
{
  /*Configure GPIO pins : PBPin PBPin */
  GPIO_InitStruct.Pin = ROM_OUT_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_PULLUP;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_HIGH;
  HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);
}
void rom_out_pin_in(void)
{
  /*Configure GPIO pins : PBPin PBPin */
  GPIO_InitStruct.Pin = ROM_OUT_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
  GPIO_InitStruct.Pull = GPIO_PULLUP;
  HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);
}
/*从相关地址（addrHigh：地址高字节,addrMid：地址中字节,addrLow：地址低字节）中连续读出 DataLen 个字节
的数据到 pBuff 的地址*/
/*连续读取*/
void get_n_bytes_data_from_ROM(uint8_t addrHigh,uint8_t addrMid,uint8_t addrLow,uint8_t *pBuff,uint8_t DataLen )
{
	uint8_t i;
	LCD_FONT_CS(0);
	LCD_FONT_SCLK(0);
	send_command_to_ROM(0x03);
	send_command_to_ROM(addrHigh);
	send_command_to_ROM(addrMid);
	send_command_to_ROM(addrLow);
	for(i = 0; i < DataLen; i++ )
		*(pBuff+i) =get_data_from_ROM();
	LCD_FONT_CS(1);
}
/********************************************************************
 *@bref 显示汉字和字符串
 *      display_GB2312_string(1,1,"JLX19264G-270,带中文字库");
 *@ret 
***********************************************************************/
uint32_t fontaddr=0;
void display_GB2312_string(uint8_t y,uint8_t x,uint8_t *text)
{
	uint8_t i= 0;
	uint8_t addrHigh,addrMid,addrLow ;
	uint8_t fontbuf[32];
	while((text[i]>0x00))
	{
		if(((text[i]>=0xb0) &&(text[i]<=0xf7))&&(text[i+1]>=0xa1))
		{
				/*国标简体（GB2312）汉字在字库 IC 中的地址由以下公式来计算：*/
			/*Address = ((MSB - 0xB0) * 94 + (LSB - 0xA1)+ 846)*32+ BaseAdd;BaseAdd=0*/
			/*由于担心 8 位单片机有乘法溢出问题，所以分三部取地址*/
			fontaddr = (text[i]- 0xb0)*94;
			fontaddr += (text[i+1]-0xa1)+846;
			fontaddr = (uint32_t)(fontaddr*32);
			addrHigh = (fontaddr&0xff0000)>>16; /*地址的高 8 位,共 24 位*/
			addrMid = (fontaddr&0xff00)>>8; /*地址的中 8 位,共 24 位*/
			addrLow = fontaddr&0xff; /*地址的低 8 位,共 24 位*/
			get_n_bytes_data_from_ROM(addrHigh,addrMid,addrLow,fontbuf,32 );/*取 32 个字节的数据，存到"fontbuf[32]"*/
			display_graphic_16x16(y,x,fontbuf);/*显示汉字到 LCD 上，y 为页地址，x 为列地址，fontbuf[]为	数据*/
			i+=2;
			x+=16;
		}
		else if((text[i]>=0x20) &&(text[i]<=0x7e))
		{
			unsigned char fontbuf[16];
			fontaddr = (text[i]- 0x20);
			fontaddr = (unsigned long)(fontaddr*16);
			fontaddr = (unsigned long)(fontaddr+0x3b7c0);
			addrHigh = (fontaddr&0xff0000)>>16;
			addrMid = (fontaddr&0xff00)>>8;
				addrLow = fontaddr&0xff;
				get_n_bytes_data_from_ROM(addrHigh,addrMid,addrLow,fontbuf,16 );/*取 16 个字节的数据，存到
			"fontbuf[32]"*/
			display_graphic_8x16(y,x,fontbuf);/*显示 8x16 的 ASCII 字到 LCD 上，y 为页地址，x 为列地址，
			fontbuf[]为数据*/
			i+=1;
			x+=8;
		}
		else
		i++;
	}
}
void LCD_Dis(uint8_t start_line,uint8_t end_line)
{
	transfer_command(0xf2);
	transfer_command(start_line);
	transfer_command(0xf3);
	transfer_command(end_line);
}
void LCD_ReverseDisplay(void)
{
	//transfer_command();
}
/********************************************************************
 *@bref 在指定位置显示数据，带有可变参
 *     
 *@ret 
***********************************************************************/
void LCD_DisString(FONT_ENUM font,uint8_t x,uint8_t y,uint8_t *str,...)
{
	char tab[30] = { 0 };
	va_list mylist;
	va_start(mylist, str);
	vsnprintf(tab,24,(char*)str,mylist);
	va_end(mylist);
	switch((int)font)
	{
		case FONT_5x8:
			display_string_5x8(y,x,0,(uint8_t*)tab);
		break;
		case FONT_8x16:
				display_string_8x16(y,x,(uint8_t*)tab);
		break;
		case FONT_15x16:
				display_GB2312_string(y,x,(uint8_t*)tab);
		break;
		default:
			
		break;
	}
}
