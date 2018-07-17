#include "Application/GUI/gui.h"

static  void VERSION_VIEW_Scanning(void *arg);
static void VERSION_VIEW_Run(int argc,char *argv[]);
static SCREEN_TypeDef VERSION_SCREEN_INFO={
	.state=STATE_IDLE,	
	.text_content[0].content="VER\r\nyu",
	.self_name="VersionView_VIEW_ID",
};
/********************************************************************
 *@bref home ����ĳ�ʼ��
 *     
 *@ret 
***********************************************************************/
void VERSION_VIEW_Init(void)
{
	USER_GUI_MANAGER[VERSION_VIEW_ID].RunProcess=VERSION_VIEW_Run;
	USER_GUI_MANAGER[VERSION_VIEW_ID].RunInit=VERSION_VIEW_Scanning;
	USER_GUI_MANAGER[VERSION_VIEW_ID].screen_info=&VERSION_SCREEN_INFO;
}
/********************************************************************
 *@bref �������к���,������յ���Ϣ
 *     
 *@ret 
***********************************************************************/
void VERSION_VIEW_Run(int argc,char *argv[])
{
	void* val=0;
	OS_MSG_SIZE get_size;
	OS_MSG_TYPE OS_MSG_TYPE;
	val= GUI_GetMsgProcess(Template_KeySpecialEffects,&OS_MSG_TYPE,&get_size);
	if(IS_MSG_ID(OS_MSG_TYPE,KEY_GET_VAL_ID))
	{
		switch((char)(char*)val)
		{
			case KEY_ENTER://�˵�����
					GUI_PUSH(POINT_GUI_CURRENT_VIEW->screen_info->screen_name[POINT_GUI_CURRENT_VIEW->screen_info->focus_point]);//�������ý���
					break;
			case KEY_ESC://���ذ���
					GUI_POP();//�˳�ǰ����
			break;
			default:			
				
			break;
		}
	}else
	{

	}
}
/********************************************************************
 *@bref //lcd���������ʼ��
 *     
 *@ret 
***********************************************************************/
 void VERSION_VIEW_Scanning(void *arg)
{
	switch((uint8_t)(arg))
	{
		case 0:
				LCD_ClearScreen();
				LCD_DisString(FONT_15x16,1,1,(uint8_t*)VERSION_SCREEN_INFO.text_content[0].content);
//				LCD_DisString(FONT_15x16,1,3,(uint8_t*)VERSION_SCREEN_INFO.text_content[1].content);
//				LCD_DisString(FONT_15x16,1,5,(uint8_t*)VERSION_SCREEN_INFO.text_content[2].content);
		break;

		default:
			break;
	}
}

