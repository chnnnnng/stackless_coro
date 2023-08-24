#pragma once

#include "task.h"

typedef struct sem_t
{
    uint32_t    count;
} sem_t;

#define SEM_INITIAL {.count = 0}

#define sem_init(pSem)  (pSem)->count = 0

#define sem_give_many(pSem, num)    (pSem)->count += ((uint32_t)num)

#define sem_give(pSem)  sem_give_many((pSem), 1)

#define sem_take(pSem)                      \
    do{                                     \
        task_wait_until((pSem)->count > 0); \
        --((pSem)->count);                  \
    }while(0)