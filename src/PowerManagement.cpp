#include "Settings.h"
#include "PowerManagement.h"
#include "Arduino.h"

ADC_MODE(ADC_VCC);

void PowerManager::goToSleep(int seconds) {
  if (NULL == seconds || seconds <= 0) {
    seconds = POWER_SLEEP_TIME;
  }
  #ifdef SERIAL_DEBUG
    Serial.printf("Going to sleep for %d seconds.. zzz", seconds);
    Serial.println();
  #endif
  ESP.deepSleep(seconds * 1000000, WAKE_METHOD); //sleep time in usecs.
}

void PowerManager::powerOffWifi() {
  //wifi_set_sleep_type(LIGHT_SLEEP_T);
  delay(1);
}

float PowerManager::getBoardVoltage() {
  float voltage = ((float)ESP.getVcc())/1000;
  return voltage;
}

void PowerManager::shutOff() {
  this->goToSleep(ESP.deepSleepMax());
}
