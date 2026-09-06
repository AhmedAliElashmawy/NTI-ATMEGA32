/*
 * Author: Ahmed Ellamie
 * Email:  ahmed.ellamiee@gmail.com
 *
 * AVR_NTI application entry.
 * Layers: LIB (types) -> MCAL (drivers) -> HAL (devices) -> Logic (app) ->
 * main.
 */

#define F_CPU 8000000UL

#include "STD_TYPES.h"
#include "UART_interface.h"
#include <avr/io.h>
#include <util/delay.h>


int main(void) {
  STD_ReturnType status = E_OK;

  /* PB0 as output — replace with MCAL GPIO once the driver is ready. */
  DDRB |= (1u << PB0);

  while (E_OK == status) {
    PORTB ^= (1u << PB0);
    _delay_ms(500);
  }

  return 0;
}
