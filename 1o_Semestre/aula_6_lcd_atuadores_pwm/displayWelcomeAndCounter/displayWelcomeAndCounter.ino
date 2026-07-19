/*
* https://www.tinkercad.com/things/eM0rZE9uxxE-lcdwelcomeandcounter?sharecode=Pwi7Nm8YZpOyn5X1xqtPU0vhSGmjb9zZlKraRSVALyg
*/
// Inclui a biblioteca LiquidCrystal
#include <LiquidCrystal.h>

#define RS 8
#define EN 9
#define BTN 12
const char specialChar = 0b11110101;

// Inicializa o objeto lcd (isso é código C++)
LiquidCrystal lcd(RS, EN, 4, 5, 6, 7);

void setup()
{
  uint8_t j = 0;
  
  pinMode(BTN,INPUT);
  // Inicializa o display informando as dimensões
  lcd.begin(16,2);
  
  
  // Mensagem de boas vindas
  for(j = 0; j < 32; j++)
  {
    if(j == 16)
    {
    	lcd.setCursor(0,1);
    }
  	lcd.write(specialChar);
  	delay(50);
  }
  
  lcd.rightToLeft();
  // Mensagem de boas vindas
  for(j = 0; j < 32; j++)
  {
    lcd.write(" ");
    if(j == 16)
    {
    	lcd.setCursor(15,0);
    }
  
  	delay(50);
  }
  
  lcd.leftToRight();
  
  for(j = 0; j < 3; j++)
  {
    lcd.print("****************");
    lcd.setCursor(0,1);
    lcd.print("****************");
    delay(200);
    lcd.clear();
    delay(200);
    lcd.home();
  }

  do
  {
    for(j = 0; j <=1; j++)
    {
  		lcd.setCursor(2,j);
  		lcd.print("Hello, FIAP!");
    	delay(200);
    	lcd.clear();
      delay(200);
    }
  }while(!digitalRead(BTN));
}

void loop()
{
    int counter = 0;
    lcd.clear();
    lcd.home();

    while(true) // Loop infitno do firmware
    { 
      while(digitalRead(BTN)) // Enquanto o botão estiver pressionado
      {
        lcd.home();
        lcd.print("Conta: ");  
        lcd.print(counter);
        lcd.print(" s");
        delay(1000); // 1 segundo
        counter++; 
      }
      
      // Como podemos resetar a contagem?

      lcd.print("_");
      delay(250);
      lcd.clear();
      lcd.home();
      delay(250); // Wait for 100 millisecond(s)
    }  
}