#pragma once

#include "common.h"

#define malloc_default(v)        pvPortMalloc(v)
#define free_default(v)          vPortFree(v)
#define realloc_default(m,s)     pvPortRealloc(m,s)

#define mem_init    memory_init
#define mem_alloc   memory_alloc
#define mem_free    memory_free

void memory_init(void);
void * memory_alloc(size_t size);
void memory_free(void *);
