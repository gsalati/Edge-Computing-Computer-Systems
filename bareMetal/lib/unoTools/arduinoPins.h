/**
 * @file arduinoPins.h
 * @brief Arquivo com definições de dados e estruturas para utilização do ATMega328p com placa do Arduino
 * @version 0.1
 * @date 2026-04-15
 * 
 * @copyright Copyright (c) 2026
 * 
 */

#ifndef ARDUINO_PINS_H
#define ARDUINO_PINS_H

#include <avr/io.h>

/*
 * =========================
 * DEFINES GERAIS
 * =========================
 */
#ifndef F_CPU
#define F_CPU 16000000UL
#endif

/*
 * =========================
 * DIGITAL PINS (D0 - D13)
 * =========================
 */

// PORTD (D0 - D7)
#define D0_PORT PORTD
#define D0_DDR  DDRD
#define D0_PIN  PIND
#define D0_BIT  PD0

#define D1_PORT PORTD
#define D1_DDR  DDRD
#define D1_PIN  PIND
#define D1_BIT  PD1

#define D2_PORT PORTD
#define D2_DDR  DDRD
#define D2_PIN  PIND
#define D2_BIT  PD2

#define D3_PORT PORTD
#define D3_DDR  DDRD
#define D3_PIN  PIND
#define D3_BIT  PD3

#define D4_PORT PORTD
#define D4_DDR  DDRD
#define D4_PIN  PIND
#define D4_BIT  PD4

#define D5_PORT PORTD
#define D5_DDR  DDRD
#define D5_PIN  PIND
#define D5_BIT  PD5

#define D6_PORT PORTD
#define D6_DDR  DDRD
#define D6_PIN  PIND
#define D6_BIT  PD6

#define D7_PORT PORTD
#define D7_DDR  DDRD
#define D7_PIN  PIND
#define D7_BIT  PD7


// PORTB (D8 - D13)
#define D8_PORT PORTB
#define D8_DDR  DDRB
#define D8_PIN  PINB
#define D8_BIT  PB0

#define D9_PORT PORTB
#define D9_DDR  DDRB
#define D9_PIN  PINB
#define D9_BIT  PB1

#define D10_PORT PORTB
#define D10_DDR  DDRB
#define D10_PIN  PINB
#define D10_BIT  PB2

#define D11_PORT PORTB
#define D11_DDR  DDRB
#define D11_PIN  PINB
#define D11_BIT  PB3

#define D12_PORT PORTB
#define D12_DDR  DDRB
#define D12_PIN  PINB
#define D12_BIT  PB4

#define D13_PORT PORTB
#define D13_DDR  DDRB
#define D13_PIN  PINB
#define D13_BIT  PB5


/*
 * =========================
 * ANALOG PINS (A0 - A5)
 * =========================
 */

// PORTC
#define A0_PORT PORTC
#define A0_DDR  DDRC
#define A0_PIN  PINC
#define A0_BIT  PC0
#define A0      PC0

#define A1_PORT PORTC
#define A1_DDR  DDRC
#define A1_PIN  PINC
#define A1_BIT  PC1
#define A1      PC1

#define A2_PORT PORTC
#define A2_DDR  DDRC
#define A2_PIN  PINC
#define A2_BIT  PC2
#define A2      PC2

#define A3_PORT PORTC
#define A3_DDR  DDRC
#define A3_PIN  PINC
#define A3_BIT  PC3
#define A3      PC3

#define A4_PORT PORTC
#define A4_DDR  DDRC
#define A4_PIN  PINC
#define A4_BIT  PC4
#define A4      PC4

#define A5_PORT PORTC
#define A5_DDR  DDRC
#define A5_PIN  PINC
#define A5_BIT  PC5
#define A5      PC5


/*
 * =========================
 * MACROS
 * =========================
 */

#define SET_OUTPUT(ddr, bit)   ((ddr) |= (1 << (bit)))
#define SET_INPUT(ddr, bit)    ((ddr) &= ~(1 << (bit)))

#define WRITE_HIGH(port, bit)  ((port) |= (1 << (bit)))
#define WRITE_LOW(port, bit)   ((port) &= ~(1 << (bit)))

#define TOGGLE(port, bit)      ((port) ^= (1 << (bit)))

#define READ(pin, bit)         ((pin) & (1 << (bit)))

#endif