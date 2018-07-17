#include "Application/GUI/gui.h"
#include "PrivateTimer/PrivateTimer.h"

 GUI_TypeDef *GUI_TAB_VIEW[GUI_SCREEN_NUM]={0};//���ڼ�¼�����л�
 GUI_TypeDef *POINT_GUI_CURRENT_VIEW=NULL;//��ǰ��ָ��Ľ���
 GUI_TypeDef USER_GUI_MANAGER[GUI_SCREEN_NUM]={0};//���������
 static GUI_TypeDef * SearchScreenByName(char *name);

/********************************************************************
 *@bref 
 *     
 *@ret 
***********************************************************************/
void APP_GUI_Init(void)
{
	GUI_MsgInit();
	MAIN_VIEW_Init();
	CONFIG_VIEW_Init();
	MANUAL_SET_VIEW_Init();
	SET_RAIN_MAIN_VIEW_Init();
	SET_RAIN_VALUE_VIEW_Init();
	HINT_VIEW_Init();
	UPLOAD_MANUAL_VIEW_Init();
	PARAMETER_SET_VIEW_Init();
	INSTALL_TEST_VIEW_Init();
	CLEAR_HISTORICAL_VIEW_Init();
	VERSION_VIEW_Init();
	POINT_GUI_CURRENT_VIEW=&USER_GUI_MANAGER[MAIN_VIEW_ID];//���ü�¼Ĭ��ֵ
	CUSTOM_TimerCreat(APP_GUI_Exc,0,10,20);
}

/********************************************************************
 *@bref ���洦�����������ڶ�ʱ���е���
 * 
 *@ret 
***********************************************************************/
void APP_GUI_Exc(void*arg)
{
	switch(POINT_GUI_CURRENT_VIEW->screen_info->state)
	{
		case STATE_IDLE:
			
		break;
		case STATE_INIT:
				POINT_GUI_CURRENT_VIEW->RunInit(0);
				POINT_GUI_CURRENT_VIEW->screen_info->state=STATE_RUN;
		break;
		case STATE_RUN:
				POINT_GUI_CURRENT_VIEW->RunProcess(0,0);
		break;
		default:
			
		break;
	}
}
/********************************************************************
 *@bref  POP ���ϸ�����
 *     
 *@ret 
***********************************************************************/
 void POP_ScreenInfo(void)
  {
	  uint8_t count=0;
	  for(;GUI_TAB_VIEW[count];count++);//������߼�¼
	  
	  POINT_GUI_CURRENT_VIEW->screen_info->focus_point=0;//����λ�����
	  POINT_GUI_CURRENT_VIEW->screen_info->state=STATE_IDLE;//˯��
	  POINT_GUI_CURRENT_VIEW=GUI_TAB_VIEW[count-1];
	  POINT_GUI_CURRENT_VIEW->screen_info->state=STATE_INIT;//����
	  GUI_TAB_VIEW[count-1]=0;
  }
/********************************************************************
   *@bref PUSH�ý���
   *     
   *@ret 
***********************************************************************/
  void PUSH_ScreenInfo(char *name)
  {
	  POINT_GUI_CURRENT_VIEW->screen_info->focus_point=0;//����λ�����
	  POINT_GUI_CURRENT_VIEW->screen_info->state=STATE_IDLE;
	  GUI_TypeDef *  val=SearchScreenByName(name); 
	  if(val)
	  {
		  uint8_t count=0;
		  for(;GUI_TAB_VIEW[count];count++);//������߼�¼
		  
		  GUI_TAB_VIEW[count]=POINT_GUI_CURRENT_VIEW;//����¼
			val->screen_info->state=STATE_INIT;
			POINT_GUI_CURRENT_VIEW=val;
			
	  }else
	  {		  
		 Debug_P("û�иý��棬�ص�Ĭ�Ͻ���\r\n");
		 USER_GUI_MANAGER[MAIN_VIEW_ID].screen_info->state=STATE_INIT;
		 POINT_GUI_CURRENT_VIEW=&USER_GUI_MANAGER[MAIN_VIEW_ID];//
		  
	  }
  }
/********************************************************************
   *@bref 
   *     
   *@ret 
***********************************************************************/
  static GUI_TypeDef * SearchScreenByName(char *name)
  {
	for(int i=0;i<GUI_SCREEN_NUM;i++)
	  {
		if(strcmp(USER_GUI_MANAGER[i].screen_info->self_name,name)==0)
		{
			return &USER_GUI_MANAGER[i];
		}
	  }
	  return NULL;
  }
/********************************************************************
   *@bref ��������ˢ�º���
   *     
   *@ret 
***********************************************************************/  
void GUI_RequestRefresh(GUI_TypeDef *ptr)
{
	ptr->RequestRefresh=1;
}
/********************************************************************
 *@bref ��ǰ����ˢ�º���
 *     
 *@ret 
***********************************************************************/
void GUI_CurrentScreenRefresh(void)
{
//	if(POINT_GUI_CURRENT_VIEW->RequestRefresh)
//	{
//		POINT_GUI_CURRENT_VIEW->RequestRefresh=0;
//		POINT_GUI_CURRENT_VIEW->RunInit(0);
//		Debug("����ˢ�´���bug����ʱֻˢ�µ�һ������\r\n");
//	}
}
