/*
 * Gyro_page.c
 *
 *  Created on: 2023年3月25日
 *      Author: Dell
 */
#include "zf_common_headfile.h"
#include "mymenu.h"
void image_page_process(int Event_Code)
{

    line_number_max=2;
//    FLAG.showimage = 1;
    if(key_get_state(KEY_1) == KEY_SHORT_PRESS)
    {
        gpio_set_level(Beep,1);
        system_delay_ms(10);
        gpio_set_level(Beep,0);
        key_clear_state(KEY_3);
        line_number--;//高亮选择往下
        pagelimit(&line_number,line_number_max);
    }
    if(key_get_state(KEY_3) == KEY_SHORT_PRESS)
    {
        gpio_set_level(Beep,1);
        system_delay_ms(10);
        gpio_set_level(Beep,0);
        key_clear_state(KEY_1);
        line_number++; //高亮选择往上
        pagelimit(&line_number,line_number_max);
    }
    if(key_get_state(KEY_2) == KEY_SHORT_PRESS)
    {
        gpio_set_level(Beep,1);
        system_delay_ms(10);
        gpio_set_level(Beep,0);
        key_clear_state(KEY_2);
        Set_Menu(&menu, MAIN_PAGE);
//        FLAG.showimage = 0;
        line_number=1;
        ips200_clear();
    }






}


