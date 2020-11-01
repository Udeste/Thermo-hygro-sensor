#include "Memory.h"

extern "C" {
  #include "user_interface.h"
}

bool isFirstStartup(){
  uint32_t first_start = 0;
  system_rtc_mem_read(RTC_FIRST_STARTUP_ADDR, &first_start, RTC_MEMORY_DATA_SIZE);
  if(first_start != 0)
    return true;
  return false;
}

bool saveValueToRTC(uint8_t address, uint32_t value){
  return system_rtc_mem_write(address, &value, RTC_MEMORY_DATA_SIZE);
}

uint32_t readValueFromRTC(uint8_t address){
  uint32_t value = 0;
  system_rtc_mem_read(address, &value, RTC_MEMORY_DATA_SIZE);
  return value;
}



