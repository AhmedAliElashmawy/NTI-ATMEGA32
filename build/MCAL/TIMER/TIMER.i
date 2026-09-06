# 1 "MCAL/TIMER/TIMER.c"
# 1 "<built-in>"
# 1 "<command-line>"
# 1 "MCAL/TIMER/TIMER.c"
# 9 "MCAL/TIMER/TIMER.c"
# 1 "LIB/STD_TYPES.h" 1
# 11 "LIB/STD_TYPES.h"
typedef unsigned char uint8;
typedef unsigned short uint16;
typedef unsigned long uint32;
typedef signed char sint8;
typedef signed short sint16;
typedef signed long sint32;

typedef unsigned char uint8_h;

typedef enum
{
    E_OK = 0,
    E_NOK = 1
} STD_ReturnType;
# 10 "MCAL/TIMER/TIMER.c" 2
# 1 "MCAL/TIMER/TIMER_interface.h" 1
# 52 "MCAL/TIMER/TIMER_interface.h"
STD_ReturnType TIMER0_Init(uint8 Copy_u8Mode);




STD_ReturnType TIMER0_Start(uint8 Copy_u8Prescaler);




STD_ReturnType TIMER0_Stop(void);




STD_ReturnType TIMER0_SetCompareValue(uint8 Copy_u8Value);




STD_ReturnType TIMER0_SetCompareOutput(uint8 Copy_u8ComMode);





STD_ReturnType TIMER0_SetOverflowInterrupt(uint8 Copy_u8State);
STD_ReturnType TIMER0_SetCompareInterrupt(uint8 Copy_u8State);




STD_ReturnType TIMER1_Init(uint8 Copy_u8Mode);




STD_ReturnType TIMER1_Start(uint8 Copy_u8Prescaler);
STD_ReturnType TIMER1_Stop(void);




STD_ReturnType TIMER1_SetCompareA(uint16 Copy_u16Value);
STD_ReturnType TIMER1_SetICR1(uint16 Copy_u16Value);
# 11 "MCAL/TIMER/TIMER.c" 2
# 1 "MCAL/TIMER/TIMER_private.h" 1
# 12 "MCAL/TIMER/TIMER.c" 2
