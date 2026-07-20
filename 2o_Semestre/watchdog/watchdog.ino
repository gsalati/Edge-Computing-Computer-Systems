#include <Watchdog.h>

#define DEFAULT_TIME 10;
#define WDT_TIME_MS 15;

/*
* Declaramos o objeto do watchdog
* O tipo de dado Watchdog é declarado e definido na biblioteca
* <Watchdog.h>
*/

Watchdog watchdog;
int delay_ms = WDT_TIME_MS;

static int leInteiroSerial(void);

void setup()
{
  pinMode(LED_BUILTIN, OUTPUT);
  Serial.begin(9600);
  digitalWrite(LED_BUILTIN,LOW);
  delay(1000);
  digitalWrite(LED_BUILTIN,HIGH);
  

  Serial.println("\n\n----------------------------------------------------------------------------------");
  Serial.println("Inicio demonstracao WDT.\nTempo do delay 15ms\nTempo do watchdog 60ms");
  Serial.println("----------------------------------------------------------------------------------\n");
  Serial.println("Informe o tempo do delay");
  
  watchdog.enable(Watchdog::TIMEOUT_60MS);
}

void loop()
{
  // Checa se há caracteres esperando para serem recebidos
  if (Serial.available() > 0) { 
	    delay_ms = leInteiroSerial();

      Serial.println("Informe o tempo do delay");
  }
  
  delay(delay_ms);

  watchdog.reset();
}
                 
/*
*******************************************************************************************************
*/                 
static int leInteiroSerial(void)
{
  	String entrada = "";
	int numero;
    
    entrada = Serial.readStringUntil('\n');
    entrada.trim();            // Remove espaços e \r
    numero = entrada.toInt();

    Serial.print("Numero recebido: ");
    Serial.println(numero);
    
    return numero;
 }