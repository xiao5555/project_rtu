#include "Application/GUI/gui.h"
static  void SET_RAIN_MAIN_VIEW_Scanning(void *arg);
static void SET_RAIN_MAIN_VIEW_Run(int argc,char *argv[]);
struct RainVal SET_RAIN_VAL={
	.val=0xffff
};
static SCREEN_TypeDef SET_RAIN_MAIN_SCREEN_INFO={
	.state=STATE_IDLE,	
	.text_content[0].content="  �����ϱ�����ֵ��%2.1f",
	.text_content[1].content="  ȷ���ϱ�",
	.screen_name[0]="SetRainValue_VIEW_ID",
	.screen_name[1]="Upload_Manual_Data_VIEW_ID",
	.screen_total_num=2,
	.focus_point=0,
	.self_name="SetRainMain_VIEW_ID",
};
/********************************************************************
 *@bref home ����ĳ�ʼ��
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
 *@bref �������к���,������յ���Ϣ
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
			case KEY_ENTER://�˵�����				
					GUI_PUSH(POINT_GUI_CURRENT_VIEW->screen_info->screen_name[POINT_GUI_CURRENT_VIEW->screen_info->focus_point]);//�������ý���
			break;
			case KEY_ESC://���ذ���
					SET_RAIN_VAL.val=0xffff;//��λ�Ӵ����е�ʹ�ñ���
					GUI_POP();//�˳�ǰ����
			break;
			default:
				
			break;
		}
	}else
	{
		GUI_CurrentScreenRefresh();//�����ʵʱ���ݵĻ���ˢ�º���//������Ϣ
	}
}
/********************************************************************
 *@bref //lcd���������ʼ��
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

