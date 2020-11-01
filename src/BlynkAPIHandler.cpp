#include "BlynkAPIHandler.h"
#include <ESP8266HTTPClient.h>

BlynkAPIHandler::BlynkAPIHandler(const char* apiEndpoint, const char* apiToken, int port) {
  _endPoint = apiEndpoint;
  _token = apiToken;
  _port = port;
}

void BlynkAPIHandler::sendValue(char* pin, float value) {
  HTTPClient http;

  #ifdef SERIAL_DEBUG
    Serial.println("Blynk API");
  #endif

  char parameters[50];

  sprintf(parameters,"/%s/update/%s",_token, pin);
  http.begin(_endPoint, _port, parameters);

  http.addHeader("Content-Type", "application/json");

  char json[5];
  sprintf(json, "[%f]", value);
  int httpCode = http.PUT(json);

  String payload = http.getString();

  #ifdef SERIAL_DEBUG
    Serial.println(httpCode);   //Print HTTP return code
    Serial.println(payload);    //Print request response payload
  #endif

  http.end();  //Close connection
}

int BlynkAPIHandler::readValue(char* pin) {
  int value = 0;
  HTTPClient http;

  char parameters[50];

  sprintf(parameters,"/%s/get/%s",_token, pin);
  http.begin(_endPoint, _port, parameters);

  int httpCode = http.GET();

  if (httpCode == HTTP_CODE_OK) {
    const char* json = http.getString().c_str();
    sscanf(json, "[\"%d\"]", &value);
  }

  http.end();  //Close connection
  return value;
}
