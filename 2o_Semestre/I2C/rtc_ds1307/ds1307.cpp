#include "ds1307.h"
#include <Wire.h>

static uint8_t decToBcd(uint8_t value);
static uint8_t bcdToDec(uint8_t value);

// Converte decimal -> BCD
static uint8_t decToBcd(uint8_t value)
{
  return ((value / 10) << 4) | (value % 10);
}

// Converte BCD -> decimal
static uint8_t bcdToDec(uint8_t value)
{
  return ((value >> 4) * 10) + (value & 0x0F);
}

void ds1307Begin(){
  Wire.begin();
}

// Escreve horário e data completos
void ds1307WriteTime(const DS1307_Time &dt)
{
  Wire.beginTransmission(DS1307_ADDR);

  // Começa a esrita no registrador de segundos
  Wire.write(0x00);

  // Registrador dos segundos bit 7 = CH (Clock Halt), mantemos no estado atual
  Wire.write(decToBcd(dt.second) & 0x7F);
  Wire.write(decToBcd(dt.minute));
  Wire.write(decToBcd(dt.hour));    
  Wire.write(decToBcd(dt.dayOfWeek));
  Wire.write(decToBcd(dt.day));
  Wire.write(decToBcd(dt.month));
  Wire.write(decToBcd(dt.year));

  Wire.endTransmission();
}

// Lê horário e data
bool ds1307ReadTime(DS1307_Time &dt)
{
  Wire.beginTransmission(DS1307_ADDR);
  Wire.write(0x00);

  if (Wire.endTransmission() != 0)
    return false;

  // Solicita os 7 registrador a partir do 0x00 through
  if (Wire.requestFrom(DS1307_ADDR, 7) != 7)
    return false;

  uint8_t seconds = Wire.read();
  dt.second    = bcdToDec(seconds & 0x7F);
  dt.minute    = bcdToDec(Wire.read());
  dt.hour      = bcdToDec(Wire.read() & 0x3F); // Mascara para formato 24 horas
  dt.dayOfWeek = bcdToDec(Wire.read());
  dt.day        = bcdToDec(Wire.read());
  dt.month      = bcdToDec(Wire.read());
  dt.year       = bcdToDec(Wire.read());

  return true;
}