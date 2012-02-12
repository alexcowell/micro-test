#include "micro_unit.h"
#include <stdio.h>

int mu_tests_run = 0;

static int test_truth_checks() {
    int foo = 7;

    assertTrue(foo == 7);
    assertFalse(foo == -7);

    assertTrue(1);
    assertFalse(0);

    return 0;
}

static int test_equality() {
    int i = 5;
    assertEqualsInt(5, i);
    assertEqualsInt(i, 5);

    char* s = "Hello!";
    assertEqualsString("Hello!", s);
    assertEqualsString(s, "Hello!");

    float f = 3.145;
    assertEqualsDouble(3.145, f, 0.000001);
    assertEqualsDouble(f, 3.145, 0.000001);

    double d = 3.14678364873;
    assertEqualsDouble(3.14678364873, d, 0.0000000000001);
    assertEqualsDouble(d, 3.14678364873, 0.0000000000001);

    return 0;
}

static int all_tests() {
    test(test_truth_checks);
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
