#ifndef OSTREAM_H
#define OSTREAM_H

#include <stddef.h>

typedef struct {
    char * buffer;
    char * insertionPos;
    size_t capactiy;
} ostream_t;

#ifdef __cplusplus
extern "C" {
#endif

ostream_t * ostream_create(size_t capacity);

void ostream_delete(ostream_t ** ostream);

int ostream_write(ostream_t * ostream, const char * fmt, ...);

int ostream_flush(ostream_t * ostream);

#ifdef __cplusplus
}
#endif

#endif