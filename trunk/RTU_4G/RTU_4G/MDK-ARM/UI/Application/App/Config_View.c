#include "Application/GUI/gui.h"
#define CONFIG_BASE_OFFSET_X  0
#define CONFIG_BASE_OFFSET_Y  0
static  void CONFIG_VIEW_Scanning(void *arg);
static void CONFIG_VIEW_Run(int argc,char *argv[]);
static SCREEN_TypeDef CONFIG_SCREEN_INFO={
	.state=STATE_IDLE,	
	.text_content[0].content="人工置数",
//	.text_content[0].font_size=DEFAULT_FONT_SIZE,
//	.text_content[0].x=CONFIG_BASE_OFFSET_X,
//	.text_content[0].y=CONFIG_BASE_OFFSET_Y+0*DEFAULT_FONT_SIZE,
	.text_content[1].content="参数设置",
//	.text_content[1].font_size=DEFAULT_FONT_SIZE,
//	.text_content[1].x=CONFIG_BASE_OFFSET_X,
//	.text_content[1].y=CONFIG_BASE_OFFSET_Y+1*DEFAULT_FONT_SIZE,
	.text_content[2].content="安装测试",
//	.text_content[2].font_size=DEFAULT_FONT_SIZE,
//	.text_content[2].x=CONFIG_BASE_OFFSET_X,
//	.text_content[2].y=CONFIG_BASE_OFFSET_Y+2*DEFAULT_FONT_SIZE,
	.text_content[3].content="清除历史数据",
//	.text_content[3].font_size=DEFAULT_FONT_SIZE,
//	.text_content[3].x=CONFIG_BASE_OFFSET_X,
//	.text_content[3].y=CONFIG_BASE_OFFSET_Y+3*DEFAULT_FONT_SIZE,
	.text_content[4].content="版本查看",
//	.text_content[4].font_size=DEFAULT_FONT_SIZE,
//	.text_content[4].x=CONFIG_BASE_OFFSET_X,
//	.text_content[4].y=CONFIG_BASE_OFFSET_Y+4*DEFAULT_FONT_SIZE,
	.text_content[5].content="恢复出厂",
//	.text_content[5].font_size=DEFAULT_FONT_SIZE,
//	.text_content[5].x=CONFIG_BASE_OFFSET_X,
//	.text_content[5].y=CONFIG_BASE_OFFSET_Y+5*DEFAULT_FONT_SIZE,
	.screen_name[0]="ManualSet_VIEW_ID",
	.screen_name[1]="ParameterSet_VIEW_ID",
	.screen_name[2]="InstallTest_VIEW_ID",
	.screen_name[3]="ClearHistorical_VIEW_ID",
	.screen_name[4]="VersionView_VIEW_ID",
	.screen_name[5]="RestoreFactory_VIEW_ID",
	.screen_total_num=6,
	.self_name="Config_View_ID",
	.focus_point=0,
};
/********************************************************************
 *@bref home 界面的初始化
 *     
 *@ret 
***********************************************************************/
void CONFIG_VIEW_Init(void)
{
	USER_GUI_MANAGER[CONFIG_VIEW_ID].RunProcess=CONFIG_VIEW_Run;
	USER_GUI_MANAGER[CONFIG_VIEW_ID].RunInit=CONFIG_VIEW_Scanning;
	USER_GUI_MANAGER[CONFIG_VIEW_ID].screen_info=&CONFIG_SCREEN_INFO;
}
/********************************************************************
 *@bref 界面运行函数,处理接收的消息
 *     
 *@ret 
***********************************************************************/
void CONFIG_VIEW_Run(int argc,char *argv[])
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
					GUI_POP();//退出前处理
			break;
			default:			
				
			break;
		}
	}else
	{

	}
}
/********************************************************************
 *@bref //lcd驱动界面初始化
 *     
 *@ret 
***********************************************************************/
 void CONFIG_VIEW_Scanning(void *arg)
{
	switch((uint8_t)(arg))
	{
		case 0:
				LCD_ClearScreen();
				LCD_DisString(FONT_15x16,1,1,(uint8_t*)CONFIG_SCREEN_INFO.text_content[0].content);
				LCD_DisString(FONT_15x16,1,3,(uint8_t*)CONFIG_SCREEN_INFO.text_content[1].content);
				LCD_DisString(FONT_15x16,1,5,(uint8_t*)CONFIG_SCREEN_INFO.text_content[2].content);
				LCD_DisString(FONT_15x16,1,7,(uint8_t*)CONFIG_SCREEN_INFO.text_content[3].content);
		break;
		case 1:
				LCD_ClearScreen();
				LCD_DisString(FONT_15x16,1,1,(uint8_t*)CONFIG_SCREEN_INFO.text_content[4].content);
				LCD_DisString(FONT_15x16,1,3,(uint8_t*)CONFIG_SCREEN_INFO.text_content[5].content);
		break;
		default:
			break;
	}
	
	
}

