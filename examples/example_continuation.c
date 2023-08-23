#include "stdlib.h"
#include "stdio.h"
#include "stdint.h"
#include "continuation.h"
#include "unistd.h"

continuation_marker_t marker;

int task1()
{
    printf("First printf by calling task1, then mark continuation\n");
    continuation_mark(marker);
    printf("Resume to the marker\n");
    sleep(1);
    continuation_resume(marker);
}

int main()
{
    coninuation_init(marker);

    task1();

    return 0;
}