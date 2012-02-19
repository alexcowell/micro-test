#include "micro_unit.h"
#include <stdio.h>

static char* test_truth_checks() {
    int foo = 7;

    assertTrue(foo == 7);
    assertFalse(foo == -7);

    assertTrue(1);
    assertFalse(1);

    return 0;
}

static char* test_equality() {
    int i = 5;
    assertEqualsInt(i, 5);
    assertEqualsInt(5, i);

    char* s = "Hello!";
    assertEqualsString("Hello!", s);
    assertEqualsString(s, "Hello!");

    float f = 3.145;
    assertEqualsDouble(3.145, f, 0.000001);
    assertEqualsDouble(f, 3.145, 0.000001);

    double d = 3.12678364873;
    assertEqualsDouble(3.14678364873, d, 0.0000000000001);
    assertEqualsDouble(d, 3.14678364873, 0.0000000000001);

    return 0;
}

static char* test_new_truth_checks() {
    assertTrue(1);
    assertFalse(1);

    return 0;
}

static char* test_another_dummy() {
    int i = 3;
    assertTrue(i == 2);
    assertFalse(i == 4);

    return 0;
}

int main(int argc, char** argv) {
    TestSuite* suite;
    newTestSuite(suite);

    addTest(suite, test_truth_checks);
    addTest(suite, test_equality);
    addTest(suite, test_new_truth_checks);
    addTest(suite, test_another_dummy);

    runTestSuite(suite);

    destroyTestSuite(suite);

    return 0;
}
