/*
 * page_setting.c
 *
 *  Created on: 2023��3��5��
 *      Author: ֣��
 */

#include "page_setting.h"


uint8 line_number_max;
uint8 row_number_max;

int8 line_number=1;
int8 row_number=1;

//*******ҳ���м������*******//
int8 main_line_number = 1;
int8 navigation_line_number = 1;
int8 Camera_line_number = 1;
//*******ҳ���м������*******//

float increment1[4]={0,1,10,100};
float increment2[4]={0,0.010000001,0.1,1};
float increment3[3]={1,5,10};
float mtspeedlevel[5]={1,5,10,15,20};

