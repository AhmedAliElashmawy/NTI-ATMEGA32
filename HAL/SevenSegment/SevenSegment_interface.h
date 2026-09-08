#ifndef SEVENSEGMENT_INTERFACE_H
#define SEVENSEGMENT_INTERFACE_H

#include "STD_TYPES.h"
#include "GPIO_interface.h"

/* ---------------- 7-Segment Display Types ---------------- */
#define SEVENSEGMENT_COMMON_CATHODE    0u
#define SEVENSEGMENT_COMMON_ANODE      1u

/* ---------------- 7-Segment Numbers ---------------- */
#define SEVENSEGMENT_NUM_0             0u
#define SEVENSEGMENT_NUM_1             1u
#define SEVENSEGMENT_NUM_2             2u
#define SEVENSEGMENT_NUM_3             3u
#define SEVENSEGMENT_NUM_4             4u
#define SEVENSEGMENT_NUM_5             5u
#define SEVENSEGMENT_NUM_6             6u
#define SEVENSEGMENT_NUM_7             7u
#define SEVENSEGMENT_NUM_8             8u
#define SEVENSEGMENT_NUM_9             9u

/*
 * Description : Initialize the port connected to the 7-segment display as output.
 */
STD_ReturnType SevenSegment_init(uint8 Copy_u8Port);

/*
 * Description : Display a number (SEVENSEGMENT_NUM_0 to SEVENSEGMENT_NUM_9) on the 7-segment display.
 */
STD_ReturnType SevenSegment_WriteNumber(uint8 Copy_u8Port, uint8 Copy_u8Type, uint8 Copy_u8Number);

/*
 * Description : Turn off all segments on the specified port.
 */
STD_ReturnType SevenSegment_Clear(uint8 Copy_u8Port, uint8 Copy_u8Type);

#endif /* SEVENSEGMENT_INTERFACE_H */