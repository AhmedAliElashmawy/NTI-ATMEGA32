/*
 * Author: Ahmed Ellamie
 * Email:  ahmed.ellamiee@gmail.com
 *
 * STUDENT TASK — GPIO.c  (ATmega32)
 * Implement every prototype from GPIO_interface.h. Return E_NOK on bad arguments.
 */

#include "STD_TYPES.h"
#include "GPIO_interface.h"
#include "GPIO_private.h"

/*
 * GPIO_SetPinDirection
 * 1. Reject Port > GPIO_PORTD or Pin > GPIO_PIN7.
 * 2. INPUT        : clear DDRx bit, clear PORTx bit (Hi-Z).
 * 3. OUTPUT       : set DDRx bit.
 * 4. INPUT_PULLUP : clear DDRx bit, set PORTx bit.
 * 5. Switch on Copy_u8Port and touch only that port's DDR/PORT.
 */

/*
 * GPIO_SetPinValue
 * 1. Validate port and pin.
 * 2. GPIO_HIGH -> set PORTx bit.  GPIO_LOW -> clear PORTx bit.
 */

/*
 * GPIO_GetPinValue
 * 1. Validate port, pin, and that Copy_pu8Value is not NULL.
 * 2. Read PINx bit into *Copy_pu8Value as GPIO_HIGH or GPIO_LOW.
 */

/*
 * GPIO_TogglePinValue
 * 1. Validate port and pin.
 * 2. Flip the matching PORTx bit (PORTx ^= mask).
 */

/*
 * GPIO_SetPortDirection
 * 1. Validate port. Direction is GPIO_INPUT or GPIO_OUTPUT.
 * 2. Write 0x00 or 0xFF to that port's DDRx.
 */

/*
 * GPIO_SetPortValue
 * 1. Validate port.
 * 2. Write Copy_u8Value to PORTx.
 */

/*
 * GPIO_GetPortValue
 * 1. Validate port and that Copy_pu8Value is not NULL.
 * 2. Read PINx into *Copy_pu8Value.
 */
