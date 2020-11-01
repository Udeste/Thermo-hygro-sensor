#include "UbidotsAPIHandler.h"
#include <ESP8266HTTPClient.h>
#include "Settings.h"
#include "WiFiClient.h"


APIHandler::APIHandler() {}

void APIHandler::sendValue(sensors_data_t* sensors_data) {
  WiFiClient client;
  HTTPClient http;

  if (!client.connect(API_HOST, API_PORT)) {
    return;
  }

  char url[200];

  sprintf(url,"%s/devices/%s/",API_ENDPOINT, DEVICE_LABEL);

  http.begin(client, url);

  http.addHeader("Content-Type", "application/json");
  http.addHeader("X-Auth-Token", API_TOKEN);

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
    Serial.println("POST: ");
    Serial.println(json);
    int httpCode = http.POST(json);
    if (httpCode == HTTP_CODE_OK) {
      const char* res = http.getString().c_str();
      Serial.println(res);
    }
  #else
    http.POST(json);
  #endif

  http.end();  //Close connection
}

int APIHandler::readValue(char* pin) {
  int value = 0;
  WiFiClient client;
  HTTPClient http;

  if (!client.connect(API_HOST, API_PORT)) {
    #ifdef SERIAL_DEBUG
      Serial.println("Failed to connect");
    #endif
    return 0;
  }

  char url[200];
  sprintf(url,"%s/devices/%s/%s/lv",API_ENDPOINT, DEVICE_LABEL, pin);
  #ifdef SERIAL_DEBUG
    Serial.println(url);
  #endif
  http.begin(client, url);

  http.addHeader("Content-Type", "application/json");
  http.addHeader("X-Auth-Token", API_TOKEN);

  int httpCode = http.GET();

  if (httpCode == HTTP_CODE_OK) {
    const char* res = http.getString().c_str();
    value = atoi(res);
  }

  http.end();  //Close connection
  return value;
}
