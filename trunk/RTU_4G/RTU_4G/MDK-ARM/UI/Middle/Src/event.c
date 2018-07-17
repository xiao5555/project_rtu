#include "Application/GUI/gui.h" 
#define FULL_SCREEN_LINE_NUM 4
/********************************************************************
 *@bref 按键触发时的模板特效处理
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
								Debug("全屏向上刷新一页，焦点指向本页首个\r\n");
								POINT_GUI_CURRENT_VIEW->RunInit((void*)((POINT_GUI_CURRENT_VIEW->screen_info->focus_point-1)/FULL_SCREEN_LINE_NUM));
							}else
							{
								Debug("只是刷新按键\r\n");		
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
									Debug("刷新下一页,焦点指向本页首个\r\n");
									POINT_GUI_CURRENT_VIEW->RunInit((void*)(POINT_GUI_CURRENT_VIEW->screen_info->focus_point/FULL_SCREEN_LINE_NUM));
								}else
								{
									Debug("只是刷新按键\r\n");
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

