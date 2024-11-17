#if !defined(VIGENERE_H_INCLUDED)
/*
 * FILE          vigenere.h
 *
 * AUTHORS
 *               Ilya Akkuzin <gr3yknigh1@gmail.com>
 *
 * NOTICE        (c) Copyright 2024 by Ilya Akkuzin. All rights reserved.
 */
#define VIGENERE_H_INCLUDED

#include <stdlib.h> // size_t

#if defined(__cplusplus)
#define VIGENERE_CXX_DETECTED
#endif

#if defined(VIGENERE_CXX_DETECTED)
#define VIGENERE_API extern "C"
#else
#define VIGENERE_API
#endif

/*
 * @breaf Encrypts message and writes result to specified buffer.
 * @param outBuffer Pointer to result buffer. There shall be enough memory to store original message.
 * @param outBufferSize Size of result buffer and also `message`'s `length - 1`.
 * @param messsage Original message.
 * @param key Key.
 */
VIGENERE_API void Vigenere_Encrypt(char *outBuffer, size_t outBufferSize, const char *message, const char *key);

/*
 * @breaf Descrypts message and writes result to specified buffer.
 * @param outBuffer Pointer to result buffer. There shall be enough memory to store original message.
 * @param outBufferSize Size of result buffer and also `message`'s `length - 1`.
 * @param messsage Original message.
 * @param key Key.
 */
VIGENERE_API void Vigenere_Decrypt(char *outBuffer, size_t outBufferSize, const char *message, const char *key);

#endif // VIGENERE_H_INCLUDED
