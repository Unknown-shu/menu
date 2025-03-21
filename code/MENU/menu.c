#include "menu.h"

uint8 menu_key_event = menu_release;
static uint8 menu_cfg_flag = 0;
static uint8 menu_global_line = 0;
MenuPage_Linked_List *menu_head_page_node = NULL; // 菜单链表头指针

/*
{"Test1", FLOAT_VALUE_SHOW_TYPE, .line_extends.float_value_show_line.show_value = &Test,.display_line_count = 0},
{"Test2", INT_VALUE_SHOW_TYPE, .line_extends.int_value_show_line.show_value = &int_val,.display_line_count = 0},
{"Beep", ENTER_FUNC_RUN_TYPE, .action.void_func=MENUT, .display_line_count = 0},
{"TEST", STATIC_FUNC_RUN_TYPE, .action.void_func=MENUTE,.display_line_count = 0},
{"EDIT", FLOAT_VALUE_EDIT_TYPE, .action.float_float_func = menu_Val_CFG,.line_extends.float_value_edit_line.edit_value = &Test,.line_extends.float_value_edit_line.basic_val = 1,.display_line_count = 0},
{"EDIT", CONFIG_VALUE_SHOW_TYPE, .line_extends.config_value_show_line.show_value = &Test,.display_line_count = 0},
{"TEST", PAGE_JUMP_TYPE, .action.void_func=Test_Page_Init,.display_line_count = 0},
 */

float Test = 100;
/***********************************************
* @brief : 主页面初始化
* @param : void
* @return: void
* @date  : 2025年3月20日14:26:28
* @author: SJX
************************************************/
void Main_Page_Init(void)
{
    static MenuLine  MENU_LineList[] = {
//            {"Test1", FLOAT_VALUE_SHOW_TYPE, .line_extends.float_value_show_line.show_value = &Test,.display_line_count = 0},
//            {"Test2", INT_VALUE_SHOW_TYPE, .line_extends.int_value_show_line.show_value = &int_val,.display_line_count = 0},
////            {"Beep", ENTER_FUNC_RUN_TYPE, .action.void_func=MENUTESTTTTTTTTTTTTTTTTTTTTT, .display_line_count = 0},
////            {"TEST", STATIC_FUNC_RUN_TYPE, .action.void_func=MENUTESTTTTTTTTTTTTTTTTTTTTT,.display_line_count = 0},
//            {"EDIT", FLOAT_VALUE_EDIT_TYPE, .action.float_float_func = menu_Val_CFG,.line_extends.float_value_edit_line.edit_value = &Test,.line_extends.float_value_edit_line.basic_val = 10,.display_line_count = 0},
//            {"TEST", PAGE_JUMP_TYPE, .action.void_func=Test_Page_Init,.display_line_count = 0},
            MENU_ITEM_FLOAT_SHOW("aaa", &Test, 0),
            {".",  }
    };
    static MenuPage Main_Page = {"Main", .line = MENU_LineList, .open_status = 0} ;

    Menu_Push_Node(&Main_Page);
}

