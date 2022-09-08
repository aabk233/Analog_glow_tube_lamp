#include<F:\Data\ESP32\Project\propro\include\ws2812\ws2812.h>
#include "F:\Data\ESP32\Project\propro\include\WiFiConnect\WiFiConnect.h"


int hourhigh[10][3]={{0,19,20},{1,18,21},{2,17,22},{3,16,23},{4,15,24},{5,14,25},{6,13,26},{7,12,27},{8,11,28},{9,10,29}};
int hourlow[10][3]={{39,40,59},{38,41,58},{37,42,57},{36,43,56},{35,44,55},{34,45,54},{33,46,53},{32,47,52},{31,48,51},{30,49,50}};
int minutehigh[10][3]={{60,79,80},{61,78,81},{62,77,82},{63,76,83},{64,75,84},{65,74,85},{66,73,86},{67,72,87},{68,71,88},{69,70,89}};
int minutelow[10][3]={{99,100,119},{98,101,118},{97,102,117},{96,103,116},{95,104,115},{94,105,114},{93,106,113},{92,107,112},{91,108,111},{90,109,110}};
int secondhigh[10][3]={{120,139,140},{121,138,141},{122,137,142},{123,136,143},{124,135,144},{125,134,145},{126,133,146},{127,132,147},{128,131,148},{129,130,149}};
int secondlow[10][3]={{159,160,179},{158,161,178},{157,162,177},{156,163,176},{155,164,175},{154,165,174},{153,166,173},{152,167,172},{151,168,171},{150,169,170}};
u8 m_color[COLOR_NUM][3] = { {255, 0, 0}, {122,122,0},{0, 255, 0},{0,122,122}, {0, 0, 255},{122,0,122},{255, 255, 255},{0, 0, 0} };//彩灯颜色数组

extern struct tm timeinfo;

void DisplayTime(void)
{
    for(int i=0;i<60;i++)
    {
    strip.setLedColorData(hourhigh[i/10][0],36);
    strip.setLedColorData(hourhigh[i/10][1],72);
    strip.setLedColorData(hourhigh[i/10][2],108);
    strip.setLedColorData(hourlow[i%10][0],144);
    strip.setLedColorData(hourlow[i%10][1],180);
    strip.setLedColorData(hourlow[i%10][2],216);
    strip.show();//显示颜色
    delay(1000);
    strip.setLedColorData(hourhigh[i/10][0],0);
    strip.setLedColorData(hourhigh[i/10][1],0);
    strip.setLedColorData(hourhigh[i/10][2],0);
    strip.setLedColorData(hourlow[i%10][0],0);
    strip.setLedColorData(hourlow[i%10][1],0);
    strip.setLedColorData(hourlow[i%10][2],0);

    }  
}

void Colorful_disp(void)
{
    for (int j = 0; j < 255; j += 2)
     {
        for (int i = 0; i < LEDS_NUM; i++)
        {
            strip.setLedColorData(i, strip.Wheel((i * 256 / LEDS_NUM + j) & 255));//设置彩灯颜色数据
        }
        strip.show();//显示颜色
        delay(5);
     }
}