/*
 * menu.h
 *
 *  Created on: 2025年3月19日
 *      Author: sun
 */

#ifndef CODE_MENU_MENU_H_
#define CODE_MENU_MENU_H_

#include "zf_device_ips200.h"
#include "MYKEY.h"

#define DEFAULT_BACKGROUD   RGB565_BLACK
#define DEFAULT_BRUSH       RGB565_WHITE
#define SELECTED_BRUSH      RGB565_RED
#define MENU_KEY            MY_KEY_1

#define my_assert(x)        zf_assert(x)

typedef enum
{
    menu_release                    ,
    menu_yes                        ,
    menu_back                       ,
} Menu_Event;

extern uint8 menu_key_event;


enum LineExtendsType{
    STATIC_FUNC_RUN_TYPE,       //常态函数,默认直接执行
    ENTER_FUNC_RUN_TYPE,        //需要按下执行的函数
    PAGE_JUMP_TYPE,
    FLOAT_VALUE_SHOW_TYPE,
    INT_VALUE_SHOW_TYPE,
    CONFIG_VALUE_SHOW_TYPE,
    FLOAT_VALUE_EDIT_TYPE
};

typedef union {
    void (*void_func)(void);
    void (*int_func)(int*);
    void (*float_func)(float*);
    void (*float_float_func)(float*, float);
} ActionFunction;

typedef union {
    struct { float *show_value; } float_value_show_line;
    struct { int *show_value; } int_value_show_line;
    struct { uint8 *show_value; } config_value_show_line;
    struct { float *edit_value; float basic_val; } float_value_edit_line;
} LineExtends;

typedef struct {
    const char *line_name;                          // 行名称
    enum LineExtendsType line_type;                 // 行类型
    ActionFunction action;                          // 统一的函数指针
    LineExtends line_extends;   // 具名 union
    int display_line_count;      // 显示的行数（可选）
    int display_x_start;         // 显示的 x 坐标起始点（可选）
} MenuLine;

typedef struct{
    const char *page_name;       // 行名称
    uint8       line_num;
    uint8       line_num_max;
    uint8       open_status ;
    MenuLine    *line   ;
}MenuPage;

// 菜单页面结构体（双向链表）
typedef struct MenuPage {
//    const char *page_name;
    MenuPage *page;
//    struct MenuPage *prev;
    struct MenuPage *next;
} MenuPage_Linked_List;

void Menu_Push_Node(MenuPage *new_page);
void Menu_Pop_Node(void);
void Menu_Event_Flush(void);
uint8 Menu_Get_Page_LineNumMAX(MenuPage* Page);
void MENU_RUN(void);
void Menu_Init(void);
void Menu_Val_CFG_Limit(uint8 *line, uint8 line_max);
void Menu_Key_Process(void);
void menu_Val_CFG(float *CFG_val, float basic_val );

static inline void My_Clear(void) {
    ips200_clear();
}

static inline void My_Full(uint16 color) {
    ips200_full(color);
}

static inline void My_Set_Dir(ips200_dir_enum dir) {
    ips200_set_dir(dir);
}

static inline void My_Set_Font(ips200_font_size_enum font) {
    ips200_set_font(font);
}

static inline void My_Set_Color(uint16 pen, uint16 bgcolor) {
    ips200_set_color(pen, bgcolor);
}

static inline void My_Draw_Point(uint16 x, uint16 y, uint16 color) {
    ips200_draw_point(x, y, color);
}

static inline void My_Draw_Line(uint16 x1, uint16 y1, uint16 x2, uint16 y2, uint16 color) {
    ips200_draw_line(x1, y1, x2, y2, color);
}

static inline void My_Show_Char(uint16 x, uint16 y, char dat) {
    ips200_show_char(x, y, dat);
}

static inline void My_Show_String(uint16 x, uint16 y, const char dat[]) {
    ips200_show_string(x, y, dat);
}

static inline void My_Show_Int(uint16 x, uint16 y, int32 dat, uint8 num) {
    ips200_show_int(x, y, dat, num);
}

static inline void My_Show_Uint(uint16 x, uint16 y, uint32 dat, uint8 num) {
    ips200_show_uint(x, y, dat, num);
}

static inline void My_Show_Float(uint16 x, uint16 y, double dat, uint8 num, uint8 pointnum) {
    ips200_show_float(x, y, dat, num, pointnum);
}

static inline void My_Show_Binary_Image(uint16 x, uint16 y, const uint8 *image, uint16 width, uint16 height, uint16 dis_width, uint16 dis_height) {
    ips200_show_binary_image(x, y, image, width, height, dis_width, dis_height);
}

static inline void My_Show_Gray_Image(uint16 x, uint16 y, const uint8 *image, uint16 width, uint16 height, uint16 dis_width, uint16 dis_height, uint8 threshold) {
    ips200_show_gray_image(x, y, image, width, height, dis_width, dis_height, threshold);
}

static inline void My_Show_RGB565_Image(uint16 x, uint16 y, const uint16 *image, uint16 width, uint16 height, uint16 dis_width, uint16 dis_height, uint8 color_mode) {
    ips200_show_rgb565_image(x, y, image, width, height, dis_width, dis_height, color_mode);
}

static inline void My_Show_Wave(uint16 x, uint16 y, const uint16 *wave, uint16 width, uint16 value_max, uint16 dis_width, uint16 dis_value_max) {
    ips200_show_wave(x, y, wave, width, value_max, dis_width, dis_value_max);
}

static inline void My_Show_Chinese(uint16 x, uint16 y, uint8 size, const uint8 *chinese_buffer, uint8 number, uint16 color) {
    ips200_show_chinese(x, y, size, chinese_buffer, number, color);
}

static inline void My_Init(ips200_type_enum type_select) {
     ips200_init(type_select);
}

static inline void My_Show_Char_Color(uint16 x, uint16 y, char dat, uint16 color) {
    ips200_show_char_color(x, y, dat, color);
}

static inline void My_Show_String_Color(uint16 x, uint16 y, const char dat[], uint16 color) {
    ips200_show_string_color(x, y, dat, color);
}

static inline void My_Show_Int_Color(uint16 x, uint16 y, int32 dat, uint8 num, uint16 color) {
    ips200_show_int_color(x, y, dat, num, color);
}

static inline void My_Show_Uint_Color(uint16 x, uint16 y, uint32 dat, uint8 num, uint16 color) {
    ips200_show_uint_color(x, y, dat, num, color);
}

static inline void My_Show_Float_Color(uint16 x, uint16 y, float dat, uint8 num, uint8 pointnum, uint16 color) {
    ips200_show_float_color(x, y, dat, num, pointnum, color);
}

static inline void My_Show_String_Centered(uint16 y, const char dat[]) {
    ips200_show_string_centered(y, dat);
}


#endif /* CODE_MENU_MENU_H_ */
