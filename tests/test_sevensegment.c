#include <stdio.h>
#include <assert.h>
#include "STD_TYPES.h"
#include "GPIO_interface.h"
#include "SevenSegment_interface.h"
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

/* Test digits lookup reference (Common Cathode) */
static const uint8 expected_digits[10] = {
    0x3F, 0x06, 0x5B, 0x4F, 0x66, 0x6D, 0x7D, 0x07, 0x7F, 0x6F
};

void test_SevenSegment_UninitializedGuard(void) {
    printf("\nRunning: test_SevenSegment_UninitializedGuard\n");
    mock_registers_reset();

    /* Calling WriteNumber before init must be rejected with E_NOK */
    STD_ReturnType ret = SevenSegment_WriteNumber(GPIO_PORTA, SEVENSEGMENT_COMMON_CATHODE, SEVENSEGMENT_NUM_0);
    TEST_ASSERT(ret == E_NOK, "WriteNumber on uninitialized PORTA returns E_NOK");

    /* Calling Clear before init must also be rejected */
    ret = SevenSegment_Clear(GPIO_PORTA, SEVENSEGMENT_COMMON_CATHODE);
    TEST_ASSERT(ret == E_NOK, "Clear on uninitialized PORTA returns E_NOK");

    /* Verify mock registers were untouched */
    TEST_ASSERT(mock_PORTA == 0x00, "mock_PORTA remained 0x00");
    TEST_ASSERT(mock_DDRA == 0x00, "mock_DDRA remained 0x00");
}

void test_SevenSegment_Init(void) {
    printf("\nRunning: test_SevenSegment_Init\n");
    mock_registers_reset();

    /* Initialize PORTA */
    STD_ReturnType ret = SevenSegment_init(GPIO_PORTA);
    TEST_ASSERT(ret == E_OK, "SevenSegment_init PORTA returns E_OK");
    TEST_ASSERT(mock_DDRA == 0xFF, "DDRA configured as all outputs (0xFF)");

    /* Initialize PORTD */
    ret = SevenSegment_init(GPIO_PORTD);
    TEST_ASSERT(ret == E_OK, "SevenSegment_init PORTD returns E_OK");
    TEST_ASSERT(mock_DDRD == 0xFF, "DDRD configured as all outputs (0xFF)");

    /* Invalid port */
    ret = SevenSegment_init(GPIO_PORTD + 1);
    TEST_ASSERT(ret == E_NOK, "SevenSegment_init with invalid port returns E_NOK");

    /* PORTB was never initialized, so writing to it must still fail */
    ret = SevenSegment_WriteNumber(GPIO_PORTB, SEVENSEGMENT_COMMON_CATHODE, SEVENSEGMENT_NUM_5);
    TEST_ASSERT(ret == E_NOK, "WriteNumber on uninitialized PORTB returns E_NOK");
}

void test_SevenSegment_WriteCommonCathode(void) {
    printf("\nRunning: test_SevenSegment_WriteCommonCathode\n");
    mock_registers_reset();

    /* Test all digits 0-9 on initialized PORTA */
    for (uint8 i = SEVENSEGMENT_NUM_0; i <= SEVENSEGMENT_NUM_9; i++) {
        STD_ReturnType ret = SevenSegment_WriteNumber(GPIO_PORTA, SEVENSEGMENT_COMMON_CATHODE, i);
        TEST_ASSERT(ret == E_OK, "WriteNumber returns E_OK for valid digit");
        TEST_ASSERT(mock_PORTA == expected_digits[i], "PORTA output matches Common Cathode pattern");
    }
}

void test_SevenSegment_WriteCommonAnode(void) {
    printf("\nRunning: test_SevenSegment_WriteCommonAnode\n");
    mock_registers_reset();

    /* Test digits with Common Anode (inverted patterns) */
    STD_ReturnType ret = SevenSegment_WriteNumber(GPIO_PORTA, SEVENSEGMENT_COMMON_ANODE, SEVENSEGMENT_NUM_0);
    TEST_ASSERT(ret == E_OK, "WriteNumber returns E_OK for Common Anode digit 0");
    TEST_ASSERT(mock_PORTA == (uint8)(~expected_digits[0]), "PORTA output matches inverted pattern (~0x3F)");

    ret = SevenSegment_WriteNumber(GPIO_PORTA, SEVENSEGMENT_COMMON_ANODE, SEVENSEGMENT_NUM_8);
    TEST_ASSERT(ret == E_OK, "WriteNumber returns E_OK for Common Anode digit 8");
    TEST_ASSERT(mock_PORTA == (uint8)(~expected_digits[8]), "PORTA output matches inverted pattern (~0x7F)");
}

