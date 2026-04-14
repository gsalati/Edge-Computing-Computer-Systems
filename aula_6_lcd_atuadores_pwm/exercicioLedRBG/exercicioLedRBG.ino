// Inclui a biblioteca LiquidCrystal
#include <LiquidCrystal.h>

#define RS 8
#define EN 3
#define BTN_SELECAO 12
#define BTN_POTENCIA 2
#define PIN_AZUL 10
#define PIN_VERDE 9
#define PIN_VERMELHO 11
/*------------------------------------------------------------------------*/
typedef enum {
    VERMELHO,
    VERDE,
    AZUL
} RGB_t;

/*------------------------------------------------------------------------*/
/**
 * @brief Atualiza as informação do display
 * 
 * @param cor cor a ser mostrado no display
 * @param pot valor de 0 a 100 referente a contribuição na mixagem
 */
static void updateDisplay(RGB_t cor, uint8_t pot);
/*------------------------------------------------------------------------*/
/**
 * @brief Atualiza os PWMs de cada led
 * 
 * @param azul valor de 0 a 100 da potência azul
 * @param vermelho valor de 0 a 100 da potência vermelho
 * @param verde valor de 0 a 100 da potência verde
 */

static void updateLed(uint8_t azul, uint8_t vermelho, uint8_t verde);

/*------------------------------------------------------------------------*/


// Inicializa o objeto lcd (isso é código C++)
LiquidCrystal lcd(RS, EN, 4, 5, 6, 7);

void setup()
{
    uint8_t j = 0;
    
    Serial.begin(9600);

    pinMode(BTN_SELECAO,INPUT);
    pinMode(BTN_POTENCIA, INPUT);
    pinMode(PIN_AZUL, OUTPUT);
    pinMode(PIN_VERDE, OUTPUT);
    pinMode(PIN_VERMELHO, OUTPUT);


    // Inicializa o display informando as dimensões
    lcd.begin(16,2);
    for(j = 0; j <=1; j++)
    {
        lcd.setCursor(2,j);
        lcd.print("Hello, FIAP!");
        delay(1000);
        lcd.clear();
        delay(1000);
    }
}
/*------------------------------------------------------------------------*/
void loop()
{ 
    uint8_t potAzul = 50;
    uint8_t potVerde = 50;
    uint8_t potVermelho = 50;
    uint8_t potDisplay;
    uint8_t btnSelecao, btnPot;
    RGB_t selecionado = VERMELHO;

    analogWrite(PIN_VERMELHO, 127);
    analogWrite(PIN_VERDE, 127);
    analogWrite(PIN_AZUL, 127);
  
    while(true){
        btnSelecao = digitalRead(BTN_SELECAO);
        btnPot = digitalRead(BTN_POTENCIA);
        
        Serial.print("Botoes S|P ");
        Serial.print(btnSelecao);
        Serial.print(" | ");
        Serial.println(btnPot);

        switch(selecionado)
        {
        case VERMELHO:
            if(btnSelecao == HIGH)
            {
                selecionado = AZUL;
            }
            else if(btnPot == HIGH)
            {
                potVermelho += 5;
                if(potVermelho > 100)
                {
                    potVermelho = 0;
                }
            }
            potDisplay = potVermelho;
        break;
        case AZUL:
            if(btnSelecao == HIGH)
                {
                    selecionado = VERDE;
                }
                else if(btnPot == HIGH)
                {
                    potAzul += 5;
                    if(potAzul > 100)
                    {
                        potAzul = 0;
                    }
                }
                potDisplay = potAzul;
        break;
        case VERDE:
                if(btnSelecao == HIGH)
                {
                    selecionado = VERMELHO;
                }
                else if(btnPot == HIGH)
                {
                    potVerde += 5;
                    if(potVerde > 100)
                    {
                        potVerde = 0;
                    }
                }
                potDisplay = potVerde;
        break;
        default:
            selecionado = VERMELHO;
        break;
        }
        updateDisplay(selecionado, potDisplay);
        updateLed(potAzul, potVermelho, potVerde);
        delay(10);
    }
   
}

/*-------------------------------------------------------------------------------------*/
static void updateDisplay(RGB_t cor, uint8_t pot)
{
    static RGB_t cor_old;
    static uint8_t pot_old;

    if(cor_old == cor && pot_old == pot){
        return;
    }
    cor_old = cor;
    pot_old = pot;

    lcd.clear();
    lcd.home();

    switch (cor)
    {
        case VERMELHO:
            lcd.print("Vermelho");
            break;
        case AZUL:
            lcd.print("Azul");
            break;
        case VERDE:
            lcd.print("Verde");
            break;
        default:
            lcd.print("ERRO");
            break;
    }
    lcd.setCursor(0,1);
    lcd.print(pot);
    return;
 }

/*-------------------------------------------------------------------------------------*/
 static void updateLed(uint8_t azul, uint8_t vermelho, uint8_t verde)
 {
    static uint8_t r_old, g_old, b_old;
    uint8_t r,g,b;

    r = map(vermelho, 0, 100, 0, 255);
    g = map(verde, 0, 100, 0, 255);
    b = map(azul, 0, 100, 0, 255);

    Serial.print("Update LEDs. R: ");
    Serial.print(r);
    Serial.print(". G: ");
    Serial.print(g);
    Serial.print(". B: ");
    Serial.println(b);
    
    if(r_old != r){
        analogWrite(PIN_VERMELHO, r);
        r_old = r;
    }

    if(g_old != g){
        analogWrite(PIN_VERDE, g);
        g_old = g;
    }

    if(b_old != b){
        analogWrite(PIN_AZUL, b);
        b_old = b;
    }


    return;
 }