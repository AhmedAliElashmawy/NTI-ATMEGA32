# NTI ATmega32 Embedded Drivers Project

This repository is developed as part of the NTI (National Telecommunication Institute) Embedded Systems program. It focuses on implementing layered firmware and modular device drivers for the Microchip/Atmel ATmega32 8-bit microcontroller.

---

## Project Structure & Architecture

The codebase is organized using a layered embedded architecture:

```
NTI-ATMEGA32/
├── LIB/              # Common utilities, standard types (STD_TYPES), and bit math macros (BIT_MATH)
├── MCAL/             # Microcontroller Abstraction Layer (hardware-specific peripheral drivers)
│   ├── ADC/          # Analog-to-Digital Converter driver
│   ├── GPIO/         # General-Purpose Input/Output driver
│   ├── I2C/          # Inter-Integrated Circuit (TWI) driver
│   ├── INTERRUPT/    # External and peripheral interrupt drivers
│   ├── SPI/          # Serial Peripheral Interface driver
│   ├── TIMER/        # Hardware timer drivers (Timer0, Timer1, Timer2)
│   └── UART/         # Universal Asynchronous Receiver-Transmitter driver
├── HAL/              # Hardware Abstraction Layer (drivers for external modules, sensors, actuators)
├── Logic/            # Application logic and control algorithms
├── main.c            # Application entry point
└── Makefile          # Build system configuration
```

---

## Driver Milestones & Development Order

Drivers are implemented sequentially in ordered stages, completing each prerequisite driver before advancing to the next peripheral:

### Phase 1: Microcontroller Abstraction Layer (MCAL)

| Step | Driver | Scope & Deliverables | Progression |
| :--- | :--- | :--- | :--- |
| 1 | **GPIO (DIO)** | Pin and port direction, digital read/write, internal pull-up control | Complete to unlock EXTI & HAL foundation |
| 2 | **EXTI & GIE** | Global Interrupt Enable, INT0/INT1/INT2 sense control, ISR callbacks | Complete to unlock interrupt-driven drivers |
| 3 | **ADC** | Single-ended channel conversion, prescaler configuration, interrupt and polling modes | Complete to unlock analog sensors |
| 4 | **TIMER** | Timer0/1/2 normal & CTC modes, PWM generation, Input Capture Unit (ICU) | Complete to unlock precise timing & motor control |
| 5 | **UART** | Full-duplex asynchronous transmission, configurable baud rates, RX/TX interrupts | Complete to unlock serial logging & communication |
| 6 | **SPI** | Master/Slave modes, clock polarity/phase control, synchronous data bus transfer | Complete to unlock SPI peripherals |
| 7 | **I2C (TWI)** | Start/Stop condition, slave addressing, ACK/NACK signaling, master/slave operation | Complete to unlock I2C sensors & EEPROM |
| 8 | **WDT** | Watchdog safety timeout configuration and reset sequence | Completes core MCAL layer |

### Phase 2: Hardware Abstraction Layer (HAL)

Built on top of the completed MCAL drivers to interface external modules:

| Step | Module | Required MCAL Driver | Scope & Deliverables |
| :--- | :--- | :--- | :--- |
| 9 | **7-Segment Display** | GPIO | BCD and direct drive, multiplexing display logic |
| 10 | **Character LCD** | GPIO | 4-bit and 8-bit mode command/data routines, custom characters |
| 11 | **Keypad (4x4)** | GPIO | Row-column scanning and key debouncing algorithms |
| 12 | **Sensors** | ADC, TIMER (ICU) | LM35 analog temperature reading, Ultrasonic distance measurement |
| 13 | **Actuators** | GPIO, TIMER (PWM) | DC Motor via H-Bridge, Stepper Motor sequencing, Servo angle control |

---

## Building & Flashing Outputs

When compiling the project, `main.c` is compiled together with all layered drivers into the `build/` directory. The build system automatically generates multiple file formats ready to be programmed into the ATmega32:

- **Intel HEX (`build/program.hex`):** The standard hexadecimal firmware image used to flash the ATmega32 on-chip flash memory via programmer utilities such as AVRDUDE and hardware programmers like USBasp.
- **Raw Binary (`build/program.bin`):** Flat binary image format directly representing executable microcontroller data.
- **ELF File (`build/program.elf`):** Executable containing machine code, symbols, and debugging data.
- **Preprocessed (`.i`) and Assembly (`.s`) Files:** Intermediate representations generated per source file inside `build/` for debugging and instruction analysis.

### Build Commands

Compile the project and produce all binary and hexadecimal outputs:

```bash
make
```

Clean all generated build artifacts:

```bash
make clean
```
