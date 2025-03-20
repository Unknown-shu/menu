#ifndef __MyEncoder_H
#define __MyEncoder_H

#include "MYHEADFILE.h"
#include "IfxGpt12_IncrEnc.h"

#define Switch_ENCODER_L         TIM3_ENCODER_CH1_P02_6        //右编码器计数引脚
#define Switch_ENCODER_R         TIM3_ENCODER_CH2_P02_7        //右编码器方向引脚

extern int switch_encoder_num;
extern int switch_encoder_change_num ;
extern uint8 switch_encode_bring_flag;
extern uint8 switch_encode_change_get_buff_flag;


void MyEncoder_Init(void);
//int16 Encoder_MTM(encoder_index_enum gptn,int n,uint8 direct);
void Get_Switch_Num(void);
int16 My_Switch_encoder_get_count (encoder_index_enum encoder_n);
uint8 If_Switch_Encoder_Change(void);



#endif
