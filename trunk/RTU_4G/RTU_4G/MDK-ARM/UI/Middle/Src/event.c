#include "Application/GUI/gui.h" 
#define FULL_SCREEN_LINE_NUM 4
/********************************************************************
 *@bref ��������ʱ��ģ����Ч����
 *     	esc->@
 *		enter->^
 *		menu->$
 *		up->%
 *		down->&
 *@ret 
***********************************************************************/
void Template_KeySpecialEffects(char val)
{
	if(val)
	{
		switch(val)
		{
			case KEY_UP://up
						if(POINT_GUI_CURRENT_VIEW->screen_info->focus_point)
						{								
							if((POINT_GUI_CURRENT_VIEW->screen_info->focus_point%FULL_SCREEN_LINE_NUM)==0)
							{
								Debug("ȫ������ˢ��һҳ������ָ��ҳ�׸�\r\n");
								POINT_GUI_CURRENT_VIEW->RunInit((void*)((POINT_GUI_CURRENT_VIEW->screen_info->focus_point-1)/FULL_SCREEN_LINE_NUM));
							}else
							{
								Debug("ֻ��ˢ�°���\r\n");		
								LCD_ClearRectangle(0,176,7,192);
							}
							POINT_GUI_CURRENT_VIEW->screen_info->focus_point--;
							LCD_DisString(FONT_15x16,176,(POINT_GUI_CURRENT_VIEW->screen_info->focus_point%FULL_SCREEN_LINE_NUM)*2+1,(uint8_t*)"*");	
						}
				break;
			case KEY_DOWN://down
							if(POINT_GUI_CURRENT_VIEW->screen_info->focus_point<POINT_GUI_CURRENT_VIEW->screen_info->screen_total_num-1)
							{
								POINT_GUI_CURRENT_VIEW->screen_info->focus_point++;
								if((POINT_GUI_CURRENT_VIEW->screen_info->focus_point%FULL_SCREEN_LINE_NUM)==0)
								{
									Debug("ˢ����һҳ,����ָ��ҳ�׸�\r\n");
									POINT_GUI_CURRENT_VIEW->RunInit((void*)(POINT_GUI_CURRENT_VIEW->screen_info->focus_point/FULL_SCREEN_LINE_NUM));
								}else
								{
									Debug("ֻ��ˢ�°���\r\n");
									LCD_ClearRectangle(0,176,7,192);
								}
								LCD_DisString(FONT_15x16,176,(POINT_GUI_CURRENT_VIEW->screen_info->focus_point%FULL_SCREEN_LINE_NUM)*2+1,(uint8_t*)"*");
							}
				break;			
			default:
				break;			
		}
	}
}

