#include <unoTools.h>

void ADCInit()
{
    ADMUX = (ADMUX & (~(1 << REFS1))) | (1 << REFS0); // tensão de referência = AVCC
    ADCSRA |= (1 << ADPS2) | (1 << ADPS1) | (1 << ADPS0); // divide fclk_IO (prescaler) por 128
    ADCSRA  |= (1 << ADEN); // habilita o conversor AD
}

uint16_t ADCRead(uint8_t channel){
    ADMUX = (ADMUX & 0xF0) | (channel & 0x0F); // escolhemos o canal a ser lido
    ADCSRA |= (1 << ADSC); // fazendo ADSC=1 em ADCSRA, iniciamos uma nova conversão   ]

    while (ADCSRA & (1 << ADSC)); // enquanto ADSC=1, a conversão está em andamento

    return ADC; // retorna o valor do canal convertido
}