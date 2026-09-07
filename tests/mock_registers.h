#ifndef MOCK_REGISTERS_H
#define MOCK_REGISTERS_H

#include <stdint.h>

/* Mock hardware registers as global volatile uint8 variables in RAM */
extern volatile uint8_t mock_DDRA;
extern volatile uint8_t mock_PORTA;
extern volatile uint8_t mock_PINA;

extern volatile uint8_t mock_DDRB;
extern volatile uint8_t mock_PORTB;
extern volatile uint8_t mock_PINB;

extern volatile uint8_t mock_DDRC;
extern volatile uint8_t mock_PORTC;
extern volatile uint8_t mock_PINC;

extern volatile uint8_t mock_DDRD;
extern volatile uint8_t mock_PORTD;
extern volatile uint8_t mock_PIND;

void mock_registers_reset(void);

#endif /* MOCK_REGISTERS_H */
