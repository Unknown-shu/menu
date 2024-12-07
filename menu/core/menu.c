#include "menu.h"
//----------------------------------------------------------------------------------------------------

struct Menu menu;

void Menu_init(void){
    menu_init(&menu, MAIN_PAGE, NULL_KEY_EVENT);
//    menu_para_init();
}
//----------------------------------------------------------------------------------------------------
/*�˵���ʼ��*/
void menu_init(struct Menu *handle, uint8_t Page, int EVENT_CODE)
{
    memset(handle, 0, sizeof(struct Menu));
    handle->Current_Page = Page  ;
    handle->KeyEvent = EVENT_CODE ;
}

/*�˵���ת*/
void Set_Menu(struct Menu *handle, uint8_t Page)
{
    handle->Current_Page= Page ;
}

/*��ȡ��ǰ�˵�*/
uint8_t Get_Menu(struct Menu *handle)
{
    return handle->Current_Page ;
}

/*���õ�ǰ�������¼�ֵ*/
void Set_Event_Code(struct Menu *handle, int Event_Code)
{
    handle->KeyEvent = Event_Code ;
}

/*��ȡ��ǰ�������¼�ֵ*/
int Get_Event_Code(struct Menu *handle)
{
    return handle->KeyEvent ;
}
/*�˵�ѡ��ѡ��ѭ��*/
void pagelimit(int8 *page_num,uint8 page_num_max)
{
    if(*page_num>page_num_max)*page_num=1;
    if(*page_num<=0)*page_num=page_num_max;
}
int Judgepress(struct Menu *handle)
{

    if(handle->KeyEvent != NULL_KEY_EVENT)
        return 1;
    else
        return 0;
}
//----------------------------------------------------------------------------------------------------
/*�˵�����*/
void Menu_Handler(struct Menu *handle)
{
    /*��ǰ�ǲ˵����ĸ�ҳ��*/

    switch(handle->Current_Page)
    {
        case MAIN_PAGE :
            /*���ע��ļ�ֵ����Ӧ�Ĵ���*/
            main_page_process(handle->KeyEvent);
            break ;
        case Start_PAGE :
            /*���ע��ļ�ֵ����Ӧ�Ĵ���*/
            Start_page_process(handle->KeyEvent);
            break ;

        case NAVIGATION_PAGE :
            /*���ע��ļ�ֵ����Ӧ�Ĵ���*/
            navigation_page_process(handle->KeyEvent);
            break ;
        case Camera_PAGE :
            /*���ע��ļ�ֵ����Ӧ�Ĵ���*/
            Camera_page_process(handle->KeyEvent);
            break ;
        case  Config_PAGE :
            Config_page_process(handle->KeyEvent);
            break ;
//        case SERVO_PAGE :
//            /*���ע��ļ�ֵ����Ӧ�Ĵ���*/
//            servo_page_process(handle->KeyEvent);
//            break ;
//        case SERVO_TURN_P_PAGE :
//            /*���ע��ļ�ֵ����Ӧ�Ĵ���*/
//            servo_turn_p_page_process(handle->KeyEvent);
//            break ;
//        case SERVO_TURN_D_PAGE :
//            /*���ע��ļ�ֵ����Ӧ�Ĵ���*/
//            servo_turn_d_page_process(handle->KeyEvent);
//            break ;
//        case SERVO_DUTY_PAGE :
//            /*���ע��ļ�ֵ����Ӧ�Ĵ���*/
//            servo_duty_page_process(handle->KeyEvent);
//            break ;
//        case START_PAGE :
//            /*���ע��ļ�ֵ����Ӧ�Ĵ���*/
//            start_page_process(handle->KeyEvent);
//            break ;
//        case GPS_MAP_PAGE :
//            /*���ע��ļ�ֵ����Ӧ�Ĵ���*/
//            gps_map_page_process(handle->KeyEvent);
//            break ;
//        case ELEMENT_PAGE :
//            /*���ע��ļ�ֵ����Ӧ�Ĵ���*/
//            element_page_process(handle->KeyEvent);
//            break ;
//        case SPEED_PAGE :
//            /*���ע��ļ�ֵ����Ӧ�Ĵ���*/
//            speed_page_process(handle->KeyEvent);
//            break ;
//        case START_ANGLE_PAGE :
//            /*���ע��ļ�ֵ����Ӧ�Ĵ���*/
//            start_angle_page_process(handle->KeyEvent);
//            break ;
//        case GPS_POINTS_PAGE :
//            /*���ע��ļ�ֵ����Ӧ�Ĵ���*/
//            points_page_process(handle->KeyEvent);
//            break ;
//        case SERVO_TURN_PAGE :
//            /*���ע��ļ�ֵ����Ӧ�Ĵ���*/
//            servo_turn_page_process(handle->KeyEvent);
//            break ;
//        case SERVO_STRAIGHT_PAGE :
//            /*���ע��ļ�ֵ����Ӧ�Ĵ���*/
//            servo_straight_page_process(handle->KeyEvent);
//            break ;
//        case SERVO_STRAIGHT_P_PAGE :
//            /*���ע��ļ�ֵ����Ӧ�Ĵ���*/
//            servo_straight_p_page_process(handle->KeyEvent);
//            break ;
//        case SERVO_STRAIGHT_D_PAGE :
//            /*���ע��ļ�ֵ����Ӧ�Ĵ���*/
//            servo_straight_d_page_process(handle->KeyEvent);
//            break ;
        default:
            break ;
    }

    /*��ʱ���¼��������ֹ�ظ�����*/

}