/***********************************************
* @brief : 菜单主函数运行
* @param : void
* @return: void
* @date  : 2025年3月20日18:58:35
* @author: SJX
************************************************/
void MENU_RUN(void)
{
    static uint8 i = 0;

    my_assert(menu_head_page_node != NULL);

    if(menu_head_page_node->page->open_status != 1)
    {
        Menu_Get_Page_LineNumMAX(menu_head_page_node->page);
        menu_global_line = menu_head_page_node->page->line_num;
//        menu_global_line = menu_head_page_node->page->line_num;
        My_Show_String_Centered(0, menu_head_page_node->page->page_name);
//        Menu_Val_CFG_Limit(&menu_global_line, menu_head_page_node->page->line_num_max);
        menu_head_page_node->page->open_status = 1;
    }

    static uint16 use_start_line = 0;
    for(i = 0; i < (menu_head_page_node->page->line_num_max); i++)
    {
        if(menu_head_page_node->page->line[i].display_line_count != 0)
        {
            use_start_line += menu_head_page_node->page->line[i].display_line_count;
        }

        if(menu_head_page_node->page->line[i].line_name != 0)
            My_Show_String_Color(0, (use_start_line + (i+1)) * 18, menu_head_page_node->page->line[i].line_name,(i+1)==menu_global_line?SELECTED_BRUSH:DEFAULT_BRUSH);
        switch(menu_head_page_node->page->line[i].line_type)
        {
            case FLOAT_VALUE_SHOW_TYPE:
                if(menu_head_page_node->page->line[i].line_extends.float_value_show_line.show_value != NULL)
                {
                    My_Show_Float_Color(120, (use_start_line + (i+1)) * 18, (*(menu_head_page_node->page->line[i].line_extends.float_value_show_line.show_value))+0.00001, 8, 5, DEFAULT_BRUSH);
                }
                else
                    My_Show_Float_Color(120, (use_start_line + (i+1)) * 18, +0.00001, 8, 5, DEFAULT_BRUSH);
                   break;
            case INT_VALUE_SHOW_TYPE:
                if(menu_head_page_node->page->line[i].line_extends.int_value_show_line.show_value != NULL)
                {
                    My_Show_Int_Color(120, (use_start_line + (i+1)) * 18, (*(menu_head_page_node->page->line[i].line_extends.int_value_show_line.show_value)), 10,  DEFAULT_BRUSH);
                }
                else
                    My_Show_Int_Color(120, (use_start_line + (i+1)) * 18, 0, 0, DEFAULT_BRUSH);
                   break;
            case STATIC_FUNC_RUN_TYPE:
            {
                if(menu_head_page_node->page->line[i].action.void_func)
                {
                    menu_head_page_node->page->line[i].action.void_func();
                }
                else
                    my_assert(0);       //不传函数执行牛魔
                   break;
            }
            case CONFIG_VALUE_SHOW_TYPE:
            {
                if(menu_head_page_node->page->line[i].line_extends.config_value_show_line.show_value != NULL)
                {
                    if(*(menu_head_page_node->page->line[i].line_extends.config_value_show_line.show_value) == 0)
                        My_Show_String(120, (use_start_line + (i+1)) * 18, "Close");
                    else if(*(menu_head_page_node->page->line[i].line_extends.config_value_show_line.show_value) == 1)
                        My_Show_String(120, (use_start_line + (i+1)) * 18, "Open ");
                    else
                        my_assert(0);                   //配置变量传入open || close以外的值
                }
                   break;
            }
            case FLOAT_VALUE_EDIT_TYPE:
            {
                if(menu_head_page_node->page->line[i].line_extends.float_value_edit_line.edit_value != NULL)
                {
                    My_Show_Float_Color(120, (use_start_line + (i+1)) * 18, (*(menu_head_page_node->page->line[i].line_extends.float_value_edit_line.edit_value))+0.00001, 8, 5, DEFAULT_BRUSH);
                }
                else
                    My_Show_Float_Color(120, (use_start_line + (i+1)) * 18, +0.00001, 8, 5, DEFAULT_BRUSH);
                   break;
            }
            default:break;

        }
    }
    Menu_Key_Process();

    use_start_line = 0;

    printf("%d,%d\r\n", menu_global_line, i);
}



