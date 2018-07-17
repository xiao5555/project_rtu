#include "Inc/key.h"
#include "PrivateTimer/PrivateTimer.h"
#include <string.h>
#include "Application/GUI/gui.h"
static void line_input_column_out(void);
void line_out_column_input(void);
static void KEY_CheckValueProcess(void);
static KEY_TypeDef MyKey={0};
static uint8_t KEY_SearchValue(uint8_t val);
static const uint8_t KEY_TAB[16]={0xE7,0xEB,0xED,0xEE,0xD7,0xDB,0xDD,0xDE,0xB7,0xBB,0xBD,0xBE,0x77,0x7B,0x7D,0x7E};
static const char KEY_TABLE_VALUE[]={
'1','1','1','1','1',//'
'2','a','b','c','2',//'
'3','d','e','f','3',//'
'$','$','$','$','$',//'menu'
'4','g','h','i','4',//'
'5','j','k','l','5',//'
'6','m','n','o','6',//'
'%','%','%','%','%',//'up'
'7','p','q','r','s', //'
'8','t','u','v','8',//'
'9','w','x','y','z',//'
'&','&','&','&','&',//'down'
'.','+','-','*','#',//'
'0','0','0','0','0',//'
'@','@','@','@','@',//'esc'
'^','^','^','^','^',};//'enter'


	/*****************************************************************************************************************
	esc->@
	enter->^
	menu->$
	up->%
	down->&
*****************************************************************************************************************/
/********************************************************************
 *@bref 
 *     
 *@ret 
***********************************************************************/
static uint8_t KEY_SearchValue(uint8_t val)
{
	for(uint8_t i=0;i<sizeof(KEY_TAB);i++)
	{
		if(KEY_TAB[i]==val)
			return i;
	}
	return 0;
}
/********************************************************************
 *@bref 
 *     
 *@ret 
***********************************************************************/
void KEY_Init(void)
{
//	KEY_LINE_INPUT_COLUMN_OUT_MODE();
	line_input_column_out();
	CUSTOM_TimerCreat(KEY_Process,0,10,10);//按键检测初始化
}
/********************************************************************
 *@bref 
 *     
 *@ret 返回的按键值0~63， 0值无效
***********************************************************************/
uint8_t KEY_GetValue(void)
{
	uint8_t value=MyKey.value;
	MyKey.value=0;
	return value;
}
/********************************************************************
 *@bref 
 *     
 *@ret 
***********************************************************************/
static void KEY_CheckValueProcess(void)
{
	if(MyKey.time_count)
	{
		MyKey.time_count--;
		if(MyKey.time_count==0)
		{
			uint8_t flag,err_count=0;
			for(uint8_t i=0;i<sizeof(MyKey.buff_table);i++)
			{
				if(MyKey.buff_table[i])
				{
					flag=i;
					err_count++;
				}
			}
			if(err_count==1)
			{
				if(MyKey.buff_table[flag]>5)
				{
					MyKey.buff_table[flag]=5;
				}
				char val=KEY_TABLE_VALUE[flag*5+MyKey.buff_table[flag]-1];
				MyKey.value=val;//按键赋值				
				MyKey.buff_table[flag]=0;
				MsgPut(MSG_KEY_VALUE,(void*)((uint32_t)MyKey.value),sizeof(MyKey.value));
//				MyKey.value=0;
			}else
			{
				memset(MyKey.buff_table,0,sizeof(MyKey.buff_table));
			}
		}
	}
}

