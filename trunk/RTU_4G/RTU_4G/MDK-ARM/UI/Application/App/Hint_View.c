#include "Application/GUI/gui.h"
static  void HINT_VIEW_Scanning(void *arg);
static void HINT_VIEW_Run(int argc,char *argv[]);

static SCREEN_TypeDef HINT_SCREEN_INFO={
	.self_name="Hint_View_ID",
};
/********************************************************************
 *@bref home ����ĳ�ʼ��
 *     
 *@ret 
***********************************************************************/
void HINT_VIEW_Init(void)
{
	USER_GUI_MANAGER[HINT_VIEW_ID].RunProcess=HINT_VIEW_Run;
	USER_GUI_MANAGER[HINT_VIEW_ID].RunInit=HINT_VIEW_Scanning;
	USER_GUI_MANAGER[HINT_VIEW_ID].screen_info=&HINT_SCREEN_INFO;
}

/********************************************************************
 *@bref �������к���,������յ���Ϣ
 *     
 *@ret 
***********************************************************************/
void HINT_VIEW_Run(int argc,char *argv[])
{
	void* val=0;
	OS_MSG_SIZE get_size;
	OS_MSG_TYPE OS_MSG_TYPE;
	val= GUI_GetMsgProcess(0,&OS_MSG_TYPE,&get_size);
	if(IS_MSG_ID(OS_MSG_TYPE,KEY_GET_VAL_ID))
	{
		switch((char)(char*)val)
		{
			default:
					GUI_POP();
			break;
		}
	}else
	{
		//������Ϣ
	}
}
/********************************************************************
 *@bref //lcd���������ʼ������ʼ������0
 *     arg ��ʾ���ǵڼ�ҳ
 *@ret 
***********************************************************************/
 void HINT_VIEW_Scanning(void *arg)
{
	
	switch((uint8_t)(arg))
	{
		case 0:
				LCD_ClearScreen();
				LCD_DisString(FONT_15x16,1,4,(uint8_t*)HINT_SCREEN_INFO.text_content[0].content);
		break;
		default:
			break;		
	}
	
}

