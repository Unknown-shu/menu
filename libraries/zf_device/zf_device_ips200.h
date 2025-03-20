/*********************************************************************************************************************
* TC377 Opensourec Library 即（TC377 开源库）是一个基于官方 SDK 接口的第三方开源库
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
* 文件名称          zf_device_ips200
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
* 2023-05-20       pudding            修复无法驱动并口两寸屏的问题
********************************************************************************************************************/
/********************************************************************************************************************
* 接线定义：
*                  ------------------------------------
*                  模块管脚             单片机管脚
*                  // 双排排针 并口两寸屏 硬件引脚
*                  RD                 查看 zf_device_ips200.h 中 IPS200_RD_PIN_PARALLEL8     宏定义
*                  WR                 查看 zf_device_ips200.h 中 IPS200_WR_PIN_PARALLEL8     宏定义
*                  RS                 查看 zf_device_ips200.h 中 IPS200_RS_PIN_PARALLEL8     宏定义
*                  RST                查看 zf_device_ips200.h 中 IPS200_RST_PIN_PARALLEL8    宏定义
*                  CS                 查看 zf_device_ips200.h 中 IPS200_CS_PIN_PARALLEL8     宏定义
*                  BL                 查看 zf_device_ips200.h 中 IPS200_BL_PIN_PARALLEL8     宏定义
*                  D0-D7              查看 zf_device_ips200.h 中 IPS200_Dx_PIN_PARALLEL8     宏定义
*                  VCC                3.3V电源
*                  GND                电源地
*
*                  // 单排排针 SPI 两寸屏 硬件引脚
*                  SCL                查看 zf_device_ips200.h 中 IPS200_SCL_PIN_SPI  宏定义
*                  SDA                查看 zf_device_ips200.h 中 IPS200_SDA_PIN_SPI  宏定义
*                  RST                查看 zf_device_ips200.h 中 IPS200_RST_PIN_SPI  宏定义
*                  DC                 查看 zf_device_ips200.h 中 IPS200_DC_PIN_SPI   宏定义
*                  CS                 查看 zf_device_ips200.h 中 IPS200_CS_PIN_SPI   宏定义
*                  BLk                查看 zf_device_ips200.h 中 IPS200_BLk_PIN_SPI  宏定义
*                  VCC                3.3V电源
*                  GND                电源地
*                  最大分辨率 320 * 240
*                  ------------------------------------
********************************************************************************************************************/

#ifndef _zf_device_ips200_h_
#define _zf_device_ips200_h_

#include "zf_common_typedef.h"

//==================================================定义 IPS200 基本配置================================================
#define IPS200_USE_SOFT_SPI             (0 )                                    // 默认使用硬件 SPI 方式驱动 建议使用硬件 SPI 方式驱动
#if IPS200_USE_SOFT_SPI                                                         // 这两段 颜色正常的才是正确的 颜色灰的就是没有用的
//====================================================软件 SPI 驱动====================================================
// 如果使用的是单排排针的两寸屏幕 SPI 驱动控制引脚 可以修改
#define IPS200_SOFT_SPI_DELAY           (0 )                                    // 软件 SPI 的时钟延时周期 数值越小 SPI 通信速率越快
#define IPS200_SCL_PIN                  (P15_3)                                 // 软件 SPI SCK 引脚
#define IPS200_SDA_PIN                  (P15_5)                                 // 软件 SPI MOSI 引脚
//====================================================软件 SPI 驱动====================================================
#else
//====================================================硬件 SPI 驱动====================================================
// 如果使用的是单排排针的两寸屏幕 SPI 驱动控制引脚 可以修改
#define IPS200_SPI_SPEED                (60*1000*1000)                          // 硬件 SPI 速率
#define IPS200_SPI                      (SPI_2           )                      // 硬件 SPI 号
#define IPS200_SCL_PIN_SPI              (SPI2_SCLK_P15_3 )                      // 硬件 SPI SCK 引脚
#define IPS200_SDA_PIN_SPI              (SPI2_MOSI_P15_5 )                      // 硬件 SPI MOSI 引脚
#define IPS200_SDA_IN_PIN_SPI           (SPI2_MISO_P15_4 )                      // 硬件 SPI MISO 引脚  IPS没有MISO引脚，但是这里任然需要定义，在spi的初始化时需要使用
//====================================================硬件 SPI 驱动====================================================
#endif
// 如果使用的是单排排针的两寸屏幕 SPI 驱动控制引脚 可以修改
#define IPS200_RST_PIN_SPI              (P15_1)                                 // 单排针(SPI)液晶复位引脚定义
#define IPS200_DC_PIN_SPI               (P15_0)                                 // 单排针(SPI)液晶命令位引脚定义
#define IPS200_CS_PIN_SPI               (P15_2)                                 // 单排针(SPI)液晶片选引脚定义
#define IPS200_BLk_PIN_SPI              (P15_4)                                 // 单排针(SPI)液晶背光引脚定义

