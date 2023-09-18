
#include "cmock.h"
#include "source.h"

void test_addOneToByte(void)
{
    volatile static uint8_t retVal = 0;
    retVal = addOneToByte((const uint8_t)2);
    TEST_ASSERT_EQUAL_HEX8(3, retVal);
    retVal = addOneToByte((const uint8_t)255);
    TEST_ASSERT_EQUAL_HEX8(0, retVal);
}
