/*
 * FILE          vigenere.c
 *
 * AUTHORS
 *               Ilya Akkuzin <gr3yknigh1@gmail.com>
 *
 * NOTICE        (c) Copyright 2024 by Ilya Akkuzin. All rights reserved.
 */
#include "vigenere.h"

#include <assert.h> // assert
#include <ctype.h>  // isupper

#define ASCII_ALPHA_COUNT ('z' - 'a' + 1)
#define ASCII_UPPER_FIRST 'A'
#define ASCII_LOWER_FIRST 'a'

static size_t
ModValueAndLoop(size_t value, size_t mod, size_t min, size_t max)
{
    size_t result = value + mod;

    while (result > max) {
        result = min + (result - max) - 1;
    }

    while (result < min) {
        result = max - (min - result) + 1;
    }

    return result;
}

VIGENERE_API void
Vigenere_Encrypt(char *outBuffer, size_t outBufferSize, const char *message, const char *key)
{
    assert(strlen(message) == (outBufferSize - 1));
    assert(strlen(key) == strlen(message));

    for (size_t messageIndex = 0; messageIndex < outBufferSize; ++messageIndex) {
        char c = message[messageIndex];
        char k = key[messageIndex];

        int ascii_first = isupper(c) ? ASCII_UPPER_FIRST : ASCII_LOWER_FIRST;

        int encryptedChar = ((c + k) % ASCII_ALPHA_COUNT) + ascii_first;

        outBuffer[messageIndex] = encryptedChar;
    }
}

VIGENERE_API void
Vigenere_Decrypt(char *outBuffer, size_t outBufferSize, const char *message, const char *key)
{
    assert(strlen(message) == (outBufferSize - 1));
    assert(strlen(key) == strlen(message));

    for (size_t messageIndex = 0; messageIndex < outBufferSize; ++messageIndex) {
        char c = message[messageIndex];
        char k = key[messageIndex];

        int ascii_first = isupper(c) ? ASCII_UPPER_FIRST : ASCII_LOWER_FIRST;

        int encryptedChar = (((c - k) + ASCII_ALPHA_COUNT) % ASCII_ALPHA_COUNT) + ascii_first;

        outBuffer[messageIndex] = encryptedChar;
    }
}
