#include "Application/GUI/gui.h" 
#include <string.h>
#include <stdlib.h>
InputBox_TypeDef MyINputBox={0};
static void StoreCharAndDis(char c);
static char *GetString(void);
static uint8_t  Del(void);
/*************************************************************************************
**@bref 创建文本框
				x 行
				y 列
				font 字号
				max_num 输入字符的数量
**************************************************************************************/
InputBox_TypeDef *CreateInputBox(uint8_t x,uint8_t y,FONT_ENUM font,uint8_t max_num)
{
	MyINputBox.max_num=max_num;
	MyINputBox.font=font;
	MyINputBox.start_x=x;
	MyINputBox.start_y=y;
	memset(MyINputBox.buff,0,BOX_LEN_BUFFER);
	MyINputBox.StoreCharAndDis=StoreCharAndDis;
	MyINputBox.GetString=GetString;
	MyINputBox.Del=Del;
	return &MyINputBox;
}

static void StoreCharAndDis(char c)
{
	uint8_t count= strlen(MyINputBox.buff);
	if(count>MyINputBox.max_num)
		return;
	if(count<BOX_LEN_BUFFER)
	{
		memset(&MyINputBox.buff[count],c,1);
		LCD_DisString(MyINputBox.font,MyINputBox.start_y+count*8,MyINputBox.start_x,(uint8_t*)"%c",c);
	}
}

static char *GetString(void)
{
	return MyINputBox.buff;
}
/*************************************************************************************
**@bref 删除单个字节
	@ret 
        1    删除空
				0    正常删除
**************************************************************************************/
static uint8_t Del(void)
{
	uint8_t count= strlen(MyINputBox.buff);
	if(count==0)
		return 1;
	LCD_DisString(MyINputBox.font,MyINputBox.start_y+(count-1)*8,MyINputBox.start_x,(uint8_t*)" ");
	MyINputBox.buff[count-1]=0;
	return 0;
}

