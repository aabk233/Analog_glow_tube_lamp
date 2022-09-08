#ifndef __WS2812_H
#define __WS2812_H

#include<F:\Data\ESP32\Project\propro\.pio\libdeps\esp32dev\Freenove WS2812 Lib for ESP32\src\Freenove_WS2812_Lib_for_ESP32.h>

#define COLOR_NUM 8
#define LEDS_NUM 180 //彩灯数目
#define LEDS_PIN 2   //输出引脚
#define CHANNEL 0   //通道

Freenove_ESP32_WS2812 strip = Freenove_ESP32_WS2812(LEDS_NUM, LEDS_PIN, CHANNEL, TYPE_GRB);//申请一个彩灯控制对象

void DisplayTime(void);
void Colorful_disp(void);




#endif