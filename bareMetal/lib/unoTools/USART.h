
#ifndef USART_H_
#define USART_H_

#include <avr/io.h>
#include <avr/pgmspace.h>



static const char HexTable[] PROGMEM = {// tabela com os dígitos hexadeximais em ASCII
    '0', '1', '2', '3',
    '4', '5', '6', '7',
    '8', '9', 'A', 'B',
    'C', 'D', 'E', 'F'
};


void USARTInitialize(void);
void USARTTransmit(char data);
char USARTReceive(void);
void USARTPrintString(char *str);
void USARTPrintStringConst(const char *str);
void USARTPrintHexUint_8(uint8_t data);
void USARTPrintNewLine(void);
void ADCTransmiteUSART(uint16_t valor);
void ADCTransmiteNibbleUSART(uint8_t valor);
uint8_t convertASCII(uint8_t valor);
void USARTPrintNewLine();
void USARTPrintHexUint_8(uint8_t data);


#endif /* USART_H_ */
