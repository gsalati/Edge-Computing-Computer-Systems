#include <LiquidCrystal.h>
// C++ code
#define H1 10
#define H2 9
#define RS 2
#define EN 3
#define BTN 8
#define UPDATE_TIME 500 //ms
#define SPEED A5
/*------------------------------------------------------------------------*/
typedef enum{
  DRIVE_POSITION_FORWARD,
  DRIVE_POSITION_BACKWARD,
  DRIVE_POSITION_UNKNOWN
} drive_position_t;

/*------------------------------------------------------------------------*/
/**
 * @brief Exibe no display uma mensagem de boas vindas ao usuário com duração 
 * minima de 2segundos
 * 
 */
static void welcome(void);
/*------------------------------------------------------------------------*/
/**
 * @brief Atualiza no display a posição do "cambio"
 * Essa função só deve enviar comandos ao display 
 * quando houver alterações a serem exibidas
 * A posição do câmbio deve ser mostrada na última coluna da primeira linha
 * Exibe D (drive) para posição "forward" (andando para frente)
 * Exibe o valor R (reverse) para posição "bakward" (ré)
 * 
 * @param pos posição selecionado pela chave seletora
 */
static void updateDisplayDrivePosition(drive_position_t pos);
/*------------------------------------------------------------------------*/
/**
 * @brief Atualiza o valor de "velocidade" no display
 * A velocidade deve ter seu valor numérico exibido na primeira linha do display
 * Na segunda linha deve haver uma "animação" mostrando a
 * aceleração ou desaceleração da velocidade.
 * 
 * @param speed valor de velociadde selecionado no potenciometro
 */
static void updateDisplayMotorSpeed(uint8_t speed);
/*------------------------------------------------------------------------*/
/**
 * @brief Atualiza o acionamento do motor de acordo com a posição
 * e a velocidade selecionado pelo usuário
 * 
 * @param speed valor de velocidade de 0 a 100 selecionado (o mesmo que é exibidp)
 * @param pos posição selecionada pela chave seletora do câmbio
 * @param f_pin pino da ponte H com direção "para frente"
 * @param b_pin pino da ponte H com direção "para trás"
 */
static void controlMotor(uint8_t speed, drive_position_t pos, uint8_t f_pin, uint8_t b_pin);
/*------------------------------------------------------------------------*/
/**
 * @brief Lê o valor do câmbio no pino indicado
 * 
 * @param digitalPin pino para leitura
 * @return drive_position_t Valor lido
 */
static drive_position_t readSelectedPosition(uint8_t digitalPin);
/*------------------------------------------------------------------------*/
/**
 * @brief Lê o valor de velocidade do potênciometo
 * 
 * @param analogPin pino para leitura do canal AD
 * @return uint8_t valor convertido na faixa de 0-100
 */
static uint8_t readSpeed(uint8_t analogPin);
/*-----------------------------------------------------------------------*/

// Inicializa o objeto lcd (isso é código C++)
LiquidCrystal lcd(RS, EN, 4, 5, 6, 7);
/*------------------------------------------------------------------------*/
void setup()
{
  Serial.begin(9600);

  pinMode(H1, OUTPUT);
  pinMode(H2, OUTPUT);
  pinMode(BTN, INPUT);

  // Começa com o motor desligado
  digitalWrite(H1, LOW);
  digitalWrite(H2, LOW);
  
  // Inicializa o display informando as dimensões
  lcd.begin(16,2);

  welcome();
}

void loop()
{
  drive_position_t selectedPosition;
  uint8_t selectedSpeed;
  while(true){
    selectedPosition = readSelectedPosition(BTN);
    selectedSpeed = readSpeed(SPEED);

    controlMotor(selectedSpeed, selectedPosition, H1, H2);
    updateDisplayDrivePosition(selectedPosition);
    updateDisplayMotorSpeed(selectedSpeed);

    Serial.print("Pos : ");
    Serial.print(selectedPosition);
    Serial.print("| Speed: ");
    Serial.println(selectedSpeed);

    delay(UPDATE_TIME);
  }
}

