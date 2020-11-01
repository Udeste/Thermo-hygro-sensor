#ifndef SensorHandler_h
#define SensorHandler_h

  #include "Settings.h"
  #include "SensorsData.h"

  class SensorHandler {
    public:
      void enableSensor();
      void disableSensor();
      void readValues(sensors_data_t* sensors_data);
  };

#endif
