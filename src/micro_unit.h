#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#ifndef MICRO_UNIT_H
#define MICRO_UNIT_H

typedef char* (*mu_test)();

struct _testSuite {
    int num_tests;
    int result;
    // May change this...
    const char* name;
    mu_test* tests;
    char** results;
};

typedef struct _testSuite TestSuite;

#define newTestSuite(suite) do {                                               \
    suite = (TestSuite*) malloc(sizeof(TestSuite));                            \
    memset(suite, 0, sizeof(TestSuite));                                       \
    suite->name = __func__;                                                    \
    suite->num_tests = 0;                                                      \
} while (0)

#define destroyTestSuite(suite) do {                                           \
    int i;                                                                     \
    for (i = 0; i < suite->num_tests; i++) {                                   \
        if (suite->results[i] != 0) free(suite->results[i]);                   \
    }                                                                          \
    free(suite->results);                                                      \
    free(suite->tests);                                                        \
    free(suite);                                                               \
} while (0)

#define addTest(suite, test) do {                                              \
    suite->num_tests++;                                                        \
    suite->tests = (mu_test*) realloc(suite->tests,                            \
            sizeof(mu_test) * suite->num_tests);                               \
    suite->tests[suite->num_tests - 1] = &test;                                \
} while (0)

#define runTestSuite(suite) do {                                               \
    printf("Running Test Suite: %s\n\n", suite->name);                         \
    suite->results = malloc(sizeof(char*) * suite->num_tests);                 \
    int i;                                                                     \
    for (i = 0; i < suite->num_tests; i++) {                                   \
        suite->results[i] = 0;                                                 \
    }                                                                          \
    for (i = 0; i < suite->num_tests; i++) {                                   \
        suite->results[i] = (*suite->tests[i])();                              \
    }                                                                          \
    for (i = 0; i < suite->num_tests; i++) {                                   \
        if (suite->results[i] != 0) {                                          \
            printf("%s", suite->results[i]);                                   \
            suite->result = 1;                                                 \
        }                                                                      \
    }                                                                          \
    if (suite->result == 0) {                                                  \
        printf("\nPASSED");                                                    \
    } else {                                                                   \
        printf("\nFAILED");                                                    \
    }                                                                          \
    printf("\nTests run: %d\n", suite->num_tests);                             \
} while (0)

#define MU_BOOL_FAIL(test, b) do {                                             \
    char* message;                                                             \
    asprintf(&message, "%s() FAILED: line %d: expected %s to be %s.\n",        \
            __func__, __LINE__, #test, b);                                     \
    return message;                                                            \
} while (0)

#define MU_NUM_EQUAL_FAIL(e, a) do {                                           \
    char* message;                                                             \
    asprintf(&message, "%s() FAILED: line %d: expected %d, actual %d.\n",      \
            __func__, __LINE__, e, a);                                         \
    return message;                                                            \
} while (0)

#define MU_FL_EQUAL_FAIL(e, a) do {                                            \
    char* message;                                                             \
    asprintf(&message, "%s() FAILED: line %d: expected %g, actual %g.\n",      \
            __func__, __LINE__, e, a);                                         \
    return message;                                                            \
} while (0)

#define MU_STR_EQUAL_FAIL(e, a) do{                                            \
    char* message;                                                             \
    asprintf(&message, "%s() FAILED: line %d: expected \"%s\", actual \"%s\".\n", \
            __func__, __LINE__, e, a);                                         \
    return message;                                                            \
} while (0)

#define assertTrue(test) if (!(test)) MU_BOOL_FAIL(test, "true")
#define assertFalse(test) if ((test)) MU_BOOL_FAIL(test, "false")

#define assertEqualsInt(expected, actual) do {                                 \
    if ((expected) != (actual)) {                                              \
        MU_NUM_EQUAL_FAIL((expected), (actual));                               \
    }                                                                          \
} while (0)

#define assertEqualsDouble(expected, actual, epsilon) do {                     \
    if (!(fabs((expected) - (actual)) < epsilon)) {                            \
        MU_FL_EQUAL_FAIL((expected), (actual));                                \
    }                                                                          \
} while (0)

#define assertEqualsString(expected, actual) do {                              \
    if (strcmp((expected), (actual)) != 0) {                                   \
        MU_STR_EQUAL_FAIL((expected), (actual));                               \
    }                                                                          \
} while (0)

#endif
