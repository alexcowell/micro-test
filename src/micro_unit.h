#include <math.h>
#include <stdio.h>
#include <string.h>

#ifndef MICRO_UNIT_H
#define MICRO_UNIT_H

extern int mu_tests_run;

#define MU_BOOL_FAIL(test, b) printf("%s() FAILED: line %d: expected %s to be %s.\n", __func__, __LINE__, #test, b)
#define MU_NUM_EQUAL_FAIL(e, a) printf("%s() FAILED: line %d: expected %d, actual %d.\n", __func__, __LINE__, e, a)
#define MU_FL_EQUAL_FAIL(e, a) printf("%s() FAILED: line %d: expected %g, actual %g.\n", __func__, __LINE__, e, a)
#define MU_STR_EQUAL_FAIL(e, a) printf("%s() FAILED: line %d: expected \"%s\", actual \"%s\".\n", __func__, __LINE__, e, a)

#define assertTrue(test) do { if (!(test)) { MU_BOOL_FAIL(test, "true"); return 1; } } while (0)
#define assertFalse(test) do { if ((test)) { MU_BOOL_FAIL(test, "false"); return 1; } } while (0)

#define assertEqualsInt(expected, actual) do { \
	if ((expected) != (actual)) { \
		MU_NUM_EQUAL_FAIL((expected), (actual)); \
		return 1; \
	} \
} while (0)

#define assertEqualsFloat(expected, actual, epsilon) do { \
	if (!(fabs((expected) - (actual)) < epsilon)) { \
		MU_FL_EQUAL_FAIL((expected), (actual)); \
		return 1; \
	} \
} while (0)

#define assertEqualsString(expected, actual) do { \
	if (strcmp((expected), (actual)) != 0) { \
		MU_STR_EQUAL_FAIL((expected), (actual)); \
		return 1; \
	} \
} while (0)

#define test(test) do { int r = test(); mu_tests_run++; if (r) return r; } while (0)

#endif
