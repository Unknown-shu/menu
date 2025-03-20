#include "MYENCODER.h"

int switch_encoder_num = 0;
int switch_encoder_change_num = 0;
uint8 switch_encode_bring_flag;
uint8 switch_encode_change_get_buff_flag = 0;                   //变化缓冲，谨防变化未用上就将变化值清零

void MyEncoder_Init(void)
{
//    encoder_dir_init(TIM2_ENCODER, ENCODER_L, ENCODER_DIR_L);//左轮编码器
//    encoder_dir_init(TIM6_ENCODER, ENCODER_R, ENCODER_DIR_R);//右轮编码器
    encoder_quad_init(TIM3_ENCODER, Switch_ENCODER_L, Switch_ENCODER_R);
//    encoder_dir_init(TIM3_ENCODER, Switch_ENCODER_L, Switch_ENCODER_R);

}
//-------------------------------------------------------------------------------------------------------------------
//  @brief      编码器采集
//  @param      gptn    ：编码器对应编号
//  @param      n       ：n次均值滤波
//  @param      direct  ：1或者0 决定 编码器的正负号
//  @return     int16
//  @note       要是编码器方向反了就把direct改一下 1或者0
//-------------------------------------------------------------------------------------------------------------------
int16 Encoder_MTM(encoder_index_enum gptn,int n,uint8 direct)
{
    int16 Coder = 0;
    int16 CoderOut = 0;
    switch(gptn)
    {
        case TIM2_ENCODER:
            for(int i = 0;i < n;i++)
            {
                if(direct)
                {
                    Coder -=  encoder_get_count(TIM2_ENCODER);
                }
                else
                {
                    Coder +=  encoder_get_count(TIM2_ENCODER);
                }

            }
            CoderOut = Coder/n;
            break;
        case TIM6_ENCODER:
            for(int i = 0;i < n;i++)
            {
                if(direct)
                {
                    Coder +=  encoder_get_count(TIM6_ENCODER);
                }
                else
                {
                    Coder -=  encoder_get_count(TIM6_ENCODER);
                }

            }
            CoderOut = Coder/n;
            break;
        case TIM3_ENCODER:
            for(int i = 0;i < n;i++)
            {
                if(direct)
                {
                    Coder +=  encoder_get_count(TIM3_ENCODER);
                }
                else
                {
                    Coder -=  encoder_get_count(TIM3_ENCODER);
                }

            }
            CoderOut = Coder/n;
            break;
        default:
            break;
    }
    encoder_clear_count(gptn);    //编码器清空

    return CoderOut;
}

/***********************************************
* @brief : 获取旋转编码器值
* @param : void
* @return: void
* @date  : 2024年11月6日12:23:25
* @author: SJX
************************************************/
void Get_Switch_Num(void)
{
    int tmp = 0;
    static int i = 0;
    static int encoder_cnt, timer_cnt, last_switch_encoder_num = 0;
    timer_cnt = -My_Switch_encoder_get_count(TIM3_ENCODER);
    encoder_clear_count(TIM3_ENCODER);

    if(abs(timer_cnt) < 4)
    {
        encoder_cnt += timer_cnt;
    }
    else
    {
        tmp = timer_cnt / 4;
        switch_encoder_num += tmp;
        tmp = timer_cnt % 4;
        encoder_cnt += tmp;
    }
    if(abs(encoder_cnt) >= 4)
    {
        tmp = encoder_cnt / 4;
        switch_encoder_num += tmp;
        tmp = encoder_cnt % 4;
        encoder_cnt = 0;
        encoder_cnt += tmp;
    }

    if((last_switch_encoder_num != switch_encoder_num ) && switch_encode_change_get_buff_flag == 0)
    {
        switch_encode_change_get_buff_flag = 1;
        switch_encoder_change_num = switch_encoder_num - last_switch_encoder_num;
        Beep_Timer_ShortRing();

    }
    else if((last_switch_encoder_num != switch_encoder_num )&& switch_encode_change_get_buff_flag == 1)
    {
        switch_encoder_change_num = switch_encoder_change_num + switch_encoder_num - last_switch_encoder_num;
        Beep_Timer_ShortRing();
    }
    if((last_switch_encoder_num == switch_encoder_num ) && switch_encode_change_get_buff_flag == 0)
    {
        switch_encoder_change_num = 0;
//        Beep_Stop();
    }
    last_switch_encoder_num = switch_encoder_num;
    if(encoder_cnt != 0)
    {
//        printf("Test\r\n");
        i++;
        if(i > 200)
        {
            i = 0;
            encoder_cnt = 0;
        }
    }
    else
        i = 0;
//    printf("%d, %d, %d, %d\r\n", switch_encoder_change_num, i,
//            last_switch_encoder_num, encoder_cnt);

}
/***********************************************
* @brief : 旋转编码器获取函数，仅用于旋转编码器
* @param : void
* @return: void
* @date  : 2024年11月6日12:26:53
* @author: SJX
************************************************/
int16 My_Switch_encoder_get_count (encoder_index_enum encoder_n)
{
    int16 encoder_data = 0;
    switch(encoder_n)
    {
        case TIM2_ENCODER: encoder_data = (int16)IfxGpt12_T2_getTimerValue(&MODULE_GPT120); break;
        case TIM3_ENCODER: encoder_data = (int16)IfxGpt12_T3_getTimerValue(&MODULE_GPT120); break;
        case TIM4_ENCODER: encoder_data = (int16)IfxGpt12_T4_getTimerValue(&MODULE_GPT120); break;
        case TIM5_ENCODER: encoder_data = (int16)IfxGpt12_T5_getTimerValue(&MODULE_GPT120); break;
        case TIM6_ENCODER: encoder_data = (int16)IfxGpt12_T6_getTimerValue(&MODULE_GPT120); break;
        default: encoder_data = 0;
    }
    return encoder_data;
}
/***********************************************
* @brief : 判断旋转编码器是否出现变化
* @param : void
* @return: uint8            1变化 0不变
* @date  : 2024年11月6日12:27:38
* @author: SJX
************************************************/
uint8 If_Switch_Encoder_Change(void)
{
    switch_encode_change_get_buff_flag = 0;
    if(switch_encoder_change_num != 0)
    {
        return 1;
    }
    else
    {
        return 0;
    }
}

