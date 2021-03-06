#ifndef Settings_h
#define Settings_h

  #include "IPAddress.h"

  // #define SERIAL_DEBUG             // Define it in platform.ini file

  // #define DHT_PWR_PIN            4 // Define it in platform.ini file
  // #define DHT_DATA_PIN           5 // Define it in platform.ini file
  #define DHTTYPE                DHT22
  #define SAMPLES_NUMBER         30

  /*
   * WAKE_RF_DEFAULT = 0, // RF_CAL or not after deep-sleep wake up, depends on init data byte 108.
   * WAKE_RFCAL = 1,      // RF_CAL after deep-sleep wake up, there will be large current.
   * WAKE_NO_RFCAL = 2,   // no RF_CAL after deep-sleep wake up, there will only be small current.
   * WAKE_RF_DISABLED = 4 // disable RF after deep-sleep wake up, just like modem sleep, there will be the smallest current.
  */
  #define WAKE_METHOD            WAKE_RF_DISABLED
  #define POWER_SLEEP_TIME       60 //seconds

  /*
   * WIFI SETUP
   */
  #define STATIC_IP              IPAddress(192, 168, 1,  151)
  #define STATIC_SUBNET          IPAddress(255, 255, 255, 0)
  #define STATIC_GATEWAY         IPAddress(192, 168, 1,  1)
  #define STATIC_DNS1            IPAddress(192, 168, 1,  201)
  #define STATIC_DNS2            IPAddress(192, 168, 1,  201)
  // #define WIFI_SSID              "" // Define it in platform.ini file
  // #define WIFI_PASSWORD          """ // Define it in platform.ini file

  /*
   * UBIDOTS SETUP
   * DEFINED IN platform.ini file
   */
  // #define API_HOST               "50.23.124.68"
  // #define API_ENDPOINT           "http://50.23.124.68/api/v1.6" // things.ubidots.com
  // #define API_PORT               80
  // #define API_TOKEN              "Y"

  // #define DEVICE_LABEL             "esp-07s_1"

  // #define SLEEP_LABEL              "sleep-time"
  // #define TEMPERATURE_LABEL        "temp"
  // #define HUMIDITY_LABEL           "humidity"
  // #define BOARD_VOLTAGE_LABEL      "voltage"
  // #define BATTERY_CAPACITY_LABEL   "capacity"
  // #define HEATINDEX_LABEL          "heat-index"


  /*
    Measured voltage map (WiFi ON)

    Volt meter   |    GetVcc
    2.54         |    2.42
    3.03         |    2.95
    3.23         |    3.16      0%
    3.3          |    3.30
    3.77         |    3.36
    4.0          |    3.388
    4.2          |    3.388     100%
  */

  #define SHUTOFF_CAPACITY 0

  #define VOLT_MAX_SCALE_VALUE 370 // 3.70 * 100
  #define VOLT_MIN_SCALE_VALUE 316 // 3.16 * 100

#endif
