#ifndef SEVENSEGMENT_PRIVATE_H
#define SEVENSEGMENT_PRIVATE_H

#include "STD_TYPES.h"

/* ---------------- Range & Bounds ---------------- */
#define SEVENSEGMENT_MIN_NUMBER        0u
#define SEVENSEGMENT_MAX_NUMBER        9u
#define SEVENSEGMENT_NUMBERS_COUNT     10u

/* ---------------- Turn Off Values ---------------- */
#define SEVENSEGMENT_OFF_CATHODE       0x00u
#define SEVENSEGMENT_OFF_ANODE         0xFFu

/*
 * BCD to 7-Segment digit patterns (Common Cathode):
 * Bit mapping: bit 0: a, bit 1: b, bit 2: c, bit 3: d,
 *              bit 4: e, bit 5: f, bit 6: g, bit 7: dp (off)
 */
static const uint8 SevenSegment_numbers[SEVENSEGMENT_NUMBERS_COUNT] = {
    0x3F, /* 0: 0b00111111 */
    0x06, /* 1: 0b00000110 */
    0x5B, /* 2: 0b01011011 */
    0x4F, /* 3: 0b01001111 */
    0x66, /* 4: 0b01100110 */
    0x6D, /* 5: 0b01101101 */
    0x7D, /* 6: 0b01111101 */
    0x07, /* 7: 0b00000111 */
    0x7F, /* 8: 0b01111111 */
    0x6F  /* 9: 0b01101111 */
};

#endif /* SEVENSEGMENT_PRIVATE_H */