// 如果使用的是双排排针的两寸屏幕 并口驱动控制引脚 可以修改
#define IPS200_RD_PIN_PARALLEL8         (P15_3)                                 // 双排针(并口)液晶读取位引脚定义
#define IPS200_WR_PIN_PARALLEL8         (P15_5)                                 // 双排针(并口)液晶写入位引脚定义
#define IPS200_RST_PIN_PARALLEL8        (P15_0)                                 // 双排针(并口)液晶复位引脚定义
#define IPS200_RS_PIN_PARALLEL8         (P15_1)                                 // 双排针(并口)液晶命令位引脚定义
#define IPS200_CS_PIN_PARALLEL8         (P15_2)                                 // 双排针(并口)液晶片选引脚定义
#define IPS200_BL_PIN_PARALLEL8         (P15_4)                                 // 双排针(并口)液晶背光引脚定义
//并口驱动数据引脚 可以修改 如果你的屏幕是双排排针 这里的引脚用得到
//D0-D3四个数据引脚必须连续 例如C0-C3,C1-C4等等，
//D4-D7四个数据引脚必须连续 例如B0-B3,B1-B4等等。
//可以连接到不同端口的意思就是屏幕的D0-D3与C1-C4连接，D4-D7与B2-B5连接。
//切换引脚后注意修改IPS200_DATA_PORT1和IPS200_DATA_PORT2宏定义
#define IPS200_D0_PIN_PARALLEL8         (P11_9 )                                // 双排针(并口)液晶数据引脚D0
#define IPS200_D1_PIN_PARALLEL8         (P11_10)                                // 双排针(并口)液晶数据引脚D1
#define IPS200_D2_PIN_PARALLEL8         (P11_11)                                // 双排针(并口)液晶数据引脚D2
#define IPS200_D3_PIN_PARALLEL8         (P11_12)                                // 双排针(并口)液晶数据引脚D3
#define IPS200_D4_PIN_PARALLEL8         (P13_0 )                                // 双排针(并口)液晶数据引脚D4
#define IPS200_D5_PIN_PARALLEL8         (P13_1 )                                // 双排针(并口)液晶数据引脚D5
#define IPS200_D6_PIN_PARALLEL8         (P13_2 )                                // 双排针(并口)液晶数据引脚D6
#define IPS200_D7_PIN_PARALLEL8         (P13_3 )                                // 双排针(并口)液晶数据引脚D7

#define IPS200_DEFAULT_DISPLAY_DIR      (IPS200_PORTAIT)                        // 默认的显示方向
#define IPS200_DEFAULT_PENCOLOR         (RGB565_WHITE    )                        // 默认的画笔颜色
#define IPS200_DEFAULT_BGCOLOR          (RGB565_BLACK  )                        // 默认的背景颜色
#define IPS200_DEFAULT_DISPLAY_FONT     (IPS200_8X16_FONT)                      // 默认的字体模式

