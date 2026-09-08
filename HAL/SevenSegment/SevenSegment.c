#include "STD_TYPES.h"
#include "BIT_MATH.h"
#include "GPIO_interface.h"

#include "SevenSegment_interface.h"
#include "SevenSegment_private.h"

/* Bitmask tracking initialized ports (bit 0 = PORTA, bit 1 = PORTB, etc.) */
static uint8 s_u8InitializedPorts = 0x00u;

STD_ReturnType SevenSegment_init(uint8 Copy_u8Port) {
    if (Copy_u8Port > GPIO_PORTD) {
        return E_NOK;
    }

    STD_ReturnType Local_u8State = GPIO_SetPortDirection(Copy_u8Port, GPIO_OUTPUT);
    if (Local_u8State == E_OK) {
        /* Mark this port as initialized */
        SET_BIT(s_u8InitializedPorts, Copy_u8Port);
        return E_OK;
    }

    return E_NOK;
}

STD_ReturnType SevenSegment_WriteNumber(uint8 Copy_u8Port, uint8 Copy_u8Type, uint8 Copy_u8Number) {
    if (Copy_u8Port > GPIO_PORTD || Copy_u8Number > SEVENSEGMENT_MAX_NUMBER) {
        return E_NOK;
    }

    if (Copy_u8Type != SEVENSEGMENT_COMMON_CATHODE && Copy_u8Type != SEVENSEGMENT_COMMON_ANODE) {
        return E_NOK;
    }

    if (READ_BIT(s_u8InitializedPorts, Copy_u8Port) == 0u) {
        return E_NOK;
    }

    uint8 Local_u8Pattern = SevenSegment_numbers[Copy_u8Number];

    /* Invert if Common Anode */
    if (Copy_u8Type == SEVENSEGMENT_COMMON_ANODE) {
        Local_u8Pattern = ~Local_u8Pattern;
    }

    return GPIO_SetPortValue(Copy_u8Port, Local_u8Pattern);
}

STD_ReturnType SevenSegment_Clear(uint8 Copy_u8Port, uint8 Copy_u8Type) {
    if (Copy_u8Port > GPIO_PORTD) {
        return E_NOK;
    }

    if (Copy_u8Type != SEVENSEGMENT_COMMON_CATHODE && Copy_u8Type != SEVENSEGMENT_COMMON_ANODE) {
        return E_NOK;
    }

    if (READ_BIT(s_u8InitializedPorts, Copy_u8Port) == 0u) {
        return E_NOK;
    }

    /* Set defined off-value according to display type */
    uint8 Local_u8OffValue = (Copy_u8Type == SEVENSEGMENT_COMMON_CATHODE) ? 
                              SEVENSEGMENT_OFF_CATHODE : SEVENSEGMENT_OFF_ANODE;

    return GPIO_SetPortValue(Copy_u8Port, Local_u8OffValue);
}
