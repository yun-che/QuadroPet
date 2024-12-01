#ifndef __ALL_EXTERN_H__
#define __ALL_EXTERN_H__

#include <Arduino.h>

extern bool init_flag;

extern bool wifi_scan_flag;
extern bool wifi_connect_flag;
extern bool wifi_button_flag;
extern bool isconnect;
extern bool time_flag;
extern char wifi_name[64];
extern const char * wifi_password;
extern struct tm timeinfo;
extern bool weather_flag;

extern const char * songoptions;
extern char songname[64];
extern bool start_flag;
extern bool play_flag;
extern int voice;

extern int action;
extern int move_flag;
extern int mic_move_flag;

extern bool mic_flag;
extern bool serial_flag;

extern char * rate_buf;

#endif

//0 前进
//4 旋转
//5 波浪
//6 俯卧撑
//7 抖腿
//8 前倾
//9 后仰
//10 前倾+后仰
//11 圆周扭动