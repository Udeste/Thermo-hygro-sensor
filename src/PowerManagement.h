#ifndef PowerManagement_h
#define PowerManagement_h

  #include "Settings.h"

  class PowerManager {
    public:
      void goToSleep(int seconds = POWER_SLEEP_TIME);
      void powerOffWifi();
      float getBoardVoltage();
      void shutOff();
  };

#endif
