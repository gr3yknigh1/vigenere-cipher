/*
 * FILE          vigenere_cli.c
 *
 * AUTHORS
 *               Ilya Akkuzin <gr3yknigh1@gmail.com>
 *
 * NOTICE        (c) Copyright 2024 by Ilya Akkuzin. All rights reserved.
 */

#include <stdio.h>
#include <stdlib.h>

#include <vigenere.h>

#if defined(WIN32) || defined(WIN64)
#define PROG_NAME "vigenere_cli.exe"
#else
#define PROG_NAME "vigenere_cli"
#endif

#define COMMAND_ENCRYPT_NAME "encrypt"
#define COMMAND_DECRYPT_NAME "decrypt"

static void
PrintHelp(void)
{
    fprintf(stdout, "%s [command] [arguments...]\n", PROG_NAME);
    fprintf(stdout, "    encrypt    [message] [key]\n");
    fprintf(stdout, "    decrypt    [message] [key]\n");
}

int
main(int argc, char *argv[])
{
    int ret = 0;

    enum {
        ARG_EXEC,
        ARG_COMMAND,
        ARG_MESSAGE,
        ARG_KEY,
        ARG_COUNT_,
    };

    if (argc < ARG_COUNT_) {
        PrintHelp();
        fputs("There are too few arguments", stderr);
        ret = 1;
    } else {
        const char *command = argv[ARG_COMMAND];
        const char *message = argv[ARG_MESSAGE];
        const char *key = argv[ARG_KEY];

        size_t messageLength = strlen(message);

        size_t resultBufferSize = messageLength + 1;
        char *resultBuffer = malloc(resultBufferSize);
        memset(resultBuffer, 0, resultBufferSize);

        if (strcmp(command, COMMAND_ENCRYPT_NAME) == 0) {
            Vigenere_Encrypt(resultBuffer, resultBufferSize, message, key);
        } else if (strcmp(command, COMMAND_DECRYPT_NAME) == 0) {
            Vigenere_Decrypt(resultBuffer, resultBufferSize, message, key);
        } else {
            PrintHelp();
            fprintf(stderr, "Unknown command: %s\n", command);
            ret = 1;
        }

        if (ret == 0) {
            resultBuffer[messageLength] = 0;
            printf("%s\n", resultBuffer);
        }

        if (resultBuffer != 0) {
            free(resultBuffer);
        }
    }

    return ret;
}
