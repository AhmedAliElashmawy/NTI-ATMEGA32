#ifndef BIT_MATH_H
#define BIT_MATH_H

#define SET_BIT(REG, BIT) ((REG) |= (1u << (BIT)))

#define CLR_BIT(REG, BIT) ((REG) &= ~(1u << (BIT)))

#endif