void test_SevenSegment_InvalidInputs(void) {
    printf("\nRunning: test_SevenSegment_InvalidInputs\n");

    /* Invalid number (> 9) */
    STD_ReturnType ret = SevenSegment_WriteNumber(GPIO_PORTA, SEVENSEGMENT_COMMON_CATHODE, 10);
    TEST_ASSERT(ret == E_NOK, "WriteNumber rejects number > 9 with E_NOK");

    /* Invalid port */
    ret = SevenSegment_WriteNumber(GPIO_PORTD + 1, SEVENSEGMENT_COMMON_CATHODE, SEVENSEGMENT_NUM_3);
    TEST_ASSERT(ret == E_NOK, "WriteNumber rejects invalid port with E_NOK");

    /* Invalid display type */
    ret = SevenSegment_WriteNumber(GPIO_PORTA, 99, SEVENSEGMENT_NUM_3);
    TEST_ASSERT(ret == E_NOK, "WriteNumber rejects invalid display type with E_NOK");
}

void test_SevenSegment_Clear(void) {
    printf("\nRunning: test_SevenSegment_Clear\n");
    mock_registers_reset();

    /* Write a digit first */
    SevenSegment_WriteNumber(GPIO_PORTA, SEVENSEGMENT_COMMON_CATHODE, SEVENSEGMENT_NUM_8);
    TEST_ASSERT(mock_PORTA == 0x7F, "PORTA has digit 8 pattern");

    /* Clear Common Cathode -> 0x00 */
    STD_ReturnType ret = SevenSegment_Clear(GPIO_PORTA, SEVENSEGMENT_COMMON_CATHODE);
    TEST_ASSERT(ret == E_OK, "Clear Common Cathode returns E_OK");
    TEST_ASSERT(mock_PORTA == 0x00, "PORTA cleared to 0x00");

    /* Clear Common Anode -> 0xFF */
    ret = SevenSegment_Clear(GPIO_PORTA, SEVENSEGMENT_COMMON_ANODE);
    TEST_ASSERT(ret == E_OK, "Clear Common Anode returns E_OK");
    TEST_ASSERT(mock_PORTA == 0xFF, "PORTA cleared to 0xFF");

    /* Clear on uninitialized PORTC */
    ret = SevenSegment_Clear(GPIO_PORTC, SEVENSEGMENT_COMMON_CATHODE);
    TEST_ASSERT(ret == E_NOK, "Clear on uninitialized PORTC returns E_NOK");

    /* Clear with invalid type */
    ret = SevenSegment_Clear(GPIO_PORTA, 55);
    TEST_ASSERT(ret == E_NOK, "Clear with invalid display type returns E_NOK");
}

void test_SevenSegment_MultiPortIndependence(void) {
    printf("\nRunning: test_SevenSegment_MultiPortIndependence\n");
    mock_registers_reset();

    /* Write digit 3 to PORTA and digit 7 to PORTD */
    SevenSegment_WriteNumber(GPIO_PORTA, SEVENSEGMENT_COMMON_CATHODE, SEVENSEGMENT_NUM_3);
    TEST_ASSERT(mock_PORTA == expected_digits[3], "PORTA holds digit 3");
    TEST_ASSERT(mock_PORTD == 0x00, "PORTD remains 0x00");

    SevenSegment_WriteNumber(GPIO_PORTD, SEVENSEGMENT_COMMON_CATHODE, SEVENSEGMENT_NUM_7);
    TEST_ASSERT(mock_PORTD == expected_digits[7], "PORTD holds digit 7");
    TEST_ASSERT(mock_PORTA == expected_digits[3], "PORTA is unaffected by PORTD write");
}

int main(void) {
    printf("======================================\n");
    printf("  RUNNING SEVEN-SEGMENT UNIT TESTS    \n");
    printf("======================================\n");

    test_SevenSegment_UninitializedGuard();
    test_SevenSegment_Init();
    test_SevenSegment_WriteCommonCathode();
    test_SevenSegment_WriteCommonAnode();
    test_SevenSegment_InvalidInputs();
    test_SevenSegment_Clear();
    test_SevenSegment_MultiPortIndependence();

    printf("\n======================================\n");
    printf("Results: %d/%d tests passed successfully!\n", tests_passed, tests_run);
    printf("======================================\n");

    return (tests_passed == tests_run) ? 0 : 1;
}
