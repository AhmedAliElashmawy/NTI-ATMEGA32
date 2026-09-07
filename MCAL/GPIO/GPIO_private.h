#ifndef GPIO_PRIVATE_H
#define GPIO_PRIVATE_H

/*
 * MCAL GPIO private layer (ATmega32)
 * Include this file ONLY from GPIO.c. Never from main, HAL, or Logic.
 */

#ifdef UNIT_TEST
    /* In unit tests on PC, redirect registers to mock memory variables */
    #include "mock_registers.h"
    #define GPIO_PORTA_REG    mock_PORTA
    #define GPIO_DDRA_REG     mock_DDRA
    #define GPIO_PINA_REG     mock_PINA

    #define GPIO_PORTB_REG    mock_PORTB
    #define GPIO_DDRB_REG     mock_DDRB
    #define GPIO_PINB_REG     mock_PINB

    #define GPIO_PORTC_REG    mock_PORTC
    #define GPIO_DDRC_REG     mock_DDRC
    #define GPIO_PINC_REG     mock_PINC

    #define GPIO_PORTD_REG    mock_PORTD
    #define GPIO_DDRD_REG     mock_DDRD
    #define GPIO_PIND_REG     mock_PIND
#else
    #define GPIO_PORTA_REG    (*(volatile uint8 *)0x3B)
    #define GPIO_DDRA_REG     (*(volatile uint8 *)0x3A)
    #define GPIO_PINA_REG     (*(volatile uint8 *)0x39)

    #define GPIO_PORTB_REG    (*(volatile uint8 *)0x38)
    #define GPIO_DDRB_REG     (*(volatile uint8 *)0x37)
    #define GPIO_PINB_REG     (*(volatile uint8 *)0x36)

    #define GPIO_PORTC_REG    (*(volatile uint8 *)0x35)
    #define GPIO_DDRC_REG     (*(volatile uint8 *)0x34)
    #define GPIO_PINC_REG     (*(volatile uint8 *)0x33)

    #define GPIO_PORTD_REG    (*(volatile uint8 *)0x32)
    #define GPIO_DDRD_REG     (*(volatile uint8 *)0x31)
    #define GPIO_PIND_REG     (*(volatile uint8 *)0x30)
#endif

#endif /* GPIO_PRIVATE_H */
