/*
 * FILE          tests/test_basic.c
 *
 * AUTHORS
 *               Ilya Akkuzin <gr3yknigh1@gmail.com>
 *
 * NOTICE        (c) Copyright 2024 by Ilya Akkuzin. All rights reserved.
 *
 * REFERENCE
 *
 *  - Source of shifted messages: <https://cryptii.com/pipes/vigenere-cipher>
 */

#include <nocheck/nocheck.h>

#include <string.h>

#define NOC_TEXPECT_STRISEQ(CASEPTR, STR0, STR1) NOC_TEXPECT((CASEPTR), strcmp((STR0), (STR1)) == 0)

#define _ENCRYPT_TEST_CASE(CASEPTR, IN_STR, EXP_STR, KEY) \
    do { \
        size_t resultBufferSize = strlen((IN_STR)) + 1; \
        char *resultBuffer = (char *)calloc(1, resultBufferSize); \
        Vigenere_Encrypt(resultBuffer, resultBufferSize, (IN_STR), (KEY)); \
        NOC_TEXPECT_STRISEQ((CASEPTR), resultBuffer, (EXP_STR)); \
        free(resultBuffer); \
    } while (0)

#define _DECRYPT_TEST_CASE(CASEPTR, IN_STR, EXP_STR, KEY) \
    do { \
        size_t resultBufferSize = strlen((IN_STR)) + 1; \
        char *resultBuffer = (char *)calloc(1, resultBufferSize); \
        Vigenere_Decrypt(resultBuffer, resultBufferSize, (IN_STR), (KEY)); \
        NOC_TEXPECT_STRISEQ((CASEPTR), resultBuffer, (EXP_STR)); \
        free(resultBuffer); \
    } while (0)

void
TC_Basic0(NOC_TestCase *c)
{
    _ENCRYPT_TEST_CASE(c, "ATTACKATDAWN", "LXFOPVEFRNHR", "LEMONLEMONLE");
    _ENCRYPT_TEST_CASE(c, "LXFOPVEFRNHR", "ATTACKATDAWN", "LEMONLEMONLE");
}

int
main(void)
{
    NOC_TestSuite *suite = NOC_TestSuiteMake("basic");
    NOC_TestSuiteAddCase(suite, "Basic0", TC_Basic0);

    int exitCode = NOC_TestSuiteExecute(suite);
    NOC_TestSuiteDestroy(suite);
    return exitCode;
}
