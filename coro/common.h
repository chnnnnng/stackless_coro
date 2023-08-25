#ifndef __COMMON_HEADER_H
#define __COMMON_HEADER_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include <assert.h>
#include <stdbool.h>


typedef enum
{
    RET_OK = 0,
    RET_ERR,
    RET_TO,
} retval;

typedef uint64_t ltime_t;             //注意：64位无符号整数在32位机器上打印要使用 %llu


#endif
