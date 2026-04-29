#include <unoTools.h> // definições do ATmega328P
#include <USART.h>

#include <util/delay.h> // para gerar atrasos




// procedimento principal
int main(void)
{
  USARTInitialize(); // inicializa o periferico USART0: 19200 Bauds, 8N1
  ADCInit();
  // faz a porta PB uma saída
  SET_OUTPUT(D8_DDR, D8_BIT);
  uint16_t value = 0;

  while(1) // repete
  {
    _delay_ms(500);
    WRITE_HIGH(D8_PORT, D8_BIT);
    _delay_ms(500);
    WRITE_LOW(D8_PORT, D8_BIT);

    value = ADCRead(0);

    ADCTransmiteUSART(value); // transmite o valor lido pelo conversor
  };

    return 0;
}
