#include "MyHeadfile.h"
// /*
// * �հ�ҳ
// * ʹ��ʱ�����Null_line_number
// *       ��page_setting���null_page_process()
// *                      ��extern Null_line_number
// *
// */
//#include "zf_common_headfile.h"
//#include "mymenu.h"
//
//#define line_number Null_line_number
//
//void null_page_process(int Event_Code)
//{
//    line_number_max=2;
//
//   //��ʾ�˵�
//
//    ips200_show_string_color(105, 0,"Null", PenColor);
//
////  1.��ϵ���
//    if(line_number!=1) ips200_show_string_color(0, 18,"", PenColor);
//    else              ips200_show_string_color(0, 18,"", PenColor_else);
//////   2.�������
//    if(line_number!=2) ips200_show_string_color(0, 18*2,"", PenColor);
//     else              ips200_show_string_color(0, 18*2,"", PenColor_else);
////
//    if(line_number!=3) ips200_show_string_color(0, 18*3,"", PenColor);
//     else              ips200_show_string_color(0, 18*3,"", PenColor_else);
//
//    if(line_number!=4) ips200_show_string_color(0, 18*4,"", PenColor);
//     else              ips200_show_string_color(0, 18*4,"", PenColor_else);
//
//    //ָ������
//       if(key_get_state(KEY_1) == KEY_SHORT_PRESS)
//       {
//           gpio_set_level(Beep,1);
//           system_delay_ms(10);
//           gpio_set_level(Beep,0);
//           key_clear_state(KEY_1);
//           line_number--;//����ѡ������
//           pagelimit(&line_number,line_number_max);
//       }
//       //ָ������
//       if(key_get_state(KEY_3) == KEY_SHORT_PRESS)
//       {
//           gpio_set_level(Beep,1);
//           system_delay_ms(10);
//           gpio_set_level(Beep,0);
//           key_clear_state(KEY_3);
//           line_number++; //����ѡ������
//           pagelimit(&line_number,line_number_max);
//       }
//       //ָ������
//       if(key_get_state(KEY_2) == KEY_SHORT_PRESS)
//       {
//           gpio_set_level(Beep,1);
//           system_delay_ms(10);
//           gpio_set_level(Beep,0);
//           key_clear_state(KEY_2);
//           Set_Menu(&menu, MAIN_PAGE);
////           line_number=1;
//           ips200_clear();
//       }
//       //ָ�밴��
//       if(key_get_state(KEY_4) == KEY_SHORT_PRESS)
//       {
//           gpio_set_level(Beep,1);
//           system_delay_ms(10);
//           gpio_set_level(Beep,0);
//           switch(line_number)
//           {
//               case 1:
//                   Set_Menu(&menu, Start_PAGE);
////                   line_number=1;
//                   ips200_clear();
//
//                   break ;
//               case 2:
//
//                   break;
//               case 3:
//
//                   break;
//               case 4:
//
//                   break;
//               default:
//                   break ;
//           }
//           key_clear_state(KEY_4);
//       }
//
//   }
//
