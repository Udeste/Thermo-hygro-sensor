#include "MQTTAPIHandler.h"
#include <ESP8266HTTPClient.h>
#include "Settings.h"
#include "WiFiClient.h"
#include <PubSubClient.h>
#include "utilities.h"

bool messageArrived = false;
uint32_t sleepTime = 0;

void callback(char* topic, byte* payload, unsigned int length) {

  char buffer[5];
  memcpy(buffer, payload, length);
  buffer[length] = '\0';

  // Convert it to integer
  char *end = nullptr;
  sleepTime = strtol(buffer, &end, 10);
  messageArrived = true;

  #ifdef SERIAL_DEBUG
    Serial.print("Message arrived [");
    Serial.print(topic);
    Serial.print("] ");
    Serial.print(length);
    Serial.println();
    for (unsigned int i=0; i<length; i++) {
      Serial.print((char)payload[i]);
    }
    Serial.println(" converted");

    if (end == buffer)
      Serial.println("Conversion error occurred");
    else
      Serial.println(sleepTime);
  #endif
}


MQTTAPIHandler::MQTTAPIHandler() {}
WiFiClient wifiClient;
PubSubClient client(MQTT_HOST, MQTT_PORT, callback, wifiClient);

void MQTTAPIHandler::sendValue(sensors_data_t* sensors_data) {
  char json[150];
  sprintf(
    json,
    "{\"%s\":%f,\"%s\":%f,\"%s\":%f,\"%s\":%f,\"%s\":%f}",
    TEMPERATURE_LABEL, sensors_data->temperature,
    HUMIDITY_LABEL, sensors_data->humidity,
    HEATINDEX_LABEL, sensors_data->heatIndex,
    BOARD_VOLTAGE_LABEL, sensors_data->voltage,
    BATTERY_CAPACITY_LABEL, sensors_data->capacity
  );

  #ifdef SERIAL_DEBUG
    Serial.println("MQTT PUBLISH: ");
    Serial.println(DEVICE_LABEL);
    Serial.println(MQTT_TOPIC_PUB);
    Serial.println(json);
  #endif
  
  if (!client.connected()) {
    client.connect(DEVICE_LABEL);
  }
  client.publish(MQTT_TOPIC_PUB, json);
}

int MQTTAPIHandler::readValue(char* pin) {
  messageArrived = false;
  uint32_t retries = 100000;

  if (!client.connected()) {
    client.connect(DEVICE_LABEL);
  }

  #ifdef SERIAL_DEBUG
    Serial.println("MQTT SUBSCRIBE");
  #endif  

  client.subscribe(MQTT_TOPIC_SUB);

  while (!messageArrived && retries > 0) {
    client.loop();
    retries--;
  }

  #ifdef SERIAL_DEBUG
    Serial.println(retries);
  #endif  

  return sleepTime;
}
