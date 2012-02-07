#include "micro_unit.h"
#include <stdio.h>

int mu_tests_run = 0;

int foo = 7;
int bar = 5;

static int test_foo() {
	assertTrue(foo == 7);
	assertFalse(foo == -7);

	return 0;
}

static int test_bar() {
	assertTrue(bar == 5);
	return 0;
}

static int test_equality() {
	int baz = 5;
	assertEqualsInt(5, baz);
	assertEqualsInt(baz, 5);

	char* s = "Hello!";
	assertEqualsString("Hello!", s);
	assertEqualsString(s, "Hello!");

	float f = 3.145;
	assertEqualsFloat(3.145, f, 0.000001);
	assertEqualsFloat(f, 3.145, 0.000001);

	double d = 3.14678364873;
	assertEqualsFloat(3.14678364873, d, 0.0000000000001);
	assertEqualsFloat(d, 3.14678364873, 0.0000000000001);

	return 0;
}

static int all_tests() {
	test(test_foo);
	test(test_bar);
	test(test_equality);

	return 0;
}

int main(int argc, char** argv) {
	int result = all_tests();

	if (result == 0) {
		printf("PASSED\n");
	}
	printf("\nTests run: %d\n", mu_tests_run);

	return result != 0;
}
