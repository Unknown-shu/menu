/*
 * MyKey.h
 *
 *  Created on: 2025年3月19日
 *      Author: sun
 */

#ifndef CODE_MYKEY_MYKEY_H_
#define CODE_MYKEY_MYKEY_H_

#include "zf_driver_gpio.h"
#include "MyHeadFile.h"

#define MY_KEY_LIST                    {P20_9, P00_9, P21_7}

#define MY_KEY_RELEASE_LEVEL           (GPIO_HIGH)                                 // 按键的默认状态 也就是按键释放状态的电平
#define MY_KEY_MAX_SHOCK_PERIOD        (20       )                                 // 按键消抖检测时长 单位毫秒 低于这个时长的信号会被认为是杂波抖动
#define MY_KEY_LONG_PRESS_PERIOD       (250     )

typedef enum
{
    MY_KEY_1,
    MY_KEY_2,
    MY_KEY_3,
    MY_KEY_NUMBER,
}my_key_index_enum;

typedef enum
{
    MY_KEY_RELEASE,                                                                // 按键释放状态
    MY_KEY_SHORT_PRESS,                                                            // 按键短按状态
    MY_KEY_LONG_PRESS,                                                             // 按键长按状态
}my_key_state_enum;

extern uint8 key_long_press_flag[];

void                my_key_scanner             (void);                                 // 按键状态扫描
my_key_state_enum   my_key_get_state           (my_key_index_enum key_n);                 // 获取按键状态
void                my_key_clear_state         (my_key_index_enum key_n);                 // 清除指定按键状态
void                my_key_clear_all_state     (void);                                 // 清除所有按键状态
void                my_key_init                (uint32 period);                        // 按键初始化
uint8               my_Key_IfEnter(void);

#endif /* CODE_MYKEY_MYKEY_H_ */
