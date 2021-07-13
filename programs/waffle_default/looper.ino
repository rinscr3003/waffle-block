#include <WiFi.h>
#include "time.h"

const char* ntpServer = "pool.ntp.org";
const long  gmtOffset_sec = 3600 * 8;
const int   daylightOffset_sec = 0;

void TaskNTP(void *pvParameters)
{
  (void) pvParameters;
  for (;;)
  {
    while (WiFi.status() != WL_CONNECTED) {
      vTaskDelay(500);
      Serial.println("[NTP] Waiting for WiFi...");
    }
    Serial.println("[NTP] WiFi CONNECTED, updating time...");
    //init and get the time
    configTime(gmtOffset_sec, daylightOffset_sec, ntpServer);
    struct tm timeinfo;
    if (!getLocalTime(&timeinfo)) {
      Serial.println("[NTP] Failed to obtain time");
      isTime = false;
      vTaskDelay(100);
      continue;
    }
    Serial.print("[NTP] Now is ");
    Serial.println(&timeinfo, "%A, %B %d %Y %H:%M:%S");
    vTaskDelay(3600 * 1000);
  }
}
