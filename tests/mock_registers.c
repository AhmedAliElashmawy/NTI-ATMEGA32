#include "mock_registers.h"

volatile uint8_t mock_DDRA = 0;
volatile uint8_t mock_PORTA = 0;
volatile uint8_t mock_PINA = 0;

volatile uint8_t mock_DDRB = 0;
volatile uint8_t mock_PORTB = 0;
volatile uint8_t mock_PINB = 0;

volatile uint8_t mock_DDRC = 0;
volatile uint8_t mock_PORTC = 0;
volatile uint8_t mock_PINC = 0;

volatile uint8_t mock_DDRD = 0;
volatile uint8_t mock_PORTD = 0;
volatile uint8_t mock_PIND = 0;

void mock_registers_reset(void) {
    mock_DDRA = 0; mock_PORTA = 0; mock_PINA = 0;
    mock_DDRB = 0; mock_PORTB = 0; mock_PINB = 0;
    mock_DDRC = 0; mock_PORTC = 0; mock_PINC = 0;
    mock_DDRD = 0; mock_PORTD = 0; mock_PIND = 0;
}
