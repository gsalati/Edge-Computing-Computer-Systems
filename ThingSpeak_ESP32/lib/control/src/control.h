#ifndef CONTROL_H
#define CONTROL_H


#define LED_PIN 26    

void init_control(void);
void controlLed(float t_atual);
void setTempTh(float t);
#endif