#ifndef APIHandler_h
#define APIHandler_h

  #include "SensorHandler.h"
  #include "SensorsData.h"

  class APIHandler {
    public:
      APIHandler();
      void sendValue(sensors_data_t* sensors_data);
      int readValue(char* pin);
  };
#endif
