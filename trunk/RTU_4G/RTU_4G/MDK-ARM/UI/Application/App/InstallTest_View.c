#include "Application/GUI/gui.h"

static  void INSTALL_TEST_VIEW_Scanning(void *arg);
static void INSTALL_TEST_VIEW_Run(int argc,char *argv[]);
static SCREEN_TypeDef INSTALL_TEST_SCREEN_INFO={
	.state=STATE_IDLE,	
	.text_content[0].content="  摄像头测试",
	.text_content[1].content="  中心连接测试",
	.text_content[2].content="  北斗测试",
	.text_content[3].content="  测试报",
	.screen_name[0]="CameraTest_VIEW_ID",
	.screen_name[1]="CentralConnectionTest_VIEW_ID",
	.screen_name[2]="BeiDouTest_VIEW_ID",
	.screen_name[3]="MessageTest_VIEW_ID",
	.screen_total_num=4,
	.focus_point=0,
	.self_name="InstallTest_VIEW_ID",
};
/********************************************************************
 *@bref home 界面的初始化
 *     
 *@ret 
***********************************************************************/
void INSTALL_TEST_VIEW_Init(void)
{
	USER_GUI_MANAGER[INSTALL_TEST_VIEW_ID].RunProcess=INSTALL_TEST_VIEW_Run;
	USER_GUI_MANAGER[INSTALL_TEST_VIEW_ID].RunInit=INSTALL_TEST_VIEW_Scanning;
	USER_GUI_MANAGER[INSTALL_TEST_VIEW_ID].screen_info=&INSTALL_TEST_SCREEN_INFO;
}
/********************************************************************
 *@bref 界面运行函数,处理接收的消息
 *     
 *@ret 
***********************************************************************/
void INSTALL_TEST_VIEW_Run(int argc,char *argv[])
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
//		GUI_CurrentScreenRefresh();//如果有实时数据的话，刷新函数//处理消息
	}
}
/********************************************************************
 *@bref //lcd驱动界面初始化
 *     
 *@ret 
***********************************************************************/
 void INSTALL_TEST_VIEW_Scanning(void *arg)
{
	switch((uint8_t)(arg))
	{
		case 0:
				LCD_ClearScreen();
				LCD_DisString(FONT_15x16,1,1,(uint8_t*)INSTALL_TEST_SCREEN_INFO.text_content[0].content);
				LCD_DisString(FONT_15x16,1,3,(uint8_t*)INSTALL_TEST_SCREEN_INFO.text_content[1].content);
				LCD_DisString(FONT_15x16,1,5,(uint8_t*)INSTALL_TEST_SCREEN_INFO.text_content[2].content);
				LCD_DisString(FONT_15x16,1,7,(uint8_t*)INSTALL_TEST_SCREEN_INFO.text_content[3].content);
		break;
	
		default:
			break;
	}
	
	
}

