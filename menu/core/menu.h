/*
 * menu.h
 *
 *  Created on: 2023��4��14��
 *      Author: ֣��
 */

#ifndef _MENU_H_
#define _MENU_H_

#include "zf_common_headfile.h"
#include "mymenu.h"
#include "MyHeadFile.h"
#include "STDBOOL.H"

/*�˵����������ĸ�ҳ�棬��������û��Լ�ȥ���*/
typedef enum
{
    MAIN_PAGE = 0,
    Start_PAGE =1,
    NAVIGATION_PAGE   =2,
    Camera_PAGE = 3,


} MENU;


/*�¼�ֵ�����������û��Լ�ȥ���壬�����Ҷ�����һЩ����Ҫ���¼�*/
typedef enum
{
    /*��һ���¼�Ϊ-1��������һ����ֹ�ظ�������ֵ*/
    NULL_KEY_EVENT              =-1,
    RETRUN_KEY_Previous         = 0,
    RETRUN_KEY_Home             = 1,
    Yes                         = 2,
    UP                          = 3,  //��
    DOWN                        = 4,  //��
    Increase                    = 5,  //��
    Increase_fast               = 6,
    Reduce                      = 7,  //��
    Reduce_fast                 = 8,

} EVENT_CODE;

/*�˵������ṹ��*/
typedef struct Menu
{
    /*��ǰ����ִ�е�ҳ��*/
    uint8 Current_Page ;
    uint8 Previous_Page ;
    /*��ǰ�������¼�*/
    int KeyEvent ;
} Menu ;

extern struct Menu menu;



void Menu_init(void);
/*�˵���ʼ��*/
void menu_init(struct Menu *handle, uint8 Page, int EVENT_CODE);
/*��ȡ��ǰ�˵�*/
uint8 Get_Menu(struct Menu *handle);
/*�˵���ת*/
void Set_Menu(struct Menu *handle, uint8 Page);
/*��ȡ��ǰ�������¼�ֵ*/
int Get_Event_Code(struct Menu *handle);
/*���õ�ǰ�������¼�ֵ*/
void Set_Event_Code(struct Menu *handle, int Event_Code);
/*�˵�ѡ��ѡ��ѭ��*/
void pagelimit(int8 *page_num,uint8 page_num_max);
/*�˵�����*/
void Menu_Handler(struct Menu *handle);

void menu_Val_CFG(float *CFG_val, uint16 page_start_row, float basic_val );
void menu_Val_CFG_clear(uint16 *page_start_row);
void menu_Val_CFG_Flush(float *CFG_val, uint16 page_start_row, bool temp_based_flag);
void menu_Val_CFG_Limit(uint16 *line, uint16 line_max);
void menu_Val_CFG_Arrow_Show(uint16 page_start_row,uint16 line_num);

#endif /* CODE_CPU2_MENU_CORE_MENU_H_ */
