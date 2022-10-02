#include <stdio.h>
#include <stdlib.h>

#include "unit_test.h"

void test_foo() {
	UT_TEST();
	UT_NAME("test_foo");
	uint i = 1;
	UT_ASSERT("i != 1 is false", i != 1);
	UT_SUCCEED();
}

void test_bar() {
	UT_TEST();
	UT_NAME("test_bar");
	UT_ASSERT("1 == 1", 1 == 1);
	UT_SUCCEED();
}

int main(void) {
	printf("%s\n", __FILE__);

	UT_INIT();

	test_foo();
	test_bar();

	UT_INFO();

	UT_END();
}
