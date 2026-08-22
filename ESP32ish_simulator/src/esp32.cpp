#include "esp32.h"

SerialCom Serial;

char* test = "Ola Fiap";

void setup()
{
    Serial.begin(9600);
    delay(2000);

    cout << "Tx: ";
    cout.write(test, strlen(test));
    cout.flush();
    cout << endl;
    
    Serial.writeBytes(test, strlen(test));

    delay(2000);
}


void loop(){
   int a;
   int n;
   char rx[256];

    while(1){
        // Checa se há caracteres esperando para serem recebidos
        a = Serial.available();
        if (a > 0) { 
            n = Serial.readBytes(rx, a);
            cout << "rx: ";
            cout.write(rx, n);
            cout.flush();
            cout << endl;


            delay(1000);
            cout << "Tx: ";
            cout.write(test, strlen(test));
            cout.flush();
            cout << endl;
            
            Serial.writeBytes(test, strlen(test));
        }

        delay(2000);

    }
}