#include "ostream.h"

#include <stdio.h>
#include <stdarg.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>

#define OSTREAM_WRITE_BUFFER_SIZE ((size_t)64)

ostream_t * ostream_create(size_t capacity)
{
    ostream_t * ostream = malloc(sizeof(ostream));
    ostream->buffer = malloc(capacity);
    ostream->insertionPos = ostream->buffer;
    ostream->capactiy = capacity;
    return ostream;
}

void ostream_delete(ostream_t ** ostream)
{
    free((*ostream)->buffer);
    free(*ostream);
    *ostream = NULL;
}

int ostream_write(ostream_t * ostream, const char * fmt, ...)
{
    char scratch[OSTREAM_WRITE_BUFFER_SIZE];
    va_list vargs;
    int formattedOutputLength;
    int bytesRemainingInStream;

    // Write formatted output to scratch buffer

    va_start(vargs, fmt);
    formattedOutputLength = vsnprintf(scratch, OSTREAM_WRITE_BUFFER_SIZE, fmt, &vargs[0]);
    va_end(vargs);

    if (formattedOutputLength < 0)
    {
        // vsnprintf() encountered an error
        return -1;
    }

    bytesRemainingInStream = ostream->capactiy - (ostream->insertionPos - ostream->buffer);

    if  (formattedOutputLength + 1 > bytesRemainingInStream)
    {
        // Insufficient space in ostream's buffer to write formatted output
        // (with null termination)
        return -1;
    }

    // Append formatted output to ostream buffer
    memcpy(ostream->insertionPos, scratch, formattedOutputLength);
    ostream->insertionPos += formattedOutputLength;

    // Append null-byte
    *ostream->insertionPos = ((char)0x00);

    return 0;
}

int ostream_flush(ostream_t * ostream)
{
    write(STDOUT_FILENO, ostream->buffer, ostream->insertionPos - ostream->buffer);

    memset(ostream->buffer, 0, ostream->capactiy);
    ostream->insertionPos = ostream->buffer;

    return 0;

}