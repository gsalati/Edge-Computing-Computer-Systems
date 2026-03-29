// Inclui a biblioteca LiquidCrystal
#include <LiquidCrystal.h>

#define RS 8
#define EN 9
#define TMP A0
#define TRG 12
#define ECHO 11
#define VREF 5
#define ADC_RESOL 1023
#define BTN 2

const char ordinalChar = 176;

// Inicializa o objeto lcd (isso é código C++)
LiquidCrystal lcd(RS, EN, 4, 5, 6, 7);

// Declaração de funções
// --------------------------------------------------------------------------------------------
static void triggerHC(uint8_t pin);
static float time2Distance(unsigned long time);

float leTemperatura(uint8_t pin);
float leDistancia(uint8_t pinTrigger, uint8_t pinEcho);

// --------------------------------------------------------------------------------------------
void setup()
{
  Serial.begin(9600);
  
  // Configura GPIOs
  pinMode(TRG, OUTPUT);
  pinMode(ECHO, INPUT);
  pinMode(BTN, INPUT);
  
  // Inicializa o display informando as dimensões
  lcd.begin(16,2);
  
  // Escreve no display
  lcd.write("Hello, FIAP!");
}
// --------------------------------------------------------------------------------------------
void loop()
{
  float temp = 0;
  float dist = 0;
  uint8_t btnState;
  // Variável para definir qual informação será exibida
  uint8_t tela = 0; // 0 - exibe temperatura, 1 exibe distancia

  /*
  * Criamos um loop "infinito" para preservar o valor da variável tela
  * Se deixarmos a função loop executar até o fim, o valor da variavel seria perdido
  * Poderiamos utilizar o qualificadror static e não esse loop adicional...
  */
  while(true)
  {

    btnState = digitalRead(BTN);

    if(btnState == HIGH)
    {
      tela = !tela; // Invertemos a tela
    }
    // Faz a leitura do valor do sensor
    temp = leTemperatura(TMP);
    // Leitura da distancia
    dist = leDistancia(TRG, ECHO);

    switch(tela)
    {
      case 0:
        lcd.clear();
        lcd.print("Temperatura: ");
        lcd.setCursor(0,1);
        lcd.print(temp);
        lcd.print(ordinalChar);
        lcd.print("C");
        Serial.println("Exibe Temperatura");
      break;

      case 1:
        lcd.clear();
        lcd.write("Distancia: ");
        lcd.setCursor(0,1);
        lcd.print(dist);
        lcd.print("cm");
        Serial.println("Exibe Distancia");
      break;

      default:
      break;
    }
    
    Serial.print("Distancia em cm: ");
    Serial.println(dist);
    
    // Imprime
    Serial.print("Temperatura medida: ");	
    Serial.println(temp);

    delay(500); // Wait for 1000 millisecond(s)
   }
}
// --------------------------------------------------------------------------------------------
// Definicao das funcoes
static void triggerHC(uint8_t pin)
{
  digitalWrite(pin, LOW);
  delayMicroseconds(5);
  digitalWrite(pin, HIGH);
  delayMicroseconds(10);
  digitalWrite(pin, LOW);
}
// --------------------------------------------------------------------------------------------
static float time2Distance(unsigned long time)
{
  return (float)time/58;
}
// --------------------------------------------------------------------------------------------
float leTemperatura(uint8_t pin)
{
  uint16_t sensor = 0;
  float sensorVoltage = 0;
  sensor = analogRead(TMP);

  sensorVoltage = (float)sensor*VREF/ADC_RESOL;
  return (sensorVoltage - 0.5) * 100;
}
// --------------------------------------------------------------------------------------------
float leDistancia(uint8_t pinTrigger, uint8_t pinEcho)
{
  unsigned long time = 0;
  triggerHC(TRG);
  time = pulseIn(ECHO, HIGH);
  return time2Distance(time);
}