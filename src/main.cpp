#include <Arduino.h>
#include <ESP8266WiFi.h>
#include "SensorHandler.h"
#include "PowerManagement.h"
#include "Settings.h"
#include "WifiHandler.h"
#include "utilities.h"
#include "Memory.h"

SensorHandler sensorHandler;
PowerManager powerManager;
WifiHandler wifiHandler;
APIHandler apiHandler;
sensors_data_t sensors_data;

void preinit() {
  ESP8266WiFiClass::preinitWiFiOff();
}

void setup(){
  #ifdef SERIAL_DEBUG
    Serial.begin(115200);
    Serial.println("Setup..");
    while(!Serial) {;}
  #endif

  wifiHandler.disable();

  bool wifiConnected = false;
  bool firstStart = isFirstStartup();
  uint32_t sleepTime = 0;

  sensors_data.voltage = powerManager.getBoardVoltage();
  sensors_data.capacity = voltPercentage(sensors_data.voltage);

  if (sensors_data.capacity <= SHUTOFF_CAPACITY) {
    // Shut off to avoid battery damage
    powerManager.shutOff();
  }

  /*
   * Sensor reading
   */
  sensorHandler.enableSensor();
  delay(2000);
  sensorHandler.readValues(&sensors_data);
  delay(50);
  sensorHandler.disableSensor();


  wifiHandler.enable();

  /*
   * Connect wifi
   */
  wifiConnected = wifiHandler.connect(WIFI_SSID, WIFI_PASSWORD);

  if (wifiConnected == true) {
    /*
     * Send values to API
     */
    apiHandler.sendValue(&sensors_data);
  }

  delay(200);

  uint32_t bootCounts = readValueFromRTC(RTC_MEMORY_BOOT_COUNTS_REF_ADDR);
  bool shouldUpdateSleepTime = bootCounts == BOOT_COUNTS_SLEEP_TIME_READ;

  if (firstStart || shouldUpdateSleepTime) {
    if (wifiConnected) {
      sleepTime = apiHandler.readValue(SLEEP_LABEL);
      saveValueToRTC(RTC_MEMORY_SLEEP_TIME_REF_ADDR, sleepTime);
      #ifdef SERIAL_DEBUG
        Serial.println("Saving sleeptime to RTC");
        Serial.println(sleepTime);
      #endif
    }
    saveValueToRTC(RTC_MEMORY_BOOT_COUNTS_REF_ADDR, 0);
  } else {
    sleepTime = readValueFromRTC(RTC_MEMORY_SLEEP_TIME_REF_ADDR);
    #ifdef SERIAL_DEBUG
      Serial.println("Reading sleeptime from RTC: ");
      Serial.println(sleepTime);
    #endif
    saveValueToRTC(RTC_MEMORY_BOOT_COUNTS_REF_ADDR, bootCounts++);
  }

  /*
   * Put in deep Sleep the board
   */
  saveValueToRTC(RTC_FIRST_STARTUP_ADDR, 0);
  wifiHandler.disconnect();
  powerManager.goToSleep(sleepTime);
}

void loop(){
  #ifdef SERIAL_DEBUG
    float voltage = powerManager.getBoardVoltage();
    Serial.println("---");
    Serial.printf("%f", voltage);
    Serial.println("---");
    delay(1000);
  #endif
}
