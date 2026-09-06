# 1 "main.c"
# 1 "<built-in>"
# 1 "<command-line>"
# 1 "main.c"
# 12 "main.c"
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
# 13 "main.c" 2
# 1 "MCAL/UART/UART_interface.h" 1
# 20 "MCAL/UART/UART_interface.h"
STD_ReturnType UART_Init(uint32 Copy_u32BaudRate);




STD_ReturnType UART_SendByte(uint8 Copy_u8Data);




STD_ReturnType UART_ReceiveByte(uint8 *Copy_pu8Data);




STD_ReturnType UART_SendString(const uint8 *Copy_pu8String);





STD_ReturnType UART_IsDataReady(void);





STD_ReturnType UART_SetRxInterrupt(uint8 Copy_u8State);
STD_ReturnType UART_SetTxInterrupt(uint8 Copy_u8State);
# 14 "main.c" 2
# 1 "c:/winavr-20100110/lib/gcc/../../avr/include/avr/io.h" 1 3
# 99 "c:/winavr-20100110/lib/gcc/../../avr/include/avr/io.h" 3
# 1 "c:/winavr-20100110/lib/gcc/../../avr/include/avr/sfr_defs.h" 1 3
# 126 "c:/winavr-20100110/lib/gcc/../../avr/include/avr/sfr_defs.h" 3
# 1 "c:/winavr-20100110/lib/gcc/../../avr/include/inttypes.h" 1 3
# 37 "c:/winavr-20100110/lib/gcc/../../avr/include/inttypes.h" 3
# 1 "c:/winavr-20100110/lib/gcc/../../avr/include/stdint.h" 1 3
# 121 "c:/winavr-20100110/lib/gcc/../../avr/include/stdint.h" 3
typedef int int8_t __attribute__((__mode__(__QI__)));
typedef unsigned int uint8_t __attribute__((__mode__(__QI__)));
typedef int int16_t __attribute__ ((__mode__ (__HI__)));
typedef unsigned int uint16_t __attribute__ ((__mode__ (__HI__)));
typedef int int32_t __attribute__ ((__mode__ (__SI__)));
typedef unsigned int uint32_t __attribute__ ((__mode__ (__SI__)));

typedef int int64_t __attribute__((__mode__(__DI__)));
typedef unsigned int uint64_t __attribute__((__mode__(__DI__)));
# 142 "c:/winavr-20100110/lib/gcc/../../avr/include/stdint.h" 3
typedef int16_t intptr_t;




typedef uint16_t uintptr_t;
# 159 "c:/winavr-20100110/lib/gcc/../../avr/include/stdint.h" 3
typedef int8_t int_least8_t;




typedef uint8_t uint_least8_t;




typedef int16_t int_least16_t;




typedef uint16_t uint_least16_t;




typedef int32_t int_least32_t;




typedef uint32_t uint_least32_t;







typedef int64_t int_least64_t;






typedef uint64_t uint_least64_t;
# 213 "c:/winavr-20100110/lib/gcc/../../avr/include/stdint.h" 3
typedef int8_t int_fast8_t;




typedef uint8_t uint_fast8_t;




typedef int16_t int_fast16_t;




typedef uint16_t uint_fast16_t;




typedef int32_t int_fast32_t;




typedef uint32_t uint_fast32_t;







typedef int64_t int_fast64_t;






typedef uint64_t uint_fast64_t;
# 273 "c:/winavr-20100110/lib/gcc/../../avr/include/stdint.h" 3
typedef int64_t intmax_t;




typedef uint64_t uintmax_t;
# 38 "c:/winavr-20100110/lib/gcc/../../avr/include/inttypes.h" 2 3
# 77 "c:/winavr-20100110/lib/gcc/../../avr/include/inttypes.h" 3
typedef int32_t int_farptr_t;



typedef uint32_t uint_farptr_t;
# 127 "c:/winavr-20100110/lib/gcc/../../avr/include/avr/sfr_defs.h" 2 3
# 100 "c:/winavr-20100110/lib/gcc/../../avr/include/avr/io.h" 2 3
# 206 "c:/winavr-20100110/lib/gcc/../../avr/include/avr/io.h" 3
# 1 "c:/winavr-20100110/lib/gcc/../../avr/include/avr/iom32.h" 1 3
# 207 "c:/winavr-20100110/lib/gcc/../../avr/include/avr/io.h" 2 3
# 408 "c:/winavr-20100110/lib/gcc/../../avr/include/avr/io.h" 3
# 1 "c:/winavr-20100110/lib/gcc/../../avr/include/avr/portpins.h" 1 3
# 409 "c:/winavr-20100110/lib/gcc/../../avr/include/avr/io.h" 2 3