//定义数据端口所在PORT，切换引脚后务必根据引脚所在PORT进行更改   这里使用了两组端口进行组合  因此定义了两个引脚起始编号
#define IPS200_DATA_PORT1               (4)       //0:P00端口  1：P01端口  2：P02端口  3：P10端口  4：P11端口  5：P12端口  6：P13端口  7：P14端口  8：P15端口  9：P20端口  10：P21端口  11：P22端口  12：P23端口  13：P32端口  14：P33端口
#define IPS200_DATAPORT1                (get_port_out_addr(IPS200_DATA_PORT1))
#define DATA_START_NUM1                 (IPS200_D0_PIN_PARALLEL8&0x1f)          // 定义数据引脚的起始编号
#define IPS200_DATA_PORT2               (6)       //0:P00端口  1：P01端口  2：P02端口  3：P10端口  4：P11端口  5：P12端口  6：P13端口  7：P14端口  8：P15端口  9：P20端口  10：P21端口  11：P22端口  12：P23端口  13：P32端口  14：P33端口
#define IPS200_DATAPORT2                (get_port_out_addr(IPS200_DATA_PORT2))
#define DATA_START_NUM2                 (IPS200_D4_PIN_PARALLEL8&0x1f)          // 定义数据引脚的起始编号

// 控制语句
#define IPS200_RD(x)                    ((x) ? (gpio_high(IPS200_RD_PIN_PARALLEL8)) : (gpio_low(IPS200_RD_PIN_PARALLEL8)))
#define IPS200_WR(x)                    ((x) ? (gpio_high(IPS200_WR_PIN_PARALLEL8)) : (gpio_low(IPS200_WR_PIN_PARALLEL8)))
#define IPS200_RST(x)                   ((x) ? (gpio_high(ips_rst_pin))             : (gpio_low(ips_rst_pin)))
#define IPS200_BL(x)                    ((x) ? (gpio_high(ips_bl_pin))              : (gpio_low(ips_bl_pin)))
#define IPS200_RS(x)                    ((x) ? (gpio_high(IPS200_RS_PIN_PARALLEL8)) : (gpio_low(IPS200_RS_PIN_PARALLEL8)))
#define IPS200_DC(x)                    ((x) ? (gpio_high(IPS200_DC_PIN_SPI))       : (gpio_low(IPS200_DC_PIN_SPI)))
#define IPS200_CS(x)                    ((x) ? (gpio_high(IPS200_CS_PIN_SPI))       : (gpio_low(IPS200_CS_PIN_SPI)))
//==================================================定义 IPS200 基本配置================================================


//==================================================定义 IPS200 参数结构体===============================================
typedef enum
{
    IPS200_TYPE_SPI,                                                            // SPI 驱动
    IPS200_TYPE_PARALLEL8,                                                      // 并口驱动
}ips200_type_enum;

typedef enum
{
    IPS200_PORTAIT                      = 0,                                    // 竖屏模式
    IPS200_PORTAIT_180                  = 1,                                    // 竖屏模式  旋转180
    IPS200_CROSSWISE                    = 2,                                    // 横屏模式
    IPS200_CROSSWISE_180                = 3,                                    // 横屏模式  旋转180
}ips200_dir_enum;

typedef enum
{
    IPS200_6X8_FONT                     = 0,                                    // 6x8      字体
    IPS200_8X16_FONT                    = 1,                                    // 8x16     字体
    IPS200_16X16_FONT                   = 2,                                    // 16x16    字体 目前不支持
}ips200_font_size_enum;
extern  uint16  ips200_width_max;
extern  uint16  ips200_height_max;
//==================================================定义 IPS200 参数结构体===============================================


//==================================================声明 IPS200 基础函数================================================
void    ips200_clear                    (void);                                                                                // IPS200 清屏函数
void    ips200_full                     (const uint16 color);                                                                  // IPS200 屏幕填充函数
void    ips200_set_dir                  (ips200_dir_enum dir);                                                                 // IPS200 设置显示方向
void    ips200_set_font                 (ips200_font_size_enum font);                                                          // IPS200 设置显示字体
void    ips200_set_color                (const uint16 pen, const uint16 bgcolor);                                              // IPS200 设置显示颜色
void    ips200_draw_point               (uint16 x, uint16 y, const uint16 color);                                              // IPS200 画点函数
void    ips200_draw_line                (uint16 x_start, uint16 y_start, uint16 x_end, uint16 y_end, const uint16 color);      // IPS200 画线函数

void    ips200_show_char                (uint16 x, uint16 y, const char dat);
void    ips200_show_string              (uint16 x, uint16 y, const char dat[]);
void    ips200_show_int                 (uint16 x, uint16 y, const int32 dat, uint8 num);
void    ips200_show_uint                (uint16 x, uint16 y, const uint32 dat, uint8 num);
void    ips200_show_float               (uint16 x, uint16 y, const double dat, uint8 num, uint8 pointnum);

