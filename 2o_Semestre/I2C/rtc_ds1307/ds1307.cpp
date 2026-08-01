#include "ds1307.h"
#include <Wire.h>

static uint8_t decToBcd(uint8_t value);
static uint8_t bcdToDec(uint8_t value);

// Convert decimal -> BCD
static uint8_t decToBcd(uint8_t value)
{
  return ((value / 10) << 4) | (value % 10);
}

// Convert BCD -> decimal
static uint8_t bcdToDec(uint8_t value)
{
  return ((value >> 4) * 10) + (value & 0x0F);
}

void ds1307Begin(){
  Wire.begin();
}

// Write a complete date/time to the DS1307
void ds1307WriteTime(const DS1307_Time &dt)
{
  Wire.beginTransmission(DS1307_ADDR);

  // Start writing at seconds register (0x00)
  Wire.write(0x00);

  // Seconds: bit 7 = CH (Clock Halt), so keep it cleared
  Wire.write(decToBcd(dt.second) & 0x7F);
  Wire.write(decToBcd(dt.minute));
  Wire.write(decToBcd(dt.hour));       // 24-hour mode
  Wire.write(decToBcd(dt.dayOfWeek));
  Wire.write(decToBcd(dt.day));
  Wire.write(decToBcd(dt.month));
  Wire.write(decToBcd(dt.year));

  Wire.endTransmission();
}

// Read the current date/time from the DS1307
bool ds1307ReadTime(DS1307_Time &dt)
{
  // Tell DS1307 which register we want to read from
  Wire.beginTransmission(DS1307_ADDR);
  Wire.write(0x00);

  if (Wire.endTransmission() != 0)
    return false;

  // Request registers 0x00 through 0x06
  if (Wire.requestFrom(DS1307_ADDR, 7) != 7)
    return false;

  uint8_t seconds = Wire.read();
  dt.second    = bcdToDec(seconds & 0x7F);
  dt.minute    = bcdToDec(Wire.read());
  dt.hour      = bcdToDec(Wire.read() & 0x3F);
  dt.dayOfWeek = bcdToDec(Wire.read());
  dt.day        = bcdToDec(Wire.read());
  dt.month      = bcdToDec(Wire.read());
  dt.year       = bcdToDec(Wire.read());

  return true;
}