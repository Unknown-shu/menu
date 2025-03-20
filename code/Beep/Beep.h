#ifndef __BEEP_H__
#define __BEEP_H__

#include "MYHEADFILE.h"

#define Beep P33_10

extern uint8 g_switch_encoder_ring_flag;
extern uint8 g_key_ring_flag;

#define    SHORT_RING_TIME          3

void Beep_Start(void);
void Beep_Init(void);
void Beep_Stop(void);
void Beep_ShortRing(void);
void Beep_MediumRing(void);
void Beep_LongRing(void);
void Beep_Ring(uint16_t Time);
void Beep_Timer_ShortRing(void);
void Beep_Timer_ShortRing_Stop(void);
void Key_Timer_ShortRing(void);
void Key_Timer_ShortRing_Stop(void);

#endif
