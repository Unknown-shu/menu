#include "MyHeadfile.h"
 /*
 * 空白页
 * 使用时请更改Null_line_number
 *       在page_setting.h添加null_page_process()
 *                      和extern int Null_line_number
 *       在page_setting.c添加int Null_line_number
 *
 */
#include "zf_common_headfile.h"
#include "mymenu.h"

#define line_number Camera_line_number

void Camera_page_process(int Event_Code)
{
    line_number_max=2;

   //显示菜单

    MyCamera_Show();
    ips200_show_string(0, 155, "Encoder_L:");
    ips200_show_string(0, 155+18, "Encoder_R:");
    ips200_show_int(160, 155, Encoder_speed_l, 5);
    ips200_show_int(160, 155+18, Encoder_speed_r, 5);

////  1.组合导航
//    if(line_number!=1) ips200_show_string_color(0, 155,"", PenColor);
//    else              ips200_show_string_color(0, 155,"", PenColor_else);
////////   2.电机控制
//    if(line_number!=2) ips200_show_string_color(0, 155+18,"", PenColor);
//     else              ips200_show_string_color(0, 155+18,"", PenColor_else);
////
//    if(line_number!=3) ips200_show_string_color(0, 18*3,"", PenColor);
//     else              ips200_show_string_color(0, 18*3,"", PenColor_else);
//
//    if(line_number!=4) ips200_show_string_color(0, 18*4,"", PenColor);
//     else              ips200_show_string_color(0, 18*4,"", PenColor_else);

    //指针向上
       if(key_get_state(KEY_1) == KEY_SHORT_PRESS || key_get_state(KEY_1) == KEY_LONG_PRESS)
       {
           Beep_ShortRing();
           key_clear_state(KEY_1);
           line_number--;//高亮选择往下
           pagelimit(&line_number,line_number_max);
       }
       //指针向下
       if(key_get_state(KEY_3) == KEY_SHORT_PRESS || key_get_state(KEY_3) == KEY_LONG_PRESS)
       {
           Beep_ShortRing();
           key_clear_state(KEY_3);
           line_number++; //高亮选择往上
           pagelimit(&line_number,line_number_max);
       }
       //指针向左
       if(key_get_state(KEY_2) == KEY_SHORT_PRESS || key_get_state(KEY_2) == KEY_LONG_PRESS)
       {
           Beep_ShortRing();
           key_clear_state(KEY_2);
           Set_Menu(&menu, MAIN_PAGE);
//           line_number=1;
           ips200_clear();
       }
       //指针按下
       if(key_get_state(KEY_4) == KEY_SHORT_PRESS)
       {
           Beep_ShortRing();
           switch(line_number)
           {
               case 1:

                   break ;
               case 2:

                   break;
               case 3:

                   break;
               case 4:

                   break;
               default:
                   break ;
           }
           key_clear_state(KEY_4);
       }

   }

