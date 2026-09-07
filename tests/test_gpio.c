#include <stdio.h>
#include <assert.h>
#include "STD_TYPES.h"
#include "GPIO_interface.h"
#include "mock_registers.h"

static int tests_run = 0;
static int tests_passed = 0;

#define TEST_ASSERT(cond, msg) do { \
    tests_run++; \
    if (cond) { \
        tests_passed++; \
        printf("  [PASS] %s\n", msg); \
    } else { \
        printf("  [FAIL] %s (line %d)\n", msg, __LINE__); \
        assert(cond); \
    } \
} while(0)

void test_GPIO_SetPinDirection(void) {
    printf("\nRunning: test_GPIO_SetPinDirection\n");
    mock_registers_reset();

    /* Test valid output on PORTA PIN0 */
    STD_ReturnType ret = GPIO_SetPinDirection(GPIO_PORTA, GPIO_PIN0, GPIO_OUTPUT);
    TEST_ASSERT(ret == E_OK, "SetPinDirection PORTA PIN0 OUTPUT returns E_OK");
    TEST_ASSERT(mock_DDRA == (1 << 0), "DDRA bit 0 is set");

    /* Test valid input pullup on PORTB PIN3 */
    ret = GPIO_SetPinDirection(GPIO_PORTB, GPIO_PIN3, GPIO_INPUT_PULLUP);
    TEST_ASSERT(ret == E_OK, "SetPinDirection PORTB PIN3 INPUT_PULLUP returns E_OK");
    TEST_ASSERT((mock_DDRB & (1 << 3)) == 0, "DDRB bit 3 is cleared");
    TEST_ASSERT((mock_PORTB & (1 << 3)) != 0, "PORTB bit 3 is set (pullup enabled)");

    /* Test invalid arguments */
    ret = GPIO_SetPinDirection(GPIO_PORTD + 1, GPIO_PIN0, GPIO_OUTPUT);
    TEST_ASSERT(ret == E_NOK, "SetPinDirection invalid port returns E_NOK");

    ret = GPIO_SetPinDirection(GPIO_PORTA, GPIO_PIN7 + 1, GPIO_OUTPUT);
    TEST_ASSERT(ret == E_NOK, "SetPinDirection invalid pin returns E_NOK");

    ret = GPIO_SetPinDirection(GPIO_PORTA, GPIO_PIN0, 99);
    TEST_ASSERT(ret == E_NOK, "SetPinDirection invalid direction returns E_NOK");
}

void test_GPIO_SetPinValue(void) {
    printf("\nRunning: test_GPIO_SetPinValue\n");
    mock_registers_reset();

    /* Set HIGH on PIN5 */
    STD_ReturnType ret = GPIO_SetPinValue(GPIO_PORTC, GPIO_PIN5, GPIO_HIGH);
    TEST_ASSERT(ret == E_OK, "SetPinValue PORTC PIN5 HIGH returns E_OK");
    TEST_ASSERT((mock_PORTC & (1 << 5)) != 0, "PORTC bit 5 is set");

    /* Set LOW on PIN5 */
    ret = GPIO_SetPinValue(GPIO_PORTC, GPIO_PIN5, GPIO_LOW);
    TEST_ASSERT(ret == E_OK, "SetPinValue PORTC PIN5 LOW returns E_OK");
    TEST_ASSERT((mock_PORTC & (1 << 5)) == 0, "PORTC bit 5 is cleared");

    /* Reject invalid level */
    ret = GPIO_SetPinValue(GPIO_PORTC, GPIO_PIN5, 2);
    TEST_ASSERT(ret == E_NOK, "SetPinValue invalid value returns E_NOK");
}

