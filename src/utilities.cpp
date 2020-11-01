#include "Settings.h"
#include <Arduino.h>

float median(float* arr, int n) {
  float r = 0.0f;
  for (int i=0;i<n;i++){
    r+=arr[i];
  }
  return (r/n);
}


 float voltPercentage(float value) {
  uint16_t scaledValue = (uint16_t) (value * 100);

  float capacity = ((scaledValue - VOLT_MIN_SCALE_VALUE) * 100) / (VOLT_MAX_SCALE_VALUE - VOLT_MIN_SCALE_VALUE);
  #ifdef SERIAL_DEBUG
    Serial.println(value);
    Serial.println(scaledValue);
    Serial.println(VOLT_MIN_SCALE_VALUE);
    Serial.println(capacity);
  #endif
  return capacity;
}