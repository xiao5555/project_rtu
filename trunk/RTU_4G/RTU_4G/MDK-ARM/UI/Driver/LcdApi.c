#include "DRIVER/LcdApi.h"
#include "LIB/Font/font.h"
#include <stdarg.h>
static void rom_out_pin_out(void);
static void rom_out_pin_in(void);

void lcd_address(uint8_t page,uint8_t column)
{
	column=column-1; //����ƽ����˵�ĵ� 1 �У��� LCD ���� IC ���ǵ� 0 �С������������ȥ 1.
	page=page-1;
	transfer_command(0xb0+page); //����ҳ��ַ��ÿҳ�� 8 �С�һ������� 64 �б��ֳ� 8 ��ҳ������ƽ����˵�ĵ� 1 ҳ���� LCD ���� IC ���ǵ� 0 ҳ�������������ȥ 1
	transfer_command(((column>>4)&0x0f)+0x10); //�����е�ַ�ĸ� 4 λ
	transfer_command(column&0x0f); //�����е�ַ�ĵ� 4 λ
}
//ȫ������
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
 *@bref //��ʾ 32x32 ����ͼ�񡢺��֡���Ƨ�ֻ� 32x32 ���������ͼ��
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
			transfer_data(*dp); //д���ݵ� LCD,ÿд��һ�� 8 λ�����ݺ��е�ַ�Զ��� 1
			dp++;
		}
	}
}
/********************************************************************
 *@bref //��ʾ 16x16 ����ͼ�񡢺��֡���Ƨ�ֻ� 16x16 ���������ͼ��
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
			transfer_data(*dp); //д���ݵ� LCD,ÿд��һ�� 8 λ�����ݺ��е�ַ�Զ��� 1
			dp++;
		}
	}
}
/********************************************************************
 *@bref //��ʾ 8x16 ����ͼ��ASCII, �� 8x16 ����������ַ�������ͼ��
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
			transfer_data(*dp); //д���ݵ� LCD,ÿд��һ�� 8 λ�����ݺ��е�ַ�Զ��� 1
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
					transfer_data(ascii_table_8x16[j][k+8*n]);//��ʾ 5x7 �� ASCII �ֵ� LCD �ϣ� y Ϊҳ��ַ��x Ϊ�е�ַ�����Ϊ����
				}
			}
			i++;
			column+=8;
		}
		else
		i++;
		}
}
//��ʾһ�� 5x8 ������ַ���
//������Ĳ����ֱ�Ϊ��ҳ���У��Ƿ��ԣ�����ָ�룩
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
				transfer_data(ascii_table_5x8[j][k]);//��ʾ 5x7 �� ASCII �ֵ� LCD �ϣ�y Ϊҳ��ַ��x Ϊ�е�ַ�����Ϊ����
			}
			i++;
			column+=6;
		}
		else
		i++;
	}
}
/****��ָ�����Ѷ�ֿ� IC***/

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
/****�Ӿ���Ѷ�ֿ� IC ��ȡ���ֻ��ַ����ݣ�1 ���ֽڣ�***/
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
/*����ص�ַ��addrHigh����ַ���ֽ�,addrMid����ַ���ֽ�,addrLow����ַ���ֽڣ����������� DataLen ���ֽ�
�����ݵ� pBuff �ĵ�ַ*/
/*������ȡ*/
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
 *@bref ��ʾ���ֺ��ַ���
 *      display_GB2312_string(1,1,"JLX19264G-270,�������ֿ�");
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
				/*������壨GB2312���������ֿ� IC �еĵ�ַ�����¹�ʽ�����㣺*/
			/*Address = ((MSB - 0xB0) * 94 + (LSB - 0xA1)+ 846)*32+ BaseAdd;BaseAdd=0*/
			/*���ڵ��� 8 λ��Ƭ���г˷�������⣬���Է�����ȡ��ַ*/
			fontaddr = (text[i]- 0xb0)*94;
			fontaddr += (text[i+1]-0xa1)+846;
			fontaddr = (uint32_t)(fontaddr*32);
			addrHigh = (fontaddr&0xff0000)>>16; /*��ַ�ĸ� 8 λ,�� 24 λ*/
			addrMid = (fontaddr&0xff00)>>8; /*��ַ���� 8 λ,�� 24 λ*/
			addrLow = fontaddr&0xff; /*��ַ�ĵ� 8 λ,�� 24 λ*/
			get_n_bytes_data_from_ROM(addrHigh,addrMid,addrLow,fontbuf,32 );/*ȡ 32 ���ֽڵ����ݣ��浽"fontbuf[32]"*/
			display_graphic_16x16(y,x,fontbuf);/*��ʾ���ֵ� LCD �ϣ�y Ϊҳ��ַ��x Ϊ�е�ַ��fontbuf[]Ϊ	����*/
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
				get_n_bytes_data_from_ROM(addrHigh,addrMid,addrLow,fontbuf,16 );/*ȡ 16 ���ֽڵ����ݣ��浽
			"fontbuf[32]"*/
			display_graphic_8x16(y,x,fontbuf);/*��ʾ 8x16 �� ASCII �ֵ� LCD �ϣ�y Ϊҳ��ַ��x Ϊ�е�ַ��
			fontbuf[]Ϊ����*/
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
 *@bref ��ָ��λ����ʾ���ݣ����пɱ��
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
