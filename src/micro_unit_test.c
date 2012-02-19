#include "micro_unit.h"
#include <stdio.h>

int mu_tests_run = 0;

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

static int all_tests() {

    // TODO: Loopify and add into TestSuite feature.
    //       Adding tests to the test suite will keep track of the number of
    //       tests. Each test can only have up to 1 error message.
    int num_tests = 4;
    char* results[num_tests];
    int hasFailed = 0;

    int i;
    for (i = 0; i < num_tests; i++) {
        results[i] = 0;
    }

    if (test_new_truth_checks() != 0) {
        results[0] = test_new_truth_checks();
        hasFailed = 1;
    }

    if (test_another_dummy() != 0) {
        results[1] = test_another_dummy();
        hasFailed = 1;
    }

    if (test_truth_checks() != 0) {
        results[2] = test_truth_checks();
        hasFailed = 1;
    }

    if (test_equality() != 0) {
        results[3] = test_equality();
        hasFailed = 1;
    }

    for (i = 0; i < num_tests; i++) {
        if (results[i] != 0) printf("%s", results[i]);
    }

    for (i = 0; i < num_tests; i++) {
        if (results[i] != 0) free(results[i]);
    }

    return hasFailed;
}

int main(int argc, char** argv) {
    int result = all_tests();

    if (result == 0) {
        printf("PASSED\n");
    }
    //printf("\nTests run: %d\n", mu_tests_run);

    return 0;
}
