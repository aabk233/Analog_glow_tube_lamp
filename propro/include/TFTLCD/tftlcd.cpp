#include "F:\Data\ESP32\Project\propro\include\TFTLCD\tftlcd.h"

TFT_eSPI tft;

void tftlcd18_init(void)
{
    tft.init();
    tft.fillScreen(TFT_BLUE);
     tft.drawCentreString("Font size 2", 120, 14, 2); // Draw text centre at position 80, 12 using font 2

    tft.drawCentreString("Font size 4", 120, 30, 4); // Draw text centre at position 80, 24 using font 4

    tft.drawCentreString("12.34", 120, 54, 6); // Draw text centre at position 80, 24 using font 6

    tft.drawCentreString("12.34 is in font size 6", 120, 92, 2);
}