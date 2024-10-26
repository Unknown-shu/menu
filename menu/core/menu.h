/*
 * menu.h
 *
 *  Created on: 2023年4月14日
 *      Author: 郑旭
 */

#ifndef _MENU_H_
#define _MENU_H_

#include "zf_common_headfile.h"
#include "mymenu.h"
#include "MyHeadFile.h"
#include "STDBOOL.H"

/*菜单，具体是哪个页面，这个留给用户自己去添加*/
typedef enum
{
    MAIN_PAGE = 0,
    Start_PAGE =1,
    NAVIGATION_PAGE   =2,
    Camera_PAGE = 3,


} MENU;


/*事件值，可以留给用户自己去定义，这里我定义了一些我需要的事件*/
typedef enum
{
    /*第一个事件为-1用来定义一个防止重复触发的值*/
    NULL_KEY_EVENT              =-1,
    RETRUN_KEY_Previous         = 0,
    RETRUN_KEY_Home             = 1,
    Yes                         = 2,
    UP                          = 3,  //上
    DOWN                        = 4,  //下
    Increase                    = 5,  //右
    Increase_fast               = 6,
    Reduce                      = 7,  //左
    Reduce_fast                 = 8,

} EVENT_CODE;

/*菜单操作结构体*/
typedef struct Menu
{
    /*当前正在执行的页面*/
    uint8 Current_Page ;
    uint8 Previous_Page ;
    /*当前触发的事件*/
    int KeyEvent ;
} Menu ;

extern struct Menu menu;



void Menu_init(void);
/*菜单初始化*/
void menu_init(struct Menu *handle, uint8 Page, int EVENT_CODE);
/*获取当前菜单*/
uint8 Get_Menu(struct Menu *handle);
/*菜单跳转*/
void Set_Menu(struct Menu *handle, uint8 Page);
/*获取当前发生的事件值*/
int Get_Event_Code(struct Menu *handle);
/*设置当前发生的事件值*/
void Set_Event_Code(struct Menu *handle, int Event_Code);
/*菜单选项选中循环*/
void pagelimit(int8 *page_num,uint8 page_num_max);
/*菜单处理*/
void Menu_Handler(struct Menu *handle);

void menu_Val_CFG(float *CFG_val, uint16 page_start_row, float basic_val );
void menu_Val_CFG_clear(uint16 *page_start_row);
void menu_Val_CFG_Flush(float *CFG_val, uint16 page_start_row, bool temp_based_flag);
void menu_Val_CFG_Limit(uint16 *line, uint16 line_max);
void menu_Val_CFG_Arrow_Show(uint16 page_start_row,uint16 line_num);

#endif /* CODE_CPU2_MENU_CORE_MENU_H_ */
