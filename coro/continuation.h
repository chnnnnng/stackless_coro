#pragma once

#include "macro_util.h"

typedef void * continuation_marker_t;


#define coninuation_init(marker)                \
    marker = NULL


#define continuation_resume(marker)             \
    if(marker != NULL)                          \
        goto *(marker)


#define continuation_mark(marker)               \
    FL_CONCAT(CONT_MARKER_, __LINE__):             \
    marker = && FL_CONCAT(CONT_MARKER_, __LINE__)


#define continuation_end()