/***********************************************
* @brief : 按键刷新菜单动作
* @param : void
* @return: void
* @date  : 2025年3月20日14:26:28
* @author: SJX
************************************************/
void Menu_Event_Flush(void)
{
    if(my_key_get_state(MENU_KEY) == MY_KEY_RELEASE)
    {
        menu_key_event = menu_release;
    }
    else if(my_key_get_state(MENU_KEY) == MY_KEY_SHORT_PRESS)
    {
        menu_key_event = menu_yes;
    }
    else if(my_key_get_state(MENU_KEY) == MY_KEY_LONG_PRESS)
    {
        menu_key_event = menu_back;
    }

    if(If_Switch_Encoder_Change() == 1)
    {
        if(menu_cfg_flag == 0)
        {
            menu_global_line += switch_encoder_change_num;
            Menu_Val_CFG_Limit(&menu_global_line, menu_head_page_node->page->line_num_max);
        }
    }
}
/***********************************************
* @brief : 菜单按键处理
* @param : void
* @return: void
* @date  : 2025年3月20日14:29:25
* @author: SJX
************************************************/
void Menu_Key_Process(void)
{
    my_assert(menu_head_page_node != NULL);

    // 处理按键事件
    if(menu_key_event != menu_release)
    {
        switch (menu_key_event)
        {
            case menu_back:
                Menu_Pop_Node();
                break;
            case menu_yes:      // 执行当前选中的行的操作
            {
                switch (menu_head_page_node->page->line[menu_global_line-1].line_type)
                {
                    case ENTER_FUNC_RUN_TYPE:
                    {
                        if(menu_head_page_node->page->line[menu_global_line-1].action.void_func)
                        {
                            menu_head_page_node->page->line[menu_global_line-1].action.void_func();
                        }
                        else
                            my_assert(0);       //不传函数执行牛魔
                           break;
                    }
                    case PAGE_JUMP_TYPE:
                    {
                        if(menu_head_page_node->page->line[menu_global_line-1].action.void_func)
                        {
                            menu_head_page_node->page->line[menu_global_line-1].action.void_func();
                        }
                        else
                            my_assert(0);       //不传函数执行牛魔
                           break;
                    }
                    case CONFIG_VALUE_SHOW_TYPE:
                    {
                        if(menu_head_page_node->page->line[menu_global_line-1].line_extends.config_value_show_line.show_value != NULL)
                        {
                            *(menu_head_page_node->page->line[menu_global_line-1].line_extends.config_value_show_line.show_value) =!*(menu_head_page_node->page->line[menu_global_line-1].line_extends.config_value_show_line.show_value);

                        }
                        else
                            my_assert(0);
                           break;
                    }
                    case FLOAT_VALUE_EDIT_TYPE:
                    {
                        if(menu_head_page_node->page->line[menu_global_line-1].action.float_float_func)
                        {
                            menu_head_page_node->page->line[menu_global_line-1].action.float_float_func(
                                menu_head_page_node->page->line[menu_global_line-1].line_extends.float_value_edit_line.edit_value,
                                menu_head_page_node->page->line[menu_global_line-1].line_extends.float_value_edit_line.basic_val
                            );
                        }
                        else
                            my_assert(0);       //不传函数执行牛魔
                           break;
                    }
                    default:break;
                }

            }
                break;
            default:break;

        }
    }
    menu_key_event = menu_release;

}



/***********************************************
* @brief : 菜单链表新加页
* @param : void
* @return: add_page
* @date  : 2025年3月20日18:43:16
* @author: SJX
************************************************/
void Menu_Push_Node(MenuPage *new_page)
{
    My_Clear();
    my_assert(new_page != NULL); // 先判断 new_page 是否为 NULL

    MenuPage_Linked_List *q = (MenuPage_Linked_List *)malloc(sizeof(MenuPage_Linked_List));

    my_assert(q != NULL);

    q->page = new_page;
    q->next = NULL;

    if(menu_head_page_node == NULL)
    {
        menu_head_page_node = q;
    }
    else
    {
//        for(p=menu_head_page_node;p->next!=NULL;p=p->next);//找到最后一个结点
//        p->next = q;
        menu_head_page_node->page->line_num = menu_global_line;
        q->next = menu_head_page_node;
        menu_head_page_node = q;
    }

//    menu_global_line
}

/***********************************************
* @brief : 菜单链表删除结点
* @param : void
* @return: add_page
* @date  : 2025年3月20日18:43:16
* @author: SJX
************************************************/
void Menu_Pop_Node(void)
{
    MenuPage_Linked_List *p;
    my_assert(menu_head_page_node != NULL);

    if(menu_head_page_node->next == NULL)
        return;

    My_Clear();

    menu_head_page_node->page->open_status = 0;
    menu_head_page_node->page->line_num = menu_global_line;

    p = menu_head_page_node->next;
    free(menu_head_page_node);

    menu_head_page_node = p;

    menu_head_page_node->page->open_status = 0;
}


