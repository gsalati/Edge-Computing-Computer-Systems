#include "control.h"
#include <Arduino.h>

float temp_th = 25;
//-------------------------------------------------------------------------------//
void init_control(void){
  pinMode(LED_PIN, OUTPUT);
  digitalWrite(LED_PIN, LOW);
}
//-------------------------------------------------------------------------------//
void controlLed(float t_atual){
  if (t_atual > temp_th){
    Serial.println("set led to high");
    digitalWrite(LED_PIN, HIGH);
  }else{
    digitalWrite(LED_PIN,LOW);
     Serial.println("set led to low");
  }
}
//-------------------------------------------------------------------------------//
void setTempTh(float t){
  Serial.print("Configura threshold de temperatura para: ");
  Serial.println(t);

  temp_th = t;
}



