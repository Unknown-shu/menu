/*********************************************************************************************************************
* TC377 Opensource Library 即（TC377 开源库）是一个基于官方 SDK 接口的第三方开源库
* Copyright (c) 2022 SEEKFREE 逐飞科技
*
* 本文件是 TC377 开源库的一部分
*
* TC377 开源库 是免费软件
* 您可以根据自由软件基金会发布的 GPL（GNU General Public License，即 GNU通用公共许可证）的条款
* 即 GPL 的第3版（即 GPL3.0）或（您选择的）任何后来的版本，重新发布和/或修改它
*
* 本开源库的发布是希望它能发挥作用，但并未对其作任何的保证
* 甚至没有隐含的适销性或适合特定用途的保证
* 更多细节请参见 GPL
*
* 您应该在收到本开源库的同时收到一份 GPL 的副本
* 如果没有，请参阅<https://www.gnu.org/licenses/>
*
* 额外注明：
* 本开源库使用 GPL3.0 开源许可证协议 以上许可申明为译文版本
* 许可申明英文版在 libraries/doc 文件夹下的 GPL3_permission_statement.txt 文件中
* 许可证副本在 libraries 文件夹下 即该文件夹下的 LICENSE 文件
* 欢迎各位使用并传播本程序 但修改内容时必须保留逐飞科技的版权声明（即本声明）
*
* 文件名称          my_device_key
* 公司名称          成都逐飞科技有限公司
* 版本信息          查看 libraries/doc 文件夹内 version 文件 版本说明
* 开发环境          ADS v1.9.20
* 适用平台          TC377TP
* 店铺链接          https://seekfree.taobao.com/
*
* 修改记录
* 日期              作者                备注
* 2022-11-03       pudding            first version
* 2023-04-28       pudding            增加中文注释说明
********************************************************************************************************************/

#include "MYKEY.h"

static uint32               scanner_period = 0;
static uint32               my_key_press_time[MY_KEY_NUMBER];
static my_key_state_enum    my_key_state[MY_KEY_NUMBER];
static const gpio_pin_enum  my_key_index[MY_KEY_NUMBER] = MY_KEY_LIST;

uint8 key_long_press_flag[MY_KEY_NUMBER] = {open_status};

void my_key_scanner (void)
{
    uint8 i = 0;
    for(i = 0; MY_KEY_NUMBER > i; i++)
    {
        if(MY_KEY_RELEASE_LEVEL != gpio_get_level(my_key_index[i]))
        {
            my_key_press_time[i] ++;
            if(key_long_press_flag[i] == close_status)
            {
                my_key_state[i] = MY_KEY_RELEASE;
            }
            else if((MY_KEY_LONG_PRESS_PERIOD / scanner_period <= my_key_press_time[i]) )
            {
                my_key_state[i] = MY_KEY_LONG_PRESS;
                Key_Timer_ShortRing();
                key_long_press_flag[i] = close_status;
            }
        }
        else
        {
            if(key_long_press_flag[i] == open_status)
            {
                if((MY_KEY_LONG_PRESS != my_key_state[i]) && (MY_KEY_MAX_SHOCK_PERIOD / scanner_period <= my_key_press_time[i]))
                {
                    my_key_state[i] = MY_KEY_SHORT_PRESS;
                    Key_Timer_ShortRing();
                }
                else
                {
                    my_key_state[i] = MY_KEY_RELEASE;
                }
            }
            my_key_press_time[i] = 0;
            key_long_press_flag[i] = open_status;
        }
    }
}

my_key_state_enum my_key_get_state (my_key_index_enum key_n)
{
    return my_key_state[key_n];
}

void my_key_clear_state (my_key_index_enum key_n)
{
    my_key_state[key_n] = MY_KEY_RELEASE;
}

void my_key_clear_all_state (void)
{
    for (uint8 i = 0; i < MY_KEY_NUMBER; i++)
    {
        my_key_state[i] = MY_KEY_RELEASE;
    }
}

void my_key_init (uint32 period)
{
    zf_assert(0 < period);
    uint8 loop_temp = 0;
    for(loop_temp = 0; MY_KEY_NUMBER > loop_temp; loop_temp++)
    {
        gpio_init(my_key_index[loop_temp], GPI, GPIO_HIGH, GPI_PULL_UP);
        my_key_state[loop_temp] = MY_KEY_RELEASE;
    }
    scanner_period = period;
}

uint8 My_Key_IfEnter(void)
{
    for (uint8 i = 0; i < MY_KEY_NUMBER; i++)
    {
        if(my_key_get_state((my_key_index_enum)i) != MY_KEY_RELEASE)
            return 1;
    }
    return 0;
}
