// C++ code
// https://www.tinkercad.com/things/caebLYOwhHQ-servosweep?sharecode=AaT3jNYDu3RnmgkfhquFZGlNIfBHbsy5ndUuNY2sHRM
#include <Servo.h>

const uint8_t servoPin = 10;


Servo srv;

void setup()
{
  srv.attach(servoPin);
}

void loop()
{
  int j = 0;
  
  srv.write(0);
  delay(2000);
  for(j = 0; j<= 180; j++)
  {
  	srv.write(j);
    delay(50);
  }
  
}