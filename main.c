/*
 * AVR_NTI application entry.
 * Layers: LIB (types) -> MCAL (drivers) -> HAL (devices) -> Logic (app) ->
 * main.
 */

#define F_CPU 8000000UL

#include "STD_TYPES.h"
#include "UART_interface.h"
#include <avr/io.h>
#include <util/delay.h>
#include "GPIO_interface.h"

int main(void) {
  GPIO_SetPinDirection(GPIO_PORTA, GPIO_PIN0, GPIO_OUTPUT);

  while (1) {
    GPIO_SetPinValue(GPIO_PORTA, GPIO_PIN0, GPIO_HIGH);
    _delay_ms(500);
    GPIO_SetPinValue(GPIO_PORTA, GPIO_PIN0, GPIO_LOW);
    _delay_ms(500);
  }

  return 0;
}
