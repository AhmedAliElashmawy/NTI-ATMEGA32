#ifndef BIT_MATH_H
#define BIT_MATH_H

#define SET_BIT(REG, BIT) ((REG) |= (1u << (BIT)))

#define CLR_BIT(REG, BIT) ((REG) &= ~(1u << (BIT)))

#define TOGGLE_BIT(REG, BIT) ((REG) ^= (1U << (BIT)))

#define READ_BIT(REG, BIT)   (((REG) >> (BIT)) & 1U)
#endif