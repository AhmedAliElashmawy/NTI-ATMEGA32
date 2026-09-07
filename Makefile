MCU      ?= atmega32
F_CPU    ?= 8000000UL
TARGET   ?= program

BUILD_DIR := build

CC      := avr-gcc
OBJCOPY := avr-objcopy
OBJDUMP := avr-objdump
SIZE    := avr-size

# Strict warning flags for embedded code quality
CFLAGS  := -mmcu=$(MCU) -DF_CPU=$(F_CPU) -Os -Wall -Wextra -Werror -std=gnu99 -ffunction-sections -fdata-sections
LDFLAGS := -mmcu=$(MCU) -Wl,--gc-sections -Wl,-Map=$(BUILD_DIR)/$(TARGET).map

# Search the whole project: root + 4 directory levels (LIB/MCAL/HAL/Logic and nested drivers).
SRCS := $(wildcard *.c)
SRCS += $(wildcard */*.c)
SRCS += $(wildcard */*/*.c)
SRCS += $(wildcard */*/*/*.c)
SRCS += $(wildcard */*/*/*/*.c)
SRCS := $(filter-out $(BUILD_DIR)/% tests/%,$(SRCS))

HDRS := $(wildcard *.h)
HDRS += $(wildcard */*.h)
HDRS += $(wildcard */*/*.h)
HDRS += $(wildcard */*/*/*.h)
HDRS += $(wildcard */*/*/*/*.h)
HDRS := $(filter-out $(BUILD_DIR)/% tests/%,$(HDRS))

ifeq ($(strip $(SRCS)),)
$(error No .c files found. Put sources in ., LIB, MCAL, HAL, or Logic.)
endif

OBJS     := $(patsubst %.c,$(BUILD_DIR)/%.o,$(SRCS))
PREPROCS := $(patsubst %.c,$(BUILD_DIR)/%.i,$(SRCS))
ASMS     := $(patsubst %.c,$(BUILD_DIR)/%.s,$(SRCS))

INC_DIRS := $(sort . LIB MCAL HAL Logic $(dir $(SRCS)) $(dir $(HDRS)))
INCLUDES := $(addprefix -I,$(INC_DIRS))

# Flash and RAM budget limits for ATmega32
# ATmega32 has 32768 bytes Flash and 2048 bytes SRAM
FLASH_LIMIT ?= 32768
SRAM_LIMIT  ?= 2048

.PHONY: all clean size verify check-size test

all: $(PREPROCS) $(ASMS) $(BUILD_DIR)/$(TARGET).hex $(BUILD_DIR)/$(TARGET).bin size check-size

$(BUILD_DIR)/%.i: %.c
	mkdir -p $(dir $@)
	$(CC) $(CFLAGS) $(INCLUDES) -E $< -o $@

$(BUILD_DIR)/%.s: %.c
	mkdir -p $(dir $@)
	$(CC) $(CFLAGS) $(INCLUDES) -S $< -o $@

$(BUILD_DIR)/%.o: %.c
	mkdir -p $(dir $@)
	$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

$(BUILD_DIR)/$(TARGET).elf: $(OBJS)
	mkdir -p $(BUILD_DIR)
	$(CC) $(LDFLAGS) $(OBJS) -o $@

$(BUILD_DIR)/$(TARGET).hex: $(BUILD_DIR)/$(TARGET).elf
	$(OBJCOPY) -O ihex -R .eeprom $< $@
	@echo HEX ready: $@

$(BUILD_DIR)/$(TARGET).bin: $(BUILD_DIR)/$(TARGET).elf
	$(OBJCOPY) -O binary -R .eeprom $< $@
	@echo BIN ready: $@

size: $(BUILD_DIR)/$(TARGET).elf
	$(SIZE) $<

check-size: $(BUILD_DIR)/$(TARGET).elf
	@echo "Checking memory footprint against ATmega32 budgets..."
	@FLASH_USED=$$($(SIZE) -A $< | grep -E "^\.text|^\.data" | awk '{s+=$$2} END {print s}'); \
	SRAM_USED=$$($(SIZE) -A $< | grep -E "^\.data|^\.bss" | awk '{s+=$$2} END {print s}'); \
	FLASH_USED=$${FLASH_USED:-0}; \
	SRAM_USED=$${SRAM_USED:-0}; \
	echo "  Flash used: $$FLASH_USED / $(FLASH_LIMIT) bytes"; \
	echo "  SRAM used:  $$SRAM_USED / $(SRAM_LIMIT) bytes"; \
	if [ $$FLASH_USED -gt $(FLASH_LIMIT) ]; then \
		echo "ERROR: Flash limit exceeded ($$FLASH_USED > $(FLASH_LIMIT))" >&2; \
		exit 1; \
	fi; \
	if [ $$SRAM_USED -gt $(SRAM_LIMIT) ]; then \
		echo "ERROR: SRAM limit exceeded ($$SRAM_USED > $(SRAM_LIMIT))" >&2; \
		exit 1; \
	fi; \
	echo "Memory budget check passed."

test:
	$(MAKE) -C tests run

verify: all
	@echo BUILD_OK MCU=$(MCU) F_CPU=$(F_CPU) SRCS=$(SRCS)

clean:
	rm -rf $(BUILD_DIR)
	$(MAKE) -C tests clean 2>/dev/null || true
	@echo Cleaned $(BUILD_DIR)
