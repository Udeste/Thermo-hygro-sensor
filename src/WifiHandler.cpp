#include "Settings.h"
#include "WifiHandler.h"
#include "IPAddress.h"
#include <ESP8266WiFi.h>

WifiHandler::WifiHandler() { }

void WifiHandler::disable() {
  this->disconnect();
  WiFi.mode(WIFI_OFF);
  WiFi.forceSleepBegin();
  delay(1);
  // Disable the WiFi persistence.  The ESP8266 will not load and save WiFi settings in the flash memory.
  WiFi.persistent(false);
  #ifdef SERIAL_DEBUG
    Serial.println("WiFi disabled");
  #endif
}

void WifiHandler::enable() {
  WiFi.forceSleepWake();
  WiFi.mode(WIFI_STA);
  #ifdef STATIC_IP
    WiFi.config(STATIC_IP, STATIC_GATEWAY, STATIC_SUBNET, STATIC_DNS1, STATIC_DNS2);
  #endif
  #ifdef SERIAL_DEBUG
    Serial.println("WiFi enabled");
  #endif
}

bool WifiHandler::connect(const char* ssid, const char* password){
    WiFi.begin(ssid, password);
    unsigned long wifiConnectStart = millis();

    while (WiFi.status() != WL_CONNECTED) {

      if (WiFi.status() == WL_CONNECT_FAILED || millis() - wifiConnectStart > 20000) {
        #ifdef SERIAL_DEBUG
          Serial.println("Failed to connect to WiFi");
        #endif
        return false;
      }

      delay(200);
      yield(); // Do (almost) nothing -- yield to allow ESP8266 background functions
      #ifdef SERIAL_DEBUG
        Serial.print(".");
      #endif
    }

    #ifdef SERIAL_DEBUG
      Serial.println("Connected");
      Serial.print(WiFi.status());
    #endif

    return true;
}

void WifiHandler::disconnect(){
  WiFi.disconnect(true);
}
