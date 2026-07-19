#define SENSOR_PIN A5
#define ADC_RESOL 1023
#define VREF 5

static void imprimeArray(float *vet, uint8_t tamanho);

static float media(float *vet, uint8_t tamanho);
/**
 * @brief Configura uma interrupção a cada 500ms
 * Utiliza o timer1 em modo de comparação
 * 
 */
static void setupTimer1ISR(void);
/*---------------------------------------------------------------*/
/**
 * @brief Configura uma interrupção externa 
 * para borda de subida No pino2 do arduino
 * 
 */
static void setupExternalISR(void);

/*---------------------------------------------------------------*/
volatile uint8_t cont = 0;
volatile uint8_t update = 0;
volatile uint8_t triggerAmostra = 0;
volatile uint8_t triggerUpdate = 0;
volatile uint8_t extTriggered = 0;

float temperaturas[16] = {0};
/*---------------------------------------------------------------*/
void setup() {

  cli(); // Desabilita interrupções globais

  setupTimer1ISR();
  setupExternalISR();

  sei(); // Habilita interrupções globais

  Serial.begin(9600);

  Serial.println("\n\n ------ OLA -------- \n");
  pinMode(LED_BUILTIN, OUTPUT);

}
/*---------------------------------------------------------------*/
void loop() {  
  uint8_t i = 0;
  float temperatura;
  while(true)
  {
    if(triggerAmostra)
    {
      temperaturas[i] = readTemperatureWithNoise();
      i++;
      if(i >= 16){
        i = 0;
      }

      imprimeArray(temperaturas, 16);
      triggerAmostra = 0;
    }
    
    if(triggerUpdate)
    {
      temperatura = media(temperaturas, 16);
      Serial.print("MEDIA MOVEL: ");
      Serial.println(temperatura);
      triggerUpdate = 0;
    }
    if(extTriggered)
    {
      Serial.print("MEDIA REQUISITADA PELO USUARIO: ");
      temperatura = media(temperaturas, 16);
      Serial.println(temperatura);
      extTriggered = 0;
    }
  }

}
/*---------------------------------------------------------------*/
static void setupTimer1ISR(void)
{
    // Limpa o registrador de controle
    TCCR1A = 0;
    TCCR1B = 0;

    // Zera o contador
    TCNT1 = 0;

    // Modo CTC (WGM12 = 1)
    TCCR1B |= (1 << WGM12);

    //  Prescaler = 1024 (CS12 + CS10)
    TCCR1B |= (1 << CS12) | (1 << CS10);

    //  OCR1A = TOP
  	// 16Mhz/1024 = 15625Hz
  	// Se a cada segundo o contador conta até 15624, para interromper a cada meio segundo:
  	// 15624/2 = 
    OCR1A = 7812;


    // Habilita interrupção de compare A
    TIMSK1 |= (1 << OCIE1A);


}
/*---------------------------------------------------------------*/
static void setupExternalISR(void)
{
    EICRA = 0;
    // Set PD2 (INT0 / Arduino pin 2) as input
    DDRD &= ~(1 << PD2);

    // Configure INT0 for rising edge:
    // ISC01 = 1 falling edge
    EICRA |= (1 << ISC01);   // set ISC01
    EICRA |= (1 << ISC00);  // set
    // Enable INT0
    EIMSK |= (1 << INT0);
}
/*----------------------------------------------------------------
*
* INTERRUPTIONS CALLBACKS
*
-----------------------------------------------------------------*/
ISR(TIMER1_COMPA_vect) {
    if(cont++ > 10){
      triggerAmostra = 1;
      cont = 0;
    }

    if(update++ > 60)
    {
      triggerUpdate = 1;
      update = 0;
    }
}
/*---------------------------------------------------------------*/
ISR(INT0_vect)
{
  extTriggered = 1;
}

/*---------------------------------------------------------------*/
static float readTemperatureWithNoise(void)
{
  	uint16_t sensor = 0;
  	float sensorVoltage = 0;
  	float temp = 0;
  	long randNumber = random(-100,100);
  

   
  	// Faz a leitura do valor do sensor
  	sensor = analogRead(SENSOR_PIN);
   
  	// Converte medida em temperatura
  	sensorVoltage = (float)sensor*VREF/ADC_RESOL;
  	temp = (sensorVoltage - 0.5) * 100 + ((float)random(-30,30)/100);

    return temp;
}

/*--------------------*/
static void imprimeArray(float *vet, uint8_t tamanho)
{
  uint8_t i = 0;
  Serial.println("-------------------------------------");
  for(i = 0; i < tamanho; i++)
  {
    Serial.print("Elemento ");
    Serial.print(i);
    Serial.print(" : ");
    Serial.println(*vet);

    // Incrementa o ponteiro: Desloca a memória para o próximo elemento
    vet++;
  }
   Serial.println("-------------------------------------");
}

/*--------------------------------------------*/
static float media(float *vet, uint8_t tamanho){
  uint8_t j = 0;
  float valorMedia = 0;
  for(j = 0; j < 16; j++)
  {
    valorMedia+=vet[j];
  }

  return valorMedia/tamanho;
}

