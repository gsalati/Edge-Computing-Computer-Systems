#include "esp32.h"

// Para Arduino conectado:
//SerialCom Serial;

// Sem Arduino, utilizamos "serial mock"
SerialMock Serial;

// Array com bytes arbitrários para teste
uint8_t test[2] = {0xAB, 0xCD};

void setup()
{
    // h -> dados escritos e lidos em hexa; s -> dados em formato de texto
    Serial.begin('h'); 

    // Com Arduino conectado, serial.begin "normal"
    // Serial.begin(9600)

    // Aguarda um tempo para serial inicializar
    delay(2000);
}


void loop(){
   int a;
   int n;
   uint8_t rx[256];

    while(1){
        // Checa se há caracteres esperando para serem recebidos
        a = Serial.available();
        if (a > 0) { 
            n = Serial.readBytes((char*)rx, a);
            /* 
             * Printa na nossa tela o dado recebido
             * Com arduino conectado, printaria apenas o primeiro byte enviado pelo arduino
             * Sem arduino conectado, printa o primeiro byte enviado por nós "simulando" o Arduino no console
            */
            cout << "RX ESP32: ";
            cout << (int)rx[0] << endl;
            cout.flush();


            delay(1000);

            /*
            * Escreve os dados definidos em test
            * Para SerialMock, os dados serão printados na tela em "TX ESP32: "
            * Para Serial (com arduino conectado) envia os dados para o Arduino
            */
            Serial.writeBytes((char*)test, sizeof(test));
        }

        delay(2000);
    }
}