void    ips200_show_binary_image        (uint16 x, uint16 y, const uint8 *image, uint16 width, uint16 height, uint16 dis_width, uint16 dis_height);                      // IPS200 显示二值图像 数据每八个点组成一个字节数据
void    ips200_show_gray_image          (uint16 x, uint16 y, const uint8 *image, uint16 width, uint16 height, uint16 dis_width, uint16 dis_height, uint8 threshold);     // IPS200 显示 8bit 灰度图像 带二值化阈值
void    ips200_show_rgb565_image        (uint16 x, uint16 y, const uint16 *image, uint16 width, uint16 height, uint16 dis_width, uint16 dis_height, uint8 color_mode);   // IPS200 显示 RGB565 彩色图像

void    ips200_show_wave                (uint16 x, uint16 y, const uint16 *wave, uint16 width, uint16 value_max, uint16 dis_width, uint16 dis_value_max);                // IPS200 显示波形
void    ips200_show_chinese             (uint16 x, uint16 y, uint8 size, const uint8 *chinese_buffer, uint8 number, const uint16 color);                                 // IPS200 汉字显示

void    ips200_init                     (ips200_type_enum type_select);                                                         // 2寸 IPS液晶初始化

void    ips200_show_char_color          (uint16 x, uint16 y, const char dat,const uint16 color);
void    ips200_show_string_color        (uint16 x, uint16 y, const char dat[],const uint16 color);
void    ips200_show_int_color           (uint16 x, uint16 y, const int32 dat, uint8 num,const uint16 color);
void    ips200_show_uint_color          (uint16 x, uint16 y, const uint32 dat, uint8 num,const uint16 color);
void    ips200_show_float_color         (uint16 x, uint16 y, const float dat, uint8 num, uint8 pointnum,const uint16 color);
void ips200_show_string_centered(uint16_t y, const char dat[]);
//extern void ips200_write_16bit_data_array (const uint16 *dat, uint32 len);
//==================================================声明 IPS200 基础函数================================================


//==================================================声明 IPS200 扩展函数================================================
//-------------------------------------------------------------------------------------------------------------------
// 函数简介     IPS200 显示小钻风图像
// 参数说明     p               图像数组指针
// 参数说明     width           图像实际宽度
// 参数说明     height          图像实际高度
// 返回参数     void
// 使用示例     ips200_displayimage7725(ov7725_image_binary[0], OV7725_W, OV7725_H);
// 备注信息     拓展的一键显示函数，默认无缩放，从屏幕坐标起始点开始显示
//-------------------------------------------------------------------------------------------------------------------
#define ips200_displayimage7725(p, width, height)       (ips200_show_binary_image(0, 0, (p), OV7725_W, OV7725_H, (width), (height)))
//-------------------------------------------------------------------------------------------------------------------
// 函数简介     IPS200 显示总钻风图像
// 参数说明     p               图像数组指针
// 参数说明     width           图像实际宽度
// 参数说明     height          图像实际高度
// 返回参数     void
// 使用示例     ips200_displayimage03x(mt9v03x_image[0], MT9V03X_W, MT9V03X_H);
// 备注信息     拓展的一键显示函数，默认无缩放，从屏幕坐标起始点开始显示
//-------------------------------------------------------------------------------------------------------------------
#define ips200_displayimage03x(p, width, height)        (ips200_show_gray_image(0, 0, (p), MT9V03X_W, MT9V03X_H, (width), (height), 0))
//-------------------------------------------------------------------------------------------------------------------
// 函数简介     IPS200 显示凌瞳图像
// 参数说明     p               图像数组指针
// 参数说明     width           图像实际宽度
// 参数说明     height          图像实际高度
// 返回参数     void
// 使用示例     ips200_displayimage8660(scc8660_image[0], SCC8660_W, SCC8660_H);
// 备注信息     拓展的一键显示函数，默认无缩放，从屏幕坐标起始点开始显示
//-------------------------------------------------------------------------------------------------------------------
#define ips200_displayimage8660(p, width, height)       (ips200_show_rgb565_image(0, 0, (p), SCC8660_W, SCC8660_H, (width), (height), 1))
//==================================================声明 IPS200 扩展函数================================================


#endif

