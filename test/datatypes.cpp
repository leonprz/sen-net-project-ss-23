#include "unity.h"
#include "datatypes.hpp"

inline const uint32_t MAX_UINT24 = 16777215;

void setUp()
{
}

void tearDown()
{
}

void test_uint24_construct()
{
	TEST_ASSERT_EQUAL(0, uint24(0));
	TEST_ASSERT_EQUAL(42, uint24(42));
	TEST_ASSERT_EQUAL(MAX_UINT24, uint24(MAX_UINT24));

	TEST_ASSERT_EQUAL(0, uint24(MAX_UINT24 + 1));
	TEST_ASSERT_EQUAL(MAX_UINT24, uint24(-1));

	TEST_ASSERT_EQUAL(0, uint24(0.5));
	TEST_ASSERT_EQUAL(42, uint24(42.235679));
}

void test_uint24_leftShift()
{
	TEST_ASSERT_EQUAL(256, uint24(1) << 8);
}

void test_uint24_rightShift()
{
	TEST_ASSERT_EQUAL(1, uint24(256) >> 8);
}

int main()
{
	UNITY_BEGIN();

	RUN_TEST(test_uint24_construct);
	RUN_TEST(test_uint24_leftShift);
	RUN_TEST(test_uint24_rightShift);

	return UNITY_END();
}
