#include "Application/GUI/gui.h"
static  void SET_RAIN_VALUE_VIEW_Scanning(void *arg);
static void SET_RAIN_VALUE_VIEW_Run(int argc,char *argv[]);
static uint8_t InPut_Is_OK(char *p_str);
static InputBox_TypeDef *p_txt;
static SCREEN_TypeDef SET_RAIN_VALUE_SCREEN_INFO={
	.state=STATE_IDLE,	
	.text_content[0].content="    雨量置数",
	.text_content[1].content="    单位: (mm)",
	.text_content[2].content="    (0-99999.9)",
	.text_content[3].content="请输入:",
	.screen_total_num=0,
	.focus_point=0,
	.self_name="SetRainValue_VIEW_ID",
};
/********************************************************************
 *@bref home 界面的初始化
 *     
 *@ret 
***********************************************************************/
void SET_RAIN_VALUE_VIEW_Init(void)
{
	USER_GUI_MANAGER[SET_RAIN_VALUE_VIEW_ID].RunProcess=SET_RAIN_VALUE_VIEW_Run;
	USER_GUI_MANAGER[SET_RAIN_VALUE_VIEW_ID].RunInit=SET_RAIN_VALUE_VIEW_Scanning;
	USER_GUI_MANAGER[SET_RAIN_VALUE_VIEW_ID].screen_info=&SET_RAIN_VALUE_SCREEN_INFO;
}
/********************************************************************
 *@bref 界面运行函数,处理接收的消息
 *     
 *@ret 
***********************************************************************/
void SET_RAIN_VALUE_VIEW_Run(int argc,char *argv[])
{	
	void* val=0;
	OS_MSG_SIZE get_size;
	OS_MSG_TYPE OS_MSG_TYPE;
	float value=0;
	val= GUI_GetMsgProcess(0,&OS_MSG_TYPE,&get_size);
	if(IS_MSG_ID(OS_MSG_TYPE,KEY_GET_VAL_ID))
	{
		switch((char)(char*)val)
		{
			case KEY_UP:
			case KEY_DOWN:
			case KEY_MENU:
					break;
			case KEY_ESC://返回按键
					if(p_txt->Del()==1)
					{
						GUI_POP();//退出前处理
					}
			break;
			case KEY_ENTER:
						if(InPut_Is_OK(p_txt->GetString()))
						{
								Debug("输入格式出错\r\n");	
								USER_GUI_MANAGER[HINT_VIEW_ID].screen_info->text_content[0].content="   输入格式出错!!!";
						  	    GUI_PUSH("Hint_View_ID");
						}else{
							sscanf(p_txt->GetString(),"%f",&value);
							SET_RAIN_VAL.val=value;
							GUI_POP();//退出前处理
						}
						
			break;
			default:			
						p_txt->StoreCharAndDis((char)val);
			break;
		}
	}else
	{
		GUI_CurrentScreenRefresh();//如果有实时数据的话，刷新函数//处理消息
	}
}
/********************************************************************
 *@bref //lcd驱动界面初始化
 *     
 *@ret 
***********************************************************************/
 void SET_RAIN_VALUE_VIEW_Scanning(void *arg)
{
	p_txt=CreateInputBox(7,70,FONT_15x16,7);//创建文本输入框
	switch((uint8_t)arg)
	{
		case 0:
				LCD_ClearScreen();
				LCD_DisString(FONT_15x16,1,1,(uint8_t*)SET_RAIN_VALUE_SCREEN_INFO.text_content[0].content);
				LCD_DisString(FONT_15x16,1,3,(uint8_t*)SET_RAIN_VALUE_SCREEN_INFO.text_content[1].content);
				LCD_DisString(FONT_15x16,1,5,(uint8_t*)SET_RAIN_VALUE_SCREEN_INFO.text_content[2].content);
				LCD_DisString(FONT_15x16,1,7,(uint8_t*)SET_RAIN_VALUE_SCREEN_INFO.text_content[3].content);
		break;
	
		default:
			break;
	}
}

uint8_t InPut_Is_OK(char *p_str)
{
	if(strstr(p_str,"+"))
		return 1;
	if(strstr(p_str,"-"))
		return 1;
	if(strstr(p_str,"*"))
		return 1;
	if(strstr(p_str,"#"))
		return 1;
	while(*p_str)
	{
		if((*p_str>='a')&&((*p_str<='z')))
			return 1;
		p_str++;
	}
	return 0;
}

