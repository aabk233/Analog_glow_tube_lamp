#ifndef __WIFICONNECT_H
#define __WIFICONNECT_H

#include "WiFi.h"
#include"time.h"
#include"HTTPClient.h"
#include"ArduinoJson.h"
#include"TFT_eSPI.h"

void WiFi_connect(void);
void WiFi_GetWeather(void);

#endif