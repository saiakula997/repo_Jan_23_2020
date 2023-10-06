
#include "utils.h"

int entry(void)
{
    while(1){    
        print("Hello, world!\n");
        print("-->  world!\n");
        print("Hello, %s! The answer is %d.\n", "world", 42);
        delay( TICKS_S(1) );
    }

    return 0;
}