void KEY_Process(void *arg)
{
	static uint8_t key_state=0;//按键处理
	static uint8_t key_check=0;
	static uint8_t key_val=0;
	static uint32_t key_out_time;
	uint8_t c_val=0;
	key_out_time++;
	c_val=0;	
	switch(key_state)
	{
		case 0:
				c_val|=HAL_GPIO_ReadPin(KEY_LINE1_GPIO_Port,KEY_LINE1_Pin)<<0;
				c_val|=HAL_GPIO_ReadPin(KEY_LINE2_GPIO_Port,KEY_LINE2_Pin)<<1;
				c_val|=HAL_GPIO_ReadPin(KEY_LINE3_GPIO_Port,KEY_LINE3_Pin)<<2;
				c_val|=HAL_GPIO_ReadPin(KEY_LINE4_GPIO_Port,KEY_LINE4_Pin)<<3;			
				if(c_val!=0x0f)
				{
					key_check++;
					if(key_check>=2)
					{
						key_val=c_val<<4;
//						KEY_LINE_OUT_COLUMN_INPUT_MODE();//翻转
						line_out_column_input();
						key_state=1;
					}
				}else
				{
					key_check=0;
					key_out_time=0;
				}
		break;
		case 1:
				c_val|=HAL_GPIO_ReadPin(KEY_COLUMN1_GPIO_Port,KEY_COLUMN1_Pin)<<0;
				c_val|=HAL_GPIO_ReadPin(KEY_COLUMN2_GPIO_Port,KEY_COLUMN2_Pin)<<1;
				c_val|=HAL_GPIO_ReadPin(KEY_COLUMN3_GPIO_Port,KEY_COLUMN3_Pin)<<2;
				c_val|=HAL_GPIO_ReadPin(KEY_COLUMN4_GPIO_Port,KEY_COLUMN4_Pin)<<3;
				if(c_val!=0x0f)
				{			
					key_val|=c_val;
					key_state=2;
				}else
				{
					if(key_out_time>500)//长按5秒算失败
					{
						key_out_time=0;
//						KEY_LINE_INPUT_COLUMN_OUT_MODE();
						line_input_column_out();
						key_state=0;
					}
				}
		break;
		case 2:
				c_val|=HAL_GPIO_ReadPin(KEY_COLUMN1_GPIO_Port,KEY_COLUMN1_Pin)<<0;
				c_val|=HAL_GPIO_ReadPin(KEY_COLUMN2_GPIO_Port,KEY_COLUMN2_Pin)<<1;
				c_val|=HAL_GPIO_ReadPin(KEY_COLUMN3_GPIO_Port,KEY_COLUMN3_Pin)<<2;
				c_val|=HAL_GPIO_ReadPin(KEY_COLUMN4_GPIO_Port,KEY_COLUMN4_Pin)<<3;
				if(c_val==0x0f)
				{
//					KEY_LINE_INPUT_COLUMN_OUT_MODE();
					line_input_column_out();
					key_state=3;
				}
		break;
		case 3:
				MyKey.buff_table[KEY_SearchValue(key_val)]++;//对应案件值++
				key_val=0;
				key_state=0;
				key_out_time=0;
				MyKey.time_count=DEFAULT_WAIT_GET_KET_VALUE;//延迟检测
		break;
		default:
			break;
	}
	KEY_CheckValueProcess();//如果确认有按键按下300ms后读取数据
}
static GPIO_InitTypeDef GPIO_InitStruct;
void line_input_column_out(void)
{
  /*Configure GPIO pins : PDPin PDPin PDPin PDPin */
  GPIO_InitStruct.Pin = KEY_COLUMN4_Pin|KEY_COLUMN3_Pin|KEY_COLUMN2_Pin|KEY_COLUMN1_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_OD;
  GPIO_InitStruct.Pull = GPIO_PULLDOWN;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_MEDIUM;
  HAL_GPIO_Init(GPIOD, &GPIO_InitStruct);

  /*Configure GPIO pins : PDPin PDPin */
  GPIO_InitStruct.Pin = KEY_LINE4_Pin|KEY_LINE3_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
  GPIO_InitStruct.Pull = GPIO_PULLUP;
  HAL_GPIO_Init(GPIOD, &GPIO_InitStruct);

  /*Configure GPIO pins : PCPin PCPin */
  GPIO_InitStruct.Pin = KEY_LINE2_Pin|KEY_LINE1_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
  GPIO_InitStruct.Pull = GPIO_PULLUP;
  HAL_GPIO_Init(GPIOC, &GPIO_InitStruct);
}
void line_out_column_input(void)
{
  /*Configure GPIO pins : PDPin PDPin PDPin PDPin */
  GPIO_InitStruct.Pin = KEY_COLUMN4_Pin|KEY_COLUMN3_Pin|KEY_COLUMN2_Pin|KEY_COLUMN1_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
  GPIO_InitStruct.Pull = GPIO_PULLUP;
  HAL_GPIO_Init(GPIOD, &GPIO_InitStruct);
	


  /*Configure GPIO pins : PDPin PDPin */
  GPIO_InitStruct.Pin = KEY_LINE4_Pin|KEY_LINE3_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_OD;
  GPIO_InitStruct.Pull = GPIO_PULLDOWN;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_MEDIUM;
  HAL_GPIO_Init(GPIOD, &GPIO_InitStruct);

  /*Configure GPIO pins : PCPin PCPin */
  GPIO_InitStruct.Pin = KEY_LINE2_Pin|KEY_LINE1_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_OD;
  GPIO_InitStruct.Pull = GPIO_PULLDOWN;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_MEDIUM;
  HAL_GPIO_Init(GPIOC, &GPIO_InitStruct);
}
