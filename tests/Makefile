CC := gcc
CFLAGS := -Wall -Wextra -Werror -std=gnu99 -DUNIT_TEST -I. -I../LIB -I../MCAL/GPIO

SRCS := test_gpio.c mock_registers.c ../MCAL/GPIO/GPIO.c
TARGET := run_tests

all: $(TARGET)

$(TARGET): $(SRCS)
	$(CC) $(CFLAGS) $(SRCS) -o $(TARGET)

run: $(TARGET)
	./$(TARGET)

clean:
	rm -f $(TARGET)

.PHONY: all run clean
