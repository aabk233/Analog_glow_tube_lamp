// #include <Arduino.h>
// #include<F:\Data\ESP32\Project\propro\.pio\libdeps\esp32dev\Freenove WS2812 Lib for ESP32\src\Freenove_WS2812_Lib_for_ESP32.h>
// #include<F:\Data\ESP32\Project\propro\include\ws2812\ws2812.h>
// #include"\Data\ESP32\Project\propro\include\ws2812\ws2812.cpp"
// #include"F:\Data\ESP32\Project\propro\include\WiFiConnect\WiFiConnect.cpp"
// #include"F:\Data\ESP32\Project\propro\include\WiFiConnect\WiFiConnect.h"
// #include "F:\Data\ESP32\Project\propro\include\TFTLCD\tftlcd.h"
// #include"F:\Data\ESP32\Project\propro\include\TFTLCD\tftlcd.cpp"
// #include"TFT_eSPI.h"
// #include"lvgl.h"
// #include<stdio.h>
// #include<WiFi.h>
// #include <HTTPClient.h>

// hw_timer_t *TIMER = NULL;
// const uint16_t screenWidth = 320;
// const uint16_t screenHeight = 170
// ;

// void my_disp_init(void); // 挂载lvgl接口，设置buffer
// void IRAM_ATTR onTimer()  //中断函数
// {

// }
// void setup()
// {
//   //lvgl初始化
//   lv_init();
  
//   //TFTLCD初始化
//   tft.init();                               //初始化
//   tft.setRotation(1);
//   tft.fillScreen(TFT_BLACK);                //屏幕颜色
//   tft.setCursor(10, 10, 1);                 //设置起始坐标(10, 10)，2 号字体
//   tft.setTextColor(TFT_YELLOW);             //设置文本颜色为白色
//   tft.setTextSize(2);                       //设置文字的大小 (1~7)
//   //WS2812端口初始化为输出
//   pinMode(2,OUTPUT);
//   strip.setBrightness(255);
//   //扫描定时器初始化    
//   TIMER=timerBegin(0,80,true);
//   timerAttachInterrupt(TIMER, &onTimer, true);    //调用中断函数
//   timerAlarmWrite(TIMER, 100000, true);        //timerBegin的参数二 80位80MHZ，这里为200000  意思为0.2秒,5HZ
//   timerAlarmEnable(TIMER);
//   //串口0初始化
//   // strip.begin();
//   // Serial.begin(115200);
//   //WIFI连接，连接不上就一直连
//   WiFi_connect();
//   //WIFI获取时间
//   WiFi_GetTime();
//   //WIFI获取天气
//   WiFi_GetWeather();  
// }

// void loop()
// {

// }
#include"lvgl.h"
#include"lv_demo.h"
#include"lv_examples.h"
#include <TFT_eSPI.h>
/*If you want to use the LVGL examples,
  make sure to install the lv_examples Arduino library
  and uncomment the following line.
#include <lv_examples.h>
*/


// #include <lv_examples.h>  //在arduino中需要把  example文件夹里的所有文件放到lvgl/src文件夹里
/*如果你想使用 LVGL 示例，
   确保安装 lv_examples Arduino 库
   并取消注释以下行。

*/

#include <lv_demo.h>//这一行只有安装了lv_examples库才能直接用
/*Change to your screen resolution*/
/*改变你的屏幕分辨率*/
static const uint16_t screenWidth  = 480;
static const uint16_t screenHeight = 320;

static lv_disp_draw_buf_t draw_buf;
static lv_color_t buf[ screenWidth * 10 ];

TFT_eSPI tft = TFT_eSPI(screenWidth, screenHeight); /* TFT instance */

#if LV_USE_LOG != 0
/* Serial debugging */
void my_print(const char * buf)
{
    Serial.printf(buf);
    Serial.flush();
}
#endif

/* Display flushing 显示填充 */
void my_disp_flush( lv_disp_drv_t *disp, const lv_area_t *area, lv_color_t *color_p )
{
    uint32_t w = ( area->x2 - area->x1 + 1 );
    uint32_t h = ( area->y2 - area->y1 + 1 );

    tft.startWrite();
    tft.setAddrWindow( area->x1, area->y1, w, h );
    tft.pushColors( ( uint16_t * )&color_p->full, w * h, true );
    tft.endWrite();

    lv_disp_flush_ready( disp );
}

