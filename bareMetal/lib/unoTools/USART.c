#include "USART.h"

/*********************/
void USARTInitialize()
{
    UCSR0A &= ~(1 << U2X0);  // transmissão em velocidade normal
    UBRR0 = 0x67; 		                        // taxa de transmissão
    UCSR0B = _BV(RXEN0) | _BV(TXEN0);    		// Permite RX e TX
    UCSR0C = (1 << UCSZ01) | (1 << UCSZ00); 	// formato do quadro 8N1
}

/*****************************/
void USARTTransmit(char data)
{
    while (!(UCSR0A & (1 << UDRE0)));       // espere o dado anterior ser transmitido

    UDR0 = data;                            // envia o dado
}

/*****************/
char USARTReceive()
{
    char data;

    while (!(UCSR0A & (1 << RXC0)));        // espere por um dado recebido

    data = UDR0;
    return data;                            // retorne o dado
}

/*******************************/
void USARTPrintString(char *str)
{
    while (*str) {                          // se caracter na string não é zero
        USARTTransmit(*str);                // transmite a string
        str++;                              // aponta para o próximo caracater
    }
}

/******************************************/
void USARTPrintStringConst(const char *str)
{
    while (pgm_read_byte(str)) {            // se caracater na string não é zero
        USARTTransmit(pgm_read_byte(str));  // transmite o caracter
        str++;                              // aponta para o próximo caracter da string
    }
}

/*************************************/
void USARTPrintHexUint_8(uint8_t data)
    char c;
    USARTTransmit('0');                     // transmite um 0 (0)
    USARTTransmit('x');                     // transmite um x (0x)
    c = pgm_read_byte(&HexTable[(data & 0xF0) >> 4]); // c: carcater do nibble mais significativo
    USARTTransmit(c);                       // transmite nibble mais significativo (0xD)
    c = pgm_read_byte(&HexTable[data & 0x0F]); // c: caracter do nibble menos significativo
    USARTTransmit(c);                       // transmite nibble menos significativo (0xDD)
}

/***********************/
void USARTPrintNewLine()
{
    USARTTransmit('\r');                     // transmite um CR
    USARTTransmit('\n');                     // transmite um LF
}


/******************************************************************************/
// Converte um valor entre 0x00 a 0x0F para o carcater hexadecimal ASCII
// equivalente
// Entrada: valor - um número entre 0x00 e 0x0F.
// Retorno: um carcater hexadecimal ASCII equivalente ao número em valor.
/******************************************************************************/
uint8_t convertASCII(uint8_t valor)
/******************************************************************************/

{
    uint8_t valorASCII;

    if (valor > 9) {
        valorASCII = valor + 0x37;
    } else {
        valorASCII = valor + 0x30;
    }

    return valorASCII;
}

/******************************************************************************/
// Transmite pelo periférico USART0 o carcater ASCII do valor hexadecimal de um
// nibble.
// Entrada: valor - nibble a ser enviado pelo periférico USART0. O valor do nibble
//          é enviado como um caracter ASCII entre '0' e 'F'
/******************************************************************************/
void ADCTransmiteNibbleUSART(uint8_t valor)
/******************************************************************************/
{
    uint8_t valorASCII;
    valorASCII = convertASCII(valor); // converte o número para um caracter hexadecimal
    USARTTransmit(valorASCII); // envia pelo periférico USART0
}

/******************************************************************************/
// Transmite uma palavra de 16 bytes pelo periférico USART0. O número é enviado
// como um número hexadecimal (caracteres hexadecimais)
// Entrada: valor - a palavra a ser enviada pelo periférico USART0
/******************************************************************************/
void ADCTransmiteUSART(uint16_t valor)
/******************************************************************************/
{
    ADCTransmiteNibbleUSART((uint8_t) valor >> 12); // transmite nibble mais significativo
    ADCTransmiteNibbleUSART((uint8_t)(valor >> 8) & 0x000F); // transmite próximo nibble
    ADCTransmiteNibbleUSART((uint8_t)(valor >> 4) & 0x000F); // transmite próximo nibble
    ADCTransmiteNibbleUSART((uint8_t) valor & 0x0000F) ; // transmite nibble menos significativo
    USARTPrintNewLine();
}


