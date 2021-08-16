#include "ostream.h"


int main(void)
{
    ostream_t * ostream = ostream_create(128);

    ostream_write(ostream, "Hello, %s", "World!");

    ostream_write(ostream, " Boo!\r\n");

    ostream_flush(ostream);

    ostream_flush(ostream);

    ostream_write(ostream, "If you're reading this, then everything works!\r\n");
    
    ostream_flush(ostream);

    ostream_delete(&ostream);

    return 0;
}