/*Read the touchpad*/
/*读取触摸板*/
// void my_touchpad_read( lv_indev_drv_t * indev_driver, lv_indev_data_t * data )
// {
//     uint16_t touchX, touchY;

//     bool touched = tft.getTouch( &touchX, &touchY, 600 );

//     if( !touched )
//     {
//         data->state = LV_INDEV_STATE_REL;
//     }
//     else
//     {
//         data->state = LV_INDEV_STATE_PR;

//         /*Set the coordinates*/
//         data->point.x = touchX;
//         data->point.y = touchY;

//         Serial.print( "Data x " );
//         Serial.println( touchX );

//         Serial.print( "Data y " );
//         Serial.println( touchY );
//     }
// }








void setup()
{
    Serial.begin( 115200 ); /* prepare for possible serial debug 为可能的串行调试做准备*/

    String LVGL_Arduino = "Hello Arduino! ";
    LVGL_Arduino += String('V') + lv_version_major() + "." + lv_version_minor() + "." + lv_version_patch();

    Serial.println( LVGL_Arduino );
    Serial.println( "I am LVGL_Arduino" );

    lv_init();

#if LV_USE_LOG != 0
    lv_log_register_print_cb( my_print ); /* register print function for debugging 注册打印功能以进行调试*/
#endif

    tft.begin();          /* TFT init TFT初始化*/
    tft.setRotation( 1 ); /* Landscape orientation, flipped 设置方向*/

    /*Set the touchscreen calibration data,
     the actual data for your display can be acquired using
     the Generic -> Touch_calibrate example from the TFT_eSPI library*/
    /*设置触摸屏校准数据，
      可以使用获取显示的实际数据
      TFT_eSPI 库中的 Generic -> Touch_calibrate 示例*/
    uint16_t calData[5] = { 187, 3596, 387, 3256, 5 };
    // tft.setTouch( calData );

    lv_disp_draw_buf_init( &draw_buf, buf, NULL, screenWidth * 10 );

    /*Initialize the display*/
    /*初始化显示*/
    static lv_disp_drv_t disp_drv;
    lv_disp_drv_init( &disp_drv );
    /*Change the following line to your display resolution*/
    /*将以下行更改为您的显示分辨率*/
    disp_drv.hor_res = screenWidth;
    disp_drv.ver_res = screenHeight;
    disp_drv.flush_cb = my_disp_flush;
    disp_drv.draw_buf = &draw_buf;
    lv_disp_drv_register( &disp_drv );

    /*Initialize the (dummy) input device driver*/
    /*初始化（虚拟）输入设备驱动程序*/
    static lv_indev_drv_t indev_drv;
    lv_indev_drv_init( &indev_drv );
    indev_drv.type = LV_INDEV_TYPE_POINTER;
    // indev_drv.read_cb = my_touchpad_read;
    lv_indev_drv_register( &indev_drv );


#if 1 // 如果是1 就只简单显示一个标签 如果是0则会跳过这个去编译下边的例子
    /* Create simple label */
    lv_obj_t *label = lv_label_create( lv_scr_act() );
    lv_label_set_text( label, LVGL_Arduino.c_str() );
    lv_obj_align( label, LV_ALIGN_CENTER, 0, 0 );
    lv_example_get_started_1();

   




     

#else
    /* Try an example from the lv_examples Arduino library
       make sure to include it as written above.
    lv_example_btn_1();
   */
    /* 尝试 lv_examples Arduino 库中的示例
        确保按照上面的说明包含它。
     lv_example_btn_1();
    */

    // lv_example_get_started_1();//反注释这个就能运行example文件夹里的一个示例函数

   
    // uncomment one of these demos 取消注释这些演示之一
    // lv_demo_widgets();            // OK
    // lv_demo_benchmark();          // OK
    // lv_demo_keypad_encoder();     // works, but I haven't an encoder
    // lv_demo_music();              // NOK
    // lv_demo_printer();
    // lv_demo_stress();             // seems to be OK
#endif
    Serial.println( "Setup done" );
}

void loop()
{
    lv_timer_handler(); /* let the GUI do its work 让 GUI 完成它的工作 */
    delay( 5 );
}