/***********************************************
* @brief : 获取页的行数
* @param : void
* @return: page
* @date  : 2025年3月20日16:31:35
* @author: SJX
************************************************/
uint8 Menu_Get_Page_LineNumMAX(MenuPage* Page)
{
    uint8 i = 0;
    if(Page->line_num_max != 0)
    {
        return Page->line_num_max;
    }
    else
    {
        Page->line_num = 1;
        for(; Page->line[i].line_name[0] != '.'; i++);
        Page->line_num_max = i;
        return Page->line_num_max;
    }
}

/***********************************************
* @brief : 菜单初始化
* @param : void
* @return: page
* @date  : 2025年3月20日16:32:05
* @author: SJX
************************************************/
void Menu_Init(void)
{
    Main_Page_Init();
}

/***********************************************
* @brief : 菜单参数配置子页面行数限幅函数
* @param : *line              需要配置的行的地址，记得&
*           line_max          最大行
* @return: void
* @
* @date  : 2024.10.18
* @author: SJX
************************************************/
void Menu_Val_CFG_Limit(uint8 *line, uint8 line_max)
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

/*****************内部调用,用户无需在意,后续自行优化*******************/
void menu_Val_CFG_clear(uint8 *page_start_row);
void menu_Val_CFG_Flush(float *CFG_val, uint16 page_start_row,  bool temp_based_flag);
void menu_Val_CFG_Arrow_Show(uint16 page_start_row,uint16 line_num);
/*****************内部调用,用户无需在意,后续自行优化*******************/

#define VAL_VFG_SHOW_NUM_BIT          6
#define VAL_VFG_SHOW_POINT_BIT        6
#define VAL_VFG_SHOW_TOTAL_LINE       6                     //总行数，包含变量固定行和几个数字行和exit行
#define LINE_MAX                      VAL_VFG_SHOW_TOTAL_LINE-1
uint8 up_down_flag = 0;         //调参菜单在上面还是在下面，默认为0在下面，为1在上面
float basic_1, basic_10, basic_100 ;
uint8 menu_Val_CFG_line;
void menu_Val_CFG(float *CFG_val, float basic_val )
{
    menu_head_page_node->page->line_num = menu_global_line;
    menu_cfg_flag = 1;
    uint8 flush_flag;
    uint8 CFG_stop_flag = 0;
    menu_Val_CFG_line = 1;
    bool based_flag = 0;                            //选中标志位，选中为1，不选中为0
    basic_1 = basic_val;
    basic_10 = basic_val / 10 ;
    basic_100 = basic_val / 100;

    uint8 page_start_row;

    page_start_row = menu_global_line*18;
//    printf("%d\r\n", page_start_row);
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
//        menu_key_event == menu_release?flush_flag = 0:flush_flag = 1;
        if(menu_key_event == menu_release)
        {
            flush_flag = 0;
        }
        else
            flush_flag = 1;
        if(menu_key_event == menu_back)
        {
            menu_key_event = menu_release;
            CFG_stop_flag = 1;
            ips200_clear();
            menu_cfg_flag = 0;
            menu_head_page_node->page->open_status = 0;
        }
        if((flush_flag == 1 || switch_encoder_change_num != 0) && CFG_stop_flag == 0)
        {
            if(menu_key_event == menu_yes)
            {
                menu_key_event = menu_release;
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
                        Beep_ShortRing();
                        break;

                    case 5:
                        CFG_stop_flag = 1;
                        menu_cfg_flag = 0;
                        menu_head_page_node->page->open_status = 0;
                        break;
                }
            }
            if(If_Switch_Encoder_Change() == 1)
            {
                if(based_flag == 0)
                {
                    menu_Val_CFG_line += switch_encoder_change_num;
                    Menu_Val_CFG_Limit(&menu_Val_CFG_line, LINE_MAX);
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
//            Flash_WriteAllVal();
        }
    }
    ips200_clear();
}

