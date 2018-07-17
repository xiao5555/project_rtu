#include "Application/GUI/gui.h"
static  void CLEAR_HISTORICAL_VIEW_Scanning(void *arg);
static void CLEAR_HISTORICAL_VIEW_Run(int argc,char *argv[]);
static SCREEN_TypeDef CLEAR_HISTORICAL_SCREEN_INFO={
	.state=STATE_IDLE,	
	.text_content[0].content="ȷ�������ʷ����???",
	.text_content[1].content=" Eec   Enter",
	.screen_total_num=0,
	.focus_point=0,
	.self_name="ClearHistorical_VIEW_ID",
};
/********************************************************************
 *@bref home ����ĳ�ʼ��
 *     
 *@ret 
***********************************************************************/
void CLEAR_HISTORICAL_VIEW_Init(void)
{
	USER_GUI_MANAGER[CLEAR_HISTORICAL_VIEW_ID].RunProcess=CLEAR_HISTORICAL_VIEW_Run;
	USER_GUI_MANAGER[CLEAR_HISTORICAL_VIEW_ID].RunInit=CLEAR_HISTORICAL_VIEW_Scanning;
	USER_GUI_MANAGER[CLEAR_HISTORICAL_VIEW_ID].screen_info=&CLEAR_HISTORICAL_SCREEN_INFO;
}
/********************************************************************
 *@bref �������к���,������յ���Ϣ
 *     
 *@ret 
***********************************************************************/
void CLEAR_HISTORICAL_VIEW_Run(int argc,char *argv[])
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
				GUI_POP();//�˳�ǰ����
//					GUI_PUSH(POINT_GUI_CURRENT_VIEW->screen_info->screen_name[POINT_GUI_CURRENT_VIEW->screen_info->focus_point]);//�������ý���
			break;
			case KEY_ESC://���ذ���
					GUI_POP();//�˳�ǰ����
			break;
			default:			
				
			break;
		}
	}else
	{
//		GUI_CurrentScreenRefresh();//�����ʵʱ���ݵĻ���ˢ�º���//������Ϣ
	}
}
/********************************************************************
 *@bref //lcd���������ʼ��
 *     
 *@ret 
***********************************************************************/
 void CLEAR_HISTORICAL_VIEW_Scanning(void *arg)
{
	switch((uint8_t)(arg))
	{
		case 0:
				LCD_ClearScreen();
				LCD_DisString(FONT_15x16,1,1,(uint8_t*)CLEAR_HISTORICAL_SCREEN_INFO.text_content[0].content);
				LCD_DisString(FONT_15x16,1,3,(uint8_t*)CLEAR_HISTORICAL_SCREEN_INFO.text_content[1].content);
		break;
	
		default:
			break;
	}
	
	
}

