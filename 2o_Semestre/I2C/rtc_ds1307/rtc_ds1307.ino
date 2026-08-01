/**
 * @file rtc_ds1307.ino
 * @author Guilherme Salati (profguilherme.salati@fiap.com.br)
 * @brief 
 * Exemplo de utilização da biblioteca Wire do arduino para comunicação com CI
 * DS1307 (RTC)
 * 
 * Link da simulação no Wokwi: https://wokwi.com/projects/471170445913281537
 * @version 0.1
 * @date 2026-08-01
 * 
 * @copyright Copyright (c) 2026
 * 
 */
#include "ds1307.h"

void setup() {
  Serial.begin(9600);
  ds1307Begin();

  // Define RTC
  DS1307_Time newTime = {
    30,   // sec
    45,   // min
    14,   // hora (formato 24h)
    6,    // dia da semana (1-7)
    1,    // dia
    8,    // mes
    26    // ano (2026 -> 26)
  };

  ds1307WriteTime(newTime);

}

void loop() {
  DS1307_Time now;

    if (ds1307ReadTime(now))
    {
        Serial.print(now.hour);
        Serial.print(':');
        Serial.print(now.minute);
        Serial.print(':');
        Serial.println(now.second);
    }

    delay(1000);
}