/***********************************************
* @brief : �˵�����������ҳ��
* @param : *CFG_val              ��Ҫ���õ�ֵ�ĵ�ַ���ǵ�&
*           page_start_row       ��ʼ��
*           basic_val            ��׼����
* @return: void
* @date  : 2024.10.15
* @author: SJX
************************************************/
#define VAL_VFG_SHOW_NUM_BIT          6
#define VAL_VFG_SHOW_POINT_BIT        6
#define VAL_VFG_SHOW_TOTAL_LINE       6                     //�����������������̶��кͼ��������к�exit��
#define LINE_MAX                      VAL_VFG_SHOW_TOTAL_LINE-1
uint8 up_down_flag = 0;         //���β˵������滹�������棬Ĭ��Ϊ0�����棬Ϊ1������
float basic_1, basic_10, basic_100 ;
uint16_t menu_Val_CFG_line;
void menu_Val_CFG(float *CFG_val, uint16 page_start_row, float basic_val )
{
    uint8 flush_flag;
    uint8 CFG_stop_flag = 0;
    menu_Val_CFG_line = 1;
    bool based_flag = 0;                            //ѡ�б�־λ��ѡ��Ϊ1����ѡ��Ϊ0
    basic_1 = basic_val;
    basic_10 = basic_val / 10 ;
    basic_100 = basic_val / 100;


    if(page_start_row > (319 - (10+18+ 18 * VAL_VFG_SHOW_TOTAL_LINE)))
    {
        up_down_flag = 1;
    }
    else up_down_flag = 0;
    menu_Val_CFG_clear(&page_start_row);
    ips200_set_color(RGB565_WHITE, RGB565_BLACK);
    menu_Val_CFG_Flush(CFG_val, page_start_row, based_flag);
    while(CFG_stop_flag == 0)
    {
//        printf("%d ,%d ,%d ,%d, %d, %d\r\n ",target_left,target_right,Encoder_speed_l,Encoder_speed_r,pwm_left, pwm_right);
        flush_flag = Key_IfEnter();
        if(flush_flag == 1 || switch_encoder_change_num != 0)
        {
            if(key_get_state(KEY_4) == KEY_SHORT_PRESS)
            {
                switch(menu_Val_CFG_line)
                {
                    case 1:
                        based_flag = !based_flag;
                        break;

                    case 2:
                        based_flag = !based_flag;
                        break;

                    case 3:
                        based_flag = !based_flag;
                        break;

                    case 4:
                        *CFG_val = 0;
                        break;

                    case 5:
                        CFG_stop_flag = 1;
                        break;
                }
            }
            if(key_get_state(KEY_3) == KEY_SHORT_PRESS)
            {
                if(based_flag == 0)
                {
                    menu_Val_CFG_line++;
                    menu_Val_CFG_Limit(&menu_Val_CFG_line, LINE_MAX);
                }
                else
                {
                    switch (menu_Val_CFG_line)
                    {
                        case 1:
                            *CFG_val += basic_1;
                            break;
                        case 2:
                            *CFG_val += basic_10;
                            break;
                        case 3:
                            *CFG_val += basic_100;
                            break;
                    }
                }

            }
            if(key_get_state(KEY_1) == KEY_SHORT_PRESS)
            {
                if(based_flag == 0)
                {
                    menu_Val_CFG_line--;
                    menu_Val_CFG_Limit(&menu_Val_CFG_line, LINE_MAX);
                }
                else
                {
                    switch (menu_Val_CFG_line)
                    {
                        case 1:
                            *CFG_val += basic_1;
                            break;
                        case 2:
                            *CFG_val += basic_10;
                            break;
                        case 3:
                            *CFG_val += basic_100;
                            break;
                    }
                }

             }
            if(If_Switch_Encoder_Change() == 1)
            {
                if(based_flag == 0)
                {
                    menu_Val_CFG_line += switch_encoder_change_num;
                    menu_Val_CFG_Limit(&menu_Val_CFG_line, LINE_MAX);
                }
                else
                {
                    switch (menu_Val_CFG_line)
                   {
                       case 1:
                           *CFG_val += (basic_1 * switch_encoder_change_num);
                           break;
                       case 2:
                           *CFG_val += basic_10 * switch_encoder_change_num;
                           break;
                       case 3:
                           *CFG_val += basic_100 * switch_encoder_change_num;
                           break;
                   }
                }
            }
            menu_Val_CFG_Flush(CFG_val, page_start_row, based_flag);
//            Beep_ShortRing();
            Flash_WriteAllVal();
        }
    }
    ips200_clear();

}
/***********************************************
* @brief : �˵�����������ҳ����������(�ú�)��ȷ����ʼ��
* @param : page_start_row       ��ʼ��
* @return: void
* @date  : 2024.10.18
* @author: SJX
************************************************/
void menu_Val_CFG_clear(uint16 *page_start_row)
{
    uint16 i = 0;
    if(up_down_flag == 0)
    {

        for(i = *page_start_row + 18; i < *page_start_row + 10+18 + VAL_VFG_SHOW_TOTAL_LINE * 18; i++)
        {
            ips200_draw_line(0, i, 239, i, RGB565_BLACK);
        }
//        IPS200_Full_Parts(0, 240, *page_start_row + 18, *page_start_row + 10+18 + VAL_VFG_SHOW_TOTAL_LINE * 18);
        *page_start_row = *page_start_row + 5 + 18 * 1;

    }
    else if(up_down_flag == 1)
    {
        for(i = *page_start_row  ; i > *page_start_row -10 -18 * VAL_VFG_SHOW_TOTAL_LINE  ; i--)
        {
            ips200_draw_line(0, i, 239, i, RGB565_BLACK);
        }
        *page_start_row = *page_start_row -5 - 18 * VAL_VFG_SHOW_TOTAL_LINE;
    }
}
/***********************************************
* @brief : �˵�����������ҳ�����ˢ�º���
* @param : *CFG_val              ��Ҫ���õ�ֵ�ĵ�ַ���ǵ�&
*           page_start_row       ��ʼ��
* @return: void
* @
* @date  : 2024.10.18
* @author: SJX
************************************************/
void menu_Val_CFG_Flush(float *CFG_val, uint16 page_start_row,  bool temp_based_flag)
{
        ips200_show_float(0, page_start_row + 18*0, *CFG_val, VAL_VFG_SHOW_NUM_BIT, VAL_VFG_SHOW_POINT_BIT);
        menu_Val_CFG_Arrow_Show(page_start_row, menu_Val_CFG_line);
        if(temp_based_flag == 1)
        {
            if(menu_Val_CFG_line == 1)  ips200_show_float_color(18, page_start_row + 18 * menu_Val_CFG_line, basic_1, VAL_VFG_SHOW_NUM_BIT, VAL_VFG_SHOW_POINT_BIT,RGB565_RED);
            else                ips200_show_float_color(18, page_start_row + 18 * 1, basic_1, VAL_VFG_SHOW_NUM_BIT, VAL_VFG_SHOW_POINT_BIT,RGB565_WHITE);

            if(menu_Val_CFG_line == 2)  ips200_show_float_color(18, page_start_row + 18 * menu_Val_CFG_line, basic_10, VAL_VFG_SHOW_NUM_BIT, VAL_VFG_SHOW_POINT_BIT,RGB565_RED);
            else                ips200_show_float_color(18, page_start_row + 18 * 2, basic_10, VAL_VFG_SHOW_NUM_BIT, VAL_VFG_SHOW_POINT_BIT,RGB565_WHITE);

            if(menu_Val_CFG_line == 3)  ips200_show_float_color(18, page_start_row + 18 * menu_Val_CFG_line, basic_100, VAL_VFG_SHOW_NUM_BIT, VAL_VFG_SHOW_POINT_BIT,RGB565_RED);
            else                ips200_show_float_color(18, page_start_row + 18 * 3, basic_100, VAL_VFG_SHOW_NUM_BIT, VAL_VFG_SHOW_POINT_BIT,RGB565_WHITE);

            if(menu_Val_CFG_line == 4)  ips200_show_string_color(18, page_start_row + 18 * menu_Val_CFG_line, "empty", RGB565_RED);
            else                ips200_show_string_color(18, page_start_row + 18 * 4, "empty", RGB565_WHITE);

            if(menu_Val_CFG_line == 5)  ips200_show_string_color(18, page_start_row + 18 * menu_Val_CFG_line, "exit", RGB565_RED);
            else                ips200_show_string_color(18, page_start_row + 18 * 5, "exit", RGB565_WHITE);

        }
        else
        {
            ips200_show_float(18, page_start_row + 18*1, basic_1, VAL_VFG_SHOW_NUM_BIT, VAL_VFG_SHOW_POINT_BIT);
            ips200_show_float(18, page_start_row + 18*2, basic_10, VAL_VFG_SHOW_NUM_BIT, VAL_VFG_SHOW_POINT_BIT);
            ips200_show_float(18, page_start_row + 18*3, basic_100, VAL_VFG_SHOW_NUM_BIT, VAL_VFG_SHOW_POINT_BIT);
            ips200_show_string(18, page_start_row + 18*5, "exit");
            ips200_show_string(18, page_start_row + 18*4, "empty");
        }

//    uint8 i;
//    i = Key_IfEnter();
//    val_cfg_key_ifenter_flag += i;
    key_clear_all_state();
}
/***********************************************
* @brief : �˵�����������ҳ�������޷�����
* @param : *line              ��Ҫ���õ��еĵ�ַ���ǵ�&
*           line_max          �����
* @return: void
* @
* @date  : 2024.10.18
* @author: SJX
************************************************/
void menu_Val_CFG_Limit(uint16 *line, uint16 line_max)
{
    if(*line > line_max)
    {
        *line = 1;
    }
    else if(*line < 1)
    {
        *line = line_max;
    }
}

