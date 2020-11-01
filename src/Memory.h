#ifndef MEMORY_H_
#define MEMORY_H_
  #include "Arduino.h"
  /*
   * During deep sleep, only RTC still working, so maybe we need to save some user data in RTC memory. Only â€œuser dataâ€� area can be used by user. 
   * Note: RTC memory is 4 bytes aligned for read and write operations. Parameter â€œdes_addrâ€� means block number(4 bytes per block). 
   * So, if we want to save some data at the beginning of user data area, â€œdes_addrâ€� will be 256/4 = 64, â€œsave_sizeâ€� will be data length.
  |_ _ _ _ _system data _ _ _ _ _|_ _ _ _ _ _ _ _ _ user data _ _ _ _ _ _ _ _ _|
  | 256 bytes                    | 512 bytes |

  BLOCK NUMBER FROM 65 TO 129 (512 bytes /4 bytes(size per block) = 129 blocks)*/
  #define RTC_MEMORY_SLEEP_TIME_REF_ADDR   65
  // #define RTC_MEMORY_Y_REF_ADDR   66
  // #define RTC_MEMORY_Z_REF_ADDR   67
  #define RTC_FIRST_STARTUP_ADDR  68
  // #define RTC_LAST_STATUS_ADDR    69
  // #define RTC_COUNT_RESET_ADDR    70
  #define RTC_MEMORY_DATA_SIZE 4 //4 bytes

  extern uint32_t last_status;

  bool isFirstStartup(void);
  bool saveValueToRTC(uint8_t address, uint32_t value);
  uint32_t readValueFromRTC(uint8_t address);
#endif


