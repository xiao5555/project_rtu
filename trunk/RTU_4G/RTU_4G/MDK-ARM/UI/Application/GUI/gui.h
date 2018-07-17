#ifndef _GUI_H_
#define _GUI_H_
#include <stdint.h>
#include <string.h>
#include <stdio.h>
#include "Middle/Inc/config.h"
#include "Middle/Inc/middle.h"
#include "Middle/Inc/InputBox.h"
#include "DRIVER/LcdApi.h"
#include "Middle/Inc/event.h"
#include "Application/Inc/Main_View.h"
#include "Application/Inc/SysRest_View.h"
#include "Application/Inc/Config_View.h"
#include "Application/Inc/ManualSet_View.h"
#include "Application/Inc/SetRainMain_VIEW.h"
#include "Application/Inc/SetRainValue_VIEW.h"
#include "Application/Inc/SetWaterMain_VIEW.h"
#include "Application/Inc/Hint_View.h"
#include "Application/Inc/UploadManualData_View.h"
#include "Application/Inc/ParameterSet_View.h" 
#include "Application/Inc/InstallTest_View.h" 
#include "Application/Inc/ClearHistorical_View.h" 
#include "Application/Inc/VersionView_View.h" 
#include "LIB/PictureComponent/PictureComponent.h"
#include "Inc/key.h"
#include "PrivateMsg/PrivateMsg.h"


#define Debug(fmt,...) 
#define GUI_SCREEN_NUM   USER_CONFIG_MAX_GUI_NUM  
#define DEFAULT_FONT_SIZE  FONT_15x16
/***************************************************************
	��Ϣ���ͣ�32λ��
	��24λ��Ϊ����ID ��8λ��Ӧ����Ϣ�¼����ڽ������¼��Ͳ���ע��˳�����
************************************************************/
typedef uint32_t MSG_Type;
#define KEY_GET_VAL_ID     20
#define DEVICE_VAL_ID      21
#define IS_MSG_ID(val,master)	((((val>>8)-1)==master)?1:0)
#define SET_MSG_ID(master,sub)  (((master+1)<<8)|sub)
#define GET_SCREEN_ID(master)   ((master-1)>>8)
#define GET_SUB_ID(master)      ((master&0xff)-1)
#define MSG_HOUR_RAIN  SET_MSG_ID(MAIN_VIEW_ID,1)//���ܴ���bug����ö�ٵ��������
#define MSG_DAY_RAIN   SET_MSG_ID(MAIN_VIEW_ID,2)
#define MSG_WATER      SET_MSG_ID(MAIN_VIEW_ID,3)
#define MEG_SIM_RSISS  SET_MSG_ID(MAIN_VIEW_ID,4)
#define MSG_RTC_UPDATE SET_MSG_ID(MAIN_VIEW_ID,5)
#define MSG_KEY_VALUE  SET_MSG_ID(KEY_GET_VAL_ID,1)	


/************************GUI to user********************************/
#define MSG_DEVICE_SET_RAIN   SET_MSG_ID(DEVICE_VAL_ID,1)

//typedef  enum VALUE{
//	VALUE_CUSTOM,
//	VALUE_ENUM
//}VALUE_TYPE_ENUM;
typedef struct PARAMETER{
//	VALUE_TYPE_ENUM value_type;
	uint8_t x;
	uint8_t y;
	uint8_t value_len;
	uint32_t *value;
	uint8_t IsRefresh;
}PARAMETER_TypeDef;//parameter
typedef enum SCREEN_ENUM{
	STATE_IDLE,//˯��
	STATE_INIT,//��ʼ��
	STATE_RUN//����
}SCREEN_ENUM_TypeDef;
typedef struct IMAGE{
	uint8_t x_start;
	uint8_t y_start;
	uint8_t width;
	uint8_t height;
	uint8_t *p_image;
}IMAGE_TypeDef;
typedef struct TEXT{
	char *content;
//	uint8_t x;
//	uint8_t y;
//	uint8_t font_size;
}TEXT_TypeDef;

typedef struct _VALUE{
	uint8_t type;
	uint8_t max_num;
	uint8_t *data;
	uint8_t (*checkChar)(char c);
	uint32_t true_data; 
}VALUE_TypeDef;
/****************************************
������Ϣ
*****************************************/
typedef struct SCREEN{
	SCREEN_ENUM_TypeDef state;//����״̬
	TEXT_TypeDef text_content[10];//������������Ϣ
	IMAGE_TypeDef image_content[4];//������ͼƬ����
//	uint8_t image_total_num;//ͼƬ����
	char *screen_name[10];//�������ӽ�������
	char *self_name;//�����������
	VALUE_TypeDef val;//����
	uint8_t screen_total_num;//�������ӽ�������
	uint8_t focus_point;//��ǰ����λ��
}SCREEN_TypeDef;

/****************************************
�������
*****************************************/
typedef struct GUI{
	void(*RunProcess)(int argc,char *argv[]);
	void(*RunInit)(void *arg);
	SCREEN_TypeDef *screen_info;
	uint8_t RequestRefresh;//�Ƿ���Ҫˢ��
}GUI_TypeDef;
extern  GUI_TypeDef *GUI_TAB_VIEW[GUI_SCREEN_NUM];//���ڼ�¼�����л�
extern GUI_TypeDef *POINT_GUI_CURRENT_VIEW;
extern  GUI_TypeDef USER_GUI_MANAGER[GUI_SCREEN_NUM];//���������
/********************************************** Private function**********************************************************/
void PUSH_ScreenInfo(char *name);
void POP_ScreenInfo(void);
/**********************************************External function**********************************************************/
void APP_GUI_Init(void);
void APP_GUI_Exc(void* arg);
void GUI_RequestRefresh(GUI_TypeDef *ptr);
void GUI_CurrentScreenRefresh(void);
#define GUI_PUSH(Name_View) {PUSH_ScreenInfo(Name_View); return;}
#define GUI_POP()     		{POP_ScreenInfo(); return;}
/**********************************************End function**********************************************************/

#endif//_GUI_H_

