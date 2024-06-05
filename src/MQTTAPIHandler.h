#ifndef MQTTAPIHandler_h
#define MQTTAPIHandler_h

  #include "SensorHandler.h"
  #include "SensorsData.h"

  class MQTTAPIHandler {
    public:
      MQTTAPIHandler();
      void sendValue(sensors_data_t* sensors_data);
      int readValue(char* pin);
  };
#endif