/*------------------------------------------------------------------------*/
static void welcome(void)
{
    uint8_t j;
    const char welcome[] = "Checkpoint 2";
  // Mensagem de boas vindas
    lcd.setCursor(2,0);
    for(j = 0; j <= 11; j++)
    {
        lcd.print(welcome[j]); 
        delay(100);
    }
    lcd.rightToLeft();
    for(j = 0; j <= 12; j++)
    {
      lcd.print(" ");
      delay(100);
    }

    lcd.leftToRight();
    lcd.clear();
}
/*------------------------------------------------------------------------*/
static drive_position_t readSelectedPosition(uint8_t digitalPin)
{
  uint8_t btnValue;
  btnValue = digitalRead(digitalPin);
  if(btnValue)
    return DRIVE_POSITION_FORWARD;
  else
    return DRIVE_POSITION_BACKWARD;
}
/*------------------------------------------------------------------------*/
static uint8_t readSpeed(uint8_t analogPin)
{
  uint16_t potValue;

  potValue = analogRead(analogPin);
  return map (potValue, 0, 1023, 0, 100);
}

/*------------------------------------------------------------------------*/
static void updateDisplayDrivePosition(drive_position_t pos)
{
  static drive_position_t p_old = DRIVE_POSITION_UNKNOWN;
  if(pos == p_old)
  {  
    return;
  }
  p_old = pos;
  lcd.setCursor(15,0);
  switch(pos)
  {
    case DRIVE_POSITION_FORWARD:
      lcd.write("D");
      break;
    case DRIVE_POSITION_BACKWARD:
      lcd.write("R");
      break;
    default:
      lcd.write("E");
      break;
  }   

}
/*------------------------------------------------------------------------*/
static void updateDisplayMotorSpeed(uint8_t speed)
{
  static uint8_t s_old = 255;
  uint8_t j;
  //const char special = 0b11111001;
    const char special = 0xBC;
  if(s_old == speed){
      return;
  }

  lcd.home();

  // Clear old value on display
  for(j = 0; j < 3; j++)
  {
    lcd.write(" ");
  }
  
  // Prints new speed
  lcd.home();
  lcd.print(speed);

  // Prints acceleration effect
  if(speed > s_old){
    lcd.setCursor(0,1);
    for(j = 0; j < 10; j++){
      if((j)*10 <= speed){
        lcd.write(special);
      }else
      {
        lcd.write(" ");
      }
      delay(50);
    }
  } 
  // De acceleartion effect
  else if(speed < s_old){
    for(j = 10; j > 0; j--){
        lcd.setCursor(j,1);
       if((j)*10 <= speed){
        lcd.write(special);
      }else
      {
        lcd.write(" ");
      }
      delay(50);
    }
  }

   s_old = speed;
}
/*------------------------------------------------------------------------*/
static void controlMotor(uint8_t speed, drive_position_t pos, uint8_t f_pin, uint8_t b_pin)
{
  static drive_position_t p_old = DRIVE_POSITION_UNKNOWN;
  static uint8_t s_old = 0;
  uint8_t pwmSpeed;

  if(pos == p_old && speed == s_old){
    return;
  }
  p_old = pos;
  s_old = speed;
  pwmSpeed = map(speed, 0, 100, 0, 255);
  if(pos == DRIVE_POSITION_FORWARD)
  {
    digitalWrite(b_pin, LOW);
    analogWrite(f_pin, pwmSpeed);
  }else if(pos == DRIVE_POSITION_BACKWARD)
  {
    digitalWrite(f_pin, LOW);
    analogWrite(b_pin, pwmSpeed);
  }else{
    digitalWrite(b_pin, LOW);
    digitalWrite(f_pin, LOW);
  }
  
}