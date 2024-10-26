/*
 * nav.c
 *
 *  Created on: 2024年10月25日
 *      Author: SJX
 */
#include "zf_common_headfile.h"
#include "mymenu.h"

#define line_number navigation_line_number

#define VAL_SHOW_NUM_BIT          2
#define VAL_SHOW_POINT_BIT        3
#define VAL_SHOW_START_COL        162

uint8 enter_flag = 1;
uint8 Test;

void navigation_page_process(int Event_Code)
{
    line_number_max=13;
    static uint16 i = 0;
    static uint16 Test = 0;
   //显示菜单
    ips200_show_string_color(60, 0,"Value", PenColor);

    enter_flag += Test;
//    printf("%d\r\n",enter_flag);
    if(enter_flag > 0)
    {
        i = 0;
        enter_flag = 0;

        // Left Speed PID
        if (line_number != 1)     ips200_show_string_color(0, 18 * 1, "Left_Speed_KP", PenColor);
        else                      ips200_show_string_color(0, 18 * 1, "Left_Speed_KP", PenColor_else);
        ips200_show_float(VAL_SHOW_START_COL, 18 * 1, Motor_Speed_PID_Left.Kp, VAL_SHOW_NUM_BIT, VAL_SHOW_POINT_BIT);

        if (line_number != 2)     ips200_show_string_color(0, 18 * 2, "Left_Speed_Ki", PenColor);
        else                      ips200_show_string_color(0, 18 * 2, "Left_Speed_Ki", PenColor_else);
        ips200_show_float(VAL_SHOW_START_COL, 18 * 2, Motor_Speed_PID_Left.Ki, VAL_SHOW_NUM_BIT, VAL_SHOW_POINT_BIT);

        if (line_number != 3)     ips200_show_string_color(0, 18 * 3, "Left_Speed_Kd", PenColor);
        else                      ips200_show_string_color(0, 18 * 3, "Left_Speed_Kd", PenColor_else);
        ips200_show_float(VAL_SHOW_START_COL, 18 * 3, Motor_Speed_PID_Left.Kd, VAL_SHOW_NUM_BIT, VAL_SHOW_POINT_BIT);

        // Right Speed PID
        if (line_number != 4)     ips200_show_string_color(0, 18 * 4, "Right_Speed_KP", PenColor);
        else                      ips200_show_string_color(0, 18 * 4, "Right_Speed_KP", PenColor_else);
        ips200_show_float(VAL_SHOW_START_COL, 18 * 4, Motor_Speed_PID_Right.Kp, VAL_SHOW_NUM_BIT, VAL_SHOW_POINT_BIT);

        if (line_number != 5)     ips200_show_string_color(0, 18 * 5, "Right_Speed_Ki", PenColor);
        else                      ips200_show_string_color(0, 18 * 5, "Right_Speed_Ki", PenColor_else);
        ips200_show_float(VAL_SHOW_START_COL, 18 * 5, Motor_Speed_PID_Right.Ki, VAL_SHOW_NUM_BIT, VAL_SHOW_POINT_BIT);

        if (line_number != 6)     ips200_show_string_color(0, 18 * 6, "Right_Speed_Kd", PenColor);
        else                      ips200_show_string_color(0, 18 * 6, "Right_Speed_Kd", PenColor_else);
        ips200_show_float(VAL_SHOW_START_COL, 18 * 6, Motor_Speed_PID_Right.Kd, VAL_SHOW_NUM_BIT, VAL_SHOW_POINT_BIT);

        // Turn Speed PID
        if (line_number != 7)     ips200_show_string_color(0, 18 * 7, "Turn_Speed_KP", PenColor);
        else                      ips200_show_string_color(0, 18 * 7, "Turn_Speed_KP", PenColor_else);
        ips200_show_float(VAL_SHOW_START_COL, 18 * 7, Turn_Speed_PID.Kp, VAL_SHOW_NUM_BIT, VAL_SHOW_POINT_BIT);

        if (line_number != 8)     ips200_show_string_color(0, 18 * 8, "Turn_Speed_Ki", PenColor);
        else                      ips200_show_string_color(0, 18 * 8, "Turn_Speed_Ki", PenColor_else);
        ips200_show_float(VAL_SHOW_START_COL, 18 * 8, Turn_Speed_PID.Ki, VAL_SHOW_NUM_BIT, VAL_SHOW_POINT_BIT);

        if (line_number != 9)     ips200_show_string_color(0, 18 * 9, "Turn_Speed_Kd", PenColor);
        else                      ips200_show_string_color(0, 18 * 9, "Turn_Speed_Kd", PenColor_else);
        ips200_show_float(VAL_SHOW_START_COL, 18 * 9, Turn_Speed_PID.Kd, VAL_SHOW_NUM_BIT, VAL_SHOW_POINT_BIT);

        if (line_number != 10)     ips200_show_string_color(0, 18 * 10, "V0", PenColor);
        else                       ips200_show_string_color(0, 18 * 10, "V0", PenColor_else);
        ips200_show_float(VAL_SHOW_START_COL, 18*10, V0, 3, 2);

        // Straight Speed PID
        if (line_number != 11)    ips200_show_string_color(0, 18 * 11, "Straight_Speed_KP", PenColor);
        else                      ips200_show_string_color(0, 18 * 11, "Straight_Speed_KP", PenColor_else);
        ips200_show_float(VAL_SHOW_START_COL, 18 * 11, Straight_Speed_PID.Kp, VAL_SHOW_NUM_BIT, VAL_SHOW_POINT_BIT);

        if (line_number != 12)    ips200_show_string_color(0, 18 * 12, "Straight_Speed_Ki", PenColor);
        else                      ips200_show_string_color(0, 18 * 12, "Straight_Speed_Ki", PenColor_else);
        ips200_show_float(VAL_SHOW_START_COL, 18 * 12, Straight_Speed_PID.Ki, VAL_SHOW_NUM_BIT, VAL_SHOW_POINT_BIT);

        if (line_number != 13)    ips200_show_string_color(0, 18 * 13, "Straight_Speed_Kd", PenColor);
        else                      ips200_show_string_color(0, 18 * 13, "Straight_Speed_Kd", PenColor_else);
        ips200_show_float(VAL_SHOW_START_COL, 18 * 13, Straight_Speed_PID.Kd, VAL_SHOW_NUM_BIT, VAL_SHOW_POINT_BIT);
    }
    Test = Key_IfEnter();

    if(key_get_state(KEY_1) == KEY_SHORT_PRESS)
    {
        Beep_ShortRing();
        line_number--;//高亮选择往下
        pagelimit(&line_number,line_number_max);
        i++;
    }
    if(key_get_state(KEY_3) == KEY_SHORT_PRESS)
    {
        Beep_ShortRing();
        line_number++; //高亮选择往上
        pagelimit(&line_number,line_number_max);
        i++;
    }
    if(key_get_state(KEY_2) == KEY_SHORT_PRESS)
    {
        Beep_ShortRing();
        Set_Menu(&menu, MAIN_PAGE);
        ips200_clear();
        i++;
    }
    if(key_get_state(KEY_4) == KEY_SHORT_PRESS)
    {
        Beep_ShortRing();
        switch(line_number)
        {
            case 1:
                menu_Val_CFG(&Motor_Speed_PID_Left.Kp, 18 * 1, 1);
                break;
            case 2:
                menu_Val_CFG(&Motor_Speed_PID_Left.Ki, 18 * 2, 1);
                break;
            case 3:
                menu_Val_CFG(&Motor_Speed_PID_Left.Kd, 18 * 3, 1);
                break;

            // 右轮速度PID参数调整
            case 4:
                menu_Val_CFG(&Motor_Speed_PID_Right.Kp, 18 * 4, 1);
                break;
            case 5:
                menu_Val_CFG(&Motor_Speed_PID_Right.Ki, 18 * 5, 1);
                break;
            case 6:
                menu_Val_CFG(&Motor_Speed_PID_Right.Kd, 18 * 6, 1);
                break;

            // 转向PID参数调整
            case 7:
                menu_Val_CFG(&Turn_Speed_PID.Kp, 18 * 7, 1);
                break;
            case 8:
                menu_Val_CFG(&Turn_Speed_PID.Ki, 18 * 8, 1);
                break;
            case 9:
                menu_Val_CFG(&Turn_Speed_PID.Kd, 18 * 9, 1);
                break;
            case 10:
                menu_Val_CFG(&V0, 18 * 10, 50);
                break;
            case 11:
                menu_Val_CFG(&Straight_Speed_PID.Kp, 18 * 11, 1);
                break;
            case 12:
                menu_Val_CFG(&Straight_Speed_PID.Ki, 18 * 12, 1);
                break;
            case 13:
                menu_Val_CFG(&Straight_Speed_PID.Kd, 18 * 13, 1);
                break;
            default:
                break ;
        }
        i++;
        Flash_WriteAllVal();
    }

    key_clear_all_state();
}
