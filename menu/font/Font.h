

#ifndef CODE_MENU_FONT_H_
#define CODE_MENU_FONT_H_
#include "zf_common_headfile.h"
#include "mymenu.h"
#define dis_MT9V03X_W 128
#define dis_MT9V03X_H 64

#define PenColor RGB565_WHITE //画笔颜色
#define BackgroundColor RGB565_Gray //背景颜色

#define PenColor_else RGB565_RED //画笔颜色
#define BackgroundColor_else RGB565_Periwinkle  //背景颜色

#define RGB565_dianqing         0x4810  //靛青
#define RGB565_Silver           0XC618  //银色
#define RGB565_Gray             0X8410  //灰色
#define RGB565_SandBeige        0XE618  //沙棕
#define RGB565_Pansy            0X7014  //三色堇紫
#define RGB565_PeachPuff        0XFED7  //粉扑桃色
#define RGB565_Periwinkle       0XCE7F  //长春花色
#define RGB565_Pink             0XFE19  //粉色
#define RGB565_RED              0xF800  //红色
extern const uint8 chinese16[][16];
extern const uint8 zx[40960];

#endif /* CODE_MENU_FONT_H_ */