/***********************************************
* @brief : 菜单参数配置子页面清屏函数(置黑)并确定起始行
* @param : page_start_row       起始行
* @return: void
* @date  : 2024.10.18
* @author: SJX
************************************************/
void menu_Val_CFG_clear(uint8 *page_start_row)
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
* @brief : 菜单参数配置子页面变量刷新函数
* @param : *CFG_val              需要配置的值的地址，记得&
*           page_start_row       起始行
* @return: void
* @
* @date  : 2024.10.18
* @author: SJX
************************************************/
void menu_Val_CFG_Flush(float *CFG_val, uint16 page_start_row,  bool temp_based_flag)
{
        ips200_show_float(0, page_start_row + 18*0, *CFG_val + 0.0000001, VAL_VFG_SHOW_NUM_BIT, VAL_VFG_SHOW_POINT_BIT);
        menu_Val_CFG_Arrow_Show(page_start_row, menu_Val_CFG_line);
        if(temp_based_flag == 1)
        {
            if(menu_Val_CFG_line == 1)  ips200_show_float_color(18, page_start_row + 18 * menu_Val_CFG_line, basic_1+ 0.0000001, VAL_VFG_SHOW_NUM_BIT, VAL_VFG_SHOW_POINT_BIT,RGB565_RED);
            else                ips200_show_float_color(18, page_start_row + 18 * 1, basic_1+ 0.0000001, VAL_VFG_SHOW_NUM_BIT, VAL_VFG_SHOW_POINT_BIT,RGB565_WHITE);

            if(menu_Val_CFG_line == 2)  ips200_show_float_color(18, page_start_row + 18 * menu_Val_CFG_line, basic_10+ 0.0000001, VAL_VFG_SHOW_NUM_BIT, VAL_VFG_SHOW_POINT_BIT,RGB565_RED);
            else                ips200_show_float_color(18, page_start_row + 18 * 2, basic_10+ 0.0000001, VAL_VFG_SHOW_NUM_BIT, VAL_VFG_SHOW_POINT_BIT,RGB565_WHITE);

            if(menu_Val_CFG_line == 3)  ips200_show_float_color(18, page_start_row + 18 * menu_Val_CFG_line, basic_100+ 0.0000001, VAL_VFG_SHOW_NUM_BIT, VAL_VFG_SHOW_POINT_BIT,RGB565_RED);
            else                ips200_show_float_color(18, page_start_row + 18 * 3, basic_100+ 0.0000001, VAL_VFG_SHOW_NUM_BIT, VAL_VFG_SHOW_POINT_BIT,RGB565_WHITE);

            if(menu_Val_CFG_line == 4)  ips200_show_string_color(18, page_start_row + 18 * menu_Val_CFG_line, "empty", RGB565_RED);
            else                ips200_show_string_color(18, page_start_row + 18 * 4, "empty", RGB565_WHITE);

            if(menu_Val_CFG_line == 5)  ips200_show_string_color(18, page_start_row + 18 * menu_Val_CFG_line, "exit", RGB565_RED);
            else                ips200_show_string_color(18, page_start_row + 18 * 5, "exit", RGB565_WHITE);

        }
        else
        {
            ips200_show_float(18, page_start_row + 18*1, basic_1   + 0.0000001 , VAL_VFG_SHOW_NUM_BIT, VAL_VFG_SHOW_POINT_BIT);
            ips200_show_float(18, page_start_row + 18*2, basic_10  + 0.0000001, VAL_VFG_SHOW_NUM_BIT, VAL_VFG_SHOW_POINT_BIT);
            ips200_show_float(18, page_start_row + 18*3, basic_100 + 0.0000001, VAL_VFG_SHOW_NUM_BIT, VAL_VFG_SHOW_POINT_BIT);
            ips200_show_string(18, page_start_row + 18*5, "exit");
            ips200_show_string(18, page_start_row + 18*4, "empty");
        }

//    uint8 i;
//    i = Key_IfEnter();
//    val_cfg_key_ifenter_flag += i;
    key_clear_all_state();
}

/***********************************************
* @brief : 菜单参数配置子页面箭头显示
* @param : *line              需要配置的行的地址，记得&
*           line_max          最大行
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
            // 当前行显示 "->"
            ips200_show_string(0, page_start_row + i * 18, "->");
        }
        else
        {
            // 其他行显示空格
            ips200_show_string(0, page_start_row + i * 18, "  ");
        }
    }
}
