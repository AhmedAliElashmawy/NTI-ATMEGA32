CC := gcc
CFLAGS := -Wall -Wextra -Werror -std=gnu99 -DUNIT_TEST -I. -I../LIB -I../MCAL/GPIO -I../HAL/SevenSegment

GPIO_SRCS := test_gpio.c mock_registers.c ../MCAL/GPIO/GPIO.c
SEVENSEG_SRCS := test_sevensegment.c mock_registers.c ../MCAL/GPIO/GPIO.c ../HAL/SevenSegment/SevenSegment.c

TARGETS := test_gpio test_sevensegment

all: $(TARGETS)

test_gpio: $(GPIO_SRCS)
	$(CC) $(CFLAGS) $(GPIO_SRCS) -o test_gpio

test_sevensegment: $(SEVENSEG_SRCS)
	$(CC) $(CFLAGS) $(SEVENSEG_SRCS) -o test_sevensegment

run: $(TARGETS)
	./test_gpio
	./test_sevensegment

clean:
	rm -f $(TARGETS) run_tests

.PHONY: all run clean
