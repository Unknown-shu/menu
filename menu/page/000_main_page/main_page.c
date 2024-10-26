 /*
 * main_page.c
 *
 *  Created on: 2023年3月5日
 *      Author: 郑旭
 */
#include "MyHeadfile.h"
#include "mymenu.h"

#define line_number main_line_number

void main_page_process(int Event_Code)
{
    line_number_max=3;

   //显示菜单

    ips200_show_chinese(105, 0, 16, chinese16[0], 2, PenColor);

//  1.组合导航
    if(line_number!=1) ips200_show_string_color(0, 18,"START", PenColor);
    else              ips200_show_string_color(0, 18,"START", PenColor_else);
////   2.电机控制
    if(line_number!=2) ips200_show_string_color(0, 18*2,"Value", PenColor);
     else              ips200_show_string_color(0, 18*2,"Value", PenColor_else);
//
    if(line_number!=3) ips200_show_string_color(0, 18*3,"Camera", PenColor);
     else              ips200_show_string_color(0, 18*3,"Camera", PenColor_else);

    if(line_number!=4) ips200_show_string_color(0, 18*4,"", PenColor);
     else              ips200_show_string_color(0, 18*4,"", PenColor_else);

    ips200_show_string_color(0, 18*5,"L:", PenColor_else);
    ips200_show_int(32, 18*5, target_left, 3);
    ips200_show_string_color(0, 18*6,"R:", PenColor_else);
    ips200_show_int(32, 18*6, target_right, 3);

    if(key_get_state(KEY_1) == KEY_SHORT_PRESS)
    {
        gpio_set_level(Beep,1);
        system_delay_ms(10);
        gpio_set_level(Beep,0);
        key_clear_state(KEY_1);
        line_number--;//高亮选择往下
        pagelimit(&line_number,line_number_max);
    }
    if(key_get_state(KEY_3) == KEY_SHORT_PRESS)
    {
        gpio_set_level(Beep,1);
        system_delay_ms(10);
        gpio_set_level(Beep,0);
        key_clear_state(KEY_3);
        line_number++; //高亮选择往上
        pagelimit(&line_number,line_number_max);
    }
    if(key_get_state(KEY_4) == KEY_SHORT_PRESS)
    {
        gpio_set_level(Beep,1);
        system_delay_ms(10);
        gpio_set_level(Beep,0);
        key_clear_state(KEY_4);
        switch(line_number)
           {
               case 1:
                   Set_Menu(&menu, Start_PAGE);
                   ips200_clear();

                   break ;
               case 2:
                   Set_Menu(&menu, NAVIGATION_PAGE);
//                   line_number=1;
                   ips200_clear();
                   break ;
               case 3:
                   Set_Menu(&menu, Camera_PAGE);
//                   line_number=1;
                   ips200_clear();
                   break ;
//               case 4:
//                   Set_Menu(&menu, IMAGE_PAGE);
//                    line_number=1;
//                    ips200_clear();
//                    break ;
               default:
                   break ;
           }
    }

}

//void menu_Val_CFG(float *CFG_Val, uint8 page_row, float basic_Val)
//{
//
//}
