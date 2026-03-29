// Inclui a biblioteca LiquidCrystal
#include <LiquidCrystal.h>

#define RS 8
#define EN 9

// Inicializa o objeto lcd (isso é código C++)
LiquidCrystal lcd(RS, EN, 4, 5, 6, 7);

void setup()
{
  // Inicializa o display informando as dimensões
  lcd.begin(16,2);
  
  // Escreve no display
  lcd.print("Hello, FIAP!");
}

void loop()
{
    delay(1000); // Wait for 1000 millisecond(s)
}