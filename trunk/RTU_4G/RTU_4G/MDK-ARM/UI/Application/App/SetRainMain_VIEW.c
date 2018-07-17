#include "Application/GUI/gui.h"
static  void SET_RAIN_MAIN_VIEW_Scanning(void *arg);
static void SET_RAIN_MAIN_VIEW_Run(int argc,char *argv[]);
struct RainVal SET_RAIN_VAL={
	.val=0xffff
};
static SCREEN_TypeDef SET_RAIN_MAIN_SCREEN_INFO={
	.state=STATE_IDLE,	
	.text_content[0].content="  设置上报雨量值：%2.1f",
	.text_content[1].content="  确认上报",
	.screen_name[0]="SetRainValue_VIEW_ID",
	.screen_name[1]="Upload_Manual_Data_VIEW_ID",
	.screen_total_num=2,
	.focus_point=0,
	.self_name="SetRainMain_VIEW_ID",
};
/********************************************************************
 *@bref home 界面的初始化
 *     
 *@ret 
***********************************************************************/
void SET_RAIN_MAIN_VIEW_Init(void)
{
	USER_GUI_MANAGER[SET_RAIN_MAIN_VIEW_ID].RunProcess=SET_RAIN_MAIN_VIEW_Run;
	USER_GUI_MANAGER[SET_RAIN_MAIN_VIEW_ID].RunInit=SET_RAIN_MAIN_VIEW_Scanning;
	USER_GUI_MANAGER[SET_RAIN_MAIN_VIEW_ID].screen_info=&SET_RAIN_MAIN_SCREEN_INFO;
}
/********************************************************************
 *@bref 界面运行函数,处理接收的消息
 *     
 *@ret 
***********************************************************************/
void SET_RAIN_MAIN_VIEW_Run(int argc,char *argv[])
{	
	void* val=0;
	OS_MSG_SIZE get_size;
	OS_MSG_TYPE OS_MSG_TYPE;
	val= GUI_GetMsgProcess(Template_KeySpecialEffects,&OS_MSG_TYPE,&get_size);
	if(IS_MSG_ID(OS_MSG_TYPE,KEY_GET_VAL_ID))
	{
		switch((char)(char*)val)
		{
			case KEY_ENTER://菜单按键				
					GUI_PUSH(POINT_GUI_CURRENT_VIEW->screen_info->screen_name[POINT_GUI_CURRENT_VIEW->screen_info->focus_point]);//进入配置界面
			break;
			case KEY_ESC://返回按键
					SET_RAIN_VAL.val=0xffff;//复位子窗口中的使用变量
					GUI_POP();//退出前处理
			break;
			default:
				
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
 void SET_RAIN_MAIN_VIEW_Scanning(void *arg)
{
	switch((uint8_t)(arg))
	{
		case 0:
				LCD_ClearScreen();
				if(SET_RAIN_VAL.val!=0xffff)
					LCD_DisString(FONT_15x16,1,3,(uint8_t*)SET_RAIN_MAIN_SCREEN_INFO.text_content[0].content,SET_RAIN_VAL.val);
				else 
					LCD_DisString(FONT_15x16,1,3,(uint8_t*)SET_RAIN_MAIN_SCREEN_INFO.text_content[0].content,0);
				
				LCD_DisString(FONT_15x16,1,5,(uint8_t*)SET_RAIN_MAIN_SCREEN_INFO.text_content[1].content);
		break;
	
		default:
			break;
	}
	
	
}