void test_GPIO_GetPinValue(void) {
    printf("\nRunning: test_GPIO_GetPinValue\n");
    mock_registers_reset();

    uint8 val = 0;
    mock_PINA = (1 << 4); /* PIN4 high */

    STD_ReturnType ret = GPIO_GetPinValue(GPIO_PORTA, GPIO_PIN4, &val);
    TEST_ASSERT(ret == E_OK, "GetPinValue valid call returns E_OK");
    TEST_ASSERT(val == GPIO_HIGH, "GetPinValue reads HIGH from PINA bit 4");

    ret = GPIO_GetPinValue(GPIO_PORTA, GPIO_PIN3, &val);
    TEST_ASSERT(ret == E_OK, "GetPinValue on low pin returns E_OK");
    TEST_ASSERT(val == GPIO_LOW, "GetPinValue reads LOW from PINA bit 3");

    /* NULL pointer safety check */
    ret = GPIO_GetPinValue(GPIO_PORTA, GPIO_PIN0, NULL);
    TEST_ASSERT(ret == E_NOK, "GetPinValue rejects NULL pointer with E_NOK");
}

void test_GPIO_TogglePinValue(void) {
    printf("\nRunning: test_GPIO_TogglePinValue\n");
    mock_registers_reset();

    mock_PORTD = 0b00000000;
    STD_ReturnType ret = GPIO_TogglePinValue(GPIO_PORTD, GPIO_PIN2);
    TEST_ASSERT(ret == E_OK, "TogglePinValue returns E_OK");
    TEST_ASSERT(mock_PORTD == (1 << 2), "PORTD bit 2 toggled from 0 to 1");

    ret = GPIO_TogglePinValue(GPIO_PORTD, GPIO_PIN2);
    TEST_ASSERT(ret == E_OK, "TogglePinValue second call returns E_OK");
    TEST_ASSERT(mock_PORTD == 0, "PORTD bit 2 toggled from 1 to 0");
}

void test_GPIO_PortOperations(void) {
    printf("\nRunning: test_GPIO_PortOperations\n");
    mock_registers_reset();

    /* SetPortDirection Output */
    STD_ReturnType ret = GPIO_SetPortDirection(GPIO_PORTA, GPIO_OUTPUT);
    TEST_ASSERT(ret == E_OK, "SetPortDirection OUTPUT returns E_OK");
    TEST_ASSERT(mock_DDRA == 0xFF, "DDRA set to 0xFF on GPIO_OUTPUT");

    /* SetPortDirection Input */
    ret = GPIO_SetPortDirection(GPIO_PORTA, GPIO_INPUT);
    TEST_ASSERT(ret == E_OK, "SetPortDirection INPUT returns E_OK");
    TEST_ASSERT(mock_DDRA == 0x00, "DDRA set to 0x00 on GPIO_INPUT");

    /* SetPortValue full 8-bit pattern */
    ret = GPIO_SetPortValue(GPIO_PORTB, 0xAA);
    TEST_ASSERT(ret == E_OK, "SetPortValue 0xAA returns E_OK");
    TEST_ASSERT(mock_PORTB == 0xAA, "PORTB received 0xAA");

    /* GetPortValue */
    mock_PINC = 0x55;
    uint8 port_val = 0;
    ret = GPIO_GetPortValue(GPIO_PORTC, &port_val);
    TEST_ASSERT(ret == E_OK, "GetPortValue returns E_OK");
    TEST_ASSERT(port_val == 0x55, "GetPortValue read 0x55 from PINC");

    /* GetPortValue NULL safety */
    ret = GPIO_GetPortValue(GPIO_PORTC, NULL);
    TEST_ASSERT(ret == E_NOK, "GetPortValue rejects NULL pointer with E_NOK");
}

int main(void) {
    printf("======================================\n");
    printf("     RUNNING GPIO HOST UNIT TESTS     \n");
    printf("======================================\n");

    test_GPIO_SetPinDirection();
    test_GPIO_SetPinValue();
    test_GPIO_GetPinValue();
    test_GPIO_TogglePinValue();
    test_GPIO_PortOperations();

    printf("\n======================================\n");
    printf("Results: %d/%d tests passed successfully!\n", tests_passed, tests_run);
    printf("======================================\n");

    return (tests_passed == tests_run) ? 0 : 1;
}
