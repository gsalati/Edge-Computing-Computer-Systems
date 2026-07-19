/**
 * @brief Configura uma interrupção de 1kHz 
 * Utiliza o timer1 em modo de comparação
 * 
 */
static void setupTimer1ISR(void);
/*---------------------------------------------------------------*/
/**
 * @brief Configura uma interrupção externa 
 * No pino2 do arduino
 * 
 */
static void setupExternalISR(void);

/*---------------------------------------------------------------*/
volatile uint16_t cont = 0;
volatile uint8_t oneSecond = 0;
volatile uint8_t extTriggered = 0;
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
  unsigned long t1, t2, tf;
  static unsigned long t_now, t_last = 0;

  t1 = millis();
  
  while(true)
  {
    if(oneSecond)
    {
      t2 = millis();

      tf = t2 - t1;
      Serial.print("Tempo passado em ms: ");
      Serial.println(tf);

      oneSecond = 0;
      t1 = t2;
    }

    if(extTriggered)
    {
      Serial.println("EXT");
      t_now = millis();
      if(t_now - t_last > 100)
      {
        Serial.println("DEBOUNCE");
        PORTB ^= (1 << PINB5);
        t_last = t_now;
      }
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

    //  Prescaler = 64 (CS11 + CS10)
    TCCR1B |= (1 << CS11) | (1 << CS10);

    //  OCR1A = TOP
    OCR1A = 249;


    // Habilita interrupção de compare A
    TIMSK1 |= (1 << OCIE1A);


}
/*---------------------------------------------------------------*/
static void setupExternalISR(void)
{
    // Set PD2 (INT0 / Arduino pin 2) as input
    DDRD &= ~(1 << PD2);

    // Optional: enable internal pull-up
    PORTD |= (1 << PORTD2);

    // Configure INT0 for rising edge:
    // ISC01 = 1 falling edge
    EICRA |= (1 << ISC01);   // set ISC01
    EICRA &= ~(1 << ISC00);  // clear ISC00 → falling edge

    // Enable INT0
    EIMSK |= (1 << INT0);
}
/*----------------------------------------------------------------
*
* INTERRUPTIONS CALLBACKS
*
-----------------------------------------------------------------*/
ISR(TIMER1_COMPA_vect) {
  if(cont++ > 1000)
  {
    cont = 0;
    oneSecond = 1;
  }

}
/*---------------------------------------------------------------*/
ISR(INT0_vect)
{
  extTriggered = 1;
}