/***********************************************
* @brief : �˵�����������ҳ���ͷ��ʾ
* @param : *line              ��Ҫ���õ��еĵ�ַ���ǵ�&
*           line_max          �����
* @return: void
* @
* @date  : 2024.10.19
* @author: SJX
************************************************/
void menu_Val_CFG_Arrow_Show(uint16 page_start_row,uint16 line_num)
{
    for (uint16 i = 1; i <= LINE_MAX; i++)
    {
        if (i == line_num)
        {
            // ��ǰ����ʾ "->"
            ips200_show_string(0, page_start_row + i * 18, "->");
        }
        else
        {
            // ��������ʾ�ո�
            ips200_show_string(0, page_start_row + i * 18, "  ");
        }
    }
}
/***********************************************
* @brief : cfg�˵�open close��ʾ
* @param : page_start_row     ��ʼ��
*          value              ֵ 1��0��
* @return: void
* @date  : 2024��10��31��15:55:00
* @author: SJX
************************************************/
void menu_Set_CFG_OpenClose_Show(uint16 page_start_row, uint8 value)
{
    if(value == 1)
    {
        ips200_show_string(190, page_start_row, "Open ");
    }
    else if(value == 0)
    {
        ips200_show_string(190, page_start_row, "Close");
    }
    else
    {
        ips200_show_string(190, page_start_row, "ValEr");
    }
}
/***********************************************
* @brief : cfg�˵�open close��ʾ
* @param : value              ��Ҫ��ת��ֵ �����ݵ�ַ
* @return: void
* @date  : 2024��10��31��15:55:00
* @author: SJX
************************************************/
void menu_Set_CFG_Value_Toggle(uint8 *value)
{
    if(*value == 1)
        *value = 0;
    else
        *value = 1;
}

/***********************************************
* @brief : �˵�ѡ������ˢ��
* @param : void
* @return: line_num �еĵ�ַ����ʹ���˼���������������Ҫ��ַ����
* @date  : 2024��11��6��13:12:04
* @author: SJX
* @exp   ��Line_Num_Flush(&line_number);
************************************************/
void Line_Num_Flush(int8 *line_num)
{
//    if(If_Switch_Encoder_Change() == 1)
    if(switch_encoder_change_num != 0)
    {
        *line_num += switch_encoder_change_num;
        pagelimit(&*line_num,line_number_max);
    }
    switch_encode_change_get_buff_flag = 0;
}
//void IPS200_Full_Parts(uint16 start_X, uint16 end_X, uint16 start_Y, uint16 end_Y)
//{
//    uint16 while_color_buffer[ips200_width_max], i, j;
//    IPS200_CS(0);
//    for(i = start_X; i < end_X; i ++)
//    {
//        while_color_buffer[i] = RGB565_WHITE;
//    }
//    for (j = start_Y; j < end_Y; j ++)
//    {
//        ips200_write_16bit_data_array(while_color_buffer, 240);
//    }
//    IPS200_CS(1);
//}
