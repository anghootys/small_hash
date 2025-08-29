#ifndef _SH_TEST_H_
#define _SH_TEST_H_

#include <stdio.h>

#define TESTING(S) printf("\033[36m[ TEST ]\033[0m %s\n", S)
#define TEST_PASS  printf("\033[32m[PASSED]\033[0m\n")
#define TEST_FAIL  printf("\033[31m[FAILED]\033[0m\n")

#endif
