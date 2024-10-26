/*
 * page_setting.h
 *
 *  Created on: 2023��3��5��
 *      Author: ֣��
 */

#ifndef _SETTING_H_
#define _SETTING_H_

#include "zf_common_headfile.h"
#include "mymenu.h"


extern int8 line_number;
extern uint8 line_number_max;

//*******ҳ���м������*******//

extern int8 main_line_number;
extern int8 navigation_line_number;
extern int8 Camera_line_number;
//*******ҳ���м������*******//

extern int8 row_number;
extern uint8 row_number_max;

extern float increment1[4];
extern float increment2[4];
extern float increment3[3];
extern float mtspeedlevel[5];

//*******ҳ���*******//

void main_page_process(int Event_Code);
void Start_page_process(int Event_Code);
void Camera_page_process(int Event_Code);
void navigation_page_process(int Event_Code);

//*******ҳ���*******//


void Key_Event(void);

#endif /* CODE_MENU_PAGE_SETTING_H_ */