# 1 "c:/winavr-20100110/lib/gcc/../../avr/include/avr/common.h" 1 3
# 411 "c:/winavr-20100110/lib/gcc/../../avr/include/avr/io.h" 2 3

# 1 "c:/winavr-20100110/lib/gcc/../../avr/include/avr/version.h" 1 3
# 413 "c:/winavr-20100110/lib/gcc/../../avr/include/avr/io.h" 2 3


# 1 "c:/winavr-20100110/lib/gcc/../../avr/include/avr/fuse.h" 1 3
# 248 "c:/winavr-20100110/lib/gcc/../../avr/include/avr/fuse.h" 3
typedef struct
{
    unsigned char low;
    unsigned char high;
} __fuse_t;
# 416 "c:/winavr-20100110/lib/gcc/../../avr/include/avr/io.h" 2 3


# 1 "c:/winavr-20100110/lib/gcc/../../avr/include/avr/lock.h" 1 3
# 419 "c:/winavr-20100110/lib/gcc/../../avr/include/avr/io.h" 2 3
# 15 "main.c" 2
# 1 "c:/winavr-20100110/lib/gcc/../../avr/include/util/delay.h" 1 3
# 39 "c:/winavr-20100110/lib/gcc/../../avr/include/util/delay.h" 3
# 1 "c:/winavr-20100110/lib/gcc/../../avr/include/util/delay_basic.h" 1 3
# 65 "c:/winavr-20100110/lib/gcc/../../avr/include/util/delay_basic.h" 3
static inline void _delay_loop_1(uint8_t __count) __attribute__((always_inline));
static inline void _delay_loop_2(uint16_t __count) __attribute__((always_inline));
# 80 "c:/winavr-20100110/lib/gcc/../../avr/include/util/delay_basic.h" 3
void
_delay_loop_1(uint8_t __count)
{
 __asm__ volatile (
  "1: dec %0" "\n\t"
  "brne 1b"
  : "=r" (__count)
  : "0" (__count)
 );
}
# 102 "c:/winavr-20100110/lib/gcc/../../avr/include/util/delay_basic.h" 3
void
_delay_loop_2(uint16_t __count)
{
 __asm__ volatile (
  "1: sbiw %0,1" "\n\t"
  "brne 1b"
  : "=w" (__count)
  : "0" (__count)
 );
}
# 40 "c:/winavr-20100110/lib/gcc/../../avr/include/util/delay.h" 2 3
# 79 "c:/winavr-20100110/lib/gcc/../../avr/include/util/delay.h" 3
static inline void _delay_us(double __us) __attribute__((always_inline));
static inline void _delay_ms(double __ms) __attribute__((always_inline));
# 109 "c:/winavr-20100110/lib/gcc/../../avr/include/util/delay.h" 3
void
_delay_ms(double __ms)
{
 uint16_t __ticks;
 double __tmp = ((8000000UL) / 4e3) * __ms;
 if (__tmp < 1.0)
  __ticks = 1;
 else if (__tmp > 65535)
 {

  __ticks = (uint16_t) (__ms * 10.0);
  while(__ticks)
  {

   _delay_loop_2(((8000000UL) / 4e3) / 10);
   __ticks --;
  }
  return;
 }
 else
  __ticks = (uint16_t)__tmp;
 _delay_loop_2(__ticks);
}
# 147 "c:/winavr-20100110/lib/gcc/../../avr/include/util/delay.h" 3
void
_delay_us(double __us)
{
 uint8_t __ticks;
 double __tmp = ((8000000UL) / 3e6) * __us;
 if (__tmp < 1.0)
  __ticks = 1;
 else if (__tmp > 255)
 {
  _delay_ms(__us / 1000.0);
  return;
 }
 else
  __ticks = (uint8_t)__tmp;
 _delay_loop_1(__ticks);
}
# 16 "main.c" 2


int main(void) {
  STD_ReturnType status = E_OK;


  (*(volatile uint8_t *)((0x17) + 0x20)) |= (1u << 0);

  while (E_OK == status) {
    (*(volatile uint8_t *)((0x18) + 0x20)) ^= (1u << 0);
    _delay_ms(500);
  }

  return 0;
}
