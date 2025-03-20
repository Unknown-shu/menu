#include "Beep.h"

uint8 g_switch_encoder_ring_flag = 0;
uint8 g_key_ring_flag = 0;

void Beep_Init(void)
{
    gpio_init(P33_10, GPO, 0, GPO_PUSH_PULL);
    system_delay_init();
    pit_ms_init(CCU61_CH1, SHORT_RING_TIME);            //蜂鸣器中断
    pit_close(CCU61_CH1);
}


void Beep_Start(void)
{
    gpio_set_level(Beep, 1);
}

void Beep_Stop(void)
{
    gpio_set_level(Beep, 0);
}

void Beep_ShortRing(void)
{
    Beep_Start();
    system_delay_ms(SHORT_RING_TIME);
//    system_delay_us(200);
    Beep_Stop();
}

void Beep_MediumRing(void)
{
    Beep_Start();
    system_delay_ms(100);
    Beep_Stop();
}

void Beep_LongRing(void)
{
    Beep_Start();
    system_delay_ms(1000);
    Beep_Stop();
}

void Beep_Ring(uint16_t Time)
{
    Beep_Start();
    system_delay_ms(Time);
    Beep_Stop();
}
/***********************************************
* @brief : 定时器开关蜂鸣器函数
* @param : void
* @return: void
* @date  : 2024年11月6日12:24:04
* @author: SJX
************************************************/
void Beep_Timer_ShortRing(void)
{
    g_switch_encoder_ring_flag = 1;
    Beep_Start();
//    pit_start(CCU61_CH1);
//    pit_enable(CCU61_CH1);
}

void Beep_Timer_ShortRing_Stop(void)
{
    if(g_switch_encoder_ring_flag == 1)
    {
        g_switch_encoder_ring_flag = 0;
        Beep_Stop();
    }
}

/***********************************************
* @brief : 定时器开关蜂鸣器函数
* @param : void
* @return: void
* @date  : 2024年11月6日12:24:04
* @author: SJX
************************************************/
void Key_Timer_ShortRing(void)
{
    g_key_ring_flag = 1;
    Beep_Start();
//    pit_start(CCU61_CH1);
//    pit_enable(CCU61_CH1);
}

void Key_Timer_ShortRing_Stop(void)
{
    if(g_key_ring_flag == 1)
    {
        g_key_ring_flag = 0;
        Beep_Stop();
    }
}


