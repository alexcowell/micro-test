#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#ifndef MICRO_UNIT_H
#define MICRO_UNIT_H

extern int mu_tests_run;

// TODO: Message size? Can it be calculated from the base message and the params?
#define MU_BOOL_FAIL(test, b) do {                                             \
    char* message = (char*) malloc(sizeof(char) * 80);                         \
    sprintf(message, "%s() FAILED: line %d: expected %s to be %s.\n",          \
            __func__, __LINE__, #test, b);                                     \
    return message;                                                            \
} while (0)

#define MU_NUM_EQUAL_FAIL(e, a) printf("%s() FAILED: line %d: expected %d, actual %d.\n", __func__, __LINE__, e, a)
#define MU_FL_EQUAL_FAIL(e, a) printf("%s() FAILED: line %d: expected %g, actual %g.\n", __func__, __LINE__, e, a)
#define MU_STR_EQUAL_FAIL(e, a) printf("%s() FAILED: line %d: expected \"%s\", actual \"%s\".\n", __func__, __LINE__, e, a)

#define assertTrue(test) if (!(test)) MU_BOOL_FAIL(test, "true")
#define assertFalse(test) if ((test)) MU_BOOL_FAIL(test, "false")

#define assertEqualsInt(expected, actual) do {                                 \
    if ((expected) != (actual)) {                                              \
        MU_NUM_EQUAL_FAIL((expected), (actual));                               \
        return 1;                                                              \
    }                                                                          \
} while (0)

#define assertEqualsDouble(expected, actual, epsilon) do {                     \
    if (!(fabs((expected) - (actual)) < epsilon)) {                            \
        MU_FL_EQUAL_FAIL((expected), (actual));                                \
        return 1;                                                              \
    }                                                                          \
} while (0)

#define assertEqualsString(expected, actual) do {                              \
    if (strcmp((expected), (actual)) != 0) {                                   \
        MU_STR_EQUAL_FAIL((expected), (actual));                               \
        return 1;                                                              \
    }                                                                          \
} while (0)

#define test(test) do { int r = test(); mu_tests_run++; if (r) return r; } while (0)

#endif
