#include <DHT.h>
#include "SensorHandler.h"
#include "Settings.h"
#include "utilities.h"

void SensorHandler::enableSensor() {
  pinMode(DHT_PWR_PIN, OUTPUT);
  digitalWrite(DHT_PWR_PIN, HIGH);
}

void SensorHandler::disableSensor() {
  digitalWrite(DHT_PWR_PIN, LOW);
}

void SensorHandler::readValues(sensors_data_t* sensors_data) {
  DHT dht(DHT_DATA_PIN, DHTTYPE);

  dht.begin();

  #ifdef SERIAL_DEBUG
    Serial.println("Reading DHT");
  #endif

  float humiditySamples[SAMPLES_NUMBER];
  float temperatureSamples[SAMPLES_NUMBER];
  float heatIndexSamples[SAMPLES_NUMBER];

  int i;
  for(i = 0; i < SAMPLES_NUMBER; i++){
    humiditySamples[i] = dht.readHumidity();
    temperatureSamples[i] = dht.readTemperature();
    heatIndexSamples[i] = dht.computeHeatIndex(temperatureSamples[i], humiditySamples[i], false);
    delay(100);
  }


  sensors_data->humidity = median(humiditySamples, SAMPLES_NUMBER);
  sensors_data->temperature = median(temperatureSamples, SAMPLES_NUMBER);
  sensors_data->heatIndex = median(heatIndexSamples, SAMPLES_NUMBER);

  #ifdef SERIAL_DEBUG
    Serial.println(sensors_data->humidity);
    Serial.println(sensors_data->temperature);
    Serial.println(sensors_data->heatIndex);
  #endif

  if (isnan(sensors_data->humidity) || isnan(sensors_data->temperature)){
    sensors_data->humidity = -100.0;
    sensors_data->temperature = -100.0;
    sensors_data->heatIndex = -100.0;
    #ifdef SERIAL_DEBUG
      Serial.println("Failed DHT");
    #endif
  }
}
