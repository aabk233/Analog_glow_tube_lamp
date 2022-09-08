#include "F:\Data\ESP32\Project\propro\include\WiFiConnect\WiFiConnect.h"
//WIFI用户名和密码
//////////////////////////////////////
const char *ssid="what_phone";
const char *password="xuyijieyeah";

//获取时间
//////////////////////////////////////
const char *ntpServer = "ntp.aliyun.com";
const long gmtOffset_sec = 28800;
const int daylightOffset_sec = 0;

//获取天气
//////////////////////////////////////
DynamicJsonDocument doc(2048);//初始化存储json的空间
String tagethttp = "https://api.seniverse.com/v3/weather/now.json?key=SnRSx97s9WQdt1zlC&location=nanjing&language=en&unit=c";
HTTPClient https;
String payload;
int httpCode;
JsonObject results_0;
JsonObject results_0_now;
const char *temperature;
const char *weather;

struct tm timeinfo;

extern TFT_eSPI tft;

//
void printLocalTime()
{
    if (!getLocalTime(&timeinfo))
    {
        tft.println("Failed to obtain time");
        return;
    }
    tft.println(&timeinfo, "%F %T %A"); // 格式化输出
}

//连接WiFi，连接不上就一直连
void WiFi_connect(void)
{
	tft.print("WiFi Connecting...");
    WiFi.begin(ssid,password);
    while(WiFi.status()!=WL_CONNECTED)
    {
        delay(300);
        tft.print(".");
    }
	// Serial.println("WiFi connected");
	tft.println("WiFi Connected");
}

void WiFi_GetTime(void)
{
	configTime(gmtOffset_sec, daylightOffset_sec, ntpServer);
    printLocalTime();
}
void WiFi_GetWeather(void)
{
	https.begin(tagethttp);
	httpCode = https.GET();
	if(httpCode>0)
	{
		tft.print("Weather Get\r\n");
		payload = https.getString();
		deserializeJson(doc, payload);
		results_0 = doc["results"][0];
		results_0_now = results_0["now"];
		temperature=results_0_now["temperature"];
		weather=results_0_now["text"];
		tft.printf("Weather:%s\r\n",weather);
		tft.printf("Temperature:%s\r\n",temperature);
	}
	else
	{
		tft.print("Weater Get Failed\r\n");
	}
}

void WiFi_Disconnect(void)
{
	WiFi.disconnect(true);
	WiFi.mode(WIFI_OFF);
	tft.println("WiFi disconnected!");
}

