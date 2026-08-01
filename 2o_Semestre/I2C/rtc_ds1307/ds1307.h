#ifndef DS1307_H 
#define DS1307_H

#include <Arduino.h>

#define DS1307_ADDR 0x68

typedef struct  {
  uint8_t second;
  uint8_t minute;
  uint8_t hour;
  uint8_t dayOfWeek;
  uint8_t day;
  uint8_t month;
  uint8_t year;   // 0-99as
} DS1307_Time;

// Initialize I2C communication 
void ds1307Begin();
void ds1307WriteTime(const DS1307_Time &time);
bool ds1307ReadTime(DS1307_Time &time);

#endif