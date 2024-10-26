

#ifndef CODE_MENU_FONT_H_
#define CODE_MENU_FONT_H_
#include "zf_common_headfile.h"
#include "mymenu.h"
#define dis_MT9V03X_W 128
#define dis_MT9V03X_H 64

#define PenColor RGB565_WHITE //������ɫ
#define BackgroundColor RGB565_Gray //������ɫ

#define PenColor_else RGB565_RED //������ɫ
#define BackgroundColor_else RGB565_Periwinkle  //������ɫ

#define RGB565_dianqing         0x4810  //����
#define RGB565_Silver           0XC618  //��ɫ
#define RGB565_Gray             0X8410  //��ɫ
#define RGB565_SandBeige        0XE618  //ɳ��
#define RGB565_Pansy            0X7014  //��ɫ����
#define RGB565_PeachPuff        0XFED7  //������ɫ
#define RGB565_Periwinkle       0XCE7F  //������ɫ
#define RGB565_Pink             0XFE19  //��ɫ
#define RGB565_RED              0xF800  //��ɫ
extern const uint8 chinese16[][16];
extern const uint8 zx[40960];

#endif /* CODE_MENU_FONT